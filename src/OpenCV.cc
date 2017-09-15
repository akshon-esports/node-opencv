#include "OpenCV.h"
#include "Matrix.h"
#include <nan.h>

class HybridAsyncWorker : public Nan::AsyncWorker {
public:
  HybridAsyncWorker(): AsyncWorker{ nullptr } {}

  virtual Local<Value> GetResult() = 0;

protected:
  void HandleOKCallback() override final {
    Nan::HandleScope scope;

    Local<Value> result = GetResult();

    Local<Value> callback_or_resolver = GetFromPersistent(0u);
    if (callback_or_resolver->IsFunction()) {
      Local<Value> argv[2] = { Nan::Undefined(), result };

      Nan::TryCatch try_catch;
      Local<Function>::Cast(callback_or_resolver)->Call(Nan::GetCurrentContext()->Global(), 2, argv);
      if (try_catch.HasCaught()) {
        Nan::FatalException(try_catch);
      }
    } else {
      Local<Promise::Resolver>::Cast(callback_or_resolver)->Resolve(result);
      Isolate::GetCurrent()->RunMicrotasks();
    }
  }

  void HandleErrorCallback() override final {
    Nan::HandleScope scope;

    Local<Value> error = Nan::Error(ErrorMessage());

    Local<Value> callback_or_resolver = GetFromPersistent(0u);
    if (callback_or_resolver->IsFunction()) {
      Local<Value> argv[1] = { error };

      Nan::TryCatch try_catch;
      Local<Function>::Cast(callback_or_resolver)->Call(Nan::GetCurrentContext()->Global(), 1, argv);
      if (try_catch.HasCaught()) {
        Nan::FatalException(try_catch);
      }
    } else {
      Local<Promise::Resolver>::Cast(callback_or_resolver)->Reject(error);
      Isolate::GetCurrent()->RunMicrotasks();
    }
  }
};

void OpenCV::Init(Local<Object> target) {
  Nan::HandleScope scope;

  // Version string.
  target->Set(Nan::New<String>("version").ToLocalChecked(), Nan::New<String>(CV_VERSION).ToLocalChecked());

  Nan::SetMethod(target, "readImage", ReadImage);
  Nan::SetMethod(target, "readImageSync", ReadImageSync);
  Nan::SetMethod(target, "readImageMulti", ReadImageMulti);
  Nan::SetMethod(target, "readImageMultiSync", ReadImageMultiSync);
}

class BaseImageReadingAsyncWorker : public HybridAsyncWorker {
public:
  BaseImageReadingAsyncWorker() : HybridAsyncWorker() {}

  void SetImreadMode(cv::ImreadModes mode) {
    this->mode = mode;
  }

protected:
  cv::ImreadModes mode = cv::IMREAD_COLOR;
};

class ReadImageAsyncWorker : public BaseImageReadingAsyncWorker {
public:
  ReadImageAsyncWorker(std::string const path) : BaseImageReadingAsyncWorker(), path(path) {}
  ReadImageAsyncWorker(unsigned const length, uint8_t* const data) : BaseImageReadingAsyncWorker(), length(length), data(data) {}

  void Execute() override {
    try {
      if (data == nullptr) {
        mat = cv::imread(path, mode);
      } else {
        cv::Mat mbuf(length, 1, CV_64FC1, data);
        mat = cv::imdecode(mbuf, mode);
      }
    } catch (cv::Exception& e) {
      return SetErrorMessage(e.what());
    }

    if (mat.empty()) {
      SetErrorMessage("Could not open or find the image");
    }
  }

  Local<Value> GetResult() {
    return Matrix::NewInstance(mat);
  }

private:
    std::string const path = nullptr;

    unsigned const length = 0;
    uint8_t* const data = nullptr;

    cv::Mat mat;
};

NAN_METHOD(OpenCV::ReadImage) {
  Nan::EscapableHandleScope scope;

  FUNCTION_MIN_ARGUMENTS(1, "readImage()");

  ReadImageAsyncWorker* worker;
  if (info[0]->IsString()) {
    worker = new ReadImageAsyncWorker(std::string(*Nan::Utf8String(info[0]->ToString())));
  } else if (Buffer::HasInstance(info[0])) {
    worker = new ReadImageAsyncWorker(Buffer::Length(info[0]->ToObject()), reinterpret_cast<uint8_t *>(Buffer::Data(info[0]->ToObject())));
  } else {
    return THROW_INVALID_ARGUMENT_TYPE(0, "a string or a Buffer");
  }

  int argumentOffset = 1;
  INT_FROM_ARGS(mode, 1) else {
    mode = cv::IMREAD_ANYCOLOR;
    argumentOffset = 0;
  }

  worker->SetImreadMode(static_cast<cv::ImreadModes>(mode));

  bool isCallback = false;
  if (info.Length() > 1 + argumentOffset) {
    if (!info[1 + argumentOffset]->IsFunction()) {
      return THROW_INVALID_ARGUMENT_TYPE(1 + argumentOffset, "a function");
    }

    isCallback = true;
  }

  if (isCallback) {
    worker->SaveToPersistent(0u, info[1 + argumentOffset]);
  } else {
    Local<Promise::Resolver> resolver = Promise::Resolver::New(Nan::GetCurrentContext()).ToLocalChecked();
    worker->SaveToPersistent(0u, resolver);
    info.GetReturnValue().Set(resolver->GetPromise());
  }

  Nan::AsyncQueueWorker(worker);
}

NAN_METHOD(OpenCV::ReadImageSync) {
  Nan::EscapableHandleScope scope;

  FUNCTION_MIN_ARGUMENTS(1, "readImage");

  ReadImageAsyncWorker *worker;
  if (info[0]->IsString()) {
    worker = new ReadImageAsyncWorker(std::string(*Nan::Utf8String(info[0]->ToString())));
  } else if (Buffer::HasInstance(info[0])) {
    worker = new ReadImageAsyncWorker(Buffer::Length(info[0]->ToObject()), reinterpret_cast<uint8_t *>(Buffer::Data(info[0]->ToObject())));
  } else {
    return Nan::ThrowTypeError("Argument 1 must be a string or a Buffer");
  }

  DEFAULT_INT_FROM_ARGS(mode, 1, cv::IMREAD_ANYCOLOR);
  worker->SetImreadMode(static_cast<cv::ImreadModes>(mode));
  worker->Execute();
  info.GetReturnValue().Set(worker->GetResult());
  delete worker;
}

#if CV_MAJOR_VERSION >= 3
class ReadImageMultiAsyncWorker : public BaseImageReadingAsyncWorker {
public:
  ReadImageMultiAsyncWorker(const std::string &path) : BaseImageReadingAsyncWorker(), path(path) {}

  void Execute() override {
    try {
      cv::imreadmulti(path, mats, mode);
    } catch (cv::Exception& e) {
      return SetErrorMessage(e.what());
    }

    if (mats.empty()) {
      SetErrorMessage("Could not open or find the file");
    }
  }

  Local<Value> GetResult() {
    Local<Array> out = Nan::New<Array>();
    for (cv::Mat &mat : mats) {
      Nan::Set(out, out->Length(), Matrix::NewInstance(mat));
    }

    return out;
  }

private:
  const std::string path = nullptr;

  std::vector<cv::Mat> mats;
};
#endif

NAN_METHOD(OpenCV::ReadImageMulti) {
#if CV_MAJOR_VERSION >= 3
  Nan::EscapableHandleScope scope;

  FUNCTION_MIN_ARGUMENTS(1, "readImage");

  int argumentOffset = 1;
  INT_FROM_ARGS(mode, 1) else {
    mode = cv::IMREAD_ANYCOLOR;
    argumentOffset = 0;
  }

  bool isCallback = false;
  if (info.Length() > 1 + argumentOffset) {
    if (!info[1 + argumentOffset]->IsFunction()) {
      return THROW_INVALID_ARGUMENT_TYPE(1 + argumentOffset, "a function");
    }

    isCallback = true;
  }

  ASSERT_STRING_FROM_ARGS(path, 0);

  ReadImageMultiAsyncWorker* worker = new ReadImageMultiAsyncWorker(path);

  worker->SetImreadMode(static_cast<cv::ImreadModes>(mode));

  if (isCallback) {
    worker->SaveToPersistent(0u, info[1 + argumentOffset]);
} else {
    Local<Promise::Resolver> resolver = Promise::Resolver::New(Nan::GetCurrentContext()).ToLocalChecked();
    worker->SaveToPersistent(0u, resolver);
    info.GetReturnValue().Set(resolver->GetPromise());
  }

  Nan::AsyncQueueWorker(worker);
#else
  Nan::ThrowError("only supported in opencv 3.x")
#endif
}

NAN_METHOD(OpenCV::ReadImageMultiSync) {
#if CV_MAJOR_VERSION >= 3
  Nan::EscapableHandleScope scope;

  FUNCTION_MIN_ARGUMENTS(1, "readImage");
  ASSERT_STRING_FROM_ARGS(path, 0);
  DEFAULT_INT_FROM_ARGS(mode, 1, cv::IMREAD_ANYCOLOR);

  ReadImageMultiAsyncWorker worker(path);
  worker.SetImreadMode(static_cast<cv::ImreadModes>(mode));
  worker.Execute();
  info.GetReturnValue().Set(worker.GetResult());
#else
  Nan::ThrowError("only supported in opencv 3.x")
#endif
}

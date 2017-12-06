#include "../common.h"

#include "opencv2/imgcodecs.hpp"

#include "../common/async.h"
#include "../common/Matrix.h"

using namespace ncv::common;

namespace ncv {
  
  namespace imgcodecs {

    class BaseImageReadingAsyncWorker : public HybridAsyncWorker {
    public:
      BaseImageReadingAsyncWorker() : HybridAsyncWorker() {}

      void SetImreadMode(cv::ImreadModes mode) {
        this->mode = mode;
      }

      Local<Value> GetResult() {
        Nan::EscapableHandleScope scope;
        return scope.Escape(Matrix::NewInstance(mat));
      }

    protected:
      cv::ImreadModes mode = cv::IMREAD_COLOR;

      cv::Mat mat;
    };

    class ReadImageAsyncWorker : public BaseImageReadingAsyncWorker {
    public:
      ReadImageAsyncWorker(std::string const path) : BaseImageReadingAsyncWorker(), path(path) {}

      void Execute() override {
        try {
          mat = cv::imread(path, mode);
        } catch (cv::Exception& e) {
          return SetErrorMessage(e.what());
        }

        if (mat.empty()) {
          SetErrorMessage("Could not open or find the image");
        }
      }

    private:
      std::string const path = "";
    };

    class DecodeImageAsyncWorker : public BaseImageReadingAsyncWorker {
    public:
      DecodeImageAsyncWorker(unsigned const length, uint8_t* const data) : BaseImageReadingAsyncWorker(), length(length), data(data) {}

      void Execute() override {
        try {
          cv::Mat mbuf(length, 1, CV_64FC1, data);
          mat = cv::imdecode(mbuf, mode);
        } catch (cv::Exception& e) {
          return SetErrorMessage(e.what());
        }

        if (mat.empty()) {
          SetErrorMessage("Could not open or find the image");
        }
      }

    private:
      unsigned const length = 0;
      uint8_t* const data = nullptr;
    };

    class WriteImageAsyncWorker : public HybridAsyncWorker {
    public:
      WriteImageAsyncWorker(std::string const &filename, cv::_InputArray const &img, std::vector<int> const &params) : HybridAsyncWorker(), filename(filename), img(img), params(params) {};

      void Execute() override {
        try {
          cv::imwrite(filename, img, params);
        } catch (cv::Exception& e) {
          return SetErrorMessage(e.what());
        }
      }

    private:
      std::string const filename = "";
      cv::_InputArray const img;
      std::vector<int> const params;
    };

    NAN_METHOD(ImageRead) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(1, 3);
      Nan::HandleScope scope;
      ASSERT_STRING_FROM_ARGS(filename, 0);
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

      ReadImageAsyncWorker* worker = new ReadImageAsyncWorker(filename);
      worker->SetImreadMode(static_cast<cv::ImreadModes>(mode));

      if (isCallback) {
        worker->SaveToPersistent(0u, info[1 + argumentOffset]);
      } else {
        Local<Promise::Resolver> resolver = Promise::Resolver::New(Nan::GetCurrentContext()).ToLocalChecked();
        worker->SaveToPersistent(0u, resolver);
        info.GetReturnValue().Set(resolver->GetPromise());
      }

      Nan::AsyncQueueWorker(worker);
    }

    NAN_METHOD(ImageReadSync) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(1, 2);
      Nan::HandleScope scope;
      ASSERT_STRING_FROM_ARGS(filename, 0);
      DEFAULT_INT_FROM_ARGS(mode, 1, cv::IMREAD_ANYCOLOR);

      ReadImageAsyncWorker worker(filename);
      worker.SetImreadMode(static_cast<cv::ImreadModes>(mode));
      worker.Execute();

      if (worker.HasError()) {
        return Nan::ThrowError(worker.Error());
      }

      info.GetReturnValue().Set(worker.GetResult());
    }

    NAN_METHOD(ImageDecode) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(1, 3);
      Nan::EscapableHandleScope scope;
      if (!Buffer::HasInstance(info[0])) {
        return THROW_INVALID_ARGUMENT_TYPE(0, "a Buffer");
      }

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

      DecodeImageAsyncWorker* worker = new DecodeImageAsyncWorker(Buffer::Length(info[0]->ToObject()), reinterpret_cast<uint8_t *>(Buffer::Data(info[0]->ToObject())));
      worker->SetImreadMode(static_cast<cv::ImreadModes>(mode));

      if (isCallback) {
        worker->SaveToPersistent(0u, info[1 + argumentOffset]);
      } else {
        Local<Promise::Resolver> resolver = Promise::Resolver::New(Nan::GetCurrentContext()).ToLocalChecked();
        worker->SaveToPersistent(0u, resolver);
        info.GetReturnValue().Set(resolver->GetPromise());
      }

      Nan::AsyncQueueWorker(worker);
    }

    NAN_METHOD(ImageDecodeSync) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(1, 2);
      Nan::HandleScope scope;
      if (!Buffer::HasInstance(info[0])) {
        return THROW_INVALID_ARGUMENT_TYPE(0, "a Buffer");
      }
      Local<Object> buffer = info[0]->ToObject();
      DEFAULT_INT_FROM_ARGS(mode, 1, cv::IMREAD_ANYCOLOR);

      DecodeImageAsyncWorker worker(Buffer::Length(buffer), reinterpret_cast<uint8_t *>(Buffer::Data(buffer)));
      worker.SetImreadMode(static_cast<cv::ImreadModes>(mode));
      worker.Execute();

      if (worker.HasError()) {
        return Nan::ThrowError(worker.Error());
      }

      info.GetReturnValue().Set(worker.GetResult());
    }

    NAN_METHOD(ImageWrite) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(2, 3);
      Nan::HandleScope scope;
      ASSERT_STRING_FROM_ARGS(filename, 0);
      ASSERT_INPUTARRAY_FROM_ARGS(img, 1);

      int argumentOffset = 0;
      std::vector<int> params;
      if (info.Length() > 2 && info[2]->IsArray()) {
        Local<Array> numbers = Local<Array>::Cast(info[2]);
        for (unsigned i = 0; i < numbers->Length(); ++i) {
          Local<Value> val = Nan::Get(numbers, i).ToLocalChecked();
          if (!val->IsNumber()) {
            return Nan::ThrowError(ERROR_INVALID_ARGUMENTS);
          }
          params.push_back(val->Int32Value());
        }
        argumentOffset += 1;
      }

      bool isCallback = false;

      if (info.Length() > 1 + argumentOffset) {
        if (!info[1 + argumentOffset]->IsFunction()) {
          return THROW_INVALID_ARGUMENT_TYPE(1 + argumentOffset, "a function");
        }

        isCallback = true;
      }

      WriteImageAsyncWorker* worker = new WriteImageAsyncWorker(filename, img, params);

      if (isCallback) {
        worker->SaveToPersistent(0u, info[1 + argumentOffset]);
      } else {
        Local<Promise::Resolver> resolver = Promise::Resolver::New(Nan::GetCurrentContext()).ToLocalChecked();
        worker->SaveToPersistent(0u, resolver);
        info.GetReturnValue().Set(resolver->GetPromise());
      }

      Nan::AsyncQueueWorker(worker);
    }

    NAN_METHOD(ImageWriteSync) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(2, 3);
      Nan::HandleScope scope;
      ASSERT_STRING_FROM_ARGS(filename, 0);
      ASSERT_INPUTARRAY_FROM_ARGS(img, 1);
      std::vector<int> params;
      if (info.Length() > 2 && info[2]->IsArray()) {
        Local<Array> numbers = Local<Array>::Cast(info[2]);
        for (unsigned i = 0; i < numbers->Length(); ++i) {
          Local<Value> val = Nan::Get(numbers, i).ToLocalChecked();
          if (!val->IsNumber()) {
            return Nan::ThrowError(ERROR_INVALID_ARGUMENTS);
          }
          params.push_back(val->Int32Value());
        }
      }

      WriteImageAsyncWorker worker(filename, img, params);
      worker.Execute();

      if (worker.HasError()) {
        return Nan::ThrowError(worker.Error());
      }
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
          SetErrorMessage("Error loading file");
        }
      }

      Local<Value> GetResult() {
        Nan::HandleScope scope;

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

    NAN_METHOD(ImageReadMulti) {
#if CV_MAJOR_VERSION >= 3
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(1, 3);
      Nan::EscapableHandleScope scope;

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

    NAN_METHOD(ImageReadMultiSync) {
#if CV_MAJOR_VERSION >= 3
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(1, 2);
      Nan::EscapableHandleScope scope;
      ASSERT_STRING_FROM_ARGS(path, 0);
      DEFAULT_INT_FROM_ARGS(mode, 1, cv::IMREAD_ANYCOLOR);

      ReadImageMultiAsyncWorker worker(path);
      worker.SetImreadMode(static_cast<cv::ImreadModes>(mode));
      worker.Execute();

      if (worker.HasError()) {
        return Nan::ThrowError(worker.Error());
      }

      info.GetReturnValue().Set(worker.GetResult());
#else
      Nan::ThrowError("only supported in opencv 3.x")
#endif
    }

    NAN_METHOD(ImageEncode) {
      NotImplemented
    }

    NAN_METHOD(ImageEncodeSync) {
      NotImplemented
    }

    extern "C" void init(Local<Object> target) {
      Nan::HandleScope scope;

      // imread modes
      DEFINE_CONST_ENUM(IMREAD_UNCHANGED);
      DEFINE_CONST_ENUM(IMREAD_GRAYSCALE);
      DEFINE_CONST_ENUM(IMREAD_COLOR);
      DEFINE_CONST_ENUM(IMREAD_ANYDEPTH);
      DEFINE_CONST_ENUM(IMREAD_ANYCOLOR);
      DEFINE_CONST_ENUM(IMREAD_LOAD_GDAL);
      DEFINE_CONST_ENUM(IMREAD_REDUCED_GRAYSCALE_2);
      DEFINE_CONST_ENUM(IMREAD_REDUCED_COLOR_2);
      DEFINE_CONST_ENUM(IMREAD_REDUCED_GRAYSCALE_4);
      DEFINE_CONST_ENUM(IMREAD_REDUCED_COLOR_4);
      DEFINE_CONST_ENUM(IMREAD_REDUCED_GRAYSCALE_8);
      DEFINE_CONST_ENUM(IMREAD_REDUCED_COLOR_8);
      DEFINE_CONST_ENUM(IMREAD_IGNORE_ORIENTATION);

      // imwrite flags
      DEFINE_CONST_ENUM(IMWRITE_JPEG_QUALITY);
      DEFINE_CONST_ENUM(IMWRITE_JPEG_PROGRESSIVE);
      DEFINE_CONST_ENUM(IMWRITE_JPEG_OPTIMIZE);
      DEFINE_CONST_ENUM(IMWRITE_JPEG_RST_INTERVAL);
      DEFINE_CONST_ENUM(IMWRITE_JPEG_LUMA_QUALITY);
      DEFINE_CONST_ENUM(IMWRITE_JPEG_CHROMA_QUALITY);
      DEFINE_CONST_ENUM(IMWRITE_PNG_COMPRESSION);
      DEFINE_CONST_ENUM(IMWRITE_PNG_STRATEGY);
      DEFINE_CONST_ENUM(IMWRITE_PNG_BILEVEL);
      DEFINE_CONST_ENUM(IMWRITE_PXM_BINARY);
      DEFINE_CONST_ENUM(IMWRITE_WEBP_QUALITY);
      DEFINE_CONST_ENUM(IMWRITE_PAM_TUPLETYPE);

      // imwrite pam flags
      DEFINE_CONST_ENUM(IMWRITE_PAM_FORMAT_NULL);
      DEFINE_CONST_ENUM(IMWRITE_PAM_FORMAT_BLACKANDWHITE);
      DEFINE_CONST_ENUM(IMWRITE_PAM_FORMAT_GRAYSCALE);
      DEFINE_CONST_ENUM(IMWRITE_PAM_FORMAT_GRAYSCALE_ALPHA);
      DEFINE_CONST_ENUM(IMWRITE_PAM_FORMAT_RGB);
      DEFINE_CONST_ENUM(IMWRITE_PAM_FORMAT_RGB_ALPHA);

      // imwrite png flags
      DEFINE_CONST_ENUM(IMWRITE_PNG_STRATEGY_DEFAULT);
      DEFINE_CONST_ENUM(IMWRITE_PNG_STRATEGY_FILTERED);
      DEFINE_CONST_ENUM(IMWRITE_PNG_STRATEGY_HUFFMAN_ONLY);
      DEFINE_CONST_ENUM(IMWRITE_PNG_STRATEGY_RLE);
      DEFINE_CONST_ENUM(IMWRITE_PNG_STRATEGY_FIXED);

      Nan::SetMethod(target, "imread", ImageRead);
      Nan::SetMethod(target, "imreadSync", ImageReadSync);
      Nan::SetMethod(target, "imdecode", ImageDecode);
      Nan::SetMethod(target, "imdecodeSync", ImageDecodeSync);
      Nan::SetMethod(target, "imencode", ImageEncode);
      Nan::SetMethod(target, "imencodeSync", ImageEncodeSync);
      Nan::SetMethod(target, "imreadmulti", ImageReadMulti);
      Nan::SetMethod(target, "imreadmultiSync", ImageReadMultiSync);
      Nan::SetMethod(target, "imwrite", ImageWrite);
      Nan::SetMethod(target, "imwriteSync", ImageWriteSync);
    }

    NODE_MODULE(imgcodec, init);

  }

}

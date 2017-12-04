#include "VideoCapture.h"

Nan::Persistent<FunctionTemplate> VideoCapture::constructor;

void VideoCapture::Init(Local<Object> target) {
  Nan::HandleScope scope;

  // Class/contructor
  Local<FunctionTemplate> ctor = Nan::New<FunctionTemplate>(New);
  constructor.Reset(ctor);
  ctor->SetClassName(Nan::New("VideoCapture").ToLocalChecked());

  Nan::SetPrototypeMethod(ctor, "get", Get);
  Nan::SetPrototypeMethod(ctor, "grab", Grab);
  Nan::SetPrototypeMethod(ctor, "isOpened", IsOpened);
  Nan::SetPrototypeMethod(ctor, "read", Read);
  Nan::SetPrototypeMethod(ctor, "release", Release);
  Nan::SetPrototypeMethod(ctor, "retrieve", Retrieve);
  Nan::SetPrototypeMethod(ctor, "set", Set);

  // Instance
  Local<ObjectTemplate> inst = ctor->InstanceTemplate();
  inst->SetInternalFieldCount(1);

  Nan::Set(target, Nan::New("VideoCapture").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(VideoCapture::New) {
  Nan::HandleScope scope;

  if (info.IsConstructCall() == 0) {
    Nan::ThrowTypeError("Cannot instantiate without new");
  }

  FUNCTION_REQUIRE_ARGUMENTS_RANGE(1, 2);

  VideoCapture *vc = new VideoCapture();
  if (info.Length() == 1 && info[0]->IsNumber()) {
    vc->cap.open(info[0]->Int32Value());
  } else if (info.Length() == 1 && info[0]->IsString()) {
    vc->cap.open(*Nan::Utf8String(info[0]->ToString()));
  } else if (info.Length() == 2 && info[0]->IsString() && info[1]->IsNumber()) {
    vc->cap.open(*Nan::Utf8String(info[0]->ToString()), info[1]->Int32Value());
  } else {
    delete vc;
    return Nan::ThrowError(ERROR_INVALID_ARGUMENTS);
  }

  vc->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(VideoCapture::Get) {
  FUNCTION_REQUIRE_ARGUMENTS(1);
  SETUP_FUNCTION(VideoCapture);
  ASSERT_INT_FROM_ARGS(propId, 0);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Number>(self->cap.get(propId))));
}

NAN_METHOD(VideoCapture::Grab) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(VideoCapture);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Boolean>(self->cap.grab())));
}

NAN_METHOD(VideoCapture::IsOpened) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(VideoCapture);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Boolean>(self->cap.isOpened())));
}

NAN_METHOD(VideoCapture::Read) {
  FUNCTION_REQUIRE_ARGUMENTS_RANGE(0, 1);
  SETUP_FUNCTION(VideoCapture);

  if (info.Length() == 1) {
    cv::_OutputArray out = ReadOutputArray(info[0]);

    TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Boolean>(self->cap.read(out))));
  } else {
    Local<Object> m = Matrix::NewInstance();
    TRY_CATCH_THROW_OPENCV(
      if (self->cap.read(UNWRAP_OBJECT(Matrix, m)->mat)) {
        info.GetReturnValue().Set(m);
      } else {
        info.GetReturnValue().SetNull();
      }
    );
  }
}

NAN_METHOD(VideoCapture::Release) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(VideoCapture);
  TRY_CATCH_THROW_OPENCV(self->cap.release());
}

NAN_METHOD(VideoCapture::Retrieve) {
  FUNCTION_REQUIRE_ARGUMENTS_RANGE(0, 2);
  SETUP_FUNCTION(VideoCapture);

  cv::_OutputArray mat;
  if (info.Length() == 0 || info[0]->IsNumber()) {
    Local<Object> m = Matrix::NewInstance();
    mat = UNWRAP_OBJECT(Matrix, m)->mat;

    bool result;
    TRY_CATCH_THROW_OPENCV(
      if (info.Length() > 0) {
        ASSERT_INT_FROM_ARGS(flag, 0);
        result = self->cap.retrieve(mat, flag);
      } else {
        result = self->cap.retrieve(mat);
      }
    );

    if (result) {
      info.GetReturnValue().Set(m);
    } else {
      info.GetReturnValue().SetNull();
    }
  } else {
    cv::_OutputArray out = ReadOutputArray(info[0]);

    bool result;
    TRY_CATCH_THROW_OPENCV(
      if (info.Length() > 1) {
        ASSERT_INT_FROM_ARGS(flag, 1);
        result = self->cap.retrieve(mat, flag);
      } else {
        result = self->cap.retrieve(mat);
      }
    );

    info.GetReturnValue().Set(Nan::New<Boolean>(result));
  }
}

NAN_METHOD(VideoCapture::Set) {
  FUNCTION_REQUIRE_ARGUMENTS(2);
  SETUP_FUNCTION(VideoCapture);
  ASSERT_INT_FROM_ARGS(propId, 0);
  ASSERT_DOUBLE_FROM_ARGS(value, 1);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Number>(self->cap.set(propId, value))));
}

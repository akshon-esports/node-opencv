#include "Size.h"

Nan::Persistent<FunctionTemplate> Size::constructor;

void Size::Init(Local<Object> const target) {
  Nan::HandleScope scope;

  // Constructor
  Local<FunctionTemplate> ctor = Nan::New<FunctionTemplate>(New);
  constructor.Reset(ctor);

  ctor->SetClassName(Nan::New("Size").ToLocalChecked());

  // Instance
  Local<ObjectTemplate> inst = ctor->InstanceTemplate();
  inst->SetInternalFieldCount(1);
  Nan::SetAccessor(inst, Nan::New<String>(OBJECT_KEY_WIDTH).ToLocalChecked(), Getter, Setter);
  Nan::SetAccessor(inst, Nan::New<String>(OBJECT_KEY_HEIGHT).ToLocalChecked(), Getter, Setter);

  // Prototype Methods
  Nan::SetPrototypeMethod(ctor, "area", Area);

  Nan::SetPrototypeMethod(ctor, "toString", ToString);


  Nan::Set(target, Nan::New("Size").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(Size::New) {
  Nan::HandleScope scope;

  if (!info.IsConstructCall()) {
    return Nan::ThrowTypeError(ERROR_MUST_USE_NEW);
  }

  SETUP_ARGC_AND_ARGV;

  cv::Size size;
  try {
    size = RawSize(argc, argv);
  } catch (const char* msg) {
    delete[] argv;
    return Nan::ThrowTypeError(msg);
  }
  delete[] argv;

  Size* sz = new Size();
  sz->size = size;
  sz->Wrap(info.This());

  info.GetReturnValue().Set(info.This());
}

Local<Object> Size::NewInstance(cv::Size const &size) {
  Nan::EscapableHandleScope scope;

  UNWRAP_NEW_INSTANCE(Size, sz);
  sz->size = size;

  return scope.Escape(inst);
}

Local<Object> Size::NewInstance(int const &width, int const &height) {
  Nan::EscapableHandleScope scope;

  UNWRAP_NEW_INSTANCE(Size, sz);
  sz->size.width = width;
  sz->size.height = height;

  return scope.Escape(inst);
}

cv::Size Size::RawSize(int const &argc, Local<Value>* const argv) {
  Nan::HandleScope scope;

  if (argc == 0) {
    return cv::Size();
  }

  if (argc == 1) {
    if (HasInstance(argv[0])) {
      Size *sz = UNWRAP_OBJECT(Size, argv[0]->ToObject());
      return sz->size;
    }

    if (argv[0]->IsArray()) {
      Local<Array> sizeLike = Local<Array>::Cast(argv[0]);

      if (sizeLike->Length() != 2) {
        throw "SizeLike array must have 2 elements";
      }

      Local<Value> objValue_w = Nan::Get(sizeLike, 0).ToLocalChecked();
      Local<Value> objValue_h = Nan::Get(sizeLike, 1).ToLocalChecked();

      if (!objValue_w->IsNumber() || !objValue_h->IsNumber()) {
        throw "SizeLike array elements must be numbers";
      }

      return cv::Size(objValue_w->Int32Value(), objValue_h->Int32Value());
    }

    if (argv[0]->IsObject()) {
      Local<Object> sizeLike = argv[0]->ToObject();

      Local<String> objKey_w = Nan::New<String>(OBJECT_KEY_WIDTH).ToLocalChecked();
      Local<String> objKey_h = Nan::New<String>(OBJECT_KEY_HEIGHT).ToLocalChecked();

      if (!Nan::HasOwnProperty(sizeLike, objKey_w).ToChecked() || !Nan::HasOwnProperty(sizeLike, objKey_h).ToChecked()) {
        throw "SizeLike object must have properties \"width\" and \"height\"";
      }

      Local<Value> objValue_w = Nan::Get(sizeLike, objKey_w).ToLocalChecked();
      Local<Value> objValue_h = Nan::Get(sizeLike, objKey_h).ToLocalChecked();

      if (!objValue_w->IsNumber() || !objValue_h->IsNumber()) {
        throw "SizeLike object properties \"width\" and \"height\" must be numbers";
      }

      return cv::Size(objValue_w->Int32Value(), objValue_h->Int32Value());
    }

    throw "Argument 1 must be a Size or a SizeLike value";
  }

  if (argc == 2) {
    if (!argv[0]->IsNumber() || !argv[1]->IsNumber()) {
      throw "Arguments 1 and 2 must be numbers";
    }

    return cv::Size(argv[0]->Int32Value(), argv[1]->Int32Value());
  }

  throw cv::format("Expected 0-2 arguments, but got %d", argc).c_str();
}

NAN_GETTER(Size::Getter) {
  std::string name = *Nan::Utf8String(property);
  Size* self = UNWRAP_OBJECT(Size, info.Holder());
  if (name == OBJECT_KEY_WIDTH) {
    info.GetReturnValue().Set(Nan::New<Number>(self->size.width));
  } else if (name == OBJECT_KEY_HEIGHT) {
    info.GetReturnValue().Set(Nan::New<Number>(self->size.height));
  }
}

NAN_SETTER(Size::Setter) {
  if (!value->IsNumber()) {
    return Nan::ThrowTypeError("value must be a number");
  }

  Size* self = UNWRAP_OBJECT(Size, info.Holder());
  std::string name = *Nan::Utf8String(property);
  if (name == OBJECT_KEY_WIDTH) {
    self->size.width = value->Int32Value();
  } else if (name == OBJECT_KEY_HEIGHT) {
    self->size.height = value->Int32Value();
  }
}

NAN_METHOD(Size::Area) {
  SETUP_FUNCTION(Size)

  info.GetReturnValue().Set(Nan::New<Number>(self->size.area()));
}

NAN_METHOD(Size::ToString) {
  SETUP_FUNCTION(Size)

  std::ostringstream stream;
  stream << self->size;

  info.GetReturnValue().Set(Nan::New<String>(stream.str()).ToLocalChecked());
}

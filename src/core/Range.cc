#include "Range.h"

Nan::Persistent<FunctionTemplate> Range::constructor;

void Range::Init(Local<Object> target) {
  Nan::HandleScope scope;

  // Constructor
  Local<FunctionTemplate> ctor = Nan::New<FunctionTemplate>(New);
  constructor.Reset(ctor);

  ctor->SetClassName(Nan::New("Range").ToLocalChecked());

  // Instance
  Local<ObjectTemplate> inst = ctor->InstanceTemplate();
  inst->SetInternalFieldCount(1);
  Nan::SetAccessor(inst, Nan::New<String>(OBJECT_KEY_X).ToLocalChecked(), Getter, Setter);
  Nan::SetAccessor(inst, Nan::New<String>(OBJECT_KEY_Y).ToLocalChecked(), Getter, Setter);

  // Prototype Methods
  Nan::SetPrototypeMethod(ctor, "size", Size);
  Nan::SetPrototypeMethod(ctor, "isEmpty", IsEmpty);

  Nan::SetPrototypeMethod(ctor, "isAll", IsAll);

  Nan::SetMethod(ctor, "all", All);

  Nan::Set(target, Nan::New("Range").ToLocalChecked(), ctor->GetFunction());
}

NAN_METHOD(Range::New) {
  Nan::HandleScope scope;

  if (!info.IsConstructCall()) {
    return Nan::ThrowTypeError(ERROR_MUST_USE_NEW);
  }

  SETUP_ARGC_AND_ARGV;

  cv::Range range;
  try {
    range = RawRange(argc, argv);
  } catch (const char* msg) {
    delete[] argv;
    return Nan::ThrowTypeError(msg);
  }
  delete[] argv;

  Range* pt = new Range();
  pt->range = range;
  pt->Wrap(info.This());

  info.GetReturnValue().Set(info.This());
}

Local<Object> Range::NewInstance(cv::Range const &range) {
  Nan::EscapableHandleScope scope;

  UNWRAP_NEW_INSTANCE(Range, r);
  r->range = range;

  return scope.Escape(inst);
}

Local<Object> Range::NewInstance(int const &start, int const &end) {
  Nan::EscapableHandleScope scope;

  UNWRAP_NEW_INSTANCE(Range, r);
  r->range.start = start;
  r->range.end = end;

  return scope.Escape(inst);
}

cv::Range Range::RawRange(int const &argc, Local<Value>* const argv) {
  Nan::HandleScope scope;

  if (argc == 0) {
    return cv::Range();
  }

  if (argc == 1) {
    if (HasInstance(argv[0])) {
      Range *r = UNWRAP_OBJECT(Range, argv[0]->ToObject());
      return r->range;
    }

    if (argv[0]->IsArray()) {
      Local<Array> rangeLike = Local<Array>::Cast(argv[0]->ToObject());

      if (rangeLike->Length() != 2) {
        throw "RangeLike array must have 2 elements";
      }

      Local<Value> objValue_x = Nan::Get(rangeLike, 0).ToLocalChecked();
      Local<Value> objValue_y = Nan::Get(rangeLike, 1).ToLocalChecked();

      if (!objValue_x->IsNumber() || !objValue_y->IsNumber()) {
        throw "RangeLike array elements must be numbers";
      }

      return cv::Range(objValue_x->Int32Value(), objValue_y->Int32Value());
    }

    if (argv[0]->IsObject()) {
      Local<Object> rangeLike = argv[0]->ToObject();

      Local<String> objKey_s = Nan::New<String>(OBJECT_KEY_START).ToLocalChecked();
      Local<String> objKey_e = Nan::New<String>(OBJECT_KEY_END).ToLocalChecked();

      if (!Nan::HasOwnProperty(rangeLike, objKey_s).ToChecked() || !Nan::HasOwnProperty(rangeLike, objKey_e).ToChecked()) {
        throw "RangeLike object must have properties \"start\" and \"end\"";
      }

      Local<Value> objValue_s = Nan::Get(rangeLike, objKey_s).ToLocalChecked();
      Local<Value> objValue_e = Nan::Get(rangeLike, objKey_e).ToLocalChecked();

      if (!objValue_s->IsNumber() || !objValue_e->IsNumber()) {
        throw "RangeLike object properties must be numbers";
      }

      return cv::Range(objValue_s->Int32Value(), objValue_e->Int32Value());
    }

    throw ERROR_INVALID_ARGUMENTS;
  }

  if (argc == 2) {
    if (!argv[0]->IsNumber() || !argv[1]->IsNumber()) {
      throw ERROR_INVALID_ARGUMENTS;
    }

    return cv::Range(argv[0]->Int32Value(), argv[1]->Int32Value());
  }

  throw cv::format("Expected 0-2 arguments, but got %d", argc).c_str();
}

NAN_GETTER(Range::Getter) {
  SETUP_FUNCTION(Range);

  std::string name = *Nan::Utf8String(property);
  if (name == OBJECT_KEY_START) {
    info.GetReturnValue().Set(Nan::New<Number>(self->range.start));
  } else if (name == OBJECT_KEY_END) {
    info.GetReturnValue().Set(Nan::New<Number>(self->range.end));
  }
}

NAN_SETTER(Range::Setter) {
  SETUP_FUNCTION(Range);

  if (!value->IsNumber()) {
    return Nan::ThrowTypeError("value must be a number");
  }

  std::string name = *Nan::Utf8String(property);
  if (name == OBJECT_KEY_START) {
    self->range.start = value->Int32Value();
  } else if (name == OBJECT_KEY_END) {
    self->range.end = value->Int32Value();
  }
}

NAN_METHOD(Range::IsEmpty) {
  SETUP_FUNCTION(Range);

  info.GetReturnValue().Set(Nan::New<Boolean>(self->range.empty()));
}

NAN_METHOD(Range::Size) {
  SETUP_FUNCTION(Range);

  info.GetReturnValue().Set(Nan::New<Number>(self->range.size()));
}

NAN_METHOD(Range::All) {
  Nan::HandleScope scope;

  UNWRAP_NEW_INSTANCE(Range, r);
  r->range = cv::Range::all();

  info.GetReturnValue().Set(inst);
}

NAN_METHOD(Range::IsAll) {
  SETUP_FUNCTION(Range);

  info.GetReturnValue().Set(Nan::New<Boolean>(self->range == cv::Range::all()));
}

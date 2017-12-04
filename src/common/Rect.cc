#include "Rect.h"

Nan::Persistent<FunctionTemplate> Rect::constructor;

void Rect::Init(Local<Object> target) {
  Nan::HandleScope scope;

  // Constructor
  Local<FunctionTemplate> ctor = Nan::New<FunctionTemplate>(New);
  constructor.Reset(ctor);
  
  ctor->SetClassName(Nan::New("Rect").ToLocalChecked());

  // Instance
  Local<ObjectTemplate> inst = ctor->InstanceTemplate();
  inst->SetInternalFieldCount(1);
  Nan::SetAccessor(inst, Nan::New<String>(OBJECT_KEY_X).ToLocalChecked(), Getter, Setter);
  Nan::SetAccessor(inst, Nan::New<String>(OBJECT_KEY_Y).ToLocalChecked(), Getter, Setter);
  Nan::SetAccessor(inst, Nan::New<String>(OBJECT_KEY_WIDTH).ToLocalChecked(), Getter, Setter);
  Nan::SetAccessor(inst, Nan::New<String>(OBJECT_KEY_HEIGHT).ToLocalChecked(), Getter, Setter);

  // Prototype Methods
  Nan::SetPrototypeMethod(ctor, "tl", TopLeft);
  Nan::SetPrototypeMethod(ctor, "br", BottomRight);

  Nan::SetPrototypeMethod(ctor, "size", Size);
  Nan::SetPrototypeMethod(ctor, "area", Area);

  Nan::SetPrototypeMethod(ctor, "contains", Contains);

  Nan::SetPrototypeMethod(ctor, "toString", ToString);


  Nan::Set(target, Nan::New("Rect").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(Rect::New) {
  Nan::HandleScope scope;

  if (!info.IsConstructCall()) {
    return Nan::ThrowTypeError(ERROR_MUST_USE_NEW);
  }

  SETUP_ARGC_AND_ARGV;

  cv::Rect rect;
  try {
    rect = RawRect(argc, argv);
  } catch (char const* msg) {
    delete[] argv;
    return Nan::ThrowTypeError(msg);
  }
  delete[] argv;

  Rect *r = new Rect();
  r->rect = rect;
  r->Wrap(info.This());

  info.GetReturnValue().Set(info.This());
}

Local<Object> Rect::NewInstance(cv::Rect const &rect) {
  Nan::EscapableHandleScope scope;

  UNWRAP_NEW_INSTANCE(Rect, r);
  r->rect = rect;

  return scope.Escape(inst);
}

Local<Object> Rect::NewInstance(cv::Point const &point, cv::Size const &size) {
  Nan::EscapableHandleScope scope;

  UNWRAP_NEW_INSTANCE(Rect, r);
  r->rect = cv::Rect(point, size);

  return scope.Escape(inst);
}

Local<Object> Rect::NewInstance(cv::Point const &point1, cv::Point const &point2) {
  Nan::EscapableHandleScope scope;

  UNWRAP_NEW_INSTANCE(Rect, r);
  r->rect = cv::Rect(point1, point2);

  return scope.Escape(inst);
}

Local<Object> Rect::NewInstance(int const &x, int const &y, int const &width, int const &height) {
  Nan::EscapableHandleScope scope;

  UNWRAP_NEW_INSTANCE(Rect, r);
  r->rect = cv::Rect(x, y, width, height);

  return scope.Escape(inst);
}

cv::Rect Rect::RawRect(int const &argc, Local<Value>* const argv) {
  Nan::HandleScope scope;

  if (argc == 0) {
    return cv::Rect();
  }

  if (argc == 1) {
    if (HasInstance(argv[0])) {
      Rect* r = UNWRAP_OBJECT(Rect, argv[0]->ToObject());
      return r->rect;
    }

    if (argv[0]->IsArray()) {
      Local<Array> rectLike = Local<Array>::Cast(argv[0]->ToObject());

      if (!rectLike->Length()) {
        throw "RectLike array must have 4 elements";
      }

      Local<Value> objValue_x = Nan::Get(rectLike, 0).ToLocalChecked();
      Local<Value> objValue_y = Nan::Get(rectLike, 1).ToLocalChecked();
      Local<Value> objValue_w = Nan::Get(rectLike, 2).ToLocalChecked();
      Local<Value> objValue_h = Nan::Get(rectLike, 3).ToLocalChecked();

      if (!objValue_x->IsNumber() || !objValue_y->IsNumber() || !objValue_w->IsNumber() || !objValue_h->IsNumber()) {
        throw "RectLike array elements must be numbers";
      }

      return cv::Rect(objValue_x->Int32Value(), objValue_y->Int32Value(), objValue_w->Int32Value(), objValue_h->Int32Value());
    }

    if (argv[0]->IsObject()) {
      Local<Object> rectLike = argv[0]->ToObject();

      Local<String> objKey_x = Nan::New<String>(OBJECT_KEY_X).ToLocalChecked();
      Local<String> objKey_y = Nan::New<String>(OBJECT_KEY_Y).ToLocalChecked();
      Local<String> objKey_w = Nan::New<String>(OBJECT_KEY_WIDTH).ToLocalChecked();
      Local<String> objKey_h = Nan::New<String>(OBJECT_KEY_HEIGHT).ToLocalChecked();

      if (!Nan::HasOwnProperty(rectLike, objKey_x).FromJust() || !Nan::HasOwnProperty(rectLike, objKey_y).FromJust() || !Nan::HasOwnProperty(rectLike, objKey_w).FromJust() || !Nan::HasOwnProperty(rectLike, objKey_h).FromJust()) {
        throw "RectLike object must have properties \"x\", \"y\", \"width\" and \"height\"";
      }

      Local<Value> objValue_x = Nan::Get(rectLike, objKey_x).ToLocalChecked();
      Local<Value> objValue_y = Nan::Get(rectLike, objKey_y).ToLocalChecked();
      Local<Value> objValue_w = Nan::Get(rectLike, objKey_w).ToLocalChecked();
      Local<Value> objValue_h = Nan::Get(rectLike, objKey_h).ToLocalChecked();

      if (!objValue_x->IsNumber() || !objValue_y->IsNumber() || !objValue_w->IsNumber() || !objValue_h->IsNumber()) {
        throw "RectLike object properties must be numbers";
      }

      return cv::Rect(objValue_x->Int32Value(), objValue_y->Int32Value(), objValue_w->Int32Value(), objValue_h->Int32Value());
    }

    throw ERROR_INVALID_ARGUMENTS;
  }

  if (argc == 2) {
    if (argv[0]->IsObject() && argv[1]->IsObject()) {
      try {
        cv::Point topLeft = Point::RawPoint(1, &argv[0]);

        try {
          cv::Point bottomRight = Point::RawPoint(1, &argv[1]);

          return cv::Rect(topLeft, bottomRight);
        } catch (char const*) {
          try {
            cv::Size size = Size::RawSize(1, &argv[1]);

            return cv::Rect(topLeft, size);
          } catch (char const*) {}
        }

      } catch (char const*) {}
    }

    throw ERROR_INVALID_ARGUMENTS;
  }

  if (argc == 4) {
    if (!argv[0]->IsNumber() || !argv[1]->IsNumber() || !argv[2]->IsNumber() || !argv[3]->IsNumber()) {
      throw ERROR_INVALID_ARGUMENTS;
    }

    return cv::Rect(argv[0]->Int32Value(), argv[1]->Int32Value(), argv[2]->Int32Value(), argv[3]->Int32Value());
  }

  throw cv::format("Expected 0, 1, 2 or 4 arguments, but got %d", argc).c_str();
}

NAN_GETTER(Rect::Getter) {
  SETUP_FUNCTION(Rect)

  std::string name = *Nan::Utf8String(property);
  if (name == OBJECT_KEY_X) {
    info.GetReturnValue().Set(Nan::New<Number>(self->rect.x));
  } else if (name == OBJECT_KEY_Y) {
    info.GetReturnValue().Set(Nan::New<Number>(self->rect.y));
  } else if (name == OBJECT_KEY_WIDTH) {
    info.GetReturnValue().Set(Nan::New<Number>(self->rect.width));
  } else if (name == OBJECT_KEY_HEIGHT) {
    info.GetReturnValue().Set(Nan::New<Number>(self->rect.height));
  }
}

NAN_SETTER(Rect::Setter) {
  SETUP_FUNCTION(Rect)

  if (!value->IsNumber()) {
    return Nan::ThrowTypeError("Value must be a number");
  }

  std::string name = *Nan::Utf8String(property);
  if (name == OBJECT_KEY_X) {
    self->rect.x = value->Int32Value();
  } else if (name == OBJECT_KEY_Y) {
    self->rect.y = value->Int32Value();
  } else if (name == OBJECT_KEY_WIDTH) {
    self->rect.width = value->Int32Value();
  } else if (name == OBJECT_KEY_HEIGHT) {
    self->rect.height = value->Int32Value();
  }
}

NAN_METHOD(Rect::TopLeft) {
  SETUP_FUNCTION(Rect);

  info.GetReturnValue().Set(Point::NewInstance(self->rect.x, self->rect.y));
}

NAN_METHOD(Rect::BottomRight) {
  SETUP_FUNCTION(Rect);

  info.GetReturnValue().Set(Point::NewInstance(self->rect.x + self->rect.width, self->rect.y + self->rect.height));
}

NAN_METHOD(Rect::Size) {
  SETUP_FUNCTION(Rect);

  info.GetReturnValue().Set(Size::NewInstance(self->rect.width, self->rect.height));
}

NAN_METHOD(Rect::Area) {
  SETUP_FUNCTION(Rect);

  info.GetReturnValue().Set(Nan::New<Number>(self->rect.area()));
}

NAN_METHOD(Rect::Contains) {
  FUNCTION_REQUIRE_ARGUMENTS(1);
  SETUP_FUNCTION(Rect);
  ASSERT_POINT_FROM_ARGS(point, 0);

  info.GetReturnValue().Set(Nan::New<Boolean>(self->rect.contains(point)));
}

NAN_METHOD(Rect::ToString) {
  SETUP_FUNCTION(Rect);

  std::ostringstream stream;
  stream << self->rect;

  info.GetReturnValue().Set(Nan::New<String>(stream.str()).ToLocalChecked());
}

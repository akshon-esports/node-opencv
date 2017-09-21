#include "Point.h"

Nan::Persistent<FunctionTemplate> Point::constructor;

void Point::Init(Local<Object> target) {
  Nan::HandleScope scope;

  // Constructor
  Local<FunctionTemplate> ctor = Nan::New<FunctionTemplate>(New);
  constructor.Reset(ctor);

  ctor->SetClassName(Nan::New("Point").ToLocalChecked());

  // Instance
  Local<ObjectTemplate> inst = ctor->InstanceTemplate();
  inst->SetInternalFieldCount(1);
  Nan::SetAccessor(inst, Nan::New<String>(OBJECT_KEY_X).ToLocalChecked(), Getter, Setter);
  Nan::SetAccessor(inst, Nan::New<String>(OBJECT_KEY_Y).ToLocalChecked(), Getter, Setter);

  // Prototype Methods
  Nan::SetPrototypeMethod(ctor, "dot", Dot);


  Nan::Set(target, Nan::New("Point").ToLocalChecked(), ctor->GetFunction());
}

NAN_METHOD(Point::New) {
  if (!info.IsConstructCall()) {
    return Nan::ThrowTypeError(ERROR_MUST_USE_NEW);
  }

  SETUP_ARGC_AND_ARGV;

  cv::Point point;
  try {
    point = RawPoint(argc, argv);
  } catch (const char* msg) {
    delete[] argv;
    return Nan::ThrowTypeError(msg);
  }
  delete[] argv;

  Point* pt = new Point();
  pt->point = point;
  pt->Wrap(info.This());

  info.GetReturnValue().Set(info.This());
}

Local<Object> Point::NewInstance(cv::Point const &point) {
  Nan::EscapableHandleScope scope;

  Local<Object> obj = NewInstance();
  Point *pt = UNWRAP_OBJECT(Point, obj);
  pt->point = point;

  return scope.Escape(obj);
}

Local<Object> Point::NewInstance(int const &x, int const &y) {
  Nan::EscapableHandleScope scope;

  Local<Object> obj = NewInstance();
  Point *pt = UNWRAP_OBJECT(Point, obj);
  pt->point.x = x;
  pt->point.y = y;

  return scope.Escape(obj);
}

cv::Point Point::RawPoint(int const &argc, Local<Value>* const argv) {
  Nan::HandleScope scope;

  if (argc == 0) {
    return cv::Point();
  }

  if (argc == 1) {
    if (HasInstance(argv[0])) {
      Point *pt = UNWRAP_OBJECT(Point, argv[0]->ToObject());
      return pt->point;
    }

    if (argv[0]->IsArray()) {
      Local<Array> pointLike = Local<Array>::Cast(argv[0]);

      if (pointLike->Length() != 2) {
        throw "PointLike array must have 2 elements";
      }

      Local<Value> objValue_x = Nan::Get(pointLike, 0).ToLocalChecked();
      Local<Value> objValue_y = Nan::Get(pointLike, 1).ToLocalChecked();

      if (!objValue_x->IsNumber() || !objValue_y->IsNumber()) {
        throw "PointLike array elements must be numbers";
      }

      return cv::Point(objValue_x->Int32Value(), objValue_y->Int32Value());
    }

    if (argv[0]->IsObject()) {
      Local<Object> pointLike = argv[0]->ToObject();

      Local<String> objKey_x = Nan::New<String>(OBJECT_KEY_X).ToLocalChecked();
      Local<String> objKey_y = Nan::New<String>(OBJECT_KEY_Y).ToLocalChecked();

      if (!Nan::HasRealNamedProperty(pointLike, objKey_x).ToChecked() || !Nan::HasRealNamedProperty(pointLike, objKey_y).ToChecked()) {
        throw "PointLike object must have properties \"x\" and \"y\"";
      }

      Local<Value> objValue_x = Nan::Get(pointLike, objKey_x).ToLocalChecked();
      Local<Value> objValue_y = Nan::Get(pointLike, objKey_y).ToLocalChecked();

      if (!objValue_x->IsNumber() || !objValue_y->IsNumber()) {
        throw "PointLike object properties must be numbers";
      }

      return cv::Point(objValue_x->Int32Value(), objValue_y->Int32Value());
    }

    throw ERROR_INVALID_ARGUMENTS;
  }

  if (argc == 2) {
    if (!argv[0]->IsNumber() || !argv[1]->IsNumber()) {
      throw ERROR_INVALID_ARGUMENTS;
    }

    return cv::Point(argv[0]->Int32Value(), argv[1]->Int32Value());
  }

  throw cv::format("Expected 0-2 arguments, but got %d", argc).c_str();
}

NAN_GETTER(Point::Getter) {
  SETUP_FUNCTION(Point);

  std::string name = *Nan::Utf8String(property);
  if (name == OBJECT_KEY_X) {
    info.GetReturnValue().Set(Nan::New<Number>(self->point.x));
  } else if (name == OBJECT_KEY_Y) {
    info.GetReturnValue().Set(Nan::New<Number>(self->point.y));
  }
}

NAN_SETTER(Point::Setter) {
  SETUP_FUNCTION(Point);

  if (!value->IsNumber()) {
    return Nan::ThrowTypeError("value must be a number");
  }

  std::string name = *Nan::Utf8String(property);
  if (name == OBJECT_KEY_X) {
    self->point.x = value->Int32Value();
  } else if (name == OBJECT_KEY_Y) {
    self->point.y = value->Int32Value();
  }
}

NAN_METHOD(Point::Dot) {
  FUNCTION_REQUIRE_ARGUMENTS(1);
  SETUP_FUNCTION(Point);
  ASSERT_POINT_FROM_ARGS(point, 0);

  info.GetReturnValue().Set(Nan::New<Number>(self->point.dot(point)));
}

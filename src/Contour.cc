#include "OpenCV.h"
#include "Contour.h"
#include "Point.h"
#include <nan.h>

#include <iostream>
#include "Rect.h"

Nan::Persistent<FunctionTemplate> Contour::constructor;

void Contour::Init(Local<Object> target) {
  Nan::HandleScope scope;

  // Class/contructor
  Local<FunctionTemplate> ctor = Nan::New<FunctionTemplate>(New);
  constructor.Reset(ctor);
  ctor->SetClassName(Nan::New("Contours").ToLocalChecked());

  // Instance
  Local<ObjectTemplate> inst = ctor->InstanceTemplate();
  inst->SetInternalFieldCount(1);
  Nan::SetIndexedPropertyHandler(inst, IndexGetter, 0, IndexQuery, 0, IndexEnumerator);

  // Prototype
  Nan::SetPrototypeMethod(ctor, "parent", Parent);
  Nan::SetPrototypeMethod(ctor, "children", Children);
  Nan::SetPrototypeMethod(ctor, "next", Next);
  Nan::SetPrototypeMethod(ctor, "previous", Previous);

//  Nan::SetPrototypeMethod(ctor, "moments", Moments);
  Nan::SetPrototypeMethod(ctor, "area", Area);
  Nan::SetPrototypeMethod(ctor, "arcLength", ArcLength);
  Nan::SetPrototypeMethod(ctor, "approxPolyDP", ApproxPolyDP);
  Nan::SetPrototypeMethod(ctor, "convexHull", ConvexHull);
  Nan::SetPrototypeMethod(ctor, "isConvex", IsConvex);
  Nan::SetPrototypeMethod(ctor, "boundingRect", BoundingRect);
//  Nan::SetPrototypeMethod(ctor, "minAreaRect", MinAreaRect);
  Nan::SetPrototypeMethod(ctor, "minEnclosingCircle", MinEnclosingCircle);
//  Nan::SetPrototypeMethod(ctor, "fitEllipse", FitEllipse);
  Nan::SetPrototypeMethod(ctor, "FitLine", FitLine);

  Nan::SetPrototypeMethod(ctor, "convexityDefects", ConvexityDefects);
  Nan::SetPrototypeMethod(ctor, "pointPolygonTest", PointPolygonTest);
  Nan::SetPrototypeMethod(ctor, "matchShapes", MatchShapes);

  target->Set(Nan::New("Contours").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(Contour::New) {
  Nan::HandleScope scope;

  if (info.This()->InternalFieldCount() == 0) {
    Nan::ThrowTypeError("Cannot instantiate without new");
  }

  Contour *contour = new Contour();

  contour->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

Local<Object> Contour::NewInstance(const std::vector<cv::Point> &in) {
  Local<Object> inst = Nan::NewInstance(Nan::GetFunction(Nan::New(constructor)).ToLocalChecked()).ToLocalChecked();

  Contour *contour = UNWRAP_OBJ(Contour, inst);
  contour->contours.push_back(in);
  contour->hierarchy.push_back(cv::Vec4i::all(-1));

  return inst;
}

Local<Object> Contour::NewInstance(const std::vector<std::vector<cv::Point>> &contours, const std::vector<cv::Vec4i> &hierarchy, int index) {
  Local<Object> inst = Nan::NewInstance(Nan::GetFunction(Nan::New(constructor)).ToLocalChecked()).ToLocalChecked();

  Contour *contour = UNWRAP_OBJ(Contour, inst);
  contour->contours = contours;
  contour->hierarchy = hierarchy;
  contour->index = index;

  return inst;
}

bool Contour::HasInstance(Local<Value> object) {
  return Nan::New(constructor)->HasInstance(object);
}

NAN_INDEX_GETTER(Contour::IndexGetter) {
  Contour *self = UNWRAP_OBJ(Contour, info.This());

  if (index < self->contours[self->index].size()) {
    info.GetReturnValue().Set(Point::NewInstance(self->contours[self->index][index]));
  }
}

NAN_INDEX_QUERY(Contour::IndexQuery) {
  info.GetReturnValue().Set(Nan::New<Integer>(ReadOnly));
}

NAN_INDEX_ENUMERATOR(Contour::IndexEnumerator) {
  Contour *self = UNWRAP_OBJ(Contour, info.This());

  v8::Local<v8::Array> arr = Nan::New<v8::Array>();
  for (int i = 0; i < self->contours[self->index].size(); i++) {
    Nan::Set(arr, i, Nan::New(std::to_string(i)).ToLocalChecked());
  }
  info.GetReturnValue().Set(arr);
}

NAN_METHOD(Contour::Parent) {
  Nan::HandleScope scope;

  Contour *self = UNWRAP_OBJ(Contour, info.This());

  int index = self->hierarchy[self->index][3];
  if (index == -1) {
    return info.GetReturnValue().SetNull();
  }

  info.GetReturnValue().Set(NewInstance(self->contours, self->hierarchy, index));
}

NAN_METHOD(Contour::Children) {
  Nan::HandleScope scope;

  Contour *self = UNWRAP_OBJ(Contour, info.This());

  Local<Array> children = Nan::New<Array>();

  int index = self->hierarchy[self->index][2];
  while (index != -1) {
    Nan::Set(children, children->Length(), NewInstance(self->contours, self->hierarchy, index));
    index = self->hierarchy[index][0];
  }

  info.GetReturnValue().Set(children);
}

NAN_METHOD(Contour::Next) {
  Nan::HandleScope scope;

  Contour *self = UNWRAP_OBJ(Contour, info.This());

  int index = self->hierarchy[self->index][0];
  if (index == -1) {
    return info.GetReturnValue().SetNull();
  }

  info.GetReturnValue().Set(NewInstance(self->contours, self->hierarchy, index));
}

NAN_METHOD(Contour::Previous) {
  SETUP_FUNCTION(Contour);

  int index = self->hierarchy[self->index][1];
  if (index == -1) {
    return info.GetReturnValue().SetNull();
  }

  info.GetReturnValue().Set(NewInstance(self->contours, self->hierarchy, index));
}

NAN_METHOD(Contour::Area) {
  SETUP_FUNCTION(Contour);
  DEFAULT_BOOLEAN_FROM_ARGS(oriented, 0, false);

  try {
    info.GetReturnValue().Set(Nan::New<Number>(cv::contourArea(self->contour(), oriented)));
  } catch(cv::Exception e) {
    return Nan::ThrowError(e.what());
  }
}

NAN_METHOD(Contour::ArcLength) {
  SETUP_FUNCTION(Contour);
  ASSERT_BOOLEAN_FROM_ARGS(closed, 0);

  try {
    info.GetReturnValue().Set(Nan::New<Number>(cv::arcLength(self->contour(), closed)));
  } catch(cv::Exception e) {
    return Nan::ThrowError(e.what());
  }
}

NAN_METHOD(Contour::ApproxPolyDP) {
  FUNCTION_MIN_ARGUMENTS(2, "Contour.approxPolyDP()");
  SETUP_FUNCTION(Contour);
  ASSERT_DOUBLE_FROM_ARGS(epsilon, 0);
  ASSERT_BOOLEAN_FROM_ARGS(closed, 1);

  std::vector<cv::Point> approx;
  try {
    cv::approxPolyDP(self->contour(), approx, epsilon, closed);
  } catch(cv::Exception e) {
    return Nan::ThrowError(e.what());
  }

  Local<Array> out = Nan::New<Array>();
  for (const cv::Point point : approx) {
    Nan::Set(out, out->Length(), Point::NewInstance(point));
  }

  info.GetReturnValue().Set(out);
}

NAN_METHOD(Contour::ConvexHull) {
  Nan::HandleScope scope;

  Contour *self = UNWRAP_OBJ(Contour, info.This());

  DEFAULT_BOOLEAN_FROM_ARGS(clockwise, 0, false);

  std::vector<cv::Point> hull;

  try {
    cv::convexHull(self->contour(), hull, clockwise);
  } catch(cv::Exception e) {
    return Nan::ThrowError(e.what());
  }

  Local<Array> out = Nan::New<Array>();
  for (const cv::Point point : hull) {
    Nan::Set(out, out->Length(), Point::NewInstance(point));
  }

  info.GetReturnValue().Set(out);
}

NAN_METHOD(Contour::IsConvex) {
  Nan::HandleScope scope;

  Contour *self = UNWRAP_OBJ(Contour, info.This());

  try {
    info.GetReturnValue().Set(Nan::New<Boolean>(cv::isContourConvex(self->contour())));
  } catch(cv::Exception e) {
    Nan::ThrowError(e.what());
  }
}

NAN_METHOD(Contour::BoundingRect) {
  Nan::HandleScope scope;

  Contour *self = UNWRAP_OBJ(Contour, info.This());

  try {
    info.GetReturnValue().Set(Rect::NewInstance(cv::boundingRect(self->contour())));
  } catch (cv::Exception e) {
    Nan::ThrowError(e.what());
  }
}

//NAN_METHOD(Contour::MinAreaRect) {
//  Nan::HandleScope scope;
//
//  Contour *self = UNWRAP_OBJ(Contour, info.This());
//
//  try {
//    cv::minAreaRect(self->contour());
//  } catch (cv::Exception e) {
//    Nan::ThrowError(e.what());
//  }
//}

NAN_METHOD(Contour::MinEnclosingCircle) {
  Nan::HandleScope scope;

  Contour *self = UNWRAP_OBJ(Contour, info.This());

  cv::Point2f center;
  float radius;

  try {
    cv::minEnclosingCircle(self->contour(), center, radius);
  } catch(cv::Exception e) {
    return Nan::ThrowError(e.what());
  }

  Local<Object> out = Nan::New<Object>();
  Nan::Set(out, Nan::New<String>("center").ToLocalChecked(), Point::NewInstance(center));
  Nan::Set(out, Nan::New<String>("radius").ToLocalChecked(), Nan::New<Number>(radius));

  info.GetReturnValue().Set(out);
}

//NAN_METHOD(Contour::FitEllipse) {
//  Nan::HandleScope scope;
//
//  Contour *self = UNWRAP_OBJ(Contour, info.This());
//
//  try {
//    cv::fitEllipse(self->contour());
//  } catch (cv::Exception e) {
//    Nan::ThrowError(e.what());
//  }
//}

NAN_METHOD(Contour::FitLine) {
  Nan::HandleScope scope;

  if (info.Length() < 4) {
    return Nan::ThrowError("Contour.fitLine requires 4 arguments");
  }

  Contour *self = UNWRAP_OBJ(Contour, info.This());

  if (!info[0]->IsNumber()) {
    return Nan::ThrowTypeError("Argument 1 must be a number");
  }
  int distType = info[0]->Int32Value();

  if (!info[1]->IsNumber()) {
    return Nan::ThrowTypeError("Argument 2 must be a number");
  }
  int param = info[1]->NumberValue();

  if (!info[2]->IsNumber()) {
    return Nan::ThrowTypeError("Argument 3 must be a number");
  }
  int reps = info[2]->NumberValue();

  if (!info[3]->IsNumber()) {
    return Nan::ThrowTypeError("Argument 4 must be a number");
  }
  int aeps = info[3]->NumberValue();

  cv::Vec4f line;
  try {
    cv::fitLine(self->contour(), line, distType, param, reps, aeps);
  } catch (cv::Exception e) {
    return Nan::ThrowError(e.what());
  }

  Local<Array> arr = Nan::New<Array>();
  Nan::Set(arr, 0, Point::NewInstance(line[0], line[1]));
  Nan::Set(arr, 1, Point::NewInstance(line[2], line[3]));

  info.GetReturnValue().Set(arr);
}

NAN_METHOD(Contour::ConvexityDefects) {
  Nan::HandleScope scope;

  if (info.Length() < 1) {
    return Nan::ThrowError("Contour.convexityDefects requires 1 argument");
  }

  Contour *self = UNWRAP_OBJ(Contour, info.This());

  if (!info[0]->IsArray()) {
    return Nan::ThrowTypeError("Argument 1 must be a Array");
  }

  Local<Array> in_arr = Local<Array>::Cast(info[0]);

  std::vector<cv::Point> hull;
  for (unsigned i = 0; i < in_arr->Length(); i++) {
    Local<Value> argv[1] = { Nan::Get(in_arr, i).ToLocalChecked() };
    hull.push_back(Point::RawPoint(1, argv));
  }

  std::vector<std::vector<cv::Vec4i>> defects;
  try {
    cv::convexityDefects(self->contour(), hull, defects);
  } catch(cv::Exception e) {
    return Nan::ThrowError(e.what());
  }

  Local<Array> out_arr = Nan::New<Array>();
  for (const std::vector<cv::Vec4i> defect : defects) {
    Local<Array> innerArr = Nan::New<Array>();
    for (const cv::Vec4i vec : defect) {
      Local<Array> vecArr = Nan::New<Array>();
      for (int i = 0; i < 4; i++) {
        Nan::Set(vecArr, i, Nan::New<Number>(vec[i]));
      }

      Nan::Set(innerArr, innerArr->Length(), vecArr);
    }

    Nan::Set(out_arr, out_arr->Length(), innerArr);
  }

  info.GetReturnValue().Set(out_arr);
}

NAN_METHOD(Contour::PointPolygonTest) {
  Nan::HandleScope scope;

  if (info.Length() < 1) {
    return Nan::ThrowError("Contour.pointPolygonTest requires 2 arguments");
  }

  Contour *self = UNWRAP_OBJ(Contour, info.This());

  if (!info[0]->IsObject()) {
    return Nan::ThrowTypeError("Argument 1 must be a Point");
  }

  cv::Point point;
  try {
    Local<Value> argv[1] = { info[0] };
    point = Point::RawPoint(1, argv);
  } catch(const char *) {
    return Nan::ThrowTypeError("Argument 1 must be a Point");
  }

  if (!info[1]->IsBoolean()) {
    return Nan::ThrowTypeError("Argument 2 must be a boolean");
  }

  double result;
  try {
    result = cv::pointPolygonTest(self->contour(), point, info[1]->BooleanValue());
  } catch(cv::Exception e) {
    return Nan::ThrowError(e.what());
  }

  info.GetReturnValue().Set(Nan::New<Number>(result));
}

NAN_METHOD(Contour::MatchShapes) {
  Nan::HandleScope scope;

  if (info.Length() < 1) {
    return Nan::ThrowError("Contour.matchShapes requires 2 arguments");
  }

  Contour *self = UNWRAP_OBJ(Contour, info.This());

  if (!info[0]->IsObject() || !HasInstance(info[0])) {
    return Nan::ThrowTypeError("Argument 1 must be a Contour");
  }

  Contour *contour = UNWRAP_OBJ(Contour, info[0]->ToObject());

  if (!info[1]->IsNumber()) {
    return Nan::ThrowTypeError("Argument 2 must be a number");
  }

  double result;
  try {
    result = cv::matchShapes(self->contour(), contour->contour(), info[1]->Int32Value(), 0.);
  } catch(cv::Exception e) {
    return Nan::ThrowError(e.what());
  }

  info.GetReturnValue().Set(Nan::New<Number>(result));
}

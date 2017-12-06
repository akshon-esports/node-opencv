#include "Contour.h"

#include <iostream>
#include "../common/Point.h"
#include "../common/Rect.h"

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
  Nan::SetAccessor(inst, Nan::New<String>("length").ToLocalChecked(), LengthGetter);

  // Prototype
  Nan::SetPrototypeMethod(ctor, "parent", Parent);
  Nan::SetPrototypeMethod(ctor, "children", Children);
  Nan::SetPrototypeMethod(ctor, "next", Next);
  Nan::SetPrototypeMethod(ctor, "previous", Previous);

  Nan::SetPrototypeMethod(ctor, "moments", Moments);
  Nan::SetPrototypeMethod(ctor, "area", Area);
  Nan::SetPrototypeMethod(ctor, "arcLength", ArcLength);
  Nan::SetPrototypeMethod(ctor, "approxPolyDP", ApproxPolyDP);
  Nan::SetPrototypeMethod(ctor, "convexHull", ConvexHull);
  Nan::SetPrototypeMethod(ctor, "isConvex", IsConvex);
  Nan::SetPrototypeMethod(ctor, "boundingRect", BoundingRect);
  Nan::SetPrototypeMethod(ctor, "minAreaRect", MinAreaRect);
  Nan::SetPrototypeMethod(ctor, "minEnclosingCircle", MinEnclosingCircle);
  Nan::SetPrototypeMethod(ctor, "fitEllipse", FitEllipse);
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
  Nan::EscapableHandleScope scope;

  Local<Object> inst = Nan::NewInstance(Nan::GetFunction(Nan::New(constructor)).ToLocalChecked()).ToLocalChecked();

  Contour *contour = UNWRAP_OBJECT(Contour, inst);
  contour->contours.push_back(in);
  contour->hierarchy.push_back(cv::Vec4i::all(-1));

  return scope.Escape(inst);
}

Local<Object> Contour::NewInstance(const std::vector<std::vector<cv::Point>> &contours, const std::vector<cv::Vec4i> &hierarchy, int index) {
  Nan::EscapableHandleScope scope;

  Local<Object> inst = Nan::NewInstance(Nan::GetFunction(Nan::New(constructor)).ToLocalChecked()).ToLocalChecked();

  Contour *contour = UNWRAP_OBJECT(Contour, inst);
  contour->contours = contours;
  contour->hierarchy = hierarchy;
  contour->index = index;

  return scope.Escape(inst);
}

bool Contour::HasInstance(Local<Value> object) {
  return Nan::New(constructor)->HasInstance(object);
}

NAN_INDEX_GETTER(Contour::IndexGetter) {
  Contour *self = UNWRAP_OBJECT(Contour, info.This());

  if (index < self->contours[self->index].size()) {
    info.GetReturnValue().Set(Point::NewInstance(self->contours[self->index][index]));
  }
}

NAN_INDEX_QUERY(Contour::IndexQuery) {
  info.GetReturnValue().Set(Nan::New<Integer>(ReadOnly));
}

NAN_INDEX_ENUMERATOR(Contour::IndexEnumerator) {
  Contour *self = UNWRAP_OBJECT(Contour, info.This());

  v8::Local<v8::Array> arr = Nan::New<v8::Array>();
  for (unsigned i = 0; i < self->contours[self->index].size(); i++) {
    Nan::Set(arr, i, Nan::New(std::to_string(i)).ToLocalChecked());
  }
  info.GetReturnValue().Set(arr);
}

NAN_GETTER(Contour::LengthGetter) {
  Contour *self = UNWRAP_OBJECT(Contour, info.This());
  info.GetReturnValue().Set(Nan::New<Number>(self->contours[self->index].size()));
}

NAN_METHOD(Contour::Parent) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(Contour);

  int index = self->hierarchy[self->index][3];
  if (index == -1) {
    return info.GetReturnValue().SetNull();
  }

  info.GetReturnValue().Set(NewInstance(self->contours, self->hierarchy, index));
}

NAN_METHOD(Contour::Children) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(Contour);

  Local<Array> children = Nan::New<Array>();

  int index = self->hierarchy[self->index][2];
  while (index != -1) {
    Nan::Set(children, children->Length(), NewInstance(self->contours, self->hierarchy, index));
    index = self->hierarchy[index][0];
  }

  info.GetReturnValue().Set(children);
}

NAN_METHOD(Contour::Next) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(Contour);

  int index = self->hierarchy[self->index][0];
  if (index == -1) {
    return info.GetReturnValue().SetNull();
  }

  info.GetReturnValue().Set(NewInstance(self->contours, self->hierarchy, index));
}

NAN_METHOD(Contour::Previous) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(Contour);

  int index = self->hierarchy[self->index][1];
  if (index == -1) {
    return info.GetReturnValue().SetNull();
  }

  info.GetReturnValue().Set(NewInstance(self->contours, self->hierarchy, index));
}

NAN_METHOD(Contour::Moments) {
  NotImplemented
}

NAN_METHOD(Contour::Area) {
  FUNCTION_REQUIRE_ARGUMENTS_RANGE(0, 1);
  SETUP_FUNCTION(Contour);
  DEFAULT_BOOLEAN_FROM_ARGS(oriented, 0, false);

  try {
    info.GetReturnValue().Set(Nan::New<Number>(cv::contourArea(self->contour(), oriented)));
  } catch(cv::Exception e) {
    return Nan::ThrowError(e.what());
  }
}

NAN_METHOD(Contour::ArcLength) {
  FUNCTION_REQUIRE_ARGUMENTS(1);
  SETUP_FUNCTION(Contour);
  ASSERT_BOOLEAN_FROM_ARGS(closed, 0);

  try {
    info.GetReturnValue().Set(Nan::New<Number>(cv::arcLength(self->contour(), closed)));
  } catch(cv::Exception e) {
    return Nan::ThrowError(e.what());
  }
}

NAN_METHOD(Contour::ApproxPolyDP) {
  FUNCTION_REQUIRE_ARGUMENTS(2);
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
  FUNCTION_REQUIRE_ARGUMENTS_RANGE(0, 1);
  SETUP_FUNCTION(Contour);
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
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(Contour);

  try {
    info.GetReturnValue().Set(Nan::New<Boolean>(cv::isContourConvex(self->contour())));
  } catch(cv::Exception e) {
    Nan::ThrowError(e.what());
  }
}

NAN_METHOD(Contour::BoundingRect) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(Contour);

  try {
    info.GetReturnValue().Set(Rect::NewInstance(cv::boundingRect(self->contour())));
  } catch (cv::Exception e) {
    Nan::ThrowError(e.what());
  }
}

NAN_METHOD(Contour::MinAreaRect) {
  NotImplemented
//  Nan::HandleScope scope;
//
//  Contour *self = UNWRAP_OBJECT(Contour, info.This());
//
//  try {
//    cv::minAreaRect(self->contour());
//  } catch (cv::Exception e) {
//    Nan::ThrowError(e.what());
//  }
}

NAN_METHOD(Contour::MinEnclosingCircle) {
  FUNCTION_REQUIRE_ARGUMENTS_RANGE(0, 2);
  SETUP_FUNCTION(Contour);

  DEFAULT_POINT_FROM_ARGS(center, 0, cv::Point());
  DEFAULT_DOUBLE_FROM_ARGS(radius, 1, 0);

  cv::Point2f center2f(center);
  float radiusf(radius);

  try {
    cv::minEnclosingCircle(self->contour(), center2f, radiusf);
  } catch(cv::Exception e) {
    return Nan::ThrowError(e.what());
  }

  Local<Object> out = Nan::New<Object>();
  Nan::Set(out, Nan::New<String>("center").ToLocalChecked(), Point::NewInstance(center));
  Nan::Set(out, Nan::New<String>("radius").ToLocalChecked(), Nan::New<Number>(radius));

  info.GetReturnValue().Set(out);
}

NAN_METHOD(Contour::FitEllipse) {
  NotImplemented
//  Nan::HandleScope scope;
//
//  Contour *self = UNWRAP_OBJECT(Contour, info.This());
//
//  try {
//    cv::fitEllipse(self->contour());
//  } catch (cv::Exception e) {
//    Nan::ThrowError(e.what());
//  }
}

NAN_METHOD(Contour::FitLine) {
  FUNCTION_REQUIRE_ARGUMENTS(4);
  SETUP_FUNCTION(Contour);

  ASSERT_INT_FROM_ARGS(distType, 0);
  ASSERT_INT_FROM_ARGS(param, 1);
  ASSERT_INT_FROM_ARGS(reps, 2);
  ASSERT_INT_FROM_ARGS(aeps, 3);

  cv::Vec4f line;
  TRY_CATCH_THROW_OPENCV(cv::fitLine(self->contour(), line, distType, param, reps, aeps));

  Local<Array> arr = Nan::New<Array>();
  Nan::Set(arr, 0, Point::NewInstance(line[0], line[1]));
  Nan::Set(arr, 1, Point::NewInstance(line[2], line[3]));

  info.GetReturnValue().Set(arr);
}

NAN_METHOD(Contour::ConvexityDefects) {
  FUNCTION_REQUIRE_ARGUMENTS(1);
  SETUP_FUNCTION(Contour);

  if (!info[0]->IsArray()) {
    return THROW_INVALID_ARGUMENT_TYPE(0, "an Array");
  }

  Local<Array> in_arr = Local<Array>::Cast(info[0]);

  std::vector<cv::Point> hull;
  for (unsigned i = 0; i < in_arr->Length(); i++) {
    Local<Value> argv[1] = { Nan::Get(in_arr, i).ToLocalChecked() };
    hull.push_back(Point::RawPoint(1, argv));
  }

  std::vector<std::vector<cv::Vec4i>> defects;
  TRY_CATCH_THROW_OPENCV(cv::convexityDefects(self->contour(), hull, defects));

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
  FUNCTION_REQUIRE_ARGUMENTS(2);
  SETUP_FUNCTION(Contour);

  ASSERT_POINT_FROM_ARGS(point, 0);
  ASSERT_BOOLEAN_FROM_ARGS(measureDist, 1);

  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Number>(cv::pointPolygonTest(self->contour(), point, measureDist))));
}

NAN_METHOD(Contour::MatchShapes) {
  FUNCTION_REQUIRE_ARGUMENTS_RANGE(2, 3);
  SETUP_FUNCTION(Contour);
  ASSERT_CONTOUR_FROM_ARGS(contour, 0);
  ASSERT_INT_FROM_ARGS(method, 1);
  DEFAULT_DOUBLE_FROM_ARGS(parameter, 2, 0);

  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Number>(cv::matchShapes(self->contour(), contour->contour(), method, parameter))));
}

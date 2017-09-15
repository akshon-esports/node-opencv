#include "Contours.h"
#include "OpenCV.h"
#include <nan.h>

#include <iostream>
#include "Contour.h"

Nan::Persistent<FunctionTemplate> Contours::constructor;

void Contours::Init(Local<Object> target) {
  Nan::HandleScope scope;

  // Class/contructor
  Local<FunctionTemplate> ctor = Nan::New<FunctionTemplate>(Contours::New);
  constructor.Reset(ctor);
  ctor->SetClassName(Nan::New("Contours").ToLocalChecked());

  // Instance
  Local<ObjectTemplate> inst = ctor->InstanceTemplate();
  inst->SetInternalFieldCount(1);
  Nan::SetIndexedPropertyHandler(inst, IndexGetter, 0, IndexQuery, 0, IndexEnumerator);

  target->Set(Nan::New("Contours").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(Contours::New) {
  Nan::HandleScope scope;

  if (info.This()->InternalFieldCount() == 0) {
    Nan::ThrowTypeError("Cannot instantiate without new");
  }

  Contours *contours = new Contours();

  contours->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

Local<Object> Contours::NewInstance() {
  return Nan::NewInstance(Nan::GetFunction(Nan::New(constructor)).ToLocalChecked()).ToLocalChecked();
}

Local<Object> Contours::NewInstance(const std::vector<std::vector<cv::Point>> &contours, const std::vector<cv::Vec4i> &hierarchy) {
  Local<Object> inst = NewInstance();

  Contours *contour = UNWRAP_OBJ(Contours, inst);
  contour->contours = contours;
  contour->hierarchy = hierarchy;

  return inst;
}

NAN_INDEX_GETTER(Contours::IndexGetter) {
  Contours *self = UNWRAP_OBJ(Contours, info.This());

  if (index < self->contours.size()) {
    info.GetReturnValue().Set(Contour::NewInstance(self->contours, self->hierarchy, index));
  }
}

NAN_INDEX_QUERY(Contours::IndexQuery) {
  info.GetReturnValue().Set(Nan::New<Integer>(ReadOnly));
}

NAN_INDEX_ENUMERATOR(Contours::IndexEnumerator) {
  Contours *self = UNWRAP_OBJ(Contours, info.This());

  v8::Local<v8::Array> arr = Nan::New<v8::Array>();
  for (int i = 0; i < self->contours.size(); i++) {
    Nan::Set(arr, i, Nan::New(std::to_string(i)).ToLocalChecked());
  }
  info.GetReturnValue().Set(arr);
}

//NAN_METHOD(Contours::Point) {
//  Nan::HandleScope scope;
//
//  Contour *self = Nan::ObjectWrap::Unwrap<Contour>(info.This());
//  int pos = info[0]->NumberValue();
//  int index = info[1]->NumberValue();
//
//  cv::Point point = self->contours[pos][index];
//
//  Local<Object> data = Nan::New<Object>();
//  data->Set(Nan::New("x").ToLocalChecked(), Nan::New<Number>(point.x));
//  data->Set(Nan::New("y").ToLocalChecked(), Nan::New<Number>(point.y));
//
//  info.GetReturnValue().Set(data);
//}
//
//NAN_METHOD(Contours::Points) {
//  Nan::HandleScope scope;
//
//  Contour *self = Nan::ObjectWrap::Unwrap<Contour>(info.This());
//  int pos = info[0]->NumberValue();
//
//  std::vector<cv::Point> points = self->contours[pos];
//  Local<Array> data = Nan::New<Array>(points.size());
//
//  for (std::vector<int>::size_type i = 0; i != points.size(); i++) {
//    Local<Object> point_data = Nan::New<Object>();
//    point_data->Set(Nan::New<String>("x").ToLocalChecked(), Nan::New<Number>(points[i].x));
//    point_data->Set(Nan::New<String>("y").ToLocalChecked(), Nan::New<Number>(points[i].y));
//
//    data->Set(i, point_data);
//  }
//
//  info.GetReturnValue().Set(data);
//}
//
//// FIXME: this should better be called "Length" as ``Contours`` is an Array like
//// structure also, this would allow to use ``Size`` for the function returning
//// the number of corners in the contour for better consistency with OpenCV.
//NAN_METHOD(Contours::Size) {
//  Nan::HandleScope scope;
//
//  Contour *self = Nan::ObjectWrap::Unwrap<Contour>(info.This());
//
//  info.GetReturnValue().Set(Nan::New<Number>(self->contours.size()));
//}
//
//NAN_METHOD(Contours::CornerCount) {
//  Nan::HandleScope scope;
//
//  Contour *self = Nan::ObjectWrap::Unwrap<Contour>(info.This());
//  int pos = info[0]->NumberValue();
//
//  info.GetReturnValue().Set(Nan::New<Number>(self->contours[pos].size()));
//}
//
//NAN_METHOD(Contours::Area) {
//  Nan::HandleScope scope;
//
//  Contour *self = Nan::ObjectWrap::Unwrap<Contour>(info.This());
//  int pos = info[0]->NumberValue();
//  bool orientation = (info.Length() > 1 && info[1]->BooleanValue());
//
//  // info.GetReturnValue().Set(Nan::New<Number>(contourArea(self->contours)));
//  info.GetReturnValue().Set(Nan::New<Number>(contourArea(cv::Mat(self->contours[pos]), orientation)));
//}
//
//NAN_METHOD(Contours::ArcLength) {
//  Nan::HandleScope scope;
//
//  Contour *self = Nan::ObjectWrap::Unwrap<Contour>(info.This());
//  int pos = info[0]->NumberValue();
//  bool isClosed = info[1]->BooleanValue();
//
//  info.GetReturnValue().Set(Nan::New<Number>(arcLength(cv::Mat(self->contours[pos]), isClosed)));
//}
//
//NAN_METHOD(Contours::ApproxPolyDP) {
//  Nan::HandleScope scope;
//
//  Contour *self = Nan::ObjectWrap::Unwrap<Contour>(info.This());
//  int pos = info[0]->NumberValue();
//  double epsilon = info[1]->NumberValue();
//  bool isClosed = info[2]->BooleanValue();
//
//  cv::Mat approxed;
//  approxPolyDP(cv::Mat(self->contours[pos]), approxed, epsilon, isClosed);
//  approxed.copyTo(self->contours[pos]);
//
//  info.GetReturnValue().Set(Nan::Null());
//}
//
//NAN_METHOD(Contours::ConvexHull) {
//  Nan::HandleScope scope;
//
//  Contour *self = Nan::ObjectWrap::Unwrap<Contour>(info.This());
//
//  int pos = info[0]->NumberValue();
//  bool clockwise = info[1]->BooleanValue();
//
//  cv::Mat hull;
//  cv::convexHull(cv::Mat(self->contours[pos]), hull, clockwise);
//  hull.copyTo(self->contours[pos]);
//
//  info.GetReturnValue().Set(Nan::Null());
//}
//
//NAN_METHOD(Contours::BoundingRect) {
//  Nan::HandleScope scope;
//
//  Contour *self = Nan::ObjectWrap::Unwrap<Contour>(info.This());
//  int pos = info[0]->NumberValue();
//
//  cv::Rect bounding = cv::boundingRect(cv::Mat(self->contours[pos]));
//  Local<Object> rect = Nan::New<Object>();
//
//  rect->Set(Nan::New("x").ToLocalChecked(), Nan::New<Number>(bounding.x));
//  rect->Set(Nan::New("y").ToLocalChecked(), Nan::New<Number>(bounding.y));
//  rect->Set(Nan::New("width").ToLocalChecked(), Nan::New<Number>(bounding.width));
//  rect->Set(Nan::New("height").ToLocalChecked(), Nan::New<Number>(bounding.height));
//
//  info.GetReturnValue().Set(rect);
//}
//
//NAN_METHOD(Contours::MinAreaRect) {
//  Nan::HandleScope scope;
//
//  Contour *self = Nan::ObjectWrap::Unwrap<Contour>(info.This());
//  int pos = info[0]->NumberValue();
//
//  cv::RotatedRect minimum = cv::minAreaRect(cv::Mat(self->contours[pos]));
//
//  Local<Object> rect = Nan::New<Object>();
//  rect->Set(Nan::New("angle").ToLocalChecked(), Nan::New<Number>(minimum.angle));
//
//  Local<Object> size = Nan::New<Object>();
//  size->Set(Nan::New("height").ToLocalChecked(), Nan::New<Number>(minimum.size.height));
//  size->Set(Nan::New("width").ToLocalChecked(), Nan::New<Number>(minimum.size.width));
//  rect->Set(Nan::New("size").ToLocalChecked(), size);
//
//  Local<Object> center = Nan::New<Object>();
//  center->Set(Nan::New("x").ToLocalChecked(), Nan::New<Number>(minimum.center.x));
//  center->Set(Nan::New("y").ToLocalChecked(), Nan::New<Number>(minimum.center.y));
//
//  v8::Local<v8::Array> points = Nan::New<Array>(4);
//
//  cv::Point2f rect_points[4];
//  minimum.points(rect_points);
//
//  for (unsigned int i=0; i<4; i++) {
//    Local<Object> point = Nan::New<Object>();
//    point->Set(Nan::New("x").ToLocalChecked(), Nan::New<Number>(rect_points[i].x));
//    point->Set(Nan::New("y").ToLocalChecked(), Nan::New<Number>(rect_points[i].y));
//    points->Set(i, point);
//  }
//
//  rect->Set(Nan::New("points").ToLocalChecked(), points);
//
//  info.GetReturnValue().Set(rect);
//}
//
//NAN_METHOD(Contours::FitEllipse) {
//  Nan::HandleScope scope;
//
//  Contour *self = Nan::ObjectWrap::Unwrap<Contour>(info.This());
//  int pos = info[0]->NumberValue();
//
//  if (self->contours[pos].size() >= 5) {  // Minimum number for an ellipse
//    cv::RotatedRect ellipse = cv::fitEllipse(cv::Mat(self->contours[pos]));
//
//    Local<Object> jsEllipse = Nan::New<Object>();
//    jsEllipse->Set(Nan::New("angle").ToLocalChecked(), Nan::New<Number>(ellipse.angle));
//
//    Local<Object> size = Nan::New<Object>();
//    size->Set(Nan::New("height").ToLocalChecked(), Nan::New<Number>(ellipse.size.height));
//    size->Set(Nan::New("width").ToLocalChecked(), Nan::New<Number>(ellipse.size.width));
//    jsEllipse->Set(Nan::New("size").ToLocalChecked(), size);
//
//    Local<Object> center = Nan::New<Object>();
//    center->Set(Nan::New("x").ToLocalChecked(), Nan::New<Number>(ellipse.center.x));
//    center->Set(Nan::New("y").ToLocalChecked(), Nan::New<Number>(ellipse.center.y));
//    jsEllipse->Set(Nan::New("center").ToLocalChecked(), center);
//
//    info.GetReturnValue().Set(jsEllipse);
//  }
//
//  info.GetReturnValue().Set(Nan::Null());
//}
//
//NAN_METHOD(Contours::IsConvex) {
//  Nan::HandleScope scope;
//
//  Contour *self = Nan::ObjectWrap::Unwrap<Contour>(info.This());
//  int pos = info[0]->NumberValue();
//
//  info.GetReturnValue().Set(Nan::New<Boolean>(isContourConvex(cv::Mat(self->contours[pos]))));
//}
//
//NAN_METHOD(Contours::Moments) {
//  Nan::HandleScope scope;
//
//  Contour *self = Nan::ObjectWrap::Unwrap<Contour>(info.This());
//  int pos = info[0]->NumberValue();
//
//  // Get the moments
//  cv::Moments mu = moments( self->contours[pos], false );
//
//  Local<Object> res = Nan::New<Object>();
//
//  res->Set(Nan::New("m00").ToLocalChecked(), Nan::New<Number>(mu.m00));
//  res->Set(Nan::New("m10").ToLocalChecked(), Nan::New<Number>(mu.m10));
//  res->Set(Nan::New("m01").ToLocalChecked(), Nan::New<Number>(mu.m01));
//  res->Set(Nan::New("m11").ToLocalChecked(), Nan::New<Number>(mu.m11));
//
//  info.GetReturnValue().Set(res);
//}
//
//NAN_METHOD(Contours::Hierarchy) {
//  Nan::HandleScope scope;
//
//  Contour *self = Nan::ObjectWrap::Unwrap<Contour>(info.This());
//  int pos = info[0]->IntegerValue();
//
//  cv::Vec4i hierarchy = self->hierarchy[pos];
//
//  Local<Array> res = Nan::New<Array>(4);
//
//  res->Set(0, Nan::New<Number>(hierarchy[0]));
//  res->Set(1, Nan::New<Number>(hierarchy[1]));
//  res->Set(2, Nan::New<Number>(hierarchy[2]));
//  res->Set(3, Nan::New<Number>(hierarchy[3]));
//
//  info.GetReturnValue().Set(res);
//}
//
//NAN_METHOD(Contours::Serialize) {
//  Nan::HandleScope scope;
//
//  Contour *self = Nan::ObjectWrap::Unwrap<Contour>(info.This());
//
//  Local<Array> contours_data = Nan::New<Array>(self->contours.size());
//
//  for (std::vector<int>::size_type i = 0; i != self->contours.size(); i++) {
//    std::vector<cv::Point> points = self->contours[i];
//    Local<Array> contour_data = Nan::New<Array>(points.size());
//
//    for (std::vector<int>::size_type j = 0; j != points.size(); j++) {
//      Local<Array> point_data = Nan::New<Array>(2);
//      point_data->Set(0, Nan::New<Number>(points[j].x));
//      point_data->Set(1, Nan::New<Number>(points[j].y));
//
//      contour_data->Set(j, point_data);
//    }
//    contours_data->Set(i, contour_data);
//  }
//
//  Local<Array> hierarchy_data = Nan::New<Array>(self->hierarchy.size());
//  for (std::vector<int>::size_type i = 0; i != self->hierarchy.size(); i++) {
//    Local<Array> contour_data = Nan::New<Array>(4);
//    contour_data->Set(0, Nan::New<Number>(self->hierarchy[i][0]));
//    contour_data->Set(1, Nan::New<Number>(self->hierarchy[i][1]));
//    contour_data->Set(2, Nan::New<Number>(self->hierarchy[i][2]));
//    contour_data->Set(3, Nan::New<Number>(self->hierarchy[i][3]));
//
//    hierarchy_data->Set(i, contour_data);
//  }
//
//  Local<Object> data = Nan::New<Object>();
//  data->Set(Nan::New<String>("contours").ToLocalChecked(), contours_data);
//  data->Set(Nan::New<String>("hierarchy").ToLocalChecked(), hierarchy_data);
//
//  info.GetReturnValue().Set(data);
//}
//
//NAN_METHOD(Contours::Deserialize) {
//  Nan::HandleScope scope;
//
//  Contour *self = Nan::ObjectWrap::Unwrap<Contour>(info.This());
//
//  Local<Object> data = Local<Object>::Cast(info[0]);
//
//  Local<Array> contours_data = Local<Array>::Cast(data->Get(Nan::New<String>("contours").ToLocalChecked()));
//  Local<Array> hierarchy_data = Local<Array>::Cast(data->Get(Nan::New<String>("hierarchy").ToLocalChecked()));
//
//  std::vector<std::vector<cv::Point> > contours_res;
//  int contours_length = contours_data->Length();
//
//  for (int i = 0; i < contours_length; i++) {
//    Local<Array> contour_data = Local<Array>::Cast(contours_data->Get(i));
//    std::vector<cv::Point> points;
//
//    int contour_length = contour_data->Length();
//    for (int j = 0; j < contour_length; j++) {
//      Local<Array> point_data = Local<Array>::Cast(contour_data->Get(j));
//      int x = point_data->Get(0)->IntegerValue();
//      int y = point_data->Get(1)->IntegerValue();
//      points.push_back(cv::Point(x, y));
//    }
//
//    contours_res.push_back(points);
//  }
//
//  std::vector<cv::Vec4i> hierarchy_res;
//  int hierarchy_length = hierarchy_data->Length();
//
//  for (int i = 0; i < hierarchy_length; i++) {
//    Local<Array> contour_data = Local<Array>::Cast(hierarchy_data->Get(i));
//    int a = contour_data->Get(0)->IntegerValue();
//    int b = contour_data->Get(1)->IntegerValue();
//    int c = contour_data->Get(2)->IntegerValue();
//    int d = contour_data->Get(3)->IntegerValue();
//    hierarchy_res.push_back(cv::Vec4i(a, b, c, d));
//  }
//
//  self->contours = contours_res;
//  self->hierarchy = hierarchy_res;
//
//  info.GetReturnValue().Set(Nan::Null());
//}

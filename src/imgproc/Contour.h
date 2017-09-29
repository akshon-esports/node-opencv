#ifndef __IMGPROC__CONTOUR_H__
#define __IMGPROC__CONTOUR_H__

#include "common.h"

#define CONTOUR_FROM_ARGS(NAME, IND) \
  Contour *NAME = nullptr; \
  if (info.Length() > IND && Contour::HasInstance(info[IND])) { \
    NAME = UNWRAP_OBJECT(Contour, info[IND]->ToObject()); \
  }

#define ASSERT_CONTOUR_FROM_ARGS(NAME, IND) \
  CONTOUR_FROM_ARGS(NAME, IND) else { \
    return THROW_INVALID_ARGUMENT_TYPE(IND, "a Contour"); \
  }

class Contour: public Nan::ObjectWrap {
private:
  static Nan::Persistent<FunctionTemplate> constructor;

public:
  std::vector<std::vector<cv::Point>> contours;
  std::vector<cv::Vec4i> hierarchy;
  int index = 0;

  static void Init(Local<Object> target);
  static NAN_METHOD(New);

  Contour() : Nan::ObjectWrap() {};

  inline std::vector<cv::Point> contour() { return contours[index]; };

  static Local<Object> NewInstance(const std::vector<cv::Point> &contour);
  static Local<Object> NewInstance(const std::vector<std::vector<cv::Point>> &contours, const std::vector<cv::Vec4i> &hierarchy, int index);

  static bool HasInstance(Local<Value> object);

  static NAN_INDEX_GETTER(IndexGetter);
  static NAN_INDEX_SETTER(IndexSetter);
  static NAN_INDEX_QUERY(IndexQuery);
  static NAN_INDEX_ENUMERATOR(IndexEnumerator);

  static NAN_GETTER(LengthGetter);

  // traversing hierarchy
  static NAN_METHOD(Parent);
  static NAN_METHOD(Children);
  static NAN_METHOD(Next);
  static NAN_METHOD(Previous);

  // contour features
  static NAN_METHOD(Moments); // no `Moments` primitive yet
  static NAN_METHOD(Area);
  static NAN_METHOD(ArcLength);
  static NAN_METHOD(ApproxPolyDP);
  static NAN_METHOD(ConvexHull);
  static NAN_METHOD(IsConvex);
  static NAN_METHOD(BoundingRect);
  static NAN_METHOD(MinAreaRect); // no `RotatedRect` primitive yet
  static NAN_METHOD(MinEnclosingCircle);
  static NAN_METHOD(FitEllipse);
  static NAN_METHOD(FitLine);

  // more contour features
  static NAN_METHOD(ConvexityDefects);
  static NAN_METHOD(PointPolygonTest);
  static NAN_METHOD(MatchShapes);
};

#endif // __IMGPROC__CONTOUR_H__

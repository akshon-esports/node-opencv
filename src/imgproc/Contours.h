#ifndef __IMGPROC__CONTOURS_H__
#define __IMGPROC__CONTOURS_H__

#include "common.h"

#define CONTOURS_FROM_ARGS(NAME, IND) \
  Contours *NAME = nullptr; \
  if (info.Length() > IND && Contours::HasInstance(info[IND])) { \
    NAME = UNWRAP_OBJECT(Contours, info[IND]->ToObject()); \
  }

#define ASSERT_CONTOURS_FROM_ARGS(NAME, IND) \
  CONTOURS_FROM_ARGS(NAME, IND) else { \
    return THROW_INVALID_ARGUMENT_TYPE(IND, "an instance of Contours"); \
  }

class Contours : public Nan::ObjectWrap {
private:
  static Nan::Persistent<FunctionTemplate> constructor;
  
public:
  std::vector<std::vector<cv::Point>> contours;
  std::vector<cv::Vec4i> hierarchy;

  static void Init(Local<Object> target);
  static NAN_METHOD(New);

  Contours() {};

  NEW_INSTANCE_DEF;
  static Local<Object> NewInstance(const std::vector<std::vector<cv::Point>> &contours, const std::vector<cv::Vec4i> &hierarchy);

  HAS_INSTANCE_DEF;

  static NAN_INDEX_GETTER(IndexGetter);
  static NAN_INDEX_SETTER(IndexSetter);
  static NAN_INDEX_QUERY(IndexQuery);
  static NAN_INDEX_ENUMERATOR(IndexEnumerator);

  static NAN_GETTER(LengthGetter);
};

#endif // __IMGPROC__CONTOURS_H__

#ifndef __CORE__POINT_H__
#define __CORE__POINT_H__

#include "common.h"

#define TRY_CATCH_POINT_FROM_ARGS(NAME, IND, CATCH) \
  cv::Point NAME; \
  try { \
    NAME = Point::RawPoint(1, &info[IND]); \
  } catch (const char *) { \
    CATCH \
  }

#define ASSERT_POINT_FROM_ARGS(NAME, IND) \
  TRY_CATCH_POINT_FROM_ARGS(NAME, IND, return THROW_INVALID_ARGUMENT_TYPE(IND, "a Point");)

#define DEFAULT_POINT_FROM_ARGS(NAME, IND, DEF) \
  TRY_CATCH_POINT_FROM_ARGS(NAME, IND, NAME = DEF;)

class NCV_CORE_EXTERN Point: public Nan::ObjectWrap {
private:
  static Nan::Persistent<FunctionTemplate> constructor;

public:
  cv::Point point;

  static void Init(Local<Object> target);
  static NAN_METHOD(New);

  Point() : Nan::ObjectWrap() {};

  NEW_INSTANCE_DEF;
  static Local<Object> NewInstance(cv::Point const &point);
  static Local<Object> NewInstance(int const &x, int const &y);

  HAS_INSTANCE_DEF;

  static cv::Point RawPoint(int const &argc, Local<Value>* const argv);

  static NAN_GETTER(Getter);
  static NAN_SETTER(Setter);

  static NAN_METHOD(Dot);
};

#endif // __CORE__POINT_H__

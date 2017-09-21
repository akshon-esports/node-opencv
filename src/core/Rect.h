#ifndef __CORE__RECT_H__
#define __CORE__RECT_H__

#include "common.h"

class NCV_CORE_EXTERN Rect : public Nan::ObjectWrap {
private:
  static Nan::Persistent<FunctionTemplate> constructor;

public:
  cv::Rect rect;

  static void Init(Local<Object> target);
  static NAN_METHOD(New);

  Rect() : Nan::ObjectWrap() {};

  NEW_INSTANCE_DEF;
  static Local<Object> NewInstance(cv::Rect const &rect);
  static Local<Object> NewInstance(cv::Point const &point, cv::Size const &size);
  static Local<Object> NewInstance(cv::Point const &point1, cv::Point const &point2);
  static Local<Object> NewInstance(int const &x, int const &y, int const &width, int const &height);

  HAS_INSTANCE_DEF;

  static cv::Rect RawRect(int const &argc, Local<Value>* const argv);

  static GENERIC_NAMED_PROPERTY_GETTER(NamedPropertyGetter);
  static GENERIC_NAMED_PROPERTY_SETTER(NamedPropertySetter);
  static GENERIC_NAMED_PROPERTY_QUERY(NamedPropertyQuery);
  static GENERIC_NAMED_PROPERTY_ENUMERATOR(NamedPropertyEnumerator);

  static NAN_GETTER(Getter);
  static NAN_SETTER(Setter);

  static NAN_METHOD(TopLeft);
  static NAN_METHOD(BottomRight);

  static NAN_METHOD(Size);
  static NAN_METHOD(Area);

  static NAN_METHOD(Contains);

  static NAN_METHOD(ToString);
};

#endif // __CORE__RECT_H__

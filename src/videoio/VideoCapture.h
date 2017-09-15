#ifndef __VIDEOIO__VIDEOCAPTURE_H__
#define __VIDEOIO__VIDEOCAPTURE_H__

#include "common.h"

class VideoCapture : public Nan::ObjectWrap {
private:
  static Nan::Persistent<FunctionTemplate> constructor;
  
public:
  cv::VideoCapture cap;

  static void Init(Local<Object> target);
  static NAN_METHOD(New);

  VideoCapture() {};

  NEW_INSTANCE_DEF;

  HAS_INSTANCE_DEF;

  static NAN_METHOD(Get);
  static NAN_METHOD(Grab);
  static NAN_METHOD(IsOpened);
  static NAN_METHOD(Read);
  static NAN_METHOD(Release);
  static NAN_METHOD(Retrieve);
  static NAN_METHOD(Set);
};

#endif // __VIDEOIO__VIDEOCAPTURE_H__

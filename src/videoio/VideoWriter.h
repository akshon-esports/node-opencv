#ifndef __VIDEOIO__VIDEOWRITER_H__
#define __VIDEOIO__VIDEOWRITER_H__

#include "common.h"

class VideoWriter : public Nan::ObjectWrap {
private:
  static Nan::Persistent<FunctionTemplate> constructor;
  
public:
  cv::VideoWriter cap;

  static void Init(Local<Object> target);
  static NAN_METHOD(New);

  VideoWriter() {};

  NEW_INSTANCE_DEF;

  HAS_INSTANCE_DEF;

  static NAN_METHOD(Get);
  static NAN_METHOD(IsOpened);
  static NAN_METHOD(Release);
  static NAN_METHOD(Set);
  static NAN_METHOD(Write);
};

#endif // __VIDEOIO__VIDEOWRITER_H__

#ifndef __TEXT__OCRTESSERACT_H__
#define __TEXT__OCRTESSERACT_H__

#include "common.h"

class OCRTesseract : public Nan::ObjectWrap {
private:
  static Nan::Persistent<FunctionTemplate> constructor;

public:
  cv::Ptr<cv::text::OCRTesseract> tesseract;

  static void Init(Local<Object> target);
  static NAN_METHOD(New);

  OCRTesseract() : Nan::ObjectWrap() {};

  NEW_INSTANCE_DEF;

  HAS_INSTANCE_DEF;

  static NAN_METHOD(SetWhitelist);

  static NAN_METHOD(Run);
};

#endif // __TEXT__OCRTESSERACT_H__

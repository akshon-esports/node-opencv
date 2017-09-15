#include "OpenCV.h"

#define CONTOURS_FROM_ARGS(NAME, IND) \
  Contours *NAME = nullptr; \
  if (info.Length() > IND && Contours::HasInstance(info[IND])) { \
    NAME = UNWRAP_OBJ(Contours, info[IND]->ToObject()); \
  }

#define ASSERTS_CONTOUR_FROM_ARGS(NAME, IND) \
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

  static Local<Object> NewInstance();
  static Local<Object> NewInstance(const std::vector<std::vector<cv::Point>> &contours, const std::vector<cv::Vec4i> &hierarchy);

  static bool HasInstance(Local<Value> object);

  static NAN_INDEX_GETTER(IndexGetter);
  static NAN_INDEX_SETTER(IndexSetter);
  static NAN_INDEX_QUERY(IndexQuery);
  static NAN_INDEX_ENUMERATOR(IndexEnumerator);
};


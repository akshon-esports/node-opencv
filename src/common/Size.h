#ifndef __COMMON__SIZE_H__
#define __COMMON__SIZE_H__

#include "common.h"

#define _TRY_CATCH_SIZE_FROM_ARGS(NAME, IND, CATCH) \
  cv::Size NAME; \
  try { \
    Local<Value> val = info[IND]; \
    NAME = Size::RawSize(1, &val); \
  } catch (const char *) { \
    CATCH \
  }

#define ASSERT_SIZE_FROM_ARGS(NAME, IND) \
  _TRY_CATCH_SIZE_FROM_ARGS(NAME, IND, return THROW_INVALID_ARGUMENT_TYPE(IND, "a Size");)

#define DEFAULT_SIZE_FROM_ARGS(NAME, IND, DEF) \
  _TRY_CATCH_SIZE_FROM_ARGS(NAME, IND, NAME = DEF;)

namespace ncv {
  
  namespace common {
    
    class NCV_COMMON_EXTERN Size : public Nan::ObjectWrap {
    private:
      static Nan::Persistent<FunctionTemplate> constructor;

    public:
      cv::Size size;

      static void Init(Local<Object> const target);
      static NAN_METHOD(New);

      Size() : Nan::ObjectWrap() {};

      NEW_INSTANCE_DECL;
      static Local<Object> NewInstance(cv::Size const &size);
      static Local<Object> NewInstance(int const &width, int const &height);

      HAS_INSTANCE_DECL;

      static cv::Size RawSize(int const &argc, Local<Value>* const argv);

      static NAN_GETTER(Getter);
      static NAN_SETTER(Setter);

      static NAN_METHOD(Area);

      static NAN_METHOD(ToString);
    };

  }

}

#endif // __COMMON__SIZE_H__

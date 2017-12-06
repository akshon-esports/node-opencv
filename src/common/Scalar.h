#ifndef __COMMON__SCALAR_H__
#define __COMMON__SCALAR_H__

#include "common.h"

#define _TRY_CATCH_SCALAR_FROM_ARGS(NAME, IND, CATCH) \
  cv::Scalar NAME; \
  try { \
    Local<Value> arg = info[IND]; \
    NAME = Scalar::RawScalar(1, &arg); \
  } catch (const char *) { \
    CATCH \
  }

#define ASSERT_SCALAR_FROM_ARGS(NAME, IND) \
  _TRY_CATCH_SCALAR_FROM_ARGS(NAME, IND, return THROW_INVALID_ARGUMENT_TYPE(IND, "a Scalar");)

#define DEFAULT_SCALAR_FROM_ARGS(NAME, IND, DEF) \
  _TRY_CATCH_SCALAR_FROM_ARGS(NAME, IND, NAME = DEF;)

namespace ncv {
  
  namespace common {

    class NCV_COMMON_EXTERN Scalar : public Nan::ObjectWrap {
    private:
      static Nan::Persistent<FunctionTemplate> constructor;

    public:
      cv::Scalar scalar;

      static NAN_MODULE_INIT(Init);
      static NAN_METHOD(New);

      Scalar() : Nan::ObjectWrap() {};

      NEW_INSTANCE_DECL;
      static Local<Object> NewInstance(cv::Scalar const &scalar);
      static Local<Object> NewInstance(double const &v0, double const &v1 = 0, double const &v2 = 0, double const &v3 = 0);

      HAS_INSTANCE_DECL;

      static cv::Scalar RawScalar(int const &argc, Local<Value>* const argv);
    };
    
  }

}

#endif // __COMMON__SCALAR_H__

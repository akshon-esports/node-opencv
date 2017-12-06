#ifndef __COMMON__MATRIX_H__
#define __COMMON__MATRIX_H__

#include "common.h"

#define MATRIX_FROM_ARGS(NAME, IND) \
  Matrix *NAME = nullptr; \
  if (info.Length() > IND && Matrix::HasInstance(info[IND])) { \
    NAME = UNWRAP_OBJECT(Matrix, info[IND]->ToObject()); \
  }

#define ASSERT_MATRIX_FROM_ARGS(NAME, IND) \
  MATRIX_FROM_ARGS(NAME, IND) else { \
    return THROW_INVALID_ARGUMENT_TYPE(IND, "a Matrix"); \
  }

namespace ncv {

  namespace common {

    class NCV_COMMON_EXTERN Matrix : public Nan::ObjectWrap {
    private:
      static Nan::Persistent<FunctionTemplate> constructor;

    public:
      cv::Mat mat;

      static NAN_MODULE_INIT(Init);
      static NAN_METHOD(New);

      Matrix(cv::Mat mat) : Nan::ObjectWrap(), mat(mat) {};

      NEW_INSTANCE_DECL;
      static Local<Object> NewInstance(cv::Mat mat);

      HAS_INSTANCE_DECL;

      static cv::Mat RawMatrix(int const &argc, Local<Value>* const argv);
    };
    
  }

}

#endif // __COMMON__MATRIX_H__

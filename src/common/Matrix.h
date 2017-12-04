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

      static void Init(Local<Object> target);
      static NAN_METHOD(New);

      Matrix(cv::Mat mat) : Nan::ObjectWrap(), mat(mat) {};

      NEW_INSTANCE_DEF;
      static Local<Object> NewInstance(cv::Mat mat);

      HAS_INSTANCE_DEF;

      static cv::Mat RawMatrix(int const &argc, Local<Value>* const argv);

      static NAN_METHOD(GetUnifiedMatrix);

      static NAN_METHOD(Row);
      static NAN_METHOD(Col);
      static NAN_METHOD(RowRange);
      static NAN_METHOD(ColRange);
      static NAN_METHOD(Diag);

      static NAN_METHOD(Clone);

      static NAN_METHOD(CopyTo);

      static NAN_METHOD(ConvertTo);
      static NAN_METHOD(SetTo);

      static NAN_METHOD(Reshape);

      static NAN_METHOD(Transpose);
      static NAN_METHOD(Invert);
      static NAN_METHOD(Multiply);

      static NAN_METHOD(Cross);
      static NAN_METHOD(Dot);

      static NAN_METHOD(Create);
      static NAN_METHOD(Release);

      static NAN_METHOD(Reserve);
      static NAN_METHOD(ReserveBuffer);

      static NAN_METHOD(Resize);

      static NAN_METHOD(PushBack);
      static NAN_METHOD(PopBack);

      static NAN_METHOD(LocateROI);
      static NAN_METHOD(AdjustROI);

      static NAN_METHOD(IsContinuous);
      static NAN_METHOD(IsSubmatrix);

      static NAN_METHOD(ElemSize);
      static NAN_METHOD(ElemSize1);

      static NAN_METHOD(Type);
      static NAN_METHOD(Depth);
      static NAN_METHOD(Channels);
      static NAN_METHOD(Step1);
      static NAN_METHOD(Empty);
      static NAN_METHOD(Total);

      static NAN_METHOD(At);

      static NAN_METHOD(Size);

      static NAN_GETTER(GetFlags);
      static NAN_GETTER(GetDimensions);
      static NAN_GETTER(GetRows);
      static NAN_GETTER(GetColumns);

      static NAN_METHOD(ToBuffer);
    };
    
  }

}

#endif // __COMMON__MATRIX_H__

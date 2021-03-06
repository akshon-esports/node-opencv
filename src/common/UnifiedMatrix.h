#ifndef __CORE__UNIFIED_MATRIX_H__
#define __CORE__UNIFIED_MATRIX_H__

#include "common.h"

namespace ncv {
  
  namespace common {
    
    class NCV_COMMON_EXTERN UnifiedMatrix : public Nan::ObjectWrap {
    private:
      static Nan::Persistent<FunctionTemplate> constructor;

    public:
      cv::UMat mat;

      static void Init(Local<Object> const &target);
      static NAN_METHOD(New);

      UnifiedMatrix() : Nan::ObjectWrap() {};
      UnifiedMatrix(cv::UMat mat) : Nan::ObjectWrap(), mat(mat) {};

      NEW_INSTANCE_DECL;
      static Local<Object> NewInstance(cv::UMat mat);

      HAS_INSTANCE_DECL;

      static cv::UMat RawUnifiedMatrix(int const &argc, Local<Value>* const argv);

      static NAN_METHOD(GetMatrix);

      static NAN_METHOD(Row);
      static NAN_METHOD(Col);
      static NAN_METHOD(RowRange);
      static NAN_METHOD(ColRange);
      static NAN_METHOD(Diag);

      static NAN_METHOD(Clone);

      static NAN_METHOD(ConvertTo);
      static NAN_METHOD(SetTo);

      static NAN_METHOD(Reshape);

      static NAN_METHOD(Transpose);
      static NAN_METHOD(Invert);
      static NAN_METHOD(Multiply);

      static NAN_METHOD(Dot);

      static NAN_METHOD(Create);
      static NAN_METHOD(Release);

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

      static NAN_METHOD(Size);

      static NAN_GETTER(GetFlags);
      static NAN_GETTER(GetDimensions);
      static NAN_GETTER(GetRows);
      static NAN_GETTER(GetColumns);
    };

  }

}

#endif // __CORE__UNIFIED_MATRIX_H__

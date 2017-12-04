#include "hist.h"

namespace ncv {

  namespace imgproc {

    NAN_METHOD(CalcBackProject) {
      NotImplemented
    }

    NAN_METHOD(CalcHist) {
      NotImplemented
    }

    NAN_METHOD(CompareHist) {
      NotImplemented
    }

    NAN_METHOD(EMD) {
      NotImplemented
    }

    NAN_METHOD(EqualizeHist) {
      FUNCTION_REQUIRE_ARGUMENTS(2);
      ASSERT_INPUTARRAY_FROM_ARGS(src, 0);
      ASSERT_OUTPUTARRAY_FROM_ARGS(dst, 1);
      TRY_CATCH_THROW_OPENCV(cv::equalizeHist(src, dst));
    }

    NAN_METHOD(WrapperEMD) {
      NotImplemented
    }

    void HistInit(Local<Object> &target) {
      // hist comp methods
      DEFINE_CONST_ENUM(HISTCMP_CORREL);
      DEFINE_CONST_ENUM(HISTCMP_CHISQR);
      DEFINE_CONST_ENUM(HISTCMP_INTERSECT);
      DEFINE_CONST_ENUM(HISTCMP_BHATTACHARYYA);
      DEFINE_CONST_ENUM(HISTCMP_HELLINGER);
      DEFINE_CONST_ENUM(HISTCMP_CHISQR_ALT);
      DEFINE_CONST_ENUM(HISTCMP_KL_DIV);

      Nan::SetMethod(target, "calcBackProject", CalcBackProject);
      Nan::SetMethod(target, "calcHist", CalcHist);
      Nan::SetMethod(target, "compareHist", CompareHist);
      Nan::SetMethod(target, "emd", EMD);
      Nan::SetMethod(target, "equalizeHist", EqualizeHist);
      Nan::SetMethod(target, "wrapperEMD", WrapperEMD);
    }

  }

}
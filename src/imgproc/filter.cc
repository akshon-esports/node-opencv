#include "filter.h"

namespace ncv {

  namespace imgproc {

    void FilterInit(Local<Object> &target) {
      // morph shapes
      DEFINE_CONST_ENUM(MORPH_RECT);
      DEFINE_CONST_ENUM(MORPH_CROSS);
      DEFINE_CONST_ENUM(MORPH_ELLIPSE);

      // morph types
      DEFINE_CONST_ENUM(MORPH_ERODE);
      DEFINE_CONST_ENUM(MORPH_DILATE);
      DEFINE_CONST_ENUM(MORPH_OPEN);
      DEFINE_CONST_ENUM(MORPH_CLOSE);
      DEFINE_CONST_ENUM(MORPH_GRADIENT);
      DEFINE_CONST_ENUM(MORPH_TOPHAT);
      DEFINE_CONST_ENUM(MORPH_BLACKHAT);
      DEFINE_CONST_ENUM(MORPH_HITMISS);

      Nan::SetMethod(target, "bilateralFilter", BilateralFilter);
      Nan::SetMethod(target, "blur", Blur);
      Nan::SetMethod(target, "boxFilter", BoxFilter);
      Nan::SetMethod(target, "buildPyramid", BuildPyramid);
      Nan::SetMethod(target, "dilate", Dilate);
      Nan::SetMethod(target, "erode", Erode);
      Nan::SetMethod(target, "filter2D", Filter2D);
      Nan::SetMethod(target, "GaussianBlur", GaussianBlur);
      Nan::SetMethod(target, "getDerivKernels", GetDerivKernels);
      Nan::SetMethod(target, "getGaborKernel", GetGaborKernel);
      Nan::SetMethod(target, "getGaussianKernel", GetGaussianKernel);
      Nan::SetMethod(target, "getStructuringElement", GetStructuringElement);
      Nan::SetMethod(target, "Laplacian", Laplacian);
      Nan::SetMethod(target, "medianBlur", MedianBlur);
      Nan::SetMethod(target, "morphologyDefaultBorderValue", MorphologyDefaultBorderValue);
      Nan::SetMethod(target, "morphologyEx", MorphologyEx);
      Nan::SetMethod(target, "pyrDown", PyrDown);
      Nan::SetMethod(target, "pyrMeanShiftFiltering", PyrMeanShiftFiltering);
      Nan::SetMethod(target, "pyrUp", PyrUp);
      Nan::SetMethod(target, "Scharr", Scharr);
      Nan::SetMethod(target, "sepFilter2D", SepFilter2D);
      Nan::SetMethod(target, "Sobel", Sobel);
      Nan::SetMethod(target, "spatialGradient", SpatialGradient);
      Nan::SetMethod(target, "sqrBoxFilter", SqrBoxFilter);
    }

    NAN_METHOD(BilateralFilter) {
      NotImplemented(info);
    }

    NAN_METHOD(Blur) {
      NotImplemented(info);
    }

    NAN_METHOD(BoxFilter) {
      NotImplemented(info);
    }

    NAN_METHOD(BuildPyramid) {
      NotImplemented(info);
    }

    NAN_METHOD(Dilate) {
      NotImplemented(info);
    }

    NAN_METHOD(Erode) {
      NotImplemented(info);
    }

    NAN_METHOD(Filter2D) {
      NotImplemented(info);
    }

    NAN_METHOD(GaussianBlur) {
      NotImplemented(info);
    }

    NAN_METHOD(GetDerivKernels) {
      NotImplemented(info);
    }

    NAN_METHOD(GetGaborKernel) {
      NotImplemented(info);
    }

    NAN_METHOD(GetGaussianKernel) {
      NotImplemented(info);
    }

    NAN_METHOD(GetStructuringElement) {
      NotImplemented(info);
    }

    NAN_METHOD(Laplacian) {
      NotImplemented(info);
    }

    NAN_METHOD(MedianBlur) {
      NotImplemented(info);
    }

    NAN_METHOD(MorphologyDefaultBorderValue) {
      NotImplemented(info);
    }

    NAN_METHOD(MorphologyEx) {
      NotImplemented(info);
    }

    NAN_METHOD(PyrDown) {
      NotImplemented(info);
    }

    NAN_METHOD(PyrMeanShiftFiltering) {
      NotImplemented(info);
    }

    NAN_METHOD(PyrUp) {
      NotImplemented(info);
    }

    NAN_METHOD(Scharr) {
      NotImplemented(info);
    }

    NAN_METHOD(SepFilter2D) {
      NotImplemented(info);
    }

    NAN_METHOD(Sobel) {
      NotImplemented(info);
    }

    NAN_METHOD(SpatialGradient) {
      NotImplemented(info);
    }

    NAN_METHOD(SqrBoxFilter) {
      NotImplemented(info);
    }

  }

}
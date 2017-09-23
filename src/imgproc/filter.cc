#include "filter.h"
#include "../core/Size.h"
#include "../core/Point.h"
#include "../core/Scalar.h"

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
      Nan::SetMethod(target, "gaussianBlur", GaussianBlur);
      Nan::SetMethod(target, "getDerivKernels", GetDerivKernels);
      Nan::SetMethod(target, "getGaborKernel", GetGaborKernel);
      Nan::SetMethod(target, "getGaussianKernel", GetGaussianKernel);
      Nan::SetMethod(target, "getStructuringElement", GetStructuringElement);
      Nan::SetMethod(target, "laplacian", Laplacian);
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
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(5, 6);
      Nan::HandleScope scope;
      ASSERT_INPUTARRAY_FROM_ARGS(src, 0);
      ASSERT_OUTPUTARRAY_FROM_ARGS(dst, 1);
      ASSERT_INT_FROM_ARGS(d, 2);
      ASSERT_DOUBLE_FROM_ARGS(sigmaColor, 3);
      DEFAULT_DOUBLE_FROM_ARGS(sigmaSpace, 4, 0);
      DEFAULT_INT_FROM_ARGS(borderType, 5, cv::BORDER_DEFAULT);
      TRY_CATCH_THROW_OPENCV(cv::bilateralFilter(src, dst, d, sigmaColor, sigmaSpace, borderType));
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
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(3, 7);
      ASSERT_INPUTARRAY_FROM_ARGS(src, 0);
      ASSERT_OUTPUTARRAY_FROM_ARGS(dst, 1);
      ASSERT_INPUTARRAY_FROM_ARGS(kernel, 2);
      DEFAULT_POINT_FROM_ARGS(anchor, 3, cv::Point(-1, -1));
      DEFAULT_INT_FROM_ARGS(iterations, 4, 1);
      DEFAULT_INT_FROM_ARGS(borderType, 5, cv::BORDER_DEFAULT);
      DEFAULT_SCALAR_FROM_ARGS(borderValue, 5, cv::morphologyDefaultBorderValue());
      TRY_CATCH_THROW_OPENCV(cv::dilate(src, dst, kernel, anchor, iterations, borderType, borderValue));
    }

    NAN_METHOD(Erode) {
      NotImplemented(info);
    }

    NAN_METHOD(Filter2D) {
      NotImplemented(info);
    }

    NAN_METHOD(GaussianBlur) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(4, 6);
      Nan::HandleScope scope;
      ASSERT_INPUTARRAY_FROM_ARGS(src, 0);
      ASSERT_OUTPUTARRAY_FROM_ARGS(dst, 1);
      ASSERT_SIZE_FROM_ARGS(ksize, 2);
      ASSERT_DOUBLE_FROM_ARGS(sigmaX, 3);
      DEFAULT_DOUBLE_FROM_ARGS(sigmaY, 4, 0);
      DEFAULT_INT_FROM_ARGS(borderType, 5, cv::BORDER_DEFAULT);
      TRY_CATCH_THROW_OPENCV(cv::GaussianBlur(src, dst, ksize, sigmaX, sigmaX, borderType));
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

#include "filter.h"
#include "../core/Size.h"
#include "../core/Point.h"
#include "../core/Scalar.h"
#include "../core/Matrix.h"

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
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(3, 5);
      ASSERT_INPUTARRAY_FROM_ARGS(src, 0);
      ASSERT_OUTPUTARRAY_FROM_ARGS(dst, 1);
      ASSERT_SIZE_FROM_ARGS(ksize, 2);
      DEFAULT_POINT_FROM_ARGS(anchor, 3, cv::Point(-1, -1));
      DEFAULT_INT_FROM_ARGS(borderType, 4, cv::BORDER_DEFAULT);
      TRY_CATCH_THROW_OPENCV(cv::blur(src, dst, ksize, anchor, borderType));
    }

    NAN_METHOD(BoxFilter) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(4, 7);
      ASSERT_INPUTARRAY_FROM_ARGS(src, 0);
      ASSERT_OUTPUTARRAY_FROM_ARGS(dst, 1);
      ASSERT_INT_FROM_ARGS(ddepth, 2);
      ASSERT_SIZE_FROM_ARGS(ksize, 3);
      DEFAULT_POINT_FROM_ARGS(anchor, 4, cv::Point(-1, -1));
      DEFAULT_BOOLEAN_FROM_ARGS(normalize, 5, true);
      DEFAULT_INT_FROM_ARGS(borderType, 6, cv::BORDER_DEFAULT);
      TRY_CATCH_THROW_OPENCV(cv::boxFilter(src, dst, ddepth, ksize, anchor, normalize, borderType));
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
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(3, 7);
      ASSERT_INPUTARRAY_FROM_ARGS(src, 0);
      ASSERT_OUTPUTARRAY_FROM_ARGS(dst, 1);
      ASSERT_INPUTARRAY_FROM_ARGS(kernel, 2);
      DEFAULT_POINT_FROM_ARGS(anchor, 3, cv::Point(-1, -1));
      DEFAULT_INT_FROM_ARGS(iterations, 4, 1);
      DEFAULT_INT_FROM_ARGS(borderType, 5, cv::BORDER_CONSTANT);
      DEFAULT_SCALAR_FROM_ARGS(borderValue, 6, cv::morphologyDefaultBorderValue());
      TRY_CATCH_THROW_OPENCV(cv::erode(src, dst, kernel, anchor, iterations, borderType, borderValue));
    }

    NAN_METHOD(Filter2D) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(4, 7);
      ASSERT_INPUTARRAY_FROM_ARGS(src, 0);
      ASSERT_OUTPUTARRAY_FROM_ARGS(dst, 1);
      ASSERT_INT_FROM_ARGS(ddepth, 2);
      ASSERT_INPUTARRAY_FROM_ARGS(kernel, 3);
      DEFAULT_POINT_FROM_ARGS(anchor, 4, cv::Point(-1, -1));
      DEFAULT_DOUBLE_FROM_ARGS(delta, 5, 0);
      DEFAULT_INT_FROM_ARGS(borderType, 6, cv::BORDER_DEFAULT);
      TRY_CATCH_THROW_OPENCV(cv::filter2D(src, dst, ddepth, kernel, anchor, delta, borderType));
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
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(5, 7);
      ASSERT_OUTPUTARRAY_FROM_ARGS(kx, 0);
      ASSERT_OUTPUTARRAY_FROM_ARGS(ky, 1);
      ASSERT_INT_FROM_ARGS(dx, 2);
      ASSERT_INT_FROM_ARGS(dy, 3);
      ASSERT_INT_FROM_ARGS(ksize, 4);
      DEFAULT_BOOLEAN_FROM_ARGS(normalize, 5, false);
      DEFAULT_INT_FROM_ARGS(ktype, 6, CV_32F);
      TRY_CATCH_THROW_OPENCV(cv::getDerivKernels(kx, ky, dx, dy, ksize, normalize, ktype));
    }

    NAN_METHOD(GetGaborKernel) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(5, 7);
      ASSERT_SIZE_FROM_ARGS(ksize, 0);
      ASSERT_DOUBLE_FROM_ARGS(sigma, 1);
      ASSERT_DOUBLE_FROM_ARGS(theta, 2);
      ASSERT_DOUBLE_FROM_ARGS(lambd, 3);
      ASSERT_DOUBLE_FROM_ARGS(gamma, 4);
      DEFAULT_DOUBLE_FROM_ARGS(psi, 5, CV_PI*0.5);
      DEFAULT_INT_FROM_ARGS(ktype, 6, CV_64F);
      TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Matrix::NewInstance(cv::getGaborKernel(ksize, sigma, theta, lambd, gamma, psi, ktype))));
    }

    NAN_METHOD(GetGaussianKernel) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(2, 3);
      ASSERT_INT_FROM_ARGS(ksize, 0);
      ASSERT_DOUBLE_FROM_ARGS(sigma, 1);
      DEFAULT_INT_FROM_ARGS(ktype, 2, CV_64F);
      TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Matrix::NewInstance(cv::getGaussianKernel(ksize, sigma, ktype))));
    }

    NAN_METHOD(GetStructuringElement) {
      NotImplemented(info);
    }

    NAN_METHOD(Laplacian) {
      NotImplemented(info);
    }

    NAN_METHOD(MedianBlur) {
      FUNCTION_REQUIRE_ARGUMENTS(3);
      ASSERT_INPUTARRAY_FROM_ARGS(src, 0);
      ASSERT_OUTPUTARRAY_FROM_ARGS(dst, 1);
      ASSERT_INT_FROM_ARGS(ksize, 2);
      TRY_CATCH_THROW_OPENCV(cv::medianBlur(src, dst, ksize));
    }

    NAN_METHOD(MorphologyDefaultBorderValue) {
      NotImplemented(info);
    }

    NAN_METHOD(MorphologyEx) {
		FUNCTION_REQUIRE_ARGUMENTS_RANGE(4, 8);
		ASSERT_INPUTARRAY_FROM_ARGS(src, 0);
		ASSERT_OUTPUTARRAY_FROM_ARGS(dst, 1);
		ASSERT_INT_FROM_ARGS(op, 2);
		ASSERT_INPUTARRAY_FROM_ARGS(kernel, 3);
		DEFAULT_POINT_FROM_ARGS(anchor, 4, cv::Point(-1, -1));
		DEFAULT_INT_FROM_ARGS(iterations, 5, 1);
		DEFAULT_INT_FROM_ARGS(borderType, 6, cv::BORDER_CONSTANT);
		DEFAULT_SCALAR_FROM_ARGS(borderValue, 7, cv::morphologyDefaultBorderValue());
		TRY_CATCH_THROW_OPENCV(cv::morphologyEx(src, dst, op, kernel, anchor, iterations, borderType, borderValue));
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

#include "transform.h"
#include "../common/Size.h"

namespace ncv {

  namespace imgproc {

    NAN_METHOD(ConvertMaps) {
      NotImplemented
    }

    NAN_METHOD(GetAffineTransform) {
      NotImplemented
    }

    NAN_METHOD(GetDefaultNewCameraMatrix) {
      NotImplemented
    }

    NAN_METHOD(GetPerspectiveTransform) {
      NotImplemented
    }

    NAN_METHOD(GetRectSubPix) {
      NotImplemented
    }

    NAN_METHOD(GetRotationMatrix2D) {
      NotImplemented
    }

    NAN_METHOD(InitUndistortRectifyMap) {
      NotImplemented
    }

    NAN_METHOD(InitWideAngleProjMap) {
      NotImplemented
    }

    NAN_METHOD(InvertAffineTransform) {
      NotImplemented
    }

    NAN_METHOD(LinearPolar) {
      NotImplemented
    }

    NAN_METHOD(LogPolar) {
      NotImplemented
    }

    NAN_METHOD(Remap) {
      NotImplemented
    }

    NAN_METHOD(Resize) {
      ASSERT_INPUTARRAY_FROM_ARGS(image, 0);
      ASSERT_OUTPUTARRAY_FROM_ARGS(dst, 1);
      ASSERT_SIZE_FROM_ARGS(dsize, 2);
      DEFAULT_DOUBLE_FROM_ARGS(fx, 3, 0);
      DEFAULT_DOUBLE_FROM_ARGS(fy, 4, 0);
      DEFAULT_INT_FROM_ARGS(interpolation, 5, cv::INTER_LINEAR);
      TRY_CATCH_THROW_OPENCV(cv::resize(image, dst, dsize, fx, fy, interpolation));
    }

    NAN_METHOD(Undistort) {
      NotImplemented
    }

    NAN_METHOD(UndistortPoints) {
      NotImplemented
    }

    NAN_METHOD(WarpAffine) {
      NotImplemented
    }

    NAN_METHOD(WarpPerspective) {
      NotImplemented
    }

    void TransformInit(Local<Object> &target) {

      // interpolation flags
      DEFINE_CONST_ENUM(INTER_NEAREST);
      DEFINE_CONST_ENUM(INTER_LINEAR);
      DEFINE_CONST_ENUM(INTER_CUBIC);
      DEFINE_CONST_ENUM(INTER_AREA);
      DEFINE_CONST_ENUM(INTER_LANCZOS4);
      DEFINE_CONST_ENUM(INTER_MAX);
      DEFINE_CONST_ENUM(WARP_FILL_OUTLIERS);
      DEFINE_CONST_ENUM(WARP_INVERSE_MAP);

      // interpolation masks
      DEFINE_CONST_ENUM(INTER_BITS);
      DEFINE_CONST_ENUM(INTER_BITS2);
      DEFINE_CONST_ENUM(INTER_TAB_SIZE);
      DEFINE_CONST_ENUM(INTER_TAB_SIZE2);

      Nan::SetMethod(target, "convertMaps", ConvertMaps);
      Nan::SetMethod(target, "getAffineTransform", GetAffineTransform);
      Nan::SetMethod(target, "getDefaultNewCameraMatrix", GetDefaultNewCameraMatrix);
      Nan::SetMethod(target, "getPerspectiveTransform", GetPerspectiveTransform);
      Nan::SetMethod(target, "getRectSubPix", GetRectSubPix);
      Nan::SetMethod(target, "getRotationMatrix2D", GetRotationMatrix2D);
      Nan::SetMethod(target, "initUndistortRectifyMap", InitUndistortRectifyMap);
      Nan::SetMethod(target, "initWideAngleProjMap", InitWideAngleProjMap);
      Nan::SetMethod(target, "invertAffineTransform", InvertAffineTransform);
      Nan::SetMethod(target, "linearPolar", LinearPolar);
      Nan::SetMethod(target, "logPolar", LogPolar);
      Nan::SetMethod(target, "remap", Remap);
      Nan::SetMethod(target, "resize", Resize);
      Nan::SetMethod(target, "undistort", Undistort);
      Nan::SetMethod(target, "undistortPoints", UndistortPoints);
      Nan::SetMethod(target, "warpAffine", WarpAffine);
      Nan::SetMethod(target, "warpPerspective", WarpPerspective);

    }

  }

}

#include "transform.h"

namespace ncv {

  namespace imgproc {

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

    NAN_METHOD(ConvertMaps) {
      NotImplemented(info);
    }

    NAN_METHOD(GetAffineTransform) {
      NotImplemented(info);
    }

    NAN_METHOD(GetDefaultNewCameraMatrix) {
      NotImplemented(info);
    }

    NAN_METHOD(GetPerspectiveTransform) {
      NotImplemented(info);
    }

    NAN_METHOD(GetRectSubPix) {
      NotImplemented(info);
    }

    NAN_METHOD(GetRotationMatrix2D) {
      NotImplemented(info);
    }

    NAN_METHOD(InitUndistortRectifyMap) {
      NotImplemented(info);
    }

    NAN_METHOD(InitWideAngleProjMap) {
      NotImplemented(info);
    }

    NAN_METHOD(InvertAffineTransform) {
      NotImplemented(info);
    }

    NAN_METHOD(LinearPolar) {
      NotImplemented(info);
    }

    NAN_METHOD(LogPolar) {
      NotImplemented(info);
    }

    NAN_METHOD(Remap) {
      NotImplemented(info);
    }

    NAN_METHOD(Resize) {
      NotImplemented(info);
    }

    NAN_METHOD(Undistort) {
      NotImplemented(info);
    }

    NAN_METHOD(UndistortPoints) {
      NotImplemented(info);
    }

    NAN_METHOD(WarpAffine) {
      NotImplemented(info);
    }

    NAN_METHOD(WarpPerspective) {
      NotImplemented(info);
    }

  }

}

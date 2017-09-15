#ifndef __IMGPROC__TRANSFORM_H__
#define __IMGPROC__TRANSFORM_H__

#include "common.h"

namespace ncv {

  namespace imgproc {

    void TransformInit(Local<Object> &target);

    NAN_METHOD(ConvertMaps);
    NAN_METHOD(GetAffineTransform);
    NAN_METHOD(GetDefaultNewCameraMatrix);
    NAN_METHOD(GetPerspectiveTransform);
    NAN_METHOD(GetRectSubPix);
    NAN_METHOD(GetRotationMatrix2D);
    NAN_METHOD(InitUndistortRectifyMap);
    NAN_METHOD(InitWideAngleProjMap);
    NAN_METHOD(InvertAffineTransform);
    NAN_METHOD(LinearPolar);
    NAN_METHOD(LogPolar);
    NAN_METHOD(Remap);
    NAN_METHOD(Resize);
    NAN_METHOD(Undistort);
    NAN_METHOD(UndistortPoints);
    NAN_METHOD(WarpAffine);
    NAN_METHOD(WarpPerspective);

  }

}

#endif // __IMGPROC__TRANSFORM_H__

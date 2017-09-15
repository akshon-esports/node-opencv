#ifndef __IMGPROC__MISC_H__
#define __IMGPROC__MISC_H__

#include "common.h"

namespace ncv {

  namespace imgproc {

    void MiscInit(Local<Object> &target);

    NAN_METHOD(AdaptiveThreshold);
    NAN_METHOD(CvtColor);
    NAN_METHOD(DistanceTransform);
    NAN_METHOD(FloodFill);
    NAN_METHOD(GrabCut);
    NAN_METHOD(Integral);
    NAN_METHOD(Threshold);
    NAN_METHOD(Watershed);

  }

}

#endif // __IMGPROC__MISC_H__

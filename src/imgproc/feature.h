#ifndef __IMGPROC__FEATURE_H__
#define __IMGPROC__FEATURE_H__

#include "common.h"

namespace ncv {

  namespace imgproc {

    void FeatureInit(Local<Object> &target);

    NAN_METHOD(Canny);
    NAN_METHOD(CornerEigenValsAndVecs);
    NAN_METHOD(CornerHarris);
    NAN_METHOD(CornerMinEigenVal);
    NAN_METHOD(CornerSubPix);
    NAN_METHOD(CreateLineSegmentDetector);
    NAN_METHOD(GoodFeaturesToTrack);
    NAN_METHOD(HoughCircles);
    NAN_METHOD(HoughLines);
    NAN_METHOD(HoughLinesP);
    NAN_METHOD(PreCornerDetect);

  }

}

#endif // __IMGPROC__FEATURE_H__

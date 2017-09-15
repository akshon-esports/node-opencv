#ifndef __IMGPROC__FILTER_H__
#define __IMGPROC__FILTER_H__

#include "common.h"

namespace ncv {

  namespace imgproc {

    void FilterInit(Local<Object> &target);

    NAN_METHOD(BilateralFilter);
    NAN_METHOD(Blur);
    NAN_METHOD(BoxFilter);
    NAN_METHOD(BuildPyramid);
    NAN_METHOD(Dilate);
    NAN_METHOD(Erode);
    NAN_METHOD(Filter2D);
    NAN_METHOD(GaussianBlur);
    NAN_METHOD(GetDerivKernels);
    NAN_METHOD(GetGaborKernel);
    NAN_METHOD(GetGaussianKernel);
    NAN_METHOD(GetStructuringElement);
    NAN_METHOD(Laplacian);
    NAN_METHOD(MedianBlur);
    NAN_METHOD(MorphologyDefaultBorderValue);
    NAN_METHOD(MorphologyEx);
    NAN_METHOD(PyrDown);
    NAN_METHOD(PyrMeanShiftFiltering);
    NAN_METHOD(PyrUp);
    NAN_METHOD(Scharr);
    NAN_METHOD(SepFilter2D);
    NAN_METHOD(Sobel);
    NAN_METHOD(SpatialGradient);
    NAN_METHOD(SqrBoxFilter);

  }

}

#endif // __IMGPROC__FILTER_H__

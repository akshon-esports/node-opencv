#ifndef __IMGPROC__SHAPE_H__
#define __IMGPROC__SHAPE_H__

#include "common.h"

namespace ncv {

  namespace imgproc {

    void ShapeInit(Local<Object> &target);

    NAN_METHOD(ApproxPolyDP);
    NAN_METHOD(ArcLength);
    NAN_METHOD(BoundingRect);
    NAN_METHOD(BoxPoints);
    NAN_METHOD(ConnectedComponents);
    NAN_METHOD(ConnectedComponentsWithStats);
    NAN_METHOD(ContourArea);
    NAN_METHOD(ConvexHull);
    NAN_METHOD(ConvexityDefects);
    NAN_METHOD(FindContours);
    NAN_METHOD(FitEllipse);
    NAN_METHOD(FitLine);
    NAN_METHOD(HuMoments);
    NAN_METHOD(IntersectConvexConvex);
    NAN_METHOD(IsContourConvex);
    NAN_METHOD(MatchShapes);
    NAN_METHOD(MinAreaRect);
    NAN_METHOD(MinEnclosingCircle);
    NAN_METHOD(MinEnclosingTriangle);
    NAN_METHOD(Moments);
    NAN_METHOD(PointPolygonTest);
    NAN_METHOD(RotatedRectangleIntersection);

  }

}

#endif // __IMGPROC__SHAPE_H__

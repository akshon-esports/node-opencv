#include "shape.h"
#include "../core/Point.h"
#include "Contours.h"

namespace ncv {

  namespace imgproc {

    void ShapeInit(Local<Object> &target) {
      // connected components algorithms types
      DEFINE_CONST_ENUM(CCL_WU);
      DEFINE_CONST_ENUM(CCL_DEFAULT);
      DEFINE_CONST_ENUM(CCL_GRANA);

      // connected components types
      DEFINE_CONST_ENUM(CC_STAT_LEFT);
      DEFINE_CONST_ENUM(CC_STAT_TOP);
      DEFINE_CONST_ENUM(CC_STAT_WIDTH);
      DEFINE_CONST_ENUM(CC_STAT_HEIGHT);
      DEFINE_CONST_ENUM(CC_STAT_AREA);
      DEFINE_CONST_ENUM(CC_STAT_MAX);

      // contour approximation modes
      DEFINE_CONST_ENUM(CHAIN_APPROX_NONE);
      DEFINE_CONST_ENUM(CHAIN_APPROX_SIMPLE);
      DEFINE_CONST_ENUM(CHAIN_APPROX_TC89_L1);
      DEFINE_CONST_ENUM(CHAIN_APPROX_TC89_KCOS);

      // rectangles intersect types
      DEFINE_CONST_ENUM(INTERSECT_NONE);
      DEFINE_CONST_ENUM(INTERSECT_PARTIAL);
      DEFINE_CONST_ENUM(INTERSECT_FULL);

      // retrieval modes
      DEFINE_CONST_ENUM(RETR_EXTERNAL);
      DEFINE_CONST_ENUM(RETR_LIST);
      DEFINE_CONST_ENUM(RETR_CCOMP);
      DEFINE_CONST_ENUM(RETR_TREE);
      DEFINE_CONST_ENUM(RETR_FLOODFILL);

      // shape match modes
      DEFINE_CONST_ENUM(CONTOURS_MATCH_I1);
      DEFINE_CONST_ENUM(CONTOURS_MATCH_I2);
      DEFINE_CONST_ENUM(CONTOURS_MATCH_I3);

      Nan::SetMethod(target, "approxPolyDP", ApproxPolyDP);
      Nan::SetMethod(target, "arcLength", ArcLength);
      Nan::SetMethod(target, "boundingRect", BoundingRect);
      Nan::SetMethod(target, "boxPoints", BoxPoints);
      Nan::SetMethod(target, "connectedComponents", ConnectedComponents);
      Nan::SetMethod(target, "connectedComponentsWithStats", ConnectedComponentsWithStats);
      Nan::SetMethod(target, "contourArea", ContourArea);
      Nan::SetMethod(target, "convexHull", ConvexHull);
      Nan::SetMethod(target, "convexityDefects", ConvexityDefects);
      Nan::SetMethod(target, "findContours", FindContours);
      Nan::SetMethod(target, "fitEllipse", FitEllipse);
      Nan::SetMethod(target, "fitLine", FitLine);
      Nan::SetMethod(target, "huMoments", HuMoments);
      Nan::SetMethod(target, "intersectConvexConvex", IntersectConvexConvex);
      Nan::SetMethod(target, "isContourConvex", IsContourConvex);
      Nan::SetMethod(target, "matchShapes", MatchShapes);
      Nan::SetMethod(target, "minAreaRect", MinAreaRect);
      Nan::SetMethod(target, "minEnclosingCircle", MinEnclosingCircle);
      Nan::SetMethod(target, "minEnclosingTriangle", MinEnclosingTriangle);
      Nan::SetMethod(target, "moments", Moments);
      Nan::SetMethod(target, "pointPolygonTest", PointPolygonTest);
      Nan::SetMethod(target, "rotatedRectangleIntersection", RotatedRectangleIntersection);
    }

    NAN_METHOD(ApproxPolyDP) {
      NotImplemented(info);
    }

    NAN_METHOD(ArcLength) {
      NotImplemented(info);
    }

    NAN_METHOD(BoundingRect) {
      NotImplemented(info);
    }

    NAN_METHOD(BoxPoints) {
      NotImplemented(info);
    }

    NAN_METHOD(ConnectedComponents) {
      NotImplemented(info);
    }

    NAN_METHOD(ConnectedComponentsWithStats) {
      NotImplemented(info);
    }

    NAN_METHOD(ContourArea) {
      NotImplemented(info);
    }

    NAN_METHOD(ConvexHull) {
      NotImplemented(info);
    }

    NAN_METHOD(ConvexityDefects) {
      NotImplemented(info);
    }

    NAN_METHOD(FindContours) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(3, 4);
      Nan::HandleScope scope;
      ASSERT_INPUTOUTPUTARRAY_FROM_ARGS(image, 0);
      ASSERT_INT_FROM_ARGS(mode, 1);
      ASSERT_INT_FROM_ARGS(method, 2);
      DEFAULT_POINT_FROM_ARGS(offset, 2, cv::Point());

      Local<Object> out = Contours::NewInstance();
      Contours* contours = UNWRAP_OBJECT(Contours, out);
      TRY_CATCH_THROW_OPENCV(cv::findContours(image, contours->contours, contours->hierarchy, mode, method, offset));

      info.GetReturnValue().Set(out);
    }

    NAN_METHOD(FitEllipse) {
      NotImplemented(info);
    }

    NAN_METHOD(FitLine) {
      NotImplemented(info);
    }

    NAN_METHOD(HuMoments) {
      NotImplemented(info);
    }

    NAN_METHOD(IntersectConvexConvex) {
      NotImplemented(info);
    }

    NAN_METHOD(IsContourConvex) {
      NotImplemented(info);
    }

    NAN_METHOD(MatchShapes) {
      NotImplemented(info);
    }

    NAN_METHOD(MinAreaRect) {
      NotImplemented(info);
    }

    NAN_METHOD(MinEnclosingCircle) {
      NotImplemented(info);
    }

    NAN_METHOD(MinEnclosingTriangle) {
      NotImplemented(info);
    }

    NAN_METHOD(Moments) {
      NotImplemented(info);
    }

    NAN_METHOD(PointPolygonTest) {
      NotImplemented(info);
    }

    NAN_METHOD(RotatedRectangleIntersection) {
      NotImplemented(info);
    }

  }

}

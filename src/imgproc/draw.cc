#include "draw.h"
#include "../core/Point.h"
#include "../core/Rect.h"
#include "../core/Scalar.h"

namespace ncv {

  namespace imgproc {

    void DrawInit(Local<Object> &target) {
      // marker types
      DEFINE_CONST_ENUM(MARKER_CROSS);
      DEFINE_CONST_ENUM(MARKER_TILTED_CROSS);
      DEFINE_CONST_ENUM(MARKER_STAR);
      DEFINE_CONST_ENUM(MARKER_DIAMOND);
      DEFINE_CONST_ENUM(MARKER_SQUARE);
      DEFINE_CONST_ENUM(MARKER_TRIANGLE_UP);
      DEFINE_CONST_ENUM(MARKER_TRIANGLE_DOWN);

      Nan::SetMethod(target, "arrowedLine", ArrowedLine);
      Nan::SetMethod(target, "circle", Circle);
      Nan::SetMethod(target, "clipLine", ClipLine);
      Nan::SetMethod(target, "drawContours", DrawContours);
      Nan::SetMethod(target, "drawMarker", DrawMarker);
      Nan::SetMethod(target, "ellipse", Ellipse);
      Nan::SetMethod(target, "ellipse2Poly", Ellipse2Poly);
      Nan::SetMethod(target, "fillConvexPoly", FillConvexPoly);
      Nan::SetMethod(target, "fillPoly", FillPoly);
      Nan::SetMethod(target, "getTextSize", GetTextSize);
      Nan::SetMethod(target, "line", Line);
      Nan::SetMethod(target, "polylines", Polylines);
      Nan::SetMethod(target, "putText", PutText);
      Nan::SetMethod(target, "rectangle", Rectangle);
    }

    NAN_METHOD(ArrowedLine) {
      NotImplemented(info);
    }

    NAN_METHOD(Circle) {
      NotImplemented(info);
    }

    NAN_METHOD(ClipLine) {
      NotImplemented(info);
    }

    NAN_METHOD(DrawContours) {
      NotImplemented(info);
    }

    NAN_METHOD(DrawMarker) {
      NotImplemented(info);
    }

    NAN_METHOD(Ellipse) {
      NotImplemented(info);
    }

    NAN_METHOD(Ellipse2Poly) {
      NotImplemented(info);
    }

    NAN_METHOD(FillConvexPoly) {
      NotImplemented(info);
    }

    NAN_METHOD(FillPoly) {
      NotImplemented(info);
    }

    NAN_METHOD(GetTextSize) {
      NotImplemented(info);
    }

    NAN_METHOD(Line) {
      NotImplemented(info);
    }

    NAN_METHOD(Polylines) {
      NotImplemented(info);
    }

    NAN_METHOD(PutText) {
      NotImplemented(info);
    }

    NAN_METHOD(Rectangle) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(2, 6);
      Nan::HandleScope scope;
      unsigned argumentOffset = 0;
      ASSERT_INPUTOUTPUTARRAY_FROM_ARGS(img, 0);

      Local<Value> v1 = info[1];
      cv::Point p1, p2;
      try {
        cv::Rect r = Rect::RawRect(1, &v1);
        p1 = r.tl();
        p2 = r.br();
      } catch (char const*) {
        try {
          Local<Value> v2 = info[2];
          p1 = Point::RawPoint(1, &v1);
          p2 = Point::RawPoint(1, &v2);
          argumentOffset = 1;
        } catch (char const*) {
          return Nan::ThrowError(ERROR_INVALID_ARGUMENTS);
        }
      }

      ASSERT_SCALAR_FROM_ARGS(color, 2 + argumentOffset);
      DEFAULT_INT_FROM_ARGS(thickness, 3 + argumentOffset, 0);
      DEFAULT_INT_FROM_ARGS(lineType, 4 + argumentOffset, cv::LINE_8);
      DEFAULT_INT_FROM_ARGS(shift, 5 + argumentOffset, 0);

      TRY_CATCH_THROW_OPENCV(cv::rectangle(img, p1, p2, color, thickness, lineType, shift));
    }

  }

}

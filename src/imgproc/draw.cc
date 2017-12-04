#include "draw.h"

#include "Contours.h"

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
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(4, 8);
      ASSERT_INPUTOUTPUTARRAY_FROM_ARGS(img, 0);
      ASSERT_POINT_FROM_ARGS(pt1, 1);
      ASSERT_POINT_FROM_ARGS(pt2, 2);
      ASSERT_SCALAR_FROM_ARGS(color, 3);
      DEFAULT_INT_FROM_ARGS(thickness, 4, 1);
      DEFAULT_INT_FROM_ARGS(lineType, 5, cv::LINE_8);
      DEFAULT_INT_FROM_ARGS(shift, 6, 0);
      DEFAULT_DOUBLE_FROM_ARGS(tipLength, 6, 0);
      TRY_CATCH_THROW_OPENCV(cv::arrowedLine(img, pt1, pt2, color, thickness, lineType, tipLength));
    }

    NAN_METHOD(Circle) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(4, 7);
      ASSERT_INPUTOUTPUTARRAY_FROM_ARGS(img, 0);
      ASSERT_POINT_FROM_ARGS(center, 1);
      ASSERT_INT_FROM_ARGS(radius, 2);
      ASSERT_SCALAR_FROM_ARGS(color, 3);
      DEFAULT_INT_FROM_ARGS(thickness, 4, 1);
      DEFAULT_INT_FROM_ARGS(lineType, 5, cv::LINE_8);
      DEFAULT_INT_FROM_ARGS(shift, 6, 0);
      TRY_CATCH_THROW_OPENCV(cv::circle(img, center, radius, color, thickness, lineType, shift));
    }

    NAN_METHOD(ClipLine) {
      FUNCTION_REQUIRE_ARGUMENTS(3);
      ASSERT_POINT_FROM_ARGS(pt1, 1);
      ASSERT_POINT_FROM_ARGS(pt2, 2);
      Local<Value> val = info[0];
      TRY_CATCH_THROW_OPENCV(
        try {
          info.GetReturnValue().Set(Nan::New<Boolean>(cv::clipLine(Size::RawSize(1, &val), pt1, pt2)));
        } catch (char const*) {
          try {
            info.GetReturnValue().Set(Nan::New<Boolean>(cv::clipLine(Rect::RawRect(1, &val), pt1, pt2)));
          } catch (char const*) {
            return Nan::ThrowError(ERROR_INVALID_ARGUMENTS);
          }
        }
      );
    }

    NAN_METHOD(DrawContours) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(4, 8);
      Nan::HandleScope scope;
      ASSERT_INPUTOUTPUTARRAY_FROM_ARGS(img, 0);
      ASSERT_CONTOURS_FROM_ARGS(contours, 1);
      ASSERT_INT_FROM_ARGS(idx, 2);
      ASSERT_SCALAR_FROM_ARGS(color, 3);
      DEFAULT_INT_FROM_ARGS(thickness, 4, 1);
      DEFAULT_INT_FROM_ARGS(lineType, 5, cv::LINE_8);
      DEFAULT_INT_FROM_ARGS(maxLevel, 6, INT_MAX);
      DEFAULT_POINT_FROM_ARGS(offset, 7, cv::Point());
      TRY_CATCH_THROW_OPENCV(cv::drawContours(img, contours->contours, idx, color, thickness, lineType, contours->hierarchy, maxLevel, offset));
    }

    NAN_METHOD(DrawMarker) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(3, 7);
      ASSERT_MATRIX_FROM_ARGS(img, 0);
      ASSERT_POINT_FROM_ARGS(position, 1);
      ASSERT_SCALAR_FROM_ARGS(color, 2);
      DEFAULT_INT_FROM_ARGS(markerType, 3, cv::MARKER_CROSS);
      DEFAULT_INT_FROM_ARGS(markerSize, 4, 20);
      DEFAULT_INT_FROM_ARGS(thickness, 5, 1);
      DEFAULT_INT_FROM_ARGS(lineType, 6, cv::LINE_8);
      TRY_CATCH_THROW_OPENCV(cv::drawMarker(img->mat, position, color, markerType, markerSize, thickness, lineType));
    }

    NAN_METHOD(Ellipse) {
      NotImplemented
    }

    NAN_METHOD(Ellipse2Poly) {
      FUNCTION_REQUIRE_ARGUMENTS(6);
      ASSERT_POINT_FROM_ARGS(center, 0);
      ASSERT_SIZE_FROM_ARGS(axes, 1);
      ASSERT_INT_FROM_ARGS(angle, 2);
      ASSERT_INT_FROM_ARGS(arcStart, 3);
      ASSERT_INT_FROM_ARGS(arcEnd, 4);
      ASSERT_INT_FROM_ARGS(delta, 5);
      std::vector<cv::Point> pts;
      TRY_CATCH_THROW_OPENCV(cv::ellipse2Poly(center, axes, angle, arcStart, arcEnd, delta, pts));

      Local<Array> out = Nan::New<Array>();
      int i = 0;
      for (cv::Point pt : pts) {
        Nan::Set(out, i, Point::NewInstance(pt));
        ++i;
      }

      info.GetReturnValue().Set(out);
    }

    NAN_METHOD(FillConvexPoly) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(3, 5);
      ASSERT_INPUTOUTPUTARRAY_FROM_ARGS(img, 0);
      ASSERT_ARRAY_FROM_ARGS(ptsArr, 1);
      std::vector<cv::Point> pts;
      for (unsigned i = 0; i < ptsArr->Length(); ++i) {
        try {
          Local<Value> val = Nan::Get(ptsArr, i).ToLocalChecked();
          pts.push_back(Point::RawPoint(1, &val));
        } catch (char const*) {
          return Nan::ThrowError(ERROR_INVALID_ARGUMENTS);
        }
      }
      ASSERT_SCALAR_FROM_ARGS(color, 2);
      DEFAULT_INT_FROM_ARGS(lineType, 3, cv::LINE_8);
      DEFAULT_INT_FROM_ARGS(shift, 4, 0);
      TRY_CATCH_THROW_OPENCV(cv::fillConvexPoly(img, pts, color, lineType, shift));
    }

    NAN_METHOD(FillPoly) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(3, 6);
      ASSERT_INPUTOUTPUTARRAY_FROM_ARGS(img, 0);
      ASSERT_ARRAY_FROM_ARGS(ptsArr, 1);
      std::vector<cv::Point> pts;
      for (unsigned i = 0; i < ptsArr->Length(); ++i) {
        try {
          Local<Value> val = Nan::Get(ptsArr, i).ToLocalChecked();
          pts.push_back(Point::RawPoint(1, &val));
        } catch (char const*) {
          return Nan::ThrowError(ERROR_INVALID_ARGUMENTS);
        }
      }
      ASSERT_SCALAR_FROM_ARGS(color, 2);
      DEFAULT_INT_FROM_ARGS(lineType, 3, cv::LINE_8);
      DEFAULT_INT_FROM_ARGS(shift, 4, 0);
      DEFAULT_POINT_FROM_ARGS(offset, 4, cv::Point());
      TRY_CATCH_THROW_OPENCV(cv::fillPoly(img, pts, color, lineType, shift, offset));
    }

    NAN_METHOD(GetTextSize) {
      FUNCTION_REQUIRE_ARGUMENTS(4);
      ASSERT_STRING_FROM_ARGS(text, 0);
      ASSERT_INT_FROM_ARGS(fontFace, 1);
      ASSERT_DOUBLE_FROM_ARGS(fontScale, 2);
      ASSERT_INT_FROM_ARGS(thickness, 3);

      int baseline;
      Local<Value> size;
      TRY_CATCH_THROW_OPENCV(size = Size::NewInstance(cv::getTextSize(text, fontFace, fontScale, thickness, &baseline)));

      Local<Object> out = Nan::New<Object>();
      Nan::Set(out, Nan::New<String>("baseline").ToLocalChecked(), Nan::New<Integer>(baseline));
      Nan::Set(out, Nan::New<String>("size").ToLocalChecked(), size);

      info.GetReturnValue().Set(out);
    }

    NAN_METHOD(Line) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(4, 7);
      ASSERT_INPUTOUTPUTARRAY_FROM_ARGS(img, 0);
      ASSERT_POINT_FROM_ARGS(pt1, 1);
      ASSERT_POINT_FROM_ARGS(pt2, 2);
      ASSERT_SCALAR_FROM_ARGS(color, 3);
      DEFAULT_INT_FROM_ARGS(thickness, 4, 1);
      DEFAULT_INT_FROM_ARGS(lineType, 5, cv::LINE_8);
      DEFAULT_INT_FROM_ARGS(shift, 6, 0);
      TRY_CATCH_THROW_OPENCV(cv::line(img, pt1, pt2, color, thickness, lineType, shift));
    }

    NAN_METHOD(Polylines) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(4, 7);
      ASSERT_INPUTOUTPUTARRAY_FROM_ARGS(img, 0);
      ASSERT_ARRAY_FROM_ARGS(ptsArr, 1);
      std::vector<cv::Point> pts;
      for (unsigned i = 0; i < ptsArr->Length(); ++i) {
        try {
          Local<Value> val = Nan::Get(ptsArr, i).ToLocalChecked();
          pts.push_back(Point::RawPoint(1, &val));
        } catch (char const*) {
          return Nan::ThrowError(ERROR_INVALID_ARGUMENTS);
        }
      }
      ASSERT_BOOLEAN_FROM_ARGS(isClosed, 2);
      ASSERT_SCALAR_FROM_ARGS(color, 3);
      DEFAULT_INT_FROM_ARGS(thickness, 4, 1);
      DEFAULT_INT_FROM_ARGS(lineType, 5, cv::LINE_8);
      DEFAULT_INT_FROM_ARGS(shift, 6, 0);
      cv::polylines(img, pts, isClosed, color, thickness, lineType, shift);
    }

    NAN_METHOD(PutText) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(6, 9);
      ASSERT_INPUTOUTPUTARRAY_FROM_ARGS(img, 0);
      ASSERT_STRING_FROM_ARGS(text, 1);
      ASSERT_POINT_FROM_ARGS(origin, 2);
      ASSERT_INT_FROM_ARGS(fontFace, 3);
      ASSERT_DOUBLE_FROM_ARGS(fontScale, 4);
      ASSERT_SCALAR_FROM_ARGS(color, 5);
      DEFAULT_INT_FROM_ARGS(thickness, 6, 1);
      DEFAULT_INT_FROM_ARGS(lineType, 7, cv::LINE_8);
      DEFAULT_BOOLEAN_FROM_ARGS(bottomLeftOrigin, 8, false);
      TRY_CATCH_THROW_OPENCV(cv::putText(img, text, origin, fontFace, fontScale, color, thickness, lineType, bottomLeftOrigin));
    }

    NAN_METHOD(Rectangle) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(2, 6);
      Nan::HandleScope scope;
      int argumentOffset = 0;
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

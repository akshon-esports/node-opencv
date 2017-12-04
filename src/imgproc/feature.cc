#include "feature.h"

namespace ncv {

  namespace imgproc {

    void FeatureInit(Local<Object> &target) {
      // line segment detector modes
      DEFINE_CONST_ENUM(LSD_REFINE_NONE);
      DEFINE_CONST_ENUM(LSD_REFINE_STD);
      DEFINE_CONST_ENUM(LSD_REFINE_ADV);

      // hough modes
      DEFINE_CONST_ENUM(HOUGH_STANDARD);
      DEFINE_CONST_ENUM(HOUGH_PROBABILISTIC);
      DEFINE_CONST_ENUM(HOUGH_MULTI_SCALE);
      DEFINE_CONST_ENUM(HOUGH_GRADIENT);

      Nan::SetMethod(target, "canny", Canny);
      Nan::SetMethod(target, "cornerEigenValsAndVecs", CornerEigenValsAndVecs);
      Nan::SetMethod(target, "cornerHarris", CornerHarris);
      Nan::SetMethod(target, "cornerMinEigenVal", CornerMinEigenVal);
      Nan::SetMethod(target, "cornerSubPix", CornerSubPix);
      Nan::SetMethod(target, "createLineSegmentDetector", CreateLineSegmentDetector);
      Nan::SetMethod(target, "goodFeaturesToTrack", GoodFeaturesToTrack);
      Nan::SetMethod(target, "houghCircles", HoughCircles);
      Nan::SetMethod(target, "houghLines", HoughLines);
      Nan::SetMethod(target, "houghLinesP", HoughLinesP);
      Nan::SetMethod(target, "preCornerDetect", PreCornerDetect);
    }

    NAN_METHOD(Canny) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(4, 6);
      Nan::HandleScope scope;
      ASSERT_INPUTARRAY_FROM_ARGS(m1, 0);
      int argumentOffset = 0;
      cv::_InputArray m2;
      cv::_OutputArray out;
      try {
        out = ReadOutputArray(info[2]);
        try {
          ASSERT_INPUTARRAY_FROM_ARGS(dy, 1);
          m2 = dy;
        } catch (char const*) {
          return Nan::ThrowError(ERROR_INVALID_ARGUMENTS);
        }
        argumentOffset = 1;
      } catch (char const*) {
        ASSERT_OUTPUTARRAY_FROM_ARGS(dst, 1);
        out = dst;
      }
      ASSERT_DOUBLE_FROM_ARGS(threshold1, 2 + argumentOffset);
      ASSERT_DOUBLE_FROM_ARGS(threshold2, 3 + argumentOffset);
      DEFAULT_BOOLEAN_FROM_ARGS(L2gradient, 5, false);

      if (argumentOffset == 0) {
        DEFAULT_INT_FROM_ARGS(apertureSize, 4, 3);
        TRY_CATCH_THROW_OPENCV(cv::Canny(m1, out, threshold1, threshold2, apertureSize, L2gradient));
      } else {
        TRY_CATCH_THROW_OPENCV(cv::Canny(m1, m2, out, threshold1, threshold2, L2gradient));
      }
    }

    NAN_METHOD(CornerEigenValsAndVecs) {
      NotImplemented
    }

    NAN_METHOD(CornerHarris) {
      NotImplemented
    }

    NAN_METHOD(CornerMinEigenVal) {
      NotImplemented
    }

    NAN_METHOD(CornerSubPix) {
      NotImplemented
    }

    NAN_METHOD(CreateLineSegmentDetector) {
      NotImplemented
    }

    NAN_METHOD(GoodFeaturesToTrack) {
      NotImplemented
    }

    NAN_METHOD(HoughCircles) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(4, 8);
      ASSERT_INPUTARRAY_FROM_ARGS(img, 0);
      ASSERT_INT_FROM_ARGS(method, 1);
      ASSERT_DOUBLE_FROM_ARGS(dp, 2);
      ASSERT_DOUBLE_FROM_ARGS(minDist, 3);
      DEFAULT_DOUBLE_FROM_ARGS(param1, 4, 100);
      DEFAULT_DOUBLE_FROM_ARGS(param2, 5, 100);
      DEFAULT_INT_FROM_ARGS(minRadius, 6, 0);
      DEFAULT_INT_FROM_ARGS(maxRadius, 7, 0);
      std::vector<cv::Vec3f> circles;
      TRY_CATCH_THROW_OPENCV(cv::HoughCircles(img, circles, method, dp, minDist, param1, param2, minRadius, maxRadius));

      Local<String> center = Nan::New<String>("center").ToLocalChecked();
      Local<String> radius = Nan::New<String>("radius").ToLocalChecked();

      Local<Array> out = Nan::New<Array>();
      for (cv::Vec3f circle : circles) {
        Local<Object> circleObj = Nan::New<Object>();

        Nan::Set(circleObj, center, Point::NewInstance(circle[0], circle[1]));
        Nan::Set(circleObj, radius, Nan::New<Number>(circle[2]));

        Nan::Set(out, out->Length(), circleObj);
      }

      info.GetReturnValue().Set(out);
    }

    NAN_METHOD(HoughLines) {
      NotImplemented
    }

    NAN_METHOD(HoughLinesP) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(4, 6);
      Nan::HandleScope scope;
      ASSERT_INPUTARRAY_FROM_ARGS(src, 0);
      ASSERT_DOUBLE_FROM_ARGS(rho, 1);
      ASSERT_DOUBLE_FROM_ARGS(theta, 2);
      ASSERT_INT_FROM_ARGS(threshold, 3);
      DEFAULT_DOUBLE_FROM_ARGS(minLineLength, 4, 0);
      DEFAULT_DOUBLE_FROM_ARGS(maxLineGap, 5, 0);

      std::vector<cv::Vec4i> lines;
      TRY_CATCH_THROW_OPENCV(cv::HoughLinesP(src, lines, rho, theta, threshold, minLineLength, maxLineGap));

      v8::Local<v8::Array> out = Nan::New<Array>(lines.size());
      for (unsigned i = 0; i < lines.size(); ++i) {
        v8::Local<v8::Array> arr = Nan::New<Array>(4);
        Nan::Set(arr, 0, Nan::New<Number>(lines[i][0]));
        Nan::Set(arr, 1, Nan::New<Number>(lines[i][1]));
        Nan::Set(arr, 2, Nan::New<Number>(lines[i][2]));
        Nan::Set(arr, 3, Nan::New<Number>(lines[i][3]));

        Nan::Set(out, i, arr);
      }

      info.GetReturnValue().Set(out);
    }

    NAN_METHOD(PreCornerDetect) {
      NotImplemented
    }

  }

}

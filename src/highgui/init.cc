#include "common.h"
#include "../core/Matrix.h"
#include "../core/Rect.h"

namespace ncv {

  namespace highgui {

    using TrackbarAction = std::function<void(int)>;
    using MouseAction = std::function<void(int, int, int, int)>;

    NAN_METHOD(CreateTrackbar) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(2, 4);
      Nan::HandleScope scope;
      ASSERT_STRING_FROM_ARGS(trackbarname, 0);
      ASSERT_STRING_FROM_ARGS(winname, 1);
      ASSERT_INT_FROM_ARGS(count, 2);
      FUNCTION_FROM_ARGS(fn, 3) else {
        TRY_CATCH_THROW_OPENCV(cv::createTrackbar(trackbarname, winname, nullptr, count));
        return;
      }

      Nan::Persistent<Function> onChange;
      TrackbarAction action = [&onChange](int pos) {
        Nan::HandleScope scope;

        if (onChange.IsEmpty()) {
          return;
        }

        Local<Function> callback = onChange.Get(Isolate::GetCurrent());
        Local<Value> argv[]{ Nan::New<Number>(pos) };

        Nan::TryCatch try_catch;
        Nan::Call(callback, Nan::GetCurrentContext()->Global(), 1, argv);
        if (try_catch.HasCaught()) {
          Nan::ThrowError(try_catch.Exception());
        }
      };

      onChange.Reset(fn);

      TRY_CATCH_THROW_OPENCV(cv::createTrackbar(trackbarname, winname, nullptr, count, [](int pos, void* userdata) {
        (*(TrackbarAction*)userdata)(pos);
      }, &action));
    }

    NAN_METHOD(DestroyAllWindows) {
      FUNCTION_REQUIRE_ARGUMENTS(0);
      Nan::HandleScope scope;
      TRY_CATCH_THROW_OPENCV(cv::destroyAllWindows());
    }

    NAN_METHOD(DestroyWindow) {
      FUNCTION_REQUIRE_ARGUMENTS(1);
      Nan::HandleScope scope;
      ASSERT_STRING_FROM_ARGS(winname, 0);
      TRY_CATCH_THROW_OPENCV(cv::destroyWindow(winname));
    }

    NAN_METHOD(GetMouseWheelDelta) {
      FUNCTION_REQUIRE_ARGUMENTS(1);
      Nan::HandleScope scope;
      ASSERT_INT_FROM_ARGS(flags, 0);
      TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Number>(cv::getMouseWheelDelta(flags))));
    }

    NAN_METHOD(GetTrackbarPos) {
      FUNCTION_REQUIRE_ARGUMENTS(2);
      Nan::HandleScope scope;
      ASSERT_STRING_FROM_ARGS(trackbarname, 0);
      ASSERT_STRING_FROM_ARGS(winname, 1);
      TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Number>(cv::getTrackbarPos(trackbarname, winname))));
    }

    NAN_METHOD(GetWindowProperty) {
      FUNCTION_REQUIRE_ARGUMENTS(2);
      Nan::HandleScope scope;
      ASSERT_STRING_FROM_ARGS(winname, 0);
      ASSERT_INT_FROM_ARGS(propId, 1);
      TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Number>(cv::getWindowProperty(winname, propId))));
    }

    NAN_METHOD(Imshow) {
      FUNCTION_REQUIRE_ARGUMENTS(2);
      Nan::HandleScope scope;
      ASSERT_STRING_FROM_ARGS(winname, 0);
      ASSERT_MATRIX_FROM_ARGS(mat, 1);
      TRY_CATCH_THROW_OPENCV(cv::imshow(winname, mat->mat));
    }

    NAN_METHOD(MoveWindow) {
      FUNCTION_REQUIRE_ARGUMENTS(3);
      Nan::HandleScope scope;
      ASSERT_STRING_FROM_ARGS(winname, 0);
      ASSERT_INT_FROM_ARGS(x, 1);
      ASSERT_INT_FROM_ARGS(y, 1);
      TRY_CATCH_THROW_OPENCV(cv::moveWindow(winname, x, y));
    }

    NAN_METHOD(NamedWindow) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(1, 2);
      Nan::HandleScope scope;
      ASSERT_STRING_FROM_ARGS(winname, 0);
      DEFAULT_INT_FROM_ARGS(flags, 1, cv::WINDOW_AUTOSIZE);
      TRY_CATCH_THROW_OPENCV(cv::namedWindow(winname, flags));
    }

    NAN_METHOD(ResizeWindow) {
      FUNCTION_REQUIRE_ARGUMENTS(3);
      Nan::HandleScope scope;
      ASSERT_STRING_FROM_ARGS(winname, 0);
      ASSERT_INT_FROM_ARGS(width, 1);
      ASSERT_INT_FROM_ARGS(height, 2);
      TRY_CATCH_THROW_OPENCV(cv::resizeWindow(winname, width, height));
    }

    NAN_METHOD(SelectROI) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(1, 4);
      Nan::HandleScope scope;

      int argumentOffset = 0;
      std::string winname;
      if (info[0]->IsString()) {
        ASSERT_STRING_FROM_ARGS(name, 0);
        argumentOffset = 1;
        winname = name;
      }

      ASSERT_INPUTARRAY_FROM_ARGS(image, 0 + argumentOffset);
      DEFAULT_BOOLEAN_FROM_ARGS(showCrosshair, 1 + argumentOffset, true);
      DEFAULT_BOOLEAN_FROM_ARGS(fromCenter, 2 + argumentOffset, false);

      TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Rect::NewInstance(
        winname.empty() ? cv::selectROI(image, showCrosshair, fromCenter) : cv::selectROI(winname, image, showCrosshair, fromCenter)
    )));
    }

    NAN_METHOD(SelectROIs) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(3, 5);
      Nan::HandleScope scope;
      ASSERT_STRING_FROM_ARGS(winname, 0);
      ASSERT_INPUTARRAY_FROM_ARGS(image, 1);
      DEFAULT_BOOLEAN_FROM_ARGS(showCrosshair, 2, true);
      DEFAULT_BOOLEAN_FROM_ARGS(fromCenter, 3, false);

      std::vector<cv::Rect> boundingBoxes;
      TRY_CATCH_THROW_OPENCV(cv::selectROIs(winname, image, boundingBoxes, showCrosshair, fromCenter));

      Local<Array> arr = Nan::New<Array>();
      for (unsigned i = 0; i < boundingBoxes.size(); ++i) {
        Nan::Set(arr, i, Rect::NewInstance(boundingBoxes[i]));
      }

      info.GetReturnValue().Set(arr);
    }

    NAN_METHOD(SetMouseCallback) {
      FUNCTION_REQUIRE_ARGUMENTS(2);
      Nan::HandleScope scope;
      ASSERT_STRING_FROM_ARGS(winname, 0);
      FUNCTION_FROM_ARGS(fn, 1);

      Nan::Persistent<Function> onMouse;
      MouseAction action = [&onMouse](int event, int x, int y, int flags) {
        Nan::HandleScope scope;

        if (onMouse.IsEmpty()) {
          return;
        }

        Local<Function> callback = onMouse.Get(Isolate::GetCurrent());
        Local<Value> argv[]{ Nan::New<Number>(event), Nan::New<Number>(x), Nan::New<Number>(y) };

        Nan::TryCatch try_catch;
        Nan::Call(callback, Nan::GetCurrentContext()->Global(), 3, argv);
        if (try_catch.HasCaught()) {
          Nan::ThrowError(try_catch.Exception());
        }
      };

      onMouse.Reset(fn);

      TRY_CATCH_THROW_OPENCV(cv::setMouseCallback(winname, [](int event, int x, int y, int flags, void* userdata) {
        (*(MouseAction*)userdata)(event, x, y, flags);
      }, &action));
    }

    NAN_METHOD(SetTrackbarMax) {
      FUNCTION_REQUIRE_ARGUMENTS(3);
      Nan::HandleScope scope;
      ASSERT_STRING_FROM_ARGS(trackbarname, 0);
      ASSERT_STRING_FROM_ARGS(winname, 1);
      ASSERT_INT_FROM_ARGS(max, 2);
      TRY_CATCH_THROW_OPENCV(cv::setTrackbarMax(trackbarname, winname, max));
    }

    NAN_METHOD(SetTrackbarMin) {
      FUNCTION_REQUIRE_ARGUMENTS(3);
      Nan::HandleScope scope;
      ASSERT_STRING_FROM_ARGS(trackbarname, 0);
      ASSERT_STRING_FROM_ARGS(winname, 1);
      ASSERT_INT_FROM_ARGS(min, 2);
      TRY_CATCH_THROW_OPENCV(cv::setTrackbarMin(trackbarname, winname, min));
    }

    NAN_METHOD(SetTrackbarPos) {
      FUNCTION_REQUIRE_ARGUMENTS(3);
      Nan::HandleScope scope;
      ASSERT_STRING_FROM_ARGS(trackbarname, 0);
      ASSERT_STRING_FROM_ARGS(winname, 1);
      ASSERT_INT_FROM_ARGS(pos, 2);
      TRY_CATCH_THROW_OPENCV(cv::setTrackbarPos(trackbarname, winname, pos));
    }

    NAN_METHOD(SetWindowProperty) {
      FUNCTION_REQUIRE_ARGUMENTS(3);
      Nan::HandleScope scope;
      ASSERT_STRING_FROM_ARGS(winname, 0);
      ASSERT_INT_FROM_ARGS(propId, 1);
      ASSERT_DOUBLE_FROM_ARGS(value, 2);
      TRY_CATCH_THROW_OPENCV(cv::setWindowProperty(winname, propId, value));
    }

    NAN_METHOD(SetWindowTitle) {
      FUNCTION_REQUIRE_ARGUMENTS(2);
      Nan::HandleScope scope;
      ASSERT_STRING_FROM_ARGS(winname, 0);
      ASSERT_STRING_FROM_ARGS(title, 1);
      TRY_CATCH_THROW_OPENCV(cv::setWindowTitle(winname, title));
    }

    NAN_METHOD(StartWindowThread) {
      NotImplemented(info);
    }

    NAN_METHOD(WaitKey) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(0, 1);
      Nan::HandleScope scope;
      DEFAULT_INT_FROM_ARGS(delay, 0, 0);
      TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Integer>(cv::waitKey(delay))));
    }

    NAN_METHOD(WaitKeyEx) {
      FUNCTION_REQUIRE_ARGUMENTS(1);
      Nan::HandleScope scope;
      ASSERT_INT_FROM_ARGS(delay, 0);
      TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Integer>(cv::waitKeyEx(delay))));
    }

    extern "C" void init(Local<Object> target) {
      Nan::HandleScope scope;

      // mouse event flags
      DEFINE_CONST_ENUM(EVENT_FLAG_LBUTTON);
      DEFINE_CONST_ENUM(EVENT_FLAG_RBUTTON);
      DEFINE_CONST_ENUM(EVENT_FLAG_MBUTTON);
      DEFINE_CONST_ENUM(EVENT_FLAG_CTRLKEY);
      DEFINE_CONST_ENUM(EVENT_FLAG_SHIFTKEY);
      DEFINE_CONST_ENUM(EVENT_FLAG_ALTKEY);

      // mouse event types
      DEFINE_CONST_ENUM(EVENT_MOUSEMOVE);
      DEFINE_CONST_ENUM(EVENT_LBUTTONDOWN);
      DEFINE_CONST_ENUM(EVENT_RBUTTONDOWN);
      DEFINE_CONST_ENUM(EVENT_MBUTTONDOWN);
      DEFINE_CONST_ENUM(EVENT_LBUTTONUP);
      DEFINE_CONST_ENUM(EVENT_RBUTTONUP);
      DEFINE_CONST_ENUM(EVENT_MBUTTONUP);
      DEFINE_CONST_ENUM(EVENT_LBUTTONDBLCLK);
      DEFINE_CONST_ENUM(EVENT_RBUTTONDBLCLK);
      DEFINE_CONST_ENUM(EVENT_MBUTTONDBLCLK);
      DEFINE_CONST_ENUM(EVENT_MOUSEWHEEL);
      DEFINE_CONST_ENUM(EVENT_MOUSEHWHEEL);

      // qt button types
      DEFINE_CONST_ENUM(QT_PUSH_BUTTON);
      DEFINE_CONST_ENUM(QT_CHECKBOX);
      DEFINE_CONST_ENUM(QT_RADIOBOX);
      DEFINE_CONST_ENUM(QT_NEW_BUTTONBAR);

      // qt font styles
      DEFINE_CONST_ENUM(QT_STYLE_NORMAL);
      DEFINE_CONST_ENUM(QT_STYLE_ITALIC);
      DEFINE_CONST_ENUM(QT_STYLE_OBLIQUE);

      // qt font weights
      DEFINE_CONST_ENUM(QT_FONT_LIGHT);
      DEFINE_CONST_ENUM(QT_FONT_NORMAL);
      DEFINE_CONST_ENUM(QT_FONT_DEMIBOLD);
      DEFINE_CONST_ENUM(QT_FONT_BOLD);
      DEFINE_CONST_ENUM(QT_FONT_BLACK);

      // window flags
      DEFINE_CONST_ENUM(WINDOW_NORMAL);
      DEFINE_CONST_ENUM(WINDOW_AUTOSIZE);
      DEFINE_CONST_ENUM(WINDOW_OPENGL);
      DEFINE_CONST_ENUM(WINDOW_FULLSCREEN);
      DEFINE_CONST_ENUM(WINDOW_FREERATIO);
      DEFINE_CONST_ENUM(WINDOW_KEEPRATIO);
      DEFINE_CONST_ENUM(WINDOW_GUI_EXPANDED);
      DEFINE_CONST_ENUM(WINDOW_GUI_NORMAL);

      // window property flags
      DEFINE_CONST_ENUM(WND_PROP_FULLSCREEN);
      DEFINE_CONST_ENUM(WND_PROP_AUTOSIZE);
      DEFINE_CONST_ENUM(WND_PROP_ASPECT_RATIO);
      DEFINE_CONST_ENUM(WND_PROP_OPENGL);
      DEFINE_CONST_ENUM(WND_PROP_VISIBLE);

      Nan::SetMethod(target, "createTrackbar", CreateTrackbar);
      Nan::SetMethod(target, "destroyAllWindows", DestroyAllWindows);
      Nan::SetMethod(target, "destroyWindow", DestroyWindow);
      Nan::SetMethod(target, "getMouseWheelDelta", GetMouseWheelDelta);
      Nan::SetMethod(target, "getTrackbarPos", GetTrackbarPos);
      Nan::SetMethod(target, "getWindowProperty", GetWindowProperty);
      Nan::SetMethod(target, "imshow", Imshow);
      Nan::SetMethod(target, "moveWindow", MoveWindow);
      Nan::SetMethod(target, "namedWindow", NamedWindow);
      Nan::SetMethod(target, "resizeWindow", ResizeWindow);
      Nan::SetMethod(target, "selectROI", SelectROI);
      Nan::SetMethod(target, "selectROIs", SelectROIs);
      Nan::SetMethod(target, "setMouseCallback", SetMouseCallback);
      Nan::SetMethod(target, "setTrackbarMax", SetTrackbarMax);
      Nan::SetMethod(target, "setTrackbarMin", SetTrackbarMin);
      Nan::SetMethod(target, "setTrackbarPos", SetTrackbarPos);
      Nan::SetMethod(target, "setWindowProperty", SetWindowProperty);
      Nan::SetMethod(target, "setWindowTitle", SetWindowTitle);
      Nan::SetMethod(target, "startWindowThread", StartWindowThread);
      Nan::SetMethod(target, "waitKey", WaitKey);
      Nan::SetMethod(target, "waitKeyEx", WaitKeyEx);
    }

    NODE_MODULE(highgui, init);

  }

}

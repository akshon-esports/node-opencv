#include "Point.h"
#include "Rect.h"
#include "Scalar.h"
#include "Size.h"
#include "Matrix.h"
#include "UnifiedMatrix.h"
#include "array.h"

NAN_METHOD(NotImplemented) {
  Nan::ThrowError("Not implemented");
}

/**
* ReadInputArray takes a value and returns a cv::_InputArray
*
* Accepts Unified, Gpu and regular Matrix objects, Matrix Expressions and arrays of numbers
*/
cv::_InputArray ReadInputArray(Local<Value> value) {
  Nan::HandleScope scope;

  if (value->IsNumber()) {
    return value->NumberValue();
  }

  if (value->IsArray()) {
    Local<Array> arr = Local<Array>::Cast(value);
    if (arr->Length() == 0) {
      return std::vector<double>{};
    }

    Local<Value> first = Nan::Get(arr, 0).ToLocalChecked();
//    if (Matrix::HasInstance(first)) {
//      std::vector<cv::Mat> mats = { UNWRAP_OBJECT(Matrix, first->ToObject())->mat };
//      for (unsigned i = 1; i < arr->Length(); ++i) {
//        Local<Value> elem = Nan::Get(arr, i).ToLocalChecked();
//        if (!Matrix::HasInstance(elem)) {
//          throw ERROR_INVALID_ARGUMENTS;
//        }
//
//        mats.push_back(UNWRAP_OBJECT(Matrix, elem->ToObject())->mat);
//      }
//
//      return mats;
//    }

    if (first->IsNumber()) {
      std::vector<double> vals{ first->NumberValue() };
      for (unsigned i = 1; i < arr->Length(); ++i) {
        Local<Value> elem = Nan::Get(arr, i).ToLocalChecked();
        if (!elem->IsNumber()) {
          throw ERROR_INVALID_ARGUMENTS;
        }

        vals.push_back(elem->NumberValue());
      }

      return vals;
    }

//    // only allow 2d arrays of numbers
//    if (first->IsArray()) {
//      std::vector<std::vector<double>> arrs;
//      for (unsigned i = 0; i < arr->Length(); ++i) {
//        std::vector<double> vals;
//
//        Local<Array> arr2 = Local<Array>::Cast(Nan::Get(arr, i).ToLocalChecked());
//        for (unsigned j = 0; j < arr2->Length(); ++j) {
//          Local<Value> elem = Nan::Get(arr2, j).ToLocalChecked();
//          if (!elem->IsNumber()) {
//            throw ERROR_INVALID_ARGUMENTS;
//          }
//
//          vals.push_back(elem->NumberValue());
//        }
//      }
//
//      return arrs;
//    }
  }

  if (value->IsObject()) {
    if (Scalar::HasInstance(value)) {
      return UNWRAP_OBJECT(Scalar, value->ToObject())->scalar;
    }

    if (Matrix::HasInstance(value)) {
      return UNWRAP_OBJECT(Matrix, value->ToObject())->mat;
    }
  }

  // TODO add condition for MatrixExpression, GpuMatrix and UnifiedMatrix

  throw ERROR_INVALID_ARGUMENTS;
}

/**
* ReadInputArray takes a value and returns a cv::_InputArray
*
* Accepts Unified, Gpu and regular Matrix objects, Matrix Expressions
*/
cv::_InputOutputArray ReadInputOutputArray(Local<Value> value) {
  Nan::HandleScope scope;

  if (value->IsObject() && Matrix::HasInstance(value)) {
    return UNWRAP_OBJECT(Matrix, value->ToObject())->mat;
  }

  // TODO add condition for MatrixExpression, GpuMatrix and UnifiedMatrix

  throw ERROR_INVALID_ARGUMENTS;
}

/**
* ReadOutputArray takes a value and returns a cv::_InputArray
*
* Accepts Unified, Gpu and regular Matrix objects, arrays of Matrix and Unified Matrix objects, Matrix Expressions, numbers, arrays of numbers and 2D arrays of numbers
*/
cv::_OutputArray ReadOutputArray(Local<Value> value) {
  Nan::HandleScope scope;

  if (value->IsObject() && Matrix::HasInstance(value)) {
    return UNWRAP_OBJECT(Matrix, value->ToObject())->mat;
  }

  // TODO add condition for GpuMatrix and UnifiedMatrix

  throw ERROR_INVALID_ARGUMENTS;
}

extern "C" void init(Local<Object> target) {
  Nan::HandleScope scope;

  Nan::Set(target, Nan::New<String>("VERSION").ToLocalChecked(), Nan::New<String>(CV_VERSION).ToLocalChecked());

  DEFINE_CONST(CV_8U);
  DEFINE_CONST(CV_8S);
  DEFINE_CONST(CV_16U);
  DEFINE_CONST(CV_16S);
  DEFINE_CONST(CV_32S);
  DEFINE_CONST(CV_32F);
  DEFINE_CONST(CV_64F);
  DEFINE_CONST(CV_USRTYPE1);

  DEFINE_CONST(CV_8UC1);
  DEFINE_CONST(CV_8UC2);
  DEFINE_CONST(CV_8UC3);
  DEFINE_CONST(CV_8UC4);

  DEFINE_CONST(CV_8SC1);
  DEFINE_CONST(CV_8SC2);
  DEFINE_CONST(CV_8SC3);
  DEFINE_CONST(CV_8SC4);

  DEFINE_CONST(CV_16UC1);
  DEFINE_CONST(CV_16UC2);
  DEFINE_CONST(CV_16UC3);
  DEFINE_CONST(CV_16UC4);

  DEFINE_CONST(CV_16SC1);
  DEFINE_CONST(CV_16SC2);
  DEFINE_CONST(CV_16SC3);
  DEFINE_CONST(CV_16SC4);

  DEFINE_CONST(CV_32SC1);
  DEFINE_CONST(CV_32SC2);
  DEFINE_CONST(CV_32SC3);
  DEFINE_CONST(CV_32SC4);

  DEFINE_CONST(CV_32FC1);
  DEFINE_CONST(CV_32FC2);
  DEFINE_CONST(CV_32FC3);
  DEFINE_CONST(CV_32FC4);

  DEFINE_CONST(CV_64FC1);
  DEFINE_CONST(CV_64FC2);
  DEFINE_CONST(CV_64FC3);
  DEFINE_CONST(CV_64FC4);

  // access flags
  DEFINE_CONST_ENUM(ACCESS_READ);
  DEFINE_CONST_ENUM(ACCESS_WRITE);
  DEFINE_CONST_ENUM(ACCESS_RW);
  DEFINE_CONST_ENUM(ACCESS_MASK);
  DEFINE_CONST_ENUM(ACCESS_FAST);

  // u mat usage flags
  DEFINE_CONST_ENUM(USAGE_DEFAULT);
  DEFINE_CONST_ENUM(USAGE_ALLOCATE_HOST_MEMORY);
  DEFINE_CONST_ENUM(USAGE_ALLOCATE_DEVICE_MEMORY);
  DEFINE_CONST_ENUM(USAGE_ALLOCATE_SHARED_MEMORY);
  DEFINE_CONST_ENUM(__UMAT_USAGE_FLAGS_32BIT);

  // covar flags
  DEFINE_CONST_ENUM(COVAR_SCRAMBLED);
  DEFINE_CONST_ENUM(COVAR_NORMAL);
  DEFINE_CONST_ENUM(COVAR_USE_AVG);
  DEFINE_CONST_ENUM(COVAR_SCALE);
  DEFINE_CONST_ENUM(COVAR_ROWS);
  DEFINE_CONST_ENUM(COVAR_COLS);

  // hershey fonts
  DEFINE_CONST_ENUM(FONT_HERSHEY_SIMPLEX);
  DEFINE_CONST_ENUM(FONT_HERSHEY_PLAIN);
  DEFINE_CONST_ENUM(FONT_HERSHEY_DUPLEX);
  DEFINE_CONST_ENUM(FONT_HERSHEY_COMPLEX);
  DEFINE_CONST_ENUM(FONT_HERSHEY_TRIPLEX);
  DEFINE_CONST_ENUM(FONT_HERSHEY_COMPLEX_SMALL);
  DEFINE_CONST_ENUM(FONT_HERSHEY_SCRIPT_SIMPLEX);
  DEFINE_CONST_ENUM(FONT_HERSHEY_SCRIPT_COMPLEX);
  DEFINE_CONST_ENUM(FONT_ITALIC);

  // kmeans flags
  DEFINE_CONST_ENUM(KMEANS_RANDOM_CENTERS);
  DEFINE_CONST_ENUM(KMEANS_PP_CENTERS);
  DEFINE_CONST_ENUM(KMEANS_USE_INITIAL_LABELS);

  // line types
  DEFINE_CONST_ENUM(FILLED);
  DEFINE_CONST_ENUM(LINE_4);
  DEFINE_CONST_ENUM(LINE_8);
  DEFINE_CONST_ENUM(LINE_AA);

  // reduce types
  DEFINE_CONST_ENUM(REDUCE_SUM);
  DEFINE_CONST_ENUM(REDUCE_AVG);
  DEFINE_CONST_ENUM(REDUCE_MAX);
  DEFINE_CONST_ENUM(REDUCE_MIN);

  Point::Init(target);
  Rect::Init(target);
  Scalar::Init(target);
  Size::Init(target);
  Matrix::Init(target);
  UnifiedMatrix::Init(target);
  ncv::core::ArrayInit(target);
}

NODE_MODULE(core, init);

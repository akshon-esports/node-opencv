#include "common.h"

namespace ncv {
  
  namespace common {

    const char * ERROR_MUST_USE_NEW = "Cannot instantiate without new";
    const char * ERROR_INVALID_ARGUMENTS = "Invalid arguments";
    const char * ERROR_NOT_IMPLEMENTED = "Not implemented";

    const char * OBJECT_KEY_X = "x";
    const char * OBJECT_KEY_Y = "y";
    const char * OBJECT_KEY_WIDTH = "width";
    const char * OBJECT_KEY_HEIGHT = "height";
    const char * OBJECT_KEY_START = "start";
    const char * OBJECT_KEY_END = "end";

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
    
  }

}

Local<Value> HybridAsyncWorker::GetResult() {
  Nan::EscapableHandleScope scope;
  return scope.Escape(Nan::Undefined());
}

inline bool HybridAsyncWorker::HasError() const {
  return ErrorMessage() != NULL;
}

Local<Value> HybridAsyncWorker::Error() const {
  Nan::EscapableHandleScope scope;
  return scope.Escape(Nan::Error(ErrorMessage()));
}

void HybridAsyncWorker::HandleOKCallback() {
  Nan::HandleScope scope;

  Local<Value> result = GetResult();

  Local<Value> callback_or_resolver = GetFromPersistent(0u);
  if (callback_or_resolver->IsFunction()) {
    Local<Value> argv[2] = { Nan::Undefined(), result };

    Nan::TryCatch try_catch;
    Local<Function>::Cast(callback_or_resolver)->Call(Nan::GetCurrentContext()->Global(), 2, argv);
    if (try_catch.HasCaught()) {
      Nan::FatalException(try_catch);
    }
  } else {
    Local<Promise::Resolver>::Cast(callback_or_resolver)->Resolve(Nan::GetCurrentContext(), result);
    Isolate::GetCurrent()->RunMicrotasks();
  }
}

void HybridAsyncWorker::HandleErrorCallback() {
  Nan::HandleScope scope;

  Local<Value> error = Error();

  Local<Value> callback_or_resolver = GetFromPersistent(0u);
  if (callback_or_resolver->IsFunction()) {
    Local<Value> argv[1]{ error };

    Nan::TryCatch try_catch;
    Nan::CallAsFunction(callback_or_resolver->ToObject(), Nan::GetCurrentContext()->Global(), 1, argv);
    if (try_catch.HasCaught()) {
      Nan::FatalException(try_catch);
    }
  } else {
    Local<Promise::Resolver>::Cast(callback_or_resolver)->Reject(error);
    Isolate::GetCurrent()->RunMicrotasks();
  }
}
#include "Matrix.h"

#include "UnifiedMatrix.h"
#include "Range.h"
#include "Size.h"
#include "Scalar.h"
#include "Rect.h"

namespace ncv {
  namespace common {
    namespace matrix {

      NAN_METHOD(GetUnifiedMatrix) {
        FUNCTION_REQUIRE_ARGUMENTS(1);
        SETUP_FUNCTION(Matrix);
        ASSERT_INT_FROM_ARGS(accessFlags, 0);
        ASSERT_INT_FROM_ARGS(usageFlags, 1);
        TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(UnifiedMatrix::NewInstance(self->mat.getUMat(accessFlags, static_cast<cv::UMatUsageFlags>(usageFlags)))));
      }

      NAN_METHOD(Row) {
        FUNCTION_REQUIRE_ARGUMENTS(1);
        SETUP_FUNCTION(Matrix);
        ASSERT_INT_FROM_ARGS(y, 0);
        TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Matrix::NewInstance(self->mat.row(y))));
      }

      NAN_METHOD(Col) {
        FUNCTION_REQUIRE_ARGUMENTS(1);
        SETUP_FUNCTION(Matrix);
        ASSERT_INT_FROM_ARGS(x, 0);
        TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Matrix::NewInstance(self->mat.col(x))));
      }

      NAN_METHOD(RowRange) {
        FUNCTION_REQUIRE_ARGUMENTS(1);
        SETUP_FUNCTION(Matrix);
        ASSERT_RANGE_FROM_ARGS(r, 0);
        TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Matrix::NewInstance(self->mat.rowRange(r))));
      }

      NAN_METHOD(ColRange) {
        FUNCTION_REQUIRE_ARGUMENTS(1);
        SETUP_FUNCTION(Matrix);
        ASSERT_RANGE_FROM_ARGS(r, 0);
        TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Matrix::NewInstance(self->mat.colRange(r))));
      }

      NAN_METHOD(Diag) {
        FUNCTION_REQUIRE_ARGUMENTS(1);
        SETUP_FUNCTION(Matrix);
        ASSERT_INT_FROM_ARGS(d, 0);
        TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Matrix::NewInstance(self->mat.diag(d))));
      }

      NAN_METHOD(Clone) {
        FUNCTION_REQUIRE_ARGUMENTS(0);
        SETUP_FUNCTION(Matrix);
        TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Matrix::NewInstance(self->mat.clone())));
      }

      NAN_METHOD(CopyTo) {
        FUNCTION_REQUIRE_ARGUMENTS_RANGE(1, 2);
        SETUP_FUNCTION(Matrix);
        ASSERT_OUTPUTARRAY_FROM_ARGS(m, 0);
        DEFAULT_INPUTARRAY_FROM_ARGS(mask, 1, cv::noArray());
        TRY_CATCH_THROW_OPENCV(self->mat.copyTo(m, mask));
      }

      NAN_METHOD(ConvertTo) {
        FUNCTION_REQUIRE_ARGUMENTS_RANGE(1, 3);
        SETUP_FUNCTION(Matrix);
        ASSERT_INT_FROM_ARGS(rtype, 0);
        DEFAULT_INT_FROM_ARGS(alpha, 1, 1);
        DEFAULT_INT_FROM_ARGS(beta, 2, 0);
        UNWRAP_NEW_INSTANCE(Matrix, m);
        TRY_CATCH_THROW_OPENCV(self->mat.convertTo(m->mat, rtype, alpha, beta));
        info.GetReturnValue().Set(inst);
      }

      NAN_METHOD(SetTo) {
        FUNCTION_REQUIRE_ARGUMENTS_RANGE(1, 2);
        SETUP_FUNCTION(Matrix);

        cv::_InputArray value;
        try {
          value = ReadInputArray(info[0]);
        } catch (char const*) {
          return THROW_INVALID_ARGUMENT_TYPE(0, "an Input Array");
        }

        cv::_InputArray mask = cv::noArray();
        if (info.Length() > 1) {
          try {
            value = ReadInputArray(info[1]);
          } catch (char const*) {
            return THROW_INVALID_ARGUMENT_TYPE(1, "an Input Array");
          }
        }

        TRY_CATCH_THROW_OPENCV(self->mat.setTo(value, mask));
      }

      NAN_METHOD(Reshape) {
        FUNCTION_REQUIRE_ARGUMENTS(2);
        SETUP_FUNCTION(Matrix);
        ASSERT_INT_FROM_ARGS(cn, 0);
        if (info[1]->IsNumber()) {
          int rows = info[1]->Int32Value();
          TRY_CATCH_THROW_OPENCV(self->mat.reshape(cn, rows));
        } else if (info[1]->IsArray()) {
          Local<Array> arr = Local<Array>::Cast(info[1]);
          int newndims = arr->Length();
          int *newsz = new int[newndims];
          for (unsigned i = 0; i < arr->Length(); ++i) {
            Local<Value> val = arr->Get(i);
            if (!val->IsNumber()) {
              delete[] newsz;
              return Nan::ThrowError(ERROR_INVALID_ARGUMENTS);
            }

            newsz[i] = val->Int32Value();
          }

          TRY_CATCH_THEN_THROW_OPENCV(self->mat.reshape(cn, newndims, newsz), delete[] newsz);

          delete[] newsz;
        }

        return Nan::ThrowError(ERROR_INVALID_ARGUMENTS);
      }

      NAN_METHOD(Transpose) {
        NotImplemented
      }

      NAN_METHOD(Invert) {
        NotImplemented
      }

      NAN_METHOD(Multiply) {
        NotImplemented
      }

      NAN_METHOD(Cross) {
        FUNCTION_REQUIRE_ARGUMENTS(1);
        SETUP_FUNCTION(Matrix);

        cv::_InputArray m;
        try {
          m = ReadInputArray(info[0]);
        } catch (char const*) {
          return THROW_INVALID_ARGUMENT_TYPE(0, "an Input Array");
        }

        TRY_CATCH_THROW_OPENCV(self->mat.cross(m));
      }

      NAN_METHOD(Dot) {
        FUNCTION_REQUIRE_ARGUMENTS(1);
        SETUP_FUNCTION(Matrix);

        cv::_InputArray m;
        try {
          m = ReadInputArray(info[0]);
        } catch (char const*) {
          return THROW_INVALID_ARGUMENT_TYPE(0, "an Input Array");
        }

        TRY_CATCH_THROW_OPENCV(self->mat.dot(m));
      }

      NAN_METHOD(Create) {
        FUNCTION_REQUIRE_ARGUMENTS_RANGE(2, 3);
        SETUP_FUNCTION(Matrix);
        if (info.Length() == 2 && info[1]->IsNumber()) {
          try {
            Local<Value> val = info[0];
            cv::Size size = Size::RawSize(1, &val);
            ASSERT_INT_FROM_ARGS(type, 1);
            TRY_CATCH_THROW_OPENCV(self->mat.create(size, type));
            return;
          } catch (char const*) {}
        } else if (info.Length() == 3 && info[0]->IsNumber() && info[1]->IsNumber() && info[2]->IsNumber()) {
          TRY_CATCH_THROW_OPENCV(self->mat.create(info[0]->NumberValue(), info[1]->NumberValue(), info[2]->NumberValue()));
          return;
        }

        return Nan::ThrowError(ERROR_INVALID_ARGUMENTS);
      }

      NAN_METHOD(Release) {
        FUNCTION_REQUIRE_ARGUMENTS(0);
        SETUP_FUNCTION(Matrix);
        TRY_CATCH_THROW_OPENCV(self->mat.release());
      }

      NAN_METHOD(Reserve) {
        NotImplemented
      }

      NAN_METHOD(ReserveBuffer) {
        NotImplemented
      }


      NAN_METHOD(Resize) {
        FUNCTION_REQUIRE_ARGUMENTS_RANGE(1, 2);
        SETUP_FUNCTION(Matrix);
        ASSERT_INT_FROM_ARGS(size, 0);
        if (info.Length() == 1) {
          TRY_CATCH_THROW_OPENCV(self->mat.resize(size));
        }

        ASSERT_SCALAR_FROM_ARGS(scalar, 1);
        TRY_CATCH_THROW_OPENCV(self->mat.resize(size, scalar));
      }

      NAN_METHOD(PushBack) {
        NotImplemented
      }

      NAN_METHOD(PopBack) {
        NotImplemented
      }

      NAN_METHOD(LocateROI) {
        NotImplemented
      }

      NAN_METHOD(AdjustROI) {
        SETUP_FUNCTION(Matrix);
        Local<Object> out;
        if (info.Length() == 1) {
          Local<Value> val = info[0];
          TRY_CATCH_THROW_OPENCV(out = Matrix::NewInstance(self->mat(Rect::RawRect(1, &val)))) catch (char const*) {
            return Nan::ThrowError(ERROR_INVALID_ARGUMENTS);
          }
        } else if (info.Length() == 2) {
          try {
            Local<Value> rv = info[0], cv = info[1];
            cv::Range rowRange = Range::RawRange(1, &rv), colRange = Range::RawRange(1, &cv);
            TRY_CATCH_THROW_OPENCV(out = Matrix::NewInstance(self->mat(rowRange, colRange)));
          } catch (char const*) {
            return Nan::ThrowError(ERROR_INVALID_ARGUMENTS);
          }
        } else if (info.Length() == 4) {
          if (info[0]->IsNumber() && info[1]->IsNumber() && info[2]->IsNumber() && info[3]->IsNumber()) {
            TRY_CATCH_THROW_OPENCV(out = Matrix::NewInstance(self->mat.adjustROI(info[0]->IsNumber(), info[1]->IsNumber(), info[2]->IsNumber(), info[3]->IsNumber())));
          } else {
            return Nan::ThrowError(ERROR_INVALID_ARGUMENTS);
          }
        }

        if (out.IsEmpty()) {
          THROW_INVALID_ARGUMENT_COUNT("1, 2, or 4");
        }

        info.GetReturnValue().Set(out);
      }

      NAN_METHOD(IsContinuous) {
        FUNCTION_REQUIRE_ARGUMENTS(0);
        SETUP_FUNCTION(Matrix);
        TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Boolean>(self->mat.isContinuous())));
      }

      NAN_METHOD(IsSubmatrix) {
        FUNCTION_REQUIRE_ARGUMENTS(0);
        SETUP_FUNCTION(Matrix);
        TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Boolean>(self->mat.isSubmatrix())));
      }

      NAN_METHOD(ElemSize) {
        FUNCTION_REQUIRE_ARGUMENTS(0);
        SETUP_FUNCTION(Matrix);
        TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Boolean>(self->mat.isSubmatrix())));
      }

      NAN_METHOD(ElemSize1) {
        NotImplemented
      }

      NAN_METHOD(Type) {
        FUNCTION_REQUIRE_ARGUMENTS(0);
        SETUP_FUNCTION(Matrix);
        TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Number>(self->mat.type())));
      }

      NAN_METHOD(Depth) {
        FUNCTION_REQUIRE_ARGUMENTS(0);
        SETUP_FUNCTION(Matrix);
        TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Number>(self->mat.depth())));
      }

      NAN_METHOD(Channels) {
        FUNCTION_REQUIRE_ARGUMENTS(0);
        SETUP_FUNCTION(Matrix);
        TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Number>(self->mat.channels())));
      }

      NAN_METHOD(Step1) {
        NotImplemented
      }

      NAN_METHOD(Empty) {
        FUNCTION_REQUIRE_ARGUMENTS(0);
        SETUP_FUNCTION(Matrix);
        TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Boolean>(self->mat.empty())));
      }

      NAN_METHOD(Total) {
        FUNCTION_REQUIRE_ARGUMENTS(0);
        SETUP_FUNCTION(Matrix);
        TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Number>(self->mat.total())));
      }

      template <typename T> Local<Value> getValuesFromPtr(uchar* raw, int channels) {
        Nan::EscapableHandleScope scope;

        T* ptr = (T*)raw;
        Local<Array> out = Nan::New<Array>();
        for (int i = 0; i < channels; i++) {
          Nan::Set(out, out->Length(), Nan::New<Number>(ptr[i]));
        }

        return scope.Escape(out);
      }

      NAN_METHOD(At) {
        FUNCTION_REQUIRE_ARGUMENTS(2);
        ASSERT_INT_FROM_ARGS(i0, 0);
        ASSERT_INT_FROM_ARGS(i1, 1);
        SETUP_FUNCTION(Matrix);
        cv::Size size = self->mat.size();

        if (i0 < 0 || i0 >= size.width) {
          return Nan::ThrowError("Argument 1 exceeds matrix bounds");
        }

        if (i1 < 0 || i1 >= size.height) {
          return Nan::ThrowError("Argument 2 exceeds matrix bounds");
        }

        uchar* raw = self->mat.ptr(i0, i1);
        const int channels = self->mat.channels();

        Local<Value> out;
        switch (self->mat.depth()) {
        case CV_64F:
          out = getValuesFromPtr<double>(raw, channels);
          break;
        case CV_32F:
          out = getValuesFromPtr<float>(raw, channels);
          break;
        case CV_32S:
          out = getValuesFromPtr<int32_t>(raw, channels);
          break;
        case CV_16S:
          out = getValuesFromPtr<int16_t>(raw, channels);
          break;
        case CV_16U:
          out = getValuesFromPtr<uint16_t>(raw, channels);
          break;
        case CV_8S:
          out = getValuesFromPtr<int8_t>(raw, channels);
          break;
        case CV_8U:
          out = getValuesFromPtr<uint8_t>(raw, channels);
          break;
        default:
          return Nan::ThrowError("Unable to handle `CV_USERTYPE1` depth");
        }

        return info.GetReturnValue().Set(out);
      }

      NAN_METHOD(Size) {
        FUNCTION_REQUIRE_ARGUMENTS(0);
        SETUP_FUNCTION(Matrix);
        TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Size::NewInstance(self->mat.size())));
      }

      NAN_GETTER(GetFlags) {
        SETUP_FUNCTION(Matrix);
        info.GetReturnValue().Set(Nan::New<Number>(self->mat.flags));
      }

      NAN_GETTER(GetDimensions) {
        SETUP_FUNCTION(Matrix);
        info.GetReturnValue().Set(Nan::New<Number>(self->mat.dims));
      }

      NAN_GETTER(GetRows) {
        SETUP_FUNCTION(Matrix);
        info.GetReturnValue().Set(Nan::New<Number>(self->mat.rows));
      }

      NAN_GETTER(GetColumns) {
        SETUP_FUNCTION(Matrix);
        info.GetReturnValue().Set(Nan::New<Number>(self->mat.cols));
      }

      NAN_METHOD(ToBuffer) {
        SETUP_FUNCTION(Matrix);

        int size = self->mat.rows * self->mat.cols * self->mat.elemSize();
        Local<Object> buf = Nan::NewBuffer(size).ToLocalChecked();
        uchar* data = (uchar*)Buffer::Data(buf);
        // if there is padding after each row, clone first to get rid of it
        if (self->mat.dims == 2 && self->mat.step[0] != size_t(self->mat.size[1])) {
          cv::Mat copy = self->mat.clone();
          memcpy(data, copy.data, size);
        } else {
          memcpy(data, self->mat.data, size);
        }

        Local<Object> globalObj = Nan::GetCurrentContext()->Global();
        Local<Function> bufferConstructor = Local<Function>::Cast(globalObj->Get(Nan::New<String>("Buffer").ToLocalChecked()));
        Local<Value> constructorArgs[3]{ buf, Nan::New<Integer>(size), Nan::New<Integer>(0) };
        info.GetReturnValue().Set(Nan::NewInstance(bufferConstructor, 3, constructorArgs).ToLocalChecked());
      }

    }
  }
}

using namespace matrix;

Nan::Persistent<FunctionTemplate> Matrix::constructor;

NAN_MODULE_INIT(Matrix::Init) {
  Nan::HandleScope scope;

  //Class
  Local<FunctionTemplate> ctor = Nan::New<FunctionTemplate>(New);
  constructor.Reset(ctor);
  ctor->SetClassName(Nan::New<String>("Matrix").ToLocalChecked());

  // ObjectTemplate
  Local<ObjectTemplate> tpl = ctor->InstanceTemplate();
  tpl->SetInternalFieldCount(1);
  Nan::SetAccessor(tpl, Nan::New<String>("flags").ToLocalChecked(), GetFlags);
  Nan::SetAccessor(tpl, Nan::New<String>("dims").ToLocalChecked(), GetDimensions);
  Nan::SetAccessor(tpl, Nan::New<String>("rows").ToLocalChecked(), GetRows);
  Nan::SetAccessor(tpl, Nan::New<String>("cols").ToLocalChecked(), GetColumns);

  // Prototype
  Nan::SetPrototypeMethod(ctor, "getUnifiedMatrix", GetUnifiedMatrix);

  Nan::SetPrototypeMethod(ctor, "row", Row);
  Nan::SetPrototypeMethod(ctor, "col", Col);
  Nan::SetPrototypeMethod(ctor, "rowRange", RowRange);
  Nan::SetPrototypeMethod(ctor, "colRange", ColRange);
  Nan::SetPrototypeMethod(ctor, "diag", Diag);

  Nan::SetPrototypeMethod(ctor, "clone", Clone);

  Nan::SetPrototypeMethod(ctor, "copyTo", CopyTo);

  Nan::SetPrototypeMethod(ctor, "convertTo", ConvertTo);
  Nan::SetPrototypeMethod(ctor, "setTo", SetTo);

  Nan::SetPrototypeMethod(ctor, "reshape", Reshape);

  Nan::SetPrototypeMethod(ctor, "transpose", Transpose);
  Nan::SetPrototypeMethod(ctor, "invert", Invert);
  Nan::SetPrototypeMethod(ctor, "multiply", Multiply);

  Nan::SetPrototypeMethod(ctor, "cross", Cross);
  Nan::SetPrototypeMethod(ctor, "dot", Dot);

  Nan::SetPrototypeMethod(ctor, "create", Create);
  Nan::SetPrototypeMethod(ctor, "release", Release);

  Nan::SetPrototypeMethod(ctor, "reserve", Reserve);
  Nan::SetPrototypeMethod(ctor, "reserveBuffer", ReserveBuffer);

  Nan::SetPrototypeMethod(ctor, "resize", Resize);

  Nan::SetPrototypeMethod(ctor, "pushBack", PushBack);
  Nan::SetPrototypeMethod(ctor, "popBack", PopBack);

  Nan::SetPrototypeMethod(ctor, "locateROI", LocateROI);
  Nan::SetPrototypeMethod(ctor, "adjustROI", AdjustROI);

  Nan::SetPrototypeMethod(ctor, "isContinuous", IsContinuous);
  Nan::SetPrototypeMethod(ctor, "isSubmatrix", IsSubmatrix);

  Nan::SetPrototypeMethod(ctor, "elemSize", ElemSize);
  Nan::SetPrototypeMethod(ctor, "elemSize1", ElemSize1);

  Nan::SetPrototypeMethod(ctor, "type", Type);
  Nan::SetPrototypeMethod(ctor, "depth", Depth);
  Nan::SetPrototypeMethod(ctor, "channels", Channels);
  Nan::SetPrototypeMethod(ctor, "step1", Step1);
  Nan::SetPrototypeMethod(ctor, "empty", Empty);
  Nan::SetPrototypeMethod(ctor, "total", Total);

  Nan::SetPrototypeMethod(ctor, "size", matrix::Size);

  Nan::SetPrototypeMethod(ctor, "toBuffer", ToBuffer);

  Nan::Set(target, Nan::New("Matrix").ToLocalChecked(), Nan::GetFunction(ctor).ToLocalChecked());
}

NAN_METHOD(Matrix::New) {
  Nan::HandleScope scope;

  if (!info.IsConstructCall()) {
    Nan::ThrowTypeError(ERROR_MUST_USE_NEW);
  }

  Matrix* m = nullptr;
  if (info.Length() == 0) {
    m = new Matrix(cv::Mat());
  } else {
    SETUP_ARGC_AND_ARGV;
    try {
      m = new Matrix(RawMatrix(argc, argv));
    } catch (const char* msg) {
      delete[] argv;
      return Nan::ThrowError(msg);
    }
    delete[] argv;
  }

  m->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

NEW_INSTANCE_DEF(Matrix)

Local<Object> Matrix::NewInstance(cv::Mat mat) {
  Nan::EscapableHandleScope scope;

  UNWRAP_NEW_INSTANCE(Matrix, m);
  m->mat = mat;
  return scope.Escape(inst);
}

HAS_INSTANCE_DEF(Matrix)

cv::Mat Matrix::RawMatrix(int const&argc, Local<Value>* const argv) {
  Nan::HandleScope scope;

  if (argc == 0) {
    return cv::Mat();
  }

  if (argc == 1) {
    if (HasInstance(argv[0])) {
      return UNWRAP_OBJECT(Matrix, argv[0]->ToObject())->mat;
    }

    // TODO add condition for GpuMatrix

    throw ERROR_INVALID_ARGUMENTS;
  }

  if ((argc == 2 || argc == 3) && argv[0]->IsObject() && argv[1]->IsNumber()) {
    int type = argv[1]->Int32Value();

    try {
      cv::Size size = Size::RawSize(1, &argv[0]);
      if (argc > 2) {
        // TODO consider allowing a Buffer input as external initial data
        // investigate whether or not it is necessary to copy the entire buffer into new memory
        // or if it is fine to just save the Buffer as Persistent

        try {
          return cv::Mat(size, type, Scalar::RawScalar(1, &argv[2]));
        } catch (const char *) {
          // assume argv[2] is not a Scalar
        }
      } else {
        return cv::Mat(size, type);
      }
    } catch (const char *) {
      // assume argv[0] is not a Size

      if (argv[0]->IsArray()) {
        Local<Array> sizes = Local<Array>::Cast(argv[0]);

        std::vector<int> vsizes;
        for (unsigned i = 0; i < sizes->Length(); i++) {
          Local<Value> size = Nan::Get(sizes, i).ToLocalChecked();
          if (!size->IsNumber()) {
            throw ERROR_INVALID_ARGUMENTS;
          }

          vsizes.push_back(size->Int32Value());
        }


        if (argc > 2) {
          // TODO consider allowing a Buffer input as external initial data

          try {
            return cv::Mat(vsizes, type, Scalar::RawScalar(1, &argv[2]));
          } catch (const char *) {
            // assume argv[2] is not a Scalar
          }
        } else {
          return cv::Mat(vsizes, type);
        }
      }
    }
  }


  if ((argc == 2 || argc == 3) && HasInstance(argv[0])) {
    Matrix* const m = UNWRAP_OBJECT(Matrix, argv[0]->ToObject());

    try {
      cv::Range rowRange = Range::RawRange(1, &argv[1]);

      if (argc == 3) {
        try {
          cv::Range colRange = Range::RawRange(1, &argv[2]);
          return cv::Mat(m->mat, rowRange, colRange);
        } catch (char const*) {}
      } else {
        return cv::Mat(m->mat, rowRange);
      }
    } catch (char const*) {}
  }

  if (argc == 2) {
    if (HasInstance(argv[0])) {
      Matrix* const m = UNWRAP_OBJECT(Matrix, argv[0]->ToObject());

      if (argv[1]->IsArray()) {
        Local<Array> ranges = Local<Array>::Cast(argv[1]);
        std::vector<cv::Range> vranges;
        for (unsigned i = 0; i < ranges->Length(); ++i) {
          Local<Value> range = Nan::Get(ranges, i).ToLocalChecked();
          try {
            vranges.push_back(Range::RawRange(1, &range));
          } catch (char const*) {
            throw ERROR_INVALID_ARGUMENTS;
          }
        }

        return cv::Mat(m->mat, vranges);
      }

      try {
        return cv::Mat(m->mat, Rect::RawRect(1, &argv[1]));
      } catch (char const*) {
        // assume argv[1] is not a Rect
      }
    }

    throw ERROR_INVALID_ARGUMENTS;
  }

  if ((argc == 3 || argc == 4) && argv[0]->IsNumber() && argv[1]->IsNumber() && argv[2]->IsNumber()) {
    int rows = argv[0]->Int32Value();
    int cols = argv[1]->Int32Value();
    int type = argv[2]->Int32Value();

    if (argc > 3) {
      // TODO consider allowing a Buffer input as external initial data

      try {
        return cv::Mat(rows, cols, type, Scalar::RawScalar(1, &argv[3]));
      } catch (const char *) {
        // assume argv[3] is not a Scalar
      }
    } else {
      return cv::Mat(rows, cols, type);
    }
  }

  if (argc == 3) {
    throw ERROR_INVALID_ARGUMENTS;
  }

  if (argc == 4) {
    throw ERROR_INVALID_ARGUMENTS;
  }

  throw cv::format("Expected 0-4 arguments, but got %d", argc).c_str();
}

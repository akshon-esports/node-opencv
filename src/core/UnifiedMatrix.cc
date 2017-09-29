#include "UnifiedMatrix.h"
#include "Range.h"
#include "Size.h"
#include "Rect.h"
#include "Scalar.h"
#include "Matrix.h"

Nan::Persistent<FunctionTemplate> UnifiedMatrix::constructor;

void UnifiedMatrix::Init(Local<Object> const &target) {
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
  Nan::SetPrototypeMethod(ctor, "getMatrix", GetMatrix);

  Nan::SetPrototypeMethod(ctor, "row", Row);
  Nan::SetPrototypeMethod(ctor, "col", Col);
  Nan::SetPrototypeMethod(ctor, "rowRange", RowRange);
  Nan::SetPrototypeMethod(ctor, "colRange", ColRange);
  Nan::SetPrototypeMethod(ctor, "diag", Diag);

  Nan::SetPrototypeMethod(ctor, "clone", Clone);

  Nan::SetPrototypeMethod(ctor, "convertTo", ConvertTo);
  Nan::SetPrototypeMethod(ctor, "setTo", SetTo);

  Nan::SetPrototypeMethod(ctor, "reshape", Reshape);

  Nan::SetPrototypeMethod(ctor, "transpose", Transpose);
  Nan::SetPrototypeMethod(ctor, "invert", Invert);
  Nan::SetPrototypeMethod(ctor, "multiply", Multiply);

  Nan::SetPrototypeMethod(ctor, "dot", Dot);

  Nan::SetPrototypeMethod(ctor, "create", Create);
  Nan::SetPrototypeMethod(ctor, "release", Release);

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

  Nan::SetPrototypeMethod(ctor, "size", Size);

  Nan::Set(target, Nan::New("UnifiedMatrix").ToLocalChecked(), Nan::GetFunction(ctor).ToLocalChecked());
}

NAN_METHOD(UnifiedMatrix::New) {
  Nan::HandleScope scope;

  if (!info.IsConstructCall()) {
    Nan::ThrowTypeError(ERROR_MUST_USE_NEW);
  }

  UnifiedMatrix* m = nullptr;
  if (info.Length() == 0) {
    m = new UnifiedMatrix(cv::UMat());
  } else {
    SETUP_ARGC_AND_ARGV;
    try {
      m = new UnifiedMatrix(RawUnifiedMatrix(argc, argv));
    } catch (const char* msg) {
      delete[] argv;
      return Nan::ThrowError(msg);
    }
    delete[] argv;
  }

  m->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

Local<Object> UnifiedMatrix::NewInstance(cv::UMat mat) {
  Nan::EscapableHandleScope scope;

  UNWRAP_NEW_INSTANCE(UnifiedMatrix, m);
  m->mat = mat;
  return scope.Escape(inst);
}

cv::UMat UnifiedMatrix::RawUnifiedMatrix(int const&argc, Local<Value>* const argv) {
  Nan::HandleScope scope;

  if (argc == 0) {
    return cv::UMat();
  }

  if (argc == 1) {
    if (HasInstance(argv[0])) {
      return UNWRAP_OBJECT(UnifiedMatrix, argv[0]->ToObject())->mat;
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
          return cv::UMat(size, type, Scalar::RawScalar(1, &argv[2]));
        } catch (const char *) {
          // assume argv[2] is not a Scalar
        }
      } else {
        return cv::UMat(size, type);
      }
    } catch (const char *) {
      // assume argv[0] is not a Size

      if (argv[0]->IsArray()) {
        Local<Array> sizesArr = Local<Array>::Cast(argv[0]);
        int dimensions = sizesArr->Length();
        int* sizes = new int[dimensions];
        for (int i = 0; i < dimensions; i++) {
          Local<Value> size = Nan::Get(sizesArr, i).ToLocalChecked();
          if (!size->IsNumber()) {
            delete[] sizes;
            throw ERROR_INVALID_ARGUMENTS;
          }

          sizes[i] = size->Int32Value();
        }

        cv::UMat out;
        if (argc > 2) {
          // TODO consider allowing a Buffer input as external initial data

          try {
            out = cv::UMat(dimensions, sizes, type, Scalar::RawScalar(1, &argv[2]));
          } catch (const char *) {
            // assume argv[2] is not a Scalar
          }
        } else {
          out = cv::UMat(dimensions, sizes, type);
        }
        delete[] sizes;
        return out;
      }
    }
  }


  if ((argc == 2 || argc == 3) && HasInstance(argv[0])) {
    UnifiedMatrix* const m = UNWRAP_OBJECT(UnifiedMatrix, argv[0]->ToObject());

    try {
      cv::Range rowRange = Range::RawRange(1, &argv[1]);

      if (argc == 3) {
        try {
          cv::Range colRange = Range::RawRange(1, &argv[2]);
          return cv::UMat(m->mat, rowRange, colRange);
        } catch (char const*) {}
      } else {
        return cv::UMat(m->mat, rowRange);
      }
    } catch (char const*) {}
  }

  if (argc == 2) {
    if (HasInstance(argv[0])) {
      UnifiedMatrix* const m = UNWRAP_OBJECT(UnifiedMatrix, argv[0]->ToObject());

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

        return cv::UMat(m->mat, vranges);
      }

      try {
        return cv::UMat(m->mat, Rect::RawRect(1, &argv[1]));
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
        return cv::UMat(rows, cols, type, Scalar::RawScalar(1, &argv[3]));
      } catch (const char *) {
        // assume argv[3] is not a Scalar
      }
    } else {
      return cv::UMat(rows, cols, type);
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

NAN_METHOD(UnifiedMatrix::GetMatrix) {
  FUNCTION_REQUIRE_ARGUMENTS(1);
  SETUP_FUNCTION(UnifiedMatrix);
  ASSERT_INT_FROM_ARGS(flags, 0);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Matrix::NewInstance(self->mat.getMat(flags))));
}

NAN_METHOD(UnifiedMatrix::Row) {
  FUNCTION_REQUIRE_ARGUMENTS(1);
  SETUP_FUNCTION(UnifiedMatrix);
  ASSERT_INT_FROM_ARGS(y, 0);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(NewInstance(self->mat.row(y))));
}

NAN_METHOD(UnifiedMatrix::Col) {
  FUNCTION_REQUIRE_ARGUMENTS(1);
  SETUP_FUNCTION(UnifiedMatrix);
  ASSERT_INT_FROM_ARGS(x, 0);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(NewInstance(self->mat.col(x))));
}

NAN_METHOD(UnifiedMatrix::RowRange) {
  FUNCTION_REQUIRE_ARGUMENTS(1);
  SETUP_FUNCTION(UnifiedMatrix);
  ASSERT_RANGE_FROM_ARGS(r, 0);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(NewInstance(self->mat.rowRange(r))));
}

NAN_METHOD(UnifiedMatrix::ColRange) {
  FUNCTION_REQUIRE_ARGUMENTS(1);
  SETUP_FUNCTION(UnifiedMatrix);
  ASSERT_RANGE_FROM_ARGS(r, 0);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(NewInstance(self->mat.colRange(r))));
}

NAN_METHOD(UnifiedMatrix::Diag) {
  FUNCTION_REQUIRE_ARGUMENTS(1);
  SETUP_FUNCTION(UnifiedMatrix);
  ASSERT_INT_FROM_ARGS(d, 0);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(NewInstance(self->mat.diag(d))));
}

NAN_METHOD(UnifiedMatrix::Clone) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(UnifiedMatrix);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(NewInstance(self->mat.clone())));
}

NAN_METHOD(UnifiedMatrix::ConvertTo) {
  FUNCTION_REQUIRE_ARGUMENTS_RANGE(1, 3);
  SETUP_FUNCTION(UnifiedMatrix);
  ASSERT_INT_FROM_ARGS(rtype, 0);
  DEFAULT_INT_FROM_ARGS(alpha, 1, 1);
  DEFAULT_INT_FROM_ARGS(beta, 2, 0);
  UNWRAP_NEW_INSTANCE(UnifiedMatrix, m);
  TRY_CATCH_THROW_OPENCV(self->mat.convertTo(m->mat, rtype, alpha, beta));
  info.GetReturnValue().Set(inst);
}

NAN_METHOD(UnifiedMatrix::SetTo) {
  FUNCTION_REQUIRE_ARGUMENTS_RANGE(1, 2);
  SETUP_FUNCTION(UnifiedMatrix);

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

NAN_METHOD(UnifiedMatrix::Reshape) {
  FUNCTION_REQUIRE_ARGUMENTS(2);
  SETUP_FUNCTION(UnifiedMatrix);
  ASSERT_INT_FROM_ARGS(cn, 0);
  if (info[1]->IsNumber()) {
    int rows = info[1]->Int32Value();
    TRY_CATCH_THROW_OPENCV(self->mat.reshape(cn, rows));
  } else if (info[1]->IsArray()) {
    Local<Array> arr = Local<Array>::Cast(info[1]);
    int dimensions = arr->Length();
    int* newShape = new int[dimensions];
    for (int i = 0; i < dimensions; ++i) {
      if (!arr->IsNumber()) {
        delete[] newShape;
        return Nan::ThrowError(ERROR_INVALID_ARGUMENTS);
      }

      newShape[i] = arr->Int32Value();
    }

    TRY_CATCH_THEN_THROW_OPENCV(self->mat.reshape(cn, dimensions, newShape), delete[] newShape);

    delete[] newShape;
  }

  return Nan::ThrowError(ERROR_INVALID_ARGUMENTS);
}

NAN_METHOD(UnifiedMatrix::Transpose) {
  NotImplemented(info);
}

NAN_METHOD(UnifiedMatrix::Invert) {
  NotImplemented(info);
}

NAN_METHOD(UnifiedMatrix::Multiply) {
  NotImplemented(info);
}

NAN_METHOD(UnifiedMatrix::Dot) {
  FUNCTION_REQUIRE_ARGUMENTS(1);
  SETUP_FUNCTION(UnifiedMatrix);

  cv::_InputArray m;
  try {
    m = ReadInputArray(info[0]);
  } catch (char const*) {
    return THROW_INVALID_ARGUMENT_TYPE(0, "an Input Array");
  }

  TRY_CATCH_THROW_OPENCV(self->mat.dot(m));
}

NAN_METHOD(UnifiedMatrix::Create) {
  FUNCTION_REQUIRE_ARGUMENTS_RANGE(2, 3);
  SETUP_FUNCTION(UnifiedMatrix);
  if (info.Length() == 2 && info[1]->IsNumber()) {
    try {
      Local<Value> val = info[0];
      cv::Size size = Size::RawSize(1, &val);
      ASSERT_INT_FROM_ARGS(type, 1);
      TRY_CATCH_THROW_OPENCV(self->mat.create(size, info[1]->NumberValue()));
    } catch (char const*) {}
  } else if (info.Length() == 3 && info[0]->IsNumber() && info[1]->IsNumber() && info[2]->IsNumber()) {
    TRY_CATCH_THROW_OPENCV(self->mat.create(info[0]->NumberValue(), info[1]->NumberValue(), info[2]->NumberValue()));
  }

  return Nan::ThrowError(ERROR_INVALID_ARGUMENTS);
}

NAN_METHOD(UnifiedMatrix::Release) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(UnifiedMatrix);
  TRY_CATCH_THROW_OPENCV(self->mat.release());
}

NAN_METHOD(UnifiedMatrix::LocateROI) {
  NotImplemented(info);
}

NAN_METHOD(UnifiedMatrix::AdjustROI) {
  SETUP_FUNCTION(UnifiedMatrix);
  Local<Object> out;
  if (info.Length() == 1) {
    Local<Value> val = info[0];
    TRY_CATCH_THROW_OPENCV(out = NewInstance(self->mat(Rect::RawRect(1, &val)))) catch (char const*) {
      return Nan::ThrowError(ERROR_INVALID_ARGUMENTS);
    }
  } else if (info.Length() == 2) {
    try {
      Local<Value> rv = info[0], cv = info[1];
      cv::Range rowRange = Range::RawRange(1, &rv), colRange = Range::RawRange(1, &cv);
      TRY_CATCH_THROW_OPENCV(out = NewInstance(self->mat(rowRange, colRange)));
    } catch (char const*) {
      return Nan::ThrowError(ERROR_INVALID_ARGUMENTS);
    }
  } else if (info.Length() == 4) {
    if (info[0]->IsNumber() && info[1]->IsNumber() && info[2]->IsNumber() && info[3]->IsNumber()) {
      TRY_CATCH_THROW_OPENCV(out = NewInstance(self->mat.adjustROI(info[0]->IsNumber(), info[1]->IsNumber(), info[2]->IsNumber(), info[3]->IsNumber())));
    } else {
      return Nan::ThrowError(ERROR_INVALID_ARGUMENTS);
    }
  }

  if (out.IsEmpty()) {
    THROW_INVALID_ARGUMENT_COUNT("1, 2, or 4");
  }

  info.GetReturnValue().Set(out);
}

NAN_METHOD(UnifiedMatrix::IsContinuous) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(UnifiedMatrix);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Boolean>(self->mat.isContinuous())));
}

NAN_METHOD(UnifiedMatrix::IsSubmatrix) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(UnifiedMatrix);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Boolean>(self->mat.isSubmatrix())));
}

NAN_METHOD(UnifiedMatrix::ElemSize) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(UnifiedMatrix);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Boolean>(self->mat.isSubmatrix())));
}

NAN_METHOD(UnifiedMatrix::ElemSize1) {
  NotImplemented(info);
}

NAN_METHOD(UnifiedMatrix::Type) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(UnifiedMatrix);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Number>(self->mat.type())));
}

NAN_METHOD(UnifiedMatrix::Depth) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(UnifiedMatrix);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Number>(self->mat.depth())));
}

NAN_METHOD(UnifiedMatrix::Channels) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(UnifiedMatrix);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Number>(self->mat.channels())));
}

NAN_METHOD(UnifiedMatrix::Step1) {
  NotImplemented(info);
}

NAN_METHOD(UnifiedMatrix::Empty) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(UnifiedMatrix);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Boolean>(self->mat.empty())));
}

NAN_METHOD(UnifiedMatrix::Total) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(UnifiedMatrix);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Number>(self->mat.total())));
}

NAN_METHOD(UnifiedMatrix::Size) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(UnifiedMatrix);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Size::NewInstance(self->mat.size())));
}

NAN_GETTER(UnifiedMatrix::GetFlags) {
  SETUP_FUNCTION(UnifiedMatrix);
  info.GetReturnValue().Set(Nan::New<Number>(self->mat.flags));
}

NAN_GETTER(UnifiedMatrix::GetDimensions) {
  SETUP_FUNCTION(UnifiedMatrix);
  info.GetReturnValue().Set(Nan::New<Number>(self->mat.dims));
}

NAN_GETTER(UnifiedMatrix::GetRows) {
  SETUP_FUNCTION(UnifiedMatrix);
  info.GetReturnValue().Set(Nan::New<Number>(self->mat.rows));
}

NAN_GETTER(UnifiedMatrix::GetColumns) {
  SETUP_FUNCTION(UnifiedMatrix);
  info.GetReturnValue().Set(Nan::New<Number>(self->mat.cols));
}


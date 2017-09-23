#include "Matrix.h"

#include "Scalar.h"
#include "Size.h"
#include "Rect.h"
#include "Range.h"

Nan::Persistent<FunctionTemplate> Matrix::constructor;

void Matrix::Init(Local<Object> target) {
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

  Nan::SetPrototypeMethod(ctor, "size", Size);

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
    } catch(const char* msg) {
      delete[] argv;
      return Nan::ThrowError(msg);
    }
    delete[] argv;
  }

  m->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

Local<Object> Matrix::NewInstance(cv::Mat mat) {
  Nan::EscapableHandleScope scope;

  UNWRAP_NEW_INSTANCE(Matrix, m);
  m->mat = mat;
  return scope.Escape(inst);
}

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
        } catch(char const*) {}
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
      cv::Mat(rows, cols, type);
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

NAN_METHOD(Matrix::GetUnifiedMatrix) {
  NotImplemented(info);
}

NAN_METHOD(Matrix::Row) {
  FUNCTION_REQUIRE_ARGUMENTS(1);
  SETUP_FUNCTION(Matrix);
  ASSERT_INT_FROM_ARGS(y, 0);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(NewInstance(self->mat.row(y))));
}

NAN_METHOD(Matrix::Col) {
  FUNCTION_REQUIRE_ARGUMENTS(1);
  SETUP_FUNCTION(Matrix);
  ASSERT_INT_FROM_ARGS(x, 0);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(NewInstance(self->mat.col(x))));
}

NAN_METHOD(Matrix::RowRange) {
  FUNCTION_REQUIRE_ARGUMENTS(1);
  SETUP_FUNCTION(Matrix);
  ASSERT_RANGE_FROM_ARGS(r, 0);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(NewInstance(self->mat.rowRange(r))));
}

NAN_METHOD(Matrix::ColRange) {
  FUNCTION_REQUIRE_ARGUMENTS(1);
  SETUP_FUNCTION(Matrix);
  ASSERT_RANGE_FROM_ARGS(r, 0);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(NewInstance(self->mat.colRange(r))));
}

NAN_METHOD(Matrix::Diag) {
  FUNCTION_REQUIRE_ARGUMENTS(1);
  SETUP_FUNCTION(Matrix);
  ASSERT_INT_FROM_ARGS(d, 0);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(NewInstance(self->mat.diag(d))));
}

NAN_METHOD(Matrix::Clone) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(Matrix);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(NewInstance(self->mat.clone())));
}

NAN_METHOD(Matrix::ConvertTo) {
  FUNCTION_REQUIRE_ARGUMENTS_RANGE(1, 3);
  SETUP_FUNCTION(Matrix);
  ASSERT_INT_FROM_ARGS(rtype, 0);
  DEFAULT_INT_FROM_ARGS(alpha, 1, 1);
  DEFAULT_INT_FROM_ARGS(beta, 2, 0);
  UNWRAP_NEW_INSTANCE(Matrix, m);
  TRY_CATCH_THROW_OPENCV(self->mat.convertTo(m->mat, rtype, alpha, beta));
  info.GetReturnValue().Set(inst);
}

NAN_METHOD(Matrix::SetTo) {
  FUNCTION_REQUIRE_ARGUMENTS_RANGE(1, 2);
  SETUP_FUNCTION(Matrix);

  cv::_InputArray value;
  try {
    value = ReadInputArray(info[0]);
  } catch(char const*) {
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

NAN_METHOD(Matrix::Reshape) {
  FUNCTION_REQUIRE_ARGUMENTS(2);
  SETUP_FUNCTION(Matrix);
  ASSERT_INT_FROM_ARGS(cn, 0);
  if (info[1]->IsNumber()) {
    int rows = info[1]->Int32Value();
    TRY_CATCH_THROW_OPENCV(self->mat.reshape(cn, rows));
  } else if (info[1]->IsArray()) {
    Local<Array> arr = Local<Array>::Cast(info[1]);
    std::vector<int> newShape(arr->Length());
    for (unsigned i = 0; i < arr->Length(); ++i) {
      if (!arr->IsNumber()) {
        throw ERROR_INVALID_ARGUMENTS;
      }

      newShape.push_back(arr->Int32Value());
    }

    TRY_CATCH_THROW_OPENCV(self->mat.reshape(cn, newShape));
  }

  throw ERROR_INVALID_ARGUMENTS;
}

NAN_METHOD(Matrix::Transpose) {
  NotImplemented(info);
}

NAN_METHOD(Matrix::Invert) {
  NotImplemented(info);
}

NAN_METHOD(Matrix::Multiply) {
  NotImplemented(info);
}

NAN_METHOD(Matrix::Cross) {
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

NAN_METHOD(Matrix::Dot) {
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

NAN_METHOD(Matrix::Create) {
  FUNCTION_REQUIRE_ARGUMENTS_RANGE(2, 3);
  SETUP_FUNCTION(Matrix);
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

NAN_METHOD(Matrix::Release) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(Matrix);
  TRY_CATCH_THROW_OPENCV(self->mat.release());
}

NAN_METHOD(Matrix::Reserve) {
  NotImplemented(info);
}

NAN_METHOD(Matrix::ReserveBuffer) {
  NotImplemented(info);
}


NAN_METHOD(Matrix::Resize) {
  FUNCTION_REQUIRE_ARGUMENTS_RANGE(1, 2);
  SETUP_FUNCTION(Matrix);
  ASSERT_INT_FROM_ARGS(size, 0);
  if (info.Length() == 1) {
    TRY_CATCH_THROW_OPENCV(self->mat.resize(size));
  }

  ASSERT_SCALAR_FROM_ARGS(scalar, 1);
  TRY_CATCH_THROW_OPENCV(self->mat.resize(size), scalar);
}

NAN_METHOD(Matrix::PushBack) {
  NotImplemented(info);
}

NAN_METHOD(Matrix::PopBack) {
  NotImplemented(info);
}

NAN_METHOD(Matrix::LocateROI) {
  NotImplemented(info);
}

NAN_METHOD(Matrix::AdjustROI) {
  SETUP_FUNCTION(Matrix);
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

NAN_METHOD(Matrix::IsContinuous) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(Matrix);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Boolean>(self->mat.isContinuous())));
}

NAN_METHOD(Matrix::IsSubmatrix) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(Matrix);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Boolean>(self->mat.isSubmatrix())));
}

NAN_METHOD(Matrix::ElemSize) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(Matrix);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Boolean>(self->mat.isSubmatrix())));
}

NAN_METHOD(Matrix::ElemSize1) {
  NotImplemented(info);
}

NAN_METHOD(Matrix::Type) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(Matrix);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Number>(self->mat.type())));
}

NAN_METHOD(Matrix::Depth) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(Matrix);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Number>(self->mat.depth())));
}

NAN_METHOD(Matrix::Channels) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(Matrix);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Number>(self->mat.channels())));
}

NAN_METHOD(Matrix::Step1) {
  NotImplemented(info);
}

NAN_METHOD(Matrix::Empty) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(Matrix);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Boolean>(self->mat.empty())));
}

NAN_METHOD(Matrix::Total) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(Matrix);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Nan::New<Number>(self->mat.total())));
}

NAN_METHOD(Matrix::Size) {
  FUNCTION_REQUIRE_ARGUMENTS(0);
  SETUP_FUNCTION(Matrix);
  TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Size::NewInstance(self->mat.size())));
}

NAN_GETTER(Matrix::GetFlags) {
  SETUP_FUNCTION(Matrix);
  info.GetReturnValue().Set(Nan::New<Number>(self->mat.flags));
};
NAN_GETTER(Matrix::GetDimensions) {
  SETUP_FUNCTION(Matrix);
  info.GetReturnValue().Set(Nan::New<Number>(self->mat.dims));
};
NAN_GETTER(Matrix::GetRows) {
  SETUP_FUNCTION(Matrix);
  info.GetReturnValue().Set(Nan::New<Number>(self->mat.rows));
};
NAN_GETTER(Matrix::GetColumns) {
  SETUP_FUNCTION(Matrix);
  info.GetReturnValue().Set(Nan::New<Number>(self->mat.cols));
};

NAN_METHOD(Matrix::ToBuffer) {
  SETUP_FUNCTION(Matrix);

  int size = self->mat.rows * self->mat.cols * self->mat.elemSize();
  Local<Object> buf = Nan::NewBuffer(size).ToLocalChecked();
  uchar* data = (uchar*) Buffer::Data(buf);
  // if there is padding after each row, clone first to get rid of it
  if (self->mat.dims == 2 && self->mat.step[0] != size_t(self->mat.size[1])) {
    cv::Mat copy = self->mat.clone();
    memcpy(data, copy.data, size);
  } else {
    memcpy(data, self->mat.data, size);
  }

  Local<Object> globalObj = Nan::GetCurrentContext()->Global();
  Local<Function> bufferConstructor = Local<Function>::Cast(globalObj->Get(Nan::New<String>("Buffer").ToLocalChecked()));
  Local<Value> constructorArgs[3] { buf, Nan::New<Integer>(size), Nan::New<Integer>(0) };
  info.GetReturnValue().Set(Nan::NewInstance(bufferConstructor, 3, constructorArgs).ToLocalChecked());
}

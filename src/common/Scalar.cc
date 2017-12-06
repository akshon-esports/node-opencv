#include "Scalar.h"

namespace ncv {
  namespace common {
    namespace scalar {
      NAN_INDEX_GETTER(IndexGetter) {
        SETUP_FUNCTION(Scalar);
        if (index < 4) {
          info.GetReturnValue().Set(Nan::New<Number>(self->scalar[index]));
        }
      }

      NAN_INDEX_SETTER(IndexSetter) {
        SETUP_FUNCTION(Scalar);
        if (index < 4) {
          if (!value->IsNumber()) {
            return Nan::ThrowTypeError("value must be a number");
          }

          self->scalar[index] = value->NumberValue();
          info.GetReturnValue().Set(info.This());
        }
      }

      NAN_INDEX_QUERY(IndexQuery) {
        if (index < 4) {
          info.GetReturnValue().Set(Nan::New<Integer>(DontDelete));
        }
      }

      NAN_INDEX_ENUMERATOR(IndexEnumerator) {
        v8::Local<v8::Array> arr = Nan::New<v8::Array>();
        for (int i = 0; i < 4; i++) {
          Nan::Set(arr, i, Nan::New(std::to_string(i)).ToLocalChecked());
        }
        info.GetReturnValue().Set(arr);
      }

      NAN_METHOD(Mul) {
        SETUP_FUNCTION(Scalar)

          if (info.Length() == 0) {
            return Nan::ThrowError("Scalar.mul requires at least 1 argument");
          }

        SETUP_ARGC_AND_ARGV;

        cv::Scalar scalar;
        try {
          scalar = Scalar::RawScalar(argc, argv);
        } catch (const char* msg) {
          delete[] argv;
          return Nan::ThrowTypeError(msg);
        }
        delete[] argv;

        DEFAULT_DOUBLE_FROM_ARGS(scale, 1, 1);

        info.GetReturnValue().Set(Scalar::NewInstance(self->scalar.mul(scalar, scale)));
      }

      NAN_METHOD(Conj) {
        SETUP_FUNCTION(Scalar)

          info.GetReturnValue().Set(Scalar::NewInstance(self->scalar.conj()));
      }

      NAN_METHOD(IsReal) {
        SETUP_FUNCTION(Scalar)

          info.GetReturnValue().Set(Nan::New<Boolean>(self->scalar.isReal()));
      }

    }
  }
}

using namespace scalar;

Nan::Persistent<FunctionTemplate> Scalar::constructor;

NAN_MODULE_INIT(Scalar::Init) {
  Nan::HandleScope scope;

  // Constructor
  Local<FunctionTemplate> ctor = Nan::New<FunctionTemplate>(New);
  constructor.Reset(ctor);

  ctor->SetClassName(Nan::New("Scalar").ToLocalChecked());

  // Instance
  Local<ObjectTemplate> inst = ctor->InstanceTemplate();
  inst->SetInternalFieldCount(1);
  Nan::SetIndexedPropertyHandler(inst, IndexGetter, IndexSetter, IndexQuery, 0, IndexEnumerator);

  // Prototype Methods
  Nan::SetPrototypeMethod(ctor, "mul", Mul);
  Nan::SetPrototypeMethod(ctor, "conj", Conj);
  Nan::SetPrototypeMethod(ctor, "isReal", IsReal);


  Nan::Set(target, Nan::New("Scalar").ToLocalChecked(), ctor->GetFunction());
}

NAN_METHOD(Scalar::New) {
  Nan::HandleScope scope;

  if (!info.IsConstructCall()) {
    return Nan::ThrowTypeError(ERROR_MUST_USE_NEW);
  }

  SETUP_ARGC_AND_ARGV;

  cv::Scalar scalar;
  try {
    scalar = RawScalar(argc, argv);
  } catch (const char* msg) {
    delete[] argv;
    return Nan::ThrowTypeError(msg);
  }
  delete[] argv;

  Scalar* s = new Scalar();
  s->scalar = scalar;
  s->Wrap(info.This());

  info.GetReturnValue().Set(info.This());
}

NEW_INSTANCE_DEF(Scalar)

Local<Object> Scalar::NewInstance(cv::Scalar const &scalar) {
  Nan::EscapableHandleScope scope;

  UNWRAP_NEW_INSTANCE(Scalar, s);
  s->scalar = scalar;

  return scope.Escape(inst);
}

Local<Object> Scalar::NewInstance(double const &v0, double const &v1, double const &v2, double const &v3) {
  Nan::EscapableHandleScope scope;

  UNWRAP_NEW_INSTANCE(Scalar, s);
  s->scalar[0] = v0;
  s->scalar[1] = v1;
  s->scalar[2] = v2;
  s->scalar[3] = v3;

  return scope.Escape(inst);
}

HAS_INSTANCE_DEF(Scalar)

cv::Scalar Scalar::RawScalar(int const &argc, Local<Value>* const argv) {
  Nan::EscapableHandleScope scope;

  if (argc == 0) {
    return cv::Scalar();
  }

  if (argc == 1) {

    if (HasInstance(argv[0])) {
      Scalar *s = UNWRAP_OBJECT(Scalar, argv[0]->ToObject());
      return s->scalar;
    }

    if (argv[0]->IsArray()) {
      Local<Array> scalarLike = Local<Array>::Cast(argv[0]);
      if (scalarLike->Length() == 0) {
        throw "Array must have at least 1 value";
      }

      cv::Scalar scalar;
      for (unsigned i = 0; i < scalarLike->Length() && i < 4; i++) {
        Local<Value> objValue = Nan::Get(scalarLike, i).ToLocalChecked();
        if (!objValue->IsNumber()) {
          throw cv::format("Array value at index %d must be a number", i).c_str();
        }

        scalar[i] = objValue->NumberValue();
      }

      return scalar;
    }

    if (!argv[0]->IsNumber()) {
      throw ERROR_INVALID_ARGUMENTS;
    }
  }

  if (argc <= 4) {
    for (int i = 0; i < argc; i++) {
      if (!argv[i]->IsNumber()) {
        throw "Invalid arugments";
      }
    }

    return cv::Scalar(argv[0]->NumberValue(), argc > 1 ? argv[1]->NumberValue() : 0, argc > 2 ? argv[2]->NumberValue() : 0, argc > 3 ? argv[3]->NumberValue() : 0);
  }

  throw cv::format("Expected 0-4 arguments, but got %d", argc).c_str();
}

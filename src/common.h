#ifndef __COMMON_H__
#define __COMMON_H__

#ifdef _WIN32
# ifndef BUILDING_NCV_CORE_BINDINGS
#   define NCV_CORE_EXTERN __declspec(dllimport)
# else
#   define NCV_CORE_EXTERN __declspec(dllexport)
# endif
#else
# define NCV_CORE_EXTERN /* nothing */
#endif

#include <v8.h>
#include <node.h>
#include <nan.h>

using namespace v8;
using namespace node;

#define UNWRAP_OBJECT(TYPE, OBJ) \
  Nan::ObjectWrap::Unwrap<TYPE>(OBJ)

#define UNWRAP_ARG(TYPE, IND) \
  UNWRAP_OBJECT(TYPE, info[IND]->ToObject())

#define UNWRAP_NEW_INSTANCE(TYPE, NAME) \
  Local<Object> inst = NewInstance(); \
  TYPE* NAME = UNWRAP_OBJECT(TYPE, inst);

#define SETUP_FUNCTION(TYP)	\
  Nan::HandleScope scope; \
  TYP *self = UNWRAP_OBJECT(TYP, info.This());

#define THROW_INVALID_ARGUMENT_COUNT(EXPECTED_STRING) \
  Nan::ThrowError(cv::format("Expected %s arguments, but got %d", EXPECTED_STRING, info.Length()).c_str())

#define FUNCTION_REQUIRE_ARGUMENTS_CUSTOM(FAIL_CONDITION, EXPECTED_STRING) \
  if (FAIL_CONDITION) { \
    return THROW_INVALID_ARGUMENT_COUNT(EXPECTED_STRING); \
  }

#define FUNCTION_REQUIRE_ARGUMENTS(COUNT) \
  FUNCTION_REQUIRE_ARGUMENTS_CUSTOM(info.Length() != COUNT, std::to_string(COUNT)) \

#define FUNCTION_REQUIRE_ARGUMENTS_MIN(COUNT) \
  FUNCTION_REQUIRE_ARGUMENTS_CUSTOM(info.Length() < COUNT, cv::format("at least %d", COUNT).c_str()) \

#define FUNCTION_REQUIRE_ARGUMENTS_RANGE(COUNT_MIN, COUNT_MAX) \
  FUNCTION_REQUIRE_ARGUMENTS_CUSTOM(info.Length() < COUNT_MIN || info.Length() > COUNT_MAX, cv::format("%d-%d", COUNT_MIN, COUNT_MAX).c_str()) \

#define NEW_INSTANCE_DEF \
  static inline Local<Object> NewInstance() { \
    Nan::EscapableHandleScope scope;\
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(Nan::New(constructor)).ToLocalChecked()).ToLocalChecked()); \
  };

#define HAS_INSTANCE_DEF \
  static inline bool HasInstance(Local<Value> object) { \
    return Nan::New(constructor)->HasInstance(object); \
  };

#define _ELSE_DEFAULT_(NAME, DEF) else { \
    NAME = DEF; \
  }

#define THROW_INVALID_ARGUMENT_TYPE(IND, TYPE_STR) \
  Nan::ThrowTypeError(cv::format("Argument %d must be %s", IND + 1, TYPE_STR).c_str())

#define _ELSE_THROW_INVALID_ARGUMENT_TYPE_(IND, TYPE_STR) else { \
    return THROW_INVALID_ARGUMENT_TYPE(IND, TYPE_STR); \
  }

#define SETUP_ARGC_AND_ARGV \
  int argc = info.Length(); \
  Local<Value> *argv = new Local<Value>[argc](); \
  for (int n = 0; n < argc; ++n) argv[n] = info[n];

#define INT_FROM_ARGS(NAME, IND) \
  int NAME; \
  if (info.Length() > IND && info[IND]->IsNumber()) { \
    NAME = info[IND]->Int32Value(); \
  }

#define ASSERT_INT_FROM_ARGS(NAME, IND) \
  INT_FROM_ARGS(NAME, IND) _ELSE_THROW_INVALID_ARGUMENT_TYPE_(IND, "a number")

#define DEFAULT_INT_FROM_ARGS(NAME, IND, DEF) \
  INT_FROM_ARGS(NAME, IND) _ELSE_DEFAULT_(NAME, DEF)

#define DOUBLE_FROM_ARGS(NAME, IND) \
  double NAME; \
  if (info.Length() > IND && info[IND]->IsNumber()) { \
    NAME = info[IND]->NumberValue(); \
  }

#define ASSERT_DOUBLE_FROM_ARGS(NAME, IND) \
  DOUBLE_FROM_ARGS(NAME, IND) _ELSE_THROW_INVALID_ARGUMENT_TYPE_(IND, "a number")

#define DEFAULT_DOUBLE_FROM_ARGS(NAME, IND, DEF) \
  DOUBLE_FROM_ARGS(NAME, IND) _ELSE_DEFAULT_(NAME, DEF)

#define BOOLEAN_FROM_ARGS(NAME, IND) \
  bool NAME; \
  if (info.Length() > IND && info[IND]->IsBoolean()) { \
    NAME = info[IND]->BooleanValue(); \
  }

#define ASSERT_BOOLEAN_FROM_ARGS(NAME, IND) \
  BOOLEAN_FROM_ARGS(NAME, IND) _ELSE_THROW_INVALID_ARGUMENT_TYPE_(IND, "a boolean")

#define DEFAULT_BOOLEAN_FROM_ARGS(NAME, IND, DEF) \
  BOOLEAN_FROM_ARGS(NAME, IND) _ELSE_DEFAULT_(NAME, DEF)

#define STRING_FROM_ARGS(NAME, IND) \
  std::string NAME; \
  if (info.Length() > IND && info[IND]->IsString()) { \
    NAME = *Nan::Utf8String(info[IND]->ToString()); \
  }

#define DEFAULT_STRING_FROM_ARGS(NAME, IND, DEF) \
  STRING_FROM_ARGS(NAME, IND) _ELSE_DEFAULT_(NAME, DEF)

#define ASSERT_STRING_FROM_ARGS(NAME, IND) \
  STRING_FROM_ARGS(NAME, IND) _ELSE_THROW_INVALID_ARGUMENT_TYPE_(IND, "a string")

#define FUNCTION_FROM_ARGS(NAME, IND) \
  Local<Function> NAME; \
  if (info.Length() > IND && info[IND]->IsFunction()) { \
    NAME = Local<Function>::Cast(info[IND]); \
  }

#define ARRAY_FROM_ARGS(NAME, IND) \
  Local<Array> NAME; \
  if (info.Length() > IND && info[IND]->IsArray()) { \
    NAME = Local<Array>::Cast(info[IND]); \
  }

#define ASSERT_ARRAY_FROM_ARGS(NAME, IND) \
  ARRAY_FROM_ARGS(NAME, IND) _ELSE_THROW_INVALID_ARGUMENT_TYPE_(IND, "an Array");

#define TRY_CATCH_THROW_OPENCV(STMT) \
  try { \
    STMT; \
  } catch (cv::Exception e) { \
    return Nan::ThrowError(e.what());\
  }

#define DEFINE_CONST(C) \
  Nan::Set(target, Nan::New<String>(#C).ToLocalChecked(), Nan::New<Integer>(C));

#define DEFINE_CONST_INT(C) \
  Nan::Set(target, Nan::New<String>(#C).ToLocalChecked(), Nan::New<Integer>((int)C));

#define DEFINE_CONST_NAMESPACED_ENUM(NS, C) \
  Nan::Set(target, Nan::New<String>(#C).ToLocalChecked(), Nan::New<Integer>((int)(NS::C)));

#define DEFINE_CONST_ENUM(C) \
  DEFINE_CONST_NAMESPACED_ENUM(cv, C)

#define GENERIC_NAMED_PROPERTY_GETTER(name) void name(Local<Name> property, const PropertyCallbackInfo<Value> &info)
#define GENERIC_NAMED_PROPERTY_SETTER(name) void name(Local<Name> property, Local<Value> value, const PropertyCallbackInfo<Value> &info)
#define GENERIC_NAMED_PROPERTY_QUERY(name) void name(Local<Name> property, const PropertyCallbackInfo<Integer> &info)
#define GENERIC_NAMED_PROPERTY_DELETER(name) void name(Local<Name> property, Local<Value> value, const PropertyCallbackInfo<Value> &info)
#define GENERIC_NAMED_PROPERTY_ENUMERATOR(name) void name(const PropertyCallbackInfo<Array> &info)

#endif // __COMMON_H__

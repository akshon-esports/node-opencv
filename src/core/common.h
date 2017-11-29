#ifndef __CORE__COMMON_H__
#define __CORE__COMMON_H__

#define BUILDING_NCV_CORE_BINDINGS

#include "../common.h"

#include "opencv2/core.hpp"

char const* const ERROR_MUST_USE_NEW = "Cannot instantiate without new";
char const* const ERROR_INVALID_ARGUMENTS = "Invalid arguments";
char const* const ERROR_NOT_IMPLEMENTED = "Not implemented";

char const* const OBJECT_KEY_X = "x";
char const* const OBJECT_KEY_Y = "y";
char const* const OBJECT_KEY_WIDTH = "width";
char const* const OBJECT_KEY_HEIGHT = "height";
char const* const OBJECT_KEY_START = "start";
char const* const OBJECT_KEY_END = "end";

#define NotImplemented(INFO) Nan::ThrowError(ERROR_NOT_IMPLEMENTED);

NCV_CORE_EXTERN cv::_InputArray ReadInputArray(Local<Value> value);
NCV_CORE_EXTERN cv::_InputOutputArray ReadInputOutputArray(Local<Value> value);
NCV_CORE_EXTERN cv::_OutputArray ReadOutputArray(Local<Value> value);

#define _TRY_CATCH_INPUTARRAY_FROM_ARGS(NAME, IND, CATCH) \
  cv::_InputArray NAME; \
  try { \
    NAME = ReadInputArray(info[IND]); \
  } catch (char const*) { \
    CATCH; \
  }

#define ASSERT_INPUTARRAY_FROM_ARGS(NAME, IND) \
  _TRY_CATCH_INPUTARRAY_FROM_ARGS(NAME, IND, return THROW_INVALID_ARGUMENT_TYPE(IND, "an InputArray"))

#define DEFAULT_INPUTARRAY_FROM_ARGS(NAME, IND, DEF) \
  _TRY_CATCH_INPUTARRAY_FROM_ARGS(NAME, IND, NAME = DEF)

#define _TRY_CATCH_INPUTOUTPUTARRAY_FROM_ARGS(NAME, IND, CATCH) \
  cv::_InputOutputArray NAME; \
  try { \
    NAME = ReadInputOutputArray(info[IND]); \
  } catch (char const*) { \
    CATCH; \
  }

#define ASSERT_INPUTOUTPUTARRAY_FROM_ARGS(NAME, IND) \
  _TRY_CATCH_INPUTOUTPUTARRAY_FROM_ARGS(NAME, IND, return THROW_INVALID_ARGUMENT_TYPE(IND, "an InputOutputArray"))

#define DEFAULT_INPUTOUTPUTARRAY_FROM_ARGS(NAME, IND, DEF) \
  _TRY_CATCH_INPUTOUTPUTARRAY_FROM_ARGS(NAME, IND, NAME = DEF)

#define _TRY_CATCH_OUTPUTARRAY_FROM_ARGS(NAME, IND, CATCH) \
  cv::_OutputArray NAME; \
  try { \
    NAME = ReadOutputArray(info[IND]); \
  } catch (char const*) { \
    CATCH; \
  }

#define ASSERT_OUTPUTARRAY_FROM_ARGS(NAME, IND) \
  _TRY_CATCH_OUTPUTARRAY_FROM_ARGS(NAME, IND, return THROW_INVALID_ARGUMENT_TYPE(IND, "an OutputArray"))

#define DEFAULT_OUTPUTARRAY_FROM_ARGS(NAME, IND, DEF) \
  _TRY_CATCH_OUTPUTARRAY_FROM_ARGS(NAME, IND, NAME = DEF)

class NCV_CORE_EXTERN HybridAsyncWorker : public Nan::AsyncWorker {
public:
  HybridAsyncWorker() : AsyncWorker{ nullptr } {}
  virtual Local<Value> GetResult();
  bool HasError() const;
  Local<Value> Error() const;
protected:
  void HandleOKCallback() override final;
  void HandleErrorCallback() override final;
};

#endif // __CORE__COMMON_H__

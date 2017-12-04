#ifndef __COMMON__COMMON_H__
#define __COMMON__COMMON_H__

#include "opencv2/core.hpp"

#define BUILDING_NCV_COMMON_BINDINGS

#include "../common.h"

namespace ncv {
  
  namespace common {

    NCV_COMMON_EXTERN extern const char * ERROR_MUST_USE_NEW;
    NCV_COMMON_EXTERN extern const char * ERROR_INVALID_ARGUMENTS;
    NCV_COMMON_EXTERN extern const char * ERROR_NOT_IMPLEMENTED;

    NCV_COMMON_EXTERN extern const char * OBJECT_KEY_X;
    NCV_COMMON_EXTERN extern const char * OBJECT_KEY_Y;
    NCV_COMMON_EXTERN extern const char * OBJECT_KEY_WIDTH;
    NCV_COMMON_EXTERN extern const char * OBJECT_KEY_HEIGHT;
    NCV_COMMON_EXTERN extern const char * OBJECT_KEY_START;
    NCV_COMMON_EXTERN extern const char * OBJECT_KEY_END;

    NCV_COMMON_EXTERN cv::_InputArray ReadInputArray(Local<Value> value);
    NCV_COMMON_EXTERN cv::_InputOutputArray ReadInputOutputArray(Local<Value> value);
    NCV_COMMON_EXTERN cv::_OutputArray ReadOutputArray(Local<Value> value);

    class NCV_COMMON_EXTERN HybridAsyncWorker : public Nan::AsyncWorker {
    public:
      HybridAsyncWorker() : AsyncWorker{ nullptr } {}
      virtual Local<Value> GetResult();
      bool HasError() const;
      Local<Value> Error() const;
    protected:
      void HandleOKCallback() override final;
      void HandleErrorCallback() override final;
    };

  }

}

#define NotImplemented Nan::ThrowError(ERROR_NOT_IMPLEMENTED);

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

using namespace ncv::common;

#endif // __COMMON__COMMON_H__

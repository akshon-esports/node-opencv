#ifndef __COMMON__RANGE_H__
#define __COMMON__RANGE_H__

#include "common.h"

#define TRY_CATCH_RANGE_FROM_ARGS(NAME, IND, CATCH) \
  cv::Range NAME; \
  try { \
    Local<Value> val = info[IND]; \
    NAME = Range::RawRange(1, &val); \
  } catch (const char *) { \
    CATCH \
  }

#define ASSERT_RANGE_FROM_ARGS(NAME, IND) \
  TRY_CATCH_RANGE_FROM_ARGS(NAME, IND, return THROW_INVALID_ARGUMENT_TYPE(IND, "a Range");)

#define DEFAULT_RANGE_FROM_ARGS(NAME, IND, DEF) \
  TRY_CATCH_RANGE_FROM_ARGS(NAME, IND, NAME = DEF;)

namespace ncv {
  
  namespace common {

    class NCV_COMMON_EXTERN Range : public Nan::ObjectWrap {
    private:
      static Nan::Persistent<FunctionTemplate> constructor;
      static Nan::Persistent<Object> all;

    public:
      cv::Range range;

      static void Init(Local<Object> target);
      static NAN_METHOD(New);

      Range() : Nan::ObjectWrap() {};

      NEW_INSTANCE_DEF;
      static Local<Object> NewInstance(cv::Range const &range);
      static Local<Object> NewInstance(int const &start, int const &end);

      HAS_INSTANCE_DEF;

      static cv::Range RawRange(int const &argc, Local<Value>* const argv);

      static NAN_GETTER(Getter);
      static NAN_SETTER(Setter);

      static NAN_METHOD(IsEmpty);
      static NAN_METHOD(Size);

      static NAN_METHOD(All);
      static NAN_METHOD(IsAll);
    };
    
  }

}

#endif // __COMMON__RANGE_H__

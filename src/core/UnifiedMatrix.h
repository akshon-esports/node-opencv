#ifndef __CORE__UNIFIED_MATRIX_H__
#define __CORE__UNIFIED_MATRIX_H__

#include "common.h"

class NCV_CORE_EXTERN UnifiedMatrix : public Nan::ObjectWrap {
public:
  static void Init(Local<Object> const &target);

  UnifiedMatrix() : Nan::ObjectWrap() {};
};

#endif // __CORE__UNIFIED_MATRIX_H__

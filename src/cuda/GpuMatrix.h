#ifndef __CORE__GPU_MATRIX_H__
#define __CORE__GPU_MATRIX_H__

#include "common.h"

class NCV_CORE_EXTERN GpuMatrix : public Nan::ObjectWrap {
private:
  static Nan::Persistent<FunctionTemplate> constructor;

public:
  cv::cuda::GpuMat mat;

  static void Init(Local<Object> const &target);

  GpuMatrix() : Nan::ObjectWrap() {};
};

#endif // __CORE__GPU_MATRIX_H__

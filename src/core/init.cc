#include "array.h"

#include <opencv2/core.hpp>

#include "../common/Matrix.h"
#include "../common/Point.h"
#include "../common/Range.h"
#include "../common/Rect.h"
#include "../common/Scalar.h"
#include "../common/Size.h"
#include "../common/UnifiedMatrix.h"

using namespace ncv::common;

extern "C" void init(Local<Object> target) {
  Nan::HandleScope scope;

  Nan::Set(target, Nan::New<String>("VERSION").ToLocalChecked(), Nan::New<String>(CV_VERSION).ToLocalChecked());

  DEFINE_CONST(CV_8U);
  DEFINE_CONST(CV_8S);
  DEFINE_CONST(CV_16U);
  DEFINE_CONST(CV_16S);
  DEFINE_CONST(CV_32S);
  DEFINE_CONST(CV_32F);
  DEFINE_CONST(CV_64F);
  DEFINE_CONST(CV_USRTYPE1);

  DEFINE_CONST(CV_8UC1);
  DEFINE_CONST(CV_8UC2);
  DEFINE_CONST(CV_8UC3);
  DEFINE_CONST(CV_8UC4);

  DEFINE_CONST(CV_8SC1);
  DEFINE_CONST(CV_8SC2);
  DEFINE_CONST(CV_8SC3);
  DEFINE_CONST(CV_8SC4);

  DEFINE_CONST(CV_16UC1);
  DEFINE_CONST(CV_16UC2);
  DEFINE_CONST(CV_16UC3);
  DEFINE_CONST(CV_16UC4);

  DEFINE_CONST(CV_16SC1);
  DEFINE_CONST(CV_16SC2);
  DEFINE_CONST(CV_16SC3);
  DEFINE_CONST(CV_16SC4);

  DEFINE_CONST(CV_32SC1);
  DEFINE_CONST(CV_32SC2);
  DEFINE_CONST(CV_32SC3);
  DEFINE_CONST(CV_32SC4);

  DEFINE_CONST(CV_32FC1);
  DEFINE_CONST(CV_32FC2);
  DEFINE_CONST(CV_32FC3);
  DEFINE_CONST(CV_32FC4);

  DEFINE_CONST(CV_64FC1);
  DEFINE_CONST(CV_64FC2);
  DEFINE_CONST(CV_64FC3);
  DEFINE_CONST(CV_64FC4);

  // access flags
  DEFINE_CONST_ENUM(ACCESS_READ);
  DEFINE_CONST_ENUM(ACCESS_WRITE);
  DEFINE_CONST_ENUM(ACCESS_RW);
  DEFINE_CONST_ENUM(ACCESS_MASK);
  DEFINE_CONST_ENUM(ACCESS_FAST);

  // u mat usage flags
  DEFINE_CONST_ENUM(USAGE_DEFAULT);
  DEFINE_CONST_ENUM(USAGE_ALLOCATE_HOST_MEMORY);
  DEFINE_CONST_ENUM(USAGE_ALLOCATE_DEVICE_MEMORY);
  DEFINE_CONST_ENUM(USAGE_ALLOCATE_SHARED_MEMORY);
  DEFINE_CONST_ENUM(__UMAT_USAGE_FLAGS_32BIT);

  // covar flags
  DEFINE_CONST_ENUM(COVAR_SCRAMBLED);
  DEFINE_CONST_ENUM(COVAR_NORMAL);
  DEFINE_CONST_ENUM(COVAR_USE_AVG);
  DEFINE_CONST_ENUM(COVAR_SCALE);
  DEFINE_CONST_ENUM(COVAR_ROWS);
  DEFINE_CONST_ENUM(COVAR_COLS);

  // hershey fonts
  DEFINE_CONST_ENUM(FONT_HERSHEY_SIMPLEX);
  DEFINE_CONST_ENUM(FONT_HERSHEY_PLAIN);
  DEFINE_CONST_ENUM(FONT_HERSHEY_DUPLEX);
  DEFINE_CONST_ENUM(FONT_HERSHEY_COMPLEX);
  DEFINE_CONST_ENUM(FONT_HERSHEY_TRIPLEX);
  DEFINE_CONST_ENUM(FONT_HERSHEY_COMPLEX_SMALL);
  DEFINE_CONST_ENUM(FONT_HERSHEY_SCRIPT_SIMPLEX);
  DEFINE_CONST_ENUM(FONT_HERSHEY_SCRIPT_COMPLEX);
  DEFINE_CONST_ENUM(FONT_ITALIC);

  // kmeans flags
  DEFINE_CONST_ENUM(KMEANS_RANDOM_CENTERS);
  DEFINE_CONST_ENUM(KMEANS_PP_CENTERS);
  DEFINE_CONST_ENUM(KMEANS_USE_INITIAL_LABELS);

  // line types
  DEFINE_CONST_ENUM(FILLED);
  DEFINE_CONST_ENUM(LINE_4);
  DEFINE_CONST_ENUM(LINE_8);
  DEFINE_CONST_ENUM(LINE_AA);

  // reduce types
  DEFINE_CONST_ENUM(REDUCE_SUM);
  DEFINE_CONST_ENUM(REDUCE_AVG);
  DEFINE_CONST_ENUM(REDUCE_MAX);
  DEFINE_CONST_ENUM(REDUCE_MIN);

  Point::Init(target);
  Range::Init(target);
  Rect::Init(target);
  Scalar::Init(target);
  Size::Init(target);
  Matrix::Init(target);
  UnifiedMatrix::Init(target);

  ncv::core::ArrayInit(target);
}

NODE_MODULE(core, init);

#ifndef __IMGPROC__OBJECT_H__
#define __IMGPROC__OBJECT_H__

#include "common.h"

namespace ncv {

  namespace imgproc {

    void ObjectInit(Local<Object> &target);

    NAN_METHOD(MatchTemplate);

  }

}

#endif // __IMGPROC__OBJECT_H__

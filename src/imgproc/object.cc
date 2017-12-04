#include "object.h"

namespace ncv {

  namespace imgproc {

    void ObjectInit(Local<Object> &target) {
      // template match modes
      DEFINE_CONST_ENUM(TM_SQDIFF);
      DEFINE_CONST_ENUM(TM_SQDIFF_NORMED);
      DEFINE_CONST_ENUM(TM_CCORR);
      DEFINE_CONST_ENUM(TM_CCORR_NORMED);
      DEFINE_CONST_ENUM(TM_CCOEFF);
      DEFINE_CONST_ENUM(TM_CCOEFF_NORMED);

      Nan::SetMethod(target, "matchTemplate", MatchTemplate);
    }

    NAN_METHOD(MatchTemplate) {
      Nan::HandleScope scope;
      ASSERT_INPUTARRAY_FROM_ARGS(image, 0);
      ASSERT_INPUTARRAY_FROM_ARGS(templ, 1);
      ASSERT_OUTPUTARRAY_FROM_ARGS(result, 2);
      ASSERT_INT_FROM_ARGS(method, 3);
      DEFAULT_OUTPUTARRAY_FROM_ARGS(mask, 4, cv::noArray());
      TRY_CATCH_THROW_OPENCV(cv::matchTemplate(image, templ, result, method, mask));
    }

  }

}

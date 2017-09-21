#include "common.h"

#include "Contour.h"
#include "Contours.h"

#include "filter.h"
#include "transform.h"
#include "misc.h"
#include "draw.h"
#include "colormap.h"
#include "subdiv2d.h"
#include "hist.h"
#include "shape.h"
#include "motion.h"
#include "feature.h"
#include "object.h"

namespace ncv {

  namespace imgproc {

    extern "C" void init(Local<Object> target) {
      Nan::HandleScope scope;

      Contour::Init(target);
      Contours::Init(target);
  
      FilterInit(target);
      TransformInit(target);
      MiscInit(target);
      DrawInit(target);
      ColormapInit(target);
      Subdiv2dInit(target);
      HistInit(target);
      ShapeInit(target);
      MotionInit(target);
      FeatureInit(target);
      ObjectInit(target);
    }

    NODE_MODULE(imgproc, init);

  }

}
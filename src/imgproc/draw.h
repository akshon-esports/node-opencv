#ifndef __IMGPROC__DRAW_H__
#define __IMGPROC__DRAW_H__

#include "common.h"

namespace ncv {

  namespace imgproc {

    void DrawInit(Local<Object> &target);

    NAN_METHOD(ArrowedLine);
    NAN_METHOD(Circle);
    NAN_METHOD(ClipLine);
    NAN_METHOD(DrawContours);
    NAN_METHOD(DrawMarker);
    NAN_METHOD(Ellipse);
    NAN_METHOD(Ellipse2Poly);
    NAN_METHOD(FillConvexPoly);
    NAN_METHOD(FillPoly);
    NAN_METHOD(GetTextSize);
    NAN_METHOD(Line);
    NAN_METHOD(Polylines);
    NAN_METHOD(PutText);
    NAN_METHOD(Rectangle);

  }

}

#endif // __IMGPROC__DRAW_H__

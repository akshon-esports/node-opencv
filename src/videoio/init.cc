#include "common.h"

#include "VideoCapture.h"
#include "VideoWriter.h"

namespace ncv {

  namespace videoio {

    extern "C" void init(Local<Object> target) {
      Nan::HandleScope scope;

      VideoCapture::Init(target);
      VideoWriter::Init(target);
    }

    NODE_MODULE(videoio, init);

  }

}

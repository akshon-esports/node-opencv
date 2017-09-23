#include "common.h"

#include "OCRTesseract.h"

namespace ncv {

  namespace text {

    extern "C" void init(Local<Object> target) {
      Nan::HandleScope scope;

      // component level
      DEFINE_CONST_NAMESPACED_ENUM(cv::text, OCR_LEVEL_WORD);
      DEFINE_CONST_NAMESPACED_ENUM(cv::text, OCR_LEVEL_TEXTLINE);

      // classifier type
      DEFINE_CONST_NAMESPACED_ENUM(cv::text, OCR_KNN_CLASSIFIER);
      DEFINE_CONST_NAMESPACED_ENUM(cv::text, OCR_CNN_CLASSIFIER);

      // decoder mode
      DEFINE_CONST_NAMESPACED_ENUM(cv::text, OCR_DECODER_VITERBI);

      // ocr engine mode
      DEFINE_CONST_NAMESPACED_ENUM(cv::text, OEM_TESSERACT_ONLY);
      DEFINE_CONST_NAMESPACED_ENUM(cv::text, OEM_CUBE_ONLY);
      DEFINE_CONST_NAMESPACED_ENUM(cv::text, OEM_TESSERACT_CUBE_COMBINED);
      DEFINE_CONST_NAMESPACED_ENUM(cv::text, OEM_DEFAULT);

      // page seg mode
      DEFINE_CONST_NAMESPACED_ENUM(cv::text, PSM_OSD_ONLY);
      DEFINE_CONST_NAMESPACED_ENUM(cv::text, PSM_AUTO_OSD);
      DEFINE_CONST_NAMESPACED_ENUM(cv::text, PSM_AUTO_ONLY);
      DEFINE_CONST_NAMESPACED_ENUM(cv::text, PSM_AUTO);
      DEFINE_CONST_NAMESPACED_ENUM(cv::text, PSM_SINGLE_COLUMN);
      DEFINE_CONST_NAMESPACED_ENUM(cv::text, PSM_SINGLE_BLOCK_VERT_TEXT);
      DEFINE_CONST_NAMESPACED_ENUM(cv::text, PSM_SINGLE_BLOCK);
      DEFINE_CONST_NAMESPACED_ENUM(cv::text, PSM_SINGLE_LINE);
      DEFINE_CONST_NAMESPACED_ENUM(cv::text, PSM_SINGLE_WORD);
      DEFINE_CONST_NAMESPACED_ENUM(cv::text, PSM_CIRCLE_WORD);
      DEFINE_CONST_NAMESPACED_ENUM(cv::text, PSM_SINGLE_CHAR);

      OCRTesseract::Init(target);
    }

    NODE_MODULE(text, init);

  }

}

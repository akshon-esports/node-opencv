#include "OCRTesseract.h"
#include "../core/Matrix.h"
#include "../core/Rect.h"

Nan::Persistent<FunctionTemplate> OCRTesseract::constructor;

void OCRTesseract::Init(Local<Object> target) {
  Nan::HandleScope scope;

  // Constructor
  Local<FunctionTemplate> ctor = Nan::New<FunctionTemplate>(New);
  constructor.Reset(ctor);

  ctor->SetClassName(Nan::New("OCRTesseract").ToLocalChecked());

  // Instance
  Local<ObjectTemplate> inst = ctor->InstanceTemplate();
  inst->SetInternalFieldCount(1);

  // Prototype Methods
  Nan::SetPrototypeMethod(ctor, "run", Run);

  Nan::Set(target, Nan::New("OCRTesseract").ToLocalChecked(), ctor->GetFunction());
}

NAN_METHOD(OCRTesseract::New) {
  if (!info.IsConstructCall()) {
    return Nan::ThrowTypeError(ERROR_MUST_USE_NEW);
  }

  FUNCTION_REQUIRE_ARGUMENTS_RANGE(0, 5);
  DEFAULT_STRING_FROM_ARGS(datapath, 0, "");
  DEFAULT_STRING_FROM_ARGS(langauge, 1, "");
  DEFAULT_STRING_FROM_ARGS(char_whitelist, 2, "");
  DEFAULT_INT_FROM_ARGS(oem, 3, cv::text::OEM_DEFAULT);
  DEFAULT_INT_FROM_ARGS(psmode, 4, cv::text::PSM_AUTO);

  OCRTesseract* pt = new OCRTesseract();
  TRY_CATCH_THROW_OPENCV(pt->tesseract = cv::text::OCRTesseract::create(
    datapath.empty() ? 0 : datapath.c_str(),
    langauge.empty() ? 0 : langauge.c_str(),
    char_whitelist.empty() ? 0 : char_whitelist.c_str(),
    oem,
    psmode
  ));
  pt->Wrap(info.This());

  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(OCRTesseract::SetWhitelist) {
  FUNCTION_REQUIRE_ARGUMENTS(1);
  SETUP_FUNCTION(OCRTesseract);
  ASSERT_STRING_FROM_ARGS(whitelist, 0);
  TRY_CATCH_THROW_OPENCV(self->tesseract->setWhiteList(whitelist.c_str()));
}

NAN_METHOD(OCRTesseract::Run) {
  FUNCTION_REQUIRE_ARGUMENTS_RANGE(1, 3);
  SETUP_FUNCTION(OCRTesseract);
  ASSERT_MATRIX_FROM_ARGS(image, 0);

  int argumentOffset = 0;
  cv::Mat mask;
  try {
    Local<Value> val = info[1];
    mask = Matrix::RawMatrix(1, &val);
    argumentOffset += 1;
  } catch (const char*) {}

  int component_level;
  bool output_components = false;
  std::vector<cv::Rect> component_rects;
  std::vector<std::string> component_texts;
  std::vector<float> component_confidences;
  if (info.Length() > 1 + argumentOffset && info[1 + argumentOffset]->IsNumber()) {
    component_level = info[1 + argumentOffset]->Int32Value();
    output_components = true;
  } else {
    component_level = cv::text::OCR_LEVEL_WORD;
  }

  std::string output;
  TRY_CATCH_THROW_OPENCV(
    if (argumentOffset == 1) {
      self->tesseract->run(image->mat, mask, output, output_components ? &component_rects : NULL, output_components ? &component_texts : NULL, output_components ? &component_confidences : NULL, component_level);
    } else {
      self->tesseract->run(image->mat, output, output_components ? &component_rects : NULL, output_components ? &component_texts : NULL, output_components ? &component_confidences : NULL, component_level);
    }
  );

  Local<Object> out = Nan::New<Object>();
  Nan::Set(out, Nan::New<String>("output").ToLocalChecked(), Nan::New<String>(output).ToLocalChecked());
  if (output_components) {
    Local<Array> rects = Nan::New<Array>();
    for (cv::Rect rect : component_rects) {
      Nan::Set(rects, rects->Length(), Rect::NewInstance(rect));
    }
    Nan::Set(out, Nan::New<String>("rects").ToLocalChecked(), rects);

    Local<Array> texts = Nan::New<Array>();
    for (std::string text : component_texts) {
      Nan::Set(texts, texts->Length(), Nan::New<String>(text).ToLocalChecked());
    }
    Nan::Set(out, Nan::New<String>("texts").ToLocalChecked(), texts);

    Local<Array> confidences = Nan::New<Array>();
    for (float confidence : component_confidences) {
      Nan::Set(confidences, confidences->Length(), Nan::New<Number>(confidence));
    }
    Nan::Set(out, Nan::New<String>("confidences").ToLocalChecked(), confidences);
  }

  info.GetReturnValue().Set(out);
}

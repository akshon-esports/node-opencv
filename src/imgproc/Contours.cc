#include "Contours.h"

#include <iostream>

#include "Contour.h"

Nan::Persistent<FunctionTemplate> Contours::constructor;

void Contours::Init(Local<Object> target) {
  Nan::HandleScope scope;

  // Class/contructor
  Local<FunctionTemplate> ctor = Nan::New<FunctionTemplate>(Contours::New);
  constructor.Reset(ctor);
  ctor->SetClassName(Nan::New("Contours").ToLocalChecked());

  // Instance
  Local<ObjectTemplate> inst = ctor->InstanceTemplate();
  inst->SetInternalFieldCount(1);
  Nan::SetIndexedPropertyHandler(inst, IndexGetter, 0, IndexQuery, 0, IndexEnumerator);
  Nan::SetAccessor(inst, Nan::New<String>("length").ToLocalChecked(), LengthGetter);

  target->Set(Nan::New("Contours").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(Contours::New) {
  Nan::HandleScope scope;

  if (info.This()->InternalFieldCount() == 0) {
    Nan::ThrowTypeError("Cannot instantiate without new");
  }

  Contours *contours = new Contours();

  contours->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

Local<Object> Contours::NewInstance(const std::vector<std::vector<cv::Point>> &contours, const std::vector<cv::Vec4i> &hierarchy) {
  Nan::EscapableHandleScope scope;

  Local<Object> inst = NewInstance();

  Contours *contour = UNWRAP_OBJECT(Contours, inst);
  contour->contours = contours;
  contour->hierarchy = hierarchy;

  return scope.Escape(inst);
}

NAN_INDEX_GETTER(Contours::IndexGetter) {
  Contours *self = UNWRAP_OBJECT(Contours, info.This());

  if (index < self->contours.size()) {
    info.GetReturnValue().Set(Contour::NewInstance(self->contours, self->hierarchy, index));
  }
}

NAN_INDEX_QUERY(Contours::IndexQuery) {
  info.GetReturnValue().Set(Nan::New<Integer>(ReadOnly));
}

NAN_INDEX_ENUMERATOR(Contours::IndexEnumerator) {
  Contours *self = UNWRAP_OBJECT(Contours, info.This());

  v8::Local<v8::Array> arr = Nan::New<v8::Array>();
  for (int i = 0; i < self->contours.size(); i++) {
    Nan::Set(arr, i, Nan::New(std::to_string(i)).ToLocalChecked());
  }
  info.GetReturnValue().Set(arr);
}

NAN_GETTER(Contours::LengthGetter) {
  Contours *self = UNWRAP_OBJECT(Contours, info.This());
  info.GetReturnValue().Set(Nan::New<Number>(self->contours.size()));
}

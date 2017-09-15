#include "VideoWriter.h"

Nan::Persistent<FunctionTemplate> VideoWriter::constructor;

void VideoWriter::Init(Local<Object> target) {
  Nan::HandleScope scope;

  // Class/contructor
  Local<FunctionTemplate> ctor = Nan::New<FunctionTemplate>(New);
  constructor.Reset(ctor);
  ctor->SetClassName(Nan::New("VideoWriter").ToLocalChecked());

  Nan::SetPrototypeMethod(ctor, "get", Get);
  Nan::SetPrototypeMethod(ctor, "isOpened", IsOpened);
  Nan::SetPrototypeMethod(ctor, "release", Release);
  Nan::SetPrototypeMethod(ctor, "set", Set);
  Nan::SetPrototypeMethod(ctor, "write", Write);

  // Instance
  Local<ObjectTemplate> inst = ctor->InstanceTemplate();
  inst->SetInternalFieldCount(1);

  Nan::Set(target, Nan::New("VideoWriter").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(VideoWriter::New) {
  NotImplemented(info);
}

NAN_METHOD(VideoWriter::Get) {
  NotImplemented(info);
}

NAN_METHOD(VideoWriter::IsOpened) {
  NotImplemented(info);
}

NAN_METHOD(VideoWriter::Release) {
  NotImplemented(info);
}

NAN_METHOD(VideoWriter::Set) {
  NotImplemented(info);
}

NAN_METHOD(VideoWriter::Write) {
  NotImplemented(info);
}

#include "common.h"
#include "async.h"

Local<Value> HybridAsyncWorker::GetResult() {
  Nan::EscapableHandleScope scope;
  return scope.Escape(Nan::Undefined());
}

inline bool HybridAsyncWorker::HasError() const {
  return ErrorMessage() != NULL;
}

Local<Value> HybridAsyncWorker::Error() const {
  Nan::EscapableHandleScope scope;
  return scope.Escape(Nan::Error(ErrorMessage()));
}

void HybridAsyncWorker::HandleOKCallback() {
  Nan::HandleScope scope;

  Local<Value> result = GetResult();

  Local<Value> callback_or_resolver = GetFromPersistent(0u);
  if (callback_or_resolver->IsFunction()) {
    Local<Value> argv[2] = { Nan::Undefined(), result };

    Nan::TryCatch try_catch;
    Local<Function>::Cast(callback_or_resolver)->Call(Nan::GetCurrentContext()->Global(), 2, argv);
    if (try_catch.HasCaught()) {
      Nan::FatalException(try_catch);
    }
  } else {
    Local<Promise::Resolver>::Cast(callback_or_resolver)->Resolve(Nan::GetCurrentContext(), result);
    Isolate::GetCurrent()->RunMicrotasks();
  }
}

void HybridAsyncWorker::HandleErrorCallback() {
  Nan::HandleScope scope;

  Local<Value> error = Error();

  Local<Value> callback_or_resolver = GetFromPersistent(0u);
  if (callback_or_resolver->IsFunction()) {
    Local<Value> argv[1]{ error };

    Nan::TryCatch try_catch;
    Nan::CallAsFunction(callback_or_resolver->ToObject(), Nan::GetCurrentContext()->Global(), 1, argv);
    if (try_catch.HasCaught()) {
      Nan::FatalException(try_catch);
    }
  } else {
    Local<Promise::Resolver>::Cast(callback_or_resolver)->Reject(error);
    Isolate::GetCurrent()->RunMicrotasks();
  }
}

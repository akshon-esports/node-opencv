#ifndef __COMMON_ASYNC_H__
#define __COMMON_ASYNC_H__

namespace ncv {

  namespace common {

    class NCV_COMMON_EXTERN HybridAsyncWorker : public Nan::AsyncWorker {
    public:
      HybridAsyncWorker() : AsyncWorker{ nullptr } {}
      virtual Local<Value> GetResult();
      bool HasError() const;
      Local<Value> Error() const;
    protected:
      void HandleOKCallback() override final;
      void HandleErrorCallback() override final;
    };

  }

}

#endif // __COMMON_ASYNC_H__

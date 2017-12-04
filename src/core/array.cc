#include "array.h"

namespace ncv {

  namespace core {

    NAN_METHOD(Absdiff) {
      NotImplemented;
    }

    NAN_METHOD(Add) {
      NotImplemented;
    }

    NAN_METHOD(AddWeighted) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(6, 7);
      Nan::HandleScope scope;
      ASSERT_INPUTARRAY_FROM_ARGS(src1, 0);
      ASSERT_DOUBLE_FROM_ARGS(alpha, 1);
      ASSERT_INPUTARRAY_FROM_ARGS(src2, 2);
      ASSERT_DOUBLE_FROM_ARGS(beta, 3);
      ASSERT_DOUBLE_FROM_ARGS(gamma, 4);
      ASSERT_OUTPUTARRAY_FROM_ARGS(dst, 5);
      DEFAULT_INT_FROM_ARGS(dtype, 6, -1);
      TRY_CATCH_THROW_OPENCV(cv::addWeighted(src1, alpha, src2, beta, gamma, dst, dtype));
    }

    NAN_METHOD(BatchDistance) {
      NotImplemented;
    }

    class BitwiseAndHybridAsyncWorker : public HybridAsyncWorker {
    public:
      BitwiseAndHybridAsyncWorker(cv::_InputArray src1, cv::_InputArray src2, cv::_OutputArray dst, cv::_InputArray mask) : HybridAsyncWorker() {
        
      }

      void Execute() override {
        try {
          cv::bitwise_and(src1, src2, dst, mask);
        } catch (cv::Exception& e) {
          return SetErrorMessage(e.what());
        }
      }
    private:
      cv::_InputArray src1;
      cv::_InputArray src2;
      cv::_OutputArray dst;
      cv::_InputArray mask;
    };

    NAN_METHOD(BitwiseAnd) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(3, 4);
      Nan::HandleScope scope;
      ASSERT_INPUTARRAY_FROM_ARGS(src1, 0);
      ASSERT_INPUTARRAY_FROM_ARGS(src2, 1);
      ASSERT_OUTPUTARRAY_FROM_ARGS(dst, 2);
      DEFAULT_INPUTARRAY_FROM_ARGS(mask, 3, cv::noArray());
      TRY_CATCH_THROW_OPENCV(cv::bitwise_and(src1, src2, dst, mask));
    }

    NAN_METHOD(BitwiseAnd_Sync) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(3, 4);
      Nan::HandleScope scope;
      ASSERT_INPUTARRAY_FROM_ARGS(src1, 0);
      ASSERT_INPUTARRAY_FROM_ARGS(src2, 1);
      ASSERT_OUTPUTARRAY_FROM_ARGS(dst, 2);
      DEFAULT_INPUTARRAY_FROM_ARGS(mask, 3, cv::noArray());
      TRY_CATCH_THROW_OPENCV(cv::bitwise_and(src1, src2, dst, mask));
    }

    NAN_METHOD(BitwiseNot) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(2, 3);
      Nan::HandleScope scope;
      ASSERT_INPUTARRAY_FROM_ARGS(src1, 0);
      ASSERT_OUTPUTARRAY_FROM_ARGS(dst, 1);
      DEFAULT_INPUTARRAY_FROM_ARGS(mask, 2, cv::noArray());
      TRY_CATCH_THROW_OPENCV(cv::bitwise_not(src1, dst, mask));
    }

    NAN_METHOD(BitwiseOr) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(3, 4);
      Nan::HandleScope scope;
      ASSERT_INPUTARRAY_FROM_ARGS(src1, 0);
      ASSERT_INPUTARRAY_FROM_ARGS(src2, 1);
      ASSERT_OUTPUTARRAY_FROM_ARGS(dst, 2);
      DEFAULT_INPUTARRAY_FROM_ARGS(mask, 3, cv::noArray());
      TRY_CATCH_THROW_OPENCV(cv::bitwise_or(src1, src2, dst, mask));
    }

    NAN_METHOD(BitwiseXor) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(3, 4);
      Nan::HandleScope scope;
      ASSERT_INPUTARRAY_FROM_ARGS(src1, 0);
      ASSERT_INPUTARRAY_FROM_ARGS(src2, 1);
      ASSERT_OUTPUTARRAY_FROM_ARGS(dst, 2);
      DEFAULT_INPUTARRAY_FROM_ARGS(mask, 3, cv::noArray());
      TRY_CATCH_THROW_OPENCV(cv::bitwise_xor(src1, src2, dst, mask));
    }

    NAN_METHOD(BorderInterpolate) {
      NotImplemented
    }

    NAN_METHOD(CalcCovarMatrix) {
      NotImplemented
    }

    NAN_METHOD(CartToPolar) {
      NotImplemented
    }

    NAN_METHOD(CheckRange) {
      NotImplemented
    }

    NAN_METHOD(Compare) {
      NotImplemented
    }

    NAN_METHOD(CompleteSymm) {
      NotImplemented
    }

    NAN_METHOD(ConvertFp16) {
      NotImplemented
    }

    NAN_METHOD(ConvertScaleAbs) {
      NotImplemented
    }

    NAN_METHOD(CopyMakeBorder) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(7, 8);
      ASSERT_INPUTARRAY_FROM_ARGS(src, 0);
      ASSERT_OUTPUTARRAY_FROM_ARGS(dst, 1);
      ASSERT_INT_FROM_ARGS(top, 2);
      ASSERT_INT_FROM_ARGS(bottom, 3);
      ASSERT_INT_FROM_ARGS(left, 4);
      ASSERT_INT_FROM_ARGS(right, 5);
      ASSERT_INT_FROM_ARGS(borderType, 6);
      DEFAULT_SCALAR_FROM_ARGS(value, 7, cv::Scalar());
      TRY_CATCH_THROW_OPENCV(cv::copyMakeBorder(src, dst, top, bottom, left, right, borderType, value));
    }

    NAN_METHOD(CountNonZero) {
      NotImplemented
    }

    NAN_METHOD(Dct) {
      NotImplemented
    }

    NAN_METHOD(Determinant) {
      NotImplemented
    }

    NAN_METHOD(Dft) {
      NotImplemented
    }

    NAN_METHOD(Divide) {
      NotImplemented
    }

    NAN_METHOD(Eigen) {
      NotImplemented
    }

    NAN_METHOD(Exp) {
      NotImplemented
    }

    NAN_METHOD(ExtractChannel) {
      NotImplemented
    }

    NAN_METHOD(FindNonZero) {
      NotImplemented
    }

    NAN_METHOD(Flip) {
      FUNCTION_REQUIRE_ARGUMENTS(3);
      ASSERT_INPUTARRAY_FROM_ARGS(src, 0);
      ASSERT_OUTPUTARRAY_FROM_ARGS(dst, 1);
      ASSERT_INT_FROM_ARGS(flipCode, 2);
      TRY_CATCH_THROW_OPENCV(cv::flip(src, dst, flipCode));
    }

    NAN_METHOD(Gemm) {
      NotImplemented
    }

    NAN_METHOD(GetOptimalDFTSize) {
      NotImplemented
    }

    NAN_METHOD(Hconcat) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(2, 3);
      if (info.Length() == 2) {
        ASSERT_ARRAY_FROM_ARGS(mats, 0);
        std::vector<cv::_InputArray> src;
        for (unsigned i = 0; i < mats->Length(); i++) {
          Local<Value> mat = Nan::Get(mats, i).ToLocalChecked();
          try {
            cv::_InputArray in = ReadInputArray(mat);
            src.push_back(in);
          } catch (char const*) {
            return Nan::ThrowError(ERROR_INVALID_ARGUMENTS);
          }
        }
        ASSERT_OUTPUTARRAY_FROM_ARGS(dst, 1);
        TRY_CATCH_THROW_OPENCV(cv::hconcat(src, dst));
      } else {
        ASSERT_INPUTARRAY_FROM_ARGS(src1, 0);
        ASSERT_INPUTARRAY_FROM_ARGS(src2, 1);
        ASSERT_OUTPUTARRAY_FROM_ARGS(dst, 2);
        TRY_CATCH_THROW_OPENCV(cv::hconcat(src1, src2, dst));
      }
    }

    NAN_METHOD(Idct) {
      NotImplemented
    }

    NAN_METHOD(Idft) {
      NotImplemented
    }

    NAN_METHOD(InRange) {
      FUNCTION_REQUIRE_ARGUMENTS(4);
      Nan::HandleScope scope;
      ASSERT_INPUTARRAY_FROM_ARGS(src1, 0);
      ASSERT_INPUTARRAY_FROM_ARGS(lowerb, 1);
      ASSERT_INPUTARRAY_FROM_ARGS(upperb, 2);
      ASSERT_OUTPUTARRAY_FROM_ARGS(dst, 3);
      TRY_CATCH_THROW_OPENCV(cv::inRange(src1, lowerb, upperb, dst));
    }

    NAN_METHOD(InsertChannel) {
      NotImplemented
    }

    NAN_METHOD(Invert) {
      NotImplemented
    }

    NAN_METHOD(Log) {
      NotImplemented
    }

    NAN_METHOD(LUT) {
      NotImplemented
    }

    NAN_METHOD(Magnitude) {
      NotImplemented
    }

    NAN_METHOD(Mahalanobis) {
      NotImplemented
    }

    NAN_METHOD(Max) {
      NotImplemented
    }

    NAN_METHOD(Mean) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(1, 2);
      Nan::HandleScope scope;
      ASSERT_INPUTARRAY_FROM_ARGS(src, 0);
      DEFAULT_INPUTARRAY_FROM_ARGS(mask, 1, cv::noArray());

      TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Scalar::NewInstance(cv::mean(src, mask))));
    }

    NAN_METHOD(MeanStdDev) {
      NotImplemented
    }

    NAN_METHOD(Merge) {
      NotImplemented
    }

    NAN_METHOD(Min) {
      NotImplemented
    }

    NAN_METHOD(MinMaxIdx) {
      NotImplemented
    }

    NAN_METHOD(MinMaxLoc) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(1, 2);
      Nan::HandleScope scope;
      ASSERT_INPUTARRAY_FROM_ARGS(src, 0);
      DEFAULT_INPUTARRAY_FROM_ARGS(mask, 1, cv::noArray());

      double minVal, maxVal;
      cv::Point minLoc, maxLoc;
      TRY_CATCH_THROW_OPENCV(cv::minMaxLoc(src, &minVal, &maxVal, &minLoc, &maxLoc, mask));
      
      Local<Object> out = Nan::New<Object>();
      Nan::Set(out, Nan::New<String>("minVal").ToLocalChecked(), Nan::New<Number>(minVal));
      Nan::Set(out, Nan::New<String>("maxVal").ToLocalChecked(), Nan::New<Number>(maxVal));
      Nan::Set(out, Nan::New<String>("minLoc").ToLocalChecked(), Point::NewInstance(minLoc));
      Nan::Set(out, Nan::New<String>("maxLoc").ToLocalChecked(), Point::NewInstance(maxLoc));

      info.GetReturnValue().Set(out);
    }

    NAN_METHOD(MixChannels) {
      NotImplemented
    }

    NAN_METHOD(MulSpectrums) {
      NotImplemented
    }

    NAN_METHOD(Multiply) {
      NotImplemented
    }

    NAN_METHOD(MulTransposed) {
      NotImplemented
    }

    NAN_METHOD(Norm) {
      NotImplemented
    }

    NAN_METHOD(Normalize) {
      NotImplemented
    }

    NAN_METHOD(PatchNaNs) {
      NotImplemented
    }

    NAN_METHOD(PCABackProject) {
      NotImplemented
    }

    NAN_METHOD(PCACompute) {
      NotImplemented
    }

    NAN_METHOD(PCAProject) {
      NotImplemented
    }

    NAN_METHOD(PerspectiveTransform) {
      NotImplemented
    }

    NAN_METHOD(Phase) {
      NotImplemented
    }

    NAN_METHOD(PolarToCart) {
      NotImplemented
    }

    NAN_METHOD(Pow) {
      FUNCTION_REQUIRE_ARGUMENTS(2);
      ASSERT_INPUTARRAY_FROM_ARGS(src, 0);
      ASSERT_DOUBLE_FROM_ARGS(power, 1);
      ASSERT_OUTPUTARRAY_FROM_ARGS(dst, 2);
      TRY_CATCH_THROW_OPENCV(cv::pow(src, power, dst));
    }

    NAN_METHOD(PSNR) {
      NotImplemented
    }

    NAN_METHOD(Randn) {
      NotImplemented
    }

    NAN_METHOD(RandShuffle) {
      NotImplemented
    }

    NAN_METHOD(Randu) {
      NotImplemented
    }

    NAN_METHOD(Reduce) {
      NotImplemented
    }

    NAN_METHOD(Repeat) {
      NotImplemented
    }

    NAN_METHOD(Rotate) {
      NotImplemented
    }

    NAN_METHOD(ScaleAdd) {
      NotImplemented
    }

    NAN_METHOD(SetIdentity) {
      NotImplemented
    }

    NAN_METHOD(SetRNGSeed) {
      NotImplemented
    }

    NAN_METHOD(Solve) {
      NotImplemented
    }

    NAN_METHOD(SolveCubic) {
      NotImplemented
    }

    NAN_METHOD(SolvePoly) {
      NotImplemented
    }

    NAN_METHOD(Sort) {
      NotImplemented
    }

    NAN_METHOD(SortIdx) {
      NotImplemented
    }

    NAN_METHOD(Split) {
      FUNCTION_REQUIRE_ARGUMENTS(1);
      ASSERT_INPUTARRAY_FROM_ARGS(m, 0);
      std::vector<cv::Mat> mv;
      TRY_CATCH_THROW_OPENCV(cv::split(m, mv));

      Local<Array> out = Nan::New<Array>();
      for (const cv::Mat &m : mv) {
        Nan::Set(out, out->Length(), Matrix::NewInstance(m));
      }

      info.GetReturnValue().Set(out);
    }

    NAN_METHOD(Sqrt) {
      FUNCTION_REQUIRE_ARGUMENTS(2);
      ASSERT_INPUTARRAY_FROM_ARGS(src, 0);
      ASSERT_OUTPUTARRAY_FROM_ARGS(dst, 1);
      TRY_CATCH_THROW_OPENCV(cv::sqrt(src, dst));
    }

    NAN_METHOD(Subtract) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(3, 5);
      ASSERT_INPUTARRAY_FROM_ARGS(src1, 0);
      ASSERT_INPUTARRAY_FROM_ARGS(src2, 1);
      ASSERT_OUTPUTARRAY_FROM_ARGS(dst, 2);
      DEFAULT_INPUTARRAY_FROM_ARGS(mask, 3, cv::noArray());
      DEFAULT_INT_FROM_ARGS(dtype, 3, -1);
      TRY_CATCH_THROW_OPENCV(cv::subtract(src1, src2, dst, mask, dtype));
    }

    NAN_METHOD(Sum) {
      FUNCTION_REQUIRE_ARGUMENTS(1);
      ASSERT_INPUTARRAY_FROM_ARGS(src, 0);
      TRY_CATCH_THROW_OPENCV(info.GetReturnValue().Set(Scalar::NewInstance(cv::sum(src))));
    }

    NAN_METHOD(SVBackSubst) {
      NotImplemented
    }

    NAN_METHOD(SVDecomp) {
      NotImplemented
    }

    NAN_METHOD(TheRNG) {
      NotImplemented
    }

    NAN_METHOD(Trace) {
      NotImplemented
    }

    NAN_METHOD(Transform) {
      NotImplemented
    }

    NAN_METHOD(Transpose) {
      NotImplemented
    }

    NAN_METHOD(Vconcat) {
      FUNCTION_REQUIRE_ARGUMENTS_RANGE(2, 3);
      if (info.Length() == 2) {
        ASSERT_ARRAY_FROM_ARGS(mats, 0);
        std::vector<cv::_InputArray> src;
        for (unsigned i = 0; i < mats->Length(); i++) {
          Local<Value> mat = Nan::Get(mats, i).ToLocalChecked();
          try {
            cv::_InputArray in = ReadInputArray(mat);
            src.push_back(in);
          } catch (char const*) {
            return Nan::ThrowError(ERROR_INVALID_ARGUMENTS);
          }
        }
        ASSERT_OUTPUTARRAY_FROM_ARGS(dst, 1);
        TRY_CATCH_THROW_OPENCV(cv::vconcat(src, dst));
      } else {
        ASSERT_INPUTARRAY_FROM_ARGS(src1, 0);
        ASSERT_INPUTARRAY_FROM_ARGS(src2, 1);
        ASSERT_OUTPUTARRAY_FROM_ARGS(dst, 2);
        TRY_CATCH_THROW_OPENCV(cv::vconcat(src1, src2, dst));
      }
    }

    void ArrayInit(Local<Object> &target) {
      // border types
      DEFINE_CONST_ENUM(BORDER_CONSTANT);
      DEFINE_CONST_ENUM(BORDER_REPLICATE);
      DEFINE_CONST_ENUM(BORDER_REFLECT);
      DEFINE_CONST_ENUM(BORDER_WRAP);
      DEFINE_CONST_ENUM(BORDER_REFLECT_101);
      DEFINE_CONST_ENUM(BORDER_TRANSPARENT);
      DEFINE_CONST_ENUM(BORDER_REFLECT101);
      DEFINE_CONST_ENUM(BORDER_DEFAULT);
      DEFINE_CONST_ENUM(BORDER_ISOLATED);

      // cmp types
      DEFINE_CONST_ENUM(CMP_EQ);
      DEFINE_CONST_ENUM(CMP_GT);
      DEFINE_CONST_ENUM(CMP_GE);
      DEFINE_CONST_ENUM(CMP_LT);
      DEFINE_CONST_ENUM(CMP_LE);
      DEFINE_CONST_ENUM(CMP_NE);

      // decomp types
      DEFINE_CONST_ENUM(DECOMP_LU);
      DEFINE_CONST_ENUM(DECOMP_SVD);
      DEFINE_CONST_ENUM(DECOMP_EIG);
      DEFINE_CONST_ENUM(DECOMP_CHOLESKY);
      DEFINE_CONST_ENUM(DECOMP_QR);
      DEFINE_CONST_ENUM(DECOMP_NORMAL);

      // dft flags
      DEFINE_CONST_ENUM(DFT_INVERSE);
      DEFINE_CONST_ENUM(DFT_SCALE);
      DEFINE_CONST_ENUM(DFT_ROWS);
      DEFINE_CONST_ENUM(DFT_COMPLEX_OUTPUT);
      DEFINE_CONST_ENUM(DFT_REAL_OUTPUT);
      DEFINE_CONST_ENUM(DFT_COMPLEX_INPUT);
      DEFINE_CONST_ENUM(DCT_INVERSE);
      DEFINE_CONST_ENUM(DCT_ROWS);

      // gemm flags
      DEFINE_CONST_ENUM(GEMM_1_T);
      DEFINE_CONST_ENUM(GEMM_2_T);
      DEFINE_CONST_ENUM(GEMM_3_T);

      // norm types
      DEFINE_CONST_ENUM(NORM_INF);
      DEFINE_CONST_ENUM(NORM_L1);
      DEFINE_CONST_ENUM(NORM_L2);
      DEFINE_CONST_ENUM(NORM_L2SQR);
      DEFINE_CONST_ENUM(NORM_HAMMING);
      DEFINE_CONST_ENUM(NORM_HAMMING2);
      DEFINE_CONST_ENUM(NORM_TYPE_MASK);
      DEFINE_CONST_ENUM(NORM_RELATIVE);
      DEFINE_CONST_ENUM(NORM_MINMAX);

      // rotate flags
      DEFINE_CONST_ENUM(ROTATE_90_CLOCKWISE);
      DEFINE_CONST_ENUM(ROTATE_180);
      DEFINE_CONST_ENUM(ROTATE_90_COUNTERCLOCKWISE);

      Nan::SetMethod(target, "absdiff", Absdiff);
      Nan::SetMethod(target, "add", Add);
      Nan::SetMethod(target, "addWeighted", AddWeighted);
      Nan::SetMethod(target, "batchDistance", BatchDistance);
      Nan::SetMethod(target, "bitwiseAnd", BitwiseAnd);
      Nan::SetMethod(target, "bitwiseAndAsync", BitwiseAnd_Sync);
      Nan::SetMethod(target, "bitwiseNot", BitwiseNot);
      Nan::SetMethod(target, "bitwiseOr", BitwiseOr);
      Nan::SetMethod(target, "bitwiseXor", BitwiseXor);
      Nan::SetMethod(target, "borderInterpolate", BorderInterpolate);
      Nan::SetMethod(target, "calcCovarMatrix", CalcCovarMatrix);
      Nan::SetMethod(target, "cartToPolar", CartToPolar);
      Nan::SetMethod(target, "checkRange", CheckRange);
      Nan::SetMethod(target, "compare", Compare);
      Nan::SetMethod(target, "completeSymm", CompleteSymm);
      Nan::SetMethod(target, "convertFp16", ConvertFp16);
      Nan::SetMethod(target, "convertScaleAbs", ConvertScaleAbs);
      Nan::SetMethod(target, "copyMakeBorder", CopyMakeBorder);
      Nan::SetMethod(target, "countNonZero", CountNonZero);
      Nan::SetMethod(target, "dct", Dct);
      Nan::SetMethod(target, "determinant", Determinant);
      Nan::SetMethod(target, "dft", Dft);
      Nan::SetMethod(target, "divide", Divide);
      Nan::SetMethod(target, "eigen", Eigen);
      Nan::SetMethod(target, "exp", Exp);
      Nan::SetMethod(target, "extractChannel", ExtractChannel);
      Nan::SetMethod(target, "findNonZero", FindNonZero);
      Nan::SetMethod(target, "flip", Flip);
      Nan::SetMethod(target, "gemm", Gemm);
      Nan::SetMethod(target, "getOptimalDFTSize", GetOptimalDFTSize);
      Nan::SetMethod(target, "hconcat", Hconcat);
      Nan::SetMethod(target, "idct", Idct);
      Nan::SetMethod(target, "idft", Idft);
      Nan::SetMethod(target, "inRange", InRange);
      Nan::SetMethod(target, "insertChannel", InsertChannel);
      Nan::SetMethod(target, "invert", Invert);
      Nan::SetMethod(target, "log", Log);
      Nan::SetMethod(target, "lut", LUT);
      Nan::SetMethod(target, "magnitude", Magnitude);
      Nan::SetMethod(target, "mahalanobis", Mahalanobis);
      Nan::SetMethod(target, "max", Max);
      Nan::SetMethod(target, "mean", Mean);
      Nan::SetMethod(target, "meanStdDev", MeanStdDev);
      Nan::SetMethod(target, "merge", Merge);
      Nan::SetMethod(target, "min", Min);
      Nan::SetMethod(target, "minMaxIdx", MinMaxIdx);
      Nan::SetMethod(target, "minMaxLoc", MinMaxLoc);
      Nan::SetMethod(target, "mixChannels", MixChannels);
      Nan::SetMethod(target, "mulSpectrums", MulSpectrums);
      Nan::SetMethod(target, "multiply", Multiply);
      Nan::SetMethod(target, "mulTransposed", MulTransposed);
      Nan::SetMethod(target, "norm", Norm);
      Nan::SetMethod(target, "normalize", Normalize);
      Nan::SetMethod(target, "patchNaNs", PatchNaNs);
      Nan::SetMethod(target, "pcaBackProject", PCABackProject);
      Nan::SetMethod(target, "pcaCompute", PCACompute);
      Nan::SetMethod(target, "pcaProject", PCAProject);
      Nan::SetMethod(target, "perspectiveTransform", PerspectiveTransform);
      Nan::SetMethod(target, "phase", Phase);
      Nan::SetMethod(target, "polarToCart", PolarToCart);
      Nan::SetMethod(target, "pow", Pow);
      Nan::SetMethod(target, "psnr", PSNR);
      Nan::SetMethod(target, "randn", Randn);
      Nan::SetMethod(target, "randShuffle", RandShuffle);
      Nan::SetMethod(target, "randu", Randu);
      Nan::SetMethod(target, "reduce", Reduce);
      Nan::SetMethod(target, "repeat", Repeat);
      Nan::SetMethod(target, "rotate", Rotate);
      Nan::SetMethod(target, "scaleAdd", ScaleAdd);
      Nan::SetMethod(target, "setIdentity", SetIdentity);
      Nan::SetMethod(target, "setRNGSeed", SetRNGSeed);
      Nan::SetMethod(target, "solve", Solve);
      Nan::SetMethod(target, "solveCubic", SolveCubic);
      Nan::SetMethod(target, "solvePoly", SolvePoly);
      Nan::SetMethod(target, "sort", Sort);
      Nan::SetMethod(target, "sortIdx", SortIdx);
      Nan::SetMethod(target, "split", Split);
      Nan::SetMethod(target, "sqrt", Sqrt);
      Nan::SetMethod(target, "subtract", Subtract);
      Nan::SetMethod(target, "sum", Sum);
      Nan::SetMethod(target, "svBackSubst", SVBackSubst);
      Nan::SetMethod(target, "svDecomp", SVDecomp);
      Nan::SetMethod(target, "theRNG", TheRNG);
      Nan::SetMethod(target, "trace", Trace);
      Nan::SetMethod(target, "transform", Transform);
      Nan::SetMethod(target, "transpose", Transpose);
      Nan::SetMethod(target, "vconcat", Vconcat);
    }

  }

}

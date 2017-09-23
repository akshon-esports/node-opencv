import { Matrix } from '../../../../core';

declare module '../../../../core' {
    interface Matrix {
        bilateralFilter(d: number, sigmaColor: number, sigmaSpace: number, borderType?: number /* = BORDER_DEFAULT */): Matrix;
    }
}

import { Matrix, Size } from '../../../../core';

declare module '../../../../core' {
    interface Matrix {
        gaussianBlur(ksize: Size, sigmaX: number, sigmaY?: number /* = 0 */, borderType?: number /* = BORDER_DEFAULT */): Matrix;
    }
}

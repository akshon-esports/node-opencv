import { Matrix } from '../../../../core';

declare module '../../../../core' {
    interface Matrix {
        canny(threshold1: number, threshold2: number, apertureSize?: number /* = 3 */, L2gradient?: boolean /* = false */): Matrix;
    }
}

import { Matrix, Size } from '../../../../core';

declare module '../../../../core' {
    interface Matrix {
        resizeImage(dsize: Size, fx?: number /* = 0 */, fy?: number /* = 0 */, interpolation?: number /* = INTER_LINEAR */): Matrix
    }
}

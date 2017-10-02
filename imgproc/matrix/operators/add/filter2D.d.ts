import { InputArray, Matrix, Point } from '../../../../core';

declare module '../../../../core' {
    interface Matrix {
        filter2D(ddepth: number, kernel: InputArray, anchor?: Point /* = Point(-1,-1) */, delta?: number /* = 0 */, borderType?: number /* = BORDER_DEFAULT */): Matrix;
    }
}

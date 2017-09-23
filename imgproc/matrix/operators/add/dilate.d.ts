import { InputArray, Matrix, Point, Scalar } from '../../../../core';

declare module '../../../../core' {
    interface Matrix {
        dilate(kernel: InputArray, anchor?: Point /* = Point(-1,-1) */, iterations?: number /* = 1 */, borderType?: number /* = BORDER_CONSTANT */, borderValue?: Scalar /* = morphologyDefaultBorderValue() */): Matrix;
    }
}

import { Matrix } from '../../../../core';

declare module '../../../../core' {
    interface Matrix {
        convertColor(code: number, dstCn?: number /* = 0 */): Matrix;
    }
}

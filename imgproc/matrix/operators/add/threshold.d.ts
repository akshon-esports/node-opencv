import { Matrix } from '../../../../core';

declare module '../../../../core' {
    interface Matrix {
        threshold(thresh: number, maxval: number, type: number): Matrix;
    }
}

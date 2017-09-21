import { Matrix } from '../../../';

declare module '../../../' {
    interface Matrix {
        flip(flipCode: number): Matrix;
    }
}

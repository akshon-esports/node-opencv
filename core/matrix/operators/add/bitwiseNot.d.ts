import { InputArray, Matrix } from '../../../';

declare module '../../../' {
    interface Matrix {
        bitwiseNot(mask?: InputArray): Matrix;
    }
}

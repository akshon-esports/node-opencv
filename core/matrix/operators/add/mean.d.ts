import { InputArray, Matrix, Scalar } from '../../../';

declare module '../../../' {
    interface Matrix {
        mean(mask?: InputArray): Scalar;
    }
}

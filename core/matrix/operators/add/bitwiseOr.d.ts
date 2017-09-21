import { InputArray, Matrix } from '../../../';

declare module '../../../' {
    interface Matrix {
        bitwiseOr(rightOperand: InputArray, mask?: InputArray): Matrix;
    }
}

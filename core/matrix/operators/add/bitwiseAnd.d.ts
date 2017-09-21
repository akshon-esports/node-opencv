import { InputArray, Matrix } from '../../../';

declare module '../../../' {
    interface Matrix {
        bitwiseAnd(rightOperand: InputArray, mask?: InputArray): Matrix;
    }
}

import { InputArray, Matrix } from '../../../';

declare module '../../../' {
    interface Matrix {
        bitwiseXor(rightOperand: InputArray, mask?: InputArray): Matrix;
    }
}

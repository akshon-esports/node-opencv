import { InputArray, Matrix } from '../../../';

declare module '../../../' {
    interface Matrix {
        inRange(lowerBound: InputArray, upperBound: InputArray): Matrix;
    }
}

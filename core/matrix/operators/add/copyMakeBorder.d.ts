import { BorderTypes, Matrix, Scalar } from '../../../';

declare module '../../../' {
    interface Matrix {
        copyMakeBorder(top: number, bottom: number, left: number, right: number, borderType: BorderTypes, value?: Scalar): Matrix;
    }
}

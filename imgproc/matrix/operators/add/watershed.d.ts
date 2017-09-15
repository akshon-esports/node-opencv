import { Matrix } from '../../../../core';

declare module '../../../../core' {
    interface Matrix {
        watershed(): Matrix;
    }
}

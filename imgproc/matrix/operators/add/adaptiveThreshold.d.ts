import { Matrix } from '../../../../core';

declare module '../../../../core' {
    interface Matrix {
        adaptiveThreshold(maxValue: number, adaptiveMethod: number, thresholdType: number, blockSize: number, C: number): Matrix;
    }
}

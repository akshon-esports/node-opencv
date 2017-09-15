import { InputArray, Matrix, Point } from '../../../';

declare module '../../../' {
    interface Matrix {
        minMaxLoc(mask?: InputArray): { minVal: number, maxVal: number, minLoc: Point, maxLoc: Point };
    }
}

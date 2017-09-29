import { Matrix } from '../../../../core';
import { Circle } from '../../../';

declare module '../../../../core' {
    interface Matrix {
        houghCircles(method: number, dp: number, minDist: number, param1?: number /* = 100 */, param2?: number /* = 100 */, minRadius?: number /* = 0 */, maxRadius?: number /* = 0 */): Circle[];
    }
}

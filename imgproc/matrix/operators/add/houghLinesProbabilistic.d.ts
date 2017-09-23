import { Matrix } from '../../../../core';

declare module '../../../../core' {
    interface Matrix {
        houghLinesProbabilistic(rho: number, theta: number, threshold: number, minLineLength?: number /* = 0 */, maxLineGap?: number /* = 0 */): [number, number, number, number][];
    }
}

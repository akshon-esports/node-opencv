import { Matrix, Point } from '../../../../core';
import { Contours } from '../../../';

declare module '../../../../core' {
    interface Matrix {
        findContours(mode: number, method: number, offset?: Point /* = Point() */): Contours;
    }
}

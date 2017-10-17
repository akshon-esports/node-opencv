import { Matrix, Point, Scalar } from '../../../../core';
import { Contour } from '../../../';

declare module '../../../../core' {
    interface Matrix {
        drawContours(contours: Contour, contourIdx: number, color: Scalar, thickness?: number /* = 1 */, lineType?: number /* = LINE_8 */, maxLevel?: number /* = INT_MAX */, offset?: Point /* = Point() */): this;
    }
}

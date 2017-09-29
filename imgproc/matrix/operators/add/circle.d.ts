import { LineTypes, Matrix, Point, PointLike, RectLike, Scalar } from '../../../../core';

declare module '../../../../core' {
    interface Matrix {
        circle(center: PointLike, radius: number, color: Scalar, thickness?: number, lineType?: LineTypes, shift?: number): this;
    }
}

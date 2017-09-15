import { LineTypes, Matrix, PointLike, RectLike, Scalar } from '../../../../core';

declare module '../../../../core' {
    interface Matrix {
        rectangle(rect: RectLike, color: Scalar, thickness?: number, lineType?: LineTypes): void;
        rectangle(p1: PointLike, p2: PointLike, color: Scalar, thickness?: number, lineType?: LineTypes): void;
    }
}

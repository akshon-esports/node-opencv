import { LineTypes, Matrix, PointLike, Scalar } from '../../../../core';

declare module '../../../../core' {
    interface Matrix {
        line(p1: PointLike, p2: PointLike, color: Scalar, thickness?: number, lineType?: LineTypes, shift?: number): this;
    }
}

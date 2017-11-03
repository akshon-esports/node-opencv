import { Matrix } from '../../../../core';
import { DistanceTransformLabelTypes, DistanceTypes } from '../../../';

declare module '../../../../core' {
    interface Matrix {
        distanceTransform(distanceType: DistanceTypes, maskSize: number, labelSize?: DistanceTransformLabelTypes): {result: Matrix, labels: Matrix};
    }
}

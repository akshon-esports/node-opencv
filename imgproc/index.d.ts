import { InputArray, InputOutputArray, Matrix, OutputArray,  Point, Rect, RotatedRect, Scalar, Size, TerminationCriteria } from '../core';

/** Image Filtering **/
export type MorphShapes = number;
export type MorphTypes = number;

export const MORPH_RECT: MorphShapes;
export const MORPH_CROSS: MorphShapes;
export const MORPH_ELLIPSE: MorphShapes;

export const MORPH_ERODE: MorphTypes;
export const MORPH_DILATE: MorphTypes;
export const MORPH_OPEN: MorphTypes;
export const MORPH_CLOSE: MorphTypes;
export const MORPH_GRADIENT: MorphTypes;
export const MORPH_TOPHAT: MorphTypes;
export const MORPH_BLACKHAT: MorphTypes;
export const MORPH_HITMISS: MorphTypes;

export function bilateralFilter(src: InputArray, dst: OutputArray, d: number, sigmaColor: number, sigmaSpace: number, borderType?: number /* = BORDER_DEFAULT */): void;

export function blur(src: InputArray, dst: OutputArray, ksize: Size, anchor?: Point /* = Point(-1,-1) */, borderType?: number /* = BORDER_DEFAULT */): void;

export function boxFilter(src: InputArray, dst: OutputArray, ddepth: number, ksize: Size, anchor?: Point /* = Point(-1,-1) */, normalize?: boolean /* = true */, borderType?: number /* = BORDER_DEFAULT */): void;

export function buildPyramid(src: InputArray, dst: OutputArray[], maxlevel: number, borderType?: number /* = BORDER_DEFAULT */): void;

export function dilate(src: InputArray, dst: OutputArray, kernel: InputArray, anchor?: Point /* = Point(-1,-1) */, iterations?: number /* = 1 */, borderType?: number /* = BORDER_CONSTANT */, borderValue?: Scalar /* = morphologyDefaultBorderValue() */): void;

export function erode(src: InputArray, dst: OutputArray, kernel: InputArray, anchor?: Point /* = Point(-1,-1) */, iterations?: number /* = 1 */, borderType?: number /* = BORDER_CONSTANT */, borderValue?: Scalar /* = morphologyDefaultBorderValue() */): void;

export function filter2D(src: InputArray, dst: OutputArray, ddepth: number, kernel: InputArray, anchor?: Point /* = Point(-1,-1) */, delta?: number /* = 0 */, borderType?: number /* = BORDER_DEFAULT */): void;

export function gaussianBlur(src: InputArray, dst: OutputArray, ksize: Size, sigmaX: number, sigmaY?: number /* = 0 */, borderType?: number /* = BORDER_DEFAULT */): void;

export function getDerivKernels(kx: OutputArray, ky: OutputArray, dx: number, dy: number, ksize: number, normalize?: boolean /* = false */, ktype?: number /* = CV_32F */): void;

export function getGaborKernel(ksize: Size, sigma: number, theta: number, lambd: number, gamma: number, psi?: number /* = CV_PI *0.5 */, ktype?: number /* = CV_64F */): Matrix;

export function getGaussianKernel(ksize: number, sigma: number, ktype?: number /* = CV_64F */): Matrix;

export function getStructuringElement(shape: number, ksize: Size, anchor?: Point /* = Point(-1,-1) */): Matrix;

export function laplacian(src: InputArray, dst: OutputArray, ddepth: number, ksize?: number /* = 1 */, scale?: number /* = 1 */, delta?: number /* = 0 */, borderType?: number /* = BORDER_DEFAULT */): void;

export function medianBlur(src: InputArray, dst: OutputArray, ksize: number): void;

export function morphologyDefaultBorderValue(): Scalar;

export function morphologyEx(src: InputArray, dst: OutputArray, op: number, kernel: InputArray, anchor?: Point /* = Point(-1,-1) */, iterations?: number /* = 1 */, borderType?: number /* = BORDER_CONSTANT */, borderValue?: Scalar /* = morphologyDefaultBorderValue() */): void;

export function pyrDown(src: InputArray, dst: OutputArray, dstsize?: Size /* = Size() */, borderType?: number /* = BORDER_DEFAULT */): void;

export function pyrMeanShiftFiltering(src: InputArray, dst: OutputArray, sp: number, sr: number, maxLevel?: number /* = 1 */, termcrit?: TerminationCriteria /* = TermCriteria(TermCriteria::MAX_ITER+TermCriteria::EPS, 5, 1) */): void;

export function pyrUp(src: InputArray, dst: OutputArray, dstsize?: Size /* = Size() */, borderType?: number /* = BORDER_DEFAULT */): void;

export function scharr(src: InputArray, dst: OutputArray, ddepth: number, dx: number, dy: number, scale?: number /* = 1 */, delta?: number /* = 0 */, borderType?: number /* = BORDER_DEFAULT */): void;

export function sepFilter2D(src: InputArray, dst: OutputArray, ddepth: number, kernelX: InputArray, kernelY: InputArray, anchor?: Point /* = Point(-1,-1) */, delta?: number /* = 0 */, borderType?: number /* = BORDER_DEFAULT */): void;

export function sobel(src: InputArray, dst: OutputArray, ddepth: number, dx: number, dy: number, ksize?: number /* = 3 */, scale?: number /* = 1 */, delta?: number /* = 0 */, borderType?: number /* = BORDER_DEFAULT */): void;

export function spatialGradient(src: InputArray, dx: OutputArray, dy: OutputArray, ksize?: number /* = 3 */, borderType?: number /* = BORDER_DEFAULT */): void;

export function sqrBoxFilter(_src: InputArray, _dst: OutputArray, ddepth: number, ksize: Size, anchor?: Point /* = Point(-1, -1) */, normalize?: boolean /* = true */, borderType?: number /* = BORDER_DEFAULT */): void;

/** Geometric Image Transformations **/
export type InterpolationFlags = number;
export type InterpolationMasks = number;

export const INTER_NEAREST: InterpolationFlags;
export const INTER_LINEAR: InterpolationFlags;
export const INTER_CUBIC: InterpolationFlags;
export const INTER_AREA: InterpolationFlags;
export const INTER_LANCZOS4: InterpolationFlags;
export const INTER_MAX: InterpolationFlags;
export const WARP_FILL_OUTLIERS: InterpolationFlags;
export const WARP_INVERSE_MAP: InterpolationFlags;

export const INTER_BITS: InterpolationMasks;
export const INTER_BITS2: InterpolationMasks;
export const INTER_TAB_SIZE: InterpolationMasks;
export const INTER_TAB_SIZE2: InterpolationMasks;

export function convertMaps(map1: InputArray, map2: InputArray, dstmap1: OutputArray, dstmap2: OutputArray, dstmap1type: number, nninterpolation?: boolean /* = false */): void;

export function getAffineTransform(src: Point[], dst: Point[]): Matrix;
export function getAffineTransform(src: InputArray, dst: InputArray): Matrix;

export function getDefaultNewCameraMatrix(cameraMatrix: InputArray, imgsize?: Size /* = Size() */, centerPrincipalPoint?: boolean /* = false */): Matrix;

export function getPerspectiveTransform(src: Point[], dst: Point[]): Matrix;
export function getPerspectiveTransform(src: InputArray, dst: InputArray): Matrix;

export function getRectSubPix(image: InputArray, patchSize: Size, center: Point, patch: OutputArray, patchType?: number /* = -1 */): void;

export function getRotationMatrix2D(center: Point, angle: number, scale: number): Matrix;

export function initUndistortRectifyMap(cameraMatrix: InputArray, distCoeffs: InputArray, R: InputArray, newCameraMatrix: InputArray, size: Size, m1type: number, map1: OutputArray, map2: OutputArray): void;

export function initWideAngleProjMap(cameraMatrix: InputArray, distCoeffs: InputArray, imageSize: Size, destImageWidth: number, m1type: number, map1: OutputArray, map2: OutputArray, projType?: number /* = PROJ_SPHERICAL_EQRECT */, alpha?: number /* = 0 */): number;

export function invertAffineTransform(M: InputArray, iM: OutputArray): void;

export function linearPolar(src: InputArray, dst: OutputArray, center: Point, maxRadius: number, flags: number): void;

export function logPolar(src: InputArray, dst: OutputArray, center: Point, M: number, flags: number): void;

export function remap(src: InputArray, dst: OutputArray, map1: InputArray, map2: InputArray, interpolation: number, borderMode?: number /* = BORDER_CONSTANT */, borderValue?: Scalar /* = Scalar() */): void;

export function resize(src: InputArray, dst: OutputArray, dsize: Size, fx?: number /* = 0 */, fy?: number /* = 0 */, interpolation?: number /* = INTER_LINEAR */): void;

export function undistort(src: InputArray, dst: OutputArray, cameraMatrix: InputArray, distCoeffs: InputArray, newCameraMatrix?: InputArray /* = noArray() */): void;

export function undistortPoints(src: InputArray, dst: OutputArray, cameraMatrix: InputArray, distCoeffs: InputArray, R?: InputArray /* = noArray() */, P?: InputArray /* = noArray() */): void;

export function warpAffine(src: InputArray, dst: OutputArray, M: InputArray, dsize: Size, flags?: number /* = INTER_LINEAR */, borderMode?: number /* = BORDER_CONSTANT */, borderValue?: Scalar /* = Scalar() */): void;

export function warpPerspective(src: InputArray, dst: OutputArray, M: InputArray, dsize: Size, flags?: number /* = INTER_LINEAR */, borderMode?: number /* = BORDER_CONSTANT */, borderValue?: Scalar /* = Scalar() */): void;

/** Miscellaneous Image Transformations **/
export type AdaptiveThresholdTypes = number;
export type ColorConversionCodes = number;
export type DistanceTransformLabelTypes = number;
export type DistanceTransformMasks = number;
export type DistanceTypes = number;
export type FloodFillFlags = number;
export type GrabCutClasses = number;
export type GrabCutModes = number;
export type ThresholdTypes = number;
export type UndistortTypes = number;

export const ADAPTIVE_THRESH_MEAN_C: AdaptiveThresholdTypes;
export const ADAPTIVE_THRESH_GAUSSIAN_C: AdaptiveThresholdTypes;

export const COLOR_BGR2BGRA: ColorConversionCodes;
export const COLOR_RGB2RGBA: ColorConversionCodes;
export const COLOR_BGRA2BGR: ColorConversionCodes;
export const COLOR_RGBA2RGB: ColorConversionCodes;
export const COLOR_BGR2RGBA: ColorConversionCodes;
export const COLOR_RGB2BGRA: ColorConversionCodes;
export const COLOR_RGBA2BGR: ColorConversionCodes;
export const COLOR_BGRA2RGB: ColorConversionCodes;
export const COLOR_BGR2RGB: ColorConversionCodes;
export const COLOR_RGB2BGR: ColorConversionCodes;
export const COLOR_BGRA2RGBA: ColorConversionCodes;
export const COLOR_RGBA2BGRA: ColorConversionCodes;
export const COLOR_BGR2GRAY: ColorConversionCodes;
export const COLOR_RGB2GRAY: ColorConversionCodes;
export const COLOR_GRAY2BGR: ColorConversionCodes;
export const COLOR_GRAY2RGB: ColorConversionCodes;
export const COLOR_GRAY2BGRA: ColorConversionCodes;
export const COLOR_GRAY2RGBA: ColorConversionCodes;
export const COLOR_BGRA2GRAY: ColorConversionCodes;
export const COLOR_RGBA2GRAY: ColorConversionCodes;
export const COLOR_BGR2BGR565: ColorConversionCodes;
export const COLOR_RGB2BGR565: ColorConversionCodes;
export const COLOR_BGR5652BGR: ColorConversionCodes;
export const COLOR_BGR5652RGB: ColorConversionCodes;
export const COLOR_BGRA2BGR565: ColorConversionCodes;
export const COLOR_RGBA2BGR565: ColorConversionCodes;
export const COLOR_BGR5652BGRA: ColorConversionCodes;
export const COLOR_BGR5652RGBA: ColorConversionCodes;
export const COLOR_GRAY2BGR565: ColorConversionCodes;
export const COLOR_BGR5652GRAY: ColorConversionCodes;
export const COLOR_BGR2BGR555: ColorConversionCodes;
export const COLOR_RGB2BGR555: ColorConversionCodes;
export const COLOR_BGR5552BGR: ColorConversionCodes;
export const COLOR_BGR5552RGB: ColorConversionCodes;
export const COLOR_BGRA2BGR555: ColorConversionCodes;
export const COLOR_RGBA2BGR555: ColorConversionCodes;
export const COLOR_BGR5552BGRA: ColorConversionCodes;
export const COLOR_BGR5552RGBA: ColorConversionCodes;
export const COLOR_GRAY2BGR555: ColorConversionCodes;
export const COLOR_BGR5552GRAY: ColorConversionCodes;
export const COLOR_BGR2XYZ: ColorConversionCodes;
export const COLOR_RGB2XYZ: ColorConversionCodes;
export const COLOR_XYZ2BGR: ColorConversionCodes;
export const COLOR_XYZ2RGB: ColorConversionCodes;
export const COLOR_BGR2YCrCb: ColorConversionCodes;
export const COLOR_RGB2YCrCb: ColorConversionCodes;
export const COLOR_YCrCb2BGR: ColorConversionCodes;
export const COLOR_YCrCb2RGB: ColorConversionCodes;
export const COLOR_BGR2HSV: ColorConversionCodes;
export const COLOR_RGB2HSV: ColorConversionCodes;
export const COLOR_BGR2Lab: ColorConversionCodes;
export const COLOR_RGB2Lab: ColorConversionCodes;
export const COLOR_BGR2Luv: ColorConversionCodes;
export const COLOR_RGB2Luv: ColorConversionCodes;
export const COLOR_BGR2HLS: ColorConversionCodes;
export const COLOR_RGB2HLS: ColorConversionCodes;
export const COLOR_HSV2BGR: ColorConversionCodes;
export const COLOR_HSV2RGB: ColorConversionCodes;
export const COLOR_Lab2BGR: ColorConversionCodes;
export const COLOR_Lab2RGB: ColorConversionCodes;
export const COLOR_Luv2BGR: ColorConversionCodes;
export const COLOR_Luv2RGB: ColorConversionCodes;
export const COLOR_HLS2BGR: ColorConversionCodes;
export const COLOR_HLS2RGB: ColorConversionCodes;
export const COLOR_BGR2HSV_FULL: ColorConversionCodes;
export const COLOR_RGB2HSV_FULL: ColorConversionCodes;
export const COLOR_BGR2HLS_FULL: ColorConversionCodes;
export const COLOR_RGB2HLS_FULL: ColorConversionCodes;
export const COLOR_HSV2BGR_FULL: ColorConversionCodes;
export const COLOR_HSV2RGB_FULL: ColorConversionCodes;
export const COLOR_HLS2BGR_FULL: ColorConversionCodes;
export const COLOR_HLS2RGB_FULL: ColorConversionCodes;
export const COLOR_LBGR2Lab: ColorConversionCodes;
export const COLOR_LRGB2Lab: ColorConversionCodes;
export const COLOR_LBGR2Luv: ColorConversionCodes;
export const COLOR_LRGB2Luv: ColorConversionCodes;
export const COLOR_Lab2LBGR: ColorConversionCodes;
export const COLOR_Lab2LRGB: ColorConversionCodes;
export const COLOR_Luv2LBGR: ColorConversionCodes;
export const COLOR_Luv2LRGB: ColorConversionCodes;
export const COLOR_BGR2YUV: ColorConversionCodes;
export const COLOR_RGB2YUV: ColorConversionCodes;
export const COLOR_YUV2BGR: ColorConversionCodes;
export const COLOR_YUV2RGB: ColorConversionCodes;
export const COLOR_YUV2RGB_NV12: ColorConversionCodes;
export const COLOR_YUV2BGR_NV12: ColorConversionCodes;
export const COLOR_YUV2RGB_NV21: ColorConversionCodes;
export const COLOR_YUV2BGR_NV21: ColorConversionCodes;
export const COLOR_YUV420sp2RGB: ColorConversionCodes;
export const COLOR_YUV420sp2BGR: ColorConversionCodes;
export const COLOR_YUV2RGBA_NV12: ColorConversionCodes;
export const COLOR_YUV2BGRA_NV12: ColorConversionCodes;
export const COLOR_YUV2RGBA_NV21: ColorConversionCodes;
export const COLOR_YUV2BGRA_NV21: ColorConversionCodes;
export const COLOR_YUV420sp2RGBA: ColorConversionCodes;
export const COLOR_YUV420sp2BGRA: ColorConversionCodes;
export const COLOR_YUV2RGB_YV12: ColorConversionCodes;
export const COLOR_YUV2BGR_YV12: ColorConversionCodes;
export const COLOR_YUV2RGB_IYUV: ColorConversionCodes;
export const COLOR_YUV2BGR_IYUV: ColorConversionCodes;
export const COLOR_YUV2RGB_I420: ColorConversionCodes;
export const COLOR_YUV2BGR_I420: ColorConversionCodes;
export const COLOR_YUV420p2RGB: ColorConversionCodes;
export const COLOR_YUV420p2BGR: ColorConversionCodes;
export const COLOR_YUV2RGBA_YV12: ColorConversionCodes;
export const COLOR_YUV2BGRA_YV12: ColorConversionCodes;
export const COLOR_YUV2RGBA_IYUV: ColorConversionCodes;
export const COLOR_YUV2BGRA_IYUV: ColorConversionCodes;
export const COLOR_YUV2RGBA_I420: ColorConversionCodes;
export const COLOR_YUV2BGRA_I420: ColorConversionCodes;
export const COLOR_YUV420p2RGBA: ColorConversionCodes;
export const COLOR_YUV420p2BGRA: ColorConversionCodes;
export const COLOR_YUV2GRAY_420: ColorConversionCodes;
export const COLOR_YUV2GRAY_NV21: ColorConversionCodes;
export const COLOR_YUV2GRAY_NV12: ColorConversionCodes;
export const COLOR_YUV2GRAY_YV12: ColorConversionCodes;
export const COLOR_YUV2GRAY_IYUV: ColorConversionCodes;
export const COLOR_YUV2GRAY_I420: ColorConversionCodes;
export const COLOR_YUV420sp2GRAY: ColorConversionCodes;
export const COLOR_YUV420p2GRAY: ColorConversionCodes;
export const COLOR_YUV2RGB_UYVY: ColorConversionCodes;
export const COLOR_YUV2BGR_UYVY: ColorConversionCodes;
export const COLOR_YUV2RGB_Y422: ColorConversionCodes;
export const COLOR_YUV2BGR_Y422: ColorConversionCodes;
export const COLOR_YUV2RGB_UYNV: ColorConversionCodes;
export const COLOR_YUV2BGR_UYNV: ColorConversionCodes;
export const COLOR_YUV2RGBA_UYVY: ColorConversionCodes;
export const COLOR_YUV2BGRA_UYVY: ColorConversionCodes;
export const COLOR_YUV2RGBA_Y422: ColorConversionCodes;
export const COLOR_YUV2BGRA_Y422: ColorConversionCodes;
export const COLOR_YUV2RGBA_UYNV: ColorConversionCodes;
export const COLOR_YUV2BGRA_UYNV: ColorConversionCodes;
export const COLOR_YUV2RGB_YUY2: ColorConversionCodes;
export const COLOR_YUV2BGR_YUY2: ColorConversionCodes;
export const COLOR_YUV2RGB_YVYU: ColorConversionCodes;
export const COLOR_YUV2BGR_YVYU: ColorConversionCodes;
export const COLOR_YUV2RGB_YUYV: ColorConversionCodes;
export const COLOR_YUV2BGR_YUYV: ColorConversionCodes;
export const COLOR_YUV2RGB_YUNV: ColorConversionCodes;
export const COLOR_YUV2BGR_YUNV: ColorConversionCodes;
export const COLOR_YUV2RGBA_YUY2: ColorConversionCodes;
export const COLOR_YUV2BGRA_YUY2: ColorConversionCodes;
export const COLOR_YUV2RGBA_YVYU: ColorConversionCodes;
export const COLOR_YUV2BGRA_YVYU: ColorConversionCodes;
export const COLOR_YUV2RGBA_YUYV: ColorConversionCodes;
export const COLOR_YUV2BGRA_YUYV: ColorConversionCodes;
export const COLOR_YUV2RGBA_YUNV: ColorConversionCodes;
export const COLOR_YUV2BGRA_YUNV: ColorConversionCodes;
export const COLOR_YUV2GRAY_UYVY: ColorConversionCodes;
export const COLOR_YUV2GRAY_YUY2: ColorConversionCodes;
export const COLOR_YUV2GRAY_Y422: ColorConversionCodes;
export const COLOR_YUV2GRAY_UYNV: ColorConversionCodes;
export const COLOR_YUV2GRAY_YVYU: ColorConversionCodes;
export const COLOR_YUV2GRAY_YUYV: ColorConversionCodes;
export const COLOR_YUV2GRAY_YUNV: ColorConversionCodes;
export const COLOR_RGBA2mRGBA: ColorConversionCodes;
export const COLOR_mRGBA2RGBA: ColorConversionCodes;
export const COLOR_RGB2YUV_I420: ColorConversionCodes;
export const COLOR_BGR2YUV_I420: ColorConversionCodes;
export const COLOR_RGB2YUV_IYUV: ColorConversionCodes;
export const COLOR_BGR2YUV_IYUV: ColorConversionCodes;
export const COLOR_RGBA2YUV_I420: ColorConversionCodes;
export const COLOR_BGRA2YUV_I420: ColorConversionCodes;
export const COLOR_RGBA2YUV_IYUV: ColorConversionCodes;
export const COLOR_BGRA2YUV_IYUV: ColorConversionCodes;
export const COLOR_RGB2YUV_YV12: ColorConversionCodes;
export const COLOR_BGR2YUV_YV12: ColorConversionCodes;
export const COLOR_RGBA2YUV_YV12: ColorConversionCodes;
export const COLOR_BGRA2YUV_YV12: ColorConversionCodes;
export const COLOR_BayerBG2BGR: ColorConversionCodes;
export const COLOR_BayerGB2BGR: ColorConversionCodes;
export const COLOR_BayerRG2BGR: ColorConversionCodes;
export const COLOR_BayerGR2BGR: ColorConversionCodes;
export const COLOR_BayerBG2RGB: ColorConversionCodes;
export const COLOR_BayerGB2RGB: ColorConversionCodes;
export const COLOR_BayerRG2RGB: ColorConversionCodes;
export const COLOR_BayerGR2RGB: ColorConversionCodes;
export const COLOR_BayerBG2GRAY: ColorConversionCodes;
export const COLOR_BayerGB2GRAY: ColorConversionCodes;
export const COLOR_BayerRG2GRAY: ColorConversionCodes;
export const COLOR_BayerGR2GRAY: ColorConversionCodes;
export const COLOR_BayerBG2BGR_VNG: ColorConversionCodes;
export const COLOR_BayerGB2BGR_VNG: ColorConversionCodes;
export const COLOR_BayerRG2BGR_VNG: ColorConversionCodes;
export const COLOR_BayerGR2BGR_VNG: ColorConversionCodes;
export const COLOR_BayerBG2RGB_VNG: ColorConversionCodes;
export const COLOR_BayerGB2RGB_VNG: ColorConversionCodes;
export const COLOR_BayerRG2RGB_VNG: ColorConversionCodes;
export const COLOR_BayerGR2RGB_VNG: ColorConversionCodes;
export const COLOR_BayerBG2BGR_EA: ColorConversionCodes;
export const COLOR_BayerGB2BGR_EA: ColorConversionCodes;
export const COLOR_BayerRG2BGR_EA: ColorConversionCodes;
export const COLOR_BayerGR2BGR_EA: ColorConversionCodes;
export const COLOR_BayerBG2RGB_EA: ColorConversionCodes;
export const COLOR_BayerGB2RGB_EA: ColorConversionCodes;
export const COLOR_BayerRG2RGB_EA: ColorConversionCodes;
export const COLOR_BayerGR2RGB_EA: ColorConversionCodes;
export const COLOR_BayerBG2BGRA: ColorConversionCodes;
export const COLOR_BayerGB2BGRA: ColorConversionCodes;
export const COLOR_BayerRG2BGRA: ColorConversionCodes;
export const COLOR_BayerGR2BGRA: ColorConversionCodes;
export const COLOR_BayerBG2RGBA: ColorConversionCodes;
export const COLOR_BayerGB2RGBA: ColorConversionCodes;
export const COLOR_BayerRG2RGBA: ColorConversionCodes;
export const COLOR_BayerGR2RGBA: ColorConversionCodes;
export const COLOR_COLORCVT_MAX: ColorConversionCodes;

export const DIST_LABEL_CCOMP: DistanceTransformLabelTypes;
export const DIST_LABEL_PIXEL: DistanceTransformLabelTypes;

export const DIST_MASK_3: DistanceTransformMasks;
export const DIST_MASK_5: DistanceTransformMasks;
export const DIST_MASK_PRECISE: DistanceTransformMasks;

export const DIST_USER: DistanceTypes;
export const DIST_L1: DistanceTypes;
export const DIST_L2: DistanceTypes;
export const DIST_C: DistanceTypes;
export const DIST_L12: DistanceTypes;
export const DIST_FAIR: DistanceTypes;
export const DIST_WELSCH: DistanceTypes;
export const DIST_HUBER: DistanceTypes;

export const FLOODFILL_FIXED_RANGE: FloodFillFlags;
export const FLOODFILL_MASK_ONLY: FloodFillFlags;

export const GC_BGD: GrabCutClasses;
export const GC_FGD: GrabCutClasses;
export const GC_PR_BGD: GrabCutClasses;
export const GC_PR_FGD: GrabCutClasses;

export const GC_INIT_WITH_RECT: GrabCutModes;
export const GC_INIT_WITH_MASK: GrabCutModes;
export const GC_EVAL: GrabCutModes;

export const THRESH_BINARY: ThresholdTypes;
export const THRESH_BINARY_INV: ThresholdTypes;
export const THRESH_TRUNC: ThresholdTypes;
export const THRESH_TOZERO: ThresholdTypes;
export const THRESH_TOZERO_INV: ThresholdTypes;
export const THRESH_MASK: ThresholdTypes;
export const THRESH_OTSU: ThresholdTypes;
export const THRESH_TRIANGLE: ThresholdTypes;

export const PROJ_SPHERICAL_ORTHO: UndistortTypes;
export const PROJ_SPHERICAL_EQRECT: UndistortTypes;

export function adaptiveThreshold(src: InputArray, dst: OutputArray, maxValue: number, adaptiveMethod: number, thresholdType: number, blockSize: number, C: number): void;

export function cvtColor(src: InputArray, dst: OutputArray, code: number, dstCn?: number /* = 0 */): void;

export function distanceTransform(src: InputArray, dst: OutputArray, labels: OutputArray, distanceType: number, maskSize: number, labelType?: number /* = DIST_LABEL_CCOMP */): void;
export function distanceTransform(src: InputArray, dst: OutputArray, distanceType: number, maskSize: number, dstType?: number /* = CV_32F */): void;

export function floodFill(image: InputOutputArray, seedPoint: Point, newVal: Scalar, rect?: Rect /* = 0 */, loDiff?: Scalar /* = Scalar() */, upDiff?: Scalar /* = Scalar() */, flags?: number /* = 4 */): number;
export function floodFill(image: InputOutputArray, mask: InputOutputArray, seedPoint: Point, newVal: Scalar, rect?: Rect /* = 0 */, loDiff?: Scalar /* = Scalar() */, upDiff?: Scalar /* = Scalar() */, flags?: number /* = 4 */): number;

export function grabCut(img: InputArray, mask: InputOutputArray, rect: Rect, bgdModel: InputOutputArray, fgdModel: InputOutputArray, iterCount: number, mode?: number /* = GC_EVAL */): void;

export function integral(src: InputArray, sum: OutputArray, sdepth?: number /* = -1 */): void;
export function integral(src: InputArray, sum: OutputArray, sqsum: OutputArray, sdepth?: number /* = -1 */, sqdepth?: number /* = -1 */): void;
export function integral(src: InputArray, sum: OutputArray, sqsum: OutputArray, tilted: OutputArray, sdepth?: number /* = -1 */, sqdepth?: number /* = -1 */): void;

export function threshold(src: InputArray, dst: OutputArray, thresh: number, maxval: number, type: number): number;

export function watershed(image: InputArray, markers: InputOutputArray): void;

/** Drawing Functions **/
export type MarkerTypes = number;

export const MARKER_CROSS: MarkerTypes;
export const MARKER_TILTED_CROSS: MarkerTypes;
export const MARKER_STAR: MarkerTypes;
export const MARKER_DIAMOND: MarkerTypes;
export const MARKER_SQUARE: MarkerTypes;
export const MARKER_TRIANGLE_UP: MarkerTypes;
export const MARKER_TRIANGLE_DOWN: MarkerTypes;

export function arrowedLine(img: InputOutputArray, pt1: Point, pt2: Point, color: Scalar, thickness?: number /* = 1 */, line_type?: number /* = 8 */, shift?: number /* = 0 */, tipLength?: number /* = 0.1 */): void;

export function circle(img: InputOutputArray, center: Point, radius: number, color: Scalar, thickness?: number /* = 1 */, lineType?: number /* = LINE_8 */, shift?: number /* = 0 */): void;

export function clipLine(imgSize: Size, pt1: Point, pt2: Point): boolean;
export function clipLine(imgSize: Size, pt1: Point, pt2: Point): boolean;
export function clipLine(imgRect: Rect, pt1: Point, pt2: Point): boolean;

export function drawContours(image: InputOutputArray, contours: Contours, contourIdx: number, color: Scalar, thickness?: number /* = 1 */, lineType?: number /* = LINE_8 */, maxLevel?: number /* = INT_MAX */, offset?: Point /* = Point() */): void;

export function drawMarker(img: Matrix, position: Point, color: Scalar, markerType?: number /* = MARKER_CROSS */, markerSize?: number /* = 20 */, thickness?: number /* = 1 */, line_type?: number /* = 8 */): void;

export function ellipse(img: InputOutputArray, center: Point, axes: Size, angle: number, startAngle: number, endAngle: number, color: Scalar, thickness?: number /* = 1 */, lineType?: number /* = LINE_8 */, shift?: number /* = 0 */): void;
export function ellipse(img: InputOutputArray, box: RotatedRect, color: Scalar, thickness?: number /* = 1 */, lineType?: number /* = LINE_8 */): void;

export function ellipse2Poly(center: Point, axes: Size, angle: number, arcStart: number, arcEnd: number, delta: number, pts: Point[]): void;
export function ellipse2Poly(center: Point, axes: Size, angle: number, arcStart: number, arcEnd: number, delta: number, pts: Point[]): void;

export function fillConvexPoly(img: Matrix, pts: Point, npts: number, color: Scalar, lineType?: number /* = LINE_8 */, shift?: number /* = 0 */): void;
export function fillConvexPoly(img: InputOutputArray, points: InputArray, color: Scalar, lineType?: number /* = LINE_8 */, shift?: number /* = 0 */): void;

// TODO export function fillPoly(img: Matrix, *pts: Point, npts: number, ncontours: number, color: Scalar, lineType?: number /* = LINE_8 */, shift?: number /* = 0 */, offset?: Point /* = Point() */): void;
export function fillPoly(img: InputOutputArray, pts: InputArray[], color: Scalar, lineType?: number /* = LINE_8 */, shift?: number /* = 0 */, offset?: Point /* = Point() */): void;

export function getTextSize(text: String, fontFace: number, fontScale: number, thickness: number, baseLine: number): Size;

export function line(img: InputOutputArray, pt1: Point, pt2: Point, color: Scalar, thickness?: number /* = 1 */, lineType?: number /* = LINE_8 */, shift?: number /* = 0 */): void;

// TODO export function polylines(img: Matrix, pts: Point *const, npts: number, ncontours: number, isClosed: boolean, color: Scalar, thickness?: number /* = 1 */, lineType?: number /* = LINE_8 */, shift?: number /* = 0 */): void;
export function polylines(img: InputOutputArray, pts: InputArray[], isClosed: boolean, color: Scalar, thickness?: number /* = 1 */, lineType?: number /* = LINE_8 */, shift?: number /* = 0 */): void;

export function putText(img: InputOutputArray, text: String, org: Point, fontFace: number, fontScale: number, color: Scalar, thickness?: number /* = 1 */, lineType?: number /* = LINE_8 */, bottomLeftOrigin?: boolean /* = false */): void;

export function rectangle(img: InputOutputArray, pt1: Point, pt2: Point, color: Scalar, thickness?: number /* = 1 */, lineType?: number /* = LINE_8 */, shift?: number /* = 0 */): void;
export function rectangle(img: Matrix, rec: Rect, color: Scalar, thickness?: number /* = 1 */, lineType?: number /* = LINE_8 */, shift?: number /* = 0 */): void;

/** ColorMaps **/
export type ColormapTypes = number;

export const COLORMAP_AUTUMN: ColormapTypes;
export const COLORMAP_BONE: ColormapTypes;
export const COLORMAP_JET: ColormapTypes;
export const COLORMAP_WINTER: ColormapTypes;
export const COLORMAP_RAINBOW: ColormapTypes;
export const COLORMAP_OCEAN: ColormapTypes;
export const COLORMAP_SUMMER: ColormapTypes;
export const COLORMAP_SPRING: ColormapTypes;
export const COLORMAP_COOL: ColormapTypes;
export const COLORMAP_HSV: ColormapTypes;
export const COLORMAP_PINK: ColormapTypes;
export const COLORMAP_HOT: ColormapTypes;
export const COLORMAP_PARULA: ColormapTypes;

export function applyColorMap(src: InputArray, colormap: number): Matrix;
export function applyColorMap(src: InputArray, userColor: InputArray): Matrix;

/** Histograms **/
export type HistCompMethods = number;

export const HISTCMP_CORREL: HistCompMethods;
export const HISTCMP_CHISQR: HistCompMethods;
export const HISTCMP_INTERSECT: HistCompMethods;
export const HISTCMP_BHATTACHARYYA: HistCompMethods;
export const HISTCMP_HELLINGER: HistCompMethods;
export const HISTCMP_CHISQR_ALT: HistCompMethods;
export const HISTCMP_KL_DIV: HistCompMethods;

// TODO export function calcBackProject(images: Matrix, nimages: number, channels: number, hist: InputArray, backProject: OutputArray, *ranges: number, scale?: number /* = 1 */, uniform?: boolean /* = true */): void;
// TODO export function calcBackProject(images: Matrix, nimages: number, channels: number, hist: SparseMat, backProject: OutputArray, *ranges: number, scale?: number /* = 1 */, uniform?: boolean /* = true */): void;
export function calcBackProject(images: InputArray[], channels: number[], hist: InputArray, dst: OutputArray, ranges: number[], scale: number): void;

// TODO export function calcHist(images: Matrix, nimages: number, channels: number, mask: InputArray, hist: OutputArray, dims: number, histSize: number, *ranges: number, uniform?: boolean /* = true */, accumulate?: boolean /* = false */): void;
// TODO export function calcHist(images: Matrix, nimages: number, channels: number, mask: InputArray, hist: SparseMat, dims: number, histSize: number, *ranges: number, uniform?: boolean /* = true */, accumulate?: boolean /* = false */): void;
export function calcHist(images: InputArray[], channels: number[], mask: InputArray, hist: OutputArray, histSize: number[], ranges: number[], accumulate?: boolean /* = false */): void;

export function compareHist(H1: InputArray, H2: InputArray, method: number): number;
// TODO export function compareHist(H1: SparseMat, H2: SparseMat, method: number): number;

export function emd(signature1: InputArray, signature2: InputArray, distType: number, cost?: InputArray /* = noArray() */, lowerBound?: number /* = 0 */, flow?: OutputArray /* = noArray() */): number;

export function equalizeHist(src: InputArray, dst: OutputArray): void;

// TODO export function wrapperEMD(signature1: InputArray, signature2: InputArray, distType: number, cost?: InputArray /* = noArray() */, lowerBound?: Ptr<float> /* = Ptr< float >() */, flow?: OutputArray /* = noArray() */): number;

/** Structural Analysis and Shape Descriptors **/
// TODO Moments
export class Moments {}

export class Contour {
    public parent(): Contour;
    public children(): Contour[];
    public next(): Contour;
    public previous(): Contour;
}

export class Contours {
    public length: number;
    [index: number]: Contour;
}

export type ConnectedComponentsAlgorithmsTypes = number;
export type ConnectedComponentsTypes = number;
export type ContourApproximationModes = number;
export type RectanglesIntersectTypes = number;
export type RetrievalModes = number;
export type ShapeMatchModes = number;

export const CCL_WU: ConnectedComponentsAlgorithmsTypes;
export const CCL_DEFAULT: ConnectedComponentsAlgorithmsTypes;
export const CCL_GRANA: ConnectedComponentsAlgorithmsTypes;

export const CC_STAT_LEFT: ConnectedComponentsTypes;
export const CC_STAT_TOP: ConnectedComponentsTypes;
export const CC_STAT_WIDTH: ConnectedComponentsTypes;
export const CC_STAT_HEIGHT: ConnectedComponentsTypes;
export const CC_STAT_AREA: ConnectedComponentsTypes;
export const CC_STAT_MAX: ConnectedComponentsTypes;

export const CHAIN_APPROX_NONE: ContourApproximationModes;
export const CHAIN_APPROX_SIMPLE: ContourApproximationModes;
export const CHAIN_APPROX_TC89_L1: ContourApproximationModes;
export const CHAIN_APPROX_TC89_KCOS: ContourApproximationModes;

export const INTERSECT_NONE: RectanglesIntersectTypes;
export const INTERSECT_PARTIAL: RectanglesIntersectTypes;
export const INTERSECT_FULL: RectanglesIntersectTypes;

export const RETR_EXTERNAL: RetrievalModes;
export const RETR_LIST: RetrievalModes;
export const RETR_CCOMP: RetrievalModes;
export const RETR_TREE: RetrievalModes;
export const RETR_FLOODFILL: RetrievalModes;

export const CONTOURS_MATCH_I1: ShapeMatchModes;
export const CONTOURS_MATCH_I2: ShapeMatchModes;
export const CONTOURS_MATCH_I3: ShapeMatchModes;

export function approxPolyDP(curve: Point[] | Contour, approxCurve: OutputArray, epsilon: number, closed: boolean): Point[];

export function arcLength(curve: Point[] | Contour, closed: boolean): number;

export function boundingRect(points: Point[] | Contour): Rect;

export function boxPoints(box: RotatedRect, points: OutputArray): void;

export function connectedComponents(image: InputArray, labels: OutputArray, connectivity: number, ltype: number, ccltype: number): number;
export function connectedComponents(image: InputArray, labels: OutputArray, connectivity?: number /* = 8 */, ltype?: number /* = CV_32S */): number;

export function connectedComponentsWithStats(image: InputArray, labels: OutputArray, stats: OutputArray, centroids: OutputArray, connectivity: number, ltype: number, ccltype: number): number;
export function connectedComponentsWithStats(image: InputArray, labels: OutputArray, stats: OutputArray, centroids: OutputArray, connectivity?: number /* = 8 */, ltype?: number /* = CV_32S */): number;

export function contourArea(contour: Point[] | Contour, oriented?: boolean /* = false */): number;

export function convexHull(points: Point[] | Contour, clockwise?: boolean /* = false */, returnPoints?: boolean /* = true */): Point[];

export function convexityDefects(contour: Point[] | Contour, convexhull: InputArray): [number, number, number, number][][];

export function findContours(image: InputOutputArray, mode: number, method: number, offset?: Point /* = Point() */): Contours;

export function fitEllipse(points: Point[] | Contour): RotatedRect;

export function fitLine(points: Point[] | Contour, line: OutputArray, distType: number, param: number, reps: number, aeps: number): void;

export function huMoments(moments: Moments, hu: [number, number, number, number, number, number, number]): void;
export function huMoments(m: Moments, hu: OutputArray): void;

export function intersectConvexConvex(_p1: InputArray, _p2: InputArray, _p12: OutputArray, handleNested?: boolean /* = true */): number;

export function isContourConvex(contour: InputArray): boolean;

export function matchShapes(contour1: InputArray, contour2: InputArray, method: number, parameter: number): number;

export function minAreaRect(points: InputArray): RotatedRect;

export function minEnclosingCircle(points: InputArray, center: Point, radius: number): void;

export function minEnclosingTriangle(points: InputArray, triangle: OutputArray): number;

export function moments(array: InputArray, binaryImage?: boolean /* = false */): Moments;

export function pointPolygonTest(contour: InputArray, pt: Point, measureDist: boolean): number;

export function rotatedRectangleIntersection(rect1: RotatedRect, rect2: RotatedRect, intersectingRegion: OutputArray): number;

/** Motion Analysis and Object Tracking **/
export function accumulate(src: InputArray, dst: InputOutputArray, mask?: InputArray /* = noArray() */): void;

export function accumulateProduct(src1: InputArray, src2: InputArray, dst: InputOutputArray, mask?: InputArray /* = noArray() */): void;

export function accumulateSquare(src: InputArray, dst: InputOutputArray, mask?: InputArray /* = noArray() */): void;

export function accumulateWeighted(src: InputArray, dst: InputOutputArray, alpha: number, mask?: InputArray /* = noArray() */): void;

export function createHanningWindow(dst: OutputArray, winSize: Size, type: number): void;

export function phaseCorrelate(src1: InputArray, src2: InputArray, window?: InputArray /* = noArray() */, response?: number /* = 0 */): Point;

/** Feature Detection **/
export type LineSegmentDetectorModes = number;

export const LSD_REFINE_NONE: LineSegmentDetectorModes;
export const LSD_REFINE_STD: LineSegmentDetectorModes;
export const LSD_REFINE_ADV: LineSegmentDetectorModes;

export function canny(image: InputArray, edges: OutputArray, threshold1: number, threshold2: number, apertureSize?: number /* = 3 */, L2gradient?: boolean /* = false */): void;
export function canny(dx: InputArray, dy: InputArray, edges: OutputArray, threshold1: number, threshold2: number, L2gradient?: boolean /* = false */): void;

export function cornerEigenValsAndVecs(src: InputArray, dst: OutputArray, blockSize: number, ksize: number, borderType?: number /* = BORDER_DEFAULT */): void;

export function cornerHarris(src: InputArray, dst: OutputArray, blockSize: number, ksize: number, k: number, borderType?: number /* = BORDER_DEFAULT */): void;

export function cornerMinEigenVal(src: InputArray, dst: OutputArray, blockSize: number, ksize?: number /* = 3 */, borderType?: number /* = BORDER_DEFAULT */): void;

export function cornerSubPix(image: InputArray, corners: InputOutputArray, winSize: Size, zeroZone: Size, criteria: TerminationCriteria): void;

// TODO export function createLineSegmentDetector(_refine?: number /* = LSD_REFINE_STD */, _scale?: number /* = 0.8 */, _sigma_scale?: number /* = 0.6 */, _quant?: number /* = 2.0 */, _ang_th?: number /* = 22.5 */, _log_eps?: number /* = 0 */, _density_th?: number /* = 0.7 */, _n_bins?: number /* = 1024 */): Ptr<LineSegmentDetector>;

export function goodFeaturesToTrack(image: InputArray, corners: OutputArray, maxCorners: number, qualityLevel: number, minDistance: number, mask?: InputArray /* = noArray() */, blockSize?: number /* = 3 */, useHarrisDetector?: boolean /* = false */, k?: number /* = 0.04 */): void;

export function houghCircles(image: InputArray, circles: OutputArray, method: number, dp: number, minDist: number, param1?: number /* = 100 */, param2?: number /* = 100 */, minRadius?: number /* = 0 */, maxRadius?: number /* = 0 */): void;

export function houghLines(image: InputArray, rho: number, theta: number, threshold: number, srn?: number /* = 0 */, stn?: number /* = 0 */, min_theta?: number /* = 0 */, max_theta?: number /* = CV_PI */): [number, number, number, number][];

export function houghLinesP(image: InputArray, rho: number, theta: number, threshold: number, minLineLength?: number /* = 0 */, maxLineGap?: number /* = 0 */): [number, number, number, number][];

export function preCornerDetect(src: InputArray, dst: OutputArray, ksize: number, borderType?: number /* = BORDER_DEFAULT */): void;

/** Object Detection **/
export type TemplateMatchModes = number;

export const TM_SQDIFF: TemplateMatchModes;
export const TM_SQDIFF_NORMED: TemplateMatchModes;
export const TM_CCORR: TemplateMatchModes;
export const TM_CCORR_NORMED: TemplateMatchModes;
export const TM_CCOEFF: TemplateMatchModes;
export const TM_CCOEFF_NORMED: TemplateMatchModes;

export function matchTemplate(image: InputArray, templ: InputArray, result: OutputArray, method: TemplateMatchModes, mask?: InputArray /* = noArray() */): void;

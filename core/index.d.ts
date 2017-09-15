export type CovarFlags = number;
export type HersheyFonts = number;
export type KmeansFlags = number;
export type LineTypes = number;
export type ReduceTypes = number;

export const COVAR_SCRAMBLED: CovarFlags;
export const COVAR_NORMAL: CovarFlags;
export const COVAR_USE_AVG: CovarFlags;
export const COVAR_SCALE: CovarFlags;
export const COVAR_ROWS: CovarFlags;
export const COVAR_COLS: CovarFlags;

export const FONT_HERSHEY_SIMPLEX: HersheyFonts;
export const FONT_HERSHEY_PLAIN: HersheyFonts;
export const FONT_HERSHEY_DUPLEX: HersheyFonts;
export const FONT_HERSHEY_COMPLEX: HersheyFonts;
export const FONT_HERSHEY_TRIPLEX: HersheyFonts;
export const FONT_HERSHEY_COMPLEX_SMALL: HersheyFonts;
export const FONT_HERSHEY_SCRIPT_SIMPLEX: HersheyFonts;
export const FONT_HERSHEY_SCRIPT_COMPLEX: HersheyFonts;
export const FONT_ITALIC: HersheyFonts;

export const KMEANS_RANDOM_CENTERS: KmeansFlags;
export const KMEANS_PP_CENTERS: KmeansFlags;
export const KMEANS_USE_INITIAL_LABELS: KmeansFlags;

export const FILLED: LineTypes;
export const LINE_4: LineTypes;
export const LINE_8: LineTypes;
export const LINE_AA: LineTypes;

export const REDUCE_SUM: ReduceTypes;
export const REDUCE_AVG: ReduceTypes;
export const REDUCE_MAX: ReduceTypes;
export const REDUCE_MIN: ReduceTypes;

/** Basic structures **/
export declare type InputArray = internal.BaseMatrix | MatrixExpression | number[];

export declare type InputOutputArray = internal.BaseMatrix;

export declare type OutputArray = internal.BaseMatrix;

export declare type MatrixType = number;
export declare type DecompTypes = number;

declare namespace internal {
    abstract class BaseMatrix<Mat extends BaseMatrix> {
        public flags: number;

        public rows: number;

        public cols: number;

        public row(y: number): Mat;

        public col(x: number): Mat;

        public rowRange(y1: number, y2: number): Mat;

        public colRange(x1: number, x2: number): Mat;

        public clone(): Mat;

        public convertTo(rtype: MatrixType, scale?: number, delta?: number): Mat;

        public reshape(cn: number, rows?: number): Mat;

        public create(size: SizeLike, type: number): void;
        public create(rows: number, cols: number, type: number): void;

        public release(): void;

        public locateROI(): { wholeSize: Size, offset: Point };

        public adjustROI(rect: RectLike): Mat;
        public adjustROI(rows: RangeLike, cols: RangeLike): Mat;
        public adjustROI(dtop: number, dbottom: number, dleft: number, dright: number): Mat;

        public isContinuous(): boolean;

        public elemSize(): number;

        public elemSize1(): number;

        public type(): MatrixType;

        public depth(): number;

        public channels(): number;

        public step1(): number;

        public empty(): boolean;
    }

    abstract class CpuMatrix<Mat extends CpuMatrix> extends BaseMatrix<Mat> {
        public dims: number;

        public diag(d: number): Mat;

        public setTo(value: InputArray, mask?: InputArray): void;

        public transpose(): MatrixExpression;

        public invert(method?: DecompTypes): MatrixExpression;

        public multiply(m: InputArray, scale?: number): MatrixExpression;

        public dot(m: InputArray): Mat;

        public isSubmatrix(): boolean;

        public total(): number;

        public size(): Size;
    }
}

export declare class Matrix extends internal.CpuMatrix<Matrix> {
    /**
     * @description Creates an empty Matrix
     */
    constructor();

    /**
     * @description Creates a new Matrix whose header points to the data of another Matrix or sub-Matrix
     * @param {Matrix} mat
     */
    constructor(mat: Matrix);

    /**
     * @description Creates a 2D Matrix
     * @param {SizeLike} size
     * @param {MatrixType} type
     * @param {ScalarLike} scalar
     */
    constructor(size: SizeLike, type: MatrixType, scalar?: ScalarLike);

    /**
     * @description Creates a 2D Matrix
     * @param {number} rows
     * @param {number} cols
     * @param {MatrixType} type
     * @param {ScalarLike} scalar
     */
    constructor(rows: number, cols: number, type: MatrixType, scalar?: ScalarLike);

    /**
     * @description Creates a Matrix of arbitrary dimensions
     * @param {number[]} sizes
     * @param {MatrixType} type
     * @param {ScalarLike} scalar
     */
    constructor(sizes: number[], type: MatrixType, scalar?: ScalarLike);

    /**
     * @description Creates a new 2D Matrix whose header points to the region of interest of another Matrix or sub-Matrix
     * @param {Matrix} mat
     * @param {RectLike} roi
     */
    constructor(mat: Matrix, roi: RectLike);

    /**
     * @description Creates a new 2D Matrix whose header points to the given rows and columns of another Matrix or sub-Matrix
     * @param {Matrix} mat
     * @param {RangeLike} rows
     * @param {RangeLike} cols
     */
    constructor(mat: Matrix, rows: RangeLike, cols?: RangeLike);

    /**
     * @description Creates a new Matrix of arbitrary dimensions whose header points to the given ranges of another Matrix or sub-Matrix
     * @param {Matrix} mat
     * @param {RangeLike} rows
     * @param {RangeLike} cols
     */
    constructor(mat: Matrix, rows: RangeLike, cols?: RangeLike);

    /**
     * @description Returns the UnifiedMatrix version of the Matrix
     * @description  Warning: The Matrix object which had this method called cannot be used until the derivative UnifiedMatrix object is destroyed
     * @return {UnifiedMatrix}
     */
    public getUnifiedMatrix(): UnifiedMatrix;

    public cross(m: InputArray): Matrix;

    public reserve(size: SizeLike): void;

    public reserveBuffer(size: SizeLike): void;

    public resize(size: SizeLike): void;

    public pushBack(mat: Matrix): void;

    public popBack(nelements: number): void;
}

export declare class UnifiedMatrix extends internal.CpuMatrix<UnifiedMatrix> {
    public getMatrix(): Matrix;
}

export declare class GpuStream {

}

export declare class GpuMatrix extends internal.BaseMatrix<GpuMatrix> {
    public convertTo: {
        (rtype: MatrixType, scale: number, delta: number): GpuMatrix;
        (rtype: MatrixType, stream: GpuStream): Promise<GpuMatrix>;
        (rtype: MatrixType, scale: number, stream: GpuStream): Promise<GpuMatrix>;
        (rtype: MatrixType, scale: number, delta: number, stream: GpuStream): Promise<GpuMatrix>;
        (rtype: MatrixType, stream: GpuStream, callback: (err: Error, out: GpuMatrix) => void): void;
        (rtype: MatrixType, scale: number, stream: GpuStream, callback: (err: Error, out: GpuMatrix) => void): void;
        (rtype: MatrixType, scale: number, delta: number, stream: GpuStream, callback: (err: Error, out: GpuMatrix) => void): void;
    };
    public setTo: {
        (value: ScalarLike, mask?: InputArray): void; (value: ScalarLike, stream: GpuStream): Promise<void>; (value: ScalarLike, mask: InputArray, stream: GpuStream): Promise<void>; (value: ScalarLike, stream: GpuStream, callback: (err: Error) => void): void; (value: ScalarLike, mask: InputArray, stream: GpuStream, callback: (err: Error) => void): void;
    };
}

export declare type _PointLike = Point | {
    x: number; y: number;
};

export declare type PointLike = _PointLike | [number, number]

export declare class Point {
    public x: number;
    public y: number;

    constructor();
    constructor(point: PointLike);
    constructor(x: number, y: number);

    dot(p2: Point): number;
}

type _SizeLike = Size | {
    width: number; height: number;
};

export declare type SizeLike = _SizeLike | [number, number];

export declare class Size {
    public width: number;
    public height: number;

    constructor();
    constructor(size: SizeLike);
    constructor(width: number, height: number);

    area(): number;
}

export declare type RectLike = Rect | _PointLike & _SizeLike | [number, number, number, number];

export declare class Rect {
    public x: number;
    public y: number;
    public width: number;
    public height: number;

    /**
     * @description Creates a Rect
     */
    constructor();

    /**
     * @description Creates a Rect
     * @param {"opencv/core".RectLike} rect
     */
    constructor(rect: RectLike);

    /**
     * @description Creates a Rect
     * @description Note: When passing a two numbers in an array for size_or_point, it will be assumed to be a Point
     * @param {PointLike} origin
     * @param {PointLike | SizeLike} size_or_point
     */
    constructor(origin: PointLike, size_or_point: PointLike | SizeLike);
    constructor(x: number, y: number, width: number, height: number);

    tl(): Point;

    br(): Point;

    size(): Size;

    area(): number;

    contains(rect: RectLike): boolean;
}

export declare type ScalarLike =
    Scalar
    | [number]
    | [number, number]
    | [number, number, number]
    | [number, number, number, number];

export declare class Scalar {
    [index: number]: number;

    constructor();
    constructor(scalar: ScalarLike);
    constructor(v0: number, v1?: number, v2?: number, v3?: number);

    public multiply(scalar: Scalar, scale?: number): Scalar;

    public conjugate(): Scalar;

    public isReal(): boolean;
}

export declare type RangeLike = Range | {
    start: number; end: number;
} | [number, number];

export declare namespace Range {
    export function all(): Range;
}

export declare class Range {
    public start: number;
    public end: number;

    public size(): number;

    public isEmpty(): boolean;

    public isAll(): boolean;
}

export declare class MatrixExpression {
    public toMatrix(): Matrix
}

export declare interface TerminationCriteria {
    type: number; // integer
    maxCount: number; // integer
    epsilon: number; // double
}

/** Operations on arrays **/
export declare type BorderTypes = number;
export declare type CmpTypes = number;
export declare type DecompTypes = number;
export declare type DftFlags = number;
export declare type GemmFlags = number;
export declare type NormTypes = number;
export declare type RotateFlags = number;

export declare const BORDER_CONSTANT: BorderTypes;
export declare const BORDER_REPLICATE: BorderTypes;
export declare const BORDER_REFLECT: BorderTypes;
export declare const BORDER_WRAP: BorderTypes;
export declare const BORDER_REFLECT_101: BorderTypes;
export declare const BORDER_TRANSPARENT: BorderTypes;
export declare const BORDER_REFLECT101: BorderTypes;
export declare const BORDER_DEFAULT: BorderTypes;
export declare const BORDER_ISOLATED: BorderTypes;

export declare const CMP_EQ: CmpTypes;
export declare const CMP_GT: CmpTypes;
export declare const CMP_GE: CmpTypes;
export declare const CMP_LT: CmpTypes;
export declare const CMP_LE: CmpTypes;
export declare const CMP_NE: CmpTypes;

export declare const DECOMP_LU: DecompTypes;
export declare const DECOMP_SVD: DecompTypes;
export declare const DECOMP_EIG: DecompTypes;
export declare const DECOMP_CHOLESKY: DecompTypes;
export declare const DECOMP_QR: DecompTypes;
export declare const DECOMP_NORMAL: DecompTypes;

export declare const DFT_INVERSE: DftFlags;
export declare const DFT_SCALE: DftFlags;
export declare const DFT_ROWS: DftFlags;
export declare const DFT_COMPLEX_OUTPUT: DftFlags;
export declare const DFT_REAL_OUTPUT: DftFlags;
export declare const DFT_COMPLEX_INPUT: DftFlags;
export declare const DCT_INVERSE: DftFlags;
export declare const DCT_ROWS: DftFlags;

export declare const GEMM_1_T: GemmFlags;
export declare const GEMM_2_T: GemmFlags;
export declare const GEMM_3_T: GemmFlags;

export declare const NORM_INF: NormTypes;
export declare const NORM_L1: NormTypes;
export declare const NORM_L2: NormTypes;
export declare const NORM_L2SQR: NormTypes;
export declare const NORM_HAMMING: NormTypes;
export declare const NORM_HAMMING2: NormTypes;
export declare const NORM_TYPE_MASK: NormTypes;
export declare const NORM_RELATIVE: NormTypes;
export declare const NORM_MINMAX: NormTypes;

export declare const ROTATE_90_CLOCKWISE: RotateFlags;
export declare const ROTATE_180: RotateFlags;
export declare const ROTATE_90_COUNTERCLOCKWISE: RotateFlags;

export class RNG {}

export declare function absdiff(src1: InputArray, src2: InputArray, dst: OutputArray): void;

export declare function add(src1: InputArray, src2: InputArray, dst: OutputArray, mask?: InputArray /* = noArray() */, dtype?: number /* = -1 */): void;

export declare function addWeighted(src1: InputArray, alpha: number, src2: InputArray, beta: number, gamma: number, dst: OutputArray, dtype?: number /* = -1 */): void;

export declare function batchDistance(src1: InputArray, src2: InputArray, dist: OutputArray, dtype: number, nidx: OutputArray, normType?: number /* = NORM_L2 */, K?: number /* = 0 */, mask?: InputArray /* = noArray() */, update?: number /* = 0 */, crosscheck?: boolean /* = false */): void;

export declare function bitwiseAnd(src1: InputArray, src2: InputArray, dst: OutputArray, mask?: InputArray /* = noArray() */): void;

export declare function bitwiseNot(src: InputArray, dst: OutputArray, mask?: InputArray /* = noArray() */): void;

export declare function bitwiseOr(src1: InputArray, src2: InputArray, dst: OutputArray, mask?: InputArray /* = noArray() */): void;

export declare function bitwiseXor(src1: InputArray, src2: InputArray, dst: OutputArray, mask?: InputArray /* = noArray() */): void;

export declare function borderInterpolate(p: number, len: number, borderType: number): number;

export declare function calcCovarMatrix(samples: Matrix, nsamples: number, covar: Matrix, mean: Matrix, flags: number, ctype?: number /* = CV_64F */): void;
export declare function calcCovarMatrix(samples: InputArray, covar: OutputArray, mean: InputOutputArray, flags: number, ctype?: number /* = CV_64F */): void;

export declare function cartToPolar(x: InputArray, y: InputArray, magnitude: OutputArray, angle: OutputArray, angleInDegrees?: boolean /* = false */): void;

export declare function checkRange(a: InputArray, quiet?: boolean /* = true */, pos?: Point /* = 0 */, minVal?: number /* = -DBL_MAX */, maxVal?: number /* = DBL_MAX */): boolean;

export declare function compare(src1: InputArray, src2: InputArray, dst: OutputArray, cmpop: number): void;

export declare function completeSymm(mtx: InputOutputArray, lowerToUpper?: boolean /* = false */): void;

export declare function convertFp16(src: InputArray, dst: OutputArray): void;

export declare function convertScaleAbs(src: InputArray, dst: OutputArray, alpha?: number /* = 1 */, beta?: number /* = 0 */): void;

export declare function copyMakeBorder(src: InputArray, dst: OutputArray, top: number, bottom: number, left: number, right: number, borderType: number, value?: Scalar /* = Scalar() */): void;

export declare function countNonZero(src: InputArray): number;

export declare function dct(src: InputArray, dst: OutputArray, flags?: number /* = 0 */): void;

export declare function determinant(mtx: InputArray): number;

export declare function dft(src: InputArray, dst: OutputArray, flags?: number /* = 0 */, nonzeroRows?: number /* = 0 */): void;

export declare function divide(src1: InputArray, src2: InputArray, dst: OutputArray, scale?: number /* = 1 */, dtype?: number /* = -1 */): void;
export declare function divide(scale: number, src2: InputArray, dst: OutputArray, dtype?: number /* = -1 */): void;

export declare function eigen(src: InputArray, eigenvalues: OutputArray, eigenvectors?: OutputArray /* = noArray() */): boolean;

export declare function exp(src: InputArray, dst: OutputArray): void;

export declare function extractChannel(src: InputArray, dst: OutputArray, coi: number): void;

export declare function findNonZero(src: InputArray, idx: OutputArray): void;

export declare function flip(src: InputArray, dst: OutputArray, flipCode: number): void;

export declare function gemm(src1: InputArray, src2: InputArray, alpha: number, src3: InputArray, beta: number, dst: OutputArray, flags?: number /* = 0 */): void;

export declare function getOptimalDFTSize(vecsize: number): number;

export declare function hconcat(src: InputArray[], dst: OutputArray): void;

export declare function idct(src: InputArray, dst: OutputArray, flags?: number /* = 0 */): void;

export declare function idft(src: InputArray, dst: OutputArray, flags?: number /* = 0 */, nonzeroRows?: number /* = 0 */): void;

export declare function inRange(src: InputArray, lowerb: InputArray, upperb: InputArray, dst: OutputArray): void;

export declare function insertChannel(src: InputArray, dst: InputOutputArray, coi: number): void;

export declare function invert(src: InputArray, dst: OutputArray, flags?: number /* = DECOMP_LU */): number;

export declare function log(src: InputArray, dst: OutputArray): void;

export declare function lut(src: InputArray, lut: InputArray, dst: OutputArray): void;

export declare function magnitude(x: InputArray, y: InputArray, magnitude: OutputArray): void;

export declare function mahalanobis(v1: InputArray, v2: InputArray, icovar: InputArray): number;

export declare function max(src1: InputArray, src2: InputArray, dst: OutputArray): void;
export declare function max(src1: Matrix, src2: Matrix, dst: Matrix): void;
export declare function max(src1: UnifiedMatrix, src2: UnifiedMatrix, dst: UnifiedMatrix): void;

export declare function mean(src: InputArray, mask?: InputArray /* = noArray() */): Scalar;

export declare function meanStdDev(src: InputArray, mean: OutputArray, stddev: OutputArray, mask?: InputArray /* = noArray() */): void;

export declare function merge(mv: InputArray[], dst: OutputArray): void;

export declare function min(src1: InputArray, src2: InputArray, dst: OutputArray): void;
export declare function min(src1: Matrix, src2: Matrix, dst: Matrix): void;
export declare function min(src1: UnifiedMatrix, src2: UnifiedMatrix, dst: UnifiedMatrix): void;

export declare function minMaxIdx(src: InputArray, minVal: number, maxVal?: number /* = 0 */, minIdx?: number /* = 0 */, maxIdx?: number /* = 0 */, mask?: InputArray /* = noArray() */): void;

export declare function minMaxLoc(src: InputArray, mask?: InputArray /* = noArray() */): { minVal: number, maxVal: number, minLoc: Point, maxLoc: Point };
// export declare function minMaxLoc(a: SparseMat): { minVal: number, maxVal: number, minIdx: number, minIdx: number };

export declare function mixChannels(src: InputArray[], dst: InputOutputArray[], fromTo: number[]): void;

export declare function mulSpectrums(a: InputArray, b: InputArray, c: OutputArray, flags: number, conjB?: boolean /* = false */): void;

export declare function multiply(src1: InputArray, src2: InputArray, dst: OutputArray, scale?: number /* = 1 */, dtype?: number /* = -1 */): void;

export declare function mulTransposed(src: InputArray, dst: OutputArray, aTa: boolean, delta?: InputArray /* = noArray() */, scale?: number /* = 1 */, dtype?: number /* = -1 */): void;

export declare function norm(src1: InputArray, normType?: number /* = NORM_L2 */, mask?: InputArray /* = noArray() */): number;
export declare function norm(src1: InputArray, src2: InputArray, normType?: number /* = NORM_L2 */, mask?: InputArray /* = noArray() */): number;
// export declare function norm(src: SparseMat, normType: number): number;

export declare function normalize(src: InputArray, dst: InputOutputArray, alpha?: number /* = 1 */, beta?: number /* = 0 */, norm_type?: number /* = NORM_L2 */, dtype?: number /* = -1 */, mask?: InputArray /* = noArray() */): void;
// export declare function normalize(src: SparseMat, dst: SparseMat, alpha: number, normType: number): void;

export declare function patchNaNs(a: InputOutputArray, val?: number /* = 0 */): void;

export declare function pcaBackProject(data: InputArray, mean: InputArray, eigenvectors: InputArray, result: OutputArray): void;

export declare function pcaCompute(data: InputArray, mean: InputOutputArray, eigenvectors: OutputArray, maxComponents?: number /* = 0 */): void;
export declare function pcaCompute(data: InputArray, mean: InputOutputArray, eigenvectors: OutputArray, retainedVariance: number): void;

export declare function pcaProject(data: InputArray, mean: InputArray, eigenvectors: InputArray, result: OutputArray): void;

export declare function perspectiveTransform(src: InputArray, dst: OutputArray, m: InputArray): void;

export declare function phase(x: InputArray, y: InputArray, angle: OutputArray, angleInDegrees?: boolean /* = false */): void;

export declare function polarToCart(magnitude: InputArray, angle: InputArray, x: OutputArray, y: OutputArray, angleInDegrees?: boolean /* = false */): void;

export declare function pow(src: InputArray, power: number, dst: OutputArray): void;

export declare function psnr(src1: InputArray, src2: InputArray): number;

export declare function randn(dst: InputOutputArray, mean: InputArray, stddev: InputArray): void;

export declare function randShuffle(dst: InputOutputArray, iterFactor?: number /* = 1. */, rng?: RNG /* = 0 */): void;

export declare function randu(dst: InputOutputArray, low: InputArray, high: InputArray): void;

export declare function reduce(src: InputArray, dst: OutputArray, dim: number, rtype: number, dtype?: number /* = -1 */): void;

export declare function repeat(src: InputArray, ny: number, nx: number, dst: OutputArray): void;
export declare function repeat(src: Matrix, ny: number, nx: number): Matrix;

export declare function rotate(src: InputArray, dst: OutputArray, rotateCode: number): void;

export declare function scaleAdd(src1: InputArray, alpha: number, src2: InputArray, dst: OutputArray): void;

export declare function setIdentity(mtx: InputOutputArray, s?: Scalar /* = Scalar(1) */): void;

export declare function setRNGSeed(seed: number): void;

export declare function solve(src1: InputArray, src2: InputArray, dst: OutputArray, flags?: number /* = DECOMP_LU */): boolean;

export declare function solveCubic(coeffs: InputArray, roots: OutputArray): number;

export declare function solvePoly(coeffs: InputArray, roots: OutputArray, maxIters?: number /* = 300 */): number;

export declare function sort(src: InputArray, dst: OutputArray, flags: number): void;

export declare function sortIdx(src: InputArray, dst: OutputArray, flags: number): void;

export declare function split(src: Matrix, mvbegin: Matrix): void;
export declare function split(m: InputArray, mv: OutputArray[]): void;

export declare function sqrt(src: InputArray, dst: OutputArray): void;

export declare function subtract(src1: InputArray, src2: InputArray, dst: OutputArray, mask?: InputArray /* = noArray() */, dtype?: number /* = -1 */): void;

export declare function sum(src: InputArray): Scalar;

export declare function svBackSubst(w: InputArray, u: InputArray, vt: InputArray, rhs: InputArray, dst: OutputArray): void;

export declare function svDecomp(src: InputArray, w: OutputArray, u: OutputArray, vt: OutputArray, flags?: number /* = 0 */): void;

export declare function theRNG(): RNG;

export declare function trace(mtx: InputArray): Scalar;

export declare function transform(src: InputArray, dst: OutputArray, m: InputArray): void;

export declare function transpose(src: InputArray, dst: OutputArray): void;

export declare function vconcat(src: InputArray[], dst: OutputArray): void;

export declare const VERSION: string;

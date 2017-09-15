import { InputArray, Matrix } from '../core';

export type EncodeExtensions = '.png' | '.jpg' | '.webp' | '.ppm' | '.pgm' | '.pbm';

export type ImreadModes = number;
export type ImwriteFlags = number;
export type ImwritePAMFlags = number;
export type ImwritePNGFlags = number;

export const IMREAD_UNCHANGED: ImreadModes;
export const IMREAD_GRAYSCALE: ImreadModes;
export const IMREAD_COLOR: ImreadModes;
export const IMREAD_ANYDEPTH: ImreadModes;
export const IMREAD_ANYCOLOR: ImreadModes;
export const IMREAD_LOAD_GDAL: ImreadModes;
export const IMREAD_REDUCED_GRAYSCALE_2: ImreadModes;
export const IMREAD_REDUCED_COLOR_2: ImreadModes;
export const IMREAD_REDUCED_GRAYSCALE_4: ImreadModes;
export const IMREAD_REDUCED_COLOR_4: ImreadModes;
export const IMREAD_REDUCED_GRAYSCALE_8: ImreadModes;
export const IMREAD_REDUCED_COLOR_8: ImreadModes;
export const IMREAD_IGNORE_ORIENTATION: ImreadModes;

export const IMWRITE_JPEG_QUALITY: ImwriteFlags;
export const IMWRITE_JPEG_PROGRESSIVE: ImwriteFlags;
export const IMWRITE_JPEG_OPTIMIZE: ImwriteFlags;
export const IMWRITE_JPEG_RST_INTERVAL: ImwriteFlags;
export const IMWRITE_JPEG_LUMA_QUALITY: ImwriteFlags;
export const IMWRITE_JPEG_CHROMA_QUALITY: ImwriteFlags;
export const IMWRITE_PNG_COMPRESSION: ImwriteFlags;
export const IMWRITE_PNG_STRATEGY: ImwriteFlags;
export const IMWRITE_PNG_BILEVEL: ImwriteFlags;
export const IMWRITE_PXM_BINARY: ImwriteFlags;
export const IMWRITE_WEBP_QUALITY: ImwriteFlags;
export const IMWRITE_PAM_TUPLETYPE: ImwriteFlags;

export const IMWRITE_PAM_FORMAT_NULL: ImwritePAMFlags;
export const IMWRITE_PAM_FORMAT_BLACKANDWHITE: ImwritePAMFlags;
export const IMWRITE_PAM_FORMAT_GRAYSCALE: ImwritePAMFlags;
export const IMWRITE_PAM_FORMAT_GRAYSCALE_ALPHA: ImwritePAMFlags;
export const IMWRITE_PAM_FORMAT_RGB: ImwritePAMFlags;
export const IMWRITE_PAM_FORMAT_RGB_ALPHA: ImwritePAMFlags;

export const IMWRITE_PNG_STRATEGY_DEFAULT: ImwritePNGFlags;
export const IMWRITE_PNG_STRATEGY_FILTERED: ImwritePNGFlags;
export const IMWRITE_PNG_STRATEGY_HUFFMAN_ONLY: ImwritePNGFlags;
export const IMWRITE_PNG_STRATEGY_RLE: ImwritePNGFlags;
export const IMWRITE_PNG_STRATEGY_FIXED: ImwritePNGFlags;

export function imread(filename: string, flags?: number): Promise<Matrix>;
export function imread(filename: string, callback: (err: Error, image: Matrix) => void): void;
export function imread(filename: string, flags: number, callback: (err: Error, image: Matrix) => void): void;

export function imreadSync(filename: string, flags?: number): Matrix;

export function imdecode(buffer: Buffer, flags?: number): Promise<Matrix>;
export function imdecode(buffer: Buffer, callback: (err: Error, image: Matrix) => void): void;
export function imdecode(buffer: Buffer, flags: number, callback: (err: Error, image: Matrix) => void): void;

export function imdecodeSync(buffer: Buffer, flags?: number): Matrix;

export function imencode(ext: EncodeExtensions, img: InputArray, params?: number[]): Promise<Buffer>;
export function imencode(ext: EncodeExtensions, img: InputArray, callback: (err: Error, buf: Buffer) => void): void;
export function imencode(ext: EncodeExtensions, img: InputArray, params: number[], callback: (err: Error, buf: Buffer) => void): void;

export function imencodeSync(ext: EncodeExtensions, img: InputArray, params: number[]): Buffer;

export function imreadmulti(filename: string, flags?: number): Promise<Matrix[]>;
export function imreadmulti(filename: string, callback: (err: Error, images: Matrix[]) => void): void;
export function imreadmulti(filename: string, flags: number, callback: (err: Error, images: Matrix[]) => void): void;

export function imreadmultiSync(filename: string, flags?: number): Matrix[];

export function imwrite(filename: string, img: InputArray, params?: number[]): Promise<boolean>;
export function imwrite(filename: string, img: InputArray, callback: (err: Error, success: boolean) => void): void;
export function imwrite(filename: string, img: InputArray, params: number[], callback: (err: Error, success: boolean) => void): void;

export function imwriteSync(filename: string, img: InputArray, params: number[]): boolean;

declare module '../core' {
    namespace Matrix {
        export function imread(filename: string, flags?: number): Promise<Matrix>;
        export function imread(filename: string, callback: (err: Error, image: Matrix) => void): void;
        export function imread(filename: string, flags: number, callback: (err: Error, image: Matrix) => void): void;

        export function imreadSync(filename: string, flags?: number): Matrix;

        export function imdecode(buffer: Buffer, flags?: number): Promise<Matrix>;
        export function imdecode(buffer: Buffer, callback: (err: Error, image: Matrix) => void): void;
        export function imdecode(buffer: Buffer, flags: number, callback: (err: Error, image: Matrix) => void): void;

        export function imdecodeSync(buffer: Buffer, flags?: number): Matrix;

        export function imreadmulti(filename: string, flags?: number): Promise<Matrix[]>;
        export function imreadmulti(filename: string, callback: (err: Error, images: Matrix[]) => void): void;
        export function imreadmulti(filename: string, flags: number, callback: (err: Error, images: Matrix[]) => void): void;

        export function imreadmultiSync(filename: string, flags?: number): Matrix[];
    }

    interface Matrix {
        imencode(ext: EncodeExtensions, params: number[]): Promise<Buffer>;
        imencode(ext: EncodeExtensions, callback: (err: Error, buf: Buffer) => void): void;
        imencode(ext: EncodeExtensions, params: number[], callback: (err: Error, buf: Buffer) => void): void;

        imencodeSync(ext: EncodeExtensions, params: number[]): Buffer;

        imwrite(filename: string, params: number[]): Promise<boolean>;
        imwrite(filename: string, callback: (err: Error, success: boolean) => void): void;
        imwrite(filename: string, params: number[], callback: (err: Error, success: boolean) => void): void;

        imwriteSync(filename: string, params: number[]): boolean;
    }
}

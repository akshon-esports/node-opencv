import { InputArray, Matrix, Rect } from '../core/index';

export type ComponentLevel = number;
export type ClassifierType = number;
export type DecoderMode = number;
export type OCREngineMode = number;
export type PageSegMode = number;

export const OCR_LEVEL_WORD: ComponentLevel;
export const OCR_LEVEL_TEXTLINE: ComponentLevel;

export const OCR_KNN_CLASSIFIER: ClassifierType;
export const OCR_CNN_CLASSIFIER: ClassifierType;

export const OCR_DECODER_VITERBI: DecoderMode;

export const OEM_TESSERACT_ONLY: OCREngineMode;
export const OEM_CUBE_ONLY: OCREngineMode;
export const OEM_TESSERACT_CUBE_COMBINED: OCREngineMode;
export const OEM_DEFAULT: OCREngineMode;

export const PSM_OSD_ONLY: PageSegMode;
export const PSM_AUTO_OSD: PageSegMode;
export const PSM_AUTO_ONLY: PageSegMode;
export const PSM_AUTO: PageSegMode;
export const PSM_SINGLE_COLUMN: PageSegMode;
export const PSM_SINGLE_BLOCK_VERT_TEXT: PageSegMode;
export const PSM_SINGLE_BLOCK: PageSegMode;
export const PSM_SINGLE_LINE: PageSegMode;
export const PSM_SINGLE_WORD: PageSegMode;
export const PSM_CIRCLE_WORD: PageSegMode;
export const PSM_SINGLE_CHAR: PageSegMode;

export interface OCRResult {
    output: string;
    components?: {
        rects: Rect[];
        texts: string[];
        confidences: number[];
    }
}

export class OCRTesseract {
    constructor(datapath?: string, language?: string, charWhitelist?: string, oem?: OCREngineMode, psmode?: PageSegMode);
    run(image: Matrix, componentLevel?: ComponentLevel): OCRResult;
    run(image: Matrix, mask: Matrix, componentLevel?: ComponentLevel): OCRResult;
    // TODO can't differentiate
    // run(image: InputArray, minConfidence: number, componentLevel?: ComponentLevel): string;
    // run(image: InputArray, mask: InputArray, minConfidence: number, componentLevel?: ComponentLevel): string;
}

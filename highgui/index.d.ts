import { InputArray, Rect, RectLike, SizeLike } from '../core';

export type MouseEventFlags = number;
export type MouseEventTypes = number;
export type QtButtonTypes = number;
export type QtFontStyles = number;
export type QtFontWeights = number;
export type WindowFlags = number;
export type WindowPropertyFlags = number;

export const EVENT_FLAG_LBUTTON: MouseEventFlags;
export const EVENT_FLAG_RBUTTON: MouseEventFlags;
export const EVENT_FLAG_MBUTTON: MouseEventFlags;
export const EVENT_FLAG_CTRLKEY: MouseEventFlags;
export const EVENT_FLAG_SHIFTKEY: MouseEventFlags;
export const EVENT_FLAG_ALTKEY: MouseEventFlags;

export const EVENT_MOUSEMOVE: MouseEventTypes;
export const EVENT_LBUTTONDOWN: MouseEventTypes;
export const EVENT_RBUTTONDOWN: MouseEventTypes;
export const EVENT_MBUTTONDOWN: MouseEventTypes;
export const EVENT_LBUTTONUP: MouseEventTypes;
export const EVENT_RBUTTONUP: MouseEventTypes;
export const EVENT_MBUTTONUP: MouseEventTypes;
export const EVENT_LBUTTONDBLCLK: MouseEventTypes;
export const EVENT_RBUTTONDBLCLK: MouseEventTypes;
export const EVENT_MBUTTONDBLCLK: MouseEventTypes;
export const EVENT_MOUSEWHEEL: MouseEventTypes;
export const EVENT_MOUSEHWHEEL: MouseEventTypes;

export const QT_PUSH_BUTTON: QtButtonTypes;
export const QT_CHECKBOX: QtButtonTypes;
export const QT_RADIOBOX: QtButtonTypes;
export const QT_NEW_BUTTONBAR: QtButtonTypes;

export const QT_STYLE_NORMAL: QtFontStyles;
export const QT_STYLE_ITALIC: QtFontStyles;
export const QT_STYLE_OBLIQUE: QtFontStyles;

export const QT_FONT_LIGHT: QtFontWeights;
export const QT_FONT_NORMAL: QtFontWeights;
export const QT_FONT_DEMIBOLD: QtFontWeights;
export const QT_FONT_BOLD: QtFontWeights;
export const QT_FONT_BLACK: QtFontWeights;

export const WINDOW_NORMAL: WindowFlags;
export const WINDOW_AUTOSIZE: WindowFlags;
export const WINDOW_OPENGL: WindowFlags;
export const WINDOW_FULLSCREEN: WindowFlags;
export const WINDOW_FREERATIO: WindowFlags;
export const WINDOW_KEEPRATIO: WindowFlags;
export const WINDOW_GUI_EXPANDED: WindowFlags;
export const WINDOW_GUI_NORMAL: WindowFlags;

export const WND_PROP_FULLSCREEN: WindowPropertyFlags;
export const WND_PROP_AUTOSIZE: WindowPropertyFlags;
export const WND_PROP_ASPECT_RATIO: WindowPropertyFlags;
export const WND_PROP_OPENGL: WindowPropertyFlags;
export const WND_PROP_VISIBLE: WindowPropertyFlags;

export type TrackbarCallback = (position: number) => void;
export type MouseCallback = (event: MouseEventTypes, x: number, y: number, flags: number) => void;

export function createTrackbar(trackbarname: string, winname: string, value: number, count: number, onChange?: TrackbarCallback /* = 0 */): number;
export function destroyAllWindows(): void;
export function destroyWindow(winname: string): void;
export function getMouseWheelDelta(flags: number): number;
export function getTrackbarPos(trackbarname: string, winname: string): number;
export function getWindowProperty(winname: string, prop_id: number): number;
export function imshow(winname: string, mat: InputArray): void;
export function moveWindow(winname: string, x: number, y: number): void;
export function namedWindow(winname: string, flags?: number /* = WINDOW_AUTOSIZE */): void;
export function resizeWindow(winname: string, width: number, height: number): void;
export function selectROI(windowName: string, img: InputArray, showCrosshair?: boolean /* = true */, fromCenter?: boolean /* = false */): Rect;
export function selectROI(img: InputArray, showCrosshair?: boolean /* = true */, fromCenter?: boolean /* = false */): Rect;
export function selectROIs(windowName: string, img: InputArray, showCrosshair?: boolean /* = true */, fromCenter?: boolean /* = false */): Rect[];
export function setMouseCallback(winname: string, onMouse: MouseCallback): void;
export function setTrackbarMax(trackbarname: string, winname: string, maxval: number): void;
export function setTrackbarMin(trackbarname: string, winname: string, minval: number): void;
export function setTrackbarPos(trackbarname: string, winname: string, pos: number): void;
export function setWindowProperty(winname: string, prop_id: number, prop_value: number): void;
export function setWindowTitle(winname: string, title: string): void;
export function startWindowThread(): number;
export function waitKey(delay?: number /* = 0 */): number;
export function waitKeyEx(delay?: number /* = 0 */): number;

export interface TrackerBar {
    getPos(): number;
    setMax(maxval: number): void;
    setMin(minval: number): void;
    setPos(pos: number): void;
}

export class NamedWindow {
    public constructor(name: string, flags?: number);

    public createTrackerbar(name: string): TrackerBar;

    public destroy();

    public getProperty(propId: number): number;

    public show(mat: InputArray): void;

    public showImage(mat: InputArray): void;

    public move(x: number, y: number): void;

    public resize(width: number, height: number): void;

    public selectROI(img: InputArray, showCrosshair?: boolean, fromCenter?: boolean): Rect;

    public selectROIMulti(img: InputArray, showCrosshair?: boolean, fromCenter?: boolean): Rect[];

    public setMouseCallback(onMouse: MouseCallback): void;

    public setProperty(propId: number, value: number): void;

    public setTitle(title: string): void;
}

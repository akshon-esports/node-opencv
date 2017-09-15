import { Matrix, OutputArray, SizeLike } from '../core/index';
import { Stream } from 'stream';

export type VideoCaptureAPIs = number;
export type VideoCaptureModes = number;
export type VideoCaptureProperties = number;
export type VideoWriterProperties = number;

export const CAP_ANY: VideoCaptureAPIs;
export const CAP_VFW: VideoCaptureAPIs;
export const CAP_V4L: VideoCaptureAPIs;
export const CAP_V4L2: VideoCaptureAPIs;
export const CAP_FIREWIRE: VideoCaptureAPIs;
export const CAP_FIREWARE: VideoCaptureAPIs;
export const CAP_IEEE1394: VideoCaptureAPIs;
export const CAP_DC1394: VideoCaptureAPIs;
export const CAP_CMU1394: VideoCaptureAPIs;
export const CAP_QT: VideoCaptureAPIs;
export const CAP_UNICAP: VideoCaptureAPIs;
export const CAP_DSHOW: VideoCaptureAPIs;
export const CAP_PVAPI: VideoCaptureAPIs;
export const CAP_OPENNI: VideoCaptureAPIs;
export const CAP_OPENNI_ASUS: VideoCaptureAPIs;
export const CAP_ANDROID: VideoCaptureAPIs;
export const CAP_XIAPI: VideoCaptureAPIs;
export const CAP_AVFOUNDATION: VideoCaptureAPIs;
export const CAP_GIGANETIX: VideoCaptureAPIs;
export const CAP_MSMF: VideoCaptureAPIs;
export const CAP_WINRT: VideoCaptureAPIs;
export const CAP_INTELPERC: VideoCaptureAPIs;
export const CAP_OPENNI2: VideoCaptureAPIs;
export const CAP_OPENNI2_ASUS: VideoCaptureAPIs;
export const CAP_GPHOTO2: VideoCaptureAPIs;
export const CAP_GSTREAMER: VideoCaptureAPIs;
export const CAP_FFMPEG: VideoCaptureAPIs;
export const CAP_IMAGES: VideoCaptureAPIs;
export const CAP_ARAVIS: VideoCaptureAPIs;
export const CAP_OPENCV_MJPEG: VideoCaptureAPIs;
export const CAP_INTEL_MFX: VideoCaptureAPIs;

export const CAP_MODE_BGR: VideoCaptureModes;
export const CAP_MODE_RGB: VideoCaptureModes;
export const CAP_MODE_GRAY: VideoCaptureModes;
export const CAP_MODE_YUYV: VideoCaptureModes;

export const CAP_PROP_POS_MSEC: VideoCaptureProperties;
export const CAP_PROP_POS_FRAMES: VideoCaptureProperties;
export const CAP_PROP_POS_AVI_RATIO: VideoCaptureProperties;
export const CAP_PROP_FRAME_WIDTH: VideoCaptureProperties;
export const CAP_PROP_FRAME_HEIGHT: VideoCaptureProperties;
export const CAP_PROP_FPS: VideoCaptureProperties;
export const CAP_PROP_FOURCC: VideoCaptureProperties;
export const CAP_PROP_FRAME_COUNT: VideoCaptureProperties;
export const CAP_PROP_FORMAT: VideoCaptureProperties;
export const CAP_PROP_MODE: VideoCaptureProperties;
export const CAP_PROP_BRIGHTNESS: VideoCaptureProperties;
export const CAP_PROP_CONTRAST: VideoCaptureProperties;
export const CAP_PROP_SATURATION: VideoCaptureProperties;
export const CAP_PROP_HUE: VideoCaptureProperties;
export const CAP_PROP_GAIN: VideoCaptureProperties;
export const CAP_PROP_EXPOSURE: VideoCaptureProperties;
export const CAP_PROP_CONVERT_RGB: VideoCaptureProperties;
export const CAP_PROP_WHITE_BALANCE_BLUE_U: VideoCaptureProperties;
export const CAP_PROP_RECTIFICATION: VideoCaptureProperties;
export const CAP_PROP_MONOCHROME: VideoCaptureProperties;
export const CAP_PROP_SHARPNESS: VideoCaptureProperties;
export const CAP_PROP_AUTO_EXPOSURE: VideoCaptureProperties;
export const CAP_PROP_GAMMA: VideoCaptureProperties;
export const CAP_PROP_TEMPERATURE: VideoCaptureProperties;
export const CAP_PROP_TRIGGER: VideoCaptureProperties;
export const CAP_PROP_TRIGGER_DELAY: VideoCaptureProperties;
export const CAP_PROP_WHITE_BALANCE_RED_V: VideoCaptureProperties;
export const CAP_PROP_ZOOM: VideoCaptureProperties;
export const CAP_PROP_FOCUS: VideoCaptureProperties;
export const CAP_PROP_GUID: VideoCaptureProperties;
export const CAP_PROP_ISO_SPEED: VideoCaptureProperties;
export const CAP_PROP_BACKLIGHT: VideoCaptureProperties;
export const CAP_PROP_PAN: VideoCaptureProperties;
export const CAP_PROP_TILT: VideoCaptureProperties;
export const CAP_PROP_ROLL: VideoCaptureProperties;
export const CAP_PROP_IRIS: VideoCaptureProperties;
export const CAP_PROP_SETTINGS: VideoCaptureProperties;
export const CAP_PROP_BUFFERSIZE: VideoCaptureProperties;
export const CAP_PROP_AUTOFOCUS: VideoCaptureProperties;

export const VIDEOWRITER_PROP_QUALITY: VideoWriterProperties;
export const VIDEOWRITER_PROP_FRAMEBYTES: VideoWriterProperties;
export const VIDEOWRITER_PROP_NSTRIPES: VideoWriterProperties;

export class VideoCapture {
    public constructor(index: number);
    public constructor(filename: string, apiPreferences?: number);

    public get(propId: VideoCaptureProperties): number;

    public grab(): boolean;

    public isOpened(): boolean;

    public read(): Matrix;
    public read(image: OutputArray): boolean;

    public release(): void;

    public retrieve(flag?: number /* = 0 */): Matrix;
    public retrieve(image: OutputArray, flag?: number /* = 0 */): boolean;

    public set(propId: VideoCaptureProperties, value: number): boolean;
}

export class VideoCaptureStream extends Stream {
    public readable: boolean;

    public constructor(cap: VideoCapture);
    public constructor(index: number);
    public constructor(filename: string, apiPreferences?: number);

    public on(event: 'readable', callback: () => void): this;
    public on(event: 'error', callback: (error: Error) => void): this;
    public on(event: 'data', callback: (data: Matrix) => void): this;
    public on(event: 'end', callback: () => void): this;
    public on(event: 'close', callback: () => void): this;

    public read(): Matrix;
    public pause(): void;
    public isPaused(): void;
    public resume(): void;
    public destroy(): void;
}

export type fcc = number;

export function fourcc(fourcc: string): fcc;
export function fourcc(c1: number, c2: number, c3: number, c4: number): fcc;

export class VideoWriter {
    public constructor(filename: string, fourcc: fcc, frameSize: SizeLike, isColor?: boolean);
    public constructor(filename: string, apiPreference: number, fourcc: fcc, fps: number, frameSize: SizeLike, isColor?: boolean);

    public get(propId: VideoCaptureProperties): number;

    public isOpened(): boolean;

    public release(): void;

    public set(propId: VideoCaptureProperties, value: number): boolean;

    public write(image: Matrix)
}

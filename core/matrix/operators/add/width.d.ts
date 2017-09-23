import { Matrix } from '../../../';

declare module '../../../' {
    interface Matrix {
        width(): number;
    }
}

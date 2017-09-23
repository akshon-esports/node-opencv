import { Matrix } from '../../../';

declare module '../../../' {
    interface Matrix {
        height(): number;
    }
}

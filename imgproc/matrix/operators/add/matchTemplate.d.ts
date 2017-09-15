import { InputArray, Matrix } from '../../../../core';
import { TemplateMatchModes } from '../../../';

declare module '../../../../core' {
    interface Matrix {
        matchTemplate(templ: InputArray, method?: TemplateMatchModes, mask?: InputArray): Matrix
    }
}

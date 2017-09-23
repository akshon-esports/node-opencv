var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.gaussianBlur = function() {
  var out = new core.Matrix();
  imgproc.gaussianBlur.apply(global, [this, out].concat(Array.from(arguments)));
  return out;
};

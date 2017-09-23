var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.bilateralFilter = function() {
  var out = new core.Matrix();
  imgproc.bilateralFilter.apply(global, [this, out].concat(Array.from(arguments)));
  return out;
};

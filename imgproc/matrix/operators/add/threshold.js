var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.threshold = function() {
  var out = new core.Matrix();
  imgproc.threshold.apply(global, [this, out].concat(Array.from(arguments)));
  return out;
};

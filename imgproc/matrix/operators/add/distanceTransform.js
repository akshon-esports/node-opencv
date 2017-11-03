var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.distanceTransform = function() {
  var out = new core.Matrix();
  var labels = new core.Matrix();
  imgproc.distanceTransform.apply(global, [this, out, labels].concat(Array.from(arguments)));
  return out;
};

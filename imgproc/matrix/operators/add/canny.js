var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.canny = function() {
  var out = new core.Matrix();
  imgproc.canny.apply(global, [this, out].concat(Array.from(arguments)));
  return out;
};

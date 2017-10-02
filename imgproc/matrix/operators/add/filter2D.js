var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.filter2D = function() {
  var out = new core.Matrix();
  imgproc.filter2D.apply(global, [this, out].concat(Array.from(arguments)));
  return out;
};

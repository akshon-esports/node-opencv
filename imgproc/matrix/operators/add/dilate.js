var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.dilate = function() {
  var out = new core.Matrix();
  imgproc.dilate.apply(global, [this, out].concat(Array.from(arguments)));
  return out;
};

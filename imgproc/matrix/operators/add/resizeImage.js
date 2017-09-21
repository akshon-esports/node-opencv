var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.resizeImage = function() {
  var out = new core.Matrix();
  imgproc.resize.apply(global, [this, out].concat(Array.from(arguments)));
  return out;
};

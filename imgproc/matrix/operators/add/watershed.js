var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.watershed = function() {
  var out = new core.Matrix();
  imgproc.watershed.apply(global, [this, out].concat(Array.from(arguments)));
  return out;
};

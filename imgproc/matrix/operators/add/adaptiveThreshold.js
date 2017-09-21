var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.adaptiveThreshold = function() {
  var out = new core.Matrix();
  imgproc.adaptiveThreshold.apply(global, [this, out].concat(Array.from(arguments)));
  return out;
};

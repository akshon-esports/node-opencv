var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.threshold = function() {
  var out = new core.Matrix();
  arguments.splice(0, 0, this, out);
  imgproc.threshold.apply(global, arguments);
  return out;
};

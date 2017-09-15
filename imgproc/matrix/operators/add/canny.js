var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.canny = function() {
  var out = new core.Matrix();
  arguments.splice(0, 0, this, out);
  imgproc.canny.apply(global, arguments);
  return out;
};

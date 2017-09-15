var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.resizeImage = function() {
  var out = new core.Matrix();
  arguments.splice(0, 0, this, out);
  imgproc.resize.apply(global, arguments);
  return out;
};

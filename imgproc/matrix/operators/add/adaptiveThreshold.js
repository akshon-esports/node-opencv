var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.adaptiveThreshold = function() {
  var out = new core.Matrix();
  arguments.splice(0, 0, this, out);
  imgproc.adaptiveThreshold.apply(global, arguments);
  return out;
};

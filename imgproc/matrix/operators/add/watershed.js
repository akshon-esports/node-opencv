var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.watershed = function() {
  var out = new core.Matrix();
  arguments.splice(0, 0, this, out);
  imgproc.watershed.apply(global, arguments);
  return out;
};

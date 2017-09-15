var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.convertColor = function() {
  var out = new core.Matrix();
  arguments.splice(0, 0, this, out);
  imgproc.cvtColor.apply(global, arguments);
  return out;
};

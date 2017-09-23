var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.equalizeHist = function() {
  var out = new core.Matrix();
  imgproc.equalizeHist.apply(global, [this, out]);
  return out;
};

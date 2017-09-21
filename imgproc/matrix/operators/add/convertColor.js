var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.convertColor = function() {
  var out = new core.Matrix();
  imgproc.cvtColor.apply(global, [this, out].concat(Array.from(arguments)));
  return out;
};

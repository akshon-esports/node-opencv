var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.matchTemplate = function() {
  arguments.splice(0, 0, this);
  var out = new core.Matrix();
  arguments.splice(2, 0, out);
  imgproc.matchTemplate.apply(global, arguments);
  return out;
};

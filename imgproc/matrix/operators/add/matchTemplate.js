var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.matchTemplate = function() {
  var out = new core.Matrix();
  var args = Array.from(arguments);
  args.splice(1, 0, out);
  args.splice(0, 0, this);
  core.matchTemplate.apply(global, args);
  return out;
};

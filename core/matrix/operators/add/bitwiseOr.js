var core = require('../../../');

core.Matrix.prototype.bitwiseOr = function() {
  var out = new core.Matrix();
  var args = Array.from(arguments);
  args.splice(1, 0, out);
  args.splice(0, 0, this);
  core.bitwiseOr.apply(global, args);
  return out;
};

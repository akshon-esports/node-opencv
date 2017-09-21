var core = require('../../../');

core.Matrix.prototype.bitwiseAnd = function() {
  var out = new core.Matrix();
  var args = Array.from(arguments);
  args.splice(1, 0, out);
  args.splice(0, 0, this);
  core.bitwiseAnd.apply(global, args);
  return out;
};

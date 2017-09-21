var core = require('../../../');

core.Matrix.prototype.bitwiseXor = function() {
  var out = new core.Matrix();
  var args = Array.from(arguments);
  args.splice(1, 0, out);
  args.splice(0, 0, this);
  core.bitwiseXor.apply(global, args);
  return out;
};

var core = require('../../../');

core.Matrix.prototype.bitwiseNot = function() {
  var out = new core.Matrix();
  var args = Array.from(arguments);
  core.bitwiseNot.apply(global, args.slice(0, 1).concat(out, args.slice(1)));
  return out;
};

var core = require('../../../');

core.Matrix.prototype.bitwiseNot = function() {
  var out = new core.Matrix();
  core.bitwiseNot.apply(global, [this, out].concat(Array.from(arguments)));
  return out;
};

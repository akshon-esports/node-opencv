var core = require('../../../');

core.Matrix.prototype.copyMakeBorder = function() {
  var out = new core.Matrix();
  core.copyMakeBorder.apply(global, [this, out].concat(Array.from(arguments)));
  return out;
};

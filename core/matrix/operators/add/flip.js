var core = require('../../../');

core.Matrix.prototype.flip = function() {
  var out = new core.Matrix();
  core.flip.apply(global, [this, out].concat(Array.from(arguments)));
  return out;
};

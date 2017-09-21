var core = require('../../../');

core.Matrix.prototype.minMaxLoc = function() {
  return core.minMaxLoc.apply(global, [this].concat(Array.from(arguments)));
};

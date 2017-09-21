var core = require('../../../');

core.Matrix.prototype.mean = function() {
  return core.mean.apply(global, [this].concat(Array.from(arguments)));
};

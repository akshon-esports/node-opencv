var core = require('../../../');

core.Matrix.prototype.minMaxLoc = function() {
  arguments.splice(0, 0, this);
  return core.minMaxLoc.apply(global, arguments);
};

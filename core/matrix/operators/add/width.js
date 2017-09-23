var core = require('../../../');

core.Matrix.prototype.width = function() {
  return this.size().width;
};

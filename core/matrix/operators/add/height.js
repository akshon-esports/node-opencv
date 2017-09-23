var core = require('../../../');

core.Matrix.prototype.height = function() {
  return this.size().height;
};

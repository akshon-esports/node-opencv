var core = require('../../../');

core.Matrix.prototype.inRange = function() {
  var out = new core.Matrix();
  core.inRange.apply(global, [this].concat(Array.from(arguments), out));
  return out;
};

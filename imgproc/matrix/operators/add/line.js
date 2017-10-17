var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.line = function() {
  imgproc.line.apply(global, [this].concat(Array.from(arguments)));
  return this;
};

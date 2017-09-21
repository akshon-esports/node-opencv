var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.rectangle = function() {
  imgproc.rectangle.apply(global, [this].concat(Array.from(arguments)));
  return this;
};

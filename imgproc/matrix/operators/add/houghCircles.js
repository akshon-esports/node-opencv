var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.houghCircles = function() {
  return imgproc.houghCircles.apply(global, [this].concat(Array.from(arguments)));
};

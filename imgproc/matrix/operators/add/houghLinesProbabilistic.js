var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.houghLinesProbabilistic = function() {
  return imgproc.houghLinesP.apply(global, [this].concat(Array.from(arguments)));
};

var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.findContours = function() {
  return imgproc.findContours.apply(global, [this].concat(Array.from(arguments)));
};

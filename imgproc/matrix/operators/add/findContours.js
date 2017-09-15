var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.findContours = function() {
  arguments.splice(0, 0, this);
  return imgproc.findContours.apply(global, arguments);
};

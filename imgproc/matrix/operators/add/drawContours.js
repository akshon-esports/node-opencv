var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.drawContours = function() {
  imgproc.drawContours.apply(global, [this].concat(Array.from(arguments)));
  return this;
};

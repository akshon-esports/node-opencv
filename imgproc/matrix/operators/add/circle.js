var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.drawContours = function() {
  imgproc.circle.apply(global, [this].concat(Array.from(arguments)));
  return this;
};

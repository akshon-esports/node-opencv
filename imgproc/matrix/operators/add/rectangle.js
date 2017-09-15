var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.rectangle = function() {
  arguments.splice(0, 0, this);
  return imgproc.rectangle.apply(global, arguments);
};

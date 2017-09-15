var core = require('../../../../core');
var imgproc = require('../../../');

core.Matrix.prototype.rectangle = function() {
  var out = this.clone();
  arguments.splice(0, 0, out);
  imgproc.rectangle.apply(global, arguments);
  return out;
};

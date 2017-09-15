var path = require('../binary')();
var core = require(path + '/core.node');
module.exports = require(path + '/imgcodecs.node');

core.Matrix.prototype.resize = function() {
  arguments.splice(1, 0, this);
  return module.exports.resize.apply(global, arguments);
};

core.Matrix.prototype.matchTemplate = function() {
  arguments.splice(1, 0, this);
  return module.exports.matchTemplate.apply(global, arguments);
};

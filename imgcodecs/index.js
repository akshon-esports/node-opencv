var binary = require('../binary');
var path = binary();
var core = require(path + '/core.node');
module.exports = require(path + '/imgcodecs.node');

binary.copyProperties(module.exports, core.Matrix);

core.Matrix.prototype.imencode = function() {
  return module.exports.imencode.apply(global, arguments.splice(1, 0, this));
};

core.Matrix.prototype.imencodeSync = function() {
  return module.exports.imencodeSync.apply(global, arguments.splice(1, 0, this));
};

core.Matrix.prototype.imwrite = function() {
  return module.exports.imwrite.apply(global, arguments.splice(1, 0, this));
};

core.Matrix.prototype.imwriteSync = function() {
  return module.exports.imwriteSync.apply(global, arguments.splice(1, 0, this));
};

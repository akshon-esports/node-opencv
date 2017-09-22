var binary = require('../binary');
var path = binary();
var core = require(path + '/core.node');
module.exports = require(path + '/imgcodecs.node');

binary.copyProperties(module.exports, core.Matrix, ['imread', 'imreadSync', 'imreadmulti', 'imreadmultiSync']);

core.Matrix.prototype.imencode = function() {
  var args = Array.from(arguments);
  args.splice(1, 0, this);
  return module.exports.imencode.apply(global, args);
};

core.Matrix.prototype.imencodeSync = function() {
  var args = Array.from(arguments);
  args.splice(1, 0, this);
  return module.exports.imencodeSync.apply(global, args);
};

core.Matrix.prototype.imwrite = function() {
  var args = Array.from(arguments);
  args.splice(1, 0, this);
  return module.exports.imwrite.apply(global, args);
};

core.Matrix.prototype.imwriteSync = function() {
  var args = Array.from(arguments);
  args.splice(1, 0, this);
  return module.exports.imwriteSync.apply(global, args);
};

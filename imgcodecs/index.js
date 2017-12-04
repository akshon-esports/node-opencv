var binary = require('../binary');
var core = binary('core');
var imgcodecs = module.exports = binary('imgcodecs');

binary.copyProperties(module.exports, core.Matrix, ['imread', 'imreadSync', 'imreadmulti', 'imreadmultiSync']);

core.Matrix.prototype.imencode = function() {
  var args = Array.from(arguments);
  args.splice(1, 0, this);
  return imgcodecs.imencode.apply(global, args);
};

core.Matrix.prototype.imencodeSync = function() {
  var args = Array.from(arguments);
  args.splice(1, 0, this);
  return imgcodecs.imencodeSync.apply(global, args);
};

core.Matrix.prototype.imwrite = function() {
  var args = Array.from(arguments);
  args.splice(1, 0, this);
  return imgcodecs.imwrite.apply(global, args);
};

core.Matrix.prototype.imwriteSync = function() {
  var args = Array.from(arguments);
  args.splice(1, 0, this);
  return imgcodecs.imwriteSync.apply(global, args);
};

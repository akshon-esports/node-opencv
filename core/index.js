var core = require(require('../binary')() + '/core.node');

core.Matrix.addWeighted = function() {
  var out = new core.Matrix();
  var args = Array.from(arguments);
  if (args.length >= 5) {
    // not enough arguments, just let it fail
    args.splice(5, 0, out);
  }
  core.addWeighted.apply(global, args);
  return out;
};

core.Matrix.subtract = function() {
  var out = new core.Matrix();
  var args = Array.from(arguments);
  if (args.length >= 2) {
    // not enough arguments, just let it fail
    args.splice(2, 0, out);
  }
  core.subtract.apply(global, args);
  return out;
};

core.Matrix.vconcat = function() {
  var out = new core.Matrix();
  core.vconcat.apply(global, Array.from(arguments).concat(out));
  return out;
};

module.exports = core;

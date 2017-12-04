var path = require('path');
var binary = require('node-pre-gyp');

var PACKAGE_PATH = path.resolve(__dirname, 'package.json');

var pkg = require(PACKAGE_PATH);
var binding_root = binary.find(PACKAGE_PATH, {
  debug: !!process.env.NODE_OPENCV_DEBUG
}).replace(new RegExp(pkg.binary.module_name + '\\.node$'), '');

module.exports = function(module_name) {
  return require(binding_root + module_name + '.node');
};

module.exports.copyProperties = function(from, to, properties) {
  for (var i = 0; i < properties.length; i++) {
    var property = properties[i];
    if (!from.hasOwnProperty(property)) {
      continue;
    }

    to[property] = from[property];
  }
};

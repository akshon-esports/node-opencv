var path = require('path');

module.exports = function() {
  return path.resolve(__dirname, 'build/' + (process.env.NODE_OPENCV_DEBUG ? 'Debug' : 'Release'));
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
var path = require('../binary')();
module.exports = require(path + '/core.node') && require(path + '/imgcodecs.node');

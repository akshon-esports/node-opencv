var path = require('../binary')();
module.exports = require(path + '/core.node') && require(path + '/videoio.node');

var util = require('util');
var stream = require('stream');

var VideoCapture = module.exports.VideoCapture;

VideoCaptureStream = module.exports.VideoCaptureStream = function(src) {
  if (!this) throw 'Cannot instantiate without new';

  if (!(src instanceof VideoCapture)) src = new (VideoCapture.bind(VideoCapture, arguments));
  this.video = src;
  this.readable = true;
  this.paused = false;

  this.emit('readable');

  var self = this;
  var frame = function() {
    try {
      var mat = self.video.read();

      if (mat.empty()) {
        return self.emit('end');
      }

      self.emit('data', mat);

      if (!self.paused) {
        process.nextTick(frame);
      }
    } catch (err) {
      return self.emit('error', err);
    }
  };

  process.nextTick(frame);
};

util.inherits(VideoCaptureStream, stream.Readable);

VideoCaptureStream.prototype.read = function() {
  return this.video.read();
};

VideoCaptureStream.prototype.pause = function() {
  this.paused = true;
};

VideoCaptureStream.prototype.isPaused = function() {
  return this.paused;
};

VideoCaptureStream.prototype.resume = function() {
  this.paused = false;
  this.read();
};

VideoCaptureStream.prototype._destroy = function() {
  this.paused = true;
  this.video.release();
  this.emit('close');
};

VideoCapture.prototype.toStream = function() {
  return new VideoCaptureStream(this);
};

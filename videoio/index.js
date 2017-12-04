var binary = require('../binary');
module.exports = binary('core') && binary('videoio');

var util = require('util');
var stream = require('stream');

var VideoCapture = module.exports.VideoCapture;

VideoCaptureStream = module.exports.VideoCaptureStream = function(src) {
  if (!this) throw 'Cannot instantiate without new';

  if (!(src instanceof VideoCapture)) src = new (Function.prototype.bind.apply(VideoCapture, [src].concat(Array.from(arguments))));

  this.video = src;
  this.readable = true;
  this.paused = true;

  this.emit('readable');

  var self = this;
  var nextFrame = function() {
    try {
      var mat = self.video.read();

      if (!mat || mat.empty()) {
        return self.emit('end', null);
      }

      self.emit('data', mat);

      if (!self.paused) {
        process.nextTick(nextFrame);
      }
    } catch (err) {
      console.log(err.message);
      self.paused = true;
      return self.emit('error', err);
    }
  };

  this.read = function() {
    return self.video.read();
  };

  this.pause = function() {
    self.paused = true;
  };

  this.isPaused = function() {
    return self.paused;
  };

  this.resume = function() {
    self.paused = false;
    process.nextTick(nextFrame);
  };

  this._destroy = function() {
    self.paused = true;
    self.video.release();
    self.emit('close');
  };

  this.resume();
};

util.inherits(VideoCaptureStream, stream.Stream);

VideoCapture.prototype.toStream = function() {
  return new VideoCaptureStream(this);
};

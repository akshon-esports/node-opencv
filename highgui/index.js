var path = require('../binary')();
var highgui = module.exports = require(path + '/core.node') && require(path + '/highgui.node');

var TrackerBar = function(winname, trackbarname) {
  this.windowName = winname;
  this.name = trackbarname;
};

TrackerBar.prototype.getPos = function() {
  return highgui.getTrackbarPos(this.name, this.windowName);
};

TrackerBar.prototype.setMax = function(maxval) {
  highgui.setTrackbarMax(this.name, this.windowName, maxval);
};

TrackerBar.prototype.setMin = function(minval) {
  highgui.setTrackbarMin(this.name, this.windowName, minval);
};

TrackerBar.prototype.setPos = function(pos) {
  highgui.setTrackbarPos(this.name, this.windowName, pos);
};

var NamedWindow = highgui.NamedWindow = function(winname, flags) {
  this.name = winname;

  highgui.namedWindow(winname, flags);
};

NamedWindow.prototype.createTrackerbar = function(trackbarname) {
  return new TrackerBar(this.name, trackbarname);
};

NamedWindow.prototype.destory = function() {
  highgui.destroyWindow(this.name);
};

NamedWindow.prototype.getProperty = function(propId) {
  return highgui.getWindowProperty(this.name, propId);
};

NamedWindow.prototype.showImage = NamedWindow.prototype.show = function(mat) {
  highgui.imshow(this.name, mat);
};

NamedWindow.prototype.move = function(x, y) {
  highgui.moveWindow(this.name, x, y);
};

NamedWindow.prototype.resize = function(width, height) {
  highgui.resizeWindow(this.name, width, height);
};

NamedWindow.prototype.selectROI = function(img, showCrosshair, fromCenter) {
  return highgui.selectROI(this.name, img, showCrosshair, fromCenter);
};

NamedWindow.prototype.selectROIMulti = function(img, showCrosshair, fromCenter) {
  return highgui.selectROIs(this.name, img, showCrosshair, fromCenter);
};

NamedWindow.prototype.setMouseCallback = function(onMouse) {
  highgui.setMouseCallback(this.name, onMouse);
};

NamedWindow.prototype.setProperty = function(propId, value) {
  highgui.setWindowProperty(this.name, propId, value);
};

NamedWindow.prototype.setTitle = function(title) {
  highgui.setWindowTitle(this.name, title);
};

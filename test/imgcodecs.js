var test = require('tape')
  , common = require('./common')
  , fs = require('fs')
  , util = require('util')
  , path = require('path');

var cv_imgcodecs = null
  , imageRead = null
  , imageReadSync = null
  , imageDecode = null
  , imageDecodeSync = null
  , imageReadMulti = null
  , imageReadMultiSync = null;

var MONA_PNG = path.resolve(__dirname, '../examples/files/mona.png')
  , MULTI_TIF = path.resolve(__dirname, '../examples/files/multipage.tif');

test('importing / smoke test', function(assert) {
  assert.ok(cv_imgcodecs = require('../imgcodecs'), 'should import');
  assert.ok(imageRead = cv_imgcodecs.imageRead, 'should have imageRead');
  assert.ok(imageReadSync = cv_imgcodecs.imageReadSync, 'should have imageReadSync');
  assert.ok(imageDecode = cv_imgcodecs.imageDecode, 'should have imageDecode');
  assert.ok(imageDecodeSync = cv_imgcodecs.imageDecodeSync, 'should have imageDecodeSync');
  assert.ok(imageReadMulti = cv_imgcodecs.imageReadMulti, 'should have imageReadMulti');
  assert.ok(imageReadMultiSync = cv_imgcodecs.imageReadMultiSync, 'should have imageReadMultiSync');

  assert.ok(cv_imgcodecs.IMREAD_UNCHANGED, 'should have IMREAD_UNCHANGED constant');
  assert.ok(cv_imgcodecs.IMREAD_GRAYSCALE === 0, 'should have IMREAD_GRAYSCALE constant');
  assert.ok(cv_imgcodecs.IMREAD_COLOR, 'should have IMREAD_COLOR constant');
  assert.ok(cv_imgcodecs.IMREAD_ANYDEPTH, 'should have IMREAD_ANYDEPTH constant');
  assert.ok(cv_imgcodecs.IMREAD_ANYCOLOR, 'should have IMREAD_ANYCOLOR constant');
  assert.ok(cv_imgcodecs.IMREAD_LOAD_GDAL, 'should have IMREAD_LOAD_GDAL constant');
  assert.ok(cv_imgcodecs.IMREAD_REDUCED_GRAYSCALE_2, 'should have IMREAD_REDUCED_GRAYSCALE_2 constant');
  assert.ok(cv_imgcodecs.IMREAD_REDUCED_COLOR_2, 'should have IMREAD_REDUCED_COLOR_2 constant');
  assert.ok(cv_imgcodecs.IMREAD_REDUCED_GRAYSCALE_4, 'should have IMREAD_REDUCED_GRAYSCALE_4 constant');
  assert.ok(cv_imgcodecs.IMREAD_REDUCED_COLOR_4, 'should have IMREAD_REDUCED_COLOR_4 constant');
  assert.ok(cv_imgcodecs.IMREAD_REDUCED_GRAYSCALE_8, 'should have IMREAD_REDUCED_GRAYSCALE_8 constant');
  assert.ok(cv_imgcodecs.IMREAD_REDUCED_COLOR_8, 'should have IMREAD_REDUCED_COLOR_8 constant');
  assert.ok(cv_imgcodecs.IMREAD_IGNORE_ORIENTATION, 'should have IMREAD_IGNORE_ORIENTATION constant');

  assert.end();
});

test('imageRead', function(assert) {
  assert.throws(function() {imageRead()}, common.argcRangeAssertionError(1, 3, 0), 'should throw when given no arguments');
  assert.throws(function() {imageRead(MONA_PNG, 'not-a-number-nor-a-function')}, common.functionArgAssertionError(1), 'should throw when given neither a number nor a function as the second argument');
  assert.throws(function() {imageRead(MONA_PNG, cv_imgcodecs.IMREAD_ANYCOLOR, 'not-a-function')}, common.functionArgAssertionError(2), 'should throw when given a non-function as the third argument');

  test('callback', function(assert) {
    assert.plan(4);

    imageRead('nothing', function(err, image) {
      assert.throws(function() {throw err}, /Could not open or find the image/, 'should fail when given an invalid path');
      assert.notok(image, 'should be undefined when given an invalid path');
    });

    imageRead(MONA_PNG, function(err, image) {
      assert.notok(err, 'should be undefined when given a path to a valid image');
      assert.ok(image, 'should work when given a path to a valid image');
    });
  });

  test('promise', function(assert) {
    assert.plan(2);

    imageRead('nothing').then(function(image) {
      assert.notok(image, 'should not be called when given a path to a valid image');
    }, function(err) {
      assert.throws(function() {throw err}, /Could not open or find the image/, 'should fail when given an invalid path');
    });

    imageRead(MONA_PNG).then(function(image) {
      assert.ok(image, 'should work when given a path to a valid image');
    }, function(err) {
      assert.notok(err, 'should be undefined when given a path to a valid image');
    });
  });

  test('sync', function(assert) {
    assert.throws(function() {imageReadSync()}, common.argcRangeAssertionError(1, 2, 0), 'should throw when given no arguments');
    assert.throws(function() {imageReadSync('nothing')}, /Could not open or find the image/, 'should fail when given an invalid path');

    assert.ok(imageReadSync(MONA_PNG), 'should work when given a path to a valid image');

    assert.end();
  });

  assert.end();
});

test('imageDecode', function(assert) {
  var monaBuf = fs.readFileSync(MONA_PNG);

  assert.throws(function() {imageDecode()}, common.argcRangeAssertionError(1, 3, 0), 'should throw when given no arguments');
  assert.throws(function() {imageDecode(monaBuf, 'not-a-number-nor-a-function')}, common.functionArgAssertionError(1), 'should throw when given neither a number nor a function as the second argument');
  assert.throws(function() {imageDecode(monaBuf, cv_imgcodecs.IMREAD_ANYCOLOR, 'not-a-function')}, common.functionArgAssertionError(2), 'should throw when given a non-function as the third argument');

  test('callback', function(assert) {
    assert.plan(2);

    imageDecode(monaBuf, function(err, image) {
      assert.notok(err, 'should be undefined when given a valid image buffer');
      assert.ok(image, 'should work when given a path to a valid image buffer');
    });
  });

  test('promise', function(assert) {
    assert.plan(1);

    imageDecode(monaBuf).then(function(image) {
      assert.ok(image, 'should work when given a valid image buffer');
    }, function(err) {
      assert.notok(err, 'should be undefined when given a valid image buffer');
    });
  });

  test('sync', function(assert) {
    assert.throws(function() {imageDecodeSync()}, common.argcRangeAssertionError(1, 2, 0), 'should throw when given no arguments');

    assert.ok(imageDecodeSync(monaBuf), 'should work when given a valid image buffer');

    assert.end();
  });

  assert.end();
});

test('imageReadMulti', function(assert) {
  assert.throws(function() {imageReadMulti()}, common.argcRangeAssertionError(1, 3, 0), 'should throw when given no arguments');
  assert.throws(function() {imageReadMulti(MULTI_TIF, 'not-a-number-nor-a-function')}, common.functionArgAssertionError(1), 'should throw when given neither a number nor a function as the second argument');
  assert.throws(function() {imageReadMulti(MULTI_TIF, cv_imgcodecs.IMREAD_ANYCOLOR, 'not-a-function')}, common.functionArgAssertionError(2), 'should throw when given a non-function as the third argument');

  test('callback', function(assert) {
    assert.plan(2);

    imageReadMulti(MULTI_TIF, function(err, image) {
      assert.notok(err, 'should be undefined when given a path to a valid image');
      assert.ok(image, 'should work when given a path to a valid image');
    });
  });

  test('promise', function(assert) {
    assert.plan(1);

    imageReadMulti(MULTI_TIF).then(function(image) {
      assert.ok(image, 'should work when given a path to a valid image');
    }, function(err) {
      assert.notok(err, 'should be undefined when given a path to a valid image');
    });
  });

  test('sync', function(assert) {
    assert.throws(function() {imageReadMultiSync()}, common.argcRangeAssertionError(1, 2, 0), 'should throw when given no arguments');

    assert.ok(imageReadMultiSync(MULTI_TIF), 'should work when given a path to a valid image');

    assert.end();
  });

  assert.end();
});

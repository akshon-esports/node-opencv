var test = require('tape')
  , common = require('./common')
  , cv_core = null;

test('importing / smoke test', function(assert) {
  assert.ok(cv_core = require('../core'), 'should import');
  assert.ok(cv_core.Point, 'should have Point');
  assert.ok(cv_core.Rect, 'should have Rect');
  assert.ok(cv_core.Scalar, 'should have Scalar');
  assert.ok(cv_core.Size, 'should have Size');
  assert.ok(cv_core.Matrix, 'should have Matrix');
  // assert.ok(cv.UnifiedMatrix, 'should have UnifiedMatrix');
  // assert.ok(cv.GpuMatrix, 'should have GpuMatrix');
  assert.end();
});

test('Point', function(assert) {
  var Point = cv_core.Point;

  assert.test('constructor', function(assert) {
    assert.throws(function() {Point()}, common.ERR_MUST_USE_NEW, 'should throw when calling the constructor without the new keyword');
    assert.throws(function() {new Point('')}, common.ERR_INVALID_ARGUMENTS, 'should throw when given invalid arguments');
    assert.throws(function() {new Point('', '')}, common.ERR_INVALID_ARGUMENTS, 'should throw when given invalid arguments');
    assert.throws(function() {new Point('', '', '')}, common.argcRangeAssertionError(0, 2, 3), 'should throw when given more than 2 arguments');

    assert.throws(function() {new Point([])}, /PointLike array must have 2 elements/, 'should throw when given an array with any number of elements other than two as the first argument');
    assert.throws(function() {new Point({})}, /PointLike object must have properties "x" and "y"/, 'should throw when given an object without properties "x" or "y" as the first argument');
    assert.throws(function() {new Point(['', ''])}, /PointLike array elements must be numbers/, 'should throw when given an array with any non-numeric elements as the first argument');
    assert.throws(function() {new Point({x: '', y: ''})}, /PointLike object properties must be numbers/ , 'should throw when given an object with non-numeric properties "x" or "y" as the first argument');

    assert.ok(new Point(), 'should instantiate properly when given no arguments');
    assert.ok(new Point(0, 0), 'should instantiate properly when given numbers for the first and second arguments');
    assert.ok(new Point([0, 0]), 'should instantiate properly when given an array with two numeric elements as the first argument');
    assert.ok(new Point({x: 0, y: 0}), 'should instantiate properly when given an object with numeric properties "x" and "y" as the first argument');
    assert.ok(new Point(new Point()), 'should instantiate properly when given an instance of Point as the first argument');

    assert.end();
  });

  var x1 = Math.floor(Math.random() * 1000), y1 = Math.floor(Math.random() * 1000),
    x2 = Math.floor(Math.random() * 1000), y2 = Math.floor(Math.random() * 1000);

  assert.test('getter', function(assert) {
    var p = new Point(x1, y1);

    assert.equals(p.x, x1, 'should equal the x value given to the constructor');
    assert.equals(p.y, y1, 'should equal the y value given to the constructor');

    assert.end();
  });

  assert.test('setter', function(assert) {
    var p = new Point(x1, y1);

    assert.throws(function() {p.x = 'not a number'}, /value must be a number/, 'should throw when setting x to a non-numeric value');
    assert.throws(function() {p.y = 'not a number'}, /value must be a number/, 'should throw when setting y to a non-numeric value');

    p.x = x2;
    p.y = y2;

    assert.equal(p.x, x2, 'should equal the new x value');
    assert.equal(p.y, y2, 'should equal the new y value');

    assert.end();
  });

  assert.test('prototype', function(assert) {
    assert.test('dot product', function(assert) {
      var p = new Point(x1, y1);

      assert.ok(p.dot, 'should have dot method');

      assert.throws(function() {p.dot()}, common.argcAssertionError(1, 0), 'should throw when given no arguments');
      assert.throws(function() {p.dot('')}, /Argument 1 must be a Point/, 'should throw when given a non-PointLike object as the first argument');

      assert.equal(typeof p.dot(new Point(x2, y2)), 'number', 'should return a number');

      assert.end();
    });

    assert.end();
  });

  assert.end();
});

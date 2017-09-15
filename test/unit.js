var fs = require('fs')
  , util = require('util')
  , path = require('path')
  , test = require('tape')
  , cv = null;

var PATH_TO_MONA_PNG = path.resolve(__dirname, '../examples/files/mona.png');

test("Smoke tests / Can Import", function(assert) {
  cv = require('../lib/opencv');
  assert.ok(cv, "imported successful");
  assert.ok(cv.version, "version is " + cv.version);

  assert.end();
});

test("readImage", function(t) {
  t.plan(8);
  t.throws(function() {cv.readImage()}, /readImage\(\) requires at least 1 arguments/);
  try {
    console.log(cv.readImage(0));
  } catch (e) {
    console.log(e);
  }
  t.throws(function() {cv.readImage(0)}, /Argument 1 must be a string or a Buffer/);
  t.throws(function() {cv.readImage(PATH_TO_MONA_PNG, 'not-a-function')}, /Argument 2 must be a Function/);
  cv.readImage(PATH_TO_MONA_PNG, function(err, im) {
    t.notok(err, 'should not be defined');
    t.ok(im);
  });
  var promise = cv.readImage(PATH_TO_MONA_PNG);
  t.ok(promise);
  t.ok(promise instanceof Promise);
  promise.then(function(im) {
    t.ok(im)
  }, function(err) {
    t.notok(err, 'should not be defined')
  });
});

test('Point', function(t){
  var x1 = 1,
      y1 = 2,
      p1, p2, p3, p4,
      x2 = 3,
      y2 = 4;

  t.test('constructor', function(t) {
    t.throws(function () {cv.Point()}, TypeError);
    t.throws(function () {new cv.Point({})}, TypeError);
    t.throws(function () {new cv.Point(null)}, TypeError);

    p1 = new cv.Point();
    p2 = new cv.Point({x: x1, y: y1});
    p3 = new cv.Point(x1, y1);
    p4 = new cv.Point(p2);

    t.ok(p1 && p2 && p3 && p4, 'should be defined');
    t.ok(typeof p1 === 'object', 'should be an object');
    t.ok(p1 instanceof cv.Point, 'should be an instance of Point');

    t.end();
  });

  t.test('enumerator', function(t) {
    t.equal(Object.keys(p1).length, 2);
    t.ok(Object.keys(p1).indexOf('x') > -1);
    t.ok(Object.keys(p1).indexOf('y') > -1);

    t.end();
  });

  t.test('property getter', function(t) {
    t.equal(p1.x, 0);
    t.equal(p1.y, 0);

    t.equal(p2.x, x1);
    t.equal(p2.y, y1);

    t.equal(p3.x, x1);
    t.equal(p3.y, y1);

    t.equal(p4.x, x1);
    t.equal(p4.y, y1);

    t.end();
  });

  t.test('property setter', function(t) {
    t.throws(function () {p1.x = 'not a number'}, TypeError, 'value must be a number');
    t.throws(function () {p1.y = 'not a number'}, TypeError, 'value must be a number');

    p1.x = x2;
    p1.y = y2;

    t.equal(p1.x, x2);
    t.equal(p1.y, y2);

    t.end();
  });

  t.test('prototype', function(t) {
    t.test('dot product', function(t) {
      t.ok(p1.dot);
      t.equal(p1.dot(p2), x1 * x2 + y1 * y2);

      t.end();
    });

    t.end();
  });

  t.end();
});

test('Size', function(t){
  var w1 = 1,
      h1 = 2,
      s1, s2, s3, s4,
      w2 = 3,
      h2 = 4

  t.test('constructor', function(t) {
    t.throws(function () {cv.Size()}, TypeError)
    t.throws(function () {new cv.Size({})}, TypeError)
    t.throws(function () {new cv.Size(null)}, TypeError)

    s1 = new cv.Size()
    s2 = new cv.Size({width: w1, height: h1})
    s3 = new cv.Size(w1, h1)
    s4 = new cv.Size(s2)

    t.ok(s1 && s2 && s3 && s4, 'should be defined')
    t.ok(typeof s1 === 'object', 'should be an object')
    t.ok(s1 instanceof cv.Size, 'should be an instance of Size')

    t.end()
  })

  t.test('getter', function(t) {
    t.equal(s1.width, 0)
    t.equal(s1.height, 0)

    t.equal(s2.width, w1)
    t.equal(s2.height, h1)

    t.equal(s3.width, w1)
    t.equal(s3.height, h1)

    t.equal(s4.width, w1)
    t.equal(s4.height, h1)

    t.end()
  })

  t.test('setter', function(t) {
    t.throws(function () {s1.width = 'not a number'}, TypeError, 'value must be a number')
    t.throws(function () {s1.height = 'not a number'}, TypeError, 'value must be a number')

    s1.width = w2
    s1.height = h2

    t.equal(s1.width, w2)
    t.equal(s1.height, h2)

    t.end()
  })

  t.test('prototype', function(t) {
    t.test('area', function(t) {
      t.ok(s1.area)
      t.equal(s1.area(), w2 * h2)

      t.end()
    })

    t.end()
  })

  t.test('inspect', function(t) {
    t.ok(util.inspect(s1))

    t.end()
  })

  t.end()
})

test('Rect', function(assert) {
  assert.ok(cv.Rect);

  assert.test('constructor', function(assert) {
    assert.ok(new cv.Rect());
    assert.ok(new cv.Rect({ x: 1, y: 2, width: 3, height: 4}));
    assert.ok(new cv.Rect({ x: 1, y: 2 }, { width: 3, height: 4}));
    assert.ok(new cv.Rect({ x: 1, y: 2 }, { x: 3, y: 4 }));
    assert.ok(new cv.Rect(1, 2, 3, 4));
    assert.end();
  });

  assert.test('getter', function(assert) {
    var rect = new cv.Rect(1, 2, 3, 4);
    assert.equal(rect.x, 1);
    assert.equal(rect.y, 2);
    assert.equal(rect.width, 3);
    assert.equal(rect.height, 4);
    assert.end();
  });

  assert.test('setter', function(assert) {
    var rect = new cv.Rect(1, 2, 3, 4);
    console.log(rect);
    rect.x = 4;
    rect.y = 3;
    rect.width = 2;
    rect.height = 1;
    assert.equal(rect.x, 4);
    assert.equal(rect.y, 3);
    assert.equal(rect.width, 2);
    assert.equal(rect.height, 1);
    console.log(rect);
    assert.end();
  });

  assert.ok(util.inspect(new cv.Rect()));

  assert.end();
});

test('Matrix', function(assert) {
  assert.test('constructor', function(assert) {
    assert.ok(cv.Matrix);
    assert.ok(new cv.Matrix);
    assert.ok(new cv.Matrix(1, 2));
    assert.ok(new cv.Matrix(1, 2, cv.Constants.CV_8U));
    assert.ok(new cv.Matrix(1, 2, cv.Constants.CV_8U, [1]));
    assert.end();
  });

  assert.test('prototype', function(assert) {
    assert.test('findContours', function(assert) {
      var mat = cv.readImageSync(PATH_TO_MONA_PNG, cv.Constants.IMREAD_REDUCED_GRAYSCALE_8);

      assert.throws(function() { mat.findContours() }, Error);
      assert.throws(function() { mat.findContours(cv.Constants.RETR_LIST) }, Error);
      assert.throws(function() { mat.findContours(cv.Constants.RETR_LIST, 'not-a-number') }, TypeError);
      assert.throws(function() { mat.findContours('not-a-number', cv.Constants.CHAIN_APPROX_NONE) }, TypeError);
      assert.ok(mat.findContours(cv.Constants.RETR_LIST, cv.Constants.CHAIN_APPROX_NONE));

      assert.end();
    });

    assert.end();
  });

  assert.end();
});

test(".norm", function(assert){
  cv.readImage("./examples/files/coin1.jpg", function(err, im) {
    cv.readImage("./examples/files/coin2.jpg", function(err, im2){
      assert.ok(im);
      assert.ok(im2);

      var errorL2 = im.norm(im2, cv.Constants.NORM_L2);
      assert.equal(errorL2, 7295.591339980605);
      errorL2 = im.norm(im, cv.Constants.NORM_L2);
      assert.equal(errorL2, 0);
      assert.end();
    });
  });
})

test("Multi-page image read from file", function(assert){
  if (parseInt(cv.version) >= 3) {
    cv.readImageMulti("./examples/files/multipage.tif", function(err, imgs){
      assert.ok(imgs);
      assert.equal(imgs.length, 10);
      for (var i = 0; i < imgs.length; i++) {
        assert.ok(imgs[i]);
        assert.equal(imgs[i].width(), 800);
        assert.equal(imgs[i].height(), 600);
        assert.equal(imgs[i].channels(), 3);
        assert.equal(imgs[i].empty(), false);
      }
      assert.end();
    })
  } else {
    assert.equal(cv.readImageMulti("./examples/files/multipage.tif"), false);
    assert.end();
  }
})

test("Distance transform", function(assert){
  cv.readImage("./examples/files/distanceTransform.png", function(err, img){
    assert.ok(img);

    // 50px image with single black pixel on right side
    var result = cv.imgproc.distanceTransform(img, cv.Constants.CV_DIST_L2, cv.Constants.CV_DIST_MASK_PRECISE);
    assert.equal(result.get(0,0), 49);
    assert.end();
  })
})

test("read Image from buffer", function(assert){
  cv.readImage(fs.readFileSync('./examples/files/opencv.png'), function(err, im){
    assert.ok(im);
    assert.equal(im.width(), 82);
    assert.equal(im.height(), 99);
    assert.equal(im.channels(), 4);
    assert.equal(im.empty(), false);
    assert.end();
  })
})

test("Cascade Classifier", function(assert){
  assert.ok(new cv.CascadeClassifier("./data/haarcascade_frontalface_alt.xml"), 'test constructor')

  cv.readImage("./examples/files/mona.png", function(err, im){
    cascade = new cv.CascadeClassifier("./data/haarcascade_frontalface_alt.xml");
    cascade.detectMultiScale(im, function(err, faces){//, 1.1, 2, [30, 30]);
      assert.error(err);
      assert.equal(typeof faces, typeof []);
      assert.equal(faces.length, 1)
      assert.end()
    })
  })
})


test("ImageDataStream", function(assert){
  var s = new cv.ImageDataStream()
  s.on('load', function(im){
    assert.ok(im)
    assert.equal(im.empty(), false);
    assert.end()
  })

  fs.createReadStream('./examples/files/mona.png').pipe(s);

})

test("ImageStream", function(assert){
  var s = new cv.ImageStream()
    , im = fs.readFileSync('./examples/files/mona.png')

  s.on('data', function(mat){
    assert.deepEqual(mat.size(), [756,500])
    assert.end()
  })
  s.write(im);
})


test("CamShift", function(assert){
  cv.readImage('./examples/files/coin1.jpg', function(e, im){
    cv.readImage('./examples/files/coin2.jpg', function(e, im2){
      var tracked = new cv.TrackedObject(im, [420, 110, 490, 170], {channel: 'v'});
      assert.ok(tracked);
      var res = tracked.track(im2)
      assert.ok(res);
      assert.ok(res[0]  < 396)
      assert.ok(res[0]  > 376)
      assert.ok(res[1]  < 122)
      assert.ok(res[1]  > 102)
      assert.ok(res[2]  < 469)
      assert.ok(res[2]  > 449)
      assert.ok(res[3]  < 176)
      assert.ok(res[3]  > 156)
      assert.end()
    })
  })
})

test("fonts", function(t) {

  function rnd() {
    return Math.round(Math.random() * 255);
  };

  cv.readImage("./examples/files/coin1.jpg", function(e, im){
    var y = 0;
    var scale = 1;

    ([
      "HERSEY_SIMPLEX",
      "HERSEY_PLAIN",
      "HERSEY_DUPLEX",
      "HERSEY_COMPLEX",
      "HERSEY_TRIPLEX",
      "HERSEY_COMPLEX_SMALL",
      "HERSEY_SCRIPT_SIMPLEX",
      "HERSEY_SCRIPT_COMPLEX",
      "HERSEY_SCRIPT_SIMPLEX"
    ]).forEach(function(font) {
      im.putText("Some text", 0, y += 20, font, [rnd(), rnd(), rnd()], 2, scale++);
    });

    t.ok(im, "image is ok");
    im.save("./examples/tmp/coin1-with-text.jpg");
    t.end();
  });
})

test('LDA Wrap', function(assert) {
  if (cv.LDA === undefined) {
    console.log('TODO: Please port LDAWrap.cc to OpenCV 3')
    assert.end();
    return;
  }

  // subspaceProject
  var mat = cv.LDA.subspaceProject(new cv.Matrix(1, 2, cv.Constants.CV_64F), new cv.Matrix(), new cv.Matrix(2, 1, cv.Constants.CV_8UC1));
  assert.deepEqual(mat.size(), [2,2], 'subspaceProject');

  // subspaceReconstruct
  mat = cv.LDA.subspaceReconstruct(new cv.Matrix(1, 2, cv.Constants.CV_64F), new cv.Matrix(), new cv.Matrix(1, 2, cv.Constants.CV_8UC1));
  assert.deepEqual(mat.size(), [1,1], 'subspaceReconstruct');

  assert.end();
})


test('Native Matrix', function(assert) {
  var nativemat = require('../build/' + (!!process.env.NODE_OPENCV_DEBUG ? 'Debug' : 'Release') + '/test_nativemat.node');
  var mat = new cv.Matrix(42, 8);

  assert.deepEqual(mat.size(), nativemat.size(mat), 'nativemat');
  assert.end();
})

test('Subtract', function(assert) {
  var a = new cv.Matrix.Zeros(1,1);
  a.set(0, 0, 3);
  var b = new cv.Matrix.Zeros(1,1);
  b.set(0, 0, 1);
  a.subtract(b);
  assert.deepEqual(a.get(0, 0), 2);
  assert.end();
});

test('Mean', function(assert) {
  var a = new cv.Matrix.Zeros(2, 2, cv.Constants.CV_8UC3);

  // Set [0, 0] element to 1 for all three channels
  a.set(0, 0, 1, 0);
  a.set(0, 0, 1, 1);
  a.set(0, 0, 1, 2);

  var means = a.mean();
  assert.deepEqual(means, [0.25, 0.25, 0.25, 0]);
  assert.end();
});

test('MatchTemplateByMatrix', function(assert) {
  var cv = require('../lib/opencv');
  var targetFilename = "./examples/files/car1.jpg";
  var templateFilename = "./examples/files/car1_template.jpg";
  cv.readImage(targetFilename, function(err, target){
    cv.readImage(templateFilename, function(err, template){
      var TM_CCORR_NORMED = 3;
      var res = target.matchTemplateByMatrix(template, TM_CCORR_NORMED);
      var minMax = res.minMaxLoc();
      var topLeft = minMax.maxLoc;
      assert.ok(topLeft, "RGB Found Match");
      assert.equal(topLeft.x, 42, "match location x === 42");
      assert.equal(topLeft.y, 263, "match location y === 263");
      target.canny(5,300);
      template.canny(5,300);
      res = target.matchTemplateByMatrix(template, TM_CCORR_NORMED);
      minMax = res.minMaxLoc();
      topLeft = minMax.maxLoc;
      assert.ok(topLeft, "Canny edge Found Match");
      assert.equal(topLeft.x, 42, "match location x === 42");
      assert.equal(topLeft.y, 263, "match location y === 263");
      assert.end();
    });
  })
});

test('setColor works will alpha channels', function(assert) {
  var cv = require('../lib/opencv');
  var mat = new cv.Matrix(100, 100, cv.Constants.CV_8UC4);

  var SQUARE = [ 50, 50 ];
  mat.rectangle([ 0, 0 ], SQUARE, [ 0, 187, 255, 255 ], -1);
  mat.rectangle([ 0, 50 ], SQUARE, [ 0, 187, 124, 200 ], -1);
  mat.rectangle([ 50, 0 ], SQUARE, [ 241, 161, 0, 128 ], -1);
  mat.rectangle([ 50, 50 ], SQUARE, [ 20, 83, 246, 70 ], -1);

  cv.readImage('./examples/files/alpha-test.png', function(err, imgMat) {
    if (!err) {
      var diff = new cv.Matrix();
      diff.absDiff(mat, imgMat);
      // We'll verify that each channel is 0
      var channels = diff.split();
      for (var i = 0; i < 4; i++) {
        assert.equal(channels[i].countNonZero(), 0);
      }
    } else {
      throw err;
    }
    assert.end();
  });
});

// Test the examples folder.
require('./examples')()

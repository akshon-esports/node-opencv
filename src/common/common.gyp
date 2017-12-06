{
  "targets": [
    {
      "target_name": "common",

      "type": "static_library",

      "defines": [ "BUILDING_NCV_COMMON_BINDINGS" ],

      "sources": [
        "async.cc",
        "common.cc",
        "Matrix.cc",
        "UnifiedMatrix.cc",
        "Point.cc",
        "Range.cc",
        "Rect.cc",
        "Scalar.cc",
        "Size.cc",
      ],

      "libraries": [
        "<!@(node <(node_opencv_utils)/find-opencv.js --libs opencv_core)",
      ],

      "include_dirs": [
        "<!@(node <(node_opencv_utils)/find-opencv.js --cflags)",
        "<!(node -e \"require('nan')\")",
      ],

      "cflags!" : [ "-fno-exceptions"],
      "cflags_cc!": [ "-fno-rtti",  "-fno-exceptions"],

      "conditions": [
        [ "OS==\"win\"", {
          "cflags": [
#            "-Wall",
          ],
          "defines": [
            "WIN"
          ],
          "msvs_settings": {
            "VCCLCompilerTool": {
#              "ExceptionHandling": "2",

              "DisableSpecificWarnings": [ "4530", "4244", "4275" ],
            },
          },
        } ],
      ],
    },
  ],
}

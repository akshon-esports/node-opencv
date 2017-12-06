{
  "targets": [
    {
      "target_name": "imgproc",

      "dependencies": [ "../core/core.gyp:core" ],

      "sources": [
        "Contour.cc",
        "Contours.cc",

        "transform.cc",
        "filter.cc",
        "transform.cc",
        "misc.cc",
        "draw.cc",
        "colormap.cc",
        "subdiv2d.cc",
        "hist.cc",
        "shape.cc",
        "motion.cc",
        "feature.cc",
        "object.cc",

        "init.cc",
      ],

      "libraries": [
        "<!@(node <(node_opencv_utils)/find-opencv.js --libs opencv_core opencv_imgproc)",
      ],

      "include_dirs": [
        "<!@(node <(node_opencv_utils)/find-opencv.js --cflags)",
        "<!(node -e \"require('nan')\")"
      ],

      "cflags!" : [ "-fno-exceptions"],
      "cflags_cc!": [ "-fno-rtti",  "-fno-exceptions"],

      "conditions": [
        [ "OS==\"win\"", {
          "libraries": [
            "<(module_root_dir)/build/$(Configuration)/core.lib",
          ],
        }, {
          "libraries": [
            "<(module_root_dir)/build/$(BUILDTYPE)/core.node",
            "-Wl,-rpath,<(module_root_dir)/build/$(BUILDTYPE)",
          ],
        }],
      ],
    },
  ],
}

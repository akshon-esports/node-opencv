{
  "targets": [
    {
      "target_name": "imgcodecs",

      "dependencies": [ "../core/core.gyp:core" ],

      "sources": [
        "init.cc",
      ],

      "libraries": [
        "<!@(node <(node_opencv_utils)/find-opencv.js --libs opencv_core opencv_imgcodecs)",
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

{
  "targets": [
    {
      "target_name": "core",

      "type": "shared_library",

      "product_extension": "node",

      "dependencies": [ "../common/common.gyp:common" ],

      "sources": [
        "array.cc",
        "init.cc",
      ],

      "libraries": [
        "<!@(node <(node_opencv_utils)/find-opencv.js --libs opencv_core)",
      ],

      "include_dirs": [
        "<!@(node <(node_opencv_utils)/find-opencv.js --cflags)",
        "<!(node -e \"require('nan')\")"
      ],

      "cflags!" : [ "-fno-exceptions"],
      "cflags_cc!": [ "-fno-rtti",  "-fno-exceptions"],

      "conditions": [
        [ "OS!=\"win\"", {
          "libraries": [
            "<(module_root_dir)/build/$(BUILDTYPE)/common.a"
          ],
        }],
        [ "OS==\"win\"", {
          "msvs_settings": {
            "VCLinkerTool": {
              "ModuleDefinitionFile": "<(module_root_dir)\\src\\common\\common.def",
            },
          },
#          "libraries": [
#            "<(module_root_dir)/build/$(Configuration)/common.lib",
#          ],
        }],
      ],
    }
  ]
}

{
  "targets": [
    {
      "target_name": "common",

      "sources": [
        "src/common/common.cc",
        "src/common/Matrix.cc",
        "src/common/UnifiedMatrix.cc",
        "src/common/Point.cc",
        "src/common/Range.cc",
        "src/common/Rect.cc",
        "src/common/Scalar.cc",
        "src/common/Size.cc",
      ],

      "libraries": [
        "<!@(node utils/find-opencv.js --libs)"
      ],

      "include_dirs": [
        "<!@(node utils/find-opencv.js --cflags)",
        "<!(node -e \"require('nan')\")"
      ],

      "cflags!" : [ "-fno-exceptions"],
      "cflags_cc!": [ "-fno-rtti",  "-fno-exceptions"],

      "conditions": [
        [ "OS!=\"win\"", {

          "type": "static_library",

        }],
        [ "OS==\"linux\" or OS==\"freebsd\" or OS==\"openbsd\" or OS==\"solaris\" or OS==\"aix\"", {
          "cflags": [
            "<!@(node utils/find-opencv.js --cflags)",
            "-Wall"
          ]
        }],
        [ "OS==\"win\"", {

          "type": "shared_library",

          "cflags": [
            "-Wall"
          ],
          "defines": [
              "WIN"
          ],
          "msvs_settings": {
            "VCCLCompilerTool": {
              "ExceptionHandling": "2",
              "DisableSpecificWarnings": [ "4530", "4506", "4244" ],
            },
          }
        }],
        # cflags on OS X are stupid and have to be defined like this
        [ "OS==\"mac\"", {
          "xcode_settings": {
            "OTHER_CFLAGS": [
              "-mmacosx-version-min=10.7",
              "-std=c++11",
              "-stdlib=libc++",
              "<!@(node utils/find-opencv.js --cflags)",
            ],
            "GCC_ENABLE_CPP_RTTI": "YES",
            "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
          }
        }]
      ],
      "configurations": {
        "Debug": {
          "defines": [
            "NODE_OPENCV_DEBUG=1"
          ],
        }
      }
    },
    {
      "target_name": "core",

      "dependencies": [ "common" ],

      "sources": [
        "src/core/array.cc",
        "src/core/init.cc",
      ],

      "libraries": [
        "<!@(node utils/find-opencv.js --libs)"
      ],

      "include_dirs": [
        "<!@(node utils/find-opencv.js --cflags)",
        "<!(node -e \"require('nan')\")"
      ],

      "cflags!" : [ "-fno-exceptions"],
      "cflags_cc!": [ "-fno-rtti",  "-fno-exceptions"],

      "conditions": [
        [ "OS!=\"win\"", {
          "libraries": [
            "<(module_root_dir)/build/Release/common.a"
          ],
        }],
        [ "OS==\"linux\" or OS==\"freebsd\" or OS==\"openbsd\" or OS==\"solaris\" or OS==\"aix\"", {
          "cflags": [
            "<!@(node utils/find-opencv.js --cflags)",
            "-Wall"
          ]
        }],
        [ "OS==\"win\"", {
          "cflags": [
            "-Wall"
          ],
          "defines": [
              "WIN"
          ],
          "libraries": [
            "<(module_root_dir)/build/Release/common.lib"
          ],
          "msvs_settings": {
            "VCCLCompilerTool": {
              "ExceptionHandling": "2",
              "DisableSpecificWarnings": [ "4530", "4506", "4244" ],
            },
          }
        }],
        # cflags on OS X are stupid and have to be defined like this
        [ "OS==\"mac\"", {
          "xcode_settings": {
            "OTHER_CFLAGS": [
              "-mmacosx-version-min=10.7",
              "-std=c++11",
              "-stdlib=libc++",
              "<!@(node utils/find-opencv.js --cflags)",
            ],
            "GCC_ENABLE_CPP_RTTI": "YES",
            "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
          }
        }]
      ],
      "configurations": {
        "Debug": {
          "defines": [
            "NODE_OPENCV_DEBUG=1"
          ],
        }
      }
    },
    {
      "target_name": "imgcodecs",

      "dependencies": [ "common" ],

      "sources": [
        "src/imgcodecs/init.cc",
      ],

      "libraries": [
        "<!@(node utils/find-opencv.js --libs)",
      ],

      "include_dirs": [
        "<!@(node utils/find-opencv.js --cflags)",
        "<!(node -e \"require('nan')\")"
      ],

      "cflags!" : [ "-fno-exceptions"],
      "cflags_cc!": [ "-fno-rtti",  "-fno-exceptions"],

      "configurations": {
        "Debug": {
          "defines": [
            "NODE_OPENCV_DEBUG=1"
          ],
        }
      },

      "conditions": [
        [ "OS!=\"win\"", {
          "libraries": [
            "<(module_root_dir)/build/Release/common.a"
          ],
        }],
        [ "OS==\"linux\" or OS==\"freebsd\" or OS==\"openbsd\" or OS==\"solaris\" or OS==\"aix\"", {
          "cflags": [
            "<!@(node utils/find-opencv.js --cflags)",
            "-Wall"
          ]
        }],
        [ "OS==\"win\"", {
          "cflags": [
            "-Wall"
          ],
          "defines": [
              "WIN"
          ],
          "libraries": [
            "<(module_root_dir)/build/Release/common.lib"
          ],
          "msvs_settings": {
            "VCCLCompilerTool": {
              "ExceptionHandling": "2",
              "DisableSpecificWarnings": [ "4530", "4506", "4244" ],
            },
          }
        }],
        # cflags on OS X are stupid and have to be defined like this
        [ "OS==\"mac\"", {
          "xcode_settings": {
            "OTHER_CFLAGS": [
              "-mmacosx-version-min=10.7",
              "-std=c++11",
              "-stdlib=libc++",
              "<!@(node utils/find-opencv.js --cflags)",
            ],
            "GCC_ENABLE_CPP_RTTI": "YES",
            "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
          }
        }]
      ],
    },
    {
      "target_name": "imgproc",

      "dependencies": [ "common" ],

      "sources": [
        "src/imgproc/Contour.cc",
        "src/imgproc/Contours.cc",

        "src/imgproc/transform.cc",
        "src/imgproc/filter.cc",
        "src/imgproc/transform.cc",
        "src/imgproc/misc.cc",
        "src/imgproc/draw.cc",
        "src/imgproc/colormap.cc",
        "src/imgproc/subdiv2d.cc",
        "src/imgproc/hist.cc",
        "src/imgproc/shape.cc",
        "src/imgproc/motion.cc",
        "src/imgproc/feature.cc",
        "src/imgproc/object.cc",

        "src/imgproc/init.cc",
      ],

      "libraries": [
        "<!@(node utils/find-opencv.js --libs)",
      ],

      "include_dirs": [
        "<!@(node utils/find-opencv.js --cflags)",
        "<!(node -e \"require('nan')\")"
      ],

      "cflags!" : [ "-fno-exceptions"],
      "cflags_cc!": [ "-fno-rtti",  "-fno-exceptions"],

      "configurations": {
        "Debug": {
          "defines": [
            "NODE_OPENCV_DEBUG=1"
          ],
        }
      },

      "conditions": [
        [ "OS!=\"win\"", {
          "libraries": [
            "<(module_root_dir)/build/Release/common.a"
          ],
        }],
        [ "OS==\"linux\" or OS==\"freebsd\" or OS==\"openbsd\" or OS==\"solaris\" or OS==\"aix\"", {
          "cflags": [
            "<!@(node utils/find-opencv.js --cflags)",
            "-Wall"
          ]
        }],
        [ "OS==\"win\"", {
          "cflags": [
            "-Wall"
          ],
          "defines": [
              "WIN"
          ],
          "libraries": [
            "<(module_root_dir)/build/Release/common.lib"
          ],
          "msvs_settings": {
            "VCCLCompilerTool": {
              "ExceptionHandling": "2",
              "DisableSpecificWarnings": [ "4530", "4506", "4244" ],
            },
          }
        }],
        # cflags on OS X are stupid and have to be defined like this
        [ "OS==\"mac\"", {
          "xcode_settings": {
            "OTHER_CFLAGS": [
              "-mmacosx-version-min=10.7",
              "-std=c++11",
              "-stdlib=libc++",
              "<!@(node utils/find-opencv.js --cflags)",
            ],
            "GCC_ENABLE_CPP_RTTI": "YES",
            "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
          }
        }]
      ],
    },
    {
      "target_name": "videoio",

      "dependencies": [ "common" ],

      "sources": [
        "src/videoio/VideoCapture.cc",
        "src/videoio/VideoWriter.cc",

        "src/videoio/init.cc",
      ],

      "libraries": [
        "<!@(node utils/find-opencv.js --libs)",
      ],

      "include_dirs": [
        "<!@(node utils/find-opencv.js --cflags)",
        "<!(node -e \"require('nan')\")"
      ],

      "cflags!" : [ "-fno-exceptions"],
      "cflags_cc!": [ "-fno-rtti",  "-fno-exceptions"],

      "configurations": {
        "Debug": {
          "defines": [
            "NODE_OPENCV_DEBUG=1"
          ],
        }
      },

      "conditions": [
        [ "OS!=\"win\"", {
          "libraries": [
            "<(module_root_dir)/build/Release/common.a"
          ],
        }],
        [ "OS==\"linux\" or OS==\"freebsd\" or OS==\"openbsd\" or OS==\"solaris\" or OS==\"aix\"", {
          "cflags": [
            "<!@(node utils/find-opencv.js --cflags)",
            "-Wall"
          ]
        }],
        [ "OS==\"win\"", {
          "cflags": [
            "-Wall"
          ],
          "defines": [
              "WIN"
          ],
          "libraries": [
            "<(module_root_dir)/build/Release/common.lib"
          ],
          "msvs_settings": {
            "VCCLCompilerTool": {
              "ExceptionHandling": "2",
              "DisableSpecificWarnings": [ "4530", "4506", "4244" ],
            },
          }
        }],
        # cflags on OS X are stupid and have to be defined like this
        [ "OS==\"mac\"", {
          "xcode_settings": {
            "OTHER_CFLAGS": [
              "-mmacosx-version-min=10.7",
              "-std=c++11",
              "-stdlib=libc++",
              "<!@(node utils/find-opencv.js --cflags)",
            ],
            "GCC_ENABLE_CPP_RTTI": "YES",
            "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
          }
        }]
      ],
    },
    {
      "target_name": "highgui",

      "dependencies": [ "common" ],

      "sources": [
        "src/highgui/init.cc",
      ],

      "libraries": [
        "<!@(node utils/find-opencv.js --libs)",
      ],

      "include_dirs": [
        "<!@(node utils/find-opencv.js --cflags)",
        "<!(node -e \"require('nan')\")"
      ],

      "cflags!" : [ "-fno-exceptions"],
      "cflags_cc!": [ "-fno-rtti",  "-fno-exceptions"],

      "configurations": {
        "Debug": {
          "defines": [
            "NODE_OPENCV_DEBUG=1"
          ],
        }
      },

      "conditions": [
        [ "OS!=\"win\"", {
          "libraries": [
            "<(module_root_dir)/build/Release/common.a"
          ],
        }],
        [ "OS==\"linux\" or OS==\"freebsd\" or OS==\"openbsd\" or OS==\"solaris\" or OS==\"aix\"", {
          "cflags": [
            "<!@(node utils/find-opencv.js --cflags)",
            "-Wall"
          ]
        }],
        [ "OS==\"win\"", {
          "cflags": [
            "-Wall"
          ],
          "defines": [
              "WIN"
          ],
          "libraries": [
            "<(module_root_dir)/build/Release/common.lib"
          ],
          "msvs_settings": {
            "VCCLCompilerTool": {
              "ExceptionHandling": "2",
              "DisableSpecificWarnings": [ "4530", "4506", "4244" ],
            },
          }
        }],
        # cflags on OS X are stupid and have to be defined like this
        [ "OS==\"mac\"", {
          "xcode_settings": {
            "OTHER_CFLAGS": [
              "-mmacosx-version-min=10.7",
              "-std=c++11",
              "-stdlib=libc++",
              "<!@(node utils/find-opencv.js --cflags)",
            ],
            "GCC_ENABLE_CPP_RTTI": "YES",
            "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
          }
        }]
      ],
    },
    {
      "target_name": "text",

      "dependencies": [ "common" ],

      "sources": [
        "src/text/OCRTesseract.cc",
        "src/text/init.cc",
      ],

      "libraries": [
        "<!@(node utils/find-opencv.js --libs)",
      ],

      "include_dirs": [
        "<!@(node utils/find-opencv.js --cflags)",
        "<!(node -e \"require('nan')\")"
      ],

      "cflags!" : [ "-fno-exceptions"],
      "cflags_cc!": [ "-fno-rtti",  "-fno-exceptions"],

      "configurations": {
        "Debug": {
          "defines": [
            "NODE_OPENCV_DEBUG=1"
          ],
        }
      },

      "conditions": [
        [ "OS!=\"win\"", {
          "libraries": [
            "<(module_root_dir)/build/Release/common.a"
          ],
        }],
        [ "OS==\"linux\" or OS==\"freebsd\" or OS==\"openbsd\" or OS==\"solaris\" or OS==\"aix\"", {
          "cflags": [
            "<!@(node utils/find-opencv.js --cflags)",
            "-Wall"
          ]
        }],
        [ "OS==\"win\"", {
          "cflags": [
            "-Wall"
          ],
          "defines": [
              "WIN"
          ],
          "libraries": [
            "<(module_root_dir)/build/Release/common.lib"
          ],
          "msvs_settings": {
            "VCCLCompilerTool": {
              "ExceptionHandling": "2",
              "DisableSpecificWarnings": [ "4530", "4506", "4244" ],
            },
          }
        }],
        # cflags on OS X are stupid and have to be defined like this
        [ "OS==\"mac\"", {
          "xcode_settings": {
            "OTHER_CFLAGS": [
              "-mmacosx-version-min=10.7",
              "-std=c++11",
              "-stdlib=libc++",
              "<!@(node utils/find-opencv.js --cflags)",
            ],
            "GCC_ENABLE_CPP_RTTI": "YES",
            "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
          }
        }]
      ],
    },
    {
      "target_name": "action_after_build",
      "type": "none",
      "dependencies": [
        "common",
        "core",
        "highgui",
        "imgcodecs",
        "imgproc",
        "text",
        "videoio",
      ],

      "conditions": [
        [ "OS==\"win\"", {

          "copies": [
            {
              "files": [ "<(PRODUCT_DIR)/common.dll" ],
              "destination": "<(module_path)"
            }
          ]

        }],
      ],

      "copies": [
        {
          "files": [ "<(PRODUCT_DIR)/core.node" ],
          "destination": "<(module_path)"
        },
        {
          "files": [ "<(PRODUCT_DIR)/highgui.node" ],
          "destination": "<(module_path)"
        },
        {
          "files": [ "<(PRODUCT_DIR)/imgcodecs.node" ],
          "destination": "<(module_path)"
        },
        {
          "files": [ "<(PRODUCT_DIR)/imgproc.node" ],
          "destination": "<(module_path)"
        },
        {
          "files": [ "<(PRODUCT_DIR)/text.node" ],
          "destination": "<(module_path)"
        },
        {
          "files": [ "<(PRODUCT_DIR)/videoio.node" ],
          "destination": "<(module_path)"
        },
      ]
    },
  ]
}

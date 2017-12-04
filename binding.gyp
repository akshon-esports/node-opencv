{
  "targets": [
#    {
#      "target_name": "old",
#
#      "sources": [
#        "src/init.cc",
#        "src/Matrix.cc",
#        "src/OpenCV.cc",
#        "src/CascadeClassifierWrap.cc",
#        "src/Contour.cc",
#        "src/Contours.cc",
#        "src/Point.cc",
#        "src/Rect.cc",
#        "src/Size.cc",
#        "src/Scalar.cc",
#        "src/VideoCaptureWrap.cc",
#        "src/CamShift.cc",
#        "src/HighGUI.cc",
#        "src/FaceRecognizer.cc",
#        "src/Features2d.cc",
#        "src/BackgroundSubtractor.cc",
#        "src/Constants.cc",
#        "src/Calib3D.cc",
#        "src/ImgProc.cc",
#        "src/Stereo.cc",
#        "src/LDAWrap.cc"
#      ],
#
#      "libraries": [
#        "<!@(node utils/find-opencv.js --libs)"
#      ],
#
#      "include_dirs": [
#        "<!@(node utils/find-opencv.js --cflags)",
#        "<!(node -e \"require('nan')\")"
#      ],
#
#      "cflags!" : [ "-fno-exceptions"],
#      "cflags_cc!": [ "-fno-rtti",  "-fno-exceptions"],
#
#      "conditions": [
#        [ "OS==\"linux\" or OS==\"freebsd\" or OS==\"openbsd\" or OS==\"solaris\" or OS==\"aix\"", {
#          "cflags": [
#            "<!@(node utils/find-opencv.js --cflags)",
#            "-Wall"
#          ]
#        }],
#        [ "OS==\"win\"", {
#          "cflags": [
#            "-Wall"
#          ],
#          "defines": [
#              "WIN"
#          ],
#          "msvs_settings": {
#            "VCCLCompilerTool": {
#              "ExceptionHandling": "2",
#              "DisableSpecificWarnings": [ "4530", "4506", "4244" ],
#            },
#          }
#        }],
#        # cflags on OS X are stupid and have to be defined like this
#        [ "OS==\"mac\"", {
#          "xcode_settings": {
#            "OTHER_CFLAGS": [
#              "-mmacosx-version-min=10.7",
#              "-std=c++11",
#              "-stdlib=libc++",
#              "<!@(node utils/find-opencv.js --cflags)",
#            ],
#            "GCC_ENABLE_CPP_RTTI": "YES",
#            "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
#          }
#        }]
#      ],
#
#      "configurations": {
#        # This is used for generating code coverage with the `--debug` argument
#        "Debug": {
#          "conditions": [
#            [ "OS==\"linux\"", {
#              "cflags": ["-coverage"],
#              "ldflags": ["-coverage"]
#            }],
#            [ "OS==\"mac\"", {
#              "xcode_settings": {
#                "OTHER_CFLAGS": [
#                  "-fprofile-arcs -ftest-coverage",
#                ],
#                "OTHER_LDFLAGS": [
#                  "--coverage"
#                ]
#              }
#            }]
#          ]
#        },
#      }
#    },
#    {
#      "target_name": "action_after_build",
#      "type": "none",
#      "dependencies": [ "old" ],
#      "copies": [
#        {
#          "files": [ "<(PRODUCT_DIR)/old.node" ],
#          "destination": "<(module_path)"
#        }
#      ]
#    }
    {
      "target_name": "common",

      "type": "shared_library",

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
            "<(module_root_dir)/build/Release/common.so"
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
            "<(module_root_dir)/build/Release/common.so"
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
            "<(module_root_dir)/build/Release/common.so"
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
            "<(module_root_dir)/build/Release/common.so"
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
            "<(module_root_dir)/build/Release/common.so"
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
            "<(module_root_dir)/build/Release/common.so"
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
  ]
}

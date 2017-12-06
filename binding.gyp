{
  "targets": [
    {
      "target_name": "opencv",

      "type": "none",

      "dependencies": [
        "src/core/core.gyp:core",

        "src/imgcodecs/imgcodecs.gyp:imgcodecs",

        "src/highgui/highgui.gyp:highgui",

        "src/imgproc/imgproc.gyp:imgproc",

        "src/videoio/videoio.gyp:videoio",

        "src/text/text.gyp:text",
      ],

      "copies": [
        {
          "files": [
            "<(PRODUCT_DIR)/core.node",

            "<(PRODUCT_DIR)/imgcodecs.node",

            "<(PRODUCT_DIR)/imgproc.node",

            "<(PRODUCT_DIR)/highgui.node",

            "<(PRODUCT_DIR)/videoio.node",

            "<(PRODUCT_DIR)/text.node",
          ],

          "destination": "<(module_path)",
        },
      ],
    },
  ],
}

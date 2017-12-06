"use strict";

var exec = require("child_process").exec;
var fs = require("fs");
var flag = process.argv[2] || "--exists";
var modules = process.argv.slice(3);

// Normally |pkg-config opencv ...| could report either OpenCV 2.x or OpenCV 3.y
// depending on what is installed.  To enable both 2.x and 3.y to co-exist on
// the same machine, the opencv.pc for 3.y can be installed as opencv3.pc and
// then selected by |export PKG_CONFIG_OPENCV3=1| before building node-opencv.
var opencv = '"opencv >= 3.3.0"';

function main(){
    //Try using pkg-config, but if it fails and it is on Windows, try the fallback
    exec("pkg-config " + opencv + " " + flag, function(error, stdout, stderr){
        if(error){
            if(process.platform === "win32"){
                fallback();
            }
            else{
                throw new Error("ERROR: failed to run: pkg-config", opencv, flag);
            }
        }
        else{
            printLibs(stdout);
        }
    });
}

//======================Windows Specific=======================================

function fallback(){
    exec("echo %OPENCV_DIR%", function(error, stdout, stderr){
        stdout = cleanupEchoOutput(stdout);
        if(error){
            throw new Error("ERROR: There was an error reading OPENCV_DIR");
        }
        else if(stdout === "%OPENCV_DIR%") {
            throw new Error("ERROR: OPENCV_DIR doesn't seem to be defined");
        }
        else {
            printPaths(stdout);
        }
    });
}

function printPaths(opencvPath){
    if(flag === "--cflags") {
        console.log("\"" + opencvPath + "\\..\\..\\include\"");
        console.log("\"" + opencvPath + "\\..\\..\\include\\opencv\"");
    }
    else if(flag === "--libs") {
        var libPath = opencvPath + "\\lib\\";

        fs.readdir(libPath, function(err, files){
            if(err){
                throw new Error("ERROR: couldn't read the lib directory " + err);
            }

            var libs = "";
            for(var i = 0; i < files.length; i++){
                if(getExtension(files[i]) === "lib"){
                    libs = libs + " \"" + libPath + files[i] + "\" \r\n ";
                }
            }
            printLibs(libs);
        });
    }
    else {
        throw new Error("Error: unknown argument '" + flag + "'");
    }
}

function printLibs(libs) {
  if(modules.length > 0){
    libs = libs.split(' ').filter(function(lib) {
      for (var i = 0; i < modules.length; i++) {
        if (lib.indexOf(modules[i]) !== -1) {
          return true;
        }
      }
      return false;
    }).join(' ');
  }
  console.log(libs);
}

function cleanupEchoOutput(s){
    return s.slice(0, s.length - 2);
}

function getExtension(s){
    return s.substr(s.lastIndexOf(".") + 1);
}
main();

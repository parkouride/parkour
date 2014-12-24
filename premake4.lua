solution "Parkour"
   configurations { "Debug", "Release" }
   platforms { "x64" }
   buildoptions { "-std=c++11" }
   location "build"

   project "LedSimulator"
       kind "WindowedApp"
       language "C++"
       files { "simulator/**.h", "simulator/**.cpp" }
   libdirs { "/Users/rhay/code/cinder/latest/lib",
             "/Users/rhay/code/cinder/latest/lib/macosx"
           }
   includedirs { "/Users/rhay/code/cinder/latest/include",
   "/users/rhay/code/cinder/latest/boost"
   }
   links { "Cocoa.framework", "OpenGL.framework",
           "CoreAudio.framework", "Carbon.framework",
           "CoreVideo.framework", "QTKit.framework",
           "Accelerate.framework",
           "AudioToolbox.framework", "AudioUnit.framework" }

       configuration "Debug"
           defines { "DEBUG" }
           flags { "Symbols" }
           links { "cinder_d" }

       configuration "Release"
           defines { "NDEBUG" }
           flags { "Optimize" }
           links { "cinder" }
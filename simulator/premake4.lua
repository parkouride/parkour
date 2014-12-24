   project "LedSimulator"
       kind "WindowedApp"
       language "C++"
       files { "src/**.h", "src/**.cpp" }
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
           "AudioToolbox.framework", "AudioUnit.framework",
           "LedImu" }

       configuration "Debug"
           defines { "DEBUG" }
           flags { "Symbols" }
           links { "cinder_d" }

       configuration "Release"
           defines { "NDEBUG" }
           flags { "Optimize" }
           links { "cinder" }

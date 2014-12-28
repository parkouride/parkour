   project "LedSimulator"
       kind "WindowedApp"
       language "C++"
       files { "src/**.h", "src/**.cpp",
               "../common/ledimu/src/**.h",
               "../common/ledimu/src/**.t.hpp",
               "../common/ledimu/src/**.cpp",
               "../common/ledimu/src/posix/**.h",
               "../common/ledimu/src/posix/**.cpp",
               "../common/ledimu/src/impl/**.h",
               "../common/ledimu/src/impl/**.cpp",
             }
       vpaths {
           ["LedVm"] = { "common/**.cpp", "common/**.h" },
           ["Simulator"] = { "simulator/**.cpp", "simulator/**.h" },
           ["LedVm/TemplateIncludes"] = "common/**.t.hpp"
       }

   libdirs { "/Users/rhay/code/cinder/latest/lib",
             "/Users/rhay/code/cinder/latest/lib/macosx"
           }
   includedirs { "/Users/rhay/code/cinder/latest/include",
   "/users/rhay/code/cinder/latest/boost",
   "../common/ledimu/src",
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

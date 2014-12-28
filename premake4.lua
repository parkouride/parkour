solution "Parkour"
   configurations { "Debug", "Release" }
   platforms { "x64" }
   buildoptions { "-std=c++11 -fno-implicit-templates" }
   location(path.join("build", _ACTION))

   include "simulator"

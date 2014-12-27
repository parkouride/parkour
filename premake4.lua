solution "Parkour"
   configurations { "Debug", "Release" }
   platforms { "x64" }
   buildoptions { "-std=c++11" }
   location(path.join("build", _ACTION))

   include "common"
   include "simulator"

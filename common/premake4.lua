   project "LedImu"
       kind "StaticLib"
       language "C++"
       files { "ledimu/src/**.h", "ledimu/src/**.cpp" }
       excludes { "ledimu/src/_*.cpp" }
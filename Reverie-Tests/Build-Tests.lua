project "Reverie-Tests"
   filter { "configurations:Debug or configurations:Release" }
      kind "ConsoleApp"
      defines { "UNIT_TESTS_ENABLED" }
   filter "configurations:Dist"  
      kind "None"
   filter {}

   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files {
     "External/**.hpp",
     "External/**.h",
     "External/**.cpp",
     "Tests/**.h",
     "Tests/**.cpp"
    }

   includedirs
   {
      "External",
      "Tests",
      "../Reverie-Core/Source/Public"
   }

   links
   {
      "Reverie-Core"
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"
project "Reverie-Core"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp" }

   includedirs
   {
      "Source",
      "Source/Private",
      "Source/Public"
   }

   externalincludedirs
   {
      "Source",
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   systemversion "latest"

   filter "system:windows"
       systemversion "latest"
       defines { "WIN32", "_WINDOWS" }
       links { "d3d12", "dxgi", "d3dcompiler", "dxguid" }
       linkoptions { "/IGNORE:4006" }

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
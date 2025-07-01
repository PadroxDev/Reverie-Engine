if premake.vstudio and premake.vstudio.fileExtension then
    premake.vstudio.fileExtension[".rc"] = "ResourceCompile"
end

workspace "Reverie Engine"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "Reverie-Game"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Core"
	include "Reverie-Core/Build-Core.lua"
group "Tests"
    include "Reverie-Tests/Build-Tests.lua"
group ""

include "Reverie-Game/Build-Game.lua"
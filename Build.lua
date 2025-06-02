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
group ""

include "Reverie-Game/Build-Game.lua"
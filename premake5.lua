--include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "[Project Name]"
	architecture "x86_64"
	startproject "[Project Name]"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Dependencies
group "Dependencies"
	include "Nebula/Nebula/Modules/Box2D"
	include "Nebula/Nebula/Modules/GLFW"
	include "Nebula/Nebula/Modules/GLad"
	include "Nebula/Nebula/Modules/ImGui"
	include "Nebula/Nebula/Modules/yaml-cpp"
group ""

--NEBULA
group "Nebula"
	include "Nebula/Nebula"		  -- Engine
	include "Nebula/Nebula-Storm" -- Editor
group ""

--Client
include "[Project Name]"
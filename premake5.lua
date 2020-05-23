workspace "Schmog"
	architecture "x64"
	startproject "Sandbox"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution dir)
IncludeDir = {}
IncludeDir["GLFW"] = "Schmog/vendor/GLFW/include"
IncludeDir["Glad"] = "Schmog/vendor/Glad/include"
IncludeDir["ImGui"] = "Schmog/vendor/imgui"
IncludeDir["glm"] = "Schmog/vendor/glm"

group "Dependencies"
include "Schmog/vendor/GLFW"
include "Schmog/vendor/Glad"
include "Schmog/vendor/imgui"

group ""


project "Schmog"
	location "Schmog"
	kind "SharedLib"
	language "C++"
	staticruntime "Off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "sgpch.h"
	pchsource "%{prj.name}/src/sgpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}
	
	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib",
		"ImGui"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines 
		{
			"SG_PLATFORM_WINDOWS",
			"SG_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "SG_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "SG_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "SG_DIST"
		runtime "Release"
		optimize "On"



project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "Off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Schmog/vendor/spdlog/include",
		"Schmog/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Schmog"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines 
		{
			"SG_PLATFORM_WINDOWS"
		}


	filter "configurations:Debug"
		defines "SG_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "SG_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "SG_DIST"
		runtime "Release"
		optimize "On"
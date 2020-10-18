workspace "Schmog"
	architecture "x64"
	startproject "Sandbox"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution dir)
IncludeDir = {}
IncludeDir["GLFW"] = "Schmog/vendor/GLFW/include"
IncludeDir["Glad"] = "Schmog/vendor/Glad/include"
IncludeDir["ImGui"] = "Schmog/vendor/imgui"
IncludeDir["glm"] = "Schmog/vendor/glm"
IncludeDir["stb_image"] = "Schmog/vendor/stb_image"

group "Dependencies"
include "Schmog/vendor/GLFW"
include "Schmog/vendor/Glad"
include "Schmog/vendor/imgui"

group ""


project "Schmog"
	location "Schmog"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "sgpch.h"
	pchsource "%{prj.name}/src/sgpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h"
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}
	
	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines 
		{
			"SG_PLATFORM_WINDOWS",
			"SG_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}


	filter "configurations:Debug"
		defines "SG_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SG_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "SG_DIST"
		runtime "Release"
		optimize "on"



project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Schmog/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Schmog"
	}

	filter "system:windows"
		systemversion "latest"

		defines 
		{
			"SG_PLATFORM_WINDOWS"
		}


	filter "configurations:Debug"
		defines "SG_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SG_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "SG_DIST"
		runtime "Release"
		optimize "on"
		
		
project "Schmeditor"
	location "Schmeditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Schmog/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Schmog"
	}

	filter "system:windows"
		systemversion "latest"

		defines 
		{
			"SG_PLATFORM_WINDOWS"
		}


	filter "configurations:Debug"
		defines "SG_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SG_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "SG_DIST"
		runtime "Release"
		optimize "on"
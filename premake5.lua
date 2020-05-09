workspace "Schmog"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Schmog"
	location "Schmog"
	kind "SharedLib"
	language "C++"

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
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"SG_PLATFORM_WINDOWS",
			"SG_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "SG_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "SG_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "SG_DIST"
		optimize "On"



project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"Schmog/src"
	}

	links
	{
		"Schmog"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"SG_PLATFORM_WINDOWS"
		}


	filter "configurations:Debug"
		defines "SG_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "SG_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "SG_DIST"
		optimize "On"
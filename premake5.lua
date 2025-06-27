function common()
	includedirs("/usr/X11R7/include")
	includedirs("/usr/X11R6/include")
	includedirs("/usr/pkg/include/ncurses")
	includedirs("/usr/pkg/include")

	libdirs("/usr/X11R7/lib")
	libdirs("/usr/X11R6/lib")
	libdirs("/usr/pkg/lib")

	filter("configurations:Debug")
		defines({
			"DEBUG"
		})
		symbols("On")
	filter("configurations:Release")
		defines({
			"NDEBUG"
		})
		optimize("On")
	filter({})

	defines("_DEFAULT_SOURCE")
end

workspace("bb")
        configurations({
                "Debug",
                "Release"
        })

project("aalib")
	kind("StaticLib")
	files("src/aa/*.c")
	includedirs("src/aa")
	common()

project("bb")
	kind("ConsoleApp")
	files("src/bb/*.c")
	includedirs("src/aa")
	common()
	links("aalib")
	links({"ncurses", "slang"})

project("server")
	kind("ConsoleApp")
	targetname("bb_snd_server")
	files("src/server/*.c")
	common()
	defines("ALSA")
	links("asound")

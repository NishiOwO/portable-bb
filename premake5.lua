function common()
	filter("platforms:Native")
		includedirs("/usr/X11R7/include")
		includedirs("/usr/X11R6/include")
		includedirs("/usr/pkg/include/ncurses")
		includedirs("/usr/pkg/include")

		libdirs("/usr/X11R7/lib")
		libdirs("/usr/X11R6/lib")
		libdirs("/usr/pkg/lib")
	filter({})

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
        platforms({
                "Native",
                "Win32",
                "Win64"
        })
        defaultplatform("Native")

filter("platforms:Win32")
        system("windows")
        architecture("x86")
        gccprefix("i686-w64-mingw32-")

filter("platforms:Win64")
        system("windows")
        architecture("x86_64")
        gccprefix("x86_64-w64-mingw32-")

filter({})

project("aalib")
	kind("StaticLib")
	files("src/aa/*.c")
	filter("system:not windows")
		removefiles("src/aa/aawin32.c")
		removefiles("src/aa/aawin32kbd.c")
	filter({})
	includedirs("src/aa")
	common()

project("bb")
	kind("ConsoleApp")
	files("src/bb/*.c")
	includedirs("src/aa")
	common()
	links("aalib")
	filter("system:windows")
		links("ws2_32")
	filter("system:not windows")
		links({"ncurses", "slang"})
	filter({})

project("server")
	kind("ConsoleApp")
	targetname("bb_snd_server")
	files("src/server/*.c")
	common()
	defines("MINIAUDIO")
	filter("system:windows")
		links("ws2_32")
	filter("system:not windows")
		links("pthread")
	filter({})

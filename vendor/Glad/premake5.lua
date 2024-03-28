project "Glad"
    kind "StaticLib"
    language "C"
    staticruntime "on"
    
    architecture "x86_64"
    
    targetdir ("bin/%{cfg.longname}")
    objdir ("bin-int/%{cfg.longname}")

    files
    {
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/glad.c"
    }

    includedirs
    {
        "include"
    }
    
    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

#ifndef PLATFORM
#define PLATFORM

#if defined(_WIN32)
    #define WINDOWS "windows" // Windows
#elif defined(_WIN64)
    #define WINDOWS "windows" // Windows
#elif defined(__CYGWIN__) && !defined(_WIN32)
    #define WINDOWS "windows" // Windows (Cygwin POSIX under Microsoft Window)
#elif defined(__ANDROID__)
    #define ANDROID "android" // Android (implies Linux, so it must come first)
#elif defined(__linux__)
    #define LINUX "linux" // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other
#elif defined(__unix__) || !defined(__APPLE__) && defined(__MACH__)
    #include <sys/param.h>
    #if defined(BSD)
        #define BSD "bsd" // FreeBSD, NetBSD, OpenBSD, DragonFly BSD
    #endif
#elif defined(__hpux)
    #define HP-UX "hp-ux" // HP-UX
#elif defined(_AIX)
    #define AIX "aix" // IBM AIX
#elif defined(__APPLE__) && defined(__MACH__) // Apple OSX and iOS (Darwin)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR == 1
        #define IOS "ios" // Apple iOS
    #elif TARGET_OS_IPHONE == 1
        #define IOS "ios" // Apple iOS
    #elif TARGET_OS_MAC == 1
        #define OSX "osx" // Apple OSX
    #endif
#elif defined(__sun) && defined(__SVR4)
    #define SOLARIS "solaris" // Oracle Solaris, Open Indiana
#else
    #define PLATFORM_NAME NULL
#endif

#endif
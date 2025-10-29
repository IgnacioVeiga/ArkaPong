#pragma once
// Define CORE_API for symbol visibility

#if defined(_WIN32) && defined(CORE_BUILD_DLL)
    #define CORE_API __declspec(dllexport)
#elif defined(_WIN32)
    #define CORE_API __declspec(dllimport)
#elif defined(__GNUC__) && __GNUC__ >= 4
    #define CORE_API __attribute__((visibility("default")))
#else
    #define CORE_API
#endif

#ifndef UTILS_HPP
#define UTILS_HPP

#define likely(x)       __builtin_expect(!!(x), 1)
#define unlikely(x)     __builtin_expect(!!(x), 0)

#define ATV_UNUSED(x) do {(void)x;} while(0)

#ifdef ATV_DEBUG
#include <iostream>
#define DEBUG_MSG(x) do {std::cerr << x << std::endl;} while(0)
#else
#define DEBUG_MSG(x) 
#endif

#if defined(__linux) || defined(__linux__)
#  define ATV_NATIVE_TLS __thread
#elif defined(_WIN32) || defined(_WIN64)
#  define ATV_NATIVE_TLS __declspec(thread)
#elif defined(__FreeBSD__) || (defined(__APPLE__) && defined(__MACH__))
#  define ATV_NATIVE_TLS __thread
#else
#  warning "Native thread local storage may not be supported for this platform"
#  warning "Using: thread_local from C++11"
#  define ATV_NATIVE_TLS thread_local
#endif

#endif // UTILS_HPP

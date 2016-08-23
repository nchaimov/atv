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

#endif // UTILS_HPP

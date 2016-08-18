#ifndef UTILS_HPP
#define UTILS_HPP

#define likely(x)       __builtin_expect(!!(x), 1)
#define unlikely(x)     __builtin_expect(!!(x), 0)

#endif // UTILS_HPP

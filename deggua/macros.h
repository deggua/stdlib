#pragma once

#include <stddef.h>

#include <deggua/target.h>
#include <deggua/logging.h>

#define containerof(ptr, type, member) ((type*)((char*)(ptr)-offsetof(type, member)))
#define lengthof(arr)                  (sizeof(arr)/sizeof((arr)[0]))
#define indexof(ptr, arr)              (((ptr) - &(arr)[0]) / sizeof((arr)[0]))

#define likely(x)   (__builtin_expect(!!(x), 1))
#define unlikely(x) (__builtin_expect(!!(x), 0))

#undef min
#define min(x, y) ({    \
    typeof(x) x_ = (x); \
    typeof(y) y_ = (y); \
    x_ > y_ ? y_ : x_;  \
})

#undef max
#define max(x, y) ({    \
    typeof(x) x_ = (x); \
    typeof(y) y_ = (y); \
    x_ < y_ ? y_ : x_;  \
})

#define abs(x) ({       \
    typeof(x) x_ = (x); \
    x_ < 0 ? -x_ : x_;  \
})

#define ASSUME(expr)                 \
    do {                             \
        if (!(expr)) {               \
            __builtin_unreachable(); \
        }                            \
    } while (0)

#if TARGET_ARCH == TARGET_ARCH_I386 || TARGET_ARCH == TARGET_ARCH_AMD64
#define BREAKPOINT() asm volatile("int3\nnop\n")
#else
# error "Unsupported"
#endif

#define ABORT(msg, ...)               \
    do {                              \
        LOG_FATAL(                    \
            "Aborted in %s @ %s:%d\n" \
            "Reason: " msg "\n\n",    \
            __func__,                 \
            __FILE__,                 \
            __LINE__,                 \
            ##__VA_ARGS__);           \
        BREAKPOINT();                 \
    } while (0)

#define STATIC_ASSERT(cond) _Static_assert((cond), #cond)

#define ASSERT(cond)                               \
    do {                                           \
        if (!(cond)) {                             \
            LOG_FATAL(                             \
                "Assertion failed in %s @ %s:%d\n" \
                "Condition: %s\n\n",               \
                __func__,                          \
                __FILE__,                          \
                __LINE__,                          \
                #cond);                            \
            BREAKPOINT();                          \
        }                                          \
    } while (0)

#define ATTR(...) __attribute__((__VA_ARGS__))

#define UNUSED(x) ((void)(x))

#if TARGET_OS == TARGET_OS_WINDOWS
# define SYM_EXPORT __declspec(dllexport)
# define SYM_WEAK   __attribute((weak))
#else
# define SYM_EXPORT __attribute((visibility("default")))
# define SYM_WEAK   __attribute((weak))
#endif

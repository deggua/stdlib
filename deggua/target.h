#pragma once

/* --- TARGET_COMPILER --- */

#define TARGET_COMPILER_CLANG   (0)
#define TARGET_COMPILER_GCC     (1)
#define TARGET_COMPILER_MSVC    (2)
#define TARGET_COMPILER_ICC     (3)
// TODO: suncc, mingw?

#if defined(__INTEL_COMPILER)
# define TARGET_COMPILER (TARGET_COMPILER_ICC)
#elif defined(__clang__)
# define TARGET_COMPILER (TARGET_COMPILER_CLANG)
#elif defined(__GNUC__) || defined(__GNUG__)
# define TARGET_COMPILER (TARGET_COMPILER_GCC)
#elif defined(_MSC_VER)
# define TARGET_COMPILER (TARGET_COMPILER_MSVC)
#else
# error "Unable to determine target compiler"
#endif

/* --- TARGET_ENDIAN --- */
#define TARGET_ENDIAN_BIG    (0)
#define TARGET_ENDIAN_LITTLE (1)

#if defined(__BYTE_ORDER) && __BYTE_ORDER == __BIG_ENDIAN || \
    defined(__BIG_ENDIAN__) || \
    defined(__ARMEB__) || \
    defined(__THUMBEB__) || \
    defined(__AARCH64EB__) || \
    defined(_MIBSEB) || defined(__MIBSEB) || defined(__MIBSEB__)
# define TARGET_ENDIAN (TARGET_ENDIAN_BIG)
#elif defined(__BYTE_ORDER) && __BYTE_ORDER == __LITTLE_ENDIAN || \
    defined(__LITTLE_ENDIAN__) || \
    defined(__ARMEL__) || \
    defined(__THUMBEL__) || \
    defined(__AARCH64EL__) || \
    defined(_MIPSEL) || defined(__MIPSEL) || defined(__MIPSEL__)
# define TARGET_ENDIAN (TARGET_ENDIAN_LITTLE)
#else
# error "Unable to determine target endianness"
#endif

/* --- TARGET_ARCH --- */

#define TARGET_ARCH_I386      (0)
#define TARGET_ARCH_AMD64     (1)
#define TARGET_ARCH_ARM       (2)
#define TARGET_ARCH_ARM64     (3)
#define TARGET_ARCH_MIPS      (4)
#define TARGET_ARCH_MIPS64    (5)
#define TARGET_ARCH_POWERPC   (6)
#define TARGET_ARCH_POWERPC64 (7)
#define TARGET_ARCH_SPARCV8   (8)
#define TARGET_ARCH_SPARCV9   (9)
#define TARGET_ARCH_IA64      (10)
#define TARGET_ARCH_RISCV64   (11)
#define TARGET_ARCH_AVR       (12)

#if (TARGET_COMPILER == TARGET_COMPILER_CLANG) || (TARGET_COMPILER == TARGET_COMPILER_GCC) || (TARGET_COMPILER == TARGET_COMPILER_ICC)
# if defined(__i386__)
#  define TARGET_ARCH (TARGET_ARCH_I386)
# elif defined(__amd64__)
#  define TARGET_ARCH (TARGET_ARCH_AMD64)
# elif defined(__arm__)
#  define TARGET_ARCH (TARGET_ARCH_ARM)
# elif defined(__aarch64__)
#  define TARGET_ARCH (TARGET_ARCH_ARM64)
# elif defined(__mips__) && !defined(__mips64)
#  define TARGET_ARCH (TARGET_ARCH_MIPS)
# elif defined(__mips__) && defined(__mips64)
#  define TARGET_ARCH (TARGET_ARCH_MIPS64)
# elif defined(__powerpc__) && !defined(__powerpc64__)
#  define TARGET_ARCH (TARGET_ARCH_POWERPC)
# elif defined(__powerpc__) && defined(__powerpc64__)
#  define TARGET_ARCH (TARGET_ARCH_POWERPC64)
# elif defined(__sparc_v8__)
#  define TARGET_ARCH (TARGET_ARCH_SPARCV8)
# elif defined(__sparc_v9__)
#  define TARGET_ARCH (TARGET_ARCH_SPARCV9)
# elif defined(__ia64__)
#  define TARGET_ARCH (TARGET_ARCH_IA64)
# elif defined(__riscv)
#  define TARGET_ARCH (TARGET_ARCH_RISCV64)
# elif defined(__AVR__)
#  define TARGET_ARCH (TARGET_ARCH_AVR)
# else
#  error "Unable to determine target architecture"
# endif
#elif (TARGET_COMPILER == TARGET_COMPILER_MSVC)
# if defined(_M_IX86)
#  define TARGET_ARCH (TARGET_ARCH_I386)
# elif defined(_M_AMD64)
#  define TARGET_ARCH (TARGET_ARCH_AMD64)
# elif defined(_M_ARM)
#  define TARGET_ARCH (TARGET_ARCH_ARM)
# elif defined(_M_ARM64)
#  define TARGET_ARCH (TARGET_ARCH_ARM64)
# else
#  error "Unable to determine target architecture"
# endif
#else
# error "Unable to determine target architecture"
#endif

/* --- TARGET_OS --- */

#define TARGET_OS_WINDOWS (0)
#define TARGET_OS_LINUX   (1)
#define TARGET_OS_ANDROID (2)
#define TARGET_OS_SOLARIS (3)
#define TARGET_OS_VXWORKS (4)
#define TARGET_OS_MACOSX  (5)

#if (TARGET_COMPILER == TARGET_COMPILER_CLANG) || (TARGET_COMPILER == TARGET_COMPILER_GCC) || (TARGET_COMPILER == TARGET_COMPILER_ICC)
# if defined(_WIN16) || defined(_WIN32) || defined(_WIN64)
#  define TARGET_OS (TARGET_OS_WINDOWS)
# elif defined(__linux__)
#  define TARGET_OS (TARGET_OS_LINUX)
# elif defined(__ANDROID__)
#  define TARGET_OS (TARGET_OS_ANDROID)
# elif defined(__sun) && defined(__SVR4)
#  define TARGET_OS (TARGET_OS_SOLARIS)
# elif defined(__VXWORKS__)
#  define TARGET_OS (TARGET_OS_VXWORKS)
# elif defined(__APPLE__) && defined(__MACH__)
#  define TARGET_OS (TARGET_OS_MACOSX)
# else
#  error "Unable to determine target operating system"
# endif
#elif (TARGET_COMPILER == TARGET_COMPILER_MSVC)
# if defined(_WIN16) || defined(_WIN32) || defined(_WIN64)
#  define TARGET_OS (TARGET_OS_WINDOWS)
# else
#  error "Unable to determine target operating system"
# endif
#endif

/* --- TARGET_ABI --- */
// TODO: this is trickier, there aren't explicit defines as far as I can tell
// so you have to determine it based on the compiler and target OS + arch

// TODO: bits per byte, register width (8, 16, 32, 64, etc.), address width, etc

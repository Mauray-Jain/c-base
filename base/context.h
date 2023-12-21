#ifndef BASE_CONTEXT_H
#define BASE_CONTEXT_H

// https://sourceforge.net/p/predef/wiki/Home/

// Compiler
#if defined (__clang__)
#	define COMPILER_CLANG
#elif defined (_MSC_VER)
#	define COMPILER_CL
#elif defined (__GNUC__)
#	define COMPILER_GCC
#else
#	error Missing compiler detection
#endif

// OS
#if defined (__gnu_linux__)
#	define OS_LINUX
#elif defined (__APPLE__) && defined (__MACH__)
#	define OS_MAC
#elif defined (_WIN32) || defined (_WIN64)
#	define OS_WINDOWS
#else
#	error Missing os detection
#endif

// Architecture
#if defined (__amd64__) || defined (_M_AMD64) || defined (__x86_64__) || defined (__x86_64)
#	define ARCH_X64
#elif defined (__i386__) || defined (_M_IX86) || defined (_X86_) || defined (_M_I386)
#	define ARCH_X86
#elif defined (__arm__) || defined (_M_ARM)
#	define ARCH_ARM
#elif defined (__aarch64__) || defined (_M_ARM64)
#	define ARCH_ARM64
#else
#	error Missing arch detection
#endif

#endif /* BASE_CONTEXT_H */

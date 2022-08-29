#ifndef NOVA_BASE_H
#define NOVA_BASE_H

#ifdef _MSC_VER
// Note(Nova): MSVC compiler produces error C4146: unary minus operator applied to unsigned type, result still unsigned
// which is not an error. The pragma command disables the error. count_set_bit function is an example where
// this error can occur without warnings disabled.
#pragma warning(disable:4146)

// It might be also good to consider turning off these warnings belows
// Warning	C26812	The enum type 'xyz' is unscoped. Prefer 'enum class' over 'enum'
#pragma warning(disable:26812)
// Warning	C26495	Variable 'xyz::x' is uninitialized. Always initialize a member variable
#pragma warning(disable:26495)
// Warning	C4201	nonstandard extension used: nameless struct/union
#pragma warning(disable:4201)
// Warning	C4458	declaration of 'xyz' hides class member
#pragma warning(disable:4458)
// Warning	C4100	'xoffset': unreferenced formal parameter
// #pragma warning(disable:4100)
// Warning	C4505	'inf_f32': unreferenced function with internal linkage has been removed	
#pragma warning(disable:4505)

// Note(Nova): Linker warnings can be disabled by passing "/ignore:<warning_number>" to linker options. This is in Properties->Linker->Command Line.
// Warning LNK4099 PDB 'xyz.pdb' was not found with 'xyz.lib(xyz.obj)'
#endif

/////////////////////////////////////////////////////////
//                      Assertions
/////////////////////////////////////////////////////////
// See https://www.pixelbeat.org/programming/gcc/static_assert.html for static asserts

#ifdef ENABLE_ASSERT
    #define ASSERT(expression) { if(!(expression)) { *(int *)0 = 0; } else {} }
    #ifdef _MSC_VER
        #define STATIC_ASSERT(expression) _STATIC_ASSERT((expression))
    #elif defined(__clang__) || defined(__gcc__)
        #define STATIC_ASSERT(expression) _Static_assert((expression))
    #endif  // _MSC_VER
#else   // TNABLE_ASSERT else
    #define ASSERT(expression)
#endif  // ENABLE_ASSERT

/////////////////////////////////////////////////////////
//                      Util Macros
/////////////////////////////////////////////////////////

// Intializes the memory allocated for a object on stack to 0
#define INITIALIZE_ZERO { 0 }

// Exports a c like function without name mangling
#ifdef __cplusplus
    #define CFUNCTION extern "C"
#endif

// Gets the count of elements in an array if the array if of type A[size]
// Note(Nova): Does not work on pointers
#define ARRAYCOUNT(array) (sizeof((array)) / sizeof((array)[0]))

// Gets the offset (in bytes) of an element from a given structure type
#define MEMBER_OFFSET(type, element) ((size_t)(&(((type*)(0))->element)))

// Converts any given type into a const char* of itself
#define STR_OF_TYPE(type) ((const char*)#type)

#define STRINGIFY_(s) #s
// Converts token to c string
#define STRINGIFY(s) STRINGIFY_(s)

#define GLUE_(x, y) x##y
// Concatenates two tokens
#define GLUE(x, y) GLUE_(x, y)

/////////////////////////////////////////////////////////
//                Bit Manipulation Macro
/////////////////////////////////////////////////////////

// Sets the bit at index to 1
#define SET_BIT32(number, bit_index) ((number) |= (1 << (bit_index)))

// Gets the bit at index
#define GET_BIT32(number, bit_index) ((number) & (1 << (bit_index)))

// Sets the bit at index to 0
#define POP_BIT32(number, bit_index) ((number) &= ~(1 << (bit_index)))

// Sets the bit at index to 1
#define SET_BIT64(number, bit_index) ((number) |= (1ULL << (bit_index)))

// Gets the bit at index
#define GET_BIT64(number, bit_index) ((number) & (1ULL << (bit_index)))

// Sets the bit at index to 0
#define POP_BIT64(number, bit_index) ((number) &= ~(1ULL << (bit_index)))


/////////////////////////////////////////////////////////
//                    Math Macro
/////////////////////////////////////////////////////////

// Return square of a number
#define SQUARE(a) ((a) * (a))

// Returns cube of a number
#define CUBE(a) ((a) * (a) * (a))

// Returns absolute value of number
#define ABS(a) ((a) < 0 ? -(a) : (a))

// Returns minimum of two numbers
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

// Returns maximum of two numbers
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

// Returns a clamped value between closed interval [min, max]
#define CLAMP(value, min, max) (((value) < (min)) ? (min) : \
								((value) > (max)) ? (max) : (value))

/////////////////////////////////////////////////////////
//                 Platform Detection
/////////////////////////////////////////////////////////

#if defined(_WIN32) || defined(_WIN64)
    #ifndef OS_WINDOWS
        #define OS_WINDOWS
    #endif
#elif defined(__linux__)
    #ifndef OS_LINUX
        #define OS_LINUX
    #endif
#elif defined(__APPLE__)
    #if defined(TARGET_OS_MAC)
        #ifndef OS_APPLE_MAC
            #define OS_APPLE_MAC
        #endif
    #elif defined(TARGET_OS_IPHONE)
        #ifndef OS_APPLE_IPHONE
            #define OS_APPLE_IPHONE
        #endif
    #endif
#elif defined(__ANDROID__)
    #ifndef OS_ANDROID
        #define OS_ANDROID
    #endif
#endif

/////////////////////////////////////////////////////////
//                 Don't use static
/////////////////////////////////////////////////////////
// Note(Nova): Cannot use "global" for some reason so using "global_variable" instead
#define global_variable static
#define local_persist static
#define function static


/////////////////////////////////////////////////////////
//                   Basic Types
/////////////////////////////////////////////////////////

#include <stdint.h>  // for std int types
#include <string.h>  // for strlen

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef s8 b8;
typedef s16 b16;
typedef s32 b32;

typedef float f32;
typedef double f64;

typedef char c8;
typedef char16_t c16;
typedef char32_t c32;
typedef unsigned char uc8;

/////////////////////////////////////////////////////////
//                  Type Constants
/////////////////////////////////////////////////////////

global_variable s8 min_s8 = (s8)INT8_MIN;
global_variable s16 min_s16 = (s16)INT16_MIN;
global_variable s32 min_s32 = (s32)INT32_MIN;
global_variable s64 min_s64 = (s64)INT64_MIN;

global_variable s8 max_s8 = (s8)INT8_MAX;
global_variable s16 max_s16 = (s16)INT16_MAX;
global_variable s32 max_s32 = (s32)INT32_MAX;
global_variable s64 max_s64 = (s64)INT64_MAX;

global_variable u8 max_u8 = (u8)UINT8_MAX;
global_variable u16 max_u16 = (u16)UINT16_MAX;
global_variable u32 max_u32 = (u32)UINT32_MAX;
global_variable u64 max_u64 = (u64)UINT64_MAX;

// For floating point types min returns the smallest finite number that is > 0 representable in the type 
// (i.e. the number having the lowest absolute value != 0) while lowest returns the smallest finite 
// number that is representable (i.e. the negative number of maximal absolute value that is less than -infinity).
#ifdef FLOAT_LIMIT_VARS
#include <limits>
global_variable f32 min_f32 = (f32)std::numeric_limits<f32>::min();
global_variable f32 lowest_f32 = (f32)std::numeric_limits<f32>::lowest();
global_variable f32 max_f32 = (f32)std::numeric_limits<f32>::max();

global_variable f64 min_f64 = (f64)std::numeric_limits<f64>::min();
global_variable f64 lowest_f64 = (f64)std::numeric_limits<f64>::lowest();
global_variable f64 max_f64 = (f64)std::numeric_limits<f64>::max();
#endif

#endif

#ifndef _TYPE_H
#define _TYPE_H

// Custom shorthand types
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

// Internal type definitions to support standard types
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

// **Corrected:** Define __int64_t as 'signed long' to match toolchain expectations
typedef signed long __int64_t;       // Changed from 'signed long long' to 'signed long'
typedef unsigned long __uint64_t;     // Ensure consistency

// Standard fixed-width integer types
typedef __int8_t int8_t;
typedef __int16_t int16_t;
typedef __int32_t int32_t;
typedef __int64_t int64_t;
typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;
typedef __uint64_t uint64_t;

// Additional standard types
typedef unsigned long size_t;
typedef unsigned long caddr_t;

// Boolean type
typedef _Bool bool;

// NULL definition
#define NULL ((void *)0)

// Boolean constants
enum {
    false = 0,
    true  = 1
};

// Alignment attribute
#define cacheline_aligned __attribute__((__aligned__(64)))

#endif /* _TYPE_H */


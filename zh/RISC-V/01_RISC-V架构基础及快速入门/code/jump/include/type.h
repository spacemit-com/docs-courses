#ifndef _TYPE_H
#define _TYPE_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;
typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;
typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;
typedef __uint64_t uint64_t;
typedef unsigned long size_t;
typedef unsigned long caddr_t;

typedef _Bool bool;

#define NULL ((void *)0)

enum {
	false	= 0,
	true	= 1
};

#define cacheline_aligned __attribute__((__aligned__(64)))

#endif /*_TYPE_H*/

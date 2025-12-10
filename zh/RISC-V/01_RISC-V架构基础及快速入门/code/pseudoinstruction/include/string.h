#ifndef	_STRING_H
#define	_STRING_H

#include "type.h"

void *memcpy(void *dest, const void *src, size_t count);
void *memset(void *s, int c, size_t count);
size_t strlen(const char *s);

#endif /* _STRING_H*/

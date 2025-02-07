#ifndef _PRINT_H
#define _PRINT_H

#include <stdint.h>

/* Print a single character */
extern void printChar(char);
#pragma aux printChar =         \
  "mov ah, 0xE"                 \
  "int 0x10"                    \
  __parm [__al]                 \
  __modify [__ax __bx __cx];

extern void printHex(uint16_t val, uint16_t width, char leading);
extern void printHex32(uint32_t val, uint16_t width, char leading);
extern void printDec(uint16_t val, uint16_t width, char leading);

extern void consolef(const char *format, ...);

#endif /* _PRINT_H */

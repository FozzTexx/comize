#include "print.h"
#include <stdarg.h>
#include <ctype.h>

static char *hex_digits = "0123456789ABCDEF";

void printHexDigit(char val)
{
  // Compiler is totally bonkers. I had this as a switch and it didn't work!
  if (val == 0)
    printChar('0');
  else if (val == 1)
    printChar('1');
  else if (val == 2)
    printChar('2');
  else if (val == 3)
    printChar('3');
  else if (val == 4)
    printChar('4');
  else if (val == 5)
    printChar('5');
  else if (val == 6)
    printChar('6');
  else if (val == 7)
    printChar('7');
  else if (val == 8)
    printChar('8');
  else if (val == 9)
    printChar('9');
  else if (val == 10)
    printChar('A');
  else if (val == 11)
    printChar('B');
  else if (val == 12)
    printChar('C');
  else if (val == 13)
    printChar('D');
  else if (val == 14)
    printChar('E');
  else if (val == 15)
    printChar('F');

  return;
}

void printHex(uint16_t val, uint16_t width, char leading)
{
  uint16_t digits, tval;


  for (tval = val, digits = 0; tval; tval >>= 4, digits++)
    ;
  if (!digits)
    digits = 1;

  for (; digits < width; width--)
    printChar(leading);

  while (digits) {
    digits--;
#if 0
    // I don't know what's going on with the compiler but this doesn't work
    printChar(hex_digits[(val >> 4 * digits) & 0xf]);
#else
    // but this does
    printHexDigit((val >> 4 * digits) & 0xf);
#endif
  }

  return;
}

void printHex32(uint32_t val, uint16_t width, char leading)
{
  uint16_t digits;
  uint32_t tval;


  for (tval = val, digits = 0; tval; tval >>= 4, digits++)
    ;
  if (!digits)
    digits = 1;

  for (; digits < width; width--)
    printChar(leading);

  while (digits) {
    digits--;
#if 0
    // I don't know what's going on with the compiler but this doesn't work
    printChar(hex_digits[(val >> 4 * digits) & 0xf]);
#else
    // but this does
    printHexDigit((val >> 4 * digits) & 0xf);
#endif
  }

  return;
}

void printDec(uint16_t val, uint16_t width, char leading)
{
  uint16_t digits, tval, tens;


  for (tval = val, digits = 0; tval; tval /= 10, digits++)
    ;
  if (!digits)
    digits = 1;
  for (tval = digits - 1, tens = 1; tval; tval--, tens *= 10)
    ;

  for (; digits < width; width--)
    printChar(leading);

  while (digits) {
    digits--;
    printChar('0' + (val / tens) % 10);
    tens /= 10;
  }

  return;
}

void printDec32(uint32_t val, uint16_t width, char leading)
{
  uint32_t tval, tens;
  uint16_t digits;


  for (tval = val, digits = 0; tval; tval /= 10, digits++)
    ;
  if (!digits)
    digits = 1;
  for (tval = digits - 1, tens = 1; tval; tval--, tens *= 10)
    ;

  for (; digits < width; width--)
    printChar(leading);

  while (digits) {
    digits--;
    printChar('0' + (val / tens) % 10);
    tens /= 10;
  }

  return;
}

void consolef(const char *format, ...)
{
  const char *pf;
  va_list args;
  char leader;
  uint8_t width;


  printHex32((uint32_t) format, 8, '0');
  printChar('\r');
  printChar('\n');
  va_start(args, format);

  for (pf = format; pf && *pf; pf++) {
    switch (*pf) {
    case '\n':
      printChar('\r');
      printChar('\n');
      break;

    case '%':
      pf++;
      if (!*pf)
	break;

      if (*pf == 'c')
	printChar(va_arg(args, char));
      else {
	leader = ' ';
	width = 0;

	if (isdigit(*pf)) {
	  if (*pf == '0') {
	    leader = '0';
	    pf++;
	  }

	  for (width = 0; isdigit(*pf); pf++) {
	    width *= 10;
	    width += *pf - '0';
	  }
	}

	if (*pf == 'l') {
	  pf++;
	  if (*pf == 'x')
	    printHex32(va_arg(args, uint32_t), width, leader);
	  if (*pf == 'i' || *pf == 'd')
	    printDec32(va_arg(args, uint32_t), width, leader);
	}
	else {
	  if (*pf == 'x')
	    printHex(va_arg(args, uint16_t), width, leader);
	  if (*pf == 'i' || *pf == 'd')
	    printDec(va_arg(args, uint16_t), width, leader);
	}
      }
      break;

    default:
      printChar(*pf);
      break;
    }
  }

  va_end(args);

  return;
}

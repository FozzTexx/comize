#include "useless.h"
#include "print.h"
#include <stdlib.h>

char *hello = "Hello again\n";

int _small_code()
{
  int idx, a;


  a = atoi("5");
  a += dumb();
  for (idx = 0, a = 2; idx < 5; idx++)
    a = a * 2;
  printChar('H');
  printChar('e');
  printChar('l');
  printChar('l');
  printChar('o');
  printChar(' ');
  printHex32((uint32_t) hello, 8, '0');
  printChar('\r');
  printChar('\n');
  printDec(sizeof(char *), 0, 0);
  printChar('\r');
  printChar('\n');
  consolef(hello);

  return 0;
}

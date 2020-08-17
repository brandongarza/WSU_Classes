#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef unsigned int u32;
char *ctable = "0123456789ABCDEF";

int myprintf(char *fmt, ...);

int main(int argc, char *argv[ ])
{
    myprintf("cha=%c string=%s      dec=%d hex=%x oct=%o neg=%d\n", 
	       'A', "this is a test", 100,    100,   100,  -100);
}

int rpu(u32 x, int BASE)
{  
    char c;
    if (x){
       c = ctable[x % BASE];
       rpu(x / BASE, BASE);
       putchar(c);
    }
}

int printu(u32 x)
{
   (x==0)? putchar('0') : rpu(x, 10);
   putchar(' ');
  printf("\n");
}

int prints(char *s)
{
    int i = 0;

  while (s[i] =! '\0')
  {
    putchar(s[i]);
    i++;
  }
  printf("\n");
}

int printd(int x)
{
  if (x < 0) 
  {
    x = (x)*(-1);
  }
  rpu(x, 10);
  printf("\n");
}

int printx(u32 x)
{
  printf("0x");
  rpu(x, 16);
  printf("\n");
}

int printo(u32 x)
{
  printf("0");     
  rpu(x, 8);
  printf("\n");
}

int myprintf(char *fmt, ...)
{
  char *cp = fmt;
  va_list ip;
  va_start (ip, cp);

  while (*cp)
  {
    if(*cp == '%')
    {
     cp++;
     switch (*cp)
     {
      case 'c':
       putchar(va_arg(ip, int));
       break;

      case 's':
       prints(va_arg(ip, char*));
       break;

      case 'u':
       printu(va_arg(ip, int));
       break;

      case 'd':
       printd(va_arg(ip, int));
       break;

      case 'o':
       printo(va_arg(ip, int));
       break;

      case 'x':
       printx(va_arg(ip, int));
       break; 
      }
    }
    else
    {
      putchar(*cp);
    }

    cp++;

    va_end(ip);
  }  
}
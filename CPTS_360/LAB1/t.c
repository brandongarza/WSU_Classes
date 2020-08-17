#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

int *FP;
typedef unsigned int u32;
char *ctable = "0123456789ABCDEF";

int A(int x, int y);
int B(int x, int y);
int C(int x, int y);
int myprintf(char *fmt, ...);


int main(int argc, char *argv[ ], char *env[ ])
{
  int a,b,c;
  printf("enter main\n");
  
  printf("&argc=%x argv=%x env=%x\n", &argc, argv, env);
  printf("&a=%8x &b=%8x &c=%8x\n\n", &a, &b, &c);

  printf("MyPrintf Ouput\n");
  myprintf("&argc=%x argv=%x env=%x\n", &argc, argv, env);
  myprintf("&a=%x &b=%x &c=%x\n\n", &a, &b, &c);

/*(1). Write C code to print values of argc and argv[] entries*/
  printf("argc value: %d\nargv[] value: %d\n\n", argv, argc);

  a=1; b=2; c=3;
  A(a,b);
  printf("exit main\n");


}

int A(int x, int y)
{
  int d,e,f;
  printf("enter A\n");
  // PRINT ADDRESS OF d, e, f
  d=4; e=5; f=6;

  printf("Address of d: %8x\nAddress of e: %8x\nAddress of f: %8x\n\n", &d, &e, &f);

  B(d,e);
  printf("exit A\n");
}

int B(int x, int y)
{
  int g,h,i;
  printf("enter B\n");
  // PRINT ADDRESS OF g,h,i
  g=7; h=8; i=9;

  printf("Address of g: %8x\nAddress of h: %8x\nAddress of i: %8x\n\n", &g, &h, &i);

  C(g,h);
  printf("exit B\n");
}

int C(int x, int y)
{
  int u, v, w, i, *p, *temp;

  printf("enter C\n");
  // PRINT ADDRESS OF u,v,w,i,p;
  u=10; v=11; w=12; i=13;

    printf("Address of u: %8x\nAddress of v: %8x\nAddress of w: %8x\nAddress of i: %8x\nAddress of p: %8x\n\n", &u, &v, &w, &i, &p);

  FP = (int *)getebp();
  p = (int *)&p;
  temp = FP;

/*(2). Write C code to print the stack frame link list.*/
  printf("Stack Frame Link List\n");

  while(*temp != 0)
  {
    printf("Address: %8x\n", *temp);
    temp = *temp;
  }

  printf("\nStack Contents\n");;

/*(3). Print the stack contents from p to the frame of main()
     YOU MAY JUST PRINT 128 entries of the stack contents.*/

  for (int x = 0; x < 127; x++)
  {
    printf("Address: %8x       Value: %8x\n", p, *p);
    p++;
  }

/*(4). On a hard copy of the print out, identify the stack contents
     as LOCAL VARIABLES, PARAMETERS, stack frame pointer of each function.*/
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
       ip++;
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



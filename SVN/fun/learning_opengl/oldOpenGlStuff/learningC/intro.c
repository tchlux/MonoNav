
#include <stdio.h>

int main()
{
  /* A nice long string */
  char string[256];                               

  printf( "Please enter a long string: " );

  /* notice stdin being passed in */
  fgets ( string, 256, stdin );           

  printf( "You entered a very long string, %s", string );

  getchar();
}


/* #include <stdio.h> */

/* int mult ( int x, int y ); */

/* int main() */
/* { */
/*   int x; */
/*   int y; */
  
/*   printf( "Please input two numbers to be multiplied: " ); */
/*   scanf( "%d", &x ); */
/*   scanf( "%d", &y ); */
/*   printf( "The product of your two numbers is %d\n", mult( x, y ) ); */
/*   getchar();  */
/* } */

/* int mult (int x, int y) */
/* { */
/*   return x * y; */
/* } */

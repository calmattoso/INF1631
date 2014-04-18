#include <cstdio>
#include "quociente.h"

#ifdef TIME
  #include "lib/CPUTimer/CPUtimer.h"
#endif

#define MAX 5

int main()
{

  for(int x = -MAX; x < MAX; ++x)
    for(int y = -MAX; y < MAX; ++y)
    {
      if( y == x )
        continue;

      Quociente q( x , y ) ;

      for(int k = 1  ; k < MAX; ++k)
      {
        long long quociente;
        
        quociente = q.FindFor( k ) ;

        printf( 
          "(%d^%d - %d^%d)/(%d - %d) = %I64d \n",
             x, k,   y, k,   x,   y,    quociente        );
      }
    }


  return 0;
}

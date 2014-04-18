#include <iostream>
#include <gmpxx.h>
#include <cstdlib>
#include "quociente.h"

#ifdef TIME
  #include "lib/CPUTimer/CPUtimer.h"
#endif

#define MAX 25

int main( int argc, const char * argv[] )
{
  int n_itrs = MAX;  

  if( argc > 1 )
    n_itrs = atoi( argv[1] );
    
    
  for(int x = -n_itrs; x < n_itrs; ++x)
    for(int y = -n_itrs; y < n_itrs; ++y)
    {
      if( y == x )
        continue;

      Quociente q( x , y ) ;

      for(int k = 1 ; k < n_itrs; ++k)
        std::cout << q.FindFor( k ) << std::endl;
    }


  return 0;
}

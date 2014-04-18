#include <iostream>
#include <gmpxx.h>
#include <cstdlib>
#include "quociente.h"

#ifdef TIME
  #include "../lib/CPUTimer/CPUTimer.h"
#endif

#define MAX 25

int main( int argc, const char * argv[] )
{
  int n_itrs = MAX;  

  if( argc > 1 )
    n_itrs = atoi( argv[1] );

  #ifdef TIME
    CPUTimer timer;
    int runs = 0;
  #endif
    
    
  for(int x = -n_itrs; x < n_itrs; ++x)
    for(int y = -n_itrs; y < n_itrs; ++y)
    {
      if( y == x )
        continue;

      Quociente q( x , y ) ;

      #ifdef TIME
        timer.start();
      #endif
      
      for(int k = 1 ; k < n_itrs; ++k)
      {
        #ifdef SHOW_QS
          mpz_class quoc = q.FindFor( k );

          std::cout << quoc << std::endl;
        #else
          q.FindFor( k )
        #endif

        runs++;
      }

      #ifdef TIME
        timer.stop();
      #endif
    }

  #ifdef TIME
    std::cout << "Total time: " << timer.getCPUTotalSecs() << "s" << std::endl;
    std::cout << "Avg. time : " << timer.getCPUTotalSecs()/runs << "s" << std::endl;
  #endif

  return 0;
}

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
  
  #ifdef SHOW_QS
    mpz_class quoc;
  #endif  

  if( argc > 1 )
    n_itrs = atoi( argv[1] );

  #ifdef TIME
    CPUTimer timer;
    unsigned int runs = 0;
  #endif

  for(int x = -n_itrs; x < n_itrs; ++x)
    for(int y = -n_itrs; y < n_itrs; ++y)
    {
      if( y == x )
        continue;

      Quociente q( x , y ) ;

      for(int k = 1 ; k < n_itrs; ++k)
      {
        std::cout << "x[" << x << "] y[" << y << "] k[" << k << "]\n";

        #ifdef TIME
          timer.start();
        #endif

        #ifdef SHOW_QS
          quoc = q.FindFor( k );
        #else
          q.FindFor( k );
        #endif

        #ifdef TIME
          timer.stop();
          
          runs++;

          std::cout << "\tTrial time: " << timer.getCPUCurrSecs() << "s" << std::endl;
        #endif
        #ifdef SHOW_QS
          std::cout << "\tQuocient: " << quoc << std::endl;
        #endif        

       
      }      
    }

  #ifdef TIME
    std::cout << "\n\nTotal time: " << timer.getCPUTotalSecs() << "s" << std::endl;
    std::cout << "Avg. time : " << timer.getCPUTotalSecs()/runs << "s" << std::endl;
  #endif

  return 0;
}

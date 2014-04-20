#include <iostream>
#include <deque>

#include "number.h"
#include "combinatorics.h"

#ifdef TIME
  #include "../lib/CPUTimer/CPUTimer.h"
  
  #define MAX(a,b) ((a>b)?a:b)
#endif



int main( int argc, const char * argv[] )
{
  Combinatorics c;
  unsigned int m_itrs = 15, k_itrs = 5;  

  #ifdef TIME
    CPUTimer timer;
    unsigned int runs = 0;
    unsigned int maxM , maxK ; /* remember m and k for largest time */
    double maxTrialTime = 0.0;
  #endif

  if( argc >= 3 )
  {
    m_itrs = atoi( argv[1] );
    k_itrs = atoi( argv[2] );
  }

  /* 
   *  Reuse the same object so that the algorithm can remember numbers
   *    with ( k - 1 ) distinct digits ( for a given m ) and just use them 
   *    to find numbers with (k) distinct digits. Otherwise, numbers would
   *    have to be regenerated all the way to the base case for a given (m).
   */

  for(unsigned int m = 1; m <= m_itrs; m++)
  {
    c.SetM( m );

    for(unsigned int k = 1; k <= m && k <= k_itrs; k++)
    {
      c.SetK( k );

      std::cout << "m[ " << m << " ] k[ " << k << " ]\n";

      #ifdef TIME
        timer.start();
      #endif

        std::deque< Number > numbers = c.GetNumbers();

      #ifdef TIME
        timer.stop();

        runs++;

        if( timer.getCPUCurrSecs() > maxTrialTime )
        {
          maxM = m;
          maxK = k;
          maxTrialTime = timer.getCPUCurrSecs();
        }
      #endif

      std::deque< Number >::iterator itr;

      for(itr = numbers.begin(); itr != numbers.end(); ++itr)
        std::cout << "\t" << itr->ToString() << std::endl;

      std::cout << "\n";
    }    
  }

  #ifdef TIME
    std::cout << "\nTotal time: " << timer.getCPUTotalSecs() << "s" << std::endl;
    std::cout << "Avg. time : " << timer.getCPUTotalSecs()/runs << "s" << std::endl;
    std::cout << "Max. trial time ( m[" << maxM << "] k[" << maxK << "] ) : " << maxTrialTime << "s" << std::endl;
  #endif


  return 0;
}

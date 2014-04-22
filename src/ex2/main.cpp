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
  unsigned int m_beg = 1 , m_end = 15,
               k_beg = 1 , k_end = 5  ;  

  #ifdef TIME
    CPUTimer timer;
    unsigned int runs = 0;
    unsigned int maxM , maxK ; /* remember m and k for largest time */
    double maxTrialTime = 0.0;
  #endif

  if( argc >= 5 )
  { 
    m_beg = atoi( argv[1] );
    m_end = atoi( argv[2] );

    k_beg = atoi( argv[3] );
    k_end = atoi( argv[4] );
  }

  /* 
   *  Reuse the same object so that the algorithm can remember numbers
   *    with ( k - 1 ) distinct digits ( for a given m ) and just use them 
   *    to find numbers with (k) distinct digits. Otherwise, numbers would
   *    have to be regenerated all the way to the base case for a given (m).
   */

  for(unsigned int m = m_beg; m <= m_end; m++)
  {
    c.SetM( m );

    for(unsigned int k = k_beg; k <= m && k <= k_end; k++)
    {
      c.SetK( k );

      std::cout << "m[ " << m << " ] k[ " << k << " ]\n";

      #ifdef TIME
        timer.start();
      #endif

        std::deque< Number > numbers = c.GetNumbers();

      #ifdef TIME
        timer.stop();
      #endif

      std::cout << "\t#numbers: " << numbers.size() << std::endl;  

      #ifdef TIME
        if( timer.getCPUCurrSecs() > 0.0 )
          runs++;

        std::cout << "\tTrial time: " << timer.getCPUCurrSecs() << "s" << std::endl;

        if( timer.getCPUCurrSecs() > maxTrialTime )
        {
          maxM = m;
          maxK = k;
          maxTrialTime = timer.getCPUCurrSecs();
        }
      #endif

      #ifdef SHOW_NUMBERS
        std::deque< Number >::iterator itr;

        for(itr = numbers.begin(); itr != numbers.end(); ++itr)
          std::cout << "\t" << itr->ToString() << std::endl;

        std::cout << "\n";
      #endif
    }    
  }

  #ifdef TIME
    runs = (( runs == 0 ) ? 1 : runs );

    std::cout << "\nTotal time: " << timer.getCPUTotalSecs() << "s" << std::endl;
    std::cout << "Avg. time ( without 0s ) : " << timer.getCPUTotalSecs()/runs << "s" << std::endl;
    std::cout << "Max. trial time ( m[" << maxM << "] k[" << maxK << "] ) : " << maxTrialTime << "s" << std::endl;
  #endif


  return 0;
}

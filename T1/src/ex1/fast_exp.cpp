#include "fast_exp.h"

Exponentiation::Exponentiation( long x ) 
{
  baseValue = x;

  memoize.push_back( 1 ) ; // x^0 = 1
}

mpz_class Exponentiation::PowerOf( unsigned long k ) 
{
  unsigned long largestPower = memoize.size() - 1;
  mpz_class last = memoize[ largestPower ] ;

  for( ; largestPower <= k ; largestPower++ )
  {
    last *= baseValue ;
    
    memoize.push_back( last ) ;
  }

  return memoize[ k ];
}

void Exponentiation::SetBaseValue( long newX )
{
  baseValue = newX ;

  memoize.erase( memoize.begin() + 1 , memoize.end() ) ;
}

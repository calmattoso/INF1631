#include "fast_exp.h"

Exponentiation::Exponentiation( long long x ) 
{
  baseValue = x;

  memoize.push_back( 1 ) ; // x^0 = 1
}

long long Exponentiation::PowerOf( unsigned long long k ) 
{
  unsigned long long largestPower = memoize.size() - 1;
  long long last = memoize[ largestPower ] ;

  for( ; largestPower <= k ; largestPower++ )
  {
    last *= baseValue ;
    
    memoize.push_back( last ) ;
  }

  return memoize[ k ];
}

void Exponentiation::SetBaseValue( long long newX )
{
  baseValue = newX ;

  memoize.erase( memoize.begin() + 1 , memoize.end() ) ;
}
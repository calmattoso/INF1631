#ifndef FAST_EXP_H
#define FAST_EXP_H

#include <vector>

class Exponentiation 
{
private:
  /* The base value whole powers we're trying to calculate */
  long long baseValue ;

  /* Store all powers of baseValue up to ( memoize.size() - 1 ) */ 
  std::vector< long long > memoize ;

public:

  Exponentiation( long long ) ;

  long long PowerOf( unsigned long long ) ;

  void SetBaseValue( long long ) ;

};

#endif

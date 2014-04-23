#ifndef FAST_EXP_H
#define FAST_EXP_H

#include <vector>
#include <gmpxx.h>

class Exponentiation 
{
private:
  /* The base value whole powers we're trying to calculate */
  mpz_class baseValue ;

  /* Store all powers of baseValue up to ( memoize.size() - 1 ) */ 
  std::vector< mpz_class > memoize ;

public:

  Exponentiation( long ) ;

  mpz_class PowerOf( unsigned long ) ;

  void SetBaseValue( long ) ;

};

#endif

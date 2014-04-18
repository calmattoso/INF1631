#ifndef QUOCIENTE_H
#define QUOCIENTE_H

#include <vector>
#include <gmpxx.h>
#include "fast_exp.h"

class Quociente 
{
private:

  Exponentiation exp;

  mpz_class x , y ;

  /* Array of previously seen quocients */
  std::vector< mpz_class > q;

  unsigned int largestK;

public:

  Quociente( long , long );

  mpz_class FindFor( unsigned long );

  void SetX( long ) ;

  void SetY( long ) ;

};

#endif

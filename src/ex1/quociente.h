#ifndef QUOCIENTE_H
#define QUOCIENTE_H

#include <vector>
#include "fast_exp.h"

class Quociente 
{
private:

  Exponentiation exp;

  long long x , y ;

  /* Array of previously seen quocients */
  std::vector<long long> q;

  unsigned int largestK;

public:

  Quociente( long long , long long );

  long long FindFor( unsigned long long );

  void SetX( long long ) ;

  void SetY( long long ) ;

};

#endif

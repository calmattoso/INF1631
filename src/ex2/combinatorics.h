#ifndef COMBINATORICS_H
#define COMBINATORICS_H

#include <string>
#include <list>
#include <deque>

#include "number.h"

typedef unsigned long ull;

class Combinatorics
{
private:
/* DATA */
  std::deque< Number > numbers;
  std::deque< std::string > digits ;

  ull k, m;

/* HELPERS */

  void GenerateDigits( ) ;

  void GenerateNumbers( ull , ull ) ;

public:

  Combinatorics( ull , ull );

  std::deque< Number > GetNumbers();

/* RECONFIGURE */
  void SetK( ull );

  void SetM( ull );

};

#endif

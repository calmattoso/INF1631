#ifndef COMBINATORICS_H
#define COMBINATORICS_H

#include <string>
#include <list>
#include <vector>

typedef unsigned long ull;

class Combinatorics
{
private:
/* DATA */
  std::list< std::string > numbers;
  std::vector< std::string > digits ;

  ull k, m;

/* UTILS */
  ull expt( ull , ull );

/* HELPERS */
  void ResizeNumbers();

  std::list< std::string > GenerateDigits( ) ;

  std::list< std::string > GenerateNumbers( ull , ull ) ;

public:

  Combinatorics( ull , ull );

  std::list< std::string > GetNumbers();

/* RECONFIGURE */
  void SetK( ull );

  void SetM( ull );

};

#endif

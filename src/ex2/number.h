#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include <set>

typedef std::pair< std::string , int > DigitAtPos ;

class Number {
private:
  
  static bool CompareDigits (  DigitAtPos , DigitAtPos ) ;

  /* Red black tree of digit and index in number ( assures fast digit detection ) */
  std::set< DigitAtPos , bool(*)( DigitAtPos , DigitAtPos ) > tree ;

public:

  Number( const Number& );
  Number( std::string digit = "" );

  void AppendDigit( std::string );

  bool HasDigit( std::string );

  unsigned int GetLength();

  std::string ToString( ) ;

};

#endif

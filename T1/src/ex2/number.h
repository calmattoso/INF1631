#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include <set>

/*                   digit       ,  index in #  */
typedef std::pair< unsigned int , unsigned int > DigitAtPos ;

class Number {
private:

/* CLASS MEMBERS */ 

  static const unsigned int NUMBER_MAX_LEN = 10;
  
  static bool CompareDigits (  DigitAtPos , DigitAtPos ) ;

/* INSTANCE ATTRIBUTES */

  /* Red black tree of digit and index in number ( assures fast digit detection ) */
  
  std::set< DigitAtPos , bool(*)( DigitAtPos , DigitAtPos ) > tree ;
  
  unsigned long maxLen;

public:

  Number( const Number& , unsigned int newMaxLen = 0 );
  Number( unsigned int digit = 0 , unsigned int maxLen = NUMBER_MAX_LEN  );

  bool AppendDigit( unsigned int );

  bool HasDigit( unsigned int );

  unsigned int GetLength();

  std::string ToString( ) ;

};

#endif

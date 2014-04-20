#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include <set>

#include "../lib/BloomFilter/bloom_filter.hpp"

typedef std::pair< std::string , int > DigitAtPos ;

class Number {
private:

/* CLASS MEMBERS */ 

  static const unsigned int NUMBER_MAX_LEN = 10;
  
  static bool CompareDigits (  DigitAtPos , DigitAtPos ) ;

/* INSTANCE ATTRIBUTES */

  /* Red black tree of digit and index in number ( assures fast digit detection ) */
  
  std::set< DigitAtPos , bool(*)( DigitAtPos , DigitAtPos ) > tree ;
  
  unsigned long maxLen;


  bloom_filter filter ;

/* HELPER */

  void SetUpFilter( unsigned int projectedCount = NUMBER_MAX_LEN ,
                    double falsePositiveRate = 0.01 ) ;

public:

  Number( const Number& , unsigned int newMaxLen = 0 );
  Number( std::string digit = "" , unsigned int maxLen = NUMBER_MAX_LEN  );

  bool AppendDigit( std::string );

  bool HasDigit( std::string );

  unsigned int GetLength();

  std::string ToString( ) ;

};

#endif

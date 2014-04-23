#include "number.h"

#include <deque>
#include <iostream>
#include <sstream>

/* Red black tree of digit and index in number ( assures fast digit detection ) */

Number::Number( const Number& copy , unsigned int newMaxLen )
{
  this->tree = copy.tree;
  this->maxLen = ( ( newMaxLen == 0 ) ? copy.maxLen : newMaxLen ) ;
}

Number::Number( unsigned int digit , unsigned int maxLen ) : 
  tree( Number::CompareDigits )
{
  this->maxLen = maxLen ;

  if( digit > 0 )
    AppendDigit( digit );
}

bool Number::CompareDigits (  DigitAtPos lhs , DigitAtPos rhs ) 
{
  return lhs.first < rhs.first ;
}

bool Number::AppendDigit( unsigned int digit )
{
  unsigned int length = tree.size() + 1 ;

  if( length > maxLen )
    return false ;

  DigitAtPos last = std::make_pair( digit , length );
  tree.insert( last );

  return true;
}

bool Number::HasDigit( unsigned int digit )
{
  DigitAtPos d = std::make_pair( digit , 0 );

  /* The digit might be in the number, so look it up in the tree */
  return ( ( tree.find( d ) != tree.end() ) ? true : false );
}

unsigned int Number::GetLength()
{
  return tree.size();
}

std::string Number::ToString( )
{
  std::string output = "";

  std::deque<std::string> pieces( tree.size() , "" );
  std::deque<std::string>::iterator piece;

  std::set< DigitAtPos , bool(*)( DigitAtPos , DigitAtPos ) >::iterator digit;

  /* Gather each digit and store them at its respective index in (pieces) */
    for( digit = tree.begin() ; digit != tree.end() ; ++digit )
    {
      std::stringstream intToString;
      intToString << digit->first;

      pieces[ digit->second - 1 ] = intToString.str();
    }

  /* Transform (pieces) into a formatted string */
    for( piece = pieces.begin(); piece != pieces.end() ; ++piece )
    {
      output
        .append( "[" )
        .append( *piece )
        .append( "]");
    }

  return output;
}


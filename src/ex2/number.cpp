#include "number.h"

/* Red black tree of digit and index in number ( assures fast digit detection ) */

bool Number::CompareDigits (  DigitAtPos lhs , DigitAtPos rhs ) 
{
  return lhs.first < rhs.first ;
}

Number::Number( const Number& copy )
{
  this->tree = copy.tree;
}

Number::Number( std::string digit ) : 
  tree( Number::CompareDigits )
{
  if( !digit.empty() )
    AppendDigit( digit );
}


void Number::AppendDigit( std::string  digit )
{
  DigitAtPos last = make_pair( digit , tree.size() + 1 );
}

bool Number::HasDigit( std::string digit )
{
  DigitAtPos d = make_pair( digit , 0 );
  return ( ( tree.find( d ) != tree.end() ) ? true : false );
}

unsigned int Number::GetLength()
{
  return tree.size();
}

std::string Number::ToString( )
{
  std::string output = "";
  std::set< DigitAtPos , bool(*)( DigitAtPos , DigitAtPos ) >::iterator itr;

  for( itr = tree.begin() ; itr != tree.end() ; ++itr )
  {
    output
      .append( "[" )
      .append( itr->first )
      .append( "]" );
  }

  return output;
}


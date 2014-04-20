#include "number.h"

#include <deque>
#include <iostream>

/* Red black tree of digit and index in number ( assures fast digit detection ) */

Number::Number( const Number& copy , unsigned int newMaxLen )
{
  this->tree = copy.tree;
  this->maxLen = ( ( newMaxLen == 0 ) ? copy.maxLen : newMaxLen ) ;
}

Number::Number( std::string digit , unsigned int maxLen ) : 
  tree( Number::CompareDigits )
{
  this->maxLen = maxLen ;

  if( !digit.empty() )
    AppendDigit( digit );

  //SetUpFilter( this->maxLen );
}

bool Number::CompareDigits (  DigitAtPos lhs , DigitAtPos rhs ) 
{
  return lhs.first < rhs.first ;
}

/*
void Number::SetUpFilter( unsigned int projectedCount ,
                          double falsePositiveRate )
{
  bloom_parameters parameters;

  // How many elements roughly do we expect to insert?
  parameters.projected_element_count = projectedCount ;

  // Maximum tolerable false positive probability? (0,1)
  parameters.false_positive_probability = falsePositiveRate ; 

  if (!parameters)
  {
    std::cout << "Error in filter parameters." << std::endl;
    exit(1);
  }

  parameters.compute_optimal_parameters();

  this->filter = bloom_filter( parameters ) ;
}
*/

bool Number::AppendDigit( std::string  digit )
{
  unsigned int length = tree.size() + 1 ;

  if( length > maxLen )
    return false ;

  DigitAtPos last = make_pair( digit , length );
  tree.insert( last );

  return true;
}

bool Number::HasDigit( std::string digit )
{
  DigitAtPos d = make_pair( digit , 0 );


  /* Bloom (filter) tells us (digit) is **certainly not** in (number) 
  if( !filter.contains( digit ) )
    return false;*/

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
      pieces[ digit->second - 1 ] = digit->first;

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


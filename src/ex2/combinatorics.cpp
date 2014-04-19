#include "combinatorics.h"

#include <sstream>

/* UTILS */
ull Combinatorics::expt( ull p, ull q)
{
  ull r = 1;

  while (q != 0) {
      if (q % 2 == 1) {    // q is odd
          r *= p;
          q--;
      }
      p *= p;
      q /= 2;
  }

  return r;
}

Combinatorics::Combinatorics( ull _k , ull _m ) 
{
  k = _k;
  m = _m;

  /* Overestimate the length of array of numbers, 
       and create those positions */
    ResizeNumbers();

  /* Generate digits */
    GenerateDigits();
}

void Combinatorics::ResizeNumbers()
{
  ull estimatedSize = expt( m , k );
  numbers.resize( estimatedSize , "" );
}

std::list< std::string > Combinatorics::GenerateDigits( )
{
  ull start = digits.size();

  digits.resize( m , "" );

  for( ull i = start ; i < m ; ++i )
  {
    std::stringstream ss;
    ss << i + 1;

    digits[i] = ss.str();
  }
}

std::list< std::string > Combinatorics::GenerateNumbers( ull n , ull m )
{
  /*
   * Caso Base
   * =========
   *
   *  Com 0 dígitos, é possível apenas o vetor vazio. 
   *  Com 1 dígito, teremos (m) números, cada um formato por um
   *    dígito distinto dos (m) possíveis.
   *
   */
    if( n == 0 )
      return std::list< std::string >();
    if( n == 1 )
      return std::list< std::string >(digits.begin(), digits.end());

  /*
   * Passo Indutivo
   * ==============
   *
   *  Queremos obter os números de (n) dígitos distintos, sendo (m) possíveis.
   *  Para cada número de (n - 1) dígitos obtidos até o momento, basta que
   *    separemos tais números segundos quais dígitos eles **não tem**. Assim
   *    teremos diferentes conjuntos dos quais fazem parte os números sem 1,
   *    sem 2, ..., sem m.
   *  Feito isso, para obtermos o conjunto dos números de (n) dígitos, basta 
   *    adicionarmos ao final de cada número de cada conjunto gerado acima o
   *    respectivo dígito de tal conjunto. Por exemplo, no conjunto dos números
   *    de (n - 1) dígitos que não tem (1), adicionamos (1) ao final de cada um
   *    deles. Fazendo isto para todos os conjuntos teremos todos os números de 
   *    (n) dígitos.
   *  Como temos que saber de (n-1) utilizamos recursão, andando para trás até
   *    atingir-se o caso base.
   *
   */

    /* Obtém E{n-1, m} */
    numbers = GenerateNumbers( n - 1 , m );

    /* 
     * Passa por cada número e verifica em quais dos conjuntos 
     *   descritos acima ele entraria, imediatamente adicionando
     *   o novo dígito ao final e introduzindo este novo número
     *   no vetor de números 
     */
    ull originalSize = numbers.size();
    for(std::list<std::string>::iterator it = numbers.begin() ;
        it != numbers.end() ; ++it )
    {
      std::string number = (*it);

      for(ull digit = 0; digit < m; digit++ )
      {
        std::size_t found = number.find( digits[ digit ] );
        
        /* O número (number) não tem o dígito ( digits[digit] ) */
        if (found == std::string::npos)
        {
          std::stringstream newNumber;
          newNumber << number << digit;
          numbers.push_back( newNumber.str() ) ;
        }
      }
    }

    /* Remove os números que tinham apenas (n - 1) dígitos */
    std::list<std::string>::iterator itrEnd = numbers.begin();
    advance( itrEnd , originalSize ) ;
    numbers.erase( numbers.begin(), itrEnd );

    /* return E{n,m} */
    return numbers;
}

std::list< std::string > Combinatorics::GetNumbers(){
  return GenerateNumbers( k , m );
}

void Combinatorics::SetK( ull _k ){
  k = _k;

  ResizeNumbers();
}

void Combinatorics::SetM( ull newM ){
  m = newM ;

  GenerateDigits();

  ResizeNumbers();
}



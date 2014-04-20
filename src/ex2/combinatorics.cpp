#include "combinatorics.h"

#include <sstream>
#include <iostream>


Combinatorics::Combinatorics() :
  k( 0 ),
  m( 9 )
{
  GenerateDigits();
}

Combinatorics::Combinatorics( ull _k , ull _m ) 
{
  k = _k;
  m = _m;

  /* Generate digits */
    GenerateDigits();
}

void Combinatorics::GenerateDigits( )
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

/* 
 *  O "retorno" é feito colocando-se no atributo (numbers) o resultado de cada
 *    passo do algoritmo 
 */
void Combinatorics::GenerateNumbers( ull n , ull m )
{
  /*
   * Caso Base
   * =========
   *
   *  Com 0 dígitos, é possível apenas o vetor vazio. Assim, basta
   *    esvaziar (numbers).
   */
    if( n == 0 )
    {
      numbers.clear();
      return;
    }

  /*
   *  Com 1 dígito, teremos (m) números, cada um formato por um
   *    dígito distinto dos (m) possíveis.
   */
    if( n == 1 )
    {
      for( ull digitIdx = 0 ; digitIdx < m ; digitIdx++ )
      {
        Number digitNumber( digits[ digitIdx ] , n );
        numbers.push_back( digitNumber );
      }

      return;
    }

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
   * !!! OBS !!!
   * -----------
   *  Para fins de otimização, esta função ao invés de retornar o vetor com 
   *    números de (n) dígitos simplesmente os salva no atributo (numbers).
   *    Essencialmente, ao alterarmos (numbers) seguindo o algoritmo é como
   *    se um retorno fosse feito.
   *
   */

    /* 
     * Obtém E{n-1, m}
     * ===============
     *  Apenas geramos números com (n-1) dígitos, caso já não os tenhamos
     *    armazenados em (numbers).
     */
      if( numbers.empty() || !numbers.empty() && numbers[0].GetLength() < (n-1) )
        GenerateNumbers( n - 1 , m ) ;

    /* 
     * Passa por cada número e verifica em quais dos conjuntos 
     *   descritos acima ele entraria, imediatamente adicionando
     *   o novo dígito ao final e introduzindo este novo número
     *   no vetor de números. 
     */
      std::deque< Number > newNumbers;

      for(std::deque< Number >::iterator it = numbers.begin() ;
          it != numbers.end() ; ++it )
      {
        Number number = (*it);

        /* 
          Checa para cada dígito se o número atual o contém 
            [ segmentação em E^d{i}{ n-1 , m } ] 
        */
          for(ull digit = 0; digit < m; digit++ )
          {
            /* 
              O número (number) não tem o dígito ( digits[digit] ),
                logo, o adicionamos ao final
                [ etada de concatenação do passo indutivo ] 
            */
              if ( !number.HasDigit( digits[ digit ] ) )
              {
                Number newNumber( number , number.GetLength() + 1 );
                newNumber.AppendDigit( digits[ digit ] );

                newNumbers.push_back( newNumber ) ;
              }
          }
      }

    /* Coloca em numbers os novos números gerados */
      numbers.assign( newNumbers.begin() , newNumbers.end() );

    /* Ao final temos E{n,m} em (numbers), como desejado.  */
}

std::deque< Number > Combinatorics::GetNumbers(){
  GenerateNumbers( k , m );

  return this->numbers ;
}

void Combinatorics::SetK( ull newK ){
  /* 
    numbers should only be cleared if (k) is decreased. If (newK) is 
      at least as large as (k), we should keep the numbers of (k) digits
      already generated so GenerateNumbers can make use of them.
  */
  if( newK < k )
    numbers.clear();

  k = newK;
}

void Combinatorics::SetM( ull newM ){
  m = newM ;

  GenerateDigits();

  numbers.clear();
}



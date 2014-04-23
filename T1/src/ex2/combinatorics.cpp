#include "combinatorics.h"

#include <sstream>
#include <iostream>


Combinatorics::Combinatorics() :
  k( 0 ), m( 9 )
{}

Combinatorics::Combinatorics( ull _k , ull _m ) 
{
  k = _k;
  m = _m;
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
   *    esvaziar (numbers). O algoritmo contudo nunca chega neste 
   *    ponto, a não ser que (n) inicial (da primeira chamada) já
   *    seja 0. [ caso degenerado ]
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
      for( unsigned int digit = 1 ; digit <= m ; ++digit )
      {
        Number digitNumber( digit , n );
        numbers.push_back( digit );
      }

      return;
    }

  /*
   * Passo Indutivo
   * ==============
   *
   *  Queremos obter os números de (n) dígitos distintos, sendo (m) possíveis.
   *  Para cada número de (n - 1) dígitos obtidos até o momento, basta que
   *    separemos tais números segundo quais dígitos eles **não tem**. Assim
   *    teremos diferentes conjuntos dos quais fazem parte os números sem 1,
   *    sem 2, ..., sem m.
   *  Feito isso, para obtermos o conjunto dos números de (n) dígitos, basta 
   *    adicionarmos ao final de cada número de cada conjunto gerado acima o
   *    respectivo dígito que não existe em tal conjunto. Por exemplo, no 
   *    conjunto dos números de (n - 1) dígitos que não tem (1), adicionamos
   *    (1) ao final de cada um deles. Fazendo isto para todos os conjuntos
   *    teremos todos os números de (n) dígitos.
   *  Como temos que saber de (n-1) utilizamos recursão, andando para trás até
   *    atingir-se o caso base.
   * !!! OBS !!!
   * -----------
   *  Para fins de otimização, esta função ao invés de retornar o vetor com 
   *    números de (n) dígitos simplesmente os salva no atributo (numbers).
   *    Essencialmente, ao alterarmos (numbers) seguindo o algoritmo é como
   *    se um retorno fosse feito ao final da função.
   *
   */

    /* 
     * Obtém E{n-1, m}
     * ===============
     *  Apenas geramos números com (n-1) dígitos, caso já não os tenhamos
     *    armazenados em (numbers).
     */
      if( numbers.empty() || numbers[0].GetLength() < (n-1) )
        GenerateNumbers( n - 1 , m ) ;

    /* 
     * Passa por cada número e verifica em quais dos conjuntos 
     *   descritos acima ele entraria, imediatamente adicionando
     *   o novo dígito ao final e introduzindo este novo número
     *   no vetor de números. 
     */
      

      std::deque<Number>::size_type len = numbers.size();
      for(std::deque<Number>::size_type i = 0 ; i < len ; ++i )
      {
        Number number = numbers[ i ];

        /* 
          Checa para cada dígito se o número atual o contém 
            [ segmentação em E^d{i}{ n-1 , m } ] 
        */
          for( unsigned int digit = 1 ; digit <= m ; ++digit )
          {
            /* 
              O número (number) não tem o dígito (digit),
                logo, o adicionamos ao final
                [ etada de concatenação do passo indutivo ] 
            */
              if ( !number.HasDigit( digit ))
              {
                Number newNumber( number , number.GetLength() + 1 );
                newNumber.AppendDigit( digit );

                /*
                  Imediatamente adiciona-se o número ao vetor que é
                   "retornado". 
                 */
                numbers.push_back( newNumber ) ;
              }
          }
      }

    /* Remove os números de n-1 dígitos que tínhamos em (numbers).
       Otimização em termos de implementação para que não seja 
         necessário gerar vários conjuntos de números que teriam que
         ser copiados e deletados.  */
      numbers.erase( numbers.begin() , numbers.begin() + len );

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

  /*
    There's nothing we can do if (m) is changed, so we purge the list
      of numbers. Everything has to be regenerated.
  */
  if( m != newM )
    numbers.clear();

  m = newM ;
}



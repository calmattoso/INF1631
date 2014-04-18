#include "quociente.h"

#define MAX(a,b) ((a>b)?a:b)

Quociente::Quociente( long x , long y ) :
  exp( x ), q( 1000 , 0 )
{
  this->x = x;
  this->y = y;

  q[ 1 ] = 1 ;
  largestK = 1 ;
}


mpz_class Quociente::FindFor( unsigned long k ) 
{
  
  /* Hack para deixar o algoritmo mais direto. */
  if( q.size() >= q.capacity() - 2 )
    q.resize( q.size() * 1.5 , 0 );

  /*
   * Caso Base
   * =========
   *   ( x^1 - y^1 )/(x - y) = 1
   */

    if( k == 1 )
      return 1;

  /* Passo Indutivo
   * ==============
   *  Da prova apresentada sabemos que:
   *   
   *    Quociente( k ) = [ x ^ (k - 1) ] + y * Quociente( k ) 
   *
   *  exp é uma variável que internamente salva os valores de x^k
   *    conforme são calculados para acelerar o processo. Assim,
   *    a chamada a PowerOf retorna x^(k-1).
   *  Além disso, é feita uma pequena otimização. Lembram-se os valores
   *    de Quociente[ k ], para todo k. Assim, em uma chamada futura,
   *    caso Quociente[ k - 1 ] já tenha sido calculado, basta usá-lo na
   *    conta diretamente. Caso contrário, segue-se a recursão para obter
   *    os valores que faltam.
   */

    else
    {
      /* Calcula x^( k - 1 ) */
      q[ k ] = exp.PowerOf( k - 1 ) ;

      /* Caso [k - 1] já tenha sido calculado */
      if( largestK >= ( k - 1 ) )
        q[ k ] += y * q[ k - 1 ] ;
      /* cc, temos que descobrir quanto é k - 1 */
      else
        q[ k ] += y * FindFor( k - 1 );
      
      largestK = MAX( largestK , k ) ;

      return q[ k ];
    }
}

void Quociente::SetX( long newX ) 
{
  x = newX;

  exp.SetBaseValue( newX ) ;

  q.erase( q.begin() + 2 , q.end() ) ;
}

void Quociente::SetY( long newY )
{
  y = newY ;

  q.erase( q.begin() + 2 , q.end() ) ;
}


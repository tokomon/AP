#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <sys/time.h>


float sum = 0.0,pi_approx;
int thread_count=4;//omp_get_num_threads();
int k,n;
double factor = 1.0;
n=1000000;

int main(int argc, char const *argv[])
{

#pragma omp parallel for num_threads(thread_count) \
default(none) reduction(+:sum) private(k, factor) \
shared(n)
  for (k = 0; k < n; k++) {
      if (k % 2 == 0)
        factor = 1.0;
      else
        factor = - 1.0;
  sum = sum + factor/(2*k+1);
  }
pi_approx = 4.0*sum;

  printf("\n");
  printf("sum %f\n",pi_approx);


  /*
  double factor = 1.0;
  double sum = 0.0;
  #pragma omp parallel for num_threads(thread_count) \
  reduction(+:sum)
  for (k = 0; k < n; k++) {
  sum += factor/(2*k+1);
  factor = - factor;
  }
  pi_approx = 4.0*sum;
  printf("sum %f\n",pi_approx);

  */

/**
Suma es una variable de reducción (que tiene propiedades de ámbito
privado y compartido).
Factor y k deben tener alcance privado.
Las variables que nunca se actualizan en paralelo o paralelo
para el bloque, como n en este ejemplo, se pueden compartir de
forma segura.

Recuerde que a diferencia de las variables privadas,
las variables compartidas tienen el mismo valor en el paralelo
o paralelo para el bloque que tenían antes del bloque, y su valor
después del bloque es el mismo que su último valor en el bloque.
Por lo tanto, si n se inicializó antes del bloque a 1000,
conservaría este valor en la instrucción parallel for y,
dado que el valor no se cambia en el ciclo for, mantendría
este valor después de que el ciclo se haya completado.
*/

}

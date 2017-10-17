#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <sys/time.h>


int thread_count=4;
int     i, j;
double* A;
double* x;
double* y;
long m,n;


void Gen_vector(double x[], int n) {
   int i;

   for (i = 0; i < n; i++)
      x[i] = random()/((double) RAND_MAX);
}
void Gen_matrix(double A[], int m, int n) {
   int i, j;
   for (i = 0; i < m; i++)
      for (j = 0; j < n; j++)
         A[i*n+j] = random()/((double) RAND_MAX);
}

void Print_matrix( char* title, double A[], int m, int n) {
   int   i, j;

   printf("%s\n", title);
   for (i = 0; i < m; i++) {
      for (j = 0; j < n; j++)
         printf("%6.3f ", A[i*n + j]);
      printf("\n");
   }
}

void Print_vector(char* title, double y[], double m) {
   int   i;

   printf("%s\n", title);
   for (i = 0; i < m; i++)
      printf("%6.3f ", y[i]);
   printf("\n");
}


int main(int argc, char* argv[]) {
   double tiempo;
  //struct timeval begin, end;
  tiempo=0.0;


   m = 8;
   n = 8000000;
   A = malloc(m*n*sizeof(double));
   x = malloc(n*sizeof(double));
   y = malloc(m*sizeof(double));
   srandom(1);
  Gen_matrix(A, m, n);
  //Print_matrix("matrix: ", A, m, n);

  Gen_vector(x, n);
//  Print_vector("vector: ", x, n);

  struct timeval begin, end;

  double tiI,tiF;
  tiI=omp_get_wtime();//captura de tiempo inicial
  gettimeofday(&begin, NULL);


# pragma omp parallel for num_threads(thread_count) \
default(none) private(i, j) shared(A, x, y, m, n)
for (i = 0; i < m; i++) {
y[i] = 0.0;
for (j = 0; j < n; j++)
y[i] += A[i*n+j]*x[j];
}

gettimeofday(&end, NULL);
tiempo=tiempo+(((end.tv_sec - begin.tv_sec) * 1000000u + end.tv_usec - begin.tv_usec) / 1.e6);

tiF=omp_get_wtime();//tiempo final
printf("tiempo for : %f\n",tiF-tiI);


printf("\n");
printf("tiempo %f\n",tiempo);


}

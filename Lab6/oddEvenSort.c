#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <sys/time.h>

int thread_count=1;//omp_get_num_threads();

void odd_even_sort(int a[],int n){
	int phase,i,tmp;
	//int my_rank=omp_get_thread_num();

	for (phase = 0; phase < n; phase++) {
		if(phase % 2 == 0)
	#pragma omp parallel for num_threads(thread_count)\
		      default(none) shared(a,n) private(i,tmp)
			for (i = 1; i < n; i+= 2) {
				if(a[i-1]>a[i]) {
					tmp=a[i-1];
					a[i-1]=a[i];
					a[i]=tmp;
				}
			}
		else
	#pragma omp parallel for num_threads(thread_count)\
		    default(none) shared(a, n) private(i,tmp)
		for(i=1;i<n-1;i+=2){
			if(a[i]>a[i+1]){
				tmp=a[i+1];
				a[i+1]=a[i];
				a[i]=tmp;
			}
		}
    }
}
void odd_even_sort2(int a[],int n){
		int phase,i,tmp;
		//int my_rank=omp_get_thread_num();

	#   pragma omp parallel num_threads(thread_count)\
		     default(none) shared(a,n)private(i,tmp,phase)

		for (phase = 0; phase < n; phase++) {
			if(phase % 2 == 0)
	  #pragma omp for
				for (i = 1; i < n; i+= 2) {
					if(a[i-1]>a[i]) {
						tmp=a[i-1];
						a[i-1]=a[i];
						a[i]=tmp;
					}
				}
			else
			#	pragma omp for
				for(i=1;i<n-1;i+=2){
					if(a[i]>a[i+1]){
						tmp=a[i+1];
						a[i+1]=a[i];
						a[i]=tmp;
					}
				}

	    }
}

int main(int argc, char const *argv[])
{   int n=20000;//la prueba con 20 000 elementos
    int a[n];
    double tiempo;
    //struct timeval begin, end;
    tiempo=0.0;

    for(int j=0;j<n;j++)// para llenar el array
	   {
		    a[j]=rand();
	    }

		double tiI,tiF;
  	struct timeval begin, end;
		tiI=omp_get_wtime();
		odd_even_sort(a,n);
		tiF=omp_get_wtime();
		tiempo=(tiF-tiI);

    printf("tiempo : %f\n",tiempo);


	return 0;

}



/*
#include <stdio.h>
#include <stdlib.h>

void Bubble_sort(int a[], int n){
  int list_length, i, tmp;
  for(list_length = n; list_length >= 2; list_length--)
    for(i = 0; i < list_length-1; i++)
      if(a[i] > a[i+1]){
			tmp = a[i];
			a[i] = a[i+1];
			a[i+1] = tmp;
      }
}

int main(){
  int n, *A, i;
  scanf("%d", &n);
  A =  malloc(n*sizeof(int));
  for(i = 0; i < n; i++) scanf("%d", &A[i]);
  Bubble_sort(A,n);
  for(i = 0; i < n; i++) printf("%d ", A[i]);
  printf("\n");
  return 0;
}


*/

#include <stdio.h>
#include <iostream>
#include <stdio.h> 
#include <sys/time.h> //gettimeofday()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std;

long long  MAX=100;

float A[500][500],B[500][500],C[500][500];


int multiplicarmtz(int m,int n, int f, int   c)
{
  int i,j,k;
      float time_spent;

/*  m=3;
  n=3;
  f=3;
  c=3;*/

  if (n==f)
  {
    //cout<<"INGRESE EL VALOR DE LA PRIMERA MATRIZ"<<endl;
    //INGRESE LAS MATRICES
    for (i=1;i<=m;i++)
     for (j=1;j<=n;j++)
    {/* printf("A(%d,%d)= ",i,j);
       scanf ("%f",&A[i][j]);*/
      A[i][j]=j;
    }
     
    //INGRESE EL VALOR DE LA SEGUNDA MATRIZ
      for (i=1;i<=f;i++)
       for (j=1;j<=c;j++)
        { /*printf("B(%d,%d)= ",i,j);
          scanf ("%f",&B[i][j]);*/
        B[i][j]=j;
        }


  clock_t begin = clock();
    //OPERACION DE MULTIPLICACION
     for (i=1;i<=m;i++)
        {for (j=1;j<=c;j++)
           { C[i][j]=0;
             for (k=1;k<=n;k++)
              {C[i][j]=C[i][j]+A[i][k]*B[k][j];
              }
           }
        }

         clock_t end = clock();
  time_spent = (double)(end-begin) /CLOCKS_PER_SEC;
  printf("%f\n", time_spent);/*

     printf("\n---------------------------------------------------\n");
     printf("\nLA MULTIPLICACION DE LAS MATRICES ES:\n\n");
    //IMPRESION
      for (i=1;i<=m;i++)
       for (j=1;j<=c;j++)
        { printf("C(%d,%d)=\t%4.2f\n",i,j,C[i][j]);
        }*/


  }
  else
  {
    cout<<"Estas matrices no se pueden multiplicar";
    
  }

}

int main(int argc, char const *argv[])
{
  /* code */
  



  struct timeval comienzo, final;

  gettimeofday(&comienzo, NULL);



  multiplicarmtz(MAX,MAX,MAX,MAX);

 



  gettimeofday(&final, NULL);

  printf("\nComienzo: %.3f s\n", comienzo.tv_sec+(float)comienzo.tv_usec/1000000);
  printf("Final: %.3f s\n", final.tv_sec+(float)final.tv_usec/1000000);
  printf("\nDuración del programa: %.3f s\n\n", (final.tv_sec+(float)final.tv_usec/1000000)-(comienzo.tv_sec+(float)comienzo.tv_usec/1000000));
  
  return 0;
}



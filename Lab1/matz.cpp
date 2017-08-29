#include <stdio.h>
#include <iostream>
#include <time.h> 
#include <stdio.h> 
#include <sys/time.h> //gettimeofday()


using namespace std;
int multiplicarmtz(int m,int n, int f, int   c)
{
  int i,j,k;
  
float A[100][100],B[100][100],C[100][100];
/*  m=3;
  n=3;
  f=3;
  c=3;*/

  if (n==f)
  {
    cout<<"INGRESE EL VALOR DE LA PRIMERA MATRIZ"<<endl;
    //INGRESE LAS MATRICES
    for (i=1;i<=m;i++)
     for (j=1;j<=n;j++)
    { printf("A(%d,%d)= ",i,j);
       scanf ("%f",&A[i][j]);
    }
     
    printf("\n");
    printf("\n---------------------------------------------------\n");
    printf("\nINGRESE EL VALOR DE LA SEGUNDA MATRIZ\n\n");
      for (i=1;i<=f;i++)
       for (j=1;j<=c;j++)
        { printf("B(%d,%d)= ",i,j);
          scanf ("%f",&B[i][j]);
        }
    //OPERACION DE MULTIPLICACION
     for (i=1;i<=m;i++)
        {for (j=1;j<=c;j++)
           { C[i][j]=0;
             for (k=1;k<=n;k++)
              {C[i][j]=C[i][j]+A[i][k]*B[k][j];
              }
           }
        }
     printf("\n---------------------------------------------------\n");
     printf("\nLA MULTIPLICACION DE LAS MATRICES ES:\n\n");
    //IMPRESION
      for (i=1;i<=m;i++)
       for (j=1;j<=c;j++)
        { printf("C(%d,%d)=\t%4.2f\n",i,j,C[i][j]);
        }
  }
  else
  {
    cout<<"Estas matrices no se pueden multiplicar";
    
  }

}


int bloqes(int m,int n, int f, int c)
{
  int count=2;//vcadadas
  int i,j,k;
  float A[m][n], B[f][c],C[n][f];
  for (int iA = 1; iA <= m/count; iA+=count)
  {
     for (int jA = 1; jA <=n/count; jA+=count)
     {

     
        //OPERACION DE MULTIPLICACION
     for (i=iA;i<=count;i++)
        {for (j=jA;j<=count;j++)
           { C[i][j]=0;
             for (k=jA;k<=count;k++)
              {C[i][j]=C[i][j]+A[i][k]*B[k][j];
              }
           }
        }

        
       
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
    
  }

    
  }

}

int main(int argc, char const *argv[])
{
  /* code */

  struct timeval comienzo, final;

  gettimeofday(&comienzo, NULL);

  multiplicarmtz(3,3,3,3);

  gettimeofday(&final, NULL);

  printf("\nComienzo: %.3f s\n", comienzo.tv_sec+(float)comienzo.tv_usec/1000000);
  printf("Final: %.3f s\n", final.tv_sec+(float)final.tv_usec/1000000);
  printf("\nDuración del programa: %.3f s\n\n", (final.tv_sec+(float)final.tv_usec/1000000)-(comienzo.tv_sec+(float)comienzo.tv_usec/1000000));
  
  return 0;
}



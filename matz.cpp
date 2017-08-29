#include <stdio.h>
#include <iostream>


using namespace std;
int main()
{
  int m,n,f,c,i,j,k;
  
float A[100][100],B[100][100],C[100][100];
  m=3;
  n=3;
  f=3;
  c=3;

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

return 0;
}
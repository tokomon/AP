#include <iostream>
#include <time.h> 
#include <stdio.h> 
#include <sys/time.h> //gettimeofday()


using namespace std;

int main()
{
	long long  MAX=1000;

	struct timeval comienzo, final;

	gettimeofday(&comienzo, NULL);


	long long  A[MAX][MAX], x[MAX], y[MAX];
	long long i,j;
	/*Initialize A and x, assign y = 0 */

	/* First pair of loops */
	for (i = 0; i < MAX; i++)
		{
			for (j = 0; j < MAX; j++)
				{
					y[i] += A[i][j]*x[j];
				}
			}
	/* Assign y = 0 */

	/* Second pair of loops */
	for (j = 0; j < MAX; j++)
	{
		for (i = 0; i < MAX; i++)
			y[i] += A[i][j]*x[j];
	}


	gettimeofday(&final, NULL);

	printf("\nComienzo: %.3f s\n", comienzo.tv_sec+(float)comienzo.tv_usec/1000000);
	printf("Final: %.3f s\n", final.tv_sec+(float)final.tv_usec/1000000);
	printf("\nDuración del programa: %.3f s\n\n", (final.tv_sec+(float)final.tv_usec/1000000)-(comienzo.tv_sec+(float)comienzo.tv_usec/1000000));
	return 0;
}

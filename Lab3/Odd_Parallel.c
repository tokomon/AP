#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

const int RMAX = 100;

int Compare(const void* a_p, const void* b_p) {
  int a = *((int*)a_p);
  int b = *((int*)b_p);

  if (a < b)
  return -1;
  else if (a == b)
  return 0;
  else /* a > b */
  return 1;
}

void Merge_split_low(int local_A[], int temp_B[], int temp_C[],
  int local_n) {
    int ai, bi, ci;

    ai = 0;bi = 0;ci = 0;
    while (ci < local_n) {
      if (local_A[ai] <= temp_B[bi]) {
        temp_C[ci] = local_A[ai];
        ci++; ai++;
      } else {
        temp_C[ci] = temp_B[bi];
        ci++; bi++;
      }
    }
    memcpy(local_A, temp_C, local_n*sizeof(int));
  }

  void Merge_split_high(int local_A[], int temp_B[], int temp_C[],
    int local_n) {
      int ai, bi, ci;

      ai = local_n-1;
      bi = local_n-1;
      ci = local_n-1;
      while (ci >= 0) {
        if (local_A[ai] >= temp_B[bi]) {
          temp_C[ci] = local_A[ai];
          ci--; ai--;
        } else {
          temp_C[ci] = temp_B[bi];
          ci--; bi--;
        }
      }
      memcpy(local_A, temp_C, local_n*sizeof(int));
    }

void Odd_even_iter(int local_A[], int temp_B[], int temp_C[],
  int local_n, int phase, int even_partner, int odd_partner,
  int my_rank, int p, MPI_Comm comm) {
    MPI_Status status;

    if (phase % 2 == 0) {  /* Even phase, odd process <-> rank-1 */
      if (even_partner >= 0) {
        MPI_Sendrecv(local_A, local_n, MPI_INT, even_partner, 0,
          temp_B, local_n, MPI_INT, even_partner, 0, comm,
          &status);
          if (my_rank % 2 != 0)
          Merge_split_high(local_A, temp_B, temp_C, local_n);
          else
          Merge_split_low(local_A, temp_B, temp_C, local_n);
        }
      } else { /* Odd phase, odd process <-> rank+1 */
        if (odd_partner >= 0) {
          MPI_Sendrecv(local_A, local_n, MPI_INT, odd_partner, 0,
            temp_B, local_n, MPI_INT, odd_partner, 0, comm,
            &status);
            if (my_rank % 2 != 0)
            Merge_split_low(local_A, temp_B, temp_C, local_n);
            else
            Merge_split_high(local_A, temp_B, temp_C, local_n);
          }
        }
      }
void Sort(int local_A[], int local_n, int my_rank,
         int p, MPI_Comm comm) {
   int phase;
   int *temp_B, *temp_C;
   int even_partner;  /* phase is even or left-looking */
   int odd_partner;   /* phase is odd or right-looking */

   /* Temporary storage used in merge-split */
   temp_B = (int*) malloc(local_n*sizeof(int));
   temp_C = (int*) malloc(local_n*sizeof(int));

   /* Find partners:  negative rank => do nothing during phase */
   if (my_rank % 2 != 0) {
      even_partner = my_rank - 1;
      odd_partner = my_rank + 1;
      if (odd_partner == p) odd_partner = -1;  // Idle during odd phase
   } else {
      even_partner = my_rank + 1;
      if (even_partner == p) even_partner = -1;  // Idle during even phase
      odd_partner = my_rank-1;
   }

   /* Sort local list using built-in quick sort */
   qsort(local_A, local_n, sizeof(int), Compare);

   for (phase = 0; phase < p; phase++)
      Odd_even_iter(local_A, temp_B, temp_C, local_n, phase,
             even_partner, odd_partner, my_rank, p, comm);

   free(temp_B);
   free(temp_C);
}

void Print_list(int local_A[], int local_n, int rank) {
   int i;
   printf("%d: ", rank);
   for (i = 0; i < local_n; i++)
      printf("%d ", local_A[i]);
   printf("\n");
}

void Print_local_lists(int local_A[], int local_n,
         int my_rank, int p, MPI_Comm comm) {
   int*       A;
   int        q;
   MPI_Status status;

   if (my_rank == 0) {
      A = (int*) malloc(local_n*sizeof(int));
      Print_list(local_A, local_n, my_rank);
      for (q = 1; q < p; q++) {
         MPI_Recv(A, local_n, MPI_INT, q, 0, comm, &status);
         Print_list(A, local_n, q);
      }
      free(A);
   } else {
      MPI_Send(local_A, local_n, MPI_INT, 0, 0, comm);
   }
}

void Generate_list(int local_A[], int local_n, int my_rank) {
   int i;

    srandom(my_rank+1);
    for (i = 0; i < local_n; i++)
       local_A[i] = random() % RMAX;

}
void Get_args(int argc, char* argv[], int* global_n_p, int* local_n_p,int my_rank, int p, MPI_Comm comm) {

   if (my_rank == 0) {
        *global_n_p = strtol(argv[1], NULL, 10);
   }

   MPI_Bcast(global_n_p, 1, MPI_INT, 0, comm);
   *local_n_p = *global_n_p/p;

}
void Print_global_list(int local_A[], int local_n, int my_rank, int p,
      MPI_Comm comm) {
   int* A = NULL;
   int i, n;

   if (my_rank == 0) {
      n = p*local_n;
      A = (int*) malloc(n*sizeof(int));
      MPI_Gather(local_A, local_n, MPI_INT, A, local_n, MPI_INT, 0,
            comm);
      printf("Global list:\n");
      for (i = 0; i < n; i++)
         printf("%d ", A[i]);
      printf("\n\n");
      free(A);
   } else {
      MPI_Gather(local_A, local_n, MPI_INT, A, local_n, MPI_INT, 0,
            comm);
   }

}

/*-------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   int my_rank, p;
   char g_i;
   int *local_A;
   int global_n;
   int local_n;
   MPI_Comm comm;
   double start, finish;

   MPI_Init(&argc, &argv);
   comm = MPI_COMM_WORLD;
   MPI_Comm_size(comm, &p);
   MPI_Comm_rank(comm, &my_rank);

   Get_args(argc, argv, &global_n, &local_n, my_rank, p, comm);
   local_A = (int*) malloc(local_n*sizeof(int));
      Generate_list(local_A, local_n, my_rank);
   Print_local_lists(local_A, local_n, my_rank, p, comm);

   start = MPI_Wtime();
   Sort(local_A, local_n, my_rank, p, comm);
   finish = MPI_Wtime();
   if (my_rank == 0)
      printf("Elapsed time = %e seconds\n", finish-start);

   Print_global_list(local_A, local_n, my_rank, p, comm);
   free(local_A);
   MPI_Finalize();
   return 0;
}

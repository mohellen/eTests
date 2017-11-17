#include <mpi.h>
#include <stdio.h>
#include <unistd.h>

/** iMPI related from <mpi.h>

#define MPI_ADAPT_FALSE             0
#define MPI_ADAPT_TRUE              1
#define MPI_ADAPT_STATUS_NEW        2
#define MPI_ADAPT_STATUS_JOINING    3
#define MPI_ADAPT_STATUS_STAYING    4
#define MPI_ADAPT_STATUS_LEAVING 	5
int MPI_Init_adapt(int *argc, char ***argv, int *local_status);
int MPI_Probe_adapt(int *current_operation, int *local_status, MPI_Info *info);
int MPI_Comm_adapt_begin(MPI_Comm *intercomm, MPI_Comm *new_comm_world, int *staying_count, int *leaving_count, int *joining_count);
int MPI_Comm_adapt_commit(void);

*/

int main(int argc, char* argv[]) {

	int mpisize, mpirank, mpistatus;

	MPI_Init_adapt(&argc, &argv, &mpistatus);
	MPI_Comm_size(MPI_COMM_WORLD, &mpisize);
	MPI_Comm_rank(MPI_COMM_WORLD, &mpirank);

	if (mpirank==0) {
		printf("Total %d ranks\n", mpisize);
		printf("IMPI_FREQ = %d\n", IMPI_FREQ);
	}
	printf("Rank %d\n", mpirank);

	sleep(30);
	MPI_Barrier(MPI_COMM_WORLD);

	printf("Rank %d again!!\n", mpirank);

	
	MPI_Finalize();
	return 0;
}


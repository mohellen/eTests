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

// IMPI_FREQ defined at compile time


void impi_adapt(
		int& mpisize,
		int& mpirank,
		int& mpistatus,
		int& iter) 
{
	int adapt_flag;
	MPI_Info mpi_info;
	MPI_Comm intercomm, newcomm;
	int numstay, numleave, numjoin;

	MPI_Probe_adapt(&adapt_flag, &mpistatus, &mpi_info);
	if (adapt_flag == MPI_ADAPT_TRUE) {
		MPI_Comm_adapt_begin(&intercomm, &newcomm, &numstay, &numleave, &numjoin);
		//************* adapt window ***************
		if (mpistatus == MPI_ADAPT_STATUS_STAYING && mpirank == 0)
			printf("Adapting... %d staying, %d leaving, %d joining.\n", numstay, numleave, numjoin);
		MPI_Bcast(&iter, 1, MPI_INT, 0, newcomm);
		//*********** adapt window end *************
		MPI_Comm_adapt_commit();
		MPI_Comm_size(MPI_COMM_WORLD, &mpisize);
		MPI_Comm_rank(MPI_COMM_WORLD, &mpirank);
	}
	return;
}

bool is_root(
		const int& mpirank,
		const int& mpistatus)
{
	return (mpirank == 0 && mpistatus != MPI_ADAPT_STATUS_JOINING);		
}


int main(int argc, char* argv[]) {

	int mpisize, mpirank, mpistatus;

	MPI_Init_adapt(&argc, &argv, &mpistatus);
	MPI_Comm_size(MPI_COMM_WORLD, &mpisize);
	MPI_Comm_rank(MPI_COMM_WORLD, &mpirank);

	int iter = 1, itermax = 50;

	// Joining ranks adapt directly
	if (mpistatus == MPI_ADAPT_STATUS_JOINING) {
		impi_adapt(mpisize, mpirank, mpistatus, iter);
	}

	// Main loop
	for (; iter <= itermax; ++iter) {

		if (is_root(mpirank, mpistatus)) {
			printf("Iteration %d: total ranks %d\n", iter, mpisize);
		}

		sleep(IMPI_FREQ);
		impi_adapt(mpisize, mpirank, mpistatus, iter); //impi_adapt must be at END of loop
	}
	MPI_Finalize();
	return 0;
}


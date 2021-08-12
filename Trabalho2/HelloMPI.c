#include<stdio.h>
#include<mpi.h>

int main (int argc, char *argv[]){
	/// Compilar com : mpicc 'nomeDoArquivo'.c -o 'nomeParaSaida'.e
	/// Executar: mpirun --oversubscribe (flag para aumentar o número de processos )-n 5(número de processos) ./'nomeParaSaida'.e
	
	int size, myRank, valorInicial, valorModificado, total, nproc;
	MPI_Status st;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

	// int valorInicial, valorModificado, total;

	printf("Hello! Sou o processo %d de um total de %d\n", myRank, size);
	fflush(stdout);

	if(myRank == 0){
		for (nproc = 1; nproc < size; nproc++){
			valorInicial = nproc*10;
			MPI_Send(&valorInicial, 1, MPI_INT, nproc, 0, MPI_COMM_WORLD);
			printf("MESTRE - Enviei %d para PROC(%d)\n",valorInicial, nproc);
			fflush(stdout);
		}
		total = 0;
		for (nproc = 1; nproc <size; nproc++){
			MPI_Recv(&valorModificado, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &st);
			printf("MESTRE- RECEBI o valor MODIFICADO %d\n",valorModificado);
			fflush(stdout);

			total+= valorModificado;
		}
		printf("MESTRE - Total do processamento = %d\n", total);
		fflush(stdout);
	}
	else{
		MPI_Recv(&valorInicial, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &st);
		printf("ESCRAVO(%d) - Recebi %d do mestre\n", myRank, valorInicial);
		fflush(stdout);
		valorModificado = valorInicial * 10;

		MPI_Send(&valorModificado, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
	}

	
	MPI_Finalize();
	
	return 0;
}


#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h>
#define TAM 100
using namespace std;
vector<int> vetor;

int main(int argc, char** argv) {
    /// mpic++ Trabalho2SD.cpp -o Trabalho2SD.e
    /// mpirun --oversubscribe -n 10 ./Trabalho2SD.e


    int valorModificado[TAM];
    int size, myRank, nproc, valorInicial, total;
    MPI_Status st;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    double local_start_time, local_finish_time, local_time_elapsed, time_elapsed;
    MPI_Barrier(MPI_COMM_WORLD);
    local_start_time = MPI_Wtime();
    
        if(myRank == 0){
                for (nproc = 1; nproc < size; nproc++){
                    valorInicial = nproc*TAM;
                    MPI_Send(&valorInicial, 1, MPI_INT, nproc, 0, MPI_COMM_WORLD);
                    fflush(stdout);
                }
                total = 0;
                for (nproc = 1; nproc <size; nproc++){
                    MPI_Recv(&valorModificado, TAM, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &st);
                    fflush(stdout);
                    for(int i=0;i<TAM;i++){
                        vetor.push_back(valorModificado[i]);
                    }
                    
                }
                
            }
            else{
                MPI_Recv(&valorInicial, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &st);
                printf("ESCRAVO(%d) - Recebi %d do mestre\n", myRank, valorInicial);
                fflush(stdout);
                
                for(int i=0;i<TAM;i++){
                    valorModificado[i] = i + valorInicial;
                }

                MPI_Send(&valorModificado, TAM, MPI_INT, 0, 1, MPI_COMM_WORLD);
            }

    local_finish_time = MPI_Wtime();
    local_time_elapsed = local_finish_time - local_start_time;

    MPI_Reduce(&local_time_elapsed, &time_elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (myRank == 0) {
        for(int i=0; i< vetor.size();i++){
            printf("posição %d do vetor tem valor |%d \n",i,vetor[i]);
            fflush(stdout);
            if(i%TAM == 0)
                printf("-------------------------------------------------------------------------------\n");
            fflush(stdout);
        }
        printf("\nElapsed time: %.4f seconds.\n", time_elapsed);
    }

    MPI_Finalize();

    return 0;
}


#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h>
using namespace std;
vector<int> vetor;

int main(int argc, char** argv) {
    int valorModificado[10];
    int size, myRank, nproc, valorInicial, total;
    MPI_Status st;
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    //Get the greatest elapsed time among all processes
    double local_start_time, local_finish_time, local_time_elapsed, time_elapsed;
    
    MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    //Barrier to count the elapsed time
    MPI_Barrier(MPI_COMM_WORLD);
    local_start_time = MPI_Wtime();
    //---------------------------------Program Logic-------------------------------------//
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
                    fflush(stdout);
                    for(int i=0;i<10;i++){
                        vetor.push_back(valorModificado[i]);
                    }
                    
                }
                for(int i=0; i< vetor.size();i++){
                    printf("posição %d do vetor tem valor %d \n",i,vetor[i]);
                    fflush(stdout);
                }
            }
            else{
                MPI_Recv(&valorInicial, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &st);
                printf("ESCRAVO(%d) - Recebi %d do mestre\n", myRank, valorInicial);
                fflush(stdout);
                for(int i=0;i<10;i++){
                    valorModificado[i] = i + valorInicial;
                }

                MPI_Send(&valorModificado, 10, MPI_INT, 0, 1, MPI_COMM_WORLD);
            }


    //-----------------------------------------------------------------------------------//
    local_finish_time = MPI_Wtime();
    local_time_elapsed = local_finish_time - local_start_time;
    //Sends to the root process the greatest time elapsed among all processes
    MPI_Reduce(&local_time_elapsed, &time_elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    //Root process prints all information
    if (myRank == 0) {
    //        printf("\nPi aproximation: %f\n", 4 * pi);
    //        printf("\nPi aproximation in cmath: %f\n", M_PI);
    //        printf("\nPi aproximation error: %f\n", M_PI - 4 * pi);
        printf("\nElapsed time: %.4f seconds.\n", time_elapsed);
    }

    // Finalize the MPI environment.
    MPI_Finalize();

    return 0;
}

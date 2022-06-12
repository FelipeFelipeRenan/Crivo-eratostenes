#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TAMANHO 1000000


int calculaTamanho (size_t tamanho, size_t proc, size_t nprocs) {

/*
 * Como dependendo da quantidade de processos o tamanho de cada sub-vetor
 * pode mudar, foi criada essa função que retorna o número de elementos
 * que cada sub-vetor pode armazenar.
 *
 * EX:. Seja T um tamanho igual a 100 para ser dividido para 3 processos,
 * os dois primeiros processos ficam com 33 elementos e o ultimo com 34.
 * */

  int vet[nprocs];
  int sum = 0, i;
  for (i = 0; i < nprocs-1; i++) {
    vet[i] = tamanho/nprocs;
    sum += vet[i];
  }

  vet[i] = tamanho - sum;

  return vet[proc];
}

int main() {

  //Iniciando MPI
  MPI_Init(NULL, NULL);
  int nprocs;
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Status status;

  float t_inicio, t_fim;
  if (rank == 0) {
    t_inicio = MPI_Wtime();
  }

  int TAMANHO_POR_PROCESSO = calculaTamanho(TAMANHO, rank, nprocs);
  int SALTO = TAMANHO / nprocs;
  int raiz_valor_limite = sqrt(TAMANHO);

  int *vetor;
  vetor = malloc((TAMANHO_POR_PROCESSO)*sizeof(int));
  if (vetor == NULL) {
    perror("Erro de alocação de memória!");
    exit(0);
  }


  // coloca os pares como 0 e ímpares como 1
  if (rank == 0){
    vetor[0] = vetor[1] = 0;
    for (int i = 2; i < TAMANHO_POR_PROCESSO; i++) {
      if (i % 2 == 0 && i > 2) {
        vetor[i] = 0;
      } else {
        vetor[i] = 1;
      }
    }
  } else {
    for (int i = (rank*SALTO), j=0; j < TAMANHO_POR_PROCESSO; i++, j++) {
      if (i % 2 == 0 && i > 2) {
        vetor[j] = 0;
      } else {
        vetor[j] = 1;
      }
    }
  }

  
  
  // verifica cada multiplo de números ímpares e seta como 0
  for (int i = 3; i <= raiz_valor_limite; i += 2) {
    if (rank == 0){
      for (int j = i+1, k=i+1; k < TAMANHO_POR_PROCESSO; j++, k++) {
        if (j % i == 0) {
          vetor[k] = 0;
        }
      }
    } else {
      for (int j = (rank*SALTO), k=0; k < TAMANHO_POR_PROCESSO; j++, k++) {
        if (j % i == 0) {
          vetor[k] = 0;
        }
      }
    }
  }
  

  // conta a quantidade de primos de cada processo
  int count;
  count = 0;
  if (rank == 0) {
    for (int i = 0; i < TAMANHO_POR_PROCESSO; i++) {
      if (vetor[i] == 1) count++;
    }
  } else {
    for (int i = (rank*SALTO), j=0; j < TAMANHO_POR_PROCESSO; i++, j++) {
      if (vetor[j] == 1) count++;
    }
  }

  // consolida os resultados de cada processo (quantidade de números primos)
  int total = 0;
  MPI_Reduce(&count, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
 
  MPI_Barrier(MPI_COMM_WORLD);
  if (rank == 0) {
    t_fim = MPI_Wtime();
    printf("Qtd MPI   [%d]\n", total);
    printf("Tempo MPI: %.3f\n", t_fim - t_inicio);
  }

  MPI_Finalize();

  return 0;
}

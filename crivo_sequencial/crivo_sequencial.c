#include "crivo_sequencial.h"

bool crivoSeq(int valorLimite, double *tempo) {

  int *indicesValPrim = (int*)malloc(valorLimite * sizeof(int));

  if(indicesValPrim == NULL) {
    perror("Erro de alocação de memória!\n");
    return false;
  }

  double t_inicio, t_final;
  int raizValorLimite = sqrt(valorLimite);

  t_inicio = omp_get_wtime();

  for(int i = 2; i <= valorLimite; i++) {
    if (i % 2 == 0 && i > 2) {
      indicesValPrim[i-2] = 0;
    }else{
      indicesValPrim[i-2] = 1;
    }
  }

  for(int i = 2; i <= raizValorLimite; i++) {
    for(int j = i+1; j <= valorLimite;j++) {
      if(j % i == 0) {
        indicesValPrim[j-2] = 0;
      }
    }
  }

  int qtdPrim = 0;
  for (int i = 0; i < valorLimite-2; i++)
    if (indicesValPrim[i] == 1)
      qtdPrim++;

  t_final = omp_get_wtime();
  *tempo = t_final - t_inicio;
  free(indicesValPrim);

  printf("QTD sequencial [%d]\n", qtdPrim);

  return true;
}

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

  indicesValPrim[0] = indicesValPrim[1] = 0;
  for(int i = 2; i < valorLimite; i++) {
    indicesValPrim[i] = 1;
  }

  for(int i = 2; i*i < valorLimite; i++) {
    if (indicesValPrim[i] == 1) {
      for(int j = i*i; j < valorLimite;j += i) {
          indicesValPrim[j] = 0;
      }
    }
  }

  int qtdPrim = 0;
  for (int i = 0; i < valorLimite; i++)
    if (indicesValPrim[i] == 1)
      qtdPrim++;

  t_final = omp_get_wtime();
  *tempo = t_final - t_inicio;
  free(indicesValPrim);

  printf("QTD sequencial [%d]\n", qtdPrim);

  return true;
}

#include "crivo_mp.h"

#define TOTAL_THREADS 3

bool crivoMP(int valorLimite, double *tempo) {
  
  int *indicesValPrim = (int*)malloc(valorLimite * sizeof(int));

  if(indicesValPrim == NULL)
    return false;

  double t_inicio, t_final;
  int qtdPrimThread[TOTAL_THREADS];
  int raizValorLimite = sqrt(valorLimite);

  t_inicio = omp_get_wtime();
  #pragma omp parallel num_threads(TOTAL_THREADS)
  {

    int num_thread = omp_get_thread_num();

    #pragma omp for
    for(int i = 2; i <= valorLimite; i++) {
	if (i % 2 == 0 && i > 2)
          indicesValPrim[i-2] = 0;
        else
          indicesValPrim[i-2] = 1;
    }

    for(int i = 3; i <= raizValorLimite; i += 2) {
      #pragma omp for
      for(int j = i+1; j <= valorLimite; j += 1) {
        if(j % i == 0) {
          indicesValPrim[j-2] = 0;
        }
      }
    }

    qtdPrimThread[num_thread] = 0;
    #pragma omp for
    for (int i = 0; i < valorLimite-2; i++) {
      if (indicesValPrim[i] == 1) {
        qtdPrimThread[num_thread]++;
      }
    }
  }

  int qtdPrim = 0;
  for(int i = 0; i < TOTAL_THREADS; i++)
    qtdPrim += qtdPrimThread[i];

  t_final = omp_get_wtime();
  *tempo = t_final - t_inicio;
  free(indicesValPrim);

  printf("QTD paralela   [%d]\n", qtdPrim);

  return true;
}

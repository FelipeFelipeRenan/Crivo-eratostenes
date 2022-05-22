#include "crivo.h"

int main () {

  double tempos[3];
  int qtd = 500000;

  for(int i = 0; i < 10; i++) {
    if ( !crivoSeq(qtd, tempos, TSEQUENCIAL) )
      break;

    if ( !crivoMP(qtd, tempos, TPARALELO) ) 
      break;

    tempos[SPEEDUP] = tempos[TSEQUENCIAL] / tempos[TPARALELO];

    printf("Tempo sequencial: %.3f\n", tempos[TSEQUENCIAL]);
    printf("Tempo paralelo  : %.3f\n", tempos[TPARALELO]);
    printf("Speedup: %.3f\n", tempos[SPEEDUP]);
    puts("");
  }
  return 0;
}

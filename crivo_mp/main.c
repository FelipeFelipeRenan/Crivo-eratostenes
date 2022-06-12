#include "crivo_mp.h"

int main () {

  double tempo;
  int qtd = 1000000;

  for(int i = 0; i < 10; i++) {
    if ( !crivoMP(qtd, &tempo) ) 
      break;

    printf("Tempo paralelo  : %.3f\n", tempo);
    puts("");
  }
  return 0;
}

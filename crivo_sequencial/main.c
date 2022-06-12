#include "crivo_sequencial.h"

int main () {

  double tempo;
  int qtd = 1000000;

  for(int i = 0; i < 10; i++) {
    if ( !crivoSeq(qtd, &tempo) )
      break;

    printf("Tempo sequencial: %.3f\n", tempo);
    puts("");
  }
  return 0;
}

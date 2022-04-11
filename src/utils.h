#include <stdio.h>
#include <stdlib.h>

#include "types.h"

int max (int a, int b){
  return a > b ? a : b;
}

FILE *abreArquivo(char *nomeArquivo, char *modo){
  FILE *arquivo;
  if (!(arquivo = fopen(nomeArquivo, modo))) {
    printf("Erro na tentativa de abrir arquivo \"%s\".\n", nomeArquivo);
    exit(-1);
  }
  return arquivo;
}

int proximaPosicao(int posicaoAtual, int salto){
  return (posicaoAtual + salto) % MAXNUMREGS;
}
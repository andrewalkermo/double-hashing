#include <stdio.h>
#include <stdlib.h>

#include "types.h"

void inserirRegistro();
void consultarRegistro();
void removerRegistro();
void imprimirArquivo();
void mediaDeAcessos();

int main() {

  char comando;
  while (scanf("%c\n", &comando)) {
    switch (comando) {
      case INSERE_REGISTRO:
        inserirRegistro();
        break;
      case CONSULTA_REGISTRO:
        consultarRegistro();
        break;
      case REMOVE_REGISTRO:
        removerRegistro();
        break;
      case IMPRIME_ARQUIVO:
        imprimirArquivo();
        break;
      case MEDIA_DE_ACESSOS:
        mediaDeAcessos();
        break;
      case FIM_DOS_COMANDOS:
        return 0;
      default:
        printf("LOG - Comando invalido\n");
        return 1;
        break;
    }
  }
  return 0;
}

void inserirRegistro() {
  Registro registro;
  scanf("%d\n", &registro.dados.chave);
  scanf("%s\n", registro.dados.nome);
  scanf("%d\n", &registro.dados.idade);
  registro.ocupado = true;
  printf("LOG - Registro inserido: %d %s %d\n", registro.dados.chave, registro.dados.nome, registro.dados.idade);
}

void consultarRegistro() {
  int chave;
  scanf("%d\n", &chave);
  printf("LOG - Consultando registro\n");
}

void removerRegistro(){
  int chave;
  scanf("%d\n", &chave);
  printf("LOG - Removendo registro\n");
}
void imprimirArquivo(){
  printf("LOG - Imprimindo arquivo\n");
}
void mediaDeAcessos(){
  printf("LOG - Calculando media de acessos\n");
}
#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_NOME 20
#define MAXNUMREGS 11

#define INSERE_REGISTRO 'i'
#define CONSULTA_REGISTRO 'c'
#define REMOVE_REGISTRO 'r'
#define IMPRIME_ARQUIVO 'p'
#define MEDIA_DE_ACESSOS 'm'
#define FIM_DOS_COMANDOS 'e'

#define FILE_NAME "registros"

#define STATUS_OCUPADO 1
#define STATUS_LIVRE 0
#define STATUS_REMOVIDO -1

int totalAcessosComSucesso = 0;
int totalAcessosComFalha = 0;
int totalConsultasComSucesso = 0;
int totalConsultasComFalha = 0;

typedef struct {
  int chave;
  char nome[TAMANHO_NOME];
  int idade;
} DadosUsuario;

typedef struct {
  int status;
  DadosUsuario dados;
} Registro;

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
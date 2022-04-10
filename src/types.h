#include <stdbool.h>

#define TAMANHO_NOME 20

#define INSERE_REGISTRO 'i'
#define CONSULTA_REGISTRO 'c'
#define REMOVE_REGISTRO 'r'
#define IMPRIME_ARQUIVO 'p'
#define MEDIA_DE_ACESSOS 'm'
#define FIM_DOS_COMANDOS 'e'

int MAXNUMREGS = 11;

typedef struct {
	   int chave;
	   char nome[TAMANHO_NOME];
     int idade;
} DadosUsuario;

typedef struct {
   bool ocupado;
   DadosUsuario dados;
} Registro;

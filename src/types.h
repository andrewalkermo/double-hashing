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

typedef struct {
  int chave;
  char nome[TAMANHO_NOME];
  int idade;
} DadosUsuario;

typedef struct {
  int status;
  DadosUsuario dados;
} Registro;

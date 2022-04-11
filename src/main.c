#include "utils.h"

int hashUm(int chave);
int hashDois(int chave);

void lerComandos();
void inserirRegistro();
void consultarRegistro();
void removerRegistro();
void imprimirArquivo();
void mediaDeAcessos();
void inicializarArquivo();


int main() {

  inicializarArquivo();
  lerComandos();
  return 0;
}

void lerComandos(){
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
        return;
      default:
        exit(-1);
    }
  }
}

void inserirRegistro() {
  Registro novoRegistro;
  novoRegistro.status = STATUS_OCUPADO;
  scanf("%d\n", &novoRegistro.dados.chave);
  scanf("%s\n", novoRegistro.dados.nome);
  scanf("%d\n", &novoRegistro.dados.idade);

  Registro registro;
  FILE *arquivo = abreArquivo(FILE_NAME, "r+");
  int posicao = hashUm(novoRegistro.dados.chave);
  int acessos = 0;
  
  do {
    fseek(arquivo, posicao * sizeof(Registro), SEEK_SET);
    fread(&registro, sizeof(Registro), 1, arquivo);
    if (registro.status != STATUS_OCUPADO) {
      fseek(arquivo, posicao *sizeof(Registro), SEEK_SET);
      fwrite(&novoRegistro, sizeof(Registro), 1, arquivo);
      printf("insercao com sucesso: %d\n", novoRegistro.dados.chave);
      fclose(arquivo);
      return;
    } else if (registro.dados.chave == novoRegistro.dados.chave) {
      printf("chave ja existente: %d\n", novoRegistro.dados.chave);
      fclose(arquivo);
      return;
    }
    posicao = proximaPosicao(posicao, hashDois(novoRegistro.dados.chave));
    acessos++;
  } while (registro.status == STATUS_OCUPADO && acessos < MAXNUMREGS);
  
  printf("insercao de chave sem sucesso - arquivo cheio: %d\n", novoRegistro.dados.chave);
  fclose(arquivo);
}

void consultarRegistro() {
  int chave;
  scanf("%d\n", &chave);
  Registro registro;
  FILE *arquivo = abreArquivo(FILE_NAME, "r");
  
  int posicao = hashUm(chave);
  int acessos = 0;
  do {
    fseek(arquivo, posicao * sizeof(Registro), SEEK_SET);
    fread(&registro, sizeof(Registro), 1, arquivo);
    
    if (registro.dados.chave == chave) {
      printf("chave: %d\n", chave);
      printf("%s\n", registro.dados.nome);
      printf("%d\n", registro.dados.idade);
      fclose(arquivo);
      return;
    } else if (registro.status == STATUS_LIVRE) {
      printf("chave nao encontrada: %d\n", chave);
      fclose(arquivo);
      return;
    }
    
    posicao = proximaPosicao(posicao, hashDois(chave));
    acessos++;
  } while (acessos < MAXNUMREGS);
  
  printf("chave nao encontrada: %d\n", chave);
  fclose(arquivo);
}

void removerRegistro(){
  int chave;
  scanf("%d\n", &chave);
  Registro registro;
  FILE *arquivo = abreArquivo(FILE_NAME, "r+");
  
  int posicao = hashUm(chave);
  int acessos = 0;
  do {
    fseek(arquivo, posicao * sizeof(Registro), SEEK_SET);
    fread(&registro, sizeof(Registro), 1, arquivo);
    
    if (registro.dados.chave == chave) {
      registro.status = STATUS_REMOVIDO;
      fseek(arquivo, posicao * sizeof(Registro), SEEK_SET);
      fwrite(&registro, sizeof(Registro), 1, arquivo);
      printf("chave removida com sucesso: %d\n", chave);
      fclose(arquivo);
      return;
    } else if (registro.status == STATUS_LIVRE) {
      printf("chave nao encontrada: %d\n", chave);
      fclose(arquivo);
      return;
    }
    
    posicao = proximaPosicao(posicao, hashDois(chave));
    acessos++;
  } while (acessos < MAXNUMREGS);
  
  printf("chave nao encontrada: %d\n", chave);
  fclose(arquivo);
}

void imprimirArquivo(){
  int i;
  Registro registro;
  FILE *arquivo = abreArquivo(FILE_NAME, "r");
  
  for (i = 0; i < MAXNUMREGS; i++) {
    fread (&registro, sizeof (Registro), 1, arquivo);
    if (registro.status == STATUS_OCUPADO) {
      printf("%d: %d %s %d\n", i, registro.dados.chave, registro.dados.nome, registro.dados.idade);
    } else if (registro.status == STATUS_LIVRE) {
      printf("%d: vazio\n", i);
    } else {
      printf("%d: *\n", i);
    }
  }
  
  fclose(arquivo);
}

void mediaDeAcessos(){
  printf("LOG - Calculando media de acessos\n");
}

void inicializarArquivo(){
  FILE *arquivo = abreArquivo(FILE_NAME, "w+");

  Registro registro;
  registro.status = STATUS_LIVRE;
  
  for (int i = 0; i < MAXNUMREGS; i++) {
    fwrite(&registro, sizeof(Registro), 1, arquivo);
  }
  fclose(arquivo);
}

int hashUm(int chave){
  return chave % MAXNUMREGS;
}

int hashDois(int chave){
  return max((chave / MAXNUMREGS) % MAXNUMREGS, 1);
}
/*
 *  Nomes: Leonardo Altemari Nogueira - 10284883
 *         Pedro Henrique Magalhães Cisdeli - 10289804
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binarioNaTela.h"

// Funcionalidades
#include"general.h"
#include"funcionalidade_1.h"
#include"funcionalidade_2.h"
#include"funcionalidade_3.h"
#include"funcionalidade_4.h"
#include"funcionalidade_5.h"
#include"funcionalidade_6.h"
#include"funcionalidade_7.h"



int main() {

  int funcionalidade;
  char nomeArquivoTexto[200];
  char nomeArquivoBinario[200];

  scanf("%d", &funcionalidade);

  // FUNCIONALIDADE 1
  if (funcionalidade == 1) {
    scanf("%s %s", nomeArquivoTexto, nomeArquivoBinario);

    FILE *fp = leituraArquivoTexto(nomeArquivoTexto);
    int *tam = malloc(sizeof(
        int)); // variavel para armazenar o numero de linhas do arquivo texto.

    // Transforma o arquivo texto em uma String e fecha ele
    char **arquivoTexto = copiaArquivoTexto(fp, tam);
    fclose(fp);

    // Cria o arquvivo binario
    FILE *fpbin = fopen(nomeArquivoBinario, "w+b");
    if (fpbin == NULL) {
      printf("Falha no carregamento do arquivo.\n");
      return 0;
    }

    // Chama a funcao para passar os dados do arquivo texto para o arquivo
    // binario
    copiaDados(fpbin, arquivoTexto, *tam);
    fseek(fpbin, 0, SEEK_SET);

    // arquivo binario
    fclose(fpbin);

    binarioNaTela(nomeArquivoBinario);

    // Libera toda memoria utilizada.
    desalocaArquivoTexto(arquivoTexto, *tam);
    free(tam);

  }
  // FUNCIONALIDADE 2
  else if (funcionalidade == 2) {
    scanf("%s ", nomeArquivoBinario);

    // Abertura do arquivo para leitura.
    FILE *fpbin = fopen(nomeArquivoBinario, "rb");

    // Confere se o arquivo existe e se é consistente.
    if (fpbin == NULL || !returnStatus(fpbin)) {
      printf("Falha no processamento do arquivo.\n");
      if (fpbin != NULL) // Fecha o arquivo caso o status não seja consistente
        fclose(fpbin);
      return 0;
    }

    // Leitura dos registros e fechamento do arquivo.
    readRegs(fpbin);
    fclose(fpbin);
  } else if (funcionalidade == 3) {
    scanf("%s ", nomeArquivoBinario);

    // Abertura do arquivo para leitura.
    FILE *fpbin = fopen(nomeArquivoBinario, "rb");

    // Confere se o arquivo existe e se é consistente.
    if (fpbin == NULL || !returnStatus(fpbin)) {
      printf("Falha no processamento do arquivo.\n");
      if (fpbin != NULL) // Fecha o arquivo caso o status não seja consistente
        fclose(fpbin);
      return 0;
    }
    int m;
    scanf("%d", &m);
    buscaCombinada(fpbin, m);
    fclose(fpbin);
  }
  // FUNCIONALIDADE 4
  else if (funcionalidade == 4) {
    scanf("%s ", nomeArquivoBinario);

    // Abertura do arquivo para leitura.
    FILE *fpbin = fopen(nomeArquivoBinario, "rb");

    // Confere se o arquivo existe e se é consistente.
    if (fpbin == NULL || !returnStatus(fpbin)) {
      printf("Falha no processamento do arquivo.\n");
      if (fpbin != NULL) // Fecha o arquivo caso o status não seja consistente
        fclose(fpbin);
      return 0;
    }

    int _rrn;
    scanf("%d", &_rrn);

    // Busca rrn e printa o registro, caso ele exista
    buscaRRN(fpbin, _rrn);
    fclose(fpbin);
  }
  // FUNCIONALIDADE 5
  else if (funcionalidade == 5) {
    scanf("%s ", nomeArquivoBinario);

    // Abertura do arquivo para leitura.
    FILE *fpbin = fopen(nomeArquivoBinario, "r+b");

    // Confere se o arquivo existe e se é consistente.
    if (fpbin == NULL || !returnStatus(fpbin)) {
      printf("Falha no processamento do arquivo.\n");
      if (fpbin != NULL) // Fecha o arquivo caso o status não seja consistente
        fclose(fpbin);
      return 0;
    } else {
      // Arquivo foi aberto para escrita(remocao de registro), portanto seu
      // status fica como 0 enquanto ele estiver aberto
      setStatus(fpbin, "0");
    }

    // Numero de vezes que vai executar a entrada das combinacoes dos campos
    int numVezes;
    scanf("%d", &numVezes);

    // Quantos campos tem em cada combinacao
    int m;

    // Executa 'n' vezes a remocao de um registro de acordo com os campos
    // buscados, Caso o registro buscado nao seja encontrado continua aplicando
    // a remocao ate completar as 'n' vezes.
    for (int i = 0; i < numVezes; i++) {
      scanf("%d", &m);
      removeRegistros(fpbin, m);
    }

    // Escrita no arquivo foi finalizada, retorna o status para 1
    setStatus(fpbin, "1");

    // Fecha o arquivo e printa o binario.
    fclose(fpbin);
    binarioNaTela(nomeArquivoBinario);
  }
  // FUNCIONALIDADE 6
  else if (funcionalidade == 6) {
    scanf("%s ", nomeArquivoBinario);

    // Abertura do arquivo para escrita.
    FILE *fpbin = fopen(nomeArquivoBinario, "r+b");

    // Confere se o arquivo existe e se é consistente.
    if (fpbin == NULL || !returnStatus(fpbin)) {
      printf("Falha no processamento do arquivo.\n");
      if (fpbin != NULL) // Fecha o arquivo caso o status não seja consistente
        fclose(fpbin);
      return 0;
    } else {
      // Arquivo foi aberto para escrita(inserção de registro), portanto seu
      // status fica como 0 enquanto ele estiver aberto
      setStatus(fpbin, "0");
    }
    int numVezes;
    scanf("%d", &numVezes);
    for (int i = 0; i < numVezes; i++)
      insereRegistros(fpbin);

    // Escrita no arquivo foi finalizada, retorna o status para 1
    setStatus(fpbin, "1");
    fclose(fpbin);
    binarioNaTela(nomeArquivoBinario);

  }
  // FUNCIONALIDADE 7
  else if (funcionalidade == 7) {
    scanf("%s ", nomeArquivoBinario);

    // Abertura do arquivo para escrita.
    FILE *fpbin = fopen(nomeArquivoBinario, "r+b");

    // Confere se o arquivo existe e se é consistente.
    if (fpbin == NULL || !returnStatus(fpbin)) {
      printf("Falha no processamento do arquivo.\n");
      if (fpbin != NULL) // Fecha o arquivo caso o status não seja consistente
        fclose(fpbin);
      return 0;
    } else {
      // Arquivo foi aberto para escrita(inserção de registro), portanto seu
      // status fica como 0 enquanto ele estiver aberto
      setStatus(fpbin, "0");
    }
    int numVezes;
    scanf("%d", &numVezes);
    for (int i = 0; i < numVezes; i++){
        int rrn, m;
        scanf("%d %d", &rrn, &m);
        atualizaRegistros(fpbin, rrn, m);

    }

    // Escrita no arquivo foi finalizada, retorna o status para 1
    setStatus(fpbin, "1");
    fclose(fpbin);
    binarioNaTela(nomeArquivoBinario);
  }

  return 0;
}

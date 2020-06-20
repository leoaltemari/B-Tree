#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "general.h"
#include"binarioNaTela.h"

/*
 * A funcao criaRegistroDados() eh responsavel por alocar os campos de tamanho
 * fixo na memoria. Parametros: RegDados * : Ponteiro para o registro de dados,
 * ele ja deve estar alocado na memoria antes de ser passado por parametro.
 * Retorno:
 *      void : nao retorna nada ja que o ponteiro eh passado por referencia e
 * nao valor.
 */

void criaRegistroDados(RegDados *r) {
  r->dataNascimento = malloc(sizeof(char) * 11);
  r->sexoBebe = malloc(sizeof(char) * 2);
  r->estadoMae = malloc(sizeof(char) * 3);
  r->estadoBebe = malloc(sizeof(char) * 3);
  return;
}

/*
 * A funcao preencheLixo() eh responsavel por preencher o atributo lixo do
 * registro de cabecalho com o caracter '$', para ser armazenado no arquivo
 * binario posteriormente. O atributo lixo eh necessario para que o registro de
 * cabecalho tenha 128 bytes. Parametros: RegCabecalho * : Ponteiro para o
 * registro de cabecalho. Retorno: void.
 */

void preencheLixo(RegCabecalho *r) {
  for (int i = 0; i < 111; i++) {
    r->lixo[i] = '$';
  }
  return;
}

void criaRegCabecalho(RegCabecalho *r) {
  preencheLixo(r);

  r->status = 0;
  r->RRNproxRegistro = 0;
  r->numeroRegistrosInseridos = 0;
  r->numeroRegistrosRemovidos = 0;
  r->numeroRegistrosAtualizados = 0;
  return;
}

/*
 * A funcao leituraArquivoTexto() eh responsavel por ler um arquivo do tipo
 * texto e retornar o ponteiro para ele. Parametros: char * : nome do arquivo
 * texto. Retorno: FILE * : ponteiro para o arquivo texto.
 */

FILE *leituraArquivoTexto(char *fileName) {
  FILE *fp;
  fp = fopen(fileName, "r");

  if (fp == NULL) {
    printf("Falha no carregamento do arquivo.\n");
    return NULL;
  }
  return fp;
}

/*
 * A funcao copiaArquivoTexto() eh responsavel por transformar um arquivo texto
 * em uma string apenas. Recebendo o ponteiro pro arquivo, ele eh transformado
 * em uma matriz de caracter(char **), onde cada linha da matriz corresponde a
 * uma linha do arquivo, e cada coluna da matriz corresponde a um caracter da
 * respectiva linha. Parametros: FILE * : ponteiro para o arquivo texto. int *
 * : variavel passada por referencia para que armazene o numero de linhas que o
 * arquivo texto possui. Retorno: char ** : Matriz de caracteres que corresponde
 * ao arquivo texto porem transformado para string.
 */
char **copiaArquivoTexto(FILE *fp, int *i) {
  char **str = malloc(sizeof(char *) * 1750);

  *i = 0;

  str[*i] = malloc(sizeof(char) * 90);
  // Vai ler as linhas do arquivo ate chegar no final dele,
  // qd chegar no final sai do while
  while (fgets(str[*i], 90, fp) != NULL) {
    *i = *i + 1; // A cada linha lida o i aumenta de 1;
    str[*i] = malloc(sizeof(char) * 90);
  }

  // Retorna a string do arquivo texto completo
  return str;
}

void desalocaArquivoTexto(char **a, int tam) {
  for (int i = 0; i < tam; i++) {
    free(a[i]);
  }

  free(a);
  a = NULL;
}



// Funcao de teste, somente para debugar qd precisar printar o que esta sendo
// armazenado no registro.
void imprimeReg(RegDados *r) {
  printf("%s ", r->cidadeMae);
  printf("%s ", r->cidadeBebe);
  printf("%d ", r->idNascimento);
  printf("%d ", r->idadeMae);
  printf("%s ", r->dataNascimento);
  printf("%s ", r->sexoBebe);
  printf("%s ", r->estadoMae);
  printf("%s\n", r->estadoBebe);
}

/*
 * A funcao atualizaCabecalho() eh responsavel por ir no comeco do arquivo
 * binario e escrever novamente os valores no cabecalho
 *
 * Parametros:
 *      FILE * : ponteiro para o arquivo binario(tem que ja estar aberto)
 *      RegCabecalho * : Struct Cabecalho passada como referencia, para ter
 * acesso aos valores, atualizados do cabecalho. Retorno:
 *
 */
void atualizaCabecalho(FILE *fpbin, RegCabecalho *r) {
  fseek(fpbin, 0, SEEK_SET);

  fwrite(&r->status, sizeof(char), 1, fpbin);
  fwrite(&r->RRNproxRegistro, sizeof(int), 1, fpbin);
  fwrite(&r->numeroRegistrosInseridos, sizeof(int), 1, fpbin);
  fwrite(&r->numeroRegistrosRemovidos, sizeof(int), 1, fpbin);
  fwrite(&r->numeroRegistrosAtualizados, sizeof(int), 1, fpbin);
  fwrite(&r->lixo, sizeof(char), 111, fpbin);
}

/*
 * A funcao getCabecalho() eh responsavel por ir no comeco do arquivo
 * binario e retornar o registro de cabecalho
 *
 * Parametros:
 *      FILE * : ponteiro para o arquivo binario(tem que ja estar aberto)
 */
void getCabecalho(FILE *fpbin, RegCabecalho *r) {
  fseek(fpbin, 0, SEEK_SET);

  fread(&r->status, sizeof(char), 1, fpbin);
  fread(&r->RRNproxRegistro, sizeof(int), 1, fpbin);
  fread(&r->numeroRegistrosInseridos, sizeof(int), 1, fpbin);
  fread(&r->numeroRegistrosRemovidos, sizeof(int), 1, fpbin);
  fread(&r->numeroRegistrosAtualizados, sizeof(int), 1, fpbin);
  fread(&r->lixo, sizeof(char), 111, fpbin);
}

/*
 * Função que retorna o status do arquivo a fim de analizar se eh consistente ou
 * não: lê o status no inicio do arquivo binário e o retorna covertendo para um
 * inteiro.
 */
int returnStatus(FILE *fpbin) {
  fseek(fpbin, 0, SEEK_SET);
  char status;
  fread(&status, sizeof(char), 1, fpbin);
  return (int)status - 48;
}

/*
 * Funcao que seta o valor do status no arquivo binario.
 */
void setStatus(FILE *fpbin, char _status[]) {
  fseek(fpbin, 0, SEEK_SET);
  fwrite(_status, sizeof(char), 1, fpbin);
  fseek(fpbin, 0, SEEK_SET);
  return;
}

/*
 *  Funcao getCampos() abaixo para pegar informacoes dos campos do registro,
 *  eh interna ao modulo.c, nao sendo possivel utiliza-la na main().
 *  OBS: Antes de chamar ela o ponteiro deve estar no comeco do registro
 * desejado e parametros passados para ela devem ser sempre por referencia,
 *       nunca por valor.
 */
void getCampos(FILE *fpbin, int *campo1, int *campo2, char *campo3,
               char *campo4, int *campo5, int *campo6, char *campo7,
               char *campo8, char *campo9, char *campo10) {

  // Get Campo1
  fread(campo1, sizeof(int), 1, fpbin);

  // Get Campo2
  fread(campo2, sizeof(int), 1, fpbin);

  if (*campo1 != -1) {
    // GetCampo3 = Cidade Mae
    char cidMae[(*campo1) + 1];
    fread(cidMae, sizeof(char), (uint)(*campo1), fpbin);
    cidMae[(*campo1)] = '\0';
    strcpy(campo3, cidMae);

    // Get Campo4 = Cidade Bebe
    char cidBebe[(*campo2) + 1];
    fread(cidBebe, sizeof(char), (uint)(*campo2), fpbin);
    cidBebe[(*campo2)] = '\0';
    strcpy(campo4, cidBebe);

    // Get campo5 = id Nascimento
    int posId = (97 - (*campo2) - (*campo1));
    fseek(fpbin, posId, SEEK_CUR);
    fread(campo5, sizeof(int), 1, fpbin);

    // Get campo6 = idade Mae
    fread(campo6, sizeof(int), 1, fpbin);

    // Get Campo 7 = Data de Nascimento
    char data[11];
    fread(data, sizeof(char), 10, fpbin);
    data[10] = '\0';
    strcpy(campo7, data);

    // Get Campo 8 = Sexo Bebe
    char sexo[2];
    fread(sexo, sizeof(char), 1, fpbin);
    sexo[1] = '\0';
    strcpy(campo8, sexo);

    // Get Campo 9 = Estado Mae
    char estadoMae[3];
    fread(estadoMae, sizeof(char), 2, fpbin);
    estadoMae[2] = '\0';
    strcpy(campo9, estadoMae);

    // Get Campo 10 = Estado Bebe
    char estadoBebe[3];
    fread(estadoBebe, sizeof(char), 2, fpbin);
    estadoBebe[2] = '\0';
    strcpy(campo10, estadoBebe);
  } else {
    // Se o registro atual estiver removido(campo1 = -1) ele pula para o proximo
    // shiftando o ponteiro do arquivo em 120 bytes(128 bytes - 8 bytes dos
    // campos 1 e 2).
    fseek(fpbin, 120, SEEK_CUR);
  }
  return;
}

/*
 * A funcao imprimeFrase() eh responsavel por imprimir uma frase dada a
 * formatacao desedaja no trabalho verificando SEMPRE registros nulos
 * Parametros:
 *      char *cidBebe : nome da cidade do bebe.
 *      char *estadoBebe : nome do estado do bebe.
 *      char *data : data de nascimento do bebe.
 *      char *sexo : sexo do bebe(MASCULINO, FEMININO ou IGNORADO)
 * Retorno:
 *      Nao ha retorno.
 * Formatacao:
 *      "Nasceu em CIDADEBEBE/ESTADOBEBE, em DATA, um bebe do sexo SEXO."
 */
void imprimeFrase(char *cidBebe, char *estadoBebe, char *data, char *sexo) {
  printf("Nasceu em ");

  if (cidBebe[0] != '\0') {
    printf("%s/", cidBebe);
  } else {
    printf("-/");
  }

  if (estadoBebe[0] != '\0') {
    printf("%s,", estadoBebe);
  } else {
    printf("-,");
  }

  printf(" em ");
  if (data[0] != '\0') {
    printf("%s,", data);
  } else {
    printf("-,");
  }

  printf(" um bebê de sexo ");
  if (strcmp(sexo, "0") == 0)
    printf("IGNORADO.\n");
  else if (strcmp(sexo, "1") == 0)
    printf("MASCULINO.\n");
  else
    printf("FEMININO.\n");
}

/*
 * A funcao leCamposBuscadoss() eh responsavel por armazenar o nome do campo e o
 * valor do campo que vai ser buscado, como pode ser uma busca combinada ela
 * sempre le 'm' vezes dado o m como o numero de campos que vao ser combinados
 * para a busca. Parametros: Busca *b: estrutuda para armazenar os nomes dos
 * campos e os valores dos campos. int m: numero de campos que vao ser
 * combinados. Retorno: Nao ha retorno.
 */
void leCamposBuscados(Busca *b, int m) {
  for (int i = 0; i < m; i++) {
    scanf("%s", b[i].nomeCampo);

    if (strcmp(b[i].nomeCampo, "cidadeMae") == 0 ||
        strcmp(b[i].nomeCampo, "cidadeBebe") == 0 ||
        strcmp(b[i].nomeCampo, "sexoBebe") == 0 ||
        strcmp(b[i].nomeCampo, "dataNascimento") == 0 ||
        strcmp(b[i].nomeCampo, "estadoMae") == 0 ||
        strcmp(b[i].nomeCampo, "estadoBebe") == 0) {
      b[i].flag = 1;
      scan_quote_string(b[i].campoStr);
    } else {
      b[i].flag = 0;
      scanf("%d", &b[i].campoInt);
    }
  }
  return;
}


/*
 * O arquivo general.h possui estruturas e funcoes que sao utilizadas por
 * varias funcionalidades, todos arquivos de funcionalidades devem
 * incluir o arquivo general.h
*/
#include <stdio.h>

// Estruturas
//typedef struct _regCabecalho RegCabecalho;
//typedef struct _regDados RegDados;

// Registro de Cabecalho
typedef struct _regCabecalho {
  char status;
  int RRNproxRegistro;
  int numeroRegistrosInseridos;
  int numeroRegistrosRemovidos;
  int numeroRegistrosAtualizados;
  char lixo[111];
} RegCabecalho;

// Registro de dados
typedef struct _regDados {
  // Campos de tamanho variavel
  int tamCidadeMae;  // Indicadores de
  int tamCidadeBebe; // tamanho
  char *cidadeMae;
  char *cidadeBebe;

  // Campos de tamanho fixo    // Os tamanhos são definidos na funcao
  // criaRegistroDados()
  int idNascimento;
  int idadeMae;
  char *dataNascimento;
  char *sexoBebe;
  char *estadoMae;
  char *estadoBebe;
} RegDados;


// Estrutua utilizada para fazer buscas combinadas
typedef struct _busca {
  char nomeCampo[30]; // Nome do campo buscado
  int flag;           // Flag para saber se o campo eh inteiro ou string
  int campoInt;       // Se for inteiro armazena inteiro
  char campoStr[97];  // Se for String armazena String
} Busca;


// Funcoes de arquivos
FILE *leituraArquivoTexto(char *fileName);
char **copiaArquivoTexto(FILE *fp, int *i);
void desalocaArquivoTexto(char **a, int tam);

// Funcoes get/set do status do arquivo
int returnStatus(FILE *fpbin);
void setStatus(FILE *fpbin, char _status[]);

// Registro de Cabecalho
void criaRegCabecalho(RegCabecalho *r);
void getCabecalho(FILE *fpbin, RegCabecalho *r);
void atualizaCabecalho(FILE *fpbin, RegCabecalho *r);

// Registro de dados
void criaRegistroDados(RegDados *r);

void getCampos(FILE *fpbin, int *campo1, int *campo2, char *campo3,
               char *campo4, int *campo5, int *campo6, char *campo7,
               char *campo8, char *campo9, char *campo10);

void imprimeFrase(char *cidBebe, char *estadoBebe, char *data, char *sexo);

void leCamposBuscados(Busca *b, int m);



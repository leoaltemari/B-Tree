#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

#include"general.h"
#include"arvore_B.h"
#include"funcionalidade_1.h"
#include"funcionalidade_2.h"
#include"funcionalidade_3.h"
#include"funcionalidade_4.h"
#include"funcionalidade_5.h"
#include"funcionalidade_6.h"
#include"funcionalidade_7.h"
#include"funcionalidade_8.h"

#include"funcionalidade_10.h"


// Funcoes de arquivos
FILE *leituraArquivoTexto(char *fileName);
char **copiaArquivoTexto(FILE *fp, int *i);
void desalocaArquivoTexto(char **a, int tam);

// Funcoes get/set do status do arquivo
int returnStatus(FILE *fpbin);
void setStatus(FILE *fpbin, char _status[]);


// Func1
void copiaDados(FILE *fpbin, char **fptxt, int tam);

// Func2
void readRegs(FILE *fpbin);

// Func3
void buscaCombinada(FILE *fpbin, int m);

// Func4
void buscaRRN(FILE *fpbin, int rrn);

// Func5
int removeRegistros(FILE *fpbin, int m);

// Func6
void insereRegistros(FILE *fpbin, int *idNascimento, int *RRNInserido);

// Func7
void atualizaRegistros(FILE *fpbin, int rrn, int m);

// Func8
void montaArquivo(FILE *btBin, BT_regCabecalho *regCab);
int driver(FILE *fpbin, FILE *btBin);

// Func10
int insereRegistroBTree(FILE *fpbin, FILE *btBin);


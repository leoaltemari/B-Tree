#include<stdio.h>
#include<stdlib.h>


#include "arvore_B.h"
#include "funcionalidade_6.h"
#include "funcionalidade_10.h"


/*
 * A funcao insereRegistroBTree() eh responsavel por adicionar um registro ao
 * arquivo de dados atraves da funcao insereRegistros() e tambem no arquivo de
 * indice arvore B atraves da funcao insertBTree().
 * Parametros:
 *      FILE *fpbin: ponteiro para o arquivo de dados.
 *      FILE *btBin: ponteiro para o arquivo de indice arvore B.
 * Retorno:
 *      Retorna 0 se algum dos arquivos nao estiver aberto corretamente.
 *      Retorna 1 caso o registro seja inserido tanto no arquivo de dados quanto
 *      no arquivo de indice.
 *
 * OBS: Sempre deve passar arquivos previamente abertos para essa funcao, ela nao
 *      trata a abertuda dos arquivos.
*/
int insereRegistroBTree(FILE *fpbin, FILE *btBin) {
    // Arquivos nao foram abertos corretamente
    if(fpbin == NULL || btBin == NULL)
        return 0;

    // Cria registro de cabecalho em memoria
    BT_regCabecalho *bt_regCab = malloc(sizeof(BT_regCabecalho));
    getBTRegCabecalho(btBin, bt_regCab);

    // Variaveis para adicionar o idNascimento em KEY e o rrn desse idNascimento em KEY_RRN
    int KEY;
    int KEY_RRN;

    // Insere o novo registro no arquivo de dados, retornando nos parametros KEY e KEY_RRN os dados
    // nescessarios para fazer a insercao no arquivo de indice arvore B.
    insereRegistros(fpbin, &KEY, &KEY_RRN);

    insertBTree(btBin, bt_regCab, KEY, KEY_RRN);

    // Atualiza cabecalho
    setBTRegCabecalho(btBin, bt_regCab);
    free(bt_regCab);    // Libera memoria utilizada.

    return 1;
}

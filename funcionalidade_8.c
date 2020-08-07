#include<stdio.h>
#include<stdlib.h>

#include"funcionalidade_8.h"
#include"general.h"

void montaArquivo(FILE *btBin, BT_regCabecalho *regCab) {
    // Cria registro de cabecalho com o valor inicial de cada campo
    criaBTRegCabecalho(regCab);

    // Escreve no arquivo o registro de cabecalho
    setBTRegCabecalho(btBin, regCab);
    return;
}

/*
 *  Funcao para recuperar o id e o campo1 do registro do arquivo de Dados.
 * sempre que essa funcao for chamada o ponteiro do arquivo deve estar no inicio do
 * registro que se quer recuperar o id e o campo1.
*/
void getId(FILE *fpbin, int *id, int *campo1) {
    fread(campo1, sizeof(int), 1, fpbin);
    // Ponteiro para o campo idNascimento
    fseek(fpbin, 101, SEEK_CUR);

    fread(id, sizeof(int), 1, fpbin);
    // Ponteiro para o fim do registro
    fseek(fpbin, 19, SEEK_CUR);
    return;
}


/*
 * A funcao driver() eh responsavel por controlar tanto a chave recuperada do arquivo de dados
 * quanto controlar se houve ou nao uma promocao na insercao dessa chave, para assim, criar-se
 * uma nova raiz para a arvore B.
 * Antes de iniciar as insercoes, criase estruturas, em memoria, para representar tanto o registro
 * de cabecalho do arquivo de dados quanto o registro de cabecalho do arquivo binario da arvore B.
*/
int driver(FILE *fpbin, FILE *btBin) {
    // Cria registro de cabecalhos
    BT_regCabecalho *bt_regCab = malloc(sizeof(BT_regCabecalho));
    montaArquivo(btBin, bt_regCab);

    RegCabecalho *fp_regCab = malloc(sizeof(RegCabecalho));
    criaRegCabecalho(fp_regCab);
    getCabecalho(fpbin, fp_regCab);
    // Neste ponto os dois ponteiros estao no final do registro de cabecalho
    // de ambos os arquivos

    int id, campo1;
    // Percorre TODOS os registro do arquivo de dados
    for(int i  = 0; i < fp_regCab->RRNproxRegistro; i++) {
        getId(fpbin, &id, &campo1); // Recurpera somente os dados que irao ser utilizados

        // Checa se o registro nao esta logicamente removido
        if(campo1 != -1) {
            int KEY = id;
            int KEY_RRN = i;

            // Insere os dados na arvore
            insertBTree(btBin, bt_regCab, KEY, KEY_RRN);
        }
    }

    // Seta status do arquivo para 1;
    bt_regCab->status[0] = '1';
    bt_regCab->status[1] = '\0';

    // Escreve o registro de cabecalho de volta no arquivo da arvore B
    setBTRegCabecalho(btBin, bt_regCab);

    // Libera memoria utilizada
    free(bt_regCab);
    free(fp_regCab);
    return 1;
}

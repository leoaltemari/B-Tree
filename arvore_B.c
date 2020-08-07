#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>

#include "arvore_B.h"

/*
 * A funcao preencheLixoBT() eh responsavel por preencher uma string com caracteres -1.
 * Parametros:
 *      char *str: string que sera preenchida
 * Retorno:
 *      nao ha retorno
 * Obs.: Essa funcao serve exclusivamente para criar o registro de cabecalho
 *       do arquivo de indice, nao utiliza-la em nenhum outro lugar, visto que
 *       ela esta hardcodada para preencher uma string de 55 posicoes.
*/
void preencheLixoBT(char *str) {
    for(int i = 0; i < 55; i++) {
        str[i] = '$';
    }
    return;
}

/*
 * A funcao criaBTRegCabecalho() eh responsavel por criar, em memoria, uma representacao
 * do registro de cabecalho do arquivo da arvore-B.
 * Valores inteiros sao inicializados com 0(com excecao da raiz que inicializa com -1,
 * ja que 0 eh um valor possivel para a raiz) e strings sao inicializadas com o caracter '0'.
 * Parametros:
 *      nao ha parametros.
 * Retorno:
 *      BT_regCabecalho *: retorna um ponteiro com o registro de cabecalho criado em memoria
*/
int criaBTRegCabecalho(BT_regCabecalho *r) {

    r->status[0] = '0';
    r->status[1] = '\0';
    r->noRaiz = -1;
    r->nroNiveis = 0;
    r->proxRRN = 0;
    r->nroChaves = 0;

    preencheLixoBT(r->lixo);

    return 1;
}


/*
 * A funcao getBTRegCabecalho() eh responsavel por copiar os dados, em memoria, do registro de cabecalho
 * do arquivo em uma estrutua passada por parametro.
*/
void getBTRegCabecalho(FILE *btBin, BT_regCabecalho *r) {
    fseek(btBin, 0, SEEK_SET);

    fread(&r->status, sizeof(char), 1, btBin);
    r->status[1] = '\0';
    fread(&r->noRaiz, sizeof(int), 1, btBin);
    fread(&r->nroNiveis, sizeof(int), 1, btBin);
    fread(&r->proxRRN, sizeof(int), 1, btBin);
    fread(&r->nroChaves, sizeof(int), 1, btBin);
    fread(r->lixo, sizeof(char), 55, btBin);

    fseek(btBin, 0, SEEK_SET);

    return;
}

/*
 * A funcao setBTRegCabecalho() eh responsavel por copiar os dados da estrutura que representa
 * o registro de cabecalho, em memoria, para o registro de cabecalho da arvore B passada por parametro.
*/
void setBTRegCabecalho(FILE *btBin, BT_regCabecalho *r) {
    fseek(btBin, 0, SEEK_SET);

    fwrite(&r->status, sizeof(char), 1, btBin);
    fwrite(&r->noRaiz, sizeof(int), 1, btBin);
    fwrite(&r->nroNiveis, sizeof(int), 1, btBin);
    fwrite(&r->proxRRN, sizeof(int), 1, btBin);
    fwrite(&r->nroChaves, sizeof(int), 1, btBin);
    fwrite(r->lixo, sizeof(char), 55, btBin);

    fseek(btBin, 0, SEEK_SET);

    return;
}

// Funcao get somente para o valor da raiz
int getRaiz(FILE *btBin) {
    fseek(btBin, 1, SEEK_SET);

    int root;
    fread(&root, sizeof(int), 1, btBin);

    fseek(btBin, 0, SEEK_SET);

    return root;
}

/*
 * A funcao getPage() eh responsavel por copiar os campos de uma pagina de disco, que esta no arquivo
 * da arvore B para a memoria. Para isso cria-se uma estrutura para armazenar esses dados(Page *)
 * e a retorna depois de preenche-la.
 * Parametros:
 *      FILE *btBin: ponteiro para o arquivo binario da arvoreB.
 *
 * Retorno:
 *      Page *: retorna um ponteiro para a estrutura que representa a pagina de disco em memoria.
*/
Page *getPage(FILE *btBin) {

    //todo: corrigir vazamento aqui
    Page *p = malloc(sizeof(Page));

    // Read nivel and n
    fread(&p->nivel, sizeof(int), 1, btBin);
    fread(&p->n, sizeof(int), 1, btBin);

    // Read all the keys
    for(int i = 0; i < ORDER-1; i++) {
        fread(&p->keys[i].key, sizeof(int), 1, btBin);
        fread(&p->keys[i].binFileRRN, sizeof(int), 1, btBin);
    }

    // Read all the children
    for(int i = 0; i < ORDER; i++) {
        fread(&p->child[i], sizeof(int), 1, btBin);
    }

    return p;
}


/*
 * A funcao setPage() eh responsavel por  escrever uma pagina que esta
 * representada na memoria no arquivo da arvoreB.
 * Parametros:
 *      FILE *btBin: ponteiro para o arquivo binario da arvoreB.
 *      Page *page: ponteiro para a estrutura que representa a pagina de disco em memoria.
 * Retorno:
 *      nao ha retorno.
 * OBS.: Para utilizar esta funcao deve-se antes de chama-la setar com fseek o ponteiro
 * para a regiao que deseja escrever a pagina, ou seja, o byte offset zero daquela
 * pagina no arquivo binario.
*/
void setPage(FILE *btBin, Page *page) {
    if(page == NULL)
        return;

    fwrite(&page->nivel, sizeof(int), 1, btBin);
    fwrite(&page->n, sizeof(int), 1, btBin);

    for(int i = 0; i < ORDER-1; i++) {
        fwrite(&page->keys[i].key, sizeof(int), 1, btBin);
        fwrite(&page->keys[i].binFileRRN, sizeof(int), 1, btBin);
    }

    for(int i = 0; i < ORDER; i++) {
        fwrite(&page->child[i], sizeof(int), 1, btBin);
    }
    return;
}

/*
 * A funcao checkPosition eh responsavel por checar em qual posicao a KEY, passada por parametro,
 * se encaixaria na pagina, tambem passada por parametro.
 * A posicao que KEY deveria estar eh retornada pela funcao.
*/
int checkPosition(Page *p, int numKeys, int KEY) {
    int POS = -1;
    int lastChecked = -1;
    for(int i = 0; i < numKeys; i++) {
        if(p->keys[i].key == KEY) {
            free(p);
            return 0;
        } else if(lastChecked == -1) {
            if(KEY < p->keys[i].key) {
                POS = i;
            } else  if(KEY > p->keys[i].key){
                POS = i+1;
            }
        } else {
            if(KEY < p->keys[i].key && KEY > lastChecked) {
                POS = i;
            } else  if(KEY > p->keys[i].key){
                POS = i+1;
            }
        }
        lastChecked = p->keys[i].key;
    }
    return POS;
}

/*
 * A  funcao insertKey() eh responsavel por inserir uma KEY passada por parametro
 * no lugar certo, sempre considerando a ordem crescente das KEYS.
*/
int insertKey(Page *p, int KEY, int KEY_RRN, int RRN) {
    int auxKey = KEY;
    int auxKeyRRN = KEY_RRN;
    int auxRRN = RRN;

    int changeKey;
    int changeKeyRRN;
    int changeRRN;

    // Insertion sort to the key
    for(int i = 0; i < p->n ; i++) {
        if(auxKey < p->keys[i].key) {
            changeKey = auxKey;
            changeKeyRRN = auxKeyRRN;
            changeRRN = auxRRN;

            auxKey = p->keys[i].key;
            auxKeyRRN = p->keys[i].binFileRRN;
            auxRRN = p->child[i+1];

            p->keys[i].key = changeKey;
            p->keys[i].binFileRRN = changeKeyRRN;
            p->child[i+1] = changeRRN;
        }
    }

    p->keys[p->n].key = auxKey;
    p->keys[p->n].binFileRRN = auxKeyRRN;
    p->child[p->n+1] = auxRRN;
    return 1;
}

/*
 * A  funcao insertKeyWorkingPage() eh responsavel por inserir uma KEY passada por parametro
 * no lugar certo de uma Working Page, sempre considerando a ordem crescente das KEYS.
*/
int insertKeyWorkingPage(WorkingPage *p, int KEY, int KEY_RRN, int RRN) {
    int auxKey = KEY;
    int auxKeyRRN = KEY_RRN;
    int auxRRN = RRN;

    int changeKey;
    int changeKeyRRN;
    int changeRRN;

    // Insertion sort to the key
    for(int i = 0; i < p->n-1; i++) {
        if(auxKey < p->keys[i].key) {
            changeKey = auxKey;
            changeKeyRRN = auxKeyRRN;
            changeRRN = auxRRN;

            auxKey = p->keys[i].key;
            auxKeyRRN = p->keys[i].binFileRRN;
            auxRRN = p->child[i+1];

            p->keys[i].key = changeKey;
            p->keys[i].binFileRRN = changeKeyRRN;
            p->child[i+1] = changeRRN;
        }
    }

    p->keys[p->n-1].key = auxKey;
    p->keys[p->n-1].binFileRRN = auxKeyRRN;
    p->child[p->n] = auxRRN;
    return 1;
}

/*
 * A funcao copyPage() eh responsavel por copiar todo conteudo de uma pagina em uma
 * WorkingPage, ambas passadas por parametro.
*/
void copyPage(Page *src, WorkingPage *dest) {
    dest->nivel = src->nivel;
    dest->n = src->n+1;

    for(int i = 0; i < src->n; i++) {
        dest->keys[i].key = src->keys[i].key;
        dest->keys[i].binFileRRN = src->keys[i].binFileRRN;
    }

    for(int i = 0; i < src->n+1; i++) {
        dest->child[i] = src->child[i];
    }
    return;
}

/*
 * Funcao split() para gerar 2 novas paginas, e tambem selecionar uma chave a ser promovida.
 * Para isso usa uma Working page que fica com todo o conteudo e possui uma chave a mais.
 * A chave a ser promovida eh sempre a da posicao 3(midlekey) do vetor de chves.
*/
int split(int I_KEY, int I_KEY_RRN, int I_RRN, Page *page, int *PROMO_KEY,
          int *PROMO_KEY_RRN, int *PROMO_R_CHILD,
          Page *newPage, BT_regCabecalho *cab) {
    WorkingPage *wpage = malloc(sizeof(WorkingPage));
    copyPage(page, wpage);
    insertKeyWorkingPage(wpage, I_KEY, I_KEY_RRN, I_RRN);

    int midleKey = wpage->n/2;
    *PROMO_KEY = wpage->keys[midleKey].key;
    *PROMO_KEY_RRN = wpage->keys[midleKey].binFileRRN;

    *PROMO_R_CHILD = cab->proxRRN;

    int numKeys = page->n;
    for(int i = 0; i < numKeys; i++) {
        if(i < midleKey) {
            page->keys[i].key = wpage->keys[i].key;
            page->keys[i].binFileRRN = wpage->keys[i].binFileRRN;
            page->child[i] = wpage->child[i];
            if(i == midleKey-1) {
                page->child[i+1] = wpage->child[i+1];
            }
        } else {
            page->keys[i].key = -1;
            page->keys[i].binFileRRN = -1;
            page->n--;
        }
    }

    newPage->n = 0;
    int pos = newPage->n;
    for(int i = midleKey+1; i < wpage->n; i++) {
        newPage->keys[pos].key = wpage->keys[i].key;
        newPage->keys[pos].binFileRRN = wpage->keys[i].binFileRRN;
        newPage->child[pos] = wpage->child[i];
        if(i == wpage->n-1) {
            newPage->child[pos+1] = wpage->child[i+1];
        }
        newPage->n++;
        pos++;
    }

    // Preenche demais chaves com -1
    for(int i = pos; i < ORDER-1; i++) {
        newPage->keys[i].key = -1;
        newPage->keys[i].binFileRRN = -1;
        newPage->child[i+1] = -1;
    }
    free(wpage);
    return 1;
}

// Funcao para preencher filhos que nao existem com o valor nulo.
void fillChildren(Page *p) {
    int n = p->n;

    for(int i = n+1; i < ORDER; i++) {
        p->child[i] = -1;
    }
    return;
}

/*
 * A funcao recursive insertion insere uma nova chave em uma pagina de disco que eh uma folha
 * retornando assim uma NOT_PROMOTION ou retona pelos parametros uma chave a ser promovida e o
 * filho da direita dessa chave a ser promovida, retornando assim PROMOTION.
*/
int recursiveInsertion(FILE *btBin, int CURRENT_RRN, int KEY, int KEY_RRN,
                       int *PROMO_R_CHILD, int *PROMO_KEY, int *PROMO_RRN,
                       BT_regCabecalho *regCab) {
    // Parametros invalidos
    if(btBin == NULL || CURRENT_RRN < -1 || regCab == NULL)
        return 0;

    // Checa se o rrn passado vei a partir de uma folha
    if(CURRENT_RRN == -1) {
        *PROMO_KEY = KEY;
        *PROMO_RRN = KEY_RRN;
        *PROMO_R_CHILD = -1;
        return PROMOTION;
    }

    // Le do arquivo a pagina de disco referente ao RRN
    fseek(btBin, (CURRENT_RRN+1) * 72, SEEK_SET);
    Page *p = getPage(btBin);

    int numKeys = p->n;

    // Checa em qual posicao a chave deveria ser inserida
    int POS = checkPosition(p, numKeys, KEY);

    int nextRRN = POS == -1? -1 : p->child[POS];
    int P_B_RRN = -1;
    int P_B_KEY = -1;
    int P_B_KEY_RRN = -1;

    // Se a pagina nao for uma folha, desaloca da memoria
    if(nextRRN != -1) {
        free(p);
    }

    // Seque para o proximo no' da arvore
    int returnValue = recursiveInsertion(btBin, nextRRN, KEY,
                                         KEY_RRN, &P_B_RRN, &P_B_KEY,
                                         &P_B_KEY_RRN, regCab);

    // Nao encontrou lugar para inserir a nova KEY
    if(returnValue == 0) {
        return NOT_PROMOTION;
    }
    // Se ainda tiver espaco na pagina atual para inserir a KEY
    else if(numKeys < MAXKEYS) {
        free(p);

        fseek(btBin, (CURRENT_RRN+1) * 72, SEEK_SET);
        p = getPage(btBin);

        insertKey(p, P_B_KEY, P_B_KEY_RRN, P_B_RRN);
        p->n++;

        fseek(btBin, (CURRENT_RRN+1) * 72, SEEK_SET);
        setPage(btBin, p);

        free(p);
        return NOT_PROMOTION;
    // Se nao tiver espaco para inserir, realiza um split 1-2, sempre criando uma
    // nova pagina a direita da pagina atual
    } else {
        Page *newPage = malloc(sizeof(Page));

        fseek(btBin, (CURRENT_RRN+1) * 72, SEEK_SET);
        p = getPage(btBin);

        newPage->nivel = p->nivel;

        // Guarda em PROMO_KEY, a chave que sera promovida pro no de cima da arvore
        split(P_B_KEY, P_B_KEY_RRN, P_B_RRN, p,
              PROMO_KEY, PROMO_RRN, PROMO_R_CHILD,
              newPage, regCab);

        // Preenche os filhos que sao nulos
        fillChildren(p);
        fillChildren(newPage);

        // Guarda no arquivo de volta as paginas ja splitadas
        fseek(btBin, (CURRENT_RRN+1) * 72, SEEK_SET);
        setPage(btBin, p);
        fseek(btBin, (*PROMO_R_CHILD+1) * 72, SEEK_SET);
        setPage(btBin, newPage);

        // Como criou-se uma nova pagina no arquvio, o RRN da proxima pagina
        // deve ser incrementado
        regCab->proxRRN++;


        // Desaloca toda memoria utilizada
        free(newPage);
        free(p);
        return PROMOTION;
    }
}

// Funcao que cria a primeira raiz do arquivo
Page *criaPrimeiraRaiz(int id, int binFileRRN) {
    // Cria uma pagina para o no raiz
    Page *p = malloc(sizeof(Page));
    for(int i = 0; i < ORDER-1; i++) {
        p->keys[i].key = -1;
        p->keys[i].binFileRRN = -1;
    }
    p->n = 1;

    // Adiciona o id ao no raiz
    p->keys[0].key = id;
    p->keys[0].binFileRRN = binFileRRN;

    // Preenche os descendentes do no raiz com -1
    for(int i = 0; i < ORDER; i++) {
        p->child[i] = -1;
    }
    p->nivel = 1; // nivel da raiz eh sempre 1 quando iniciada a arvore

    return p;
}

Page *criaRaiz(int PROMO_KEY, int PROMO_KEY_RRN,
               int PROMO_R_CHILD, BT_regCabecalho *bt_regCab) {
    Page *newRoot = malloc(sizeof(Page));
    newRoot->nivel = bt_regCab->nroNiveis+1;
    newRoot->n = 1;

    // New root data
    newRoot->keys[0].key = PROMO_KEY;      // Root key
    newRoot->keys[0].binFileRRN = PROMO_KEY_RRN;
    newRoot->child[0] = bt_regCab->noRaiz; // LEFT child
    newRoot->child[1] = PROMO_R_CHILD;     // RIGHT child

    // Preenche chaves restantes com lixo
    for(int i = 2; i < ORDER; i++) {
        newRoot->child[i] = -1;
        if(i-1 < ORDER-1) {
            newRoot->keys[i-1].key = -1;
            newRoot->keys[i-1].binFileRRN = -1;
        }
    }
    return newRoot;
}

/*
 * A funcao insertBTree() eh responsavel por inserir uma novo par de chave na arvore, que corresponde a
 * KEY = idNascimento
 * KEY_RRN = RRN do registro de dados que contem a KEY
*/
int insertBTree(FILE *btBin, BT_regCabecalho *bt_regCab, int KEY, int KEY_RRN) {
    if(KEY < 0 || KEY_RRN < 0 || btBin == NULL || bt_regCab == NULL)
        return 0;   // Retorna erro

    if(bt_regCab->proxRRN == 0) { // Primeiro elemento inserido
            Page *p = criaPrimeiraRaiz(KEY, KEY_RRN);

            fseek(btBin, (bt_regCab->proxRRN+1)*72, SEEK_SET);
            setPage(btBin, p);  // Escreve a raiz no arquivo

            free(p);

            bt_regCab->noRaiz = bt_regCab->proxRRN;
            bt_regCab->proxRRN++;
            bt_regCab->nroNiveis = 1;
    }
    // Demais elementos inseridos
    else {
        int ROOT = bt_regCab->noRaiz;
        int PROMO_KEY = -1;
        int PROMO_KEY_RRN = -1;
        int PROMO_R_CHILD = -1;

        if(recursiveInsertion(btBin, ROOT, KEY, KEY_RRN,
                              &PROMO_R_CHILD, &PROMO_KEY, &PROMO_KEY_RRN,
                              bt_regCab) == PROMOTION) {

            Page *newRoot = criaRaiz(PROMO_KEY, PROMO_KEY_RRN, PROMO_R_CHILD, bt_regCab);  // Cria um novo no raiz em memoria

            // Arruma o registro de cabecalho
            int newRootRRN = bt_regCab->proxRRN;
            bt_regCab->proxRRN++;
            bt_regCab->noRaiz = newRootRRN;
            bt_regCab->nroNiveis++;

            // Escreve a nova raiz no arquivo
            fseek(btBin, (bt_regCab->noRaiz+1) * 72, SEEK_SET);
            setPage(btBin, newRoot);

            free(newRoot);
        }
    }
    // A cada chave inserida aumenta o nro de chaves
    bt_regCab->nroChaves++;

    // Retorna sucesso
    return 1;
}




#include <stdio.h>

// Ordem da arvore-B
#define ORDER 6
#define MAXKEYS ORDER-1
#define PROMOTION 1
#define NOT_PROMOTION 0

// Registro que representa, em memoria, o registro de cabecalho do arquivo da arvore B
struct btRegCabecalho {
    char status[2];
    int noRaiz;
    int nroNiveis;
    int proxRRN;
    int nroChaves;
    char lixo[55];
};

// Struc que representa nossa KEY, sempre com a key(idNascimento) e o
// RRN referente a esse idNascimento no arquivo de dados(Arquivão)
struct pair {
    int key;
    int binFileRRN;
};


// Struct que representa uma pagina de disco, em memoria.
struct page {
    int nivel;
    int n;
    struct pair keys[MAXKEYS];
    int child[ORDER];
};

// Struct que representa uma Working Page, possui uma chave e um filho a mais
struct wpage {
    int nivel;
    int n;
    struct pair keys[MAXKEYS+1];
    int child[ORDER+1];
};

// Typedefs
typedef struct btRegCabecalho BT_regCabecalho;
typedef struct page Page;
typedef struct wpage WorkingPage;


// Methods
int criaBTRegCabecalho(BT_regCabecalho *r);
void getBTRegCabecalho(FILE *btBin, BT_regCabecalho *r);
void setBTRegCabecalho(FILE *btBin, BT_regCabecalho *r);
Page *getPage(FILE *btBin);
void setPage(FILE *btBin, Page *page);
int recursiveInsertion(FILE *btBin, int CURRENT_RRN, int KEY,
                       int KEY_RRN, int *PROMO_R_CHILD, int *PROMO_KEY,
                       int *PROMO_RRN, BT_regCabecalho *regCab);
int insertBTree(FILE *btBin, BT_regCabecalho *bt_regCab, int KEY, int KEY_RRN);


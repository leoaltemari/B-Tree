#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include "funcionalidade_1.h"
#include "general.h"


/*
 * AS funcoeS get abaixo sao responsaveis por pegar uma linha do arquivo, na
 * forma de string(char *) e armazenarem somente aquilo que corresponde ao
 * pedido da funcao, por exemplo, a funcao getCidadeMae() recebe a linha do
 * arquivo e armazena no parametro cidadeMae passado por referencia somente a
 * cidade da mae daquela linha. Parametros: char *dados : string correspondente
 * a linha do arquivo. char * : String passada por referencia para armazenar
 * aquilo que esta sendo buscado em cada funcao get. Retorno: void.
 */
void getCidadeMae(char *dados, char *cidadeMae) {
  int tamLinha = (int)strlen(dados);

  int contCampos = 0;
  int i = 0;
  int pos = 0;
  while (contCampos < 1 && i < tamLinha) {
    if (dados[i] == ',') {
      contCampos++;
    } else {
      cidadeMae[pos] = dados[i];
      pos++;
    }
    i++;
  }
  cidadeMae[pos] = '\0';
  return;
}

void getCidadeBebe(char *dados, char *cidadeBebe) {
  int tamLinha = (int)strlen(dados);
  int contCampos = 0;
  int i = 0;
  int pos = 0;
  while (contCampos < 2 && i < tamLinha) {
    if (dados[i] == ',') {
      contCampos++;
    } else if (contCampos == 1) {
      cidadeBebe[pos] = dados[i];
      pos++;
    }
    i++;
  }
  cidadeBebe[pos] = '\0';
  return;
}

void getIdIdadeMae(char *dados, int *idadeMae) {
  int tamLinha = (int)strlen(dados);
  int contCampos = 0;
  int i = 0;
  int pos = 0;
  char aux[3];
  aux[2] = '\0';

  while (contCampos < 4 && i < tamLinha) {
    if (dados[i] == ',') {
      contCampos++;
    } else if (contCampos == 3) {
      aux[pos] = dados[i];
      pos++;
    }
    i++;
  }

  *idadeMae = atoi(aux);
  return;
}

void getDataNascimento(char *dados, char *dataNascimento) {

  int tamLinha = (int)strlen(dados);
  int contCampos = 0;
  int i = 0;
  int pos = 0;
  while (contCampos < 5 && i < tamLinha) {
    if (dados[i] == ',') {
      contCampos++;
    } else if (contCampos == 4) {
      dataNascimento[pos] = dados[i];
      pos++;
    }
    i++;
  }
  dataNascimento[pos] = '\0';
  return;
}

void getSexoBebe(char *dados, char *sexoBebe) {
  int tamLinha = (int)strlen(dados);
  int contCampos = 0;
  int i = 0;
  int pos = 0;
  while (contCampos < 6 && i < tamLinha) {
    if (dados[i] == ',') {
      contCampos++;
    } else if (contCampos == 5) {
      sexoBebe[pos] = dados[i];
      pos++;
    }
    i++;
  }
  sexoBebe[pos] = '\0';
  return;
}

void getEstadoMae(char *dados, char *estadoMae) {
  int tamLinha = (int)strlen(dados);
  int contCampos = 0;
  int i = 0;
  int pos = 0;
  while (contCampos < 7 && i < tamLinha) {
    if (dados[i] == ',') {
      contCampos++;
    } else if (contCampos == 6) {
      estadoMae[pos] = dados[i];
      pos++;
    }
    i++;
  }

  estadoMae[pos] = '\0';
}

void getEstadoBebe(char *dados, char *estadoBebe) {
  int tamLinha = (int)strlen(dados);
  int contCampos = 0;
  int i = 0;
  int pos = 0;
  while (contCampos < 8 && i < tamLinha) {
    if (dados[i] == ',') {
      contCampos++;
    } else if (contCampos == 7) {
      if (dados[i] != '\n') {
        estadoBebe[pos] = dados[i];
        pos++;
      }
    }
    i++;
  }
  estadoBebe[pos] = '\0';
  return;
}
/*
 * A funcao preencheRegistro() eh responsavel por pegar uma linha do arquivo
 * texto e transforma-la em um registro. Para isso eh criado uma variavel do
 * tipo RegDados e eh armazenado nela os valores da linha do arquivo passado por
 * parametro. Por exemplo, se eu passar a linha 1 do arquivo, ele ira criar um
 * RegDados e preencher os campos cidadeMae, cidadeBebe, estadoMae, sexoBebe,
 * etc. utilizanddo as funcoes get() ja citadas acima. Parametros: char ** :
 * matriz de caracter que corresponde ao arquivo texto na forma de string. int :
 * numero da linha que eu quero transformar em registro. Retorno: RegDados * :
 * retorna um ponteiro para um registro de dados, ja alocado e ja preenchido com
 * os valores da linha passada.
 */

RegDados *preencheRegistro(char **file, int fileLine) {
  char *_cidadeMae;
  char *_cidadeBebe;

  int _idNascimento;
  int _idadeMae;
  char *_dataNascimento;
  char *_sexoBebe;
  char *_estadoMae;
  char *_estadoBebe;

  // Getting cidade da mae
  _cidadeMae = malloc(sizeof(char) * 97);
  getCidadeMae(file[fileLine], _cidadeMae);

  // Getting cidade do bebe
  _cidadeBebe = malloc(sizeof(char) * 97);
  getCidadeBebe(file[fileLine], _cidadeBebe);

  // Getting id de Nascimento
  _idNascimento = fileLine;

  // Getting idade da mae
  getIdIdadeMae(file[fileLine], &_idadeMae);

  // Getting data de nascimento
  _dataNascimento = malloc(sizeof(char) * 11);
  getDataNascimento(file[fileLine], _dataNascimento);

  // Getting sexo do bebe
  _sexoBebe = malloc(sizeof(char) * 2);
  getSexoBebe(file[fileLine], _sexoBebe);

  // Getting estado da mae
  _estadoMae = malloc(sizeof(char) * 3);
  getEstadoMae(file[fileLine], _estadoMae);

  // Getting estado do Bebe
  _estadoBebe = malloc(sizeof(char) * 3);
  getEstadoBebe(file[fileLine], _estadoBebe);

  // Cria o registro e aloca na memora
  RegDados *reg = malloc(sizeof(RegDados));
  reg->tamCidadeMae = (int)strlen(_cidadeMae);
  reg->tamCidadeBebe = (int)strlen(_cidadeBebe);
  reg->cidadeMae = malloc(sizeof(char) * (uint)strlen(_cidadeMae));
  reg->cidadeBebe = malloc(sizeof(char) * (uint)strlen(_cidadeBebe));

  criaRegistroDados(reg);

  // Preenche o registro com os valores adquiridos
  strcpy(reg->cidadeMae, _cidadeMae);
  strcpy(reg->cidadeBebe, _cidadeBebe);
  reg->idNascimento = _idNascimento;
  reg->idadeMae = _idadeMae;
  strcpy(reg->dataNascimento, _dataNascimento);
  strcpy(reg->sexoBebe, _sexoBebe);
  strcpy(reg->estadoMae, _estadoMae);
  strcpy(reg->estadoBebe, _estadoBebe);

  // Liberando memoria usada
  free(_cidadeMae);
  free(_cidadeBebe);
  free(_dataNascimento);
  free(_sexoBebe);
  free(_estadoMae);
  free(_estadoBebe);

  return reg;
}


/*
 * AS funcoeS copia() sao responsaveis por pegar um valor no registro e DADOS e
 * copiar esse valor no arquivo binario atraves do fwrite. O valor copiado eh
 * sempre referente ao nome de cada funcao copia(), por exemplo a funcao
 * copiaCidades() eh responsavel por pegar os valores de tamanho de cada string
 * cidade(cidade da mae e cidade do bebe), passsar esses valores para o arquivo
 * binario no Campo 1 e Campo 2, depois eh feita a copia do nome de cada cidade
 * em si, armazenando primeiro o nome da cidade da MAE no Campo 3 e depois o
 * nome da cidade do BEBE no campo 4 do registro.
 *
 * Parametro :
 *      FILE * : ponteiro para o arquivo binario.
 *      RegDados * : ponteiro para a struct que faz o papel do registro para ter
 * acesso aos valores dos campos. retorno: void.
 */
void copiaCidades(FILE *fpbin, RegDados *regDados) {
  int citM = regDados->tamCidadeMae;
  int citB = regDados->tamCidadeBebe;

  // Tamanho cidade mae
  fwrite(&citM, sizeof(int), 1, fpbin);
  // Tamanho cidade bebe
  fwrite(&citB, sizeof(int), 1, fpbin);

  // Escreve cidade mae
  if (citM != 0) {
    fwrite(regDados->cidadeMae, sizeof(char), (uint)citM, fpbin);
  }

  // Escreve cidade bebe
  if (citB != 0) {
    fwrite(regDados->cidadeBebe, sizeof(char), (uint)citB, fpbin);
  }

  // Preenche os bytes que sobraram com lixo;
  char lixo = '$';
  int resto = 97 - citM - citB;
  if (resto > 0) {
    for (int i = 0; i < resto; i++) {
      fwrite(&lixo, sizeof(char), 1, fpbin);
    }
  }
  return;
}

void copiaIdNascimento(FILE *fpbin, RegDados *regDados) {
  int id = regDados->idNascimento;

  fwrite(&id, sizeof(int), 1, fpbin);

  return;
}

void copiaIdadeMae(FILE *fpbin, RegDados *regDados) {
  int idadeMae = regDados->idadeMae;
  int nulo = -1;

  if (idadeMae != 0) {
    fwrite(&regDados->idadeMae, sizeof(int), 1, fpbin);
  } else {
    fwrite(&nulo, sizeof(int), 1, fpbin);
  }
  return;
}

void copiaDataNascimento(FILE *fpbin, RegDados *regDados) {
  int sizeData = (int)strlen(regDados->dataNascimento);

  char *nulo = malloc(sizeof(char) * 10);
  strcpy(nulo, "$$$$$$$$$");

  if (sizeData != 0) {
    fwrite(regDados->dataNascimento, sizeof(char), 10, fpbin);
  } else {
    fwrite("\0", sizeof(char), 1, fpbin);
    fwrite(nulo, sizeof(char), 9, fpbin);
  }

  free(nulo);
  return;
}

void copiaSexoBebe(FILE *fpbin, RegDados *regDados) {
  if (strcmp(regDados->sexoBebe, "") != 0) {
    fwrite(regDados->sexoBebe, sizeof(char), 1, fpbin);
  } else {
    fwrite("0", sizeof(char), 1, fpbin);
  }

  return;
}

void copiaEstadoMae(FILE *fpbin, RegDados *regDados) {
  int sizeData = (int)strlen(regDados->estadoMae);

  char *nulo = malloc(sizeof(char) * 2);
  strcpy(nulo, "$");

  if (sizeData != 0) {
    fwrite(regDados->estadoMae, sizeof(char), 2, fpbin);
  } else {
    fwrite("\0", sizeof(char), 1, fpbin);
    fwrite(nulo, sizeof(char), 1, fpbin);
  }

  free(nulo);

  return;
}

void copiaEstadoBebe(FILE *fpbin, RegDados *regDados) {
  int sizeData = (int)strlen(regDados->estadoBebe);

  char *nulo = malloc(sizeof(char) * 2);
  strcpy(nulo, "$");

  if (sizeData != 0) {
    fwrite(regDados->estadoBebe, sizeof(char), 2, fpbin);
  } else {
    fwrite("\0", sizeof(char), 1, fpbin);
    fwrite(nulo, sizeof(char), 1, fpbin);
  }

  free(nulo);

  return;
}

/*
 * A funcao copiaDados() eh responsavel por pegar um arquivo texto e
 * transformalo em arquivo binario, respeitando o tamanho de cada campo e de
 * cada registro. Ao finalizar essa funcao o arquivo binario estara preenchido.
 * Parametros:
 *      FILE * : ponteiro para o arquvio binario(ele vai ser criado na main e
 * passado por parametro). char ** : String que contem o arquvio texto so que na
 * forma de string para facilitar. int tam : numero de linhas desse arquivo
 * texto, para saber quando parar de 'ler' ele. Retorno: void.
 *
 */
void copiaDados(FILE *fpbin, char **fptxt, int tam) {
  // Seta o ponteiro para o comeco do arquivo, caso ainda nao esteja
  fseek(fpbin, 0, SEEK_SET);

  // Registro de dados
  RegDados *regDados;

  // Registro de cabecalho
  RegCabecalho *regCab = malloc(sizeof(RegCabecalho));
  criaRegCabecalho(regCab); // inicia valores no registro de cabecalho

  // Arquivo vai comecar a ser gravado, portanto o status dele eh 0
  regCab->status = '0';
  atualizaCabecalho(
      fpbin, regCab); // Armazena os vaores do registro de cabecalho no arquivo
                      // binario, antes de comecar a adicionar registros.

  // Se o arquivo texto, passado por parametro nao estiver vazio, o arquivo
  // binario eh preenchido com o conteudo do arquivo texto. Se o arquivo texto
  // estiver vazio, somente o registro de cabecalho sera armazenado no arquivo
  // binario.
  if (strlen(fptxt[0]) != 0) {

    // Loop que percorre as linhas do arquivo texto, transformando-as em
    // registros
    for (int i = 1; i < tam; i++) {
      regDados =
          preencheRegistro(fptxt, i); // Pega os campos da linha do arquivo
                                      // texto e transforma em um registro

      // Copia os dados do registro no arquivo binario
      // Campo variavel(Campo 1, Campo 2, Campo 3, Campo 4)
      copiaCidades(fpbin, regDados); // 105 bytes    - 4 Bytes inteiro + 4 bytes
                                     // inteiro + 97 bytes char

      // Campos Fixos
      copiaIdNascimento(fpbin,
                        regDados); // 4 bytes      - 4 bytes inteiro   (Campo 5)
      copiaIdadeMae(fpbin,
                    regDados); // 4 bytes      - 4 bytes inteiro   (Campo 6)
      copiaDataNascimento(
          fpbin, regDados); // 10 bytes     - 10 bytes char     (Campo 7)
      copiaSexoBebe(fpbin,
                    regDados); // 1 byte       - 1 byte char       (Campo 8)
      copiaEstadoMae(fpbin, regDados); // 2 bytes      - 2 bytes char (Campo 9)
      copiaEstadoBebe(fpbin,
                      regDados); // 2 bytes      - 2 bytes char      (Campo 10)
                                 // Total = 105 + 23 = 128 Bytes por Registro

      // A cada registro inserido, atualiza o rrnProx e o numRegInseridos na
      // memoria somente.
      regCab->RRNproxRegistro += 1;
      regCab->numeroRegistrosInseridos += 1;
    }
  }

  // Terminada a insercao dos registros, o status muda para 1 e atualiza o
  // cabecalho novamente.
  regCab->status = '1';
  atualizaCabecalho(fpbin, regCab);
  free(regCab);
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include"funcionalidade_6.h"
#include"general.h"
#include"binarioNaTela.h"

/*
 * A função insereRegistros() eh responsavel por inserir um novo registro no fim
 * do arquivo binário e atualizar o cabeçalho
 * Parametros: FILE *fpbin : ponteiro para o arquivo binario.
 * Retorno: Não há retorno na função pois uma inserção nunca ira falhar.
 *
 * Retorna pelos parametros o idNascimento e o RRN em que o novo registro foi inserido.
 */
void insereRegistros(FILE *fpbin, int *idNascimento, int *RRNInserido) {
  /*
   * Variáveis auxiliares para armazenar o registro a ser inserido.
   * As variáveis foram inciadas com espaço para o \0 apenas para fins de
   * debug, na hora da inserção ele é excluido.
   */
  char cMae[48], cBebe[49], idN[5], idMae[4], dataNasc[11], sBebe[2], eMae[3],
      eBebe[3];
  int tamCidMae, tamCidBebe, id, idade;

  // Cópia do cabeçalho.
  RegCabecalho *rg = malloc(sizeof(RegCabecalho));
  getCabecalho(fpbin, rg);

  // Armazenamento dos campos do registro.
  scan_quote_string(cMae);
  scan_quote_string(cBebe);
  scan_quote_string(idN);
  scan_quote_string(idMae);
  scan_quote_string(dataNasc);
  scan_quote_string(sBebe);
  scan_quote_string(eMae);
  scan_quote_string(eBebe);

  /*
   * Conversão para inteiro das strings e tratamento dos dados caso seja nulo.
   * O campo idNascimento não é tratado visto que nunca é nulo.
   */
  id = atoi(idN);
  if (strcmp(idMae, "") == 0)
    idade = -1;
  else
    idade = atoi(idMae);

  // Armazenamento dos tamanhos de cada cidade.
  tamCidMae = (int)strlen(cMae);
  tamCidBebe = (int)strlen(cBebe);

  /*
   * Tratamento do lixo da string dataNascimento.
   * Verifica se está vazia comparando o tamanho da string com o tamanho em
   * bytes alocado, caso esteja vazia strlen() = 0 e sizeof() = 11, e entrao
   * preenche o lixo, caso não, nem executa o for.
   */
  char lixo = '$';
  for (int i = (int)strlen(dataNasc) + 1; i < (int)sizeof(dataNasc); i++)
    dataNasc[i] = '$';

  // Ajusta o ponteiro para o fim do arquivo e armazena os campos.
  fseek(fpbin, 0, SEEK_END);
  fwrite(&tamCidMae, sizeof(tamCidMae), 1, fpbin);
  fwrite(&tamCidBebe, sizeof(tamCidBebe), 1, fpbin);
  fwrite(&cMae, (uint)tamCidMae, 1, fpbin);
  fwrite(&cBebe, (uint)tamCidBebe, 1, fpbin);

  // Adiciona o lixo após os nomes da cidade.
  for (int i = 0; i < 97 - (tamCidMae + tamCidBebe); i++)
    fwrite(&lixo, sizeof(char), 1, fpbin);

  fwrite(&id, sizeof(id), 1, fpbin);
  *idNascimento = id; // Armazena o id no parametro da funcao

  fwrite(&idade, sizeof(idade), 1, fpbin);
  fwrite(&dataNasc, sizeof(char) * 10, 1, fpbin);

  // Tratamento para  o caso da entrada do sexo do bebe seja nulo.
  if (strcmp(sBebe, "") == 0)
    strcpy(sBebe, "0");
  fwrite(&sBebe, sizeof(char), 1, fpbin);

  // Tratamento para os casos das entradas dos estados sejam nulos.
  if (strcmp(eMae, "") == 0) {
    fwrite(&eMae, sizeof(char), 1, fpbin);
    fwrite(&lixo, sizeof(char), 1, fpbin);
  } else
    fwrite(&eMae, sizeof(char) * 2, 1, fpbin);
  if (strcmp(eBebe, "") == 0) {
    fwrite(&eBebe, sizeof(char), 1, fpbin);
    fwrite(&lixo, sizeof(char), 1, fpbin);
  } else
    fwrite(&eBebe, sizeof(char) * 2, 1, fpbin);

  /*
   * Incremento das informações e atualização do cabeçalho, além do free na
   * cópia.
   */
  *RRNInserido = rg->RRNproxRegistro; // armazena o rrn do registro que foi inserido antes de alterar o cabecalho

  rg->RRNproxRegistro++;
  rg->numeroRegistrosInseridos++;
  atualizaCabecalho(fpbin, rg);
  free(rg);
}


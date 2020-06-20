#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include"funcionalidade_4.h"
#include"general.h"


/*
 * A funcao buscaRRN() eh reponsavel por buscar um registro dado o seu rrn e
 * printar as informacoes na formatacao desejada. Parametros: FILE *fpbin:
 * ponteiro para o arquivo binario int rrn: valor do rrn do registro buscado.
 * Retorno:
 *      nao ha retorno na funcao
 */
void buscaRRN(FILE *fpbin, int rrn) {
  int numRegistros;

  rrn = rrn + 1;

  fseek(fpbin, 5, SEEK_SET);

  // Pega o numero de registros inseridos do registro de cabecalho
  fread(&numRegistros, sizeof(int), 1, fpbin);

  if (rrn > numRegistros) {
    printf("Registro Inexistente.");
    return;
  }

  // Variaveis locais para armazenar os conteudos dos campos.
  int tamCidMae;
  int tamCidBebe;
  char cidMae[97];
  char cidBebe[97];
  int idNascimento;
  int idadeMae;
  char data[11];
  char sexo[3];
  char estadoMae[3];
  char estadoBebe[3];

  // Coloca o ponteiro no registro buscado;
  int regBuscado = rrn * 128;
  fseek(fpbin, regBuscado, SEEK_SET);

  // Funcao que recupeda todos os campos do registro
  getCampos(fpbin, &tamCidMae, &tamCidBebe, cidMae, cidBebe, &idNascimento,
            &idadeMae, data, sexo, estadoMae, estadoBebe);


  // Monta a frase se o registro nao estiver logicamente removido
  if (tamCidMae != -1) {
    imprimeFrase(cidBebe, estadoBebe, data, sexo);
  } else {
    printf("Registro Inexistente.");
  }
}

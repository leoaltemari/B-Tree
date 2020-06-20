#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include"funcionalidade_7.h"
#include"general.h"
#include"binarioNaTela.h"


/*
 * A função atualizaRegistros() eh responsavel por atualizar um determinado
 * registro do arquivo binário e atualizar o cabeçalho
 * Parametros: FILE fpbin : ponteiro para o arquivo binario.
 * Retorno: Não há retorno na função pois caso uma atualização falhe o programa
 * continua para os outros rrns e campos.
 */
void atualizaRegistros(FILE *fpbin, int rrn, int m) {
  /*
   * Variáveis auxiliares para o campo1, byteoffset e uma flag que representa o
   * sucesso da atualização do registro.
   */
  int c1, byteoffset, flag = 0;
  char lixo = '$';
  byteoffset = (rrn + 1) * 128;

  // Cópia do cabeçalho.
  RegCabecalho *rg = malloc(sizeof(RegCabecalho));
  getCabecalho(fpbin, rg);

  // Evitar que tente atualizar um rrn inexistente.
  if (rrn <= rg->RRNproxRegistro) {
    fseek(fpbin, byteoffset, SEEK_SET); // leitura do Campo 1;
    fread(&c1, sizeof(int), 1, fpbin);

    for (int i = 0; i < m; i++) { // Looping principal para atualizar m campos.
      char *nomeCampo, campo[49]; // Leitura do tipo e do campo.
      scanf("%ms", &nomeCampo);
      scan_quote_string(campo);

      if (c1 != -1) { // Evitar que registros removidos sejam atualizados.
        flag = 1;     // Registro será atualizado.

        // Conjunto de ifs para determinar qual campo será atualizado.
        if (strcmp(nomeCampo, "idNascimento") == 0) { // Campo 5
          int id = atoi(campo); // Conversão da string para um inteiro
          fseek(fpbin, byteoffset + 105, SEEK_SET); // Ajuste do ponteiro
          fwrite(&id, sizeof(int), 1, fpbin);

        } else if (strcmp(nomeCampo, "idadeMae") == 0) { // Campo 6
          int idade;                  // Conversão da string para um inteiro
          if (strcmp(campo, "") == 0) // Tratamento do caso de ser nulo
            idade = -1;
          else
            idade = atoi(campo);
          fseek(fpbin, byteoffset + 109, SEEK_SET); // Ajuste do ponteiro
          fwrite(&idade, sizeof(int), 1, fpbin);

        } else if (strcmp(nomeCampo, "dataNascimento") == 0) { // Campo 7
          fseek(fpbin, byteoffset + 113, SEEK_SET); // Ajuste do ponteiro
          if (strcmp(campo, "") == 0) {             // Tratamento do lixo
            for (int i = 0; i < 10; i++)
              fwrite(&lixo, sizeof(char), 1, fpbin);
          } else
            fwrite(&campo, sizeof(char) * 10, 1, fpbin);

        } else if (strcmp(nomeCampo, "sexoBebe") == 0) { // Campo 8
          if (strcmp(campo, "") == 0)
            strcpy(campo, "0");
          fseek(fpbin, byteoffset + 123, SEEK_SET); // Ajuste do ponteiro
          fwrite(&campo, sizeof(char), 1, fpbin);

        } else if (strcmp(nomeCampo, "estadoMae") == 0) { // Campo 9
          fseek(fpbin, byteoffset + 124, SEEK_SET);       // Ajuste do ponteiro
          if (strcmp(campo, "") == 0) {                   // Tratamento do lixo
            fwrite(&campo, sizeof(char), 1, fpbin);
            fwrite(&lixo, sizeof(char), 1, fpbin);
          } else
            fwrite(&campo, sizeof(char) * 2, 1, fpbin);

        } else if (strcmp(nomeCampo, "estadoBebe") == 0) { // Campo 10
          fseek(fpbin, byteoffset + 126, SEEK_SET);        // Ajuste do ponteiro
          if (strcmp(campo, "") == 0) {                    // Tratamento do lixo
            fwrite(&campo, sizeof(char), 1, fpbin);
            fwrite(&lixo, sizeof(char), 1, fpbin);
          } else
            fwrite(&campo, sizeof(char) * 2, 1, fpbin);

        } else if (strcmp(nomeCampo, "cidadeMae") == 0) { // Campo 3
          int tamCidMae = strlen(campo), tamCidBebe;
          fseek(fpbin, byteoffset, SEEK_SET); // Overwrite do novo tamCidadeMae
          fwrite(&tamCidMae, sizeof(int), 1, fpbin);
          fseek(fpbin, byteoffset + 4, SEEK_SET); // Leitura do tamCidadeBebe
          fread(&tamCidBebe, sizeof(int), 1, fpbin);

          char cidBebe[tamCidBebe];
          fseek(fpbin, byteoffset + 8 + c1, SEEK_SET); // Leitura da cidadeBebe
          fread(&cidBebe, tamCidBebe, 1, fpbin);

          fseek(fpbin, byteoffset + 8, SEEK_SET); // Overwrite das cidades
          fwrite(&campo, tamCidMae, 1, fpbin);
          fwrite(&cidBebe, tamCidBebe, 1, fpbin);
          for (int i = 0; i < 97 - (tamCidMae + tamCidBebe); i++)
            fwrite(&lixo, sizeof(char), 1, fpbin); // Tratamento do lixo

        } else if (strcmp(nomeCampo, "cidadeBebe") == 0) { // Campo 4
          int tamBebe = strlen(campo);
          fseek(fpbin, byteoffset + 4, SEEK_SET);  // Ajuste do ponteiro
          fwrite(&tamBebe, sizeof(int), 1, fpbin); // Ajusta o tamanho da cidade
          fseek(fpbin, byteoffset + 8 + c1, SEEK_SET); // Ajuste do ponteiro
          fwrite(&campo, tamBebe, 1, fpbin);
        }
      }
      free(nomeCampo);
    }
    // Atualizacao do cabecalho;
    if (flag == 1)
      rg->numeroRegistrosAtualizados++;
    atualizaCabecalho(fpbin, rg);
    free(rg);
  }
}


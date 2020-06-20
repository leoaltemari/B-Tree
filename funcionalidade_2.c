#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include"funcionalidade_2.h"
#include"general.h"

// Função de leitura dos registros
void readRegs(FILE *fpbin) {
  // Variáveis auxiliares para o armazenamento dos campos 1, 2, 4, 10, 7 e 8
  int campo1, campo2, i = 2;
  fseek(fpbin, 128, SEEK_SET); // Ajuste para pular o registro de cabeçalho

  /*
   * Looping principal para a leitura até o final do arquivo: armazena o campo 1
   * e 2 e confere se o registro foi logicamente removido, caso não, cria
   * variáveis auxiliares vazias para os campos 4, 10, 7 e 8, respectivamente.
   * É realizado o ajuste do ponteiro do arquivo a cada leitura de um campo,
   * além da verificação se o campo continuou vazio mesmo após a leitura, caso
   * esteja, é utilizado o indicado "-", caso não adiciona um '\0' ao fim do
   * campo para evitar lixo.
   */
  if (fread(&campo1, sizeof(int), 1, fpbin) == 0) {
    printf("Registro inexistente.\n");
    return;
  } else {
    fseek(fpbin, 128, SEEK_SET); // Ajuste para pular o registro de cabeçalho
    while (fread(&campo1, sizeof(int), 1, fpbin) != 0) {
      fread(&campo2, sizeof(int), 1, fpbin);
      if (campo1 != -1) {
        char cidade[campo2 + 1], estado[3], dataNasc[11], sexo[3];
        cidade[0] = estado[0] = dataNasc[0] = sexo[0] = '\0';

        // Campo 4
        fseek(fpbin, 128 * (i - 1) + 8 + campo1, SEEK_SET);
        fread(&cidade, sizeof(char) * (uint)campo2, 1, fpbin);
        if (cidade[0] == '\0')
          strcpy(cidade, "-\0");
        else
          cidade[campo2] = '\0';
        printf("Nasceu em %s/", cidade);

        // Campo 10
        fseek(fpbin, 128 * i - 2, SEEK_SET);
        fread(&estado, sizeof(char) * 2, 1, fpbin);
        if (estado[0] == '\0')
          strcpy(estado, "-\0");
        else
          estado[3] = '\0';
        printf("%s, ", estado);

        // Campo 7
        fseek(fpbin, 128 * i - 15, SEEK_SET);
        fread(&dataNasc, sizeof(char) * 10, 1, fpbin);
        if (dataNasc[0] == '\0')
          strcpy(dataNasc, "-\0");
        else
          dataNasc[11] = '\0';
        printf("em %s, um bebê de sexo ", dataNasc);

        // Campo 8
        fseek(fpbin, 128 * i - 5, SEEK_SET);
        fread(&sexo, sizeof(char), 1, fpbin);
        sexo[3] = '\0';
        if (strcmp(sexo, "0") == 0)
          printf("IGNORADO.\n");
        else if (strcmp(sexo, "1") == 0)
          printf("MASCULINO.\n");
        else
          printf("FEMININO.\n");
      }

      // Incremento do RNN e ajuste do arquivo para o próximo registro.
      i++;
      fseek(fpbin, 128 * (i - 1), SEEK_SET);
    }
  }
}

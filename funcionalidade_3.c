#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include"funcionalidade_3.h"
#include"general.h"
#include"binarioNaTela.h"


/*
 * A funcao satisfazBusca() eh responsavelpor ler todos os campos de um registro
 * checar esses campos com os campos buscados(sendo eles combinados ou nao) e
 * imprimir na tela a frase dada a formatacao, caso a busca seja satisfeita.
 * Caso a busca nao seja satisfeita ele ja para e retorna 0(false). Parametros:
 *      FILE *fpbin: ponteiro para o arquivo binario.
 *      Busca *busca: estrutura que armazena os campos buscados.
 *      int m : inteiro para dizer quantos campos estao sendo buscados, em caso
 * de busca combinada. Retorno: Retorna 1 caso a busca seja satisfeita naquele
 * registro. Retorana 0 caso a busca nao seja satisfeita.
 */
int satisfazBusca(FILE *fpbin, Busca *busca, int m) {

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

  // Pega todos os campos do registro
  getCampos(fpbin, &tamCidMae, &tamCidBebe, cidMae, cidBebe, &idNascimento,
            &idadeMae, data, sexo, estadoMae, estadoBebe);

  // Registro inexistente
  if (tamCidMae == -1) {
    printf("Registro Inexistente.\n");
    return 0;
  }

  // Contador para verificar os campos buscados, se encontrar o campo buscado no
  // registro que esta atualmente contador aumenta de 1, se contador for igual
  // ao numero de campos buscados significa que o registro atual satisfaz a
  // busca combinada
  int contaCamposBuscados = 0;

  // Percorre os campos buscados checando com os campos do registro
  for (int i = 0; i < m; i++) {
    if (strcmp(busca[i].nomeCampo, "cidadeMae") == 0) {
      if (strcmp(busca[i].campoStr, cidMae) == 0) {
        contaCamposBuscados++;
      } else {
        return 0;
      }
    } else if (strcmp(busca[i].nomeCampo, "cidadeBebe") == 0) {
      if (strcmp(busca[i].campoStr, cidBebe) == 0) {
        contaCamposBuscados++;
      } else {
        return 0;
      }
    } else if (strcmp(busca[i].nomeCampo, "idNascimento") == 0) {
      if (busca[i].campoInt == idNascimento) {
        contaCamposBuscados++;
      } else {
        return 0;
      }
    } else if (strcmp(busca[i].nomeCampo, "idadeMae") == 0) {
      if (busca[i].campoInt == idadeMae) {
        contaCamposBuscados++;
      } else {
        return 0;
      }
    } else if (strcmp(busca[i].nomeCampo, "dataNascimento") == 0) {
      if (strcmp(busca[i].campoStr, data) == 0) {
        contaCamposBuscados++;
      } else {
        return 0;
      }
    } else if (strcmp(busca[i].nomeCampo, "sexoBebe") == 0) {
      if (strcmp(busca[i].campoStr, sexo) == 0) {
        contaCamposBuscados++;
      } else {
        return 0;
      }
    } else if (strcmp(busca[i].nomeCampo, "estadoMae") == 0) {
      if (strcmp(busca[i].campoStr, estadoMae) == 0) {
        contaCamposBuscados++;
      } else {
        return 0;
      }
    } else if (strcmp(busca[i].nomeCampo, "estadoBebe") == 0) {
      if (strcmp(busca[i].campoStr, estadoBebe) == 0) {
        contaCamposBuscados++;
      } else {
        return 0;
      }
    }
  }

  // Se satisfazer a busca combinada printa a frase daquele registro
  if (contaCamposBuscados == m) {
    imprimeFrase(cidBebe, estadoBebe, data, sexo);
    return 1;
  }

  return 0;
}

/*
 * A funcao buscaCombinada() eh responsavel por ler os campos que serao buscados
 * e percorrer o arquivo binario linearmente buscando por esses campos, sendo
 * eles combinados ou nao. Parametros: FILE *fpbin : ponteiro para o arquivo
 * binario. int m: numero de campos que serao combinados para busca. Retorno:
 *      Nao ha retorno.
 */
void buscaCombinada(FILE *fpbin, int m) {
  Busca *busca = malloc(sizeof(Busca) * (uint)m);

  leCamposBuscados(busca, m);

  int numRegistros;
  // Pega o numero de registros inseridos do registro de cabecalho
  fseek(fpbin, 5, SEEK_SET);
  fread(&numRegistros, sizeof(int), 1, fpbin);

  // Se nenhum registro foi inserido no arquivo ele nem testa
  if (numRegistros == 0) {
    printf("Registro Inexistente.\n");
    return;
  }

  // Pula para o primeiro registro
  fseek(fpbin, 119, SEEK_CUR);

  int succes =
      0; // Variavel que armazena 0 se o registro buscado nao for encontrado
  // Percorre todos os registros verificando se eles satisfazem os campos
  // buscados
  for (int i = 0; i < numRegistros; i++) {
    if (satisfazBusca(fpbin, busca, m)) {
      succes =
          1; // Achou pelo menos 1 registro no arquivo que satisfez a busca.
    }
  }

  // Se nenhum registro satisfez a busca
  if (succes == 0) {
    printf("Registro Inexistente.\n");
  }

  // Libera memoria utilizada
  free(busca);
}

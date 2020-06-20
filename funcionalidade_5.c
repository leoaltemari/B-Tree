#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include"funcionalidade_5.h"
#include"general.h"
#include"binarioNaTela.h"

/*
 * A funcao satisfazRemocao() eh responsavel por checar um registro e ver se os
 * campos buscados sao iguais aos campos do registro atual. Se for igual a
 * remocao eh feita na funcao removeRegistros(). Parametros: FILE *fpbin :
 * ponteiro para o arquivo binario. Busca *busca : ponteiro para a estrutura que
 * armazena os 'm' campos buscados(nomeCampo, valorCampo). int m : numero de
 * campos que foram combinados. Retorno: Retorna 1 caso o registro que satisfaca
 * a busca. Retorna 0 caso o registro nao satisfaca a busca em algum ponto. OBS:
 * Ao chamar essa funcao o ponteiro do arquivo ja deve estar no comeco do
 * registro, caso contrario ela nao funciona-ra.
 */
int satisfazRemocao(FILE *fpbin, Busca *busca, int m) {
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
    return 1;
  }

  return 0;
}

/*
 * A funcao removeRegisstros() eh responsavel por ler os 'm' campos buscados
 * e fazer uma busca no arquivo binario por um registro que satisfaca essa
 * busca, sendo ela combinada ou nao. Parametros: FILE *fpbin : ponteiro para o
 * arquivo binario. int m : numero de campos que serao combinados. Retorno: Nao
 * ha retorno na funcao, caso o registro nao seja encontrado a propria funcao
 * trata disso.
 */
int removeRegistros(FILE *fpbin, int m) {
  // Recupera o cabecalho
  RegCabecalho *rg = malloc(sizeof(RegCabecalho));
  getCabecalho(fpbin, rg);

  int numRegistros = rg->RRNproxRegistro;

  // Se nenhum registro foi inserido no arquivo ele nem testa
  if (rg->numeroRegistrosInseridos == 0) {
    return 0;
  }

  // Le os campos que irao ser combinados para remocao
  Busca *busca = malloc(sizeof(Busca) * (uint)m);
  leCamposBuscados(busca, m);

  // Percorre todos os registros verificando se eles satisfazem os campos
  // buscados
  for (int i = 0; i < numRegistros; i++) {
    // Checa se o registro atual satisfaz a combinacao dos campos para remocao
    if (satisfazRemocao(fpbin, busca, m)) {
      // Retorna no inicio do registro
      fseek(fpbin, -128, SEEK_CUR);

      // Remove
      int removido = -1;
      fwrite(&removido, sizeof(int), 1, fpbin);

      // Faz as atualizações no cabecalho em memoria
      rg->numeroRegistrosInseridos--;
      rg->numeroRegistrosRemovidos++;

      // Proximo registro
      fseek(fpbin, 124, SEEK_CUR);
    }
  }

  // Atualiza o cabecalho com os novos valores
  atualizaCabecalho(fpbin, rg);

  // Libera memoria utilizada
  free(rg);
  free(busca);

  return 0;
}



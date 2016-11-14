/***************************************************************************
 *
 *  $MCD Módulo de implementação: CRP  Módulo de Criação de Peça
 *
 *  Arquivo gerado:              CRIAPECA.C
 *  Letras identificadoras:      CRP
 *
 *  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
 *  Autores: iars

 *  $HA Histórico de evolução:
 *     Versão  Autor    Data     Observações
 *     1       iars   14/nov/2016 início desenvolvimento
 *
 ***************************************************************************/

#include   <stdio.h>
#include   <stdlib.h>
#include   <dirent.h>
#include   <string.h>
#include   <errno.h>

#define PECAS_DIR "..\\pecas\\default\\pecas"

/***** Protótipos das funções encapuladas no módulo *****/


/***************************************************************************
 *
 *  Função: CRP  &Criar peça
 *  ****/

int countPecasExistentes()
{
  // Code To Retrieve All Files in a Directory
  // http://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
  DIR *dir;
  int count = 0;

  struct dirent *ent;
  int size_file_name;
  if ((dir = opendir (PECAS_DIR)) != NULL)
  {
    while ((ent = readdir (dir)) != NULL)
    {
      size_file_name = strlen(ent->d_name);
      if(size_file_name == 5)
      {
        if(ent->d_name[size_file_name-1] == 'a'
            && ent->d_name[size_file_name-2] == 'c'
            && ent->d_name[size_file_name-3] == 'p'
            && ent->d_name[size_file_name-4] == '.' )
        {
          count++;
        }
      }
    }
    closedir (dir);
  }
  else
  {
    /* could not open directory */
    printf("ERRO FATAL: Nao foi possivel abrir a pasta %s.",PECAS_DIR);
    exit(1);
  }
  return count;
}

void getPecasExistentes(char** pecas, int* num_pecas)
{
  // Code To Retrieve All Files in a Directory
  // http://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
  DIR *dir;

  struct dirent *ent;
  int size_file_name;
  int i=0;

  *num_pecas = countPecasExistentes();

  *num_pecas;
  *pecas = (char*) malloc(sizeof(char)*(*num_pecas));

  if ((dir = opendir (PECAS_DIR)) != NULL)
  {
    while ((ent = readdir (dir)) != NULL)
    {
      size_file_name = strlen(ent->d_name);
      if(size_file_name == 5)
      {
        if(ent->d_name[size_file_name-1] == 'a'
            && ent->d_name[size_file_name-2] == 'c'
            && ent->d_name[size_file_name-3] == 'p'
            && ent->d_name[size_file_name-4] == '.' )
        {
          (*pecas)[i] = ent->d_name[0];
          i++;
        }
      }
    }
    closedir (dir);
  }
  else
  {
    /* could not open directory */
    printf("ERRO FATAL: Nao foi possivel abrir a pasta %s.",PECAS_DIR);
    exit(1);
  }
}

void printPecasExistentes()
{
  char* pecas;
  int num_pecas;
  int i;
  getPecasExistentes(&pecas, &num_pecas);

  printf("Pecas Existentes:\n");
  for(i=0; i<num_pecas; i++)
  {
    printf ("%c ", pecas[i]); 
  }
  printf ("\n");

  free(pecas);
}

void deletaPeca()
{
  // Code To Remove a File From a Directory
  // http://www.programmingsimplified.com/c-program-delete-file
  int status;
  char file_name[200];
  char char_peca_string[2] = "x";
  char char_peca;

  printPecasExistentes();
  printf("--------------------\n");
  printf("Digite o nome da peca a ser deletada: ");
  scanf(" %c",&char_peca);

  char_peca_string[0] = char_peca;

  strcpy(file_name,PECAS_DIR);
  strcat(file_name,"\\");
  strcat(file_name,char_peca_string);
  strcat(file_name,".pca");

  status = remove(file_name);

  if( status == 0 )
  {
    printf("A peca %c foi deletada com sucesso.\n",char_peca);
  }
  else
  {
    printf("ERRO: Nao foi possivel deletar a peca %c.\n",char_peca);
    printf("DESCRICAO DO ERRO: ");
    switch(errno)
    {
      case EACCES:
      printf("Erro de permissao do arquivo %s.\n",file_name);
      break;
      case EBUSY:
      printf("Arquivo da peca ja sendo utilizado.\n");
      break;
      case ENOENT:
      printf("Arquivo %s nao existe.\n",file_name);
      break;
      case EPERM:
      printf("Erro ao deletar um diretorio com o nome da peca\n");
      break;
      default:
      printf("Erro Desconhecido.\n");
      break;
    }
  }
}

void criarNovaPeca()
{
  char char_peca;
  char* pecas;
  int num_pecas;
  int i;
  int opcao_escolhida;

  int pula_que_nem_cavalo;

  printPecasExistentes();
  printf("--------------------\n");
  printf("Digite o nome da nova peca a ser criada:\n");
  printf("(Nome de pecas devem possuir somente 1 letra)\n");
  printf("(Pecas em caixa alta e caixa baixa sao diferentes)\n");
  printf(">> ");
  scanf(" %c",&char_peca);

  getPecasExistentes(&pecas, &num_pecas);

  for(i=0; i<num_pecas; i++)
  {
    if(pecas[i] == char_peca)
    {
      printf("ERRO: A peca %c ja existe. Escolha outro nome.\n",char_peca);
      printf("Caso voce queira atualizar essa peca, delete e crie novamente.\n");
      free(pecas);
      return;
    }
  }

  free(pecas);

  printf("--------------------\n");
  printf("CARACTERISTICAS DA PECA:\n");
  printf("--------------------\n");

  printf("A peca pulara outras pecas (que nem o cavalo?):\n");
  printf("(0) - Nao\n");
  printf("(1) - Sim\n");
  printf(">> ");
  scanf(" %d",&opcao_escolhida);

  switch(opcao_escolhida)
  {
    case 0:
      pula_que_nem_cavalo = 0;
    case 1:
      pula_que_nem_cavalo = 1;
      break;
    default:
      printf("Opcao nao existente.\n");
      return;
  }
}

int main( int argc, char** argv )
{
  printf("--------------------\n");
  printf("ASSISTENTE DE CRIACAO DE PECAS\n");
  printf("--------------------\n");
  printf("Bem vindo ao assistente de criacao de pecas.\n");
  printf("Esse assistente ajudara voce a criar novas pecas\n");
  printf("Os arquivos da pecas estao sendo alterados em:\n");
  printf("%s\n",PECAS_DIR);
  printf("--------------------\n");
  printf("Sobre o Edicao de Pecas Avancadas:\n");
  printf("Caso deseje, voce tambem pode alterar manualmente as pecas em:\n");
  printf("%s\n",PECAS_DIR);
  printf("Sera mais complexo, mas voce podera criar qualquer movimento, sem restricoes.\n");
  printf("Requer conhecimento de logica de primeira ordem.\n");

  int opcao_escolhida;
  while(1)
  {
  printf("--------------------\n");
    printf("Digite a opcao desejada:\n");
    printf("(0) - Sair\n");
    printf("(1) - Mostrar pecas ja criadas\n");
    printf("(2) - Criar nova peca\n");
    printf("(3) - Deletar peca ja existente\n");
    printf("--------------------\n");
    printf("Opcao >> ");
    scanf(" %d",&opcao_escolhida);
    printf("--------------------\n");

    switch(opcao_escolhida)
    {
      case 0:
        exit(0);
      case 1:
        printPecasExistentes();
        break;
      case 2:
        criarNovaPeca();
        break;
      case 3:
        deletaPeca();
        break;
      default:
        printf("Opcao nao existente.\n");
        break;

    }
  }
} /* Fim função: main */

/***************************************************************************

/********** Fim do módulo de Criação de Peças **********/


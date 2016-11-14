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
#define MAX_MOVIMENTOS 32

/***** Protótipos das funções encapuladas no módulo *****/

enum Direcao
{
  HORIZONTAL=0,
  VERTICAL=1,
  DIAGONAL_CRESCENTE=2,
  DIAGONAL_DECRESCENTE=3
};

typedef enum Direcao tpDirecao;

struct MovimentoSimples
{
  int pontual;

  // Se pontual == 1
  int horizontal;
  int vertical;

  // Se pontual == 0
  tpDirecao direcao; 
};

typedef struct MovimentoSimples tpMovimentoSimples;

void escreveMovimentoNoArquivo(FILE* file, tpMovimentoSimples mov);
void printMovimentoSimples(tpMovimentoSimples mov);
int countPecasExistentes();
void getPecasExistentes(char** pecas, int* num_pecas);
void printPecasExistentes();
void deletaPeca();
void criarNovaPeca();
void criarArquivoPecaMovimento(char char_peca, tpMovimentoSimples* movimentosPeca, int num_movimentos);

/***************************************************************************
 *
 *  Função: CRP  &Criar peça
 *  ****/

void printMovimentoSimples(tpMovimentoSimples mov)
{
  char nomeDirecoes[4][100] = {"HORIZONTAL", "VERTICAL", "DIAGONAL CRESCENTE", "DIAGONAL DECRESCENTE"};

  if(mov.pontual == 1)
  {
    printf("Movimento Pontual (horizontal = %d, vertical = %d)\n",mov.horizontal,mov.vertical);
  }
  else
  {
    printf("Movimento Continuo na Direcao: %s\n",nomeDirecoes[(int)mov.direcao]);
  }
}

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
  tpMovimentoSimples movimentosPeca[MAX_MOVIMENTOS];
  int num_movimentos;

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

  num_movimentos = 0;

  while(1)
  {
    printf("========================================\n");
    printf("MOVIMENTOS DA PECA %c:\n",char_peca);
    printf("========================================\n");

    printf("Total Movimentos: %d (max: %d)\n",num_movimentos,MAX_MOVIMENTOS);
    if(num_movimentos>0)
    {
      printf("--------------------\n");
      printf("Lista de Movimentos:\n");
      printf("--------------------\n");
      if(num_movimentos>1)
      {
        printf("(Nao ha problemas de existirem movimentos redundantes)\n");
      }
      for(i=0;i<num_movimentos;i++)
      {
        printf("%d) ",i+1);
        printMovimentoSimples(movimentosPeca[i]);
      }
    }

    while(1)
    {
      printf("--------------------\n");
      printf("Inserir novo movimento ou finalizar peca?\n");
      printf("(0) - Finalizar\n");
      printf("(1) - Inserir Novo Movimento\n");
      printf(">> ");
      scanf(" %d",&opcao_escolhida);

      if(opcao_escolhida == 0 && num_movimentos == 0)
      {
        printf("Voce deve adicionar ao menos 1 movimento a nova peca!\n");
        continue;
      }

      if(opcao_escolhida == 0 || opcao_escolhida == 1)
      {
        break;
      }
      else
      {
        printf("Opcao invalida!\n");        
      }
    }

    if(opcao_escolhida==0)
    {
      break;
    }

    while(1)
    {
      printf("--------------------\n");
      printf("Movimento pontual (movimento direto para o local) ou continuo?\n");
      printf("\n");
      printf("Movimento pontual = move instantaneamente para a posicao de destino.\n");
      printf("Movimento continuo = liberdade de se mover continuamente em uma direcao\n");
      printf("\n");
      printf("(0) - Pontual (exemplo: cavalo, rei, peao)\n");
      printf("(1) - Continuo (exexemplo: torre, bispo, rainha)\n");
      printf(">> ");
      scanf(" %d",&opcao_escolhida);

      if(opcao_escolhida == 0 || opcao_escolhida == 1)
      {
        break;
      }
      else
      {
        printf("Opcao invalida!\n");        
      }
    }

    if(opcao_escolhida==0)
    {
      movimentosPeca[num_movimentos].pontual = 1;
      printf("--------------------\n");
      printf("[MOVIMENTO PONTUAL]\n");
      printf("Quantas casas devem ser movidas (puladas) horizontalmente?\n");
      printf("Numero positivo -> movimento para direita\n");
      printf("Numero negativo -> movimento para esquerda\n");
      printf(">> ");
      scanf(" %d",&movimentosPeca[num_movimentos].horizontal);
      printf("--------------------\n");
      printf("[MOVIMENTO PONTUAL]\n");
      printf("Quantas casas devem ser movidas (puladas) verticalmente?\n");
      printf("Numero positivo -> movimento para baixo\n");
      printf("Numero negativo -> movimento para cima\n");
      printf(">> ");
      scanf(" %d",&movimentosPeca[num_movimentos].vertical);
    }
    else
    {
      while(1)
      {
        printf("--------------------\n");
        printf("[MOVIMENTO CONTINUO]\n");
        printf("Qual direcao do movimento a ser realizado\n");
        printf("(0) - Horizontal\n");
        printf("(1) - Vertical\n");
        printf("(2) - Diagonal Crescente (/)\n");
        printf("(3) - Diagonal Decrescente (\\)\n");
        printf(">> ");
        scanf(" %d",&opcao_escolhida);

        if(opcao_escolhida >= 0 && opcao_escolhida <= 3)
        {
          break;
        }
        else
        {
          printf("Opcao invalida!\n");   
        }
      }

      switch(opcao_escolhida)
      {
        case 0:
        movimentosPeca[num_movimentos].direcao = HORIZONTAL;
        break;
        case 1:
        movimentosPeca[num_movimentos].direcao = VERTICAL;
        break;
        case 2:
        movimentosPeca[num_movimentos].direcao = DIAGONAL_CRESCENTE;
        break;
        case 3:
        movimentosPeca[num_movimentos].direcao = DIAGONAL_DECRESCENTE;
        break;
        default:
        printf("ERRO DESCONHECIDO.\n");
        exit(1);
        break;
      }
    }

    num_movimentos++;

  }

  printf("========================================\n");
  printf("Nova Peca: %c\n",char_peca);
  printf("========================================\n");

  printf("Total Movimentos: %d (max: %d)\n",num_movimentos,MAX_MOVIMENTOS);
  if(num_movimentos>0)
  {
    printf("--------------------\n");
    printf("Lista de Movimentos:\n");
    printf("--------------------\n");
    if(num_movimentos>1)
    {
      printf("(Nao ha problemas de existirem movimentos redundantes)\n");
    }
    for(i=0;i<num_movimentos;i++)
    {
      printf("%d) ",i+1);
      printMovimentoSimples(movimentosPeca[i]);
    }
  }

  while(1)
  {
    printf("--------------------\n");
    printf("Confirmar Peca?\n");
    printf("(0) - Cancelar\n");
    printf("(1) - Confirmar\n");
    printf(">> ");
    scanf(" %d",&opcao_escolhida);

    if(opcao_escolhida == 0 || opcao_escolhida == 1)
    {
      break;
    }
    else
    {
      printf("Opcao invalida!\n");        
    }
  }

  if(opcao_escolhida==0)
  {
    return;
  }

  criarArquivoPecaMovimento(char_peca, movimentosPeca, num_movimentos);    
}

void criarArquivoPecaMovimento(char char_peca, tpMovimentoSimples* movimentosPeca, int num_movimentos)
{
  char file_name[200];
  char char_peca_string[2] = "x";
  FILE* file;
  int i;

  char_peca_string[0] = char_peca;

  strcpy(file_name,PECAS_DIR);
  strcat(file_name,"\\");
  strcat(file_name,char_peca_string);
  strcat(file_name,".pca");

  file = fopen(file_name,"w");
  if(file == NULL)
  {
    printf("ERRO: Erro ao abrir arquivo %s. Peca nao criada.\n",file_name);
    return;
  }

  for(i=0; i<num_movimentos-1; i++)
  {
    fprintf(file,"L_OR \n");
    escreveMovimentoNoArquivo(file,movimentosPeca[i]);
  }
  escreveMovimentoNoArquivo(file,movimentosPeca[num_movimentos-1]);

  printf("SUCESSO!\n");
  printf("Peca %c criada com sucesso!\n",char_peca);
  printf("Arquivo %s gerado.\n",file_name);

  fclose(file);
}

void escreveMovimentoNoArquivo(FILE* file, tpMovimentoSimples mov)
{
  if(mov.pontual == 1)
  {
    fprintf(file,"L_AND\n");

    fprintf(file,"\tL_OR P_VAZ D P_INI D\n");

    fprintf(file,"L_AND\n");

    fprintf(file,"\tP_IGUAL\n");
    fprintf(file,"\t\tF_SUB V_DIM 0 D V_DIM 0 A\n");
    fprintf(file,"\t\tV_NUM %d\n",mov.horizontal);

    fprintf(file,"\tP_IGUAL\n");
    fprintf(file,"\t\tF_SUB V_DIM 1 D V_DIM 1 A\n");
    fprintf(file,"\t\tV_NUM %d\n",mov.vertical);
  }
  else
  {
    fprintf(file,"L_AND\n");

    fprintf(file,"\tL_OR P_VAZ D P_INI D\n");

    fprintf(file,"L_AND\n");

    if(mov.direcao == HORIZONTAL)
    {
      fprintf(file,"L_AND\n");
      fprintf(file,"\tP_IGUAL V_DIM 1 D V_DIM 1 A\n");
      fprintf(file,"\tL_FORALL C\n");
      fprintf(file,"\t\tL_IFTHEN\n");
      fprintf(file,"\t\t\tL_AND\n");
      fprintf(file,"\t\t\t\tP_IGUAL V_DIM 1 C V_DIM 1 A\n");
      fprintf(file,"\t\t\t\tP_MENOR\n");
      fprintf(file,"\t\t\t\t\tF_ABS F_SUB V_DIM 0 C V_DIM 0 A\n");
      fprintf(file,"\t\t\t\t\tF_ABS F_SUB V_DIM 0 D V_DIM 0 A\n");
      fprintf(file,"\t\t\tP_VAZ C\n");
    }
    else if(mov.direcao == VERTICAL)
    {
      fprintf(file,"L_AND\n");
      fprintf(file,"\tP_IGUAL V_DIM 0 D V_DIM 0 A\n");
      fprintf(file,"\tL_FORALL C\n");
      fprintf(file,"\t\tL_IFTHEN\n");
      fprintf(file,"\t\t\tL_AND\n");
      fprintf(file,"\t\t\t\tP_IGUAL V_DIM 0 C V_DIM 0 A\n");
      fprintf(file,"\t\t\t\tP_MENOR\n");
      fprintf(file,"\t\t\t\t\tF_ABS F_SUB V_DIM 1 C V_DIM 1 A\n");
      fprintf(file,"\t\t\t\t\tF_ABS F_SUB V_DIM 1 D V_DIM 1 A\n");
      fprintf(file,"\t\t\tP_VAZ C\n");
    }
    else if(mov.direcao == DIAGONAL_CRESCENTE)
    {
      fprintf(file,"L_AND\n");
      fprintf(file,"\tP_IGUAL F_ADD F_SUB V_DIM 0 D V_DIM 0 A F_SUB V_DIM 1 D V_DIM 1 A V_NUM 0\n");
      fprintf(file,"\tL_FORALL C\n");
      fprintf(file,"\t\tL_IFTHEN\n");
      fprintf(file,"\t\t\tL_AND\n");
      fprintf(file,"\t\t\t\tP_IGUAL F_ADD F_SUB V_DIM 0 C V_DIM 0 A F_SUB V_DIM 1 C V_DIM 1 A V_NUM 0\n");
      fprintf(file,"\t\t\t\tP_MENOR\n");
      fprintf(file,"\t\t\t\t\tF_ABS F_SUB V_DIM 1 C V_DIM 1 A\n");
      fprintf(file,"\t\t\t\t\tF_ABS F_SUB V_DIM 1 D V_DIM 1 A\n");
      fprintf(file,"\t\t\tP_VAZ C\n");
    }
    else if(mov.direcao == DIAGONAL_DECRESCENTE)
    {
      fprintf(file,"L_AND\n");
      fprintf(file,"\tP_IGUAL F_SUB F_SUB V_DIM 0 D V_DIM 0 A F_SUB V_DIM 1 D V_DIM 1 A V_NUM 0\n");
      fprintf(file,"\tL_FORALL C\n");
      fprintf(file,"\t\tL_IFTHEN\n");
      fprintf(file,"\t\t\tL_AND\n");
      fprintf(file,"\t\t\t\tP_IGUAL F_SUB F_SUB V_DIM 0 C V_DIM 0 A F_SUB V_DIM 1 C V_DIM 1 A V_NUM 0\n");
      fprintf(file,"\t\t\t\tP_MENOR\n");
      fprintf(file,"\t\t\t\t\tF_ABS F_SUB V_DIM 1 C V_DIM 1 A\n");
      fprintf(file,"\t\t\t\t\tF_ABS F_SUB V_DIM 1 D V_DIM 1 A\n");
      fprintf(file,"\t\t\tP_VAZ C\n");
    }
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


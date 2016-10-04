/***************************************************************************
*  $MCD Módulo de definição: VMV  Validador de Movimentos
*
*  Arquivo gerado:              VALIDA_MOV.C
*  Letras identificadoras:      VMV
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Tabuleiro de Xadrez
*  Gestor:  LES/DI/PUC-Rio
*  Autores: iars
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       avs   04/out/2016 início desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>

#define VALIDA_MOV_OWN
#include "VALIDA_MOV.H"
#undef VALIDA_MOV_OWN

/***********************************************************************
*
*  $TC Tipo de dados: VMV TODO
*
***********************************************************************/

   typedef struct VMV_configDir {

         const char * pPathDirPecas ;
               /* Ponteiro para o valor contido no elemento */

         const char * pPathArquivoInicial ;
               /* Ponteiro para o elemento predecessor */

   } VMV_tpConfigDir ;

/***********************************************************************
* Constantes Globais Utilizadas Pelo Módulo
***********************************************************************/

static const char CONFIG_DEFAULT_FILE_NAME [ ] = "config.conf";
static const char CMD_CONFIG_TABULEIRO_INICIAL [ ] = "tabuleiro_inicial";
static const char CMD_CONFIG_DIRETORIO_PECAS [ ] = "diretorio_pecas";

/***********************************************************************
* Protótipos das funções encapuladas no módulo
***********************************************************************/

   VMV_tpCondRet VMV_AbreArquivo ( const char* nomeArquivo, FILE** pArquivo )
   {
      FILE* arquivoEntrada = fopen(nomeArquivo, "r");

      if(arquivoEntrada == NULL)
      {
         return VMV_CondRetErrAberturaArquivo;
      }

      *pArquivo = arquivoEntrada;

      return VMV_CondRetOK;
   }

   VMV_tpCondRet VMV_FechaArquivo ( FILE* pArquivo )
   {
      fclose(pArquivo);
      return VMV_CondRetOK;
   }

   VMV_tpCondRet VMV_LerArquivoConfig( FILE* configArq, 
                                       char* pathArqInicial, 
                                       char* pathDirPecas )
   {
      char* buffer[256];
      while(fscanf(configArq, " %s", buffer) == 1)
      {
         if(strcmp(buffer,CMD_CONFIG_TABULEIRO_INICIAL)==0)
         {
            if(fscanf(configArq, " %s", buffer) != 1)
            {
               return VMV_CondRetErrFormatoArquivoErrado;
            }
            pathArqInicial = (char*) malloc(sizeof(char)*(strlen(buffer)+1));
            if(pathArqInicial==NULL)
            {
               return VMV_CondRetErrFaltouMemoria;
            }
            strcpy(pathArqInicial,buffer);
         }

         if(strcmp(buffer,CMD_CONFIG_DIRETORIO_PECAS)==0)
         {
            if(fscanf(configArq, " %s", buffer) != 1)
            {
               return VMV_CondRetErrFormatoArquivoErrado;
            }
            pathDirPecas = (char*) malloc(sizeof(char)*(strlen(buffer)+1));
            if(pathDirPecas==NULL)
            {
               free(pathArqInicial);
               return VMV_CondRetErrFaltouMemoria;
            }
            strcpy(pathDirPecas,buffer);
         }
      }
   }

/***********************************************************************
* Código das funções exportadas pelo módulo
***********************************************************************/

/***********************************************************************
* Função: VMV  &Cria Estrutura de Diretorio de Configuracao
***********************************************************************/

   VMV_tpCondRet VMV_CriarConfigDir (  VMV_tppConfigDir* pConfigDir, const char* pathConfigArq )
   {
      FILE* configArq;
      char* pathArqInicial;
      char* pathDirPecas;
      VMV_tppConfigDir pNewConfigDir;

      VMV_tpCondRet statusOperacao;

      if(pathConfigArq == NULL)
      {
         statusOperacao = VMV_AbreArquivo(CONFIG_DEFAULT_FILE_NAME, &configArq);
      }
      else
      {
         statusOperacao = VMV_AbreArquivo(pathConfigArq, &configArq);
      }
      if(statusOperacao != VMV_tpCondRetOK)
      {
         return statusOperacao;
      }

      statusOperacao = VMV_LerArquivoConfig(configArq, pathArqInicial, pathDirPecas);
      if(statusOperacao != VMV_tpCondRetOK)
      {
         return statusOperacao;
      }

      pNewConfigDir = (VMV_tppConfigDir) malloc(sizeof(VMV_tpConfigDir));
      if(pNewConfigDir==NULL)
      {
         free(pathArqInicial);
         free(pathDirPecas);
         return VMV_CondRetErrFaltouMemoria;
      }

      pNewConfigDir->pPathArquivoInicial = pathArqInicial;
      pNewConfigDir->pPathDirPecas = pathDirPecas;

      VMV_FechaArquivo(arquivoEntrada)

   } /* Fim função: VMV  &Cria Estrutura de Diretorio de Configuracao */

/***********************************************************************
* Função: VMV  &Destroi Estrutura de Diretorio de Configuracao
***********************************************************************/

   VMV_tpCondRet VMV_DestruirConfigDir (  VMV_tppConfigDir pConfigDir )
   {
      if(pConfigDir != NULL)
      {
         free(pConfigDir->pPathDirPecas);
         free(pConfigDir->pPathArquivoInicial);
         free(pConfigDir);
      }
   } /* Fim função: VMV  &Destroi Estrutura de Diretorio de Configuracao */

/***********************************************************************
* Função: VMV  &Ler Tabuleiro Inicial
***********************************************************************/

   VMV_tpCondRet VMV_LerTabuleiroInicial ( VMV_tppConfigDir pConfig, double* pecas, double* cores, double* num_casas )
   {
      FILE* arquivoEntrada;

      VMV_tpCondRet statusAberturaArquivo = VMV_AbreArquivo(pConfig->pPathArquivoInicial, &arquivoEntrada);
      
      if(statusAberturaArquivo != VMV_tpCondRetOK)
      {
         return statusAberturaArquivo;
      }



      VMV_FechaArquivo(arquivoEntrada)

   } /* Fim função: VMV  &Ler Tabuleiro Inicial */

/***********************************************************************
* Função: VMV  &Checa Movimento de Peça
***********************************************************************/

   VMV_tpCondRet VMV_ChecarMovimentoPeca (   VMV_tpMovimentoValido* movimento_valido,
                                             char peca,
                                             char cor, 
                                             void* casa_atual,
                                             void* casa_destino,
                                             void* casas,
                                             int num_casas,
                                             int num_dimensoes,
                                             int (*array_dimensao)(void* casa),
                                             int* array_sinal,
                                             int (*vazio)(void* array_de_casas, int num_casas),
                                             int (*inimigo)(void* array_de_casas, int num_casas),
                                             int* cond_especiais,
                                             int num_cond_especiais)

   {


   } /* Fim função: VMV  &Checa Movimento de Peça*/

/***************************************************************************

/********** Fim do módulo de implementação: VMV  Lista duplamente encadeada **********/


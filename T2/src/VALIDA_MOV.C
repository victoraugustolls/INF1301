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
#include   <stdlib.h>

#define VALIDA_MOV_OWN
#include "VALIDA_MOV.H"
#undef VALIDA_MOV_OWN

/***********************************************************************
*
*  $TC Tipo de dados: VMV TODO
*
***********************************************************************/

   typedef struct VMV_configDir {

         char * pPathDirPecas ;
               /* Ponteiro para o valor contido no elemento */

         char * pPathArquivoInicial ;
               /* Ponteiro para o elemento predecessor */

   } VMV_tpConfigDir ;


/***********************************************************************
*
*  $TC Tipo de dados: VMV TODO
*
***********************************************************************/

   typedef struct VMV_exprEvalTools {

      char peca;
      void* casa_atual;
      void* casa_destino;
      void** casas;
      int num_casas;
      int num_dimensoes;
      int (**array_dimensao)(void* casa, void* aux);
      int* array_sinal;
      int (*vazio)(void* casa, void* aux);
      int (*inimigo)(void* casa, void* aux);
      int* cond_especiais;
      int num_cond_especiais;
      void* aux;

   } VMV_tpExprEvalTools ;

/***********************************************************************
*
*  $TC Tipo de dados: VMV TODO
*
***********************************************************************/

   typedef struct VMV_casaIterator {

      char* id;
      void* casa;

   } VMV_tpCasaIterator ;


/***********************************************************************
*
*  $TC Tipo de dados: VMV TODO
*
***********************************************************************/
   typedef enum {

         VMV_ReturnExpectedBool = 0 ,
               /* O Movimento não é válido */

         VMV_ReturnExpectedInteger = 1
               /* O Movimento não é válido */

   } VMV_tpReturnExpected ;


/***********************************************************************
* Constantes Globais Utilizadas Pelo Módulo
***********************************************************************/

static const char CONFIG_DEFAULT_FILE_NAME [ ] = "config.conf";
static const char CMD_CONFIG_TABULEIRO_INICIAL [ ] = "tabuleiro_inicial";
static const char CMD_CONFIG_DIRETORIO_PECAS [ ] = "diretorio_pecas";

static const char CMD_PCA_L_OR [ ]           = "L_OR";
static const char CMD_PCA_L_AND [ ]          = "L_AND";
static const char CMD_PCA_L_IFTHEN [ ]       = "L_IFTHEN";
static const char CMD_PCA_L_NOT [ ]          = "L_NOT";
static const char CMD_PCA_L_FORALL [ ]       = "L_FORALL";
static const char CMD_PCA_L_EXIST [ ]        = "L_EXIST";

static const char CMD_PCA_P_IGUAL [ ]        = "P_IGUAL";
static const char CMD_PCA_P_MAIOR [ ]        = "P_MAIOR";
static const char CMD_PCA_P_MENOR [ ]        = "P_MENOR";
static const char CMD_PCA_P_VAZ [ ]          = "P_VAZ";
static const char CMD_PCA_P_INI [ ]          = "P_INI";
static const char CMD_PCA_P_COND [ ]         = "P_COND";

static const char CMD_PCA_F_ADD [ ]          = "F_ADD";
static const char CMD_PCA_F_SUB [ ]          = "F_SUB";
static const char CMD_PCA_F_MUL [ ]          = "F_MUL";
static const char CMD_PCA_F_ABS [ ]          = "F_ABS";

static const char CMD_PCA_V_DIM [ ]          = "V_DIM";
static const char CMD_PCA_V_SIG [ ]          = "V_SIG";
static const char CMD_PCA_V_NUM [ ]          = "V_NUM";

static const char CMD_PCA_C_A [ ]                = "A";
static const char CMD_PCA_C_D [ ]                = "D";
static const char CMD_PCA_C_C [ ]                = "C";

/***********************************************************************
* Protótipos das funções encapuladas no módulo
***********************************************************************/

   VMV_tpCondRet VMV_AbreArquivo ( const char* nomeArquivo, FILE** pArquivo )
   {
      FILE* arquivoEntrada = fopen(nomeArquivo, "r");

      if(arquivoEntrada == NULL)
      {
          printf("\n\nNOME DO ARQUIVO\n\n%s\n\n", nomeArquivo);
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
                                       char** pathArqInicial, 
                                       char** pathDirPecas )
   {
      char* buffer[512];
      while(fscanf(configArq, " %s", buffer) == 1)
      {

         if(strcmp((const unsigned char*)buffer,CMD_CONFIG_TABULEIRO_INICIAL)==0)
         {
            if(fscanf(configArq, " %s", buffer) != 1)
            {
               return VMV_CondRetErrFormatoArquivoErrado;
            }
            *pathArqInicial = (char*) malloc(sizeof(char)*(strlen((const unsigned char*)buffer)+1));
            if(*pathArqInicial==NULL)
            {
               return VMV_CondRetErrFaltouMemoria;
            }
            strcpy(*pathArqInicial,(const unsigned char*)buffer);
         }
         else if(strcmp((const unsigned char*)buffer,CMD_CONFIG_DIRETORIO_PECAS)==0)
         {
            if(fscanf(configArq, " %s", buffer) != 1)
            {
               return VMV_CondRetErrFormatoArquivoErrado;
            }
            *pathDirPecas = (char*) malloc(sizeof(char)*(strlen((const unsigned char*)buffer)+1));
            if(*pathDirPecas==NULL)
            {
               free(*pathArqInicial);
               return VMV_CondRetErrFaltouMemoria;
            }
            strcpy(*pathDirPecas,(const unsigned char*)buffer);
         }
         else
         {
            return VMV_CondRetErrFormatoArquivoErrado;
         }
      }
      return VMV_CondRetOK;
   }

   VMV_tpCondRet VMV_AvaliarProxLinha (   FILE* file,
                                          VMV_tpReturnExpected returnExpected,
                                          VMV_tpMovimentoValido* booleanValue,
                                          int* integerValue,
                                          VMV_tpExprEvalTools* tools,
                                          VMV_tpCasaIterator* casaIterators,
                                          int numCasaIterators )
   {
         char buffer[32];
         VMV_tpCondRet condRet;
         VMV_tpMovimentoValido boolRetA;
         VMV_tpMovimentoValido boolRetB;
         int intRetA;
         int intRetB;
         int i,j;
         int valor;
         VMV_tpCasaIterator* novoCasaIterators;
         char* novoId;
         long int currentFilePosition;

         if( fscanf( file, " %s", buffer ) != 1 )
         {
            return VMV_CondRetErrFormatoArquivoErrado;
         }

         if( strcmp( buffer, CMD_PCA_L_OR ) == 0 )
         {
            if(returnExpected != VMV_ReturnExpectedBool)
               return VMV_CondRetErrFormatoArquivoErrado;

            condRet =     VMV_AvaliarProxLinha (   file,
                                                   VMV_ReturnExpectedBool,
                                                   &boolRetA,
                                                   NULL,
                                                   tools,
                                                   casaIterators,
                                                   numCasaIterators );
            if(condRet != VMV_CondRetOK)
               return condRet;
            condRet =     VMV_AvaliarProxLinha (   file,
                                                   VMV_ReturnExpectedBool,
                                                   &boolRetB,
                                                   NULL,
                                                   tools,
                                                   casaIterators,
                                                   numCasaIterators );
            if(condRet != VMV_CondRetOK)
               return condRet;

            if( boolRetA == VMV_MovimentoValidoSim || boolRetB == VMV_MovimentoValidoSim )
            {
               *booleanValue = VMV_MovimentoValidoSim;
               return VMV_CondRetOK;
            }
            else
            {
               *booleanValue = VMV_MovimentoValidoNao;
               return VMV_CondRetOK;
            }
         }
         else if( strcmp( buffer, CMD_PCA_L_AND ) == 0 )
         {
            if(returnExpected != VMV_ReturnExpectedBool)
               return VMV_CondRetErrFormatoArquivoErrado;

            condRet =     VMV_AvaliarProxLinha (   file,
                                                   VMV_ReturnExpectedBool,
                                                   &boolRetA,
                                                   NULL,
                                                   tools,
                                                   casaIterators,
                                                   numCasaIterators );
            if(condRet != VMV_CondRetOK)
               return condRet;
            condRet =     VMV_AvaliarProxLinha (   file,
                                                   VMV_ReturnExpectedBool,
                                                   &boolRetB,
                                                   NULL,
                                                   tools,
                                                   casaIterators,
                                                   numCasaIterators );
            if(condRet != VMV_CondRetOK)
               return condRet;

            if( boolRetA == VMV_MovimentoValidoSim && boolRetB == VMV_MovimentoValidoSim )
            {
               *booleanValue = VMV_MovimentoValidoSim;
               return VMV_CondRetOK;
            }
            else
            {
               *booleanValue = VMV_MovimentoValidoNao;
               return VMV_CondRetOK;
            }
         }
         else if( strcmp( buffer, CMD_PCA_L_IFTHEN ) == 0 )
         {
            if(returnExpected != VMV_ReturnExpectedBool)
               return VMV_CondRetErrFormatoArquivoErrado;

            condRet =     VMV_AvaliarProxLinha (   file,
                                                   VMV_ReturnExpectedBool,
                                                   &boolRetA,
                                                   NULL,
                                                   tools,
                                                   casaIterators,
                                                   numCasaIterators );
            if(condRet != VMV_CondRetOK)
               return condRet;
            condRet =     VMV_AvaliarProxLinha (   file,
                                                   VMV_ReturnExpectedBool,
                                                   &boolRetB,
                                                   NULL,
                                                   tools,
                                                   casaIterators,
                                                   numCasaIterators );
            if(condRet != VMV_CondRetOK)
               return condRet;

            if( !(boolRetA == VMV_MovimentoValidoSim) || boolRetB == VMV_MovimentoValidoSim )
            {
               *booleanValue = VMV_MovimentoValidoSim;
               return VMV_CondRetOK;
            }
            else
            {
               *booleanValue = VMV_MovimentoValidoNao;
               return VMV_CondRetOK;
            }
         }
         else if( strcmp( buffer, CMD_PCA_L_NOT ) == 0 )
         {
            if(returnExpected != VMV_ReturnExpectedBool)
               return VMV_CondRetErrFormatoArquivoErrado;

            condRet =     VMV_AvaliarProxLinha (   file,
                                                   VMV_ReturnExpectedBool,
                                                   &boolRetA,
                                                   NULL,
                                                   tools,
                                                   casaIterators,
                                                   numCasaIterators );
            if(condRet != VMV_CondRetOK)
               return condRet;

            if( !(boolRetA == VMV_MovimentoValidoSim) )
            {
               *booleanValue = VMV_MovimentoValidoSim;
               return VMV_CondRetOK;
            }
            else
            {
               *booleanValue = VMV_MovimentoValidoNao;
               return VMV_CondRetOK;
            }
         }
         else if( strcmp( buffer, CMD_PCA_P_IGUAL ) == 0 )
         {
            if(returnExpected != VMV_ReturnExpectedBool)
               return VMV_CondRetErrFormatoArquivoErrado;

            condRet =     VMV_AvaliarProxLinha (   file,
                                                   VMV_ReturnExpectedInteger,
                                                   NULL,
                                                   &intRetA,
                                                   tools,
                                                   casaIterators,
                                                   numCasaIterators );
            if(condRet != VMV_CondRetOK)
               return condRet;

            condRet =     VMV_AvaliarProxLinha (   file,
                                                   VMV_ReturnExpectedInteger,
                                                   NULL,
                                                   &intRetB,
                                                   tools,
                                                   casaIterators,
                                                   numCasaIterators );
            if(condRet != VMV_CondRetOK)
               return condRet;


            if( intRetA == intRetB )
            {
               *booleanValue = VMV_MovimentoValidoSim;
               return VMV_CondRetOK;
            }
            else
            {
               *booleanValue = VMV_MovimentoValidoNao;
               return VMV_CondRetOK;
            }
         }
         else if( strcmp( buffer, CMD_PCA_P_MAIOR ) == 0 )
         {
            if(returnExpected != VMV_ReturnExpectedBool)
               return VMV_CondRetErrFormatoArquivoErrado;

            condRet =     VMV_AvaliarProxLinha (   file,
                                                   VMV_ReturnExpectedInteger,
                                                   NULL,
                                                   &intRetA,
                                                   tools,
                                                   casaIterators,
                                                   numCasaIterators );
            if(condRet != VMV_CondRetOK)
               return condRet;

            condRet =     VMV_AvaliarProxLinha (   file,
                                                   VMV_ReturnExpectedInteger,
                                                   NULL,
                                                   &intRetB,
                                                   tools,
                                                   casaIterators,
                                                   numCasaIterators );
            if(condRet != VMV_CondRetOK)
               return condRet;


            if( intRetA > intRetB )
            {
               *booleanValue = VMV_MovimentoValidoSim;
               return VMV_CondRetOK;
            }
            else
            {
               *booleanValue = VMV_MovimentoValidoNao;
               return VMV_CondRetOK;
            }
         }
         else if( strcmp( buffer, CMD_PCA_P_MENOR ) == 0 )
         {
            if(returnExpected != VMV_ReturnExpectedBool)
               return VMV_CondRetErrFormatoArquivoErrado;

            condRet =     VMV_AvaliarProxLinha (   file,
                                                   VMV_ReturnExpectedInteger,
                                                   NULL,
                                                   &intRetA,
                                                   tools,
                                                   casaIterators,
                                                   numCasaIterators );
            if(condRet != VMV_CondRetOK)
               return condRet;

            condRet =     VMV_AvaliarProxLinha (   file,
                                                   VMV_ReturnExpectedInteger,
                                                   NULL,
                                                   &intRetB,
                                                   tools,
                                                   casaIterators,
                                                   numCasaIterators );
            if(condRet != VMV_CondRetOK)
               return condRet;


            if( intRetA < intRetB )
            {
               *booleanValue = VMV_MovimentoValidoSim;
               return VMV_CondRetOK;
            }
            else
            {
               *booleanValue = VMV_MovimentoValidoNao;
               return VMV_CondRetOK;
            }
         }
         else if( strcmp( buffer, CMD_PCA_P_VAZ ) == 0 )
         {
            if(returnExpected != VMV_ReturnExpectedBool)
               return VMV_CondRetErrFormatoArquivoErrado;

            if( fscanf( file, " %s", buffer ) != 1 )
            {
               return VMV_CondRetErrFormatoArquivoErrado;
            }
            
            if( strcmp( buffer, CMD_PCA_C_A ) == 0 )
            {
               if( tools->vazio(tools->casa_atual,tools->aux) == 1 )
               {
                  *booleanValue = VMV_MovimentoValidoSim;
                  return VMV_CondRetOK;
               }
               else
               {
                  *booleanValue = VMV_MovimentoValidoNao;
                  return VMV_CondRetOK;
               }             
            }
            else if( strcmp( buffer, CMD_PCA_C_D ) == 0 )
            {
               if( tools->vazio(tools->casa_destino,tools->aux) == 1 )
               {
                  *booleanValue = VMV_MovimentoValidoSim;
                  return VMV_CondRetOK;
               }
               else
               {
                  *booleanValue = VMV_MovimentoValidoNao;
                  return VMV_CondRetOK;
               }             
            }
            else
            {
               for(i=0;i<numCasaIterators;i++)
               {
                  if( strcmp( buffer, casaIterators[i].id ) == 0 )
                  {
                     if( tools->vazio(casaIterators[i].casa,tools->aux) == 1 )
                     {
                        *booleanValue = VMV_MovimentoValidoSim;
                        return VMV_CondRetOK;
                     }
                     else
                     {
                        *booleanValue = VMV_MovimentoValidoNao;
                        return VMV_CondRetOK;
                     }               
                  } 
               }
               return VMV_CondRetVariavelNaoExistente;
            }
         }
         else if( strcmp( buffer, CMD_PCA_P_INI ) == 0 )
         {
            if(returnExpected != VMV_ReturnExpectedBool)
               return VMV_CondRetErrFormatoArquivoErrado;

            if( fscanf( file, " %s", buffer ) != 1 )
            {
               return VMV_CondRetErrFormatoArquivoErrado;
            }
            
            if( strcmp( buffer, CMD_PCA_C_A ) == 0 )
            {
               if( tools->inimigo(tools->casa_atual,tools->aux) == 1 )
               {
                  *booleanValue = VMV_MovimentoValidoSim;
                  return VMV_CondRetOK;
               }
               else
               {
                  *booleanValue = VMV_MovimentoValidoNao;
                  return VMV_CondRetOK;
               }             
            }
            else if( strcmp( buffer, CMD_PCA_C_D ) == 0 )
            {
               if( tools->inimigo(tools->casa_destino,tools->aux) == 1 )
               {
                  *booleanValue = VMV_MovimentoValidoSim;
                  return VMV_CondRetOK;
               }
               else
               {
                  *booleanValue = VMV_MovimentoValidoNao;
                  return VMV_CondRetOK;
               }             
            }
            else
            {
               for(i=0;i<numCasaIterators;i++)
               {
                  if( strcmp( buffer, casaIterators[i].id ) == 0 )
                  {
                     if( tools->inimigo(casaIterators[i].casa,tools->aux) == 1 )
                     {
                        *booleanValue = VMV_MovimentoValidoSim;
                        return VMV_CondRetOK;
                     }
                     else
                     {
                        *booleanValue = VMV_MovimentoValidoNao;
                        return VMV_CondRetOK;
                     }               
                  } 
               }
               return VMV_CondRetVariavelNaoExistente;
            }
         }
         else if( strcmp( buffer, CMD_PCA_P_COND ) == 0 )
         {
            if(returnExpected != VMV_ReturnExpectedBool)
               return VMV_CondRetErrFormatoArquivoErrado;

            if( fscanf( file, " %d", &valor ) != 1 )
            {
               return VMV_CondRetErrFormatoArquivoErrado;
            }
            
            if( tools->cond_especiais[valor] == 1)
            {
               *booleanValue = VMV_MovimentoValidoSim;
               return VMV_CondRetOK;
            }
            else
            {
               *booleanValue = VMV_MovimentoValidoNao;
               return VMV_CondRetOK;
            }
         }
         else if( strcmp( buffer, CMD_PCA_F_ADD ) == 0 )
         {
            if(returnExpected != VMV_ReturnExpectedInteger)
               return VMV_CondRetErrFormatoArquivoErrado;

            condRet =     VMV_AvaliarProxLinha (   file,
                                                   VMV_ReturnExpectedInteger,
                                                   NULL,
                                                   &intRetA,
                                                   tools,
                                                   casaIterators,
                                                   numCasaIterators );
            if(condRet != VMV_CondRetOK)
               return condRet;

            condRet =     VMV_AvaliarProxLinha (   file,
                                                   VMV_ReturnExpectedInteger,
                                                   NULL,
                                                   &intRetB,
                                                   tools,
                                                   casaIterators,
                                                   numCasaIterators );
            if(condRet != VMV_CondRetOK)
               return condRet;

            *integerValue = intRetA + intRetB;
            return VMV_CondRetOK;
         }
         else if( strcmp( buffer, CMD_PCA_F_SUB ) == 0 )
         {
            if(returnExpected != VMV_ReturnExpectedInteger)
               return VMV_CondRetErrFormatoArquivoErrado;

            condRet =     VMV_AvaliarProxLinha (   file,
                                                   VMV_ReturnExpectedInteger,
                                                   NULL,
                                                   &intRetA,
                                                   tools,
                                                   casaIterators,
                                                   numCasaIterators );
            if(condRet != VMV_CondRetOK)
               return condRet;

            condRet =     VMV_AvaliarProxLinha (   file,
                                                   VMV_ReturnExpectedInteger,
                                                   NULL,
                                                   &intRetB,
                                                   tools,
                                                   casaIterators,
                                                   numCasaIterators );
            if(condRet != VMV_CondRetOK)
               return condRet;

            *integerValue = intRetA - intRetB;
            return VMV_CondRetOK;
         }
         else if( strcmp( buffer, CMD_PCA_F_MUL ) == 0 )
         {
            if(returnExpected != VMV_ReturnExpectedInteger)
               return VMV_CondRetErrFormatoArquivoErrado;

            condRet =     VMV_AvaliarProxLinha (   file,
                                                   VMV_ReturnExpectedInteger,
                                                   NULL,
                                                   &intRetA,
                                                   tools,
                                                   casaIterators,
                                                   numCasaIterators );
            if(condRet != VMV_CondRetOK)
               return condRet;

            condRet =     VMV_AvaliarProxLinha (   file,
                                                   VMV_ReturnExpectedInteger,
                                                   NULL,
                                                   &intRetB,
                                                   tools,
                                                   casaIterators,
                                                   numCasaIterators );
            if(condRet != VMV_CondRetOK)
               return condRet;

            *integerValue = intRetA - intRetB;
            return VMV_CondRetOK;
         }
         else if( strcmp( buffer, CMD_PCA_F_ABS ) == 0 )
         {
            if(returnExpected != VMV_ReturnExpectedInteger)
               return VMV_CondRetErrFormatoArquivoErrado;

            condRet =     VMV_AvaliarProxLinha (   file,
                                                   VMV_ReturnExpectedInteger,
                                                   NULL,
                                                   &intRetA,
                                                   tools,
                                                   casaIterators,
                                                   numCasaIterators );
            if(condRet != VMV_CondRetOK)
               return condRet;

            *integerValue = intRetA<0?-intRetA:intRetA;
            return VMV_CondRetOK;
         }
         else if( strcmp( buffer, CMD_PCA_V_DIM ) == 0 )
         {
            if(returnExpected != VMV_ReturnExpectedInteger)
               return VMV_CondRetErrFormatoArquivoErrado;

            if( fscanf( file, " %d", &valor ) != 1 )
            {
               return VMV_CondRetErrFormatoArquivoErrado;
            }

            if( fscanf( file, " %s", buffer ) != 1 )
            {
               return VMV_CondRetErrFormatoArquivoErrado;
            }
            
            if( strcmp( buffer, CMD_PCA_C_A ) == 0 )
            {
               *integerValue = (*tools->array_dimensao[valor])(tools->casa_atual,tools->aux);
               return VMV_CondRetOK;          
            }
            else if( strcmp( buffer, CMD_PCA_C_D ) == 0 )
            {
               *integerValue = (*tools->array_dimensao[valor])(tools->casa_destino,tools->aux);
               return VMV_CondRetOK;              
            }
            else
            {
               for(i=0;i<numCasaIterators;i++)
               {
                  if( strcmp( buffer, casaIterators[i].id ) == 0 )
                  {
                     *integerValue = (*tools->array_dimensao[valor])(casaIterators[i].casa,tools->aux);
                     return VMV_CondRetOK;              
                  } 
               }
               return VMV_CondRetVariavelNaoExistente;
            }
         }
         else if( strcmp( buffer, CMD_PCA_V_SIG ) == 0 )
         {
            if(returnExpected != VMV_ReturnExpectedInteger)
               return VMV_CondRetErrFormatoArquivoErrado;

            if( fscanf( file, " %d", &valor ) != 1 )
            {
               return VMV_CondRetErrFormatoArquivoErrado;
            }

            *integerValue = tools->array_sinal[valor];
            return VMV_CondRetOK;  
         }
         else if( strcmp( buffer, CMD_PCA_V_NUM ) == 0 )
         {
            if(returnExpected != VMV_ReturnExpectedInteger)
               return VMV_CondRetErrFormatoArquivoErrado;

            if( fscanf( file, " %d", &valor ) != 1 )
            {
               return VMV_CondRetErrFormatoArquivoErrado;
            }

            *integerValue = valor;
            return VMV_CondRetOK;  
         }
         else if( strcmp( buffer, CMD_PCA_L_FORALL ) == 0 )
         {
            if(returnExpected != VMV_ReturnExpectedBool)
               return VMV_CondRetErrFormatoArquivoErrado;

            if( fscanf( file, " %s", buffer ) != 1 )
            {
               return VMV_CondRetErrFormatoArquivoErrado;
            }

            novoId = (char*) malloc( sizeof(char)* strlen((const unsigned char*)buffer) );
            strcpy(novoId, (const unsigned char*) buffer);

            currentFilePosition = ftell(file);

            for(i=0;i<tools->num_casas;i++)
            {
               novoCasaIterators = (VMV_tpCasaIterator*) malloc( sizeof(VMV_tpCasaIterator)*(numCasaIterators+1) );
               for(j=0;j<numCasaIterators;j++)
               {
                  novoCasaIterators[j].id = casaIterators[j].id;
                  novoCasaIterators[j].casa = casaIterators[j].casa;
               }
               novoCasaIterators[numCasaIterators].id = novoId;
               novoCasaIterators[numCasaIterators].casa = tools->casas[i];

               if( fseek(file, currentFilePosition, SEEK_SET) != 0 )
               {
                  free(novoId);
                  return VMV_CondRetErrManuseioArquivo;
               }

               condRet =     VMV_AvaliarProxLinha (   file,
                                                      VMV_ReturnExpectedBool,
                                                      &boolRetA,
                                                      NULL,
                                                      tools,
                                                      novoCasaIterators,
                                                      numCasaIterators+1 );
               if(condRet != VMV_CondRetOK)
               {
                  free(novoId);
                  return condRet;
               }

               if(boolRetA != VMV_MovimentoValidoSim)
               {
                  free(novoId);
                  *booleanValue = VMV_MovimentoValidoNao;
                  return VMV_CondRetOK;
               }               
            }

            free(novoId);
            *booleanValue = VMV_MovimentoValidoSim;
            return VMV_CondRetOK;  
         }
         else if( strcmp( buffer, CMD_PCA_L_EXIST ) == 0 )
         {
            if(returnExpected != VMV_ReturnExpectedBool)
               return VMV_CondRetErrFormatoArquivoErrado;

            if( fscanf( file, " %s", buffer ) != 1 )
            {
               return VMV_CondRetErrFormatoArquivoErrado;
            }

            novoId = (char*) malloc( sizeof(char)* strlen((const unsigned char*)buffer) );
            strcpy(novoId, (const unsigned char*) buffer);

            currentFilePosition = ftell(file);

            for(i=0;i<tools->num_casas;i++)
            {
               novoCasaIterators = (VMV_tpCasaIterator*) malloc( sizeof(VMV_tpCasaIterator)*(numCasaIterators+1) );
               for(j=0;j<numCasaIterators;j++)
               {
                  novoCasaIterators[j].id = casaIterators[j].id;
                  novoCasaIterators[j].casa = casaIterators[j].casa;
               }
               novoCasaIterators[numCasaIterators].id = novoId;
               novoCasaIterators[numCasaIterators].casa = tools->casas[i];

               if( fseek(file, currentFilePosition, SEEK_SET) != 0 )
               {
                  free(novoId);
                  return VMV_CondRetErrManuseioArquivo;
               }

               condRet =     VMV_AvaliarProxLinha (   file,
                                                      VMV_ReturnExpectedBool,
                                                      &boolRetA,
                                                      NULL,
                                                      tools,
                                                      novoCasaIterators,
                                                      numCasaIterators+1 );
               if(condRet != VMV_CondRetOK)
               {
                  free(novoId);
                  return condRet;
               }

               if(boolRetA == VMV_MovimentoValidoSim)
               {
                  free(novoId);
                  *booleanValue = VMV_MovimentoValidoSim;
                  return VMV_CondRetOK;
               }               
            }

            free(novoId);
            *booleanValue = VMV_MovimentoValidoNao;
            return VMV_CondRetOK;  
         }

         return VMV_CondRetErrComandoNaoExistente;
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

       printf( "" ) ;
      if(pathConfigArq == NULL)
      {
         statusOperacao = VMV_AbreArquivo(CONFIG_DEFAULT_FILE_NAME, &configArq);
      }
      else
      {
         statusOperacao = VMV_AbreArquivo(pathConfigArq, &configArq);
      }
      if(statusOperacao != VMV_CondRetOK)
      {
         return statusOperacao;
      }

      statusOperacao = VMV_LerArquivoConfig(configArq, &pathArqInicial, &pathDirPecas);
      if(statusOperacao != VMV_CondRetOK)
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

      VMV_FechaArquivo(configArq);

      *pConfigDir = pNewConfigDir;

      return VMV_CondRetOK;

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
      return VMV_CondRetOK;
   } /* Fim função: VMV  &Destroi Estrutura de Diretorio de Configuracao */

/***********************************************************************
* Função: VMV  &Ler Tabuleiro Inicial
***********************************************************************/

   VMV_tpCondRet VMV_LerTabuleiroInicial ( VMV_tppConfigDir pConfig, char** pecas, char** cores, int* num_casas )
   {
      int i;

      FILE* arquivoEntrada;

      VMV_tpCondRet statusAberturaArquivo = VMV_AbreArquivo(pConfig->pPathArquivoInicial, &arquivoEntrada);
      
      if(statusAberturaArquivo != VMV_CondRetOK)
      {
         return statusAberturaArquivo;
      }

      if(fscanf(arquivoEntrada, " %d", num_casas) != 1)
      {
         return VMV_CondRetErrFormatoArquivoErrado;
      }

      *pecas = (char*) malloc(sizeof(char)*(*num_casas));
      if(*pecas == NULL)
      {
         return VMV_CondRetErrFaltouMemoria;
      }
      *cores = (char*) malloc(sizeof(char)*(*num_casas));
      if(*cores == NULL)
      {
         free(*cores);
         return VMV_CondRetErrFaltouMemoria;
      }

      for(i=0; i<*num_casas; i++)
      {
         if(fscanf(arquivoEntrada, " %c", &(*pecas)[i]) != 1 || fscanf(arquivoEntrada, " %c", &(*cores)[i]) != 1)
         {
            free(*pecas);
            free(*cores);
            return VMV_CondRetErrFormatoArquivoErrado;
         }
      }

      VMV_FechaArquivo(arquivoEntrada);

      return VMV_CondRetOK;

   } /* Fim função: VMV  &Ler Tabuleiro Inicial */

/***********************************************************************
* Função: VMV  &Checa Movimento de Peça
***********************************************************************/

   VMV_tpCondRet VMV_ChecarMovimentoPeca (   VMV_tppConfigDir pConfig,
                                             VMV_tpMovimentoValido* movimento_valido,
                                             char peca,
                                             void* casa_atual,
                                             void* casa_destino,
                                             void** casas,
                                             int num_casas,
                                             int num_dimensoes,
                                             int (**array_dimensao)(void* casa, void* aux),
                                             int* array_sinal,
                                             int (*vazio)(void* casa, void* aux),
                                             int (*inimigo)(void* casa, void* aux),
                                             int* cond_especiais,
                                             int num_cond_especiais,
                                             void* aux)

   {
      FILE* arquivoMovimento;
      char* pathPecaMov;
      int sizePath;
      VMV_tpExprEvalTools tools;
      VMV_tpCondRet statusAberturaArquivo;
      VMV_tpCondRet status;

      // Open File --------------------------

      sizePath = strlen(pConfig->pPathDirPecas);
      pathPecaMov = (char*) malloc(sizeof(char)*(sizePath+6));
      strcpy(pathPecaMov,pConfig->pPathDirPecas);
      pathPecaMov[sizePath] = peca;
      pathPecaMov[sizePath+1] = '\0';
      strcat(pathPecaMov,".pca");

      statusAberturaArquivo = VMV_AbreArquivo(pathPecaMov, &arquivoMovimento);

      free(pathPecaMov);
      
      if(statusAberturaArquivo != VMV_CondRetOK)
      {
         return statusAberturaArquivo;
      }

      // ----------------------------------

      tools.peca = peca;
      tools.casa_atual = casa_atual;
      tools.casa_destino = casa_destino;
      tools.casas = casas;
      tools.num_casas = num_casas;
      tools.num_dimensoes = num_dimensoes;
      tools.array_dimensao = array_dimensao;
      tools.array_sinal = array_sinal;
      tools.vazio = vazio;
      tools.inimigo = inimigo;
      tools.cond_especiais = cond_especiais;
      tools.num_cond_especiais = num_cond_especiais;
      tools.aux = aux;

      status =     VMV_AvaliarProxLinha (   arquivoMovimento,
                                             VMV_ReturnExpectedBool,
                                             movimento_valido,
                                             NULL,
                                             &tools,
                                             NULL,
                                             0);

      VMV_FechaArquivo(arquivoMovimento);

      return status; 
   } /* Fim função: VMV  &Checa Movimento de Peça*/

/***************************************************************************

/********** Fim do módulo de implementação: VMV  Lista duplamente encadeada **********/


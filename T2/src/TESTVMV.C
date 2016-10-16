/***************************************************************************
*  $MCI Módulo de implementação: TVMV Teste lista de símbolos
*
*  Arquivo gerado:              TestVMV.c
*  Letras identificadoras:      TVMV
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\VMVTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: iars
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       avs   06/10/2016 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "VALIDA_MOV.H"


static const char CRIAR_CONFIG_CMD                [ ] = "=criarconfig"              ;
static const char CRIAR_CONFIG_DEFAULT_CMD        [ ] = "=criarconfigdefault"       ;
static const char DESTRUIR_CONFIG_CMD             [ ] = "=destruirconfig"           ;
static const char LER_TAB_INICIAL_CMD             [ ] = "=lertabinicial"            ;
static const char CHECAR_MOV_PEÇA_CMD             [ ] = "=checarmovpeca"            ;

/***************************************************************************
*
*  Constantes Usadas
*
***************************************************************************/

#define TRUE  1
#define FALSE 0

#define NUM_CASAS 49
#define NUM_DIMENSOES 2
#define NUM_COND_ESPECIAIS 5

typedef struct TVMV_casa{
   int y;
   int x;
   char v;
} TVMV_tpCasa ;

typedef struct TVMV_casa* TVMV_tppCasa;

TVMV_tpCasa casas[49] =  { {0,0,'.'}, {0,1,'.'}, {0,2,'.'}, {0,3,'I'}, {0,4,'.'}, {0,5,'.'}, {0,6,'.'},
                           {1,0,'.'}, {1,1,'.'}, {1,2,'.'}, {1,3,'.'}, {1,4,'.'}, {1,5,'.'}, {1,6,'.'},
                           {2,0,'.'}, {2,1,'I'}, {2,2,'.'}, {2,3,'.'}, {2,4,'.'}, {2,5,'.'}, {2,6,'.'},
                           {3,0,'.'}, {3,1,'F'}, {3,2,'.'}, {3,3,'.'}, {3,4,'.'}, {3,5,'I'}, {3,6,'.'},
                           {4,0,'.'}, {4,1,'.'}, {4,2,'.'}, {4,3,'.'}, {4,4,'.'}, {4,5,'.'}, {4,6,'.'},
                           {5,0,'I'}, {5,1,'I'}, {5,2,'.'}, {5,3,'F'}, {5,4,'F'}, {5,5,'F'}, {5,6,'.'},
                           {6,0,'I'}, {6,1,'I'}, {6,2,'.'}, {6,3,'.'}, {6,4,'.'}, {6,5,'.'}, {6,6,'I'} };


TVMV_tppCasa pCasas[49] =   { &casas[0],  &casas[1],  &casas[2],  &casas[3],  &casas[4],
                              &casas[5],  &casas[6],  &casas[7],  &casas[8],  &casas[9],
                              &casas[10], &casas[11], &casas[12], &casas[13], &casas[14],
                              &casas[15], &casas[16], &casas[17], &casas[18], &casas[19],
                              &casas[20], &casas[21], &casas[22], &casas[23], &casas[24],
                              &casas[25], &casas[26], &casas[27], &casas[28], &casas[29],
                              &casas[30], &casas[31], &casas[32], &casas[33], &casas[34],
                              &casas[35], &casas[36], &casas[37], &casas[38], &casas[39],
                              &casas[40], &casas[41], &casas[42], &casas[43], &casas[44],
                              &casas[45], &casas[46], &casas[47], &casas[48]              };

TVMV_tppCasa getCasa(int x, int y)
{
   return pCasas[7*y+x];
}

int dim0(void* _pCasa,void* aux)
{
   TVMV_tppCasa pCasa = (TVMV_tppCasa) _pCasa;
   (void) aux;
   return pCasa->x;
}

int dim1(void* _pCasa,void* aux)
{
   TVMV_tppCasa pCasa = (TVMV_tppCasa) _pCasa;
   (void) aux;
   return pCasa->y;
}

int (*dimensao[2]) (void* _pCasa,void* aux) = {dim0, dim1};

int sinal[2] = {0,1};

int vazio(void* _pCasa,void* aux)
{
   TVMV_tppCasa pCasa = (TVMV_tppCasa) _pCasa;
   (void) aux;
   return pCasa->v == '.'?1:0;
}

int inimigo(void* _pCasa,void* aux)
{
   TVMV_tppCasa pCasa = (TVMV_tppCasa) _pCasa;
   (void) aux;
   return pCasa->v == 'I'?1:0;
}

int condicoesEspeciais[5] = {0,1,0,1,0};

/**************************************************************************
* Variáveis Globais
***************************************************************************/

VMV_tppConfigDir configDirBeingTested;
int configDirAberto = FALSE;

/***** Protótipos das funções encapuladas no módulo *****/


/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TVMV &Testar Validado de Movimento
*
*  O teste utiliza um arquivo de configuração global.
*  Uma vez criada uma config, somente será possivel criar
*  uma nova com sucesso após destruir a primeira.
*
*  $ED Descrição da função
*
*     Comandos disponíveis:
*
*     =criarconfig condRet pathArquivo
*     =criarconfigdefault condRet
*     =destruirconfig condRet
*     =lertabinicial condRet numCasasEsperado  pecasStringEsperado coresStringEsperado
*     =checarmovpeca condRet movValidoSimOuNao peca xAtual yAtual xDestino yDestino*
*
* --------------------------------------------
*
*  Geometria do Tabuleiro Utilizada no Comando checarmovpeca
*
*   NUM DIMENSIONS = 2
*   NUM_COND_ESPECIAIS = 5
*   COND_ESPECIAIS = {0,1,0,1,0}
*
*      0   1   2   3   4   5   6 ----> DIM 0, SIG 0, X
*   0  .   .   .   I   .   .   .
*   1  .   .   .   .   .   .   .
*   2  .   I   .   .   .   .   .
*   3  .   F   .   .   .   I   .
*   4  .   .   .   .   .   .   .
*   5  I   I   .   F   F   F   .
*   6  I   I   .   .   .   .   I
*   |
*   |
*   V
*   DIM 1
*   SIG 1
*   Y
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * comandoTeste )
   {
      int i;

      int numParametrosLidos;
      char configPath[100];

      char* pecasStringRecebido;
      char* coresStringRecebido;

      char pecasStringEsperado[100];
      char coresStringEsperado[100];

      int numCasasLidasRecebido;
      int numCasasLidasEsperado;

      VMV_tpCondRet condRetEsperada;
      VMV_tpCondRet condRetRecebida;

      int xAtual;
      int yAtual;

      int xDest;
      int yDest;

      char peca;

      VMV_tpMovimentoValido validezMovimentoRecebida;
      VMV_tpMovimentoValido validezMovimentoRecebidaEsperada; // VMV_MovimentoValidoNao VMV_MovimentoValidoSim

      TVMV_tppCasa casaAtual;
      TVMV_tppCasa casaDestino;


      if( strcmp( comandoTeste , CRIAR_CONFIG_CMD ) == 0 )
      {

         numParametrosLidos = LER_LerParametros(   "is" ,
                                                   &condRetEsperada,
                                                   &configPath );

         if( numParametrosLidos != 2 || configDirAberto == TRUE )
         {
            return TST_CondRetParm ;
         }

         condRetRecebida = VMV_CriarConfigDir(  &configDirBeingTested, 
                                                configPath );

         if(condRetRecebida == VMV_CondRetOK)
         {
            configDirAberto = TRUE;
         }

         if( condRetEsperada == condRetRecebida)
         {
            return TST_CondRetOK;
         }
         else
         {
            return TST_NotificarFalha("Condicao de retorno recebida diferente da esperada.");
         }

      }
      else if( strcmp( comandoTeste , CRIAR_CONFIG_DEFAULT_CMD ) == 0 )
      {

         numParametrosLidos = LER_LerParametros(   "i" ,
                                                   &condRetEsperada );

         if( numParametrosLidos != 1 || configDirAberto == TRUE )
         {
            return TST_CondRetParm ;
         }

         condRetRecebida = VMV_CriarConfigDir(  &configDirBeingTested, 
                                                NULL );

         if(condRetRecebida == VMV_CondRetOK)
         {
            configDirAberto = TRUE;
         }

         if( condRetEsperada == condRetRecebida)
         {
            return TST_CondRetOK;
         }
         else
         {
            return TST_NotificarFalha("Condicao de retorno recebida diferente da esperada.");
         }

      }
      else if( strcmp( comandoTeste , DESTRUIR_CONFIG_CMD ) == 0 )
      {
         numParametrosLidos = LER_LerParametros(   "i" ,
                                                   &condRetEsperada );
         if( numParametrosLidos != 1 || configDirAberto == FALSE )
         {
            return TST_CondRetParm ;
         }
         condRetRecebida = VMV_DestruirConfigDir( configDirBeingTested );

         if(condRetRecebida == VMV_CondRetOK)
         {
            configDirAberto = FALSE;
         }

         if( condRetEsperada == condRetRecebida)
         {
            return TST_CondRetOK;
         }
         else
         {
            return TST_NotificarFalha("Condicao de retorno recebida diferente da esperada.");
         }
      }
      else if( strcmp( comandoTeste , LER_TAB_INICIAL_CMD ) == 0 )
      {
         numParametrosLidos = LER_LerParametros(   "iiss" ,
                                                   &condRetEsperada,
                                                   &numCasasLidasEsperado,
                                                   pecasStringEsperado,
                                                   coresStringEsperado );

         if( numParametrosLidos != 4 || configDirAberto == FALSE )
         {
            return TST_CondRetParm ;
         }

         condRetRecebida = VMV_LerTabuleiroInicial(   configDirBeingTested, 
                                                      &pecasStringRecebido,
                                                      &coresStringRecebido,
                                                      &numCasasLidasRecebido );

         if( condRetEsperada != condRetRecebida )
         {
            if( condRetRecebida == VMV_CondRetOK )
            {
               free(pecasStringRecebido);
               free(coresStringRecebido);
            }
            return TST_NotificarFalha("Condicao de retorno recebida diferente da esperada.");
         }

         if( condRetRecebida == VMV_CondRetErrFaltouMemoria )
         {
            return TST_CondRetMemoria;
         }

         if( condRetRecebida != VMV_CondRetOK )
         {
            return TST_CondRetOK;
         }

         if( numCasasLidasRecebido != numCasasLidasEsperado )
         {
            if( condRetRecebida == VMV_CondRetOK )
            {
               free(pecasStringRecebido);
               free(coresStringRecebido);
            }
            return TST_NotificarFalha("Numero de casas lidas diferente do esperado.");
         }

         for( i=0; i<numCasasLidasRecebido; i++)
         {
            if( pecasStringRecebido[i] != pecasStringEsperado[i] )
            {
               if( condRetRecebida == VMV_CondRetOK )
               {
                  free(pecasStringRecebido);
                  free(coresStringRecebido);
               }
               return TST_NotificarFalha("Pecas recebidas diferentes do esperado.");
            }
            if( coresStringRecebido[i] != coresStringEsperado[i] )
            {
               if( condRetRecebida == VMV_CondRetOK )
               {
                  free(pecasStringRecebido);
                  free(coresStringRecebido);
               }
               return TST_NotificarFalha("Cores recebidas diferentes do esperado.");
            }
         }

         free(pecasStringRecebido);
         free(coresStringRecebido);
         return TST_CondRetOK;
      }
      else if( strcmp( comandoTeste , CHECAR_MOV_PEÇA_CMD ) == 0 )
      {
         numParametrosLidos = LER_LerParametros(   "iiciiii" ,
                                                   &condRetEsperada,
                                                   &validezMovimentoRecebidaEsperada,
                                                   &peca,
                                                   &xAtual,
                                                   &yAtual,
                                                   &xDest,
                                                   &yDest );

         if( numParametrosLidos != 7 || configDirAberto == FALSE )
         {
            return TST_CondRetParm ;
         }

         casaAtual = getCasa(xAtual,yAtual);
         casaDestino = getCasa(xDest,yDest);

         condRetRecebida = VMV_ChecarMovimentoPeca (  configDirBeingTested,
                                                      &validezMovimentoRecebida,
                                                      peca,
                                                      casaAtual,
                                                      casaDestino,
                                                      pCasas,
                                                      NUM_CASAS,
                                                      NUM_DIMENSOES,
                                                      dimensao,
                                                      sinal,
                                                      vazio,
                                                      inimigo,
                                                      condicoesEspeciais,
                                                      NUM_COND_ESPECIAIS,
                                                      NULL);

         if( condRetEsperada != condRetRecebida )
         {
            return TST_NotificarFalha("Condicao de retorno recebida diferente da esperada.");
         }

         if( condRetRecebida != VMV_CondRetOK )
         {
            return TST_CondRetOK;
         }

         if( validezMovimentoRecebidaEsperada != validezMovimentoRecebida )
         {
            return TST_NotificarFalha("Condicao de validez de movimento diferente do esperado.");
         } 

         return TST_CondRetOK;    
      }

      return TST_CondRetNaoConhec ;
   }
/***************************************************************************
*  $MCI Módulo de implementação: TLIS Teste lista de símbolos
*
*  Arquivo gerado:              TestLIS.c
*  Letras identificadoras:      TLIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs, vas
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     5       vas   14/set/2016 adaptação dos testes para funcionar com a lista modificada
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Lista.h"
#include    "Etiqueta_nominal.h"


static const char RESET_LISTA_CMD         [ ] = "=resetteste"     ;
static const char CRIAR_LISTA_CMD         [ ] = "=criarlista"     ;
static const char DESTRUIR_LISTA_CMD      [ ] = "=destruirlista"  ;
static const char ESVAZIAR_LISTA_CMD      [ ] = "=esvaziarlista"  ;
static const char INS_ELEM_ANTES_CMD      [ ] = "=inselemantes"   ;
static const char INS_ELEM_APOS_CMD       [ ] = "=inselemapos"    ;
static const char INS_ELEM_ORD_CMD        [ ] = "inselemanord"    ;
static const char OBTER_VALOR_CMD         [ ] = "=obtervalorelem" ;
static const char EXC_ELEM_CMD            [ ] = "=excluirelem"    ;
static const char IR_INICIO_CMD           [ ] = "=irinicio"       ;
static const char IR_FIM_CMD              [ ] = "=irfinal"        ;
static const char AVANCAR_ELEM_CMD        [ ] = "=avancarelem"    ;
static const char PROCURA_VALOR_CMD       [ ] = "=procurarvalor"  ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA 10
#define DIM_VALOR    100

LIS_tppLista vtListas[ DIM_VT_LISTA ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static int ValidarInxLista( int inxLista , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Testar lista
*
*  $ED Descrição da função
*     Podem ser criadas até 10 listas, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de listas. Provoca vazamento de memória
*     =criarlista                   inxLista
*     =destruirlista                inxLista
*     =esvaziarlista                inxLista
*     =inselemantes                 inxLista  iniciais  nomeCompleto  paramNULL  CondRetEsp
*     =inselemapos                  inxLista  iniciais  nomeCompleto  paramNULL  CondRetEsp
*     =inselemanord                 inxLista  iniciais  nomeCompleto  paramNull  CondRetEsp
*     =obtervalorelem               inxLista  iniciais  nomeCompleto  CondretPonteiro
*     =excluirelem                  inxLista  CondRetEsp
*     =irinicio                     inxLista
*     =irfinal                      inxLista
*     =avancarelem                  inxLista  numElem CondRetEsp
*     =procurarvalor                inxLista  iniciais  nomeCompleto  paramNULL  CondRetEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxLista  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ;

      TST_tpCondRet CondRet ;

      char   StringIniciais[  DIM_VALOR ] ;
      char   StringNome[ DIM_VALOR ] ;
      ETI_tppEtiquetaNominal * pEtiquetaNominal ;

      int ValEsp = -1 ;

      int paramNULL = -1 ;

      int i ;

      int numElem = -1 ;

      StringDado[ 0 ] = 0 ;

      /* Efetuar reset de teste de lista */

         if ( strcmp( ComandoTeste , RESET_LISTA_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_LISTA ; i++ )
            {
               vtListas[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de lista */

      /* Testar CriarLista */

         else if ( strcmp( ComandoTeste , CRIAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                       &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            vtListas[ inxLista ] =
                 LIS_CriarLista( ) ;

            return TST_CompararPonteiroNulo( 1 , vtListas[ inxLista ] ,
               "Erro em ponteiro de nova lista."  ) ;

         } /* fim ativa: Testar CriarLista */

      /* Testar Esvaziar lista lista */

         else if ( strcmp( ComandoTeste , ESVAZIAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_EsvaziarLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Esvaziar lista lista */

      /* Testar Destruir lista */

         else if ( strcmp( ComandoTeste , DESTRUIR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_DestruirLista( vtListas[ inxLista ] ) ;
            vtListas[ inxLista ] = NULL ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Destruir lista */

      /* Testar inserir elemento antes */

         else if ( strcmp( ComandoTeste , INS_ELEM_ANTES_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "issii" ,
                       &inxLista , StringIniciais , StringNome , &paramNULL , &CondRetEsp ) ;

            if ( ( numLidos != 5 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pEtiquetaNominal = ETI_CriarEtiquetaNominal(StringIniciais, StringNome) ;
            if ( pEtiquetaNominal == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            if (paramNULL)
            {
              CondRet = LIS_InserirElementoAntes( vtListas[ inxLista ] , pEtiquetaNominal ) ;
            }
            else
            {
              CondRet = LIS_InserirElementoAntes( vtListas[ inxLista ] , NULL ) ;
              EIT_DestruirEtiquetaNominal( pEtiquetaNominal ) ;
            }
            

            if ( CondRet != LIS_CondRetOK )
            {
               EIT_DestruirEtiquetaNominal( pEtiquetaNominal ) ;
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir antes."                   ) ;

         } /* fim ativa: Testar inserir elemento antes */

      /* Testar inserir elemento apos */

         else if ( strcmp( ComandoTeste , INS_ELEM_APOS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "issii" ,
                       &inxLista , StringIniciais , StringNome , &paramNULL , &CondRetEsp ) ;

            if ( ( numLidos != 5 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pEtiquetaNominal = ETI_CriarEtiquetaNominal(StringIniciais, StringNome) ;
            if ( pEtiquetaNominal == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            if (paramNULL)
            {
              CondRet = LIS_InserirElementoApos( vtListas[ inxLista ] , pEtiquetaNominal ) ;
            }
            else
            {
              CondRet = LIS_InserirElementoApos( vtListas[ inxLista ] , NULL ) ;
              EIT_DestruirEtiquetaNominal( pEtiquetaNominal ) ;
            }

            if ( CondRet != LIS_CondRetOK )
            {
               EIT_DestruirEtiquetaNominal( pEtiquetaNominal ) ;
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir apos."                   ) ;

         } /* fim ativa: Testar inserir elemento apos */

       /* Testar inserir elemento ordenado */

         else if ( strcmp( ComandoTeste , INS_ELEM_ORD_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "issii" ,
                       &inxLista , StringIniciais , StringNome , &paramNULL , &CondRetEsp ) ;

            if ( ( numLidos != 5 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pEtiquetaNominal = ETI_CriarEtiquetaNominal(StringIniciais, StringNome) ;
            if ( pEtiquetaNominal == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            if (paramNULL)
            {
              CondRet = LIS_InserirElementoOrdenado( vtListas[ inxLista ] , pEtiquetaNominal ) ;
            }
            else
            {
              CondRet = LIS_InserirElementoOrdenado( vtListas[ inxLista ] , NULL ) ;
              EIT_DestruirEtiquetaNominal( pEtiquetaNominal ) ;
            }

            if ( CondRet != LIS_CondRetOK )
            {
               EIT_DestruirEtiquetaNominal( pEtiquetaNominal ) ;
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir apos."                   ) ;

         } /* fim ativa: Testar inserir elemento ordenado */

      /* Testar excluir simbolo */

         else if ( strcmp( ComandoTeste , EXC_ELEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                  &inxLista , &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      LIS_ExcluirElemento( vtListas[ inxLista ] ) ,
                     "Condição de retorno errada ao excluir."   ) ;

         } /* fim ativa: Testar excluir simbolo */

      /* Testar obter valor do elemento corrente */

         else if ( strcmp( ComandoTeste , OBTER_VALOR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "issi" ,
                       &inxLista , StringNome , StringIniciais , &ValEsp ) ;

            if ( ( numLidos != 4 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pEtiquetaNominal = LIS_ObterValor( vtListas[inxLista] ) ;

            if ( ValEsp == 0 )
            {
               return TST_CompararPonteiroNulo( 0 , pEtiquetaNominal ,
                         "Valor não deveria existir." ) ;
            } /* if */

            if ( pEtiquetaNominal == NULL )
            {
               return TST_CompararPonteiroNulo( 1 , pEtiquetaNominal ,
                         "Dado tipo um deveria existir." ) ;
            } /* if */

            return TST_CompararString( StringNome , pEtiquetaNominal->nomeCompleto ,
                         "Valor do nome errado." ) &&
                   TST_CompararString( StringIniciais , pEtiquetaNominal->iniciais ,
                         "Valor da inicial errado." ) ;

         } /* fim ativa: Testar obter valor do elemento corrente */

      /* Testar ir para o elemento inicial */

         else if ( strcmp( ComandoTeste , IR_INICIO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            IrInicioLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar ir para o elemento inicial */

      /* LIS  &Ir para o elemento final */

         else if ( strcmp( ComandoTeste , IR_FIM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            IrFinalLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: LIS  &Ir para o elemento final */

      /* LIS  &Avançar elemento */

         else if ( strcmp( ComandoTeste , AVANCAR_ELEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" , &inxLista , &numElem ,
                                &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      LIS_AvancarElementoCorrente( vtListas[ inxLista ] , numElem ) ,
                      "Condicao de retorno errada ao avancar" ) ;

         } /* fim ativa: LIS  &Avançar elemento */

      /* LIS  &Procurar valor */

         else if ( strcmp( ComandoTeste , PROCURA_VALOR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "issii" , &inxLista , StringNome ,
                                StringIniciais , &paramNULL , &CondRetEsp ) ;

            if ( ( numLidos != 5 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pEtiquetaNominal = ETI_CriarEtiquetaNominal(StringIniciais, StringNome) ;
            if ( pEtiquetaNominal == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            if (paramNULL)
            {
              CondRet = LIS_ProcurarValor( vtListas[ inxLista ] , pEtiquetaNominal ) ;
            }
            else
            {
              CondRet = LIS_ProcurarValor( vtListas[ inxLista ] , NULL ) ;
            }

            EIT_DestruirEtiquetaNominal( pEtiquetaNominal ) ;

            return TST_CompararInt( CondRetEsp ,
                      CondRet ,
                      "Condicao de retorno errada ao procurar valor" ) ;

         } /* fim ativa: LIS  &Procurar valor */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TLIS &Testar lista */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim função: TLIS -Destruir valor */


/***********************************************************************
*
*  $FC Função: TLIS -Validar indice de lista
*
***********************************************************************/

   int ValidarInxLista( int inxLista , int Modo )
   {

      if ( ( inxLista <  0 )
        || ( inxLista >= DIM_VT_LISTA ))
      {
         return FALSE ;
      } /* if */

      if ( Modo == VAZIO )
      {
         if ( vtListas[ inxLista ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtListas[ inxLista ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */

      return TRUE ;

   } /* Fim função: TLIS -Validar indice de lista */

/********** Fim do módulo de implementação: TLIS Teste lista de símbolos **********/

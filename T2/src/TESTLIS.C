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
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     5       vas   04/out/2016 modificar as funções de teste para as expecificadas no enunciado
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


static const char RESET_LISTA_CMD            [ ] = "=resetteste"        ;
static const char CRIAR_LISTA_CMD            [ ] = "=criarlista"        ;
static const char OBTER_ID_LISTA_CMD         [ ] = "=obterIdLista"      ;
static const char INSERIR_NO_CMD             [ ] = "=inserirNo"         ;
static const char OBTER_NO_CMD               [ ] = "=obterNo"           ;
static const char EXCLUIR_NO_CMD             [ ] = "=excluirNoCorrente" ;
static const char IR_PROX_CMD                [ ] = "=irProx"            ;
static const char IR_ANT_CMD                 [ ] = "=irAnt"             ;
static const char ALTERAR_NO_CMD             [ ] = "=alterarNoCorrente" ;
static const char DESTROI_LISTA_CMD          [ ] = "=destroiLista"      ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10
#define DIM_VALOR     100

LIS_tppLista   vtListas[ DIM_VT_LISTA ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pDado ) ;

   static int CompararValor( void * pDado_1 , void * pDado_2 ) ;

   static int IgualValor( void * pDado_1 , void * pDado_2 ) ;

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
*     =criarlista                   inx    idLista      condRetorno
*     =obterIdLista                 inx    idLista
*     =inserirNo                    inx    char         condRetorno
*     =obterNo                      inx    char         condRetorno
*     =excluirNoCorrente            inx
*     =irProx                       inx    condRetorno
*     =irAnt                        inx    condRetorno
*     =alterarNoCorrente            inx    char         condRetorno
*     =destroiLista                 inx    condRetorno
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxLista  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ;

      TST_tpCondRet CondRet ;

      char idLista[4] ;
      char idListaEsp[4] ;

      char pValor[10] ;
      char pValorEsp[10] ;

      int i ;

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

            numLidos = LER_LerParametros( "isi" ,
                       &inxLista , idListaEsp , &CondRetEsp) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = LIS_CriarLista( vtListas[ inxLista ] , idLista ,
                                      DestruirValor , CompararValor ,  IgualValor ) ;

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao criar lista." ) ;

         } /* fim ativa: Testar CriarLista */

      /* Testar Obter id lista */

         else if ( strcmp( ComandoTeste , OBTER_ID_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "is" ,
                               &inxLista , idListaEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_ObterId( vtListas[ inxLista ] , idLista ) ;
            if ( strcmp( idLista , idListaEsp ) == 0 )
            {
              return TST_CondRetOK ;
            }/* if */

            return TST_CondRetErro ;

         } /* fim ativa: Testar Obter id lista */

      /* Testar Inserir no na lista */

         else if ( strcmp( ComandoTeste , INSERIR_NO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                               &inxLista , pValorEsp , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = LIS_InserirElementoApos( vtListas[ inxLista ] , ( void * )pValorEsp ) ;

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir apos." ) ;

         } /* fim ativa: Testar Inserir no na lista */

      /* Testar Obter no corrente da lista */

         else if ( strcmp( ComandoTeste , OBTER_NO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                               &inxLista , pValorEsp , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = LIS_ObterValor( vtListas[ inxLista ] , ( void * )pValor ) ;

            if ( CondRetEsp )
            {
              return TST_CompararInt( CondRetEsp , CondRet ,
                     "Lista deveria estar vazia." ) ;
            }/* if */

            if ( strcmp( pValor , pValorEsp ) == 0 )
            {
              return TST_CondRetOK ;
            }/* if */

            TST_NotificarFalha( "Valor da lista recebido errado." ) ;

         } /* fim ativa: Testar Obter no corrente da lista */

      /* Testar Excluir no corrente da lista */

         else if ( strcmp( ComandoTeste , EXCLUIR_NO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = LIS_ExcluirElemento( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Excluir no corrente da lista */

      /* Testar Ir pro próximo elemento da lista */

         else if ( strcmp( ComandoTeste , IR_PROX_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                               &inxLista , &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = LIS_AvancarElementoCorrente( vtListas[ inxLista ] , 1 ) ;

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao avançar um elemento." ) ;

         } /* fim ativa: Testar Ir pro próximo elemento da lista */

      /* Testar Ir pro elemento anterior da lista */

         else if ( strcmp( ComandoTeste , IR_ANT_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                               &inxLista , &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = LIS_AvancarElementoCorrente( vtListas[ inxLista ] , -1 ) ;

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao retornar um elemento." ) ;

         } /* fim ativa: Testar Ir pro elemento anterior da lista */

      /* Testar Alterar elemento do nó corrente da lista */

         else if ( strcmp( ComandoTeste , IR_ANT_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                               &inxLista , pValorEsp , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = LIS_AlteraValor( vtListas[ inxLista ] , ( void * )pValorEsp ) ;

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao alterar o elemento." ) ;

         } /* fim ativa: Testar Alterar elemento do nó corrente da lista */

      /* Testar Destruir lista */

         else if ( strcmp( ComandoTeste , DESTROI_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                               &inxLista , &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = LIS_DestruirLista( vtListas[ inxLista ] ) ;

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao destruir a lista." ) ;

         } /* fim ativa: Testar Destruir lista */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TLIS &Testar lista */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pDado )
   {
      char * valor = ( char * ) pDado ;
      free( valor ) ;
      valor = NULL ;

   } /* Fim função: TLIS -Destruir valor */


/***********************************************************************
*
*  $FC Função: TLIS -Comparar valor
*
***********************************************************************/

   int CompararValor( void * pDado_1 , void * pDado_2 )
   {
      char * valor_1 = ( char * ) pDado_1 ;
      char * valor_2 = ( char * ) pDado_2 ;
      return strcmp( valor_1 , valor_2 ) ;

   } /* Fim função: TLIS -Comparar valor */


/***********************************************************************
*
*  $FC Função: TLIS -Igual valor
*
***********************************************************************/

   int IgualValor( void * pDado_1 , void * pDado_2 )
   {
      char * valor_1 = ( char * ) pDado_1 ;
      char * valor_2 = ( char * ) pDado_2 ;
      return strcmp( valor_1 , valor_2 ) ;

   } /* Fim função: TLIS -Igual valor */


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

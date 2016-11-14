/***************************************************************************
*  $MCI Módulo de implementação: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs, iars, vas
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     8       vas   13/nov/2016 adição da implementação da função de comparar listas
*     7       vas   11/nov/2016 adição da função de lista vazia
*     6       vas   03/out/2016 ajuste das funções para todas terem condições de retorno
*                               e retirada de funções não utilizadas
*     5       iars  14/set/2016 inserção ordenada, procurar valor, imprimir
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

   typedef struct tagElemLista {

         void * pValor ;
               /* Ponteiro para o valor contido no elemento */

         struct tagElemLista * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemLista * pProx ;
               /* Ponteiro para o elemento sucessor */

   } tpElemLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabeça de lista
*
*
***********************************************************************/

   typedef struct LIS_tagLista {

         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */

         int numElem ;
               /* Número de elementos da lista */

         char * idLista ;
               /* Identificação da lista */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a função de destruição do valor contido em um elemento */
         
         int ( * CompararValores ) ( void * pValor_1, void * pValor_2 ) ;
               /* Ponteiro para a função de comparação de valores */
         
         int ( * Igual ) ( void * pValor_1, void * pValor_2 ) ;
               /* Ponteiro para a função de checagem de igualdade de valores */

   } LIS_tpLista ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       void *       pValor  ) ;

   static void LIS_EsvaziarLista( LIS_tppLista pLista ) ;

   static void LimparCabeca( LIS_tppLista pLista ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: LIS  &Criar lista
*  ****/

   LIS_tpCondRet LIS_CriarLista( LIS_tppLista * pLista ,
             char * idLista ,
             void   ( * ExcluirValor ) ( void * pDado ),
             int   ( * CompararValores ) ( void * pDado_1, void * pDado_2 ),
             int   ( * Igual ) ( void * pDado_1, void * pDado_2 ) )
   {

      LIS_tppLista pNewLista = NULL ;

      pNewLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
      if ( pNewLista == NULL )
      {
         return LIS_CondRetFaltouMemoria ;
      } /* if */

      LimparCabeca( pNewLista ) ;

      pNewLista->idLista = ( char * ) malloc ( strlen ( idLista ) + 1 ) ;
      strcpy( pNewLista->idLista , idLista ) ;
      pNewLista->ExcluirValor = ExcluirValor ;
      pNewLista->CompararValores = CompararValores ;
      pNewLista->Igual = Igual ;

      *pLista = pNewLista ;

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Criar lista */

/***************************************************************************
*
*  Função: LIS  &Destruir lista
*  ****/

   LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista )
   {

      if ( pLista == NULL )
      {
         return LIS_CondRetListaNaoExiste ;
      } /* if */

      LIS_EsvaziarLista( pLista ) ;

      free( pLista ) ;

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Destruir lista */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento após
*  ****/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        )
   {

      tpElemLista * pElem ;;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inerir após */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento após o elemento */

         if ( pLista->pElemCorr == NULL )
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pProx != NULL )
            {
               pElem->pProx  = pLista->pElemCorr->pProx ;
               pLista->pElemCorr->pProx->pAnt = pElem ;
            } else
            {
               pLista->pFimLista = pElem ;
            } /* if */

            pElem->pAnt = pLista->pElemCorr ;
            pLista->pElemCorr->pProx = pElem ;

         } /* if */
                  
         pLista->pElemCorr = pElem ;
                  
         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Inserir elemento após */

/***************************************************************************
*
*  Função: LIS  &Excluir elemento
*  ****/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      pElem = pLista->pElemCorr ;

      /* Desencadeia à esquerda */

         if ( pElem->pAnt != NULL )
         {
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
         } else {
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } /* if */

      /* Desencadeia à direita */

         if ( pElem->pProx != NULL )
         {
            pElem->pProx->pAnt = pElem->pAnt ;
         } else
         {
            pLista->pFimLista = pElem->pAnt ;
         } /* if */

      LiberarElemento( pLista , pElem ) ;

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Excluir elemento */

/***************************************************************************
*
*  Função: LIS  &Obter referência para o valor contido no elemento
*  ****/

   LIS_tpCondRet LIS_ObterValor( LIS_tppLista pLista , void ** elementoCorrente )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */
      
      *elementoCorrente = pLista->pElemCorr->pValor ;

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Obter referência para o valor contido no elemento */

/***************************************************************************
*
*  Função: LIS  &Obter referência para a identificação contida na cabeça da lista
*  ****/

   LIS_tpCondRet LIS_ObterId( LIS_tppLista pLista , char ** idLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif
      
      *idLista = pLista->idLista ;

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Obter referência para a identificação contida na cabeça da lista */

/***************************************************************************
*
*  Função: LIS  &Avançar elemento
*  ****/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem )
   {

      int i ;

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Tratar lista vazia */

         if ( pLista->pElemCorr == NULL )
         {
            return LIS_CondRetListaVazia ;
         } /* fim ativa: Tratar lista vazia */

      /* Tratar avançar para frente */

         if ( numElem > 0 )
         {

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i > 0 ; i-- )
            {
               if ( pElem == NULL )
               {
                  break ;
               } /* if */
               pElem = pElem->pProx ;
            } /* for */

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pFimLista ;
            return LIS_CondRetNoCorrenteUlt ;

         } /* fim ativa: Tratar avançar para frente */

      /* Tratar avançar para trás */

         else if ( numElem < 0 )
         {

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i < 0 ; i++ )
            {
               if ( pElem == NULL )
               {
                  break ;
               } /* if */
               pElem = pElem->pAnt ;
            } /* for */

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pOrigemLista ;
            return LIS_CondRetNoCorrentePrim ;

         } /* fim ativa: Tratar avançar para trás */

      /* Tratar não avançar */

         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Avançar elemento */

/***************************************************************************
*
*  Função: LIS  &Altera conteudo do nó corrente
*  ****/

   LIS_tpCondRet LIS_AlteraValor( LIS_tppLista pLista ,
                                    void * pValor )
   {

      if ( pLista == NULL )
      {
         return LIS_CondRetListaNaoExiste ;
      }/* if */

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      pLista->pElemCorr->pValor = pValor;

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Altera conteudo do nó corrente */

/***************************************************************************
*
*  Função: LIS  &Verifica se a lista está vazia
*  ****/

   LIS_tpCondRet LIS_VerificaVazia( LIS_tppLista pLista ,
                                    int * vazia )
   {

      if ( pLista == NULL )
      {
         return LIS_CondRetListaNaoExiste ;
      } /* if */

      if ( pLista->numElem == 0 )
      {
         *vazia = 1 ;
      }
      else
      {
         *vazia = 0 ;
      } /* if */

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Verifica se a lista está vazia */

/***************************************************************************
*
*  Função: LIS  &Compara duas listas
*  ****/

   LIS_tpCondRet LIS_VerificaIgualdade( LIS_tppLista pLista1 ,
                                        LIS_tppLista pLista2 ,
                                        int * igualdade )
   {

      int i ;

      if ( pLista1 == NULL || pLista2 == NULL )
      {
         *igualdade = 0 ;
         return LIS_CondRetListaNaoExiste ;
      } /* if */

      if ( pLista1->numElem != pLista2->numElem )
      {
         *igualdade = 0 ;
         return LIS_CondRetOK ;
      } /* if */

      for ( i = 0 ; i < pLista1->numElem ; i++ )
      {
         if ( !pLista1->CompararValores( pLista1->pElemCorr , pLista2->pElemCorr ) )
         {
            *igualdade = 0;
            return LIS_CondRetOK ;
         } /* if */

         LIS_AvancarElementoCorrente( pLista1 , 1 ) ;
         LIS_AvancarElementoCorrente( pLista2 , 1 ) ;

      } /* for */

      *igualdade = 1 ;

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Verifica se a lista está vazia */

/***************************************************************************
*
*  Função: LIS  &Esvazia lista
*  ****/

   LIS_tpCondRet LIS_Esvazia( LIS_tppLista pLista )
   {

      int i ;

      if ( pLista == NULL )
      {
         return LIS_CondRetListaNaoExiste ;
      } /* if */

      printf("Vai entrar no while\n");

      while( pLista->pElemCorr->pProx != NULL ) {
         printf("Entrou no while\n");
         LIS_AvancarElementoCorrente( pLista , 1 ) ;
      }
      printf("Saiu do while\n");

      for ( i = 0 ; i < pLista->numElem ; i++ )
      {
         printf("Entrou no for\n");
         LIS_AvancarElementoCorrente( pLista, -1 ) ;
         pLista->numElem-- ;
         pLista->pElemCorr->pProx = NULL ;
      } /* for */

      printf("Saiu do for\n");

      pLista->pElemCorr = NULL ;
      pLista->numElem-- ;

      printf("Acabou LIS_Esvazia\n");

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Esvazia lista */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: LIS  -Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
*
***********************************************************************/

   void LiberarElemento( LIS_tppLista   pLista ,
                         tpElemLista  * pElem   )
   {

      if ( ( pLista->ExcluirValor != NULL )
        && ( pElem->pValor != NULL        ))
      {
         pLista->ExcluirValor( pElem->pValor ) ;
      } /* if */

      free( pElem ) ;

      pLista->numElem-- ;

   } /* Fim função: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Função: LIS  -Criar o elemento
*
***********************************************************************/

   tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                void *       pValor  )
   {

      tpElemLista * pElem ;

      pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
      if ( pElem == NULL )
      {
         return NULL ;
      } /* if */

      pElem->pValor = pValor ;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;

      pLista->numElem ++ ;

      return pElem ;

   } /* Fim função: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Função: LIS  -Esvaziar a lista
*
***********************************************************************/

   void LIS_EsvaziarLista( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;
      tpElemLista * pProx ;

      pElem = pLista->pOrigemLista ;
      while ( pElem != NULL )
      {
         pProx = pElem->pProx ;
         LiberarElemento( pLista , pElem ) ;
         pElem = pProx ;
      } /* while */

      LimparCabeca( pLista ) ;

   } /* Fim função: LIS  -Esvaziar a lista */


/***********************************************************************
*
*  $FC Função: LIS  -Limpar a cabeça da lista
*
***********************************************************************/

   void LimparCabeca( LIS_tppLista pLista )
   {

      pLista->idLista = NULL;
      pLista->pOrigemLista = NULL ;
      pLista->pFimLista = NULL ;
      pLista->pElemCorr = NULL ;
      pLista->numElem   = 0 ;

   } /* Fim função: LIS  -Limpar a cabeça da lista */

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/


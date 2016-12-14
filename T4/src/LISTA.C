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
*     9       iars  15/nov/2016 copia lista
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

#ifdef _DEBUG
    #include "GENERICO.H"
    #include "CESPDIN.H"
    #include "CONTA.H"
    #include   "..\\tabelas\\IdTiposEspaco.def"
#endif

#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN

#ifdef _DEBUG
   #define MAGIC_NUMBER = 0xDEADBEEF;
#endif

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

   typedef struct tagElemLista {

         #ifdef _DEBUG
            int magic_number;
         #endif

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

         #ifdef _DEBUG
            int magic_number;
         #endif

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

         #ifdef _DEBUG

         int tipoArmazenado;

         #endif

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

      #ifdef _DEBUG
         pNewLista->magic_number = MAGIC_NUMBER;
      #endif

      *pLista = pNewLista ;

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Criar lista */


/***************************************************************************
*
*  Função: LIS  &Copiar lista
*  ****/


   LIS_tpCondRet LIS_CopiarLista( LIS_tppLista* pLista , LIS_tppLista listaOriginal, void ( * CopiarElemento ) ( void ** pValor, void* pValorOriginal ) )
   {

      LIS_tppLista pNewLista = NULL ;
      tpElemLista * pElem ;
      LIS_tpCondRet listaCondRet;
      void * pValorNovo;
      int tipoNovoEspaco;

      pNewLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
      if ( pNewLista == NULL )
      {
         return LIS_CondRetFaltouMemoria ;
      } /* if */

      LimparCabeca( pNewLista ) ;

      pNewLista->idLista = ( char * ) malloc ( strlen ( listaOriginal->idLista ) + 1 ) ;
      strcpy( pNewLista->idLista , listaOriginal->idLista ) ;

      pNewLista->ExcluirValor = listaOriginal->ExcluirValor ;
      pNewLista->CompararValores = listaOriginal->CompararValores ;
      pNewLista->Igual = listaOriginal->Igual ;

      #ifdef _DEBUG
         pNewLista->magic_number = MAGIC_NUMBER;
      #endif

      if ( listaOriginal->pElemCorr == NULL )
      {
         *pLista = pNewLista ;
         return LIS_CondRetOK ;
      } /* if */

      for ( pElem  = listaOriginal->pOrigemLista ;
            pElem != NULL ;
            pElem  = pElem->pProx )
      {
         CopiarElemento(&pValorNovo, pElem->pValor);
         listaCondRet = LIS_InserirElementoApos( pNewLista, pValorNovo );
         if(listaCondRet == LIS_CondRetFaltouMemoria)
         {
            LIS_DestruirLista(pNewLista);
            return LIS_CondRetFaltouMemoria;
         }
      } /* for */

      *pLista = pNewLista ;
      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Copiar lista */

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
*  Função: LIS  &Move Inicio
*  ****/

   LIS_tpCondRet LIS_MoveInicio( LIS_tppLista pLista )
   {
      pLista->pElemCorr = pLista->pOrigemLista;
      return LIS_CondRetOK;
   }

/***************************************************************************
*
*  Função: LIS  &Inserir elemento após
*  ****/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        )
   {

      tpElemLista * pElem ;

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

      if ( pLista == NULL )
      {
         return LIS_CondRetListaNaoExiste ;
      } /* if */

      free( pLista ) ;

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

      pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista ) ) ;
      if ( pElem == NULL )
      {
         return NULL ;
      } /* if */

      pElem->pValor = pValor ;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;

      #ifdef _DEBUG
         pElem->magic_number = MAGIC_NUMBER;
      #endif

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

/***************************************************************************
*
*  Função: LIS  &Procurar elemento contendo valor
*
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor )
   {

      tpElemLista * pElem ;

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      for ( pElem  = pLista->pElemCorr ;
            pElem != NULL ;
            pElem  = pElem->pProx )
      {
         if ( pLista->Igual( pElem->pValor, pValor ) )
         {
            pLista->pElemCorr = pElem ;
            return LIS_CondRetOK ;
         } /* if */
      } /* for */

      return LIS_CondRetNaoAchou ;

   } /* Fim função: LIS  &Procurar elemento contendo valor */


#ifdef _DEBUG

/* --------------------------------------------------------------
*   DEBUG
* -------------------------------------------------------------- */

   LIS_tpCondRet LIS_SetTipo( LIS_tppLista pLista ,
                              int identificadorDoTipo )
   {
      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      pLista->tipoArmazenado = identificadorDoTipo;

      return LIS_CondRetOK ;
   }

   LIS_tpCondRet LIS_GetTipo( LIS_tppLista pLista ,
                              int* identificadorDoTipo )
   {

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      *identificadorDoTipo = pLista->tipoArmazenado;

      return LIS_CondRetOK ;
   }

   LIS_tpCondRet LIS_Tamanho( LIS_tppLista pLista ,
                              int * tamanhoDaLista )
   {
      if ( pLista == NULL )
      {
         return LIS_CondRetListaNaoExiste ;
      } /* if */

      *tamanhoDaLista = pLista->numElem;

      return LIS_CondRetOK ;
   }

   LIS_tpCondRet LIS_VerificaAssertivasEstruturais( LIS_tppLista pLista, LIS_tpErroEstrutura* erroOcorrido )
   {
      tpElemLista * pElem;
      int elementoCorrenteEstaNaLista;
      int numElemContados;

      if( pLista->magic_number != MAGIC_NUMBER )
      {
         *erroOcorrido = LIS_tpErroEstruturaCabecaCorrompida;
         CNT_CONTAR( "erro-lista-cabeca-corrompida" ) ;
         return LIS_CondRetFalhaNaEstrutura;
      }

      if( pLista->pElemCorr == NULL && pLista->numElem != 0 )
      {
         *erroOcorrido = LIS_tpErroEstruturaCorrenteNuloIndevidamente;
         CNT_CONTAR( "erro-lista-corrente-nulo" ) ;
         return LIS_CondRetFalhaNaEstrutura;
      }
      if( pLista->pOrigemLista == NULL && pLista->numElem != 0 )
      {
         *erroOcorrido = LIS_tpErroEstruturaOrigemNuloIndevidamente;
         CNT_CONTAR( "erro-lista-origem-nulo" ) ;
         return LIS_CondRetFalhaNaEstrutura;
      }
      if( pLista->pFimLista == NULL && pLista->numElem != 0 )
      {
         *erroOcorrido = LIS_tpErroEstruturaFimNuloIndevidamente;
         CNT_CONTAR( "erro-lista-fim-nulo" ) ;
         return LIS_CondRetFalhaNaEstrutura;
      }

      if( pLista->numElem == 0 && pLista->pElemCorr != NULL )
      {
         *erroOcorrido = LIS_tpErroEstruturaListaVaziaMasElementosNaoNulos;
         CNT_CONTAR( "erro-lista-vazia-elementos-nao-nulos" ) ;
         return LIS_CondRetFalhaNaEstrutura;
      }
      if( pLista->numElem == 0 && pLista->pOrigemLista != NULL )
      {
         *erroOcorrido = LIS_tpErroEstruturaListaVaziaMasElementosNaoNulos;
         CNT_CONTAR( "erro-lista-vazia-origem-nao-nula" ) ;
         return LIS_CondRetFalhaNaEstrutura;
      }
      if( pLista->numElem == 0 && pLista->pFimLista != NULL )
      {
         *erroOcorrido = LIS_tpErroEstruturaListaVaziaMasElementosNaoNulos;
         CNT_CONTAR( "erro-lista-vazia-fim-nao-nulo" ) ;
         return LIS_CondRetFalhaNaEstrutura;
      }

      if( pLista->numElem != 0 )
      {
         if( pLista->pOrigemLista->pAnt != NULL )
         {
            *erroOcorrido = LIS_tpErroEstruturaInicioDaListaPossuiAnterior;
            CNT_CONTAR( "erro-lista-inicio-possui-anterior" ) ;
            return LIS_CondRetFalhaNaEstrutura;
         }
         if( pLista->pFimLista->pProx != NULL)
         {
            *erroOcorrido = LIS_tpErroEstruturaFimDaListaPossuiProximo;
            CNT_CONTAR( "erro-lista-fim-possui-proximo" ) ;
            return LIS_CondRetFalhaNaEstrutura;
         }
      }

      elementoCorrenteEstaNaLista = 0;
      numElemContados = 0;
      for(pElem = pLista->pOrigemLista; pElem != NULL; pElem = pElem->pProx)
      {
         if( pElem->magic_number != MAGIC_NUMBER )
         {
            *erroOcorrido = LIS_tpErroEstruturaElementoDaListaCorrompido;
            CNT_CONTAR( "erro-lista-magic-number-errado" ) ;
            return LIS_CondRetFalhaNaEstrutura;
         }

         if(pElem->pProx != NULL)
         {
            if(pElem->pProx->pAnt != pElem)
            {
               *erroOcorrido = LIS_tpErroEstruturaElementoDaListaCorrompido;
               CNT_CONTAR( "erro-lista-anterior-proximo-diferente-corrente" ) ;
               return LIS_CondRetFalhaNaEstrutura;
            }
         }
         else
         {
            if(pElem != pLista->pFimLista)
            {
               *erroOcorrido = LIS_tpErroEstruturaElementoDaListaCorrompido;
               CNT_CONTAR( "erro-lista-ultimo-diferente-fim" ) ;
               return LIS_CondRetFalhaNaEstrutura;
            }
         }

         if(pElem->pAnt != NULL)
         {
            if(pElem->pAnt->pProx != pElem)
            {
               *erroOcorrido = LIS_tpErroEstruturaEncadeamentoIncorretoNaLista;
               CNT_CONTAR( "erro-lista-proximo-anterior-diferente-corrente" ) ;
               return LIS_CondRetFalhaNaEstrutura;
            }
         }
         else
         {
            if(pElem != pLista->pOrigemLista)
            {
               *erroOcorrido = LIS_tpErroEstruturaEncadeamentoIncorretoNaLista;
               CNT_CONTAR( "erro-lista-primeiro-diferente-inicio" ) ;
               return LIS_CondRetFalhaNaEstrutura;
            }
         }

         if(pElem->pValor == NULL)
         {
            *erroOcorrido = LIS_tpErroEstruturaValorArmazenadoNulo;
            CNT_CONTAR( "erro-lista-valor-corrente-nulo" ) ;
            return LIS_CondRetFalhaNaEstrutura;
         }


         if(CED_ObterTipoEspaco( pElem->pValor ) != pLista->tipoArmazenado)
         {
            *erroOcorrido = LIS_tpErroEstruturaTipoDoValorIncoerente;
            CNT_CONTAR( "erro-lista-tipo-valor-incoerente" ) ;
            return LIS_CondRetFalhaNaEstrutura;
         }

         if( pElem == pLista->pElemCorr )
         {
            elementoCorrenteEstaNaLista = 1;
         }

         numElemContados++;
      }

      if(elementoCorrenteEstaNaLista == 0)
      {
         *erroOcorrido = LIS_tpErroEstruturaElementoCorrenteNaoEstaNaLista;
         CNT_CONTAR( "erro-lista-corrente-fora-lista" ) ;
         return LIS_CondRetFalhaNaEstrutura;
      }

      if(numElemContados != pLista->numElem)
      {
         *erroOcorrido = LIS_tpErroEstruturaNumeroDeElementosIncorreto;
         CNT_CONTAR( "erro-lista-numero-elementos-incorreto" ) ;
         return LIS_CondRetFalhaNaEstrutura;
      }

      *erroOcorrido = LIS_tpErroEstruturaNenhum;
      return LIS_CondRetOK;
   }

LIS_tpCondRet LIS_ObterPonteiroProximo( LIS_tppLista pLista ,
                                       void ** ponteiroProxElem )
{
    tpElemLista noCorrente ;
    
    noCorrente = *pLista->pElemCorr ;
    
    *ponteiroProxElem = noCorrente->pProx ;
}

LIS_tpCondRet LIS_ObterPonteiroAnterior( LIS_tppLista pLista ,
                                       void ** ponteiroAntElem )
{
    tpElemLista noCorrente ;
    
    noCorrente = *pLista->pElemCorr ;
    
    *ponteiroAntElem = noCorrente->pAnt ;
}

#endif

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/


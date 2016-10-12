/***************************************************************************
 *
 *  $MCD Módulo de definição: CSA  Casa de um tabuleiro para jogo de xadrez
 *
 *  Arquivo gerado:              CASA.h
 *  Letras identificadoras:      CSA
 *
 *  Nome da base de software:    ArcabouÁo para a automaÁ„o de testes de programas redigidos em C
 *  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
 *
 *  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
 *  Gestor:  LES/DI/PUC-Rio
 *  Autores: lff
 *
 *  $HA Histórico de evolução:
 *     Versão  Autor    Data     Observações
 *     3       lff   12/out/2016 desenvolvimento acabado
 *     2       lff   11/out/2016 desenvolvimento em andamento
 *     1       lff   10/out/2016 início desenvolvimento
 *
 ***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   "PECA.H"
#include   "LISTA.H"

#define CASA_OWN
#include "CASA.H"
#undef CASA_OWN

/***** Protótipos das funções encapuladas no módulo *****/

static void DestruirValor( void * pDado ) ;

static int NuncaIgual( void * pDado_1 , void * pDado_2 ) ;

/***********************************************************************
 *
 *  $TC Tipo de dados: CSA Descritor da casa
 *
 *
 ***********************************************************************/

typedef struct CSA_tagCasa {
    
    PCA_tppPeca peca ;
    /* Ponteiro para a peça contida na casa */
    
    LIS_tppLista listaAmeacantes ;
    /* Ponteiro para a lista de peças ameaçantes a peça contida na casa */
    
    LIS_tppLista listaAmeacados ;
    /* Ponteiro para a lista de peças ameaçado pela peça contida na casa */
    
} CSA_tpCasa ;


/***************************************************************************
 *
 *  Função: PCA  &Criar peça
 *  ****/

CSA_tpCondRet CSA_CriarCasa( CSA_tppCasa pCasa )
{
    
    PCA_tpCondRet retPeca ;
    LIS_tpCondRet retLista ;
    
    PCA_tppPeca peca = NULL ;
    LIS_tppLista listaAmeacantes = NULL ;
    LIS_tppLista listaAmeacados = NULL ;
    char charPeca = 'V' ;
    
    pCasa = NULL ;
    
    pCasa = ( CSA_tpCasa * ) malloc( sizeof( CSA_tpCasa )) ;
    if ( pCasa == NULL )
    {
        return CSA_CondRetFaltouMemoria ;
    } /* if */
    
    retPeca = PCA_CriarPeca( &peca ,
                   &charPeca ,
                   &charPeca ) ;
    if ( retPeca == PCA_CondRetFaltouMemoria )
    {
        return CSA_CondRetFaltouMemoria ;
    }/* if */
    
    retLista = LIS_CriarLista( listaAmeacantes ,
                    "listaAmeacantes" ,
                    DestruirValor ,
                    NuncaIgual ,
                    NuncaIgual ) ;
    if ( retLista == LIS_CondRetFaltouMemoria )
    {
        return CSA_CondRetFaltouMemoria ;
    }/* if */
    
    retLista = LIS_CriarLista( listaAmeacados ,
                    "listaAmeacantes" ,
                    DestruirValor ,
                    NuncaIgual ,
                    NuncaIgual ) ;
    if ( retLista == LIS_CondRetFaltouMemoria )
    {
        return CSA_CondRetFaltouMemoria ;
    }/* if */
    
    pCasa->peca = peca ;
    pCasa->listaAmeacantes = listaAmeacantes ;
    pCasa->listaAmeacados = listaAmeacados ;
    
    return CSA_CondRetOK ;
    
} /* Fim função: PCA  &Criar peça */

/***************************************************************************
 *
 *  Função: CSA  &Destruir casa
 *  ****/

CSA_tpCondRet CSA_DestruirCasa( CSA_tppCasa pCasa )
{
    
    PCA_tpCondRet retPeca ;
    LIS_tpCondRet retLista ;

    if ( pCasa = NULL )
    {
        return CSA_CondRetNaoExiste ;
    }/* if */
    
    retPeca = PCA_DestruirPeca( pCasa->peca ) ;
    if ( retPeca == PCA_CondRetPecaNaoExiste )
    {
        return CSA_CondRetNaoExiste ;
    }
    
    retLista = LIS_DestruirLista( pCasa->listaAmeacantes ) ;
    if ( retLista == LIS_CondRetListaNaoExiste )
    {
        return CSA_CondRetNaoExiste ;
    }/* if */
    
    retLista = LIS_DestruirLista( pCasa->listaAmeacados ) ;
    if ( retLista == LIS_CondRetListaNaoExiste )
    {
        return CSA_CondRetNaoExiste ;
    }/* if */
    
    DestruirValor ( pCasa ) ;
    
    return CSA_CondRetOK ;
    
} /* Fim função: CSA  &Destruir casa */

/***************************************************************************
 *
 *  Função: CSA  &Inserir peça na casa
 *  ****/

CSA_tpCondRet CSA_InserirPecaCasa( char nomePeca ,
                                   char corPeca ,
                                   CSA_tppCasa pCasa )
{
    
    PCA_tpCondRet retPeca ;
    
    if ( pCasa = NULL )
    {
        return CSA_CondRetNaoExiste ;
    }/* if */
    
    retPeca = PCA_CriarPeca( &( pCasa->peca ) ,
                             &nomePeca ,
                             &corPeca ) ;
    if ( retPeca == PCA_CondRetFaltouMemoria )
    {
        return CSA_CondRetNaoExiste ;
    }
    
    return CSA_CondRetOK ;
    
} /* Fim função: CSA  &Inserir peça na casa */

/***************************************************************************
 *
 *  Função: CSA  &Retirar peça da casa
 *  ****/

CSA_tpCondRet CSA_RetirarPecaCasa( CSA_tppCasa pCasa )
{
    
    PCA_tpCondRet retPeca ;

    if ( pCasa = NULL )
    {
        return CSA_CondRetNaoExiste ;
    }/* if */
    
    retPeca = PCA_DestruirPeca( &( pCasa->peca ) ) ;
    if ( retPeca == PCA_CondRetPecaNaoExiste )
    {
        return CSA_CondRetNaoExiste ;
    }
    
    return CSA_CondRetOK ;
    
} /* Fim função: CSA  &Retirar peça da casa */

/***************************************************************************
 *
 *  Função: CSA  &Obter peça da casa
 *  ****/

CSA_tpCondRet CSA_ObterPecaCasa( char* pNomePeca,
                                 char* pCorPeca,
                                 CSA_tppCasa pCasa )
{
    
    PCA_tpCondRet retPeca ;
    
    if ( pCasa = NULL )
    {
        return CSA_CondRetNaoExiste ;
    }/* if */
    
    retPeca = PCA_ObterValor( &( pCasa->peca ) ,
                              &pNomePeca ,
                              &pCorPeca ) ;
    if ( retPeca == PCA_CondRetPecaVazia )
    {
        return CSA_CondRetNaoExiste ;
    }

    
    return CSA_CondRetOK ;
    
} /* Fim função: CSA  &Obter peça da casa */

/***************************************************************************
 *
 *  Função: CSA  &Obter lista de ameaçantes de uma casa
 *  ****/

CSA_tpCondRet CSA_ObterListaAmeacantesCasa( LIS_tppLista * pListaAmeacantes,
                                            CSA_tppCasa pCasa )
{
    
    if ( pCasa = NULL )
    {
        return CSA_CondRetNaoExiste ;
    }/* if */
    
    *pListaAmeacantes = pCasa->listaAmeacantes ;
    
    return CSA_CondRetOK ;
    
} /* Fim função: CSA  &Obter lista de ameaçantes de uma casa */

/***************************************************************************
 *
 *  Função: CSA  &Obter lista de ameaçados de uma casa
 *  ****/

CSA_tpCondRet CSA_ObterListaAmeacadosCasa( LIS_tppLista * pListaAmeacantes,
                                           CSA_tppCasa pCasa )
{
    
    if ( pCasa = NULL )
    {
        return CSA_CondRetNaoExiste ;
    }/* if */
    
    *pListaAmeacados = pCasa->listaAmeacados ;
    
    return CSA_CondRetOK ;
    
} /* Fim função: CSA  &Obter lista de ameaçados de uma casa */

/***************************************************************************
 *
 *  Função: CSA  &Modificar lista de ameaçantes de uma casa
 *  ****/

CSA_tpCondRet CSA_ModificarListaAmeacantesCasa( CSA_tppCasa * vetorCasasAmeacantes ,
                                                int qtdCasasAmeacantes ,
                                                CSA_tppCasa pCasa )
{
    
    int i ;
    LIS_tpCondRet retLista ;
    
    if ( pCasa = NULL )
    {
        return CSA_CondRetNaoExiste ;
    }/* if */
    
    /* Limpa o lista para preenche-la */
    retLista = LIS_DestruirLista( pCasa->listaAmeacantes ) ;
    if ( retLista == LIS_CondRetListaNaoExiste )
    {
        return CSA_CondRetNaoExiste ;
    }/* if */
    
    retLista = LIS_CriarLista( pCasa->listaAmeacantes ,
                               "listaAmeacantes" ,
                               DestruirValor ,
                               NuncaIgual ,
                               NuncaIgual ) ;
    if ( retLista == LIS_CondRetFaltouMemoria )
    {
        return CSA_CondRetNaoExiste ;
    }/* if */
    
    /* Preenche a lista com as casas recebidas pelo vetor */
    for ( i = 0 ; i < qtdCasasAmeacantes ; i++ )
    {
        retLista = LIS_InserirElementoApos( pCasa->listaAmeacantes , vetorCasasAmeacantes[i] ) ;
        if ( retLista == LIS_CondRetFaltouMemoria )
        {
            return CSA_CondRetNaoExiste ;
        }/* if */
    } /* for */
    
    return CSA_CondRetOK ;
    
} /* Fim função: CSA  &Modificar lista de ameaçantes de uma casa */

/***************************************************************************
 *
 *  Função: CSA  &Modificar lista de ameaçados de uma casa
 *  ****/

CSA_tpCondRet CSA_ModificarListaAmeacadosCasa( CSA_tppCasa * vetorCasasAmeacadas ,
                                               int qtdCasasAmeacadas ,
                                               CSA_tppCasa pCasa )
{
    
    int i ;
    LIS_tpCondRet retLista ;
    
    if ( pCasa = NULL )
    {
        return CSA_CondRetNaoExiste ;
    }/* if */
    
    /* Limpa o lista para preenche-la */
    retLista = LIS_DestruirLista( pCasa->listaAmeacados ) ;
    if ( retLista == LIS_CondRetListaNaoExiste )
    {
        return CSA_CondRetNaoExiste ;
    }/* if */
    
    retLista = LIS_CriarLista( pCasa->listaAmeacados ,
                              "listaAmeacados" ,
                              DestruirValor ,
                              NuncaIgual ,
                              NuncaIgual ) ;
    if ( retLista == LIS_CondRetFaltouMemoria )
    {
        return CSA_CondRetNaoExiste ;
    }/* if */
    
    /* Preenche a lista com as casas recebidas pelo vetor */
    for ( i = 0 ; i < qtdCasasAmeacadas ; i++ )
    {
        retLista = LIS_InserirElementoApos( pCasa->listaAmeacados , vetorCasasAmeacadas[i] ) ;
        if ( retLista == LIS_CondRetFaltouMemoria )
        {
            return CSA_CondRetNaoExiste ;
        }/* if */
    } /* for */
    
    return CSA_CondRetOK ;
    
} /* Fim função: CSA  &Modificar lista de ameaçados de uma casa */

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
 *
 *  $FC Função: TLIS -Destruir valor
 *
 ***********************************************************************/

void DestruirValor( void * pDado )
{
    
    PCA_DestruirPeca( pDado->peca ) ;
    LIS_DestruirLista( pDado->listaAmeacantes ) ;
    LIS_DestruirLista( pDado->listaAmeacados ) ;
    
    free ( pDado ) ;
    
} /* Fim Função: CSA -Destruir valor */


/***********************************************************************
 *
 *  $FC Função: CSA -Nunca igual
 *
 ***********************************************************************/

int NuncaIgual( void * pDado_1 , void * pDado_2 )
{
    /* Duas casas nunca são iguais */
    return 1 ;
    
} /* Fim função: CSA -Nunca igual */


/********** Fim do mÛdulo de implementaÁ„o:  CSA  Casa de um tabuleiro para jogo de xadrez
 **********/


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
 *     2       lff   11/out/2016 desenvolvimento em andamento
 *     1       lff   10/out/2016 início desenvolvimento
 *
 ***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define CASA_OWN
#include "CASA.H"
#undef CASA_OWN

#include "PECA.H"
#include "LISTA.H"

/***** Protótipos das funções encapuladas no módulo *****/

static void DestruirValor( void * pDado ) ;

static int CompararValor( void * pDado_1 , void * pDado_2 ) ;

static int IgualValor( void * pDado_1 , void * pDado_2 ) ;

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
    
    PCA_CriarPeca( &peca ,
                   &charPeca ,
                   &charPeca ) ;
    
    LIS_CriarLista( listaAmeacantes ,
                    "listaAmeacantes" ,
                    DestruirValor ,
                    CompararValor ,
                    IgualValor ) ;
    
    LIS_CriarLista( listaAmeacados ,
                    "listaAmeacantes" ,
                    DestruirValor ,
                    CompararValor ,
                    IgualValor ) ;
    
    return CSA_CondRetOK ;
    
} /* Fim função: PCA  &Criar peça */

/***************************************************************************
 *
 *  Função: CSA  &Destruir casa
 *  ****/

CSA_tpCondRet CSA_DestruirCasa( CSA_tppCasa pCasa )
{
    
    if ( pCasa = NULL )
    {
        return CSA_CondRetNaoExiste ;
    }/* if */
    
    PCA_DestruirPeca( pCasa->peca ) ;
    LIS_DestruirLista( pCasa->listaAmeacantes ) ;
    LIS_DestruirLista( pCasa->listaAmeacados ) ;
    
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
    
    if ( pCasa = NULL )
    {
        return CSA_CondRetNaoExiste ;
    }/* if */
    
    PCA_CriarPeca(  &( pCasa->peca ) ,
                    &nomePeca ,
                    &corPeca ) ;
    
    return CSA_CondRetOK ;
    
} /* Fim função: CSA  &Inserir peça na casa */

/***************************************************************************
 *
 *  Função: CSA  &Retirar peça da casa
 *  ****/

CSA_tpCondRet CSA_RetirarPecaCasa( CSA_tppCasa pCasa )
{
    
    if ( pCasa = NULL )
    {
        return CSA_CondRetNaoExiste ;
    }/* if */
    
    PCA_DestruirPeca( &( pCasa->peca ) ) ;
    
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
    
    if ( pCasa = NULL )
    {
        return CSA_CondRetNaoExiste ;
    }/* if */
    
    PCA_ObterValor( &( pCasa->peca ) ,
                    &pNomePeca ,
                    &pCorPeca ) ;

    
    return CSA_CondRetOK ;
    
} /* Fim função: CSA  &Obter peça da casa */

/***************************************************************************
 *
 *  Função: CSA  &Obter lista de ameaçantes de uma casa
 *  ****/

CSA_tpCondRet CSA_ObterListaAmeacantesCasa( LIS_tppLista pListaAmeacantes,
                                            CSA_tppCasa pCasa )
{
    
    if ( pCasa = NULL )
    {
        return CSA_CondRetNaoExiste ;
    }/* if */
    
    /* verificar possíveis movimentos da peça presente na casa */
    
    /* para cada um dos movimentos checar se tem alguma peça na casa destino 
        e inserir essa peça na lista
     */
    
    
    return CSA_CondRetOK ;
    
} /* Fim função: CSA  &Obter lista de ameaçantes de uma casa */

/***************************************************************************
 *
 *  Função: CSA  &Obter lista de ameaçados de uma casa
 *  ****/

CSA_tpCondRet CSA_ObterListaAmeacadosCasa( LIS_tppLista pListaAmeacantes,
                                           CSA_tppCasa pCasa )
{
    
    if ( pCasa = NULL )
    {
        return CSA_CondRetNaoExiste ;
    }/* if */
    
    /* verificar possíveis movimentos das peças de cor diferente que a presente na casa */
    
    /* para cada um dos movimentos checar se tem como destino a casa em questão */
    
    
    return CSA_CondRetOK ;
    
} /* Fim função: CSA  &Obter lista de ameaçados de uma casa */

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
 *
 *  $FC Função: TLIS -Destruir valor
 *
 ***********************************************************************/

void DestruirValor( void * pDado )
{
    
    free ( pDado ) ;
    
} /* Fim Função: CSA -Destruir valor */


/***********************************************************************
 *
 *  $FC Função: CSA -Comparar valor
 *
 ***********************************************************************/

int CompararValor( void * pDado_1 , void * pDado_2 )
{
    
    char * valor_1 = ( char * ) pDado_1 ;
    char * valor_2 = ( char * ) pDado_2 ;
    return strcmp( valor_1 , valor_2 ) ;
    
} /* Fim função: CSA -Comparar valor */


/***********************************************************************
 *
 *  $FC Função: CSA -Igual valor
 *
 ***********************************************************************/

int IgualValor( void * pDado_1 , void * pDado_2 )
{
    
    char * valor_1 = ( char * ) pDado_1 ;
    char * valor_2 = ( char * ) pDado_2 ;
    return strcmp( valor_1 , valor_2 ) ;
    
} /* Fim função: CSA -Igual valor */

/********** Fim do mÛdulo de implementaÁ„o:  CSA  Casa de um tabuleiro para jogo de xadrez
 **********/


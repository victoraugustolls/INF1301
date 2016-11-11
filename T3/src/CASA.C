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
 *  Autores: lff, vas
 *
 *  $HA Histórico de evolução:
 *     Versão  Autor    Data     Observações
 *     5       vas   10/nov/2016 alteracoes devido a mudanca da estrutura da peca
 *     4       vas   12/out/2016 corrigir esvaziar peça da casa
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

CSA_tpCondRet CSA_CriarCasa( CSA_tppCasa * pCasa )
{
    
    PCA_tpCondRet retPeca ;
    LIS_tpCondRet retLista ;
    
    PCA_tppPeca peca = NULL ;
    LIS_tppLista listaAmeacantes = NULL ;
    LIS_tppLista listaAmeacados = NULL ;

    CSA_tppCasa newCasa = NULL ;

    char charPeca = 'V' ;
    
    newCasa = ( CSA_tpCasa * ) malloc( sizeof( CSA_tpCasa ) ) ;

    if ( newCasa == NULL )
    {
        return CSA_CondRetFaltouMemoria ;
    } /* if */
    
    retPeca = PCA_CriarPeca( &peca ,
                   charPeca ,
                   charPeca ) ;
    if ( retPeca == PCA_CondRetFaltouMemoria )
    {
        return CSA_CondRetFaltouMemoria ;
    }/* if */
    
    retLista = LIS_CriarLista( &listaAmeacantes ,
                    "amts" ,
                    DestruirValor ,
                    NuncaIgual ,
                    NuncaIgual ) ;
    if ( retLista == LIS_CondRetFaltouMemoria )
    {
        return CSA_CondRetFaltouMemoria ;
    }/* if */
    
    retLista = LIS_CriarLista( &listaAmeacados ,
                    "amds" ,
                    DestruirValor ,
                    NuncaIgual ,
                    NuncaIgual ) ;
    if ( retLista == LIS_CondRetFaltouMemoria )
    {
        return CSA_CondRetFaltouMemoria ;
    }/* if */
    
    newCasa->peca = peca ;
    newCasa->listaAmeacantes = listaAmeacantes ;
    newCasa->listaAmeacados = listaAmeacados ;

    *pCasa = newCasa ;
    
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

    if ( pCasa == NULL )
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
    
    free( pCasa ) ;
    
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
    
    if ( pCasa == NULL )
    {
        return CSA_CondRetNaoExiste ;
    }/* if */
    
    retPeca = PCA_CriarPeca( &( pCasa->peca ) ,
                            nomePeca ,
                            corPeca ) ;
    if ( retPeca == PCA_CondRetFaltouMemoria )
    {
        return CSA_CondRetFaltouMemoria ;
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

    char pecaVazia = 'V' ;

    if ( pCasa == NULL )
    {
        return CSA_CondRetNaoExiste ;
    }/* if */
    
    retPeca = PCA_AlterarPeca( pCasa->peca , pecaVazia , pecaVazia ) ;
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
    
    if ( pCasa == NULL )
    {
        return CSA_CondRetNaoExiste ;
    }/* if */
    
    retPeca = PCA_ObterValor( pCasa->peca ,
                              pNomePeca ,
                              pCorPeca ) ;
    if ( retPeca == PCA_CondRetPecaVazia )
    {
        return CSA_CondRetNaoExiste ;
    }
    
    return CSA_CondRetOK ;
    
} /* Fim função: CSA  &Obter peça da casa */

/***************************************************************************
 *
 *  Função: CSA  &Comparar Casas
 *  ****/

CSA_tpCondRet CSA_CompararCasa( CSA_tppCasa pCasa1 ,
                                CSA_tppCasa pCasa2 ,
                                int * igualdade )
{
    
    PCA_tpCondRet retPeca ;

    printf("Entrou no CSA_CompararCasa\n");
    
    if ( pCasa1 == NULL || pCasa2 == NULL )
    {
        printf("Uma das casas e nula\n");
        *igualdade = 0 ;
        printf("Saiu do CSA_CompararCasa\n");
        return CSA_CondRetNaoExiste ;
    }/* if */


    printf("Nenhuma das casas era nula\n");
    
    retPeca = PCA_ComparaPecas( pCasa1->peca ,
                                pCasa2->peca ,
                                igualdade ) ;

    if ( retPeca == PCA_CondRetPecaNaoExiste )
    {
        printf("Saiu do CSA_CompararCasa\n");
        return CSA_CondRetVazia ;
    }

    printf("Saiu do CSA_CompararCasa\n");
    return CSA_CondRetOK ;
    
} /* Fim função: CSA  &Comparar Casas */


/***************************************************************************
 *
 *  Função: CSA  &Obter lista de ameaçantes de uma casa
 *  ****/

CSA_tpCondRet CSA_ObterListaAmeacantesCasa( LIS_tppLista * pListaAmeacantes,
                                            CSA_tppCasa pCasa )
{
    
    if ( pCasa == NULL )
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

CSA_tpCondRet CSA_ObterListaAmeacadosCasa( LIS_tppLista * pListaAmeacados,
                                           CSA_tppCasa pCasa )
{
    
    if ( pCasa == NULL )
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
    
    if ( pCasa == NULL )
    {
        return CSA_CondRetNaoExiste ;
    }/* if */
    
    /* Limpa o lista para preenche-la */
    retLista = LIS_DestruirLista( pCasa->listaAmeacantes ) ;
    if ( retLista == LIS_CondRetListaNaoExiste )
    {
        return CSA_CondRetNaoExiste ;
    }/* if */
    
    retLista = LIS_CriarLista( &( pCasa->listaAmeacantes ) ,
                               "amts" ,
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
    
    if ( pCasa == NULL )
    {
        return CSA_CondRetNaoExiste ;
    }/* if */
    
    /* Limpa o lista para preenche-la */
    retLista = LIS_DestruirLista( pCasa->listaAmeacados ) ;
    if ( retLista == LIS_CondRetListaNaoExiste )
    {
        return CSA_CondRetNaoExiste ;
    }/* if */
    
    retLista = LIS_CriarLista( &( pCasa->listaAmeacados ) ,
                              "amds" ,
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
    
    CSA_tppCasa pCasa = ( CSA_tppCasa ) pDado ;
    
    PCA_DestruirPeca( pCasa->peca ) ;
    LIS_DestruirLista( pCasa->listaAmeacantes ) ;
    LIS_DestruirLista( pCasa->listaAmeacados ) ;
    
    free ( pDado ) ;
    
} /* Fim Função: CSA -Destruir valor */


/***********************************************************************
 *
 *  $FC Função: CSA -Nunca igual
 *
 ***********************************************************************/

int NuncaIgual( void * pDado_1 , void * pDado_2 )
{
    (void) pDado_1;
    (void) pDado_2;
    /* Duas casas nunca são iguais */
    return 1 ;
    
} /* Fim função: CSA -Nunca igual */


/********** Fim do mÛdulo de implementaÁ„o:  CSA  Casa de um tabuleiro para jogo de xadrez
 **********/


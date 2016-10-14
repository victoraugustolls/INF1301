/***************************************************************************
 *  $MCI Módulo de implementação: TAB  Tabuleiro para jogo de xadrez
 *
 *  Arquivo gerado:              TABULEIRO.c
 *  Letras identificadoras:      TAB
 *
 *  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
 *  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
 *
 *  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
 *  Gestor:  LES/DI/PUC-Rio
 *  Autores: lff
 *
 *  $HA Histórico de evolução:
 *     Versão  Autor    Data     Observações
 *     3       lff   11/out/2016 em desenvolvimento
 *     2       lff   05/out/2016 em desenvolvimento
 *     1       lff   04/out/2016 início desenvolvimento
 *
 *
 ***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   "CASA.H"
#include   "VALIDA_MOV.H"

#define TABULEIRO_OWN
#include "TABULEIRO.h"
#undef TABULEIRO_OWN

/***********************************************************************
 *
 *  $TC Tipo de dados: TAB Descritor do tabuleiro
 *
 *
 ***********************************************************************/

typedef struct TAB_tagTabuleiro {
    
    CSA_tppCasa tabuleiro [8] [8] ;
    /* Matriz de ponteiros para casas que define o tabuleiro */
    
} TAB_tpTabuleiro ;

/***** Protótipos das funções encapuladas no módulo *****/

int TAB_VerificaCoordValida( char coluna , char linha ) ;
int TAB_CasaVazia( void * casa ) ;
int TAB_CasaInimigo( void * casa ) ;
int TAB_Dim0( void * casa ) ;
int TAB_Dim1 (void * casa ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
 *
 *  Função: TAB  &Criar tabuleiro
 *  ****/

TAB_tpCondRet TAB_CriarTabuleiro( TAB_tppTabuleiro * pTabuleiro )
{

    int i , j ;
    TAB_tppTabuleiro pNovoTabuleiro = NULL ;
    CSA_tpCondRet retCasa ;
    
    pNovoTabuleiro = ( TAB_tpTabuleiro * ) malloc( sizeof( TAB_tpTabuleiro )) ;
    
    if ( pNovoTabuleiro == NULL )
    {
        return TAB_CondRetFaltouMemoria ;
    } /* if */
    
    for ( i = 0 ; i < 8 ; i++ )
    {
        for ( j = 0 ; j < 8 ; j++ )
        {
            retCasa = CSA_CriarCasa( &( pNovoTabuleiro->tabuleiro[i][j] ) ) ;
            if ( retCasa == CSA_CondRetFaltouMemoria )
            {
                return TAB_CondRetFaltouMemoria ;
            } /* if */
        } /* for */
    } /* for */
    
    *pTabuleiro = pNovoTabuleiro ;
    
    return TAB_CondRetOK ;
    
} /* Fim função: TAB  &Criar tabuleiro */

/***************************************************************************
 *
 *  Função: TAB  &Destruir tabuleiro
 *  ****/

TAB_tpCondRet TAB_DestruirTabuleiro( TAB_tppTabuleiro pTabuleiro )
{
    
    int i , j ;
    CSA_tpCondRet retCasa ;
    
    if ( pTabuleiro == NULL )
    {
        return TAB_CondRetNaoExiste ;
    } /* if */
    
    for ( i = 0; i < 8 ; i++ )
    {
        for ( j = 0; j < 8 ; j++ )
        {
            retCasa = CSA_DestruirCasa( pTabuleiro->tabuleiro[i][j] ) ;
            if ( retCasa == CSA_CondRetNaoExiste )
            {
                return TAB_CondRetNaoExiste ;
            } /* if */
        } /* for */
    } /* for */
    
    free( pTabuleiro ) ;
    
    return TAB_CondRetOK ;
    
} /* Fim função: TAB  &Destruir tabuleiro */

/***************************************************************************
 *
 *  Função: TAB  &Inserir peça no tabuleiro
 *  ****/

TAB_tpCondRet TAB_InserirPecaTabuleiro( char coluna ,
                                        char linha ,
                                        char nomePeca ,
                                        char corPeca ,
                                        TAB_tppTabuleiro pTabuleiro )
{
    
    int i , j ;
    CSA_tpCondRet retCasa ;
    
    if ( ! TAB_VerificaCoordValida( coluna , linha ) )
    {
        return TAB_CondRetCoordNaoExiste ;
    } /* if */
    
    i = linha - '0' ;
    j = coluna - 'A' + 1 ;
    
    retCasa = CSA_InserirPecaCasa( nomePeca, corPeca, pTabuleiro->tabuleiro[i][j] ) ;
    if ( retCasa == CSA_CondRetNaoExiste )
    {
        return TAB_CondRetCoordNaoExiste ;
    } /* if */
             
    return TAB_CondRetOK ;
            
} /* Fim função: TAB  &Inserir peça no tabuleiro */

/***************************************************************************
 *
 *  Função: TAB  &Mover peça no tabuleiro
 *  ****/

/*  $FV Valor retornado
*     TAB_CondRetOK                - inseriu sem problemas
*     TAB_CondRetCoordNaoExiste    - coordenada não existe
*     TAB_CondRetMovInvalido       - o movimento indicado não é válido
*     TAB_CondRetFaltouMemoria     - faltou memória para alocação da peça
*/

TAB_tpCondRet TAB_MoverPecaTabuleiro( char colInicial ,
                                      char linInicial ,
                                      char colFinal ,
                                      char linFinal ,
                                      TAB_tppTabuleiro pTabuleiro )
{
    
    CSA_tpCondRet           retCasa ;
    CSA_tppCasa *           vetTodasCasas ;
    VMV_tpCondRet           retDirMov ;
    VMV_tpMovimentoValido   retMov ;
    VMV_tppConfigDir        pConfigDir ;
    
    int i , j , colAtual , linAtual , colDestino , linDestino ;
    int sinal[] = { 1 , 0 } , condEsp[] = { 0 } ;
    char * peca , * cor ;
    
    int (*TAB_Dimensao[2]) (void* casa) = { TAB_Dim0 , TAB_Dim1 } ;
    
    if ( ( ! TAB_VerificaCoordValida( colInicial , linInicial ) ) ||
         ( ! TAB_VerificaCoordValida( colFinal , linFinal ) ) )
    {
        return TAB_CondRetCoordNaoExiste ;
    } /* if */
    
    /* Converte a linha e a coluna para inteiros */
    linAtual   = linInicial - '0' ;
    linDestino = linFinal   - '0' ;
    colAtual   = colInicial - 'A' + 1 ;
    colDestino = colFinal   - 'A' + 1 ;
    
    
    /* Pré-processamento para validação do movimento */
    retDirMov = VMV_CriarConfigDir ( &pConfigDir, NULL ) ;
    if ( ( retDirMov == VMV_CondRetErrAberturaArquivo ) ||
         ( retDirMov == VMV_CondRetErrFormatoArquivoErrado ) )
    {
        return TAB_CondRetFalhaArq ;
    } /* if */
    else if ( retDirMov == VMV_CondRetErrFaltouMemoria )
    {
        return TAB_CondRetFaltouMemoria ;
    } /* if */
    
    retCasa = CSA_ObterPecaCasa( &peca , &cor , pTabuleiro->tabuleiro[linAtual][colAtual] ) ;
    if ( retCasa == CSA_CondRetNaoExiste )
    {
        return TAB_CondRetNaoExiste ;
    } /* if */
    
    for ( i = 0 ; i < 8; i++ )
    {
        for ( j = 0 ; j < 8; j++ )
        {
            vetTodasCasas[j + 8 * i] = pTabuleiro->tabuleiro[i][j] ;
        } /* for */
    } /* for */
    
    if ( *cor == 'B' )
    {
        sinal[0] = 1 ;
    }
    else
    {
        sinal[0] = -1 ;
    } /* if */

    
    /* Verificar validade do movimento */
    retDirMov = VMV_ChecarMovimentoPeca ( pConfigDir ,
                                          &retMov ,
                                          *peca ,
                                          ( void* ) &pTabuleiro->tabuleiro[linAtual][colAtual] ,
                                          ( void* ) &pTabuleiro->tabuleiro[linDestino][colDestino] ,
                                          vetTodasCasas ,
                                          64 ,
                                          2 ,
                                          TAB_Dimensao ,
                                          sinal ,
                                          TAB_CasaVazia ,
                                          TAB_CasaInimigo ,
                                          condEsp ,
                                          0 ) ;
    if ( ( retDirMov == VMV_CondRetErrAberturaArquivo ) ||
         ( retDirMov == VMV_CondRetErrFormatoArquivoErrado ) ||
         ( retDirMov == VMV_CondRetErrManuseioArquivo ) )
    {
        return TAB_CondRetFalhaArq ;
    } /* if */
    else if ( ( retDirMov == VMV_CondRetVariavelNaoExistente ) ||
              ( retDirMov == VMV_CondRetErrComandoNaoExistente ) )
    {
        return TAB_CondRetNaoExiste ;
    } /* if */
    
    retDirMov = VMV_DestruirConfigDir ( pConfigDir ) ;
    
    if ( retMov == VMV_MovimentoValidoNao )
    {
        return TAB_CondRetMovInvalido ;
    }
    
    
    /* Mover peça de casa */
    retCasa = CSA_RetirarPecaCasa ( pTabuleiro->tabuleiro[linAtual][colAtual] ) ;
    if ( retCasa == CSA_CondRetNaoExiste )
    {
        return TAB_CondRetNaoExiste ;
    } /* if */
    
    retCasa = CSA_InserirPecaCasa( 'V' ,
                                   'V' ,
                                   pTabuleiro->tabuleiro[linAtual][colAtual] ) ;
    if ( retCasa == CSA_CondRetNaoExiste )
    {
        return TAB_CondRetNaoExiste ;
    } /* if */
    
    retCasa = CSA_RetirarPecaCasa ( pTabuleiro->tabuleiro[linDestino][colDestino] ) ;
    if ( retCasa == CSA_CondRetNaoExiste )
    {
        return TAB_CondRetNaoExiste ;
    } /* if */
    
    retCasa = CSA_InserirPecaCasa( *peca ,
                                   *cor ,
                                   pTabuleiro->tabuleiro[linDestino][colDestino] ) ;
    if ( retCasa == CSA_CondRetNaoExiste )
    {
        return TAB_CondRetNaoExiste ;
    } /* if */

    return TAB_CondRetOK ;
    
} /* Fim função: TAB  &Mover peça no tabuleiro */

/***************************************************************************
 *
 *  Função: TAB  &Retirar peça do tabuleiro
 *  ****/

TAB_tpCondRet TAB_RetirarPecaTabuleiro( char coluna ,
                                        char linha ,
                                        TAB_tppTabuleiro pTabuleiro )
{
    
    int i , j ;
    CSA_tpCondRet retCasa ;
    
    if ( ! TAB_VerificaCoordValida( coluna , linha ) )
    {
        return TAB_CondRetCoordNaoExiste ;
    } /* if */

    /* Converte a linha e a coluna para inteiros */
    i = linha - '0' ;
    j = coluna - 'A' + 1 ;
    
    retCasa = CSA_RetirarPecaCasa( pTabuleiro->tabuleiro[i][j] ) ;
    if ( retCasa == CSA_CondRetNaoExiste )
    {
        return TAB_CondRetNaoExiste ;
    } /* if */
    
    return TAB_CondRetOK ;
    
} /* Fim função: TAB  &Retirar peça do tabuleiro */

/***************************************************************************
 *
 *  Função: TAB  &Obter peça do tabuleiro
 *  ****/

TAB_tpCondRet TAB_ObterPecaTabuleiro( char coluna ,
                                      char linha ,
                                      char** pNomePeca ,
                                      char** pCorPeca ,
                                      TAB_tppTabuleiro pTabuleiro )
{
    
    int i , j ;
    CSA_tpCondRet retCasa ;
    
    if ( ! TAB_VerificaCoordValida( coluna , linha ) )
    {
        return TAB_CondRetCoordNaoExiste ;
    } /* if */
    
    /* Converte a linha e a coluna para inteiros */
    i = linha - '0' ;
    j = coluna - 'A' + 1 ;
    
    retCasa = CSA_ObterPecaCasa( pNomePeca , pCorPeca , pTabuleiro->tabuleiro[i][j] ) ;
    if ( retCasa == CSA_CondRetNaoExiste )
    {
        return TAB_CondRetNaoExiste ;
    } /* if */
    
    return TAB_CondRetOK ;
    
} /* Fim função: TAB  &Obter peça do tabuleiro */

/***************************************************************************
 *
 *  Função: TAB  &Obter casa do tabuleiro
 *  ****/

TAB_tpCondRet TAB_ObterCasaTabuleiro( char coluna ,
                                     char linha ,
                                     CSA_tppCasa * pCasa ,
                                     TAB_tppTabuleiro pTabuleiro )
{
    
    int i , j ;
    
    if ( ! TAB_VerificaCoordValida( coluna , linha ) )
    {
        return TAB_CondRetCoordNaoExiste ;
    } /* if */
    
    /* Converte a linha e a coluna para inteiros */
    i = linha - '0' ;
    j = coluna - 'A' + 1 ;
    
    *pCasa = pTabuleiro->tabuleiro[i][j] ;
    if ( pCasa == NULL )
    {
        return TAB_CondRetNaoExiste ;
    } /* if */
    
    return TAB_CondRetOK ;
    
}/* Fim função: TAB  &Obter casa do tabuleiro */

/***************************************************************************
 *
 *  Função: TAB  &Obter lista de ameaçantes de uma peça do tabuleiro
 *  ****/

TAB_tpCondRet TAB_ObterListaAmeacantesTabuleiro( char coluna ,
                                                 char linha ,
                                                 LIS_tppLista * pListaAmeacantes ,
                                                 TAB_tppTabuleiro pTabuleiro )
{
    
    int i , j ;
    CSA_tpCondRet retCasa ;
    
    if ( ! TAB_VerificaCoordValida( coluna , linha ) )
    {
        return TAB_CondRetCoordNaoExiste ;
    } /* if */
    
    /* Converte a linha e a coluna para inteiros */
    i = linha - '0' ;
    j = coluna - 'A' + 1 ;
    
    retCasa = CSA_ObterListaAmeacantesCasa( pListaAmeacantes , pTabuleiro->tabuleiro[i][j] ) ;
    
    if ( retCasa == CSA_CondRetNaoExiste )
    {
        return TAB_CondRetNaoExiste ;
    } /* if */
    
    return TAB_CondRetOK ;
    
} /* Fim função: TAB  &Obter lista de ameaçados de uma peça do tabuleiro */

TAB_tpCondRet TAB_ObterListaAmeacadosTabuleiro( char coluna ,
                                                char linha ,
                                                LIS_tppLista * pListaAmeacados ,
                                                TAB_tppTabuleiro pTabuleiro )
{
    
    int i , j ;
    CSA_tpCondRet retCasa ;
    
    if ( ! TAB_VerificaCoordValida( coluna , linha ) )
    {
        return TAB_CondRetCoordNaoExiste ;
    } /* if */
    
    /* Converte a linha e a coluna para inteiros */
    i = linha - '0' ;
    j = coluna - 'A' + 1 ;
    
    retCasa = CSA_ObterListaAmeacadosCasa( pListaAmeacados , pTabuleiro->tabuleiro[i][j] ) ;
    
    if ( retCasa == CSA_CondRetNaoExiste )
    {
        return TAB_CondRetNaoExiste ;
    } /* if */
    
    return TAB_CondRetOK ;
    
} /* Fim função: TAB  &Obter lista de ameaçados de uma peça do tabuleiro */

/***** Código das funções encapuladas no módulo *****/

int TAB_VerificaCoordValida( char coluna , char linha )
{
    
    int i , j ;
    
    i = linha - '0' ;
    j = coluna - 'A' + 1 ;
    
    if ( ( i > 8 ) || ( i < 0 ) || ( j > 8 ) || ( j < 0 ) )
    {
        return 0 ;
    } /* if */
    return 1 ;
    
}

int TAB_CasaVazia( void * casa )
{
    
    CSA_tppCasa pCasa = ( CSA_tppCasa ) casa ;
    char * nomePeca, * corPeca ;
    
    CSA_ObterPecaCasa( &nomePeca , &corPeca , pCasa ) ;
    
    if ( ( *nomePeca == 'V' ) && ( *corPeca == 'V' ) )
    {
        return 1 ;
    }
    return 0 ;
    
}

int TAB_CasaInimigo( void * casa )
{
    
    CSA_tppCasa pCasa = ( CSA_tppCasa ) casa ;
    char * nomePeca, * corPeca ;
    
    CSA_ObterPecaCasa( &nomePeca , &corPeca , pCasa ) ;
    
    if ( ( *nomePeca == 'V' ) && ( *corPeca == 'V' ) )
    {
        return 0 ;
    }
    return 1 ;
    
}

int TAB_Dim0( void * casa )
{
    
    int i , j , igual ;
    TAB_tppTabuleiro pTabuleiro ;
    CSA_tppCasa pCasa = ( CSA_tppCasa ) casa ;

    TAB_CriarTabuleiro( &pTabuleiro ) ;
        
    for ( i = 0 ; i < 8; i++ )
    {
        for ( j = 0 ; j < 8; j++ )
        {
            CSA_CompararCasa( pCasa ,
                              pTabuleiro->tabuleiro[i][j] ,
                              &igual ) ;
            
            if ( igual == 1 ) {
                return i ;
            }
        } /* for */
    } /* for */
    
}

int TAB_Dim1 (void * casa )
{
    
    int i , j , igual ;
    TAB_tppTabuleiro pTabuleiro ;
    CSA_tppCasa pCasa = ( CSA_tppCasa ) casa ;

    TAB_CriarTabuleiro( &pTabuleiro ) ;
    
    for ( i = 0 ; i < 8; i++ )
    {
        for ( j = 0 ; j < 8; j++ )
        {
            CSA_CompararCasa( pCasa ,
                             pTabuleiro->tabuleiro[i][j] ,
                             &igual ) ;
            
            if ( igual == 1 ) {
                return j ;
            }
        } /* for */
    } /* for */
    
}

/********** Fim do módulo de implementação: TAB  Tabuleiro para jogo de xadrez **********/









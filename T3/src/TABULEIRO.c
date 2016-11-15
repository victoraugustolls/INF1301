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
 *  Autores: lff, vas
 *
 *  $HA Histórico de evolução:
 *     Versão  Autor    Data     Observações
 *     5       vas   12/nov/2016 correção de múltiplos erros devido a nova interface do modulo casa
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
#include "TABULEIRO.H"
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

    VMV_tppConfigDir configDir ;
    
} TAB_tpTabuleiro ;

/***** Protótipos das funções encapuladas no módulo *****/

int TAB_VerificaCoordValida ( int linha , int coluna ) ;
int TAB_CasaVazia ( void * casa , void * aux ) ;
int TAB_CasaInimigo ( void * casa , void * aux ) ;
int TAB_Dim0 ( void * casa , void * aux ) ;
int TAB_Dim1 ( void * casa , void * aux ) ;
void ExcluirChar ( void * pDado ) ;
int CompararChar ( void * pDado_1 , void * pDado_2 ) ;
int IgualChar ( void * pDado_1 , void * pDado_2 ) ;
void AtualizaListaAmeacantesAmeacados ( TAB_tppTabuleiro pTabuleiro ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
 *
 *  Função: TAB  &Criar tabuleiro
 *  ****/

TAB_tpCondRet TAB_CriarTabuleiro( TAB_tppTabuleiro * pTabuleiro, char * pathConfig )
{

    int i , j ;
    TAB_tppTabuleiro pNovoTabuleiro = NULL ;
    CSA_tpCondRet retCasa ;
    char* pecas ;
    char* cores ;
    int num_casas ;

    VMV_tpCondRet condRetCriarConfigDir ;
    
    pNovoTabuleiro = ( TAB_tpTabuleiro * ) malloc( sizeof( TAB_tpTabuleiro ) ) ;

    condRetCriarConfigDir = VMV_CriarConfigDir( &pNovoTabuleiro->configDir ,
                                                pathConfig ) ;

    if ( condRetCriarConfigDir == VMV_CondRetErrAberturaArquivo )
    {
        free( pNovoTabuleiro ) ;
        return TAB_CondRetFalhaArq ;
    } /* if */
    else if ( condRetCriarConfigDir == VMV_CondRetErrFormatoArquivoErrado )
    {
        free( pNovoTabuleiro ) ;
        return TAB_CondRetFalhaArq ;
    } /* if */
    else if ( condRetCriarConfigDir == VMV_CondRetErrFaltouMemoria )
    {
        free( pNovoTabuleiro ) ;
        return TAB_CondRetFaltouMemoria ;
    } /* if */
    
    if ( pNovoTabuleiro == NULL )
    {
        return TAB_CondRetFaltouMemoria ;
    } /* if */
    
    condRetCriarConfigDir = VMV_LerTabuleiroInicial (   pNovoTabuleiro->configDir ,
                                                        &pecas , 
                                                        &cores , 
                                                        &num_casas ) ;

    // printf("Vai entrar nos fors, %d\n", condRetCriarConfigDir) ;

    for ( i = 0 ; i < 8 ; i++ )
    {
        for ( j = 0 ; j < 8 ; j++ )
        {
            retCasa = CSA_CriarCasa( &( pNovoTabuleiro->tabuleiro[i][j] ) ) ;
            if ( retCasa == CSA_CondRetFaltouMemoria )
            {
                for ( ; i >= 0 ; i-- )
                {
                    for ( j-- ; j >= 0 ; j-- )
                    {
                        CSA_DestruirCasa( ( *pTabuleiro )->tabuleiro[i][j] ) ;
                    } /* for */
                } /* for */
                free( pecas ) ;
                free( cores ) ;
                free( pNovoTabuleiro ) ;
                VMV_DestruirConfigDir( pNovoTabuleiro->configDir ) ;
                return TAB_CondRetFaltouMemoria ;
            } /* if */

            retCasa = CSA_InserirPecaCasa(  pecas[ 8 * i + j ] ,
                                            cores[ 8 * i + j ] ,
                                            pNovoTabuleiro->tabuleiro[i][j] ) ;
            // printf("retCasa: %d\n", retCasa);
            if ( retCasa == CSA_CondRetFaltouMemoria )
            {
                for ( ; i >= 0 ; i-- )
                {
                    for (j--; j >= 0 ; j-- )
                    {
                        CSA_DestruirCasa( ( *pTabuleiro )->tabuleiro[i][j] ) ;
                    } /* for */
                } /* for */
                free( pecas ) ;
                free( cores ) ;
                free( pNovoTabuleiro ) ;
                VMV_DestruirConfigDir( pNovoTabuleiro->configDir ) ;
                return TAB_CondRetFaltouMemoria ;
            } /* if */
            // printf("for 2: %d\n", j) ;

        } /* for */
        // printf("for 1: %d\n", i) ;
    } /* for */

    // printf("Acabou todos os fors\n") ;

    free( pecas ) ;
    free( cores ) ;
    *pTabuleiro = pNovoTabuleiro ;

    // printf("Vai atualizar listas\n") ;

    AtualizaListaAmeacantesAmeacados ( * pTabuleiro ) ;
    
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
    
    VMV_DestruirConfigDir( pTabuleiro->configDir ) ;
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

    i = linha - '0' - 1 ;
    j = coluna - 'A' ;

    if ( ! TAB_VerificaCoordValida( i , j ) )
    {
        return TAB_CondRetCoordNaoExiste ;
    } /* if */

    retCasa = CSA_InserirPecaCasa( nomePeca, corPeca, pTabuleiro->tabuleiro[i][j] ) ;

    if ( retCasa == CSA_CondRetNaoExiste )
    {
        return TAB_CondRetCoordNaoExiste ;
    } /* if */

    // printf("TAB_InserirPecaTabuleiro vai chamar AtualizaListaAmeacantesAmeacados\n");
             
    AtualizaListaAmeacantesAmeacados ( pTabuleiro );

    return TAB_CondRetOK ;
            
} /* Fim função: TAB  &Inserir peça no tabuleiro */

/***************************************************************************
 *
 *  Função: TAB  &Mover peça no tabuleiro
 *  ****/

TAB_tpCondRet TAB_MoverPecaTabuleiro( char colInicial ,
                                      char linInicial ,
                                      char colFinal ,
                                      char linFinal ,
                                      TAB_tppTabuleiro pTabuleiro )
{
    
    CSA_tpCondRet           retCasa ;
    CSA_tppCasa             vetTodasCasas[64] ;
    VMV_tpCondRet           retDirMov ;
    VMV_tpMovimentoValido   retMov ;
    
    int i , j ;
    int colAtual , linAtual ;
    int colDestino , linDestino ;

    int sinal[] = { 0 , 0 } ;
    int condEsp[] = { 0 } ;

    char peca ;
    char cor ;

    int (*TAB_Dimensao[2]) (void* casa, void* tab) = { TAB_Dim1 , TAB_Dim1 } ;

    if ( pTabuleiro == NULL )
    {
        printf(">>1\n");
        return TAB_CondRetNaoExiste ;
    }

    /* Converte a linha e a coluna para inteiros */
    linAtual   = linInicial - '0' - 1 ;
    linDestino = linFinal   - '0' - 1 ;
    colAtual   = colInicial - 'A' ;
    colDestino = colFinal   - 'A' ;

    if ( ( ! TAB_VerificaCoordValida( linAtual , colAtual ) ) ||
         ( ! TAB_VerificaCoordValida( linDestino , colDestino ) ) )
    {
        return TAB_CondRetCoordNaoExiste ;
    } /* if */
    
    retCasa = CSA_ObterPecaCasa( &peca , &cor , pTabuleiro->tabuleiro[linAtual][colAtual] ) ;
    if ( retCasa == CSA_CondRetNaoExiste )
    {
        printf(">>2\n");
        return TAB_CondRetNaoExiste ;
    } /* if */
    
    for ( i = 0 ; i < 8; i++ )
    {
        for ( j = 0 ; j < 8; j++ )
        {
            vetTodasCasas[j + 8 * i] = pTabuleiro->tabuleiro[i][j] ;
        } /* for */
    } /* for */
    
    sinal[0] = cor == 'B' ? 1 : -1 ;

    /* Verificar validade do movimento */
    retDirMov = VMV_ChecarMovimentoPeca ( pTabuleiro->configDir ,
                                          &retMov ,
                                          peca ,
                                          ( void* ) pTabuleiro->tabuleiro[linAtual][colAtual] ,
                                          ( void* ) pTabuleiro->tabuleiro[linDestino][colDestino] ,
                                          vetTodasCasas ,
                                          64 ,
                                          2 ,
                                          TAB_Dimensao ,
                                          sinal ,
                                          TAB_CasaVazia ,
                                          TAB_CasaInimigo ,
                                          condEsp ,
                                          0,
                                          ( void* ) pTabuleiro ) ;

    if ( ( retDirMov == VMV_CondRetErrAberturaArquivo ) ||
         ( retDirMov == VMV_CondRetErrFormatoArquivoErrado ) ||
         ( retDirMov == VMV_CondRetErrManuseioArquivo ) )
    {
        printf("retorno do vmv %d\n",retDirMov);
        return TAB_CondRetFalhaArq ;
    }
    else if ( ( retDirMov == VMV_CondRetVariavelNaoExistente ) ||
              ( retDirMov == VMV_CondRetErrComandoNaoExistente ) )
    {
        printf(">>3\n");
        return TAB_CondRetNaoExiste ;
    } /* if */

    if ( retMov == VMV_MovimentoValidoNao )
    {
        return TAB_CondRetMovInvalido ;
    } /* if */
    
    /* Mover peça de casa */
    retCasa = CSA_RetirarPecaCasa ( pTabuleiro->tabuleiro[linAtual][colAtual] ) ;

    if ( retCasa == CSA_CondRetNaoExiste )
    {
        printf(">>4\n");
        return TAB_CondRetNaoExiste ;
    } /* if */
    
    retCasa = CSA_InserirPecaCasa( 'V' , 'V' ,
                                   pTabuleiro->tabuleiro[linAtual][colAtual] ) ;

    if ( retCasa == CSA_CondRetNaoExiste )
    {
        printf(">>5\n");
        return TAB_CondRetNaoExiste ;
    } /* if */
    
    retCasa = CSA_RetirarPecaCasa ( pTabuleiro->tabuleiro[linDestino][colDestino] ) ;
    if ( retCasa == CSA_CondRetNaoExiste )
    {
        printf(">>6\n");
        return TAB_CondRetNaoExiste ;
    } /* if */
    
    retCasa = CSA_InserirPecaCasa( peca , cor ,
                                   pTabuleiro->tabuleiro[linDestino][colDestino] ) ;

    if ( retCasa == CSA_CondRetNaoExiste )
    {
        printf(">>7\n");
        return TAB_CondRetNaoExiste ;
    } /* if */

    AtualizaListaAmeacantesAmeacados ( pTabuleiro );

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

    if ( pTabuleiro == NULL )
    {
        return TAB_CondRetNaoExiste ;
    } /* if */

    /* Converte a linha e a coluna para inteiros */
    i = linha - '0' - 1 ;
    j = coluna - 'A';
    
    if ( ! TAB_VerificaCoordValida( i , j ) )
    {
        return TAB_CondRetCoordNaoExiste ;
    } /* if */
    
    retCasa = CSA_RetirarPecaCasa( pTabuleiro->tabuleiro[i][j] ) ;
    
    if ( retCasa == CSA_CondRetNaoExiste )
    {
        return TAB_CondRetNaoExiste ;
    } /* if */
    
    AtualizaListaAmeacantesAmeacados ( pTabuleiro ) ;

    return TAB_CondRetOK ;
    
} /* Fim função: TAB  &Retirar peça do tabuleiro */

/***************************************************************************
 *
 *  Função: TAB  &Obter peça do tabuleiro
 *  ****/

TAB_tpCondRet TAB_ObterPecaTabuleiro( char coluna ,
                                      char linha ,
                                      char* pNomePeca ,
                                      char* pCorPeca ,
                                      TAB_tppTabuleiro pTabuleiro )
{
    
    int i , j ;
    CSA_tpCondRet retCasa ;

    if ( pTabuleiro == NULL )
    {
        return TAB_CondRetNaoExiste ;
    } /* if */

    /* Converte a linha e a coluna para inteiros */
    i = linha - '0'- 1 ;
    j = coluna - 'A' ;
    
    if ( ! TAB_VerificaCoordValida( i , j ) )
    {
        return TAB_CondRetCoordNaoExiste ;
    } /* if */
    
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

    if ( pTabuleiro == NULL )
    {
        return TAB_CondRetNaoExiste ;
    } /* if */

    /* Converte a linha e a coluna para inteiros */
    i = linha - '0' - 1 ;
    j = coluna - 'A' ;
    
    if ( ! TAB_VerificaCoordValida( i , j ) )
    {
        return TAB_CondRetCoordNaoExiste ;
    } /* if */
    
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
                                                 LIS_tppLista * pListaAmeacantesLinhas ,
                                                 LIS_tppLista * pListaAmeacantesColunas ,
                                                 TAB_tppTabuleiro pTabuleiro )
{
    
    int i , j ;
    int linhaInt , colunaInt ;
    CSA_tpCondRet retCasa ;
    LIS_tpCondRet retLista ;
    LIS_tppLista pListaAmeacantes ;
    CSA_tppCasa ptCasa ;
    char* linhaIns ;
    char* colunaIns ;

    /* Converte a linha e a coluna para inteiros */
    linhaInt = linha - '0' - 1 ;
    colunaInt = coluna - 'A' ;
    
    if ( ! TAB_VerificaCoordValida( linhaInt , colunaInt ) )
    {
        return TAB_CondRetCoordNaoExiste ;
    } /* if */
    
    retCasa = CSA_ObterListaAmeacantesCasa( &pListaAmeacantes , pTabuleiro->tabuleiro[linhaInt][colunaInt] ) ;
    
    if ( retCasa == CSA_CondRetNaoExiste )
    {
        return TAB_CondRetNaoExiste ;
    } /* if */
    
    retLista = LIS_CriarLista(  pListaAmeacantesLinhas ,
                                "lin" ,
                                ExcluirChar ,
                                CompararChar ,
                                IgualChar ) ;
    
    retLista = LIS_CriarLista(  pListaAmeacantesColunas ,
                                "col" ,
                                ExcluirChar ,
                                CompararChar ,
                                IgualChar ) ;

    retLista = LIS_AvancarElementoCorrente( pListaAmeacantes , -64 ) ;
    
    if( retLista == LIS_CondRetListaVazia )
    {
        return TAB_CondRetOK ;
    } /* if */ 

    while( retLista != LIS_CondRetNoCorrenteUlt )
    {
        retLista = LIS_ObterValor( pListaAmeacantes , ( void** ) &ptCasa ) ;
        for( i = 0 ; i < 8 ; i++ )
        {
            for( j = 0 ; j < 8 ; j++ )
            {
                if( ptCasa == pTabuleiro->tabuleiro[i][j] )
                {
                    linhaIns = ( char* ) malloc( sizeof( char ) ) ;
                    colunaIns = ( char* ) malloc( sizeof( char ) ) ;
                    *linhaIns = ( char ) i + 1 + '0' ;
                    *colunaIns = ( char ) j + 'A' ;
                    retLista = LIS_InserirElementoApos( *pListaAmeacantesLinhas ,
                                                        ( void* ) linhaIns ) ;
                    retLista = LIS_InserirElementoApos( *pListaAmeacantesColunas ,
                                                        ( void* ) colunaIns ) ;
   
                } /* if */
            } /* for */
        } /* for */

        retLista = LIS_AvancarElementoCorrente( pListaAmeacantes , 1 ) ;
    } /* while */

    return TAB_CondRetOK ;

} /* Fim função: TAB  &Obter lista de ameaçados de uma peça do tabuleiro */

TAB_tpCondRet TAB_ObterListaAmeacadosTabuleiro( char coluna ,
                                                char linha ,
                                                LIS_tppLista * pListaAmeacadosLinhas ,
                                                LIS_tppLista * pListaAmeacadosColunas ,
                                                TAB_tppTabuleiro pTabuleiro )
{
    int i , j ;
    int linhaInt , colunaInt ;
    CSA_tpCondRet retCasa ;
    LIS_tpCondRet retLista ;
    LIS_tppLista pListaAmeacados ;
    CSA_tppCasa ptCasa ;
    char* linhaIns ;
    char* colunaIns ;

    /* Converte a linha e a coluna para inteiros */
    linhaInt = linha - '0' - 1 ;
    colunaInt = coluna - 'A' ;
    
    if ( ! TAB_VerificaCoordValida( linhaInt , colunaInt ) )
    {
        return TAB_CondRetCoordNaoExiste ;
    } /* if */

    retCasa = CSA_ObterListaAmeacadosCasa( &pListaAmeacados , pTabuleiro->tabuleiro[linhaInt][colunaInt] ) ;
    
    if ( retCasa == CSA_CondRetNaoExiste )
    {
        return TAB_CondRetNaoExiste ;
    } /* if */
    
    retLista = LIS_CriarLista(  pListaAmeacadosLinhas ,
                                "lin" ,
                                ExcluirChar ,
                                CompararChar ,
                                IgualChar ) ;
    retLista = LIS_CriarLista(  pListaAmeacadosColunas ,
                                "col" ,
                                ExcluirChar ,
                                CompararChar ,
                                IgualChar ) ;

    retLista = LIS_AvancarElementoCorrente( pListaAmeacados , -64 ) ;
    if( retLista == LIS_CondRetListaVazia )
    {
        return TAB_CondRetOK ;
    } /* if */

    while( retLista != LIS_CondRetNoCorrenteUlt )
    {
        retLista = LIS_ObterValor( pListaAmeacados , ( void** ) &ptCasa ) ;
        for( i = 0 ; i < 8 ; i++ )
        {
            for( j = 0 ; j < 8 ; j++ )
            {
                if( ptCasa == pTabuleiro->tabuleiro[i][j] )
                {
                    linhaIns = ( char* ) malloc( sizeof( char ) ) ;
                    colunaIns = ( char* ) malloc( sizeof( char ) ) ;
                    *linhaIns = ( char ) i + 1 + '0' ;
                    *colunaIns = ( char ) j + 'A' ;
                    retLista = LIS_InserirElementoApos( *pListaAmeacadosLinhas ,
                                                        ( void* ) linhaIns ) ;
                    retLista = LIS_InserirElementoApos( *pListaAmeacadosColunas ,
                                                        ( void* ) colunaIns ) ;
   
                } /* if */
            } /* for */
        } /* for */

        retLista = LIS_AvancarElementoCorrente( pListaAmeacados , 1 ) ;
    } /* while */

    return TAB_CondRetOK ;
    
} /* Fim função: TAB  &Obter lista de ameaçados de uma peça do tabuleiro */

TAB_tpCondRet TAB_ObterCasasComPeca( LIS_tppLista * pListaCasasLinhas ,
                                     LIS_tppLista * pListaCasasColunas ,
                                     char peca ,
                                     char cor ,
                                     TAB_tppTabuleiro pTabuleiro )
{
    TAB_tpCondRet tabRet ;
    LIS_tpCondRet retLista ;
    char pecaRecebida ;
    char corRecebida ;
    int i ;
    int j ;

    retLista = LIS_CriarLista(   pListaCasasLinhas,
                                 "lin" ,
                                 ExcluirChar,
                                 CompararChar,
                                 IgualChar ) ;
    retLista = LIS_CriarLista(   pListaCasasColunas,
                                 "col" ,
                                 ExcluirChar,
                                 CompararChar,
                                 IgualChar ) ;
    for( i = 0 ; i < 8 ; i++ )
    {
        for( j = 0 ; j < 8 ; j++ )
        {
            tabRet = TAB_ObterPecaTabuleiro( ( char ) j + 'A' ,
                                             ( char ) i + 1 + '0' ,
                                             &pecaRecebida ,
                                             &corRecebida ,
                                             pTabuleiro ) ;

            if( pecaRecebida == peca && corRecebida == cor )
            {
                char* linhaIns = ( char* ) malloc( sizeof( char ) ) ;
                char* colunaIns = ( char* ) malloc( sizeof( char ) ) ;
                *linhaIns = ( char ) i + 1 + '0' ;
                *colunaIns = ( char ) j + 'A' ;
                retLista = LIS_InserirElementoApos( *pListaCasasLinhas ,
                                                    ( void* ) linhaIns ) ;
                retLista = LIS_InserirElementoApos( *pListaCasasColunas ,
                                                    ( void* ) colunaIns ) ;

            } /* if */
        } /* for */
    } /* for */

    return TAB_CondRetOK ;

} /* Fim função: TAB  &Obter Casas Com Peça */

/***** Código das funções encapuladas no módulo *****/

int TAB_VerificaCoordValida( int linha , int coluna )
{
    
    if ( ( linha > 7 ) || ( linha < 0 ) || ( coluna > 7 ) || ( coluna < 0 ) )
    {
        return 0 ;
    } /* if */
    return 1 ;
    
}

int TAB_CasaVazia( void* casa, void* aux )
{

    CSA_tppCasa pCasa = ( CSA_tppCasa ) casa ;
    char nomePeca, corPeca ;

    ( void ) aux;
    
    CSA_ObterPecaCasa( &nomePeca , &corPeca , pCasa ) ;

    if ( ( nomePeca == 'V' ) && ( corPeca == 'V' ) )
    {
        return 1 ;
    } /* if */
    return 0 ;
    
}

int TAB_CasaInimigo( void * casa, void * aux )
{
    
    CSA_tppCasa pCasa = ( CSA_tppCasa ) casa ;
    char nomePeca, corPeca ;

    ( void ) aux ;

    CSA_ObterPecaCasa( &nomePeca , &corPeca , pCasa ) ;
    
    if ( ( nomePeca == 'V' ) && ( corPeca == 'V' ) )
    {
        return 0 ;
    } /* if */
    return 1 ;
    
}

// linhas
int TAB_Dim1( void * casa, void* tab )
{
    int i , j ;
    TAB_tppTabuleiro pTabuleiro = (TAB_tppTabuleiro) tab ;
    CSA_tppCasa pCasa = ( CSA_tppCasa ) casa ;
        
    for ( i = 0 ; i < 8; i++ )
    {
        for ( j = 0 ; j < 8; j++ )
        {
            if ( pCasa == ( pTabuleiro->tabuleiro[i][j] ) ) {
                return i ;
            } /* if */
        } /* for */
    } /* for */
    return -1 ;
    
}

// colunas
int TAB_Dim0 ( void * casa , void* tab )
{
    int i , j ;
    TAB_tppTabuleiro pTabuleiro = ( TAB_tppTabuleiro ) tab ;
    CSA_tppCasa pCasa = ( CSA_tppCasa ) casa ;
    
    for ( i = 0 ; i < 8; i++ )
    {
        for ( j = 0 ; j < 8; j++ )
        {
            if ( pCasa == ( pTabuleiro->tabuleiro[i][j] ) ) {
                return j ;
            } /* if */
        } /* for */
    } /* for */
    return -1 ;
    
}

void ExcluirChar ( void * pDado )
{
    (void) pDado;
    return ;
}

int CompararChar ( void * pDado_1, void * pDado_2 )
{
    char* x = ( char* ) pDado_1 ;
    char* y = ( char* ) pDado_2 ;
    return *y - *x ;
}

int IgualChar ( void * pDado_1, void * pDado_2 )
{
    char* x = ( char* ) pDado_1 ;
    char* y = ( char* ) pDado_2 ;
    return *x == *y ;
}

void AtualizaListaAmeacantesAmeacados (TAB_tppTabuleiro pTabuleiro)
{
    int i , j , k , l ;

    char peca ;
    char cor ;

    CSA_tppCasa vetorCasasAmeacantes[8][8][64];
    int size_vetorCasasAmeacantes[8][8];
    CSA_tppCasa vetorCasasAmeacadas[8][8][64];
    int size_vetorCasasAmeacadas[8][8];

    CSA_tpCondRet           retCasa ;
    CSA_tppCasa             vetTodasCasas[64] ;
    VMV_tpCondRet           retDirMov ;
    VMV_tpMovimentoValido   retMov ;

    int sinal[] = { 0 , 0 };
    int condEsp[] = { 0 } ;

    int (*TAB_Dimensao[2]) (void* casa, void* tab) = { TAB_Dim0 , TAB_Dim1 } ;

    /* Atualizar Lista de Ameaçacdos e Ameaçantes */

    for ( i = 0 ; i < 8; i++ )
    {
        for ( j = 0 ; j < 8; j++ )
        {
            vetTodasCasas[j + 8 * i] = pTabuleiro->tabuleiro[i][j] ;
        } /* for */
    } /* for */
    

    for ( i = 0 ; i < 8 ; i++ )
    {
        for ( j = 0 ; j < 8 ; j++ )
        {
            size_vetorCasasAmeacantes[i][j] = 0;
            size_vetorCasasAmeacadas[i][j] = 0;
        } /* for */
    } /* for */

    for ( i = 0 ; i < 8 ; i++ )
    {
        for ( j = 0 ; j < 8 ; j++ )
        {
            retCasa = CSA_ObterPecaCasa( &peca , &cor , pTabuleiro->tabuleiro[i][j] ) ;
            if( TAB_CasaVazia( ( void* ) pTabuleiro->tabuleiro[i][j] , ( void* ) pTabuleiro ) == 1)
            {
                continue;
            } /* if */

            for ( k = 0 ; k < 8 ; k++ )
            {
                for ( l = 0 ; l < 8 ; l++ )
                {
                    retCasa = CSA_ObterPecaCasa( &peca , &cor , pTabuleiro->tabuleiro[i][j] ) ;
                    sinal[0] = cor == 'B' ? 1 : -1 ;

                    retDirMov = VMV_ChecarMovimentoPeca ( pTabuleiro->configDir ,
                                                          &retMov ,
                                                          peca ,
                                                          ( void * ) pTabuleiro->tabuleiro[i][j] ,
                                                          ( void * ) pTabuleiro->tabuleiro[k][l] ,
                                                          vetTodasCasas ,
                                                          64 ,
                                                          2 ,
                                                          TAB_Dimensao ,
                                                          sinal ,
                                                          TAB_CasaVazia ,
                                                          TAB_CasaInimigo ,
                                                          condEsp ,
                                                          0 ,
                                                          ( void * ) pTabuleiro ) ;
                    // retDirMov = VMV_MovimentoValidoSim ;
                    if ( retMov == VMV_MovimentoValidoSim )
                    {
                        vetorCasasAmeacantes[k][l][size_vetorCasasAmeacantes[k][l]] = pTabuleiro->tabuleiro[i][j] ;
                        vetorCasasAmeacadas[i][j][size_vetorCasasAmeacadas[i][j]] = pTabuleiro->tabuleiro[k][l] ;
                        size_vetorCasasAmeacantes[k][l]++ ;
                        size_vetorCasasAmeacadas[i][j]++ ;
                    } /* if */
                } /* for */
            } /* for */
        } /* for */
    } /* for */

    for ( i = 0 ; i < 8; i++ )
    {
        for ( j = 0 ; j < 8; j++ )
        {
            CSA_ModificarListaAmeacantesCasa( vetorCasasAmeacantes[i][j] , 
                                            size_vetorCasasAmeacantes[i][j] , 
                                            pTabuleiro->tabuleiro[i][j] ) ;
            CSA_ModificarListaAmeacadosCasa( vetorCasasAmeacadas[i][j] , 
                                            size_vetorCasasAmeacadas[i][j] , 
                                            pTabuleiro->tabuleiro[i][j] ) ;
        } /* for */
    } /* for */
}

/********** Fim do módulo de implementação: TAB  Tabuleiro para jogo de xadrez **********/

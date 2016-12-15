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
 *     6       vas   03/dez/2016 transformar o tabuleiro em dinamico
 *     5       vas   12/nov/2016 correção de múltiplos erros devido a nova interface do modulo casa
 *     3       lff   11/out/2016 em desenvolvimento
 *     2       lff   05/out/2016 em desenvolvimento
 *     1       lff   04/out/2016 início desenvolvimento
 *
 *
 ***************************************************************************/

// #define _DEBUG

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   "CASA.H"
#include   "VALIDA_MOV.H"
#include   "LISTA.H"

#ifdef _DEBUG
    #include "GENERICO.H"
    #include "CESPDIN.H"
    #include "CONTA.H"
    #include "TIPOS_ESPACO.H"
    //#include   "..\\tabelas\\IdTiposEspaco.def"
#endif

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
    
    // CSA_tppCasa tabuleiro [8] [8] ; //MUDAR
    LIS_tppLista tabuleiro ;

    /* Matriz de ponteiros para casas que define o tabuleiro */

    VMV_tppConfigDir configDir ;
    
} TAB_tpTabuleiro ;

/***** Protótipos das funções encapuladas no módulo *****/

static int TAB_VerificaCoordValida ( int linha , int coluna ) ;
static int TAB_CasaVazia ( void * casa , void * aux ) ;
static int TAB_CasaInimigo( void * casa, void* casa_atual, void * aux );
static int TAB_Dim0 ( void * casa , void * aux ) ;
static int TAB_Dim1 ( void * casa , void * aux ) ;
static void ExcluirChar ( void * pDado ) ;
static int CompararChar ( void * pDado_1 , void * pDado_2 ) ;
static int IgualChar ( void * pDado_1 , void * pDado_2 ) ;
static void ExcluirCasa ( void * pDado ) ;
static int CompararCasa ( void * pDado_1 , void * pDado_2 ) ;
static int IgualCasa ( void * pDado_1 , void * pDado_2 ) ;
static void CopiarListaCasa ( void ** pValor, void * pValorOriginal ) ;
static void ExcluirLista ( void * pDado ) ;
static int CompararLista ( void * pDado_1 , void * pDado_2 ) ;
static int IgualLista ( void * pDado_1 , void * pDado_2 ) ;
static void CopiarListaLista ( void ** pValor, void * pValorOriginal ) ;
static void AtualizaListaAmeacantesAmeacados ( TAB_tppTabuleiro pTabuleiro ) ;
static CSA_tppCasa TAB_PegarCasa( TAB_tppTabuleiro pTabuleiro , int linha , int coluna ) ;

#ifdef _DEBUG

    static TAB_tpCondRet TAB_DestroiCasaAtual( TAB_tppTabuleiro pTabuleiro , int coluna , int linha );
    static TAB_tpCondRet TAB_AtribuiNuloPonteiroProximaCasa( TAB_tppTabuleiro pTabuleiro , int coluna , int linha );
    static TAB_tpCondRet TAB_AtribuiNuloPonteiroCasaAnterior( TAB_tppTabuleiro pTabuleiro , int coluna , int linha );
    static TAB_tpCondRet TAB_AtribuiLixoPonteiroProximaCasa( TAB_tppTabuleiro pTabuleiro , int coluna , int linha );
    static TAB_tpCondRet TAB_AtribuiLixoPonteiroCasaAnterior( TAB_tppTabuleiro pTabuleiro , int coluna , int linha );
    static TAB_tpCondRet TAB_AtribuiNuloPonteiroValorCasa( TAB_tppTabuleiro pTabuleiro , int coluna , int linha );
    static TAB_tpCondRet TAB_AlteraEstruturaCasa( TAB_tppTabuleiro pTabuleiro , int coluna , int linha );
    static TAB_tpCondRet TAB_DestacaCasa( TAB_tppTabuleiro pTabuleiro , int coluna , int linha );
    static TAB_tpCondRet TAB_AtribuiNuloCasaAtual( TAB_tppTabuleiro pTabuleiro , int coluna , int linha );

#endif

#ifdef _DEBUG

    TAB_tpCondRet TAB_VerificaAssertivasEstruturais( TAB_tppTabuleiro pTabuleiro, int* numEncontrados  )
    {
        int tamanho;
        int identificadorDoTipo;
        int i;
        LIS_tppLista linha;
        LIS_tpErroEstrutura erroOcorrido;
        TAB_tpCondRet ret = TAB_CondRetOK;
        int numErrosRecebidos;
        
        *numEncontrados = 0;

        LIS_VerificaAssertivasEstruturais( pTabuleiro->tabuleiro, &erroOcorrido, &numErrosRecebidos );

        (*numEncontrados) += numErrosRecebidos;

        LIS_Tamanho( pTabuleiro->tabuleiro , &tamanho ) ;
        if(tamanho != 8)
        {
            CNT_CONTAR("erro-tamanho-lista-de-listas") ;

            (*numEncontrados)++;
            ret = TAB_CondRetFalhaNaEstrutura ;
        }

        LIS_GetTipo( pTabuleiro->tabuleiro, &identificadorDoTipo );
        if(identificadorDoTipo != TAB_TipoEspacoListaDeCasas)
        {
            CNT_CONTAR("erro-tipo-lista-de-listas") ;

            (*numEncontrados)++;
            ret = TAB_CondRetFalhaNaEstrutura ;
        }

        LIS_MoveInicio( pTabuleiro->tabuleiro ) ;

        for( i = 0 ; i < 8 ; i++ )
        {
            LIS_ObterValor( pTabuleiro->tabuleiro, (void**) &linha ) ;   

            LIS_VerificaAssertivasEstruturais( linha, &erroOcorrido, &numErrosRecebidos );
            (*numEncontrados) += numErrosRecebidos;

            LIS_Tamanho( linha, &tamanho );
            if( tamanho != 8)
            {
                CNT_CONTAR("erro-tamanho-lista-de-casas") ;

                (*numEncontrados)++;
                ret = TAB_CondRetFalhaNaEstrutura ;
            }

            LIS_GetTipo( linha, &identificadorDoTipo );
            if(identificadorDoTipo != TAB_TipoEspacoCasa)
            {
                CNT_CONTAR("erro-tipo-lista-de-casas") ;

                (*numEncontrados)++;
                ret = TAB_CondRetFalhaNaEstrutura ;
            }

            LIS_AvancarElementoCorrente( pTabuleiro->tabuleiro , 1 ) ;
        }

        return ret;
    }

#endif

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
 *
 *  Função: TAB  &Criar tabuleiro
 *  ****/

TAB_tpCondRet TAB_CriarTabuleiro( TAB_tppTabuleiro * pTabuleiro, char * pathConfig )
{

    int i , j ;
    TAB_tppTabuleiro pNovoTabuleiro = NULL ;
    CSA_tppCasa pCasa ;
    CSA_tpCondRet retCasa ;
    LIS_tppLista pLista = NULL ;
    LIS_tppLista novaLista = NULL ;
    LIS_tpCondRet retLista ;
    char* pecas ;
    char* cores ;
    int num_casas ;

    VMV_tpCondRet condRetCriarConfigDir ;
    
    pNovoTabuleiro = ( TAB_tpTabuleiro * ) malloc( sizeof( TAB_tpTabuleiro ) ) ;
    if ( pNovoTabuleiro == NULL )
    {
        return TAB_CondRetFaltouMemoria ;
    } /* if */

    #ifdef _DEBUG
        if( CED_DefinirTipoEspaco( ( void * ) pNovoTabuleiro , TAB_TipoTabuleiro ) == 0 )
        {
            printf("RETORNO 1");
            return TAB_CondRetFalhaDefinirTipoEspaco ;
        } /* if */
    #endif

    retLista = LIS_CriarLista( &pLista , "li" , ExcluirLista , CompararLista , IgualLista ) ;

    if( retLista == LIS_CondRetFaltouMemoria )
    {
        free( pNovoTabuleiro ) ;
        return TAB_CondRetFaltouMemoria ;
    } /* if */

    #ifdef _DEBUG
        LIS_SetTipo( pLista, TAB_TipoEspacoListaDeCasas );
    #endif
    
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
    
    condRetCriarConfigDir = VMV_LerTabuleiroInicial (   pNovoTabuleiro->configDir ,
                                                        &pecas , 
                                                        &cores , 
                                                        &num_casas ) ;

    for ( i = 0 ; i < 8 ; i++ )
    {
        retLista = LIS_CriarLista( &novaLista , "cl" , ExcluirCasa , CompararCasa , IgualCasa ) ;
        if ( retLista == LIS_CondRetFaltouMemoria )
        {
            return TAB_CondRetFaltouMemoria ;
        } /* if */

        #ifdef _DEBUG
            LIS_SetTipo( novaLista , TAB_TipoEspacoCasa ) ;
        #endif

        //TRATAR RET LISTA CORRETAMENTE
        for ( j = 0 ; j < 8 ; j++ )
        {
            retCasa = CSA_CriarCasa( &pCasa ) ;
            if ( retCasa == CSA_CondRetFaltouMemoria )
            {
                for ( ; i >= 0 ; i-- )
                {
                    for ( j-- ; j >= 0 ; j-- )
                    {
                        CSA_DestruirCasa( pCasa ) ;
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
                                            pCasa ) ;
            if ( retCasa == CSA_CondRetFaltouMemoria )
            {
                for ( ; i >= 0 ; i-- )
                {
                    for ( j-- ; j >= 0 ; j-- )
                    {
                        CSA_DestruirCasa( pCasa ) ;
                    } /* for */
                } /* for */
                free( pecas ) ;
                free( cores ) ;
                free( pNovoTabuleiro ) ;
                VMV_DestruirConfigDir( pNovoTabuleiro->configDir ) ;
                return TAB_CondRetFaltouMemoria ;
            } /* if */
            
            retLista = LIS_InserirElementoApos( novaLista , ( void * ) pCasa ) ;
            if ( retLista == LIS_CondRetFaltouMemoria )
            {
                return TAB_CondRetFaltouMemoria ;
            } /* if */

            #ifdef _DEBUG
                if( CED_DefinirTipoEspaco( pCasa , TAB_TipoEspacoCasa ) == 0 )
                {
                    printf("RETORNO 2 %d",j);
                    return TAB_CondRetFalhaDefinirTipoEspaco ;
                } /* if */
            #endif

            //TRATAR RET LISTA CORRETAMENTE
        } /* for */
        LIS_InserirElementoApos( pLista , ( void * ) novaLista ) ;
        if ( retLista == LIS_CondRetFaltouMemoria )
        {
            return TAB_CondRetFaltouMemoria ;
        } /* if */

        #ifdef _DEBUG
            if( CED_DefinirTipoEspaco (  novaLista , TAB_TipoEspacoListaDeCasas ) == 0 )
            {
                printf("RETORNO 3");
                return TAB_CondRetFalhaDefinirTipoEspaco ;
            }
        #endif
        //TRATAR RET LISTA CORRETAMENTE
    } /* for */

    pNovoTabuleiro->tabuleiro = pLista ;

    free( pecas ) ;
    free( cores ) ;
    *pTabuleiro = pNovoTabuleiro ;

    #ifdef _DEBUG
         // CED_DefinirTipoEspaco( pTabuleiro , TAB_TipoEspacoCabeca ) ;
        CED_MarcarEspacoAtivo( pNovoTabuleiro ) ;
    #endif

    AtualizaListaAmeacantesAmeacados ( * pTabuleiro ) ;
    
    return TAB_CondRetOK ;
    
} /* Fim função: TAB  &Criar tabuleiro */

/***************************************************************************
 *
 *  Função: TAB  &Copiar tabuleiro
 *  ****/

TAB_tpCondRet TAB_CopiarTabuleiro( TAB_tppTabuleiro * pTabuleiro, TAB_tppTabuleiro tabuleiroOriginal )
{

    TAB_tppTabuleiro pNovoTabuleiro = NULL ;

    VMV_tpCondRet condRetCriarConfigDir ;

    pNovoTabuleiro = ( TAB_tpTabuleiro * ) malloc( sizeof( TAB_tpTabuleiro ) ) ;
    if ( pNovoTabuleiro == NULL )
    {
        return TAB_CondRetFaltouMemoria ;
    } /* if */

    #ifdef _DEBUG
        if( CED_DefinirTipoEspaco( ( void * ) pNovoTabuleiro , TAB_TipoTabuleiro ) == 0 )
        {
            printf("RETORNO 4");
            return TAB_CondRetFalhaDefinirTipoEspaco ;
        }
    #endif

    condRetCriarConfigDir = VMV_CopiarConfigDir( &pNovoTabuleiro->configDir , tabuleiroOriginal->configDir) ;
    if ( condRetCriarConfigDir == VMV_CondRetErrFaltouMemoria )
    {
        free( pNovoTabuleiro ) ;
        return TAB_CondRetFaltouMemoria ;
    } /* if */

    LIS_CopiarLista( &pNovoTabuleiro->tabuleiro , tabuleiroOriginal->tabuleiro , CopiarListaLista ) ;

    *pTabuleiro = pNovoTabuleiro ;

    AtualizaListaAmeacantesAmeacados ( *pTabuleiro ) ;
    
    return TAB_CondRetOK ;
    
} /* Fim função: TAB  &Criar tabuleiro */

/***************************************************************************
 *
 *  Função: TAB  &Destruir tabuleiro
 *  ****/

TAB_tpCondRet TAB_DestruirTabuleiro( TAB_tppTabuleiro pTabuleiro )
{

    LIS_tpCondRet retLista ;
    
    if ( pTabuleiro == NULL )
    {
        return TAB_CondRetNaoExiste ;
    } /* if */

    retLista = LIS_DestruirLista( pTabuleiro->tabuleiro ) ;
    if ( retLista == LIS_CondRetListaNaoExiste )
    {
        return TAB_CondRetNaoExiste ;
    } /* if */
    
    VMV_DestruirConfigDir( pTabuleiro->configDir ) ;

    #ifdef _DEBUG
        CED_MarcarEspacoNaoAtivo( pTabuleiro ) ;
    #endif

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
    CSA_tppCasa casa ;
    CSA_tpCondRet retCasa ;

    i = linha - '0' - 1 ;
    j = coluna - 'A' ;

    if ( ! TAB_VerificaCoordValida( i , j ) )
    {
        return TAB_CondRetCoordNaoExiste ;
    } /* if */

    casa = TAB_PegarCasa( pTabuleiro , i , j ) ;

    retCasa = CSA_InserirPecaCasa( nomePeca, corPeca, casa ) ;

    if ( retCasa == CSA_CondRetNaoExiste )
    {
        return TAB_CondRetCoordNaoExiste ;
    } /* if */

    AtualizaListaAmeacantesAmeacados ( pTabuleiro ) ;

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
    CSA_tppCasa             casaAtual ;
    CSA_tppCasa             casaDestino ;
    VMV_tpCondRet           retDirMov ;
    VMV_tpMovimentoValido   retMov ;
    
    int i , j ;
    int colAtual , linAtual ;
    int colDestino , linDestino ;

    int sinal[] = { 0 , 0 } ;
    int condEsp[] = { 0 } ;

    char peca ;
    char cor ;

    int (*TAB_Dimensao[2]) (void* casa, void* tab) = { TAB_Dim0 , TAB_Dim1 } ;

    if ( pTabuleiro == NULL )
    {
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
    
    casaAtual = TAB_PegarCasa( pTabuleiro , linAtual , colAtual ) ;

    retCasa = CSA_ObterPecaCasa( &peca , &cor , casaAtual ) ;
    if ( retCasa == CSA_CondRetNaoExiste )
    {
        return TAB_CondRetNaoExiste ;
    } /* if */
    
    for ( i = 0 ; i < 8; i++ )
    {
        for ( j = 0 ; j < 8; j++ )
        {
            casaAtual = TAB_PegarCasa( pTabuleiro , i , j ) ;
            if ( casaAtual == NULL )
            {
                return TAB_CondRetNaoExiste ;
            } /* if */
            vetTodasCasas[ j + 8 * i ] = casaAtual ;
        } /* for */
    } /* for */
    
    sinal[0] = cor == 'B' ? 1 : -1 ;

    casaAtual = TAB_PegarCasa( pTabuleiro , linAtual , colAtual ) ;
    if ( casaAtual == NULL )
    {
        return TAB_CondRetNaoExiste ;
    } /* if */

    casaDestino = TAB_PegarCasa( pTabuleiro , linDestino , colDestino ) ;
    if ( casaDestino == NULL )
    {
        return TAB_CondRetNaoExiste ;
    } /* if */

    /* Verificar validade do movimento */
    retDirMov = VMV_ChecarMovimentoPeca ( pTabuleiro->configDir ,
                                          &retMov ,
                                          peca ,
                                          //( void* ) pTabuleiro->tabuleiro[linAtual][colAtual] ,
                                          ( void * ) casaAtual ,
                                          //( void* ) pTabuleiro->tabuleiro[linDestino][colDestino] ,
                                          ( void * ) casaDestino ,
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
        return TAB_CondRetFalhaArq ;
    }
    else if ( ( retDirMov == VMV_CondRetVariavelNaoExistente ) ||
              ( retDirMov == VMV_CondRetErrComandoNaoExistente ) )
    {
        return TAB_CondRetNaoExiste ;
    } /* if */

    if ( retMov == VMV_MovimentoValidoNao )
    {
        return TAB_CondRetMovInvalido ;
    } /* if */
    
    /* Mover peça de casa */
    casaAtual = TAB_PegarCasa( pTabuleiro , linAtual , colAtual ) ;

    retCasa = CSA_RetirarPecaCasa ( casaAtual ) ;
    if ( retCasa == CSA_CondRetNaoExiste )
    {
        return TAB_CondRetNaoExiste ;
    } /* if */

    retCasa = CSA_InserirPecaCasa( 'V' , 'V' , casaAtual ) ;

    casaDestino = TAB_PegarCasa( pTabuleiro , linDestino , colDestino ) ;

    retCasa = CSA_RetirarPecaCasa ( casaDestino ) ;
    if ( retCasa == CSA_CondRetNaoExiste )
    {
        return TAB_CondRetNaoExiste ;
    } /* if */

    retCasa = CSA_InserirPecaCasa( peca , cor , casaDestino ) ;
    if ( retCasa == CSA_CondRetFaltouMemoria )
    {
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
    CSA_tppCasa casa ;
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

    casa = TAB_PegarCasa( pTabuleiro , i , j ) ;
    
    retCasa = CSA_RetirarPecaCasa( casa ) ;
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
    CSA_tppCasa casa ;
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

    casa = TAB_PegarCasa( pTabuleiro , i , j ) ;

    retCasa = CSA_ObterPecaCasa( pNomePeca , pCorPeca , casa ) ;
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
    
    // *pCasa = pTabuleiro->tabuleiro[i][j] ;
    *pCasa = TAB_PegarCasa( pTabuleiro , i , j ) ;
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
    CSA_tppCasa casa ;
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

    casa = TAB_PegarCasa( pTabuleiro , linhaInt , colunaInt ) ;
    
    retCasa = CSA_ObterListaAmeacantesCasa( &pListaAmeacantes , casa ) ;
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
                casa = TAB_PegarCasa( pTabuleiro , i , j ) ;
                if ( casa == NULL )
                {
                    return TAB_CondRetNaoExiste ;
                } /* if */

                if( ptCasa == casa )
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

/***************************************************************************
 *
 *  Função: TAB  &Obter lista de ameaçados de uma peça do tabuleiro
 *  ****/

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
    CSA_tppCasa casa ;
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

    casa = TAB_PegarCasa( pTabuleiro , linhaInt , colunaInt ) ;

    retCasa = CSA_ObterListaAmeacadosCasa( &pListaAmeacados , casa ) ;
    
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
                casa = TAB_PegarCasa( pTabuleiro , i , j ) ;
                if ( casa == NULL )
                {
                    return TAB_CondRetNaoExiste ;
                } /* if */

                // if( ptCasa == pTabuleiro->tabuleiro[i][j] )
                if( ptCasa == casa )
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

/***************************************************************************
 *
 *  Função: TAB  &Obter as casas com peça do tabuleiro
 *  ****/

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

/***************************************************************************
 *
 *  Função: TAB  &Print Tabuleiro
 *  ****/

TAB_tpCondRet TAB_GetPrintTabuleiro( TAB_tppTabuleiro pTabuleiro, char** print )
{

    int i , j ;
    char * tempPrint ;
    CSA_tppCasa casa ;
    CSA_tpCondRet casaCondRet ;
    char letterString[ 2 ] = "X" ;

    *print = ( char* ) malloc( sizeof( char ) * ( 10*11*3+1 ) ) ;

    if( *print == NULL )
    {
        return TAB_CondRetFaltouMemoria;
    }

    (*print)[ 0 ] = '\0' ;

    strcat( *print , " |A  B  C  D  E  F  G  H  \n" ) ;
    strcat( *print , "--------------------------\n" ) ;
    for( i = 0 ; i < 8 ; i++ )
    {
        letterString[ 0 ] = ( char ) i + '1' ;
        strcat( *print , letterString ) ;
        strcat( *print , "|" ) ;

        for( j = 0 ; j < 8 ; j++)
        {
            casa = TAB_PegarCasa( pTabuleiro , i , j ) ;
            if ( casa == NULL )
            {
                return TAB_CondRetNaoExiste ;
            } /* if */
            
            casaCondRet = CSA_GetPrintCasa( casa , &tempPrint ) ;
            if( casaCondRet == CSA_CondRetFaltouMemoria )
            {
                free( *print ) ;
                return TAB_CondRetFaltouMemoria ;
            }
            strcat( *print , tempPrint ) ;
            strcat( *print , " ") ;
            free( tempPrint ) ;
        }
        strcat( *print , "\n" ) ;
    }
    
    return TAB_CondRetOK ;
} /* Fim função: TAB  &Print Tabuleiro */

#ifdef _DEBUG

    /***********************************************************************
     *
     *  Função: TAB  &Deturpa Tabuleiro
     *  ****/

    TAB_tpCondRet TAB_Deturpa( TAB_tppTabuleiro pTabuleiro, TAB_tpDeturpacao tipoDeturpacao , char coluna , char linha )
    {
        TAB_tpCondRet ret = TAB_CondRetOK;

        int linhaInt = linha - '0' - 1 ;
        int colunaInt = coluna - 'A' ;
        
        if ( tipoDeturpacao == TAB_ELIMINA_ELEMENTO_CORRENTE )
        {
            ret = TAB_DestroiCasaAtual( pTabuleiro , colunaInt , linhaInt ) ;
        }
        else if ( tipoDeturpacao == TAB_NULL_CASA_SUCESSORA )
        {
            ret = TAB_AtribuiNuloPonteiroProximaCasa( pTabuleiro , colunaInt , linhaInt ) ;
        }
        else if ( tipoDeturpacao == TAB_NULL_CASA_PREDECESSORA )
        {
            ret = TAB_AtribuiNuloPonteiroCasaAnterior( pTabuleiro , colunaInt , linhaInt ) ;
        }
        else if ( tipoDeturpacao == TAB_LIXO_CASA_SUCESSORA )
        {
            ret = TAB_AtribuiLixoPonteiroProximaCasa( pTabuleiro , colunaInt , linhaInt ) ;
        }
        else if ( tipoDeturpacao == TAB_LIXO_CASA_PREDECESSORA )
        {
            ret = TAB_AtribuiLixoPonteiroCasaAnterior( pTabuleiro , colunaInt , linhaInt ) ;
        }
        else if ( tipoDeturpacao == TAB_NULL_CONTEUDO_CASA )
        {
            ret = TAB_AtribuiNuloPonteiroValorCasa( pTabuleiro , colunaInt , linhaInt ) ;
        }
        else if ( tipoDeturpacao == TAB_ALTERA_TIPO_APONTADO_CASA )
        {
            ret = TAB_AlteraEstruturaCasa( pTabuleiro , colunaInt , linhaInt ) ;
        }
        else if ( tipoDeturpacao == TAB_DESTACA_CASA_SEM_FREE )
        {
            ret = TAB_DestacaCasa( pTabuleiro , colunaInt , linhaInt ) ;
        }
        else if ( tipoDeturpacao == TAB_NULL_PONTEIRO_CORRENTE )
        {
            ret = TAB_AtribuiNuloCasaAtual( pTabuleiro , colunaInt , linhaInt ) ;
        }
        
        if ( ret != TAB_CondRetOK )
        {
            return TAB_CondRetFalhaDeturpar ;
        }
        
        return ret ;
    }

#endif

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

    ( void ) aux ;
    
    CSA_ObterPecaCasa( &nomePeca , &corPeca , pCasa ) ;

    if ( ( nomePeca == 'V' ) && ( corPeca == 'V' ) )
    {
        return 1 ;
    } /* if */

    return 0 ;
}

int TAB_CasaInimigo( void * casa, void * casa_atual, void * aux )
{
    
    CSA_tppCasa pCasa = ( CSA_tppCasa ) casa ;
    CSA_tppCasa pCasaAtual = ( CSA_tppCasa ) casa_atual ;
    char nomePeca, corPeca ;
    char corAtual;
    char corOposta;

    ( void ) aux ;

    CSA_ObterPecaCasa( &nomePeca , &corPeca , pCasa ) ;
    CSA_ObterPecaCasa( &nomePeca , &corAtual , pCasaAtual ) ;

    corOposta = corAtual == 'B' ? 'P' : 'B' ;
    
    if ( corPeca == corOposta )
    {
        return 1 ;
    } /* if */

    return 0 ;    
}

// linhas
int TAB_Dim1( void * casa, void * tab )
{
    int i , j ;
    TAB_tppTabuleiro pTabuleiro = ( TAB_tppTabuleiro ) tab ;
    CSA_tppCasa casa2 ;
    CSA_tppCasa pCasa = ( CSA_tppCasa ) casa ;
        
    for ( i = 0 ; i < 8; i++ )
    {
        for ( j = 0 ; j < 8; j++ )
        {
            casa2 = TAB_PegarCasa( pTabuleiro , i , j ) ;

            if ( pCasa == casa2 )
            {
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
    TAB_tppTabuleiro pTabuleiro = (TAB_tppTabuleiro) tab ;
    CSA_tppCasa casa2 ;
    CSA_tppCasa pCasa = ( CSA_tppCasa ) casa ;
        
    for ( i = 0 ; i < 8; i++ )
    {
        for ( j = 0 ; j < 8; j++ )
        {
            casa2 = TAB_PegarCasa( pTabuleiro , i , j ) ;

            if ( pCasa == casa2 )
            {
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

void ExcluirCasa ( void * pDado )
{
    CSA_tppCasa x = ( CSA_tppCasa ) pDado ;

    CSA_DestruirCasa( x ) ;

    return ;
}

int CompararCasa ( void * pDado_1, void * pDado_2 )
{
    int igualdade ;
    CSA_tppCasa x = ( CSA_tppCasa ) pDado_1 ;
    CSA_tppCasa y = ( CSA_tppCasa ) pDado_2 ;

    CSA_CompararCasa( x , y , &igualdade) ;

    return igualdade ;
}

int IgualCasa ( void * pDado_1, void * pDado_2 )
{
    int igualdade ;
    CSA_tppCasa x = ( CSA_tppCasa ) pDado_1 ;
    CSA_tppCasa y = ( CSA_tppCasa ) pDado_2 ;

    CSA_CompararCasa( x , y , &igualdade) ;

    return igualdade ;
}

void CopiarListaCasa ( void ** pValor, void * pValorOriginal )
{
    CSA_tppCasa casaOriginal = ( CSA_tppCasa ) pValorOriginal ;
    CSA_tppCasa * casaNova = ( CSA_tppCasa * ) pValor ;

    CSA_CopiarCasa( casaNova , casaOriginal ) ;

    #ifdef _DEBUG
        CED_DefinirTipoEspaco( (void*) *casaNova, TAB_TipoEspacoCasa);
    #endif

    return ;
}

void ExcluirLista ( void * pDado )
{
    LIS_tppLista x = ( LIS_tppLista ) pDado ;

    LIS_DestruirLista( x ) ;

    return ;
}

int CompararLista ( void * pDado_1, void * pDado_2 )
{
    int igualdade ;
    LIS_tppLista x = ( LIS_tppLista ) pDado_1 ;
    LIS_tppLista y = ( LIS_tppLista ) pDado_2 ;

    LIS_VerificaIgualdade( x , y , &igualdade) ;

    return igualdade ;
}

int IgualLista ( void * pDado_1, void * pDado_2 )
{
    int igualdade ;
    LIS_tppLista x = ( LIS_tppLista ) pDado_1 ;
    LIS_tppLista y = ( LIS_tppLista ) pDado_2 ;

    LIS_VerificaIgualdade( x , y , &igualdade) ;

    return igualdade ;
}

void CopiarListaLista ( void ** pValor, void * pValorOriginal )
{
    LIS_tppLista listaOriginal = ( LIS_tppLista ) pValorOriginal ;
    LIS_tppLista * listaNova = ( LIS_tppLista * ) pValor ;

    LIS_CopiarLista( listaNova , listaOriginal , CopiarListaCasa ) ;

    #ifdef _DEBUG
        CED_DefinirTipoEspaco( (void*) *listaNova, TAB_TipoEspacoListaDeCasas);
    #endif

    return ;
}

void AtualizaListaAmeacantesAmeacados ( TAB_tppTabuleiro pTabuleiro )
{
    int i , j , k , l ;

    char peca ;
    char cor ;

    CSA_tppCasa vetorCasasAmeacantes[ 8 ][ 8 ][ 64 ] ;
    int size_vetorCasasAmeacantes[ 8 ][ 8 ] ;
    CSA_tppCasa vetorCasasAmeacadas[ 8 ][ 8 ][ 64 ] ;
    int size_vetorCasasAmeacadas[ 8 ][ 8 ] ;

    CSA_tpCondRet           retCasa ;
    CSA_tppCasa             vetTodasCasas[ 64 ] ;
    CSA_tppCasa             casa ;
    CSA_tppCasa             casa2 ;
    VMV_tpCondRet           retDirMov ;
    VMV_tpMovimentoValido   retMov ;

    int sinal[] = { 0 , 0 } ;
    int condEsp[] = { 0 } ;

    int ( * TAB_Dimensao[2] ) ( void * casa , void * tab ) = { TAB_Dim0 , TAB_Dim1 } ;

    /* Atualizar Lista de Ameaçacdos e Ameaçantes */

    for ( i = 0 ; i < 8; i++ )
    {
        for ( j = 0 ; j < 8; j++ )
        {
            vetTodasCasas[j + 8 * i] = TAB_PegarCasa( pTabuleiro , i , j ) ;
        } /* for */
    } /* for */
    

    for ( i = 0 ; i < 8 ; i++ )
    {
        for ( j = 0 ; j < 8 ; j++ )
        {
            size_vetorCasasAmeacantes[ i ][ j ] = 0 ;
            size_vetorCasasAmeacadas[ i ][ j ] = 0 ;
        } /* for */
    } /* for */

    for ( i = 0 ; i < 8 ; i++ )
    {
        for ( j = 0 ; j < 8 ; j++ )
        {
            casa = TAB_PegarCasa( pTabuleiro , i , j ) ;

            retCasa = CSA_ObterPecaCasa( &peca , &cor , casa ) ;
            if( TAB_CasaVazia( ( void * ) casa , ( void * ) pTabuleiro ) == 1 )
            {
                continue ;
            } /* if */

            for ( k = 0 ; k < 8 ; k++ )
            {
                for ( l = 0 ; l < 8 ; l++ )
                {
                    casa = TAB_PegarCasa( pTabuleiro , i , j ) ;

                    casa2 = TAB_PegarCasa( pTabuleiro , k , l ) ;

                    retCasa = CSA_ObterPecaCasa( &peca , &cor , casa ) ;

                    sinal[ 0 ] = cor == 'B' ? 1 : -1 ;

                    retDirMov = VMV_ChecarMovimentoPeca ( pTabuleiro->configDir ,
                                                          &retMov ,
                                                          peca ,
                                                          ( void * ) casa ,
                                                          ( void * ) casa2 ,
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
                        vetorCasasAmeacantes[k][l][size_vetorCasasAmeacantes[k][l]] = casa ;
                        vetorCasasAmeacadas[i][j][size_vetorCasasAmeacadas[i][j]] = casa2 ;
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

            casa = TAB_PegarCasa( pTabuleiro , i , j ) ;

            CSA_ModificarListaAmeacantesCasa( vetorCasasAmeacantes[i][j] , 
                                            size_vetorCasasAmeacantes[i][j] , 
                                            casa ) ;
            CSA_ModificarListaAmeacadosCasa( vetorCasasAmeacadas[i][j] , 
                                            size_vetorCasasAmeacadas[i][j] , 
                                            casa ) ;
        } /* for */
    } /* for */
}

CSA_tppCasa TAB_PegarCasa( TAB_tppTabuleiro pTabuleiro , int linha , int coluna )
{
    CSA_tppCasa casa = NULL ;
    LIS_tppLista linhas  = NULL ;
    LIS_tppLista colunas = NULL ;
    LIS_tpCondRet retLista ;

    linhas = pTabuleiro->tabuleiro ;

    retLista = LIS_MoveInicio( linhas ) ;

    retLista = LIS_AvancarElementoCorrente( linhas , linha ) ;
    if ( retLista == LIS_CondRetNoCorrenteUlt )
    {
        return NULL ;
    }
    else if ( retLista == LIS_CondRetNoCorrentePrim )
    {
        return NULL ;
    }
    else if ( retLista == LIS_CondRetListaVazia )
    {
        return NULL ;
    } /* if */

    retLista = LIS_ObterValor( linhas , ( void ** ) &colunas ) ;

    retLista = LIS_MoveInicio( colunas ) ;

    retLista = LIS_AvancarElementoCorrente( colunas , coluna ) ;
    if ( retLista == LIS_CondRetNoCorrenteUlt )
    {
        return NULL ;
    }
    else if ( retLista == LIS_CondRetNoCorrentePrim )
    {
        return NULL ;
    }
    else if ( retLista == LIS_CondRetListaVazia )
    {
        return NULL ;
    } /* if */

    retLista = LIS_ObterValor( colunas , ( void ** ) &casa ) ;

    return casa ;
}

/***** Código das funções de deturpação do módulo *****/

#ifdef _DEBUG

    TAB_tpCondRet TAB_DestroiCasaAtual( TAB_tppTabuleiro pTabuleiro , int coluna , int linha )
    {
        
        LIS_tppLista linhas  = NULL ;
        LIS_tppLista colunas = NULL ;
        LIS_tpCondRet retLista ;
        
        linhas = pTabuleiro->tabuleiro ;
        
        retLista = LIS_MoveInicio( linhas ) ;
        
        retLista = LIS_AvancarElementoCorrente( linhas , linha ) ;
        if ( retLista == LIS_CondRetNoCorrenteUlt )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetNoCorrentePrim )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista = LIS_ObterValor( linhas , ( void ** ) &colunas ) ;
        if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista = LIS_MoveInicio( colunas ) ;
        
        retLista = LIS_AvancarElementoCorrente( colunas , coluna ) ;
        if ( retLista == LIS_CondRetNoCorrenteUlt )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetNoCorrentePrim )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista = LIS_ExcluirElemento( colunas ) ;
        if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste;
        }
        
        return TAB_CondRetOK ;
        
    }

    TAB_tpCondRet TAB_AtribuiNuloPonteiroProximaCasa( TAB_tppTabuleiro pTabuleiro , int coluna , int linha )
    {
        
        void ** pProxCasa ;
        LIS_tppLista linhas  = NULL ;
        LIS_tppLista colunas = NULL ;
        LIS_tpCondRet retLista ;
        
        linhas = pTabuleiro->tabuleiro ;
        
        retLista = LIS_MoveInicio( linhas ) ;
        
        retLista = LIS_AvancarElementoCorrente( linhas , linha ) ;
        if ( retLista == LIS_CondRetNoCorrenteUlt )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetNoCorrentePrim )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista = LIS_ObterValor( linhas , ( void ** ) &colunas ) ;
        if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista = LIS_MoveInicio( colunas ) ;
        
        retLista = LIS_AvancarElementoCorrente( colunas , coluna ) ;
        if ( retLista == LIS_CondRetNoCorrenteUlt )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetNoCorrentePrim )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista =  LIS_ObterPonteiroProximo( colunas , &pProxCasa ) ;
        if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste;
        }
        
        *pProxCasa = NULL ;
        
        return TAB_CondRetOK ;
        
    }

    TAB_tpCondRet TAB_AtribuiNuloPonteiroCasaAnterior( TAB_tppTabuleiro pTabuleiro , int coluna , int linha )
    {
        
        void ** pCasaAnterior ;
        LIS_tppLista linhas  = NULL ;
        LIS_tppLista colunas = NULL ;
        LIS_tpCondRet retLista ;
        
        linhas = pTabuleiro->tabuleiro ;
        
        retLista = LIS_MoveInicio( linhas ) ;
        
        retLista = LIS_AvancarElementoCorrente( linhas , linha ) ;
        if ( retLista == LIS_CondRetNoCorrenteUlt )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetNoCorrentePrim )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista = LIS_ObterValor( linhas , ( void ** ) &colunas ) ;
        if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista = LIS_MoveInicio( colunas ) ;
        
        retLista = LIS_AvancarElementoCorrente( colunas , coluna ) ;
        if ( retLista == LIS_CondRetNoCorrenteUlt )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetNoCorrentePrim )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista = LIS_ObterPonteiroAnterior( colunas , &pCasaAnterior ) ;
        if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste;
        }
        
        *pCasaAnterior = NULL ;
        
        return TAB_CondRetOK ;
        
    }

    TAB_tpCondRet TAB_AtribuiLixoPonteiroProximaCasa( TAB_tppTabuleiro pTabuleiro , int coluna , int linha )
    {
        
        void ** pProxCasa ;
        LIS_tppLista linhas  = NULL ;
        LIS_tppLista colunas = NULL ;
        LIS_tpCondRet retLista ;
        
        linhas = pTabuleiro->tabuleiro ;
        
        retLista = LIS_MoveInicio( linhas ) ;
        
        retLista = LIS_AvancarElementoCorrente( linhas , linha ) ;
        if ( retLista == LIS_CondRetNoCorrenteUlt )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetNoCorrentePrim )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista = LIS_ObterValor( linhas , ( void ** ) &colunas ) ;
        if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista = LIS_MoveInicio( colunas ) ;
        
        retLista = LIS_AvancarElementoCorrente( colunas , coluna ) ;
        if ( retLista == LIS_CondRetNoCorrenteUlt )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetNoCorrentePrim )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista = LIS_ObterPonteiroProximo( colunas , &pProxCasa ) ;
        if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste;
        }
        
        *pProxCasa = (void*) 0 ;
        
        return TAB_CondRetOK ;
        
    }

    TAB_tpCondRet TAB_AtribuiLixoPonteiroCasaAnterior( TAB_tppTabuleiro pTabuleiro , int coluna , int linha )
    {
        
        void ** pCasaAnterior ;
        LIS_tppLista linhas  = NULL ;
        LIS_tppLista colunas = NULL ;
        LIS_tpCondRet retLista ;
        
        linhas = pTabuleiro->tabuleiro ;
        
        retLista = LIS_MoveInicio( linhas ) ;
        
        retLista = LIS_AvancarElementoCorrente( linhas , linha ) ;
        if ( retLista == LIS_CondRetNoCorrenteUlt )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetNoCorrentePrim )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista = LIS_ObterValor( linhas , ( void ** ) &colunas ) ;
        if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista = LIS_MoveInicio( colunas ) ;
        
        retLista = LIS_AvancarElementoCorrente( colunas , coluna ) ;
        if ( retLista == LIS_CondRetNoCorrenteUlt )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetNoCorrentePrim )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista = LIS_ObterPonteiroAnterior( colunas , &pCasaAnterior ) ;
        if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste;
        }
        
        *pCasaAnterior = (void*) 0 ;
        
        return TAB_CondRetOK ;
        
    }

    TAB_tpCondRet TAB_AtribuiNuloPonteiroValorCasa( TAB_tppTabuleiro pTabuleiro , int coluna , int linha )
    {
        
        CSA_tppCasa* pCasa ;
        LIS_tppLista linhas  = NULL ;
        LIS_tppLista colunas = NULL ;
        LIS_tpCondRet retLista ;
        
        linhas = pTabuleiro->tabuleiro ;
        
        retLista = LIS_MoveInicio( linhas ) ;
        
        retLista = LIS_AvancarElementoCorrente( linhas , linha ) ;
        if ( retLista == LIS_CondRetNoCorrenteUlt )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetNoCorrentePrim )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista = LIS_ObterValor( linhas , ( void ** ) &colunas ) ;
        if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista = LIS_MoveInicio( colunas ) ;
        
        retLista = LIS_AvancarElementoCorrente( colunas , coluna ) ;
        if ( retLista == LIS_CondRetNoCorrenteUlt )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetNoCorrentePrim )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista = LIS_ObterValor( colunas , (void**) &pCasa ) ;
        if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        *pCasa = NULL ;
        
        return TAB_CondRetOK ;
        
    }

    TAB_tpCondRet TAB_AlteraEstruturaCasa( TAB_tppTabuleiro pTabuleiro , int coluna , int linha )
    {
        
        CSA_tppCasa pCasa ;
        LIS_tppLista linhas  = NULL ;
        LIS_tppLista colunas = NULL ;
        LIS_tpCondRet retLista ;
        
        linhas = pTabuleiro->tabuleiro ;
        
        retLista = LIS_MoveInicio( linhas ) ;
        
        retLista = LIS_AvancarElementoCorrente( linhas , linha ) ;
        if ( retLista == LIS_CondRetNoCorrenteUlt )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetNoCorrentePrim )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista = LIS_ObterValor( linhas , ( void ** ) &colunas ) ;
        if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista = LIS_MoveInicio( colunas ) ;
        
        retLista = LIS_AvancarElementoCorrente( colunas , coluna ) ;
        if ( retLista == LIS_CondRetNoCorrenteUlt )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetNoCorrentePrim )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista = LIS_ObterValor( colunas , &pCasa ) ;
        if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        CED_DefinirTipoEspaco( pCasa , TAB_TipoEspacoPeca) ;
        
        return TAB_CondRetOK ;
        
    }

    TAB_tpCondRet TAB_DestacaCasa( TAB_tppTabuleiro pTabuleiro , int coluna , int linha )
    {
        
        void** pCasaAnterior;
        void** pCasaProxima ;
        CSA_tppCasa casaAnterior;
        CSA_tppCasa casaProxima;
        LIS_tppLista linhas  = NULL ;
        LIS_tppLista colunas = NULL ;
        LIS_tpCondRet retLista ;
        
        linhas = pTabuleiro->tabuleiro ;
        
        retLista = LIS_MoveInicio( linhas ) ;
        
        retLista = LIS_AvancarElementoCorrente( linhas , linha ) ;
        if ( retLista == LIS_CondRetNoCorrenteUlt )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetNoCorrentePrim )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista = LIS_ObterValor( linhas , ( void ** ) &colunas ) ;
        if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista = LIS_MoveInicio( colunas ) ;
        
        retLista = LIS_AvancarElementoCorrente( colunas , coluna - 1 ) ;
        if ( retLista == LIS_CondRetNoCorrenteUlt )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetNoCorrentePrim )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista = LIS_ObterValor( colunas , &casaAnterior ) ;
        if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        }

        printf("Obteve casa anterior\n");

        retLista = LIS_MoveInicio( colunas ) ;
        
        retLista = LIS_AvancarElementoCorrente( colunas , coluna + 1 ) ;
        if ( retLista == LIS_CondRetNoCorrenteUlt )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetNoCorrentePrim )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista = LIS_ObterValor( colunas , &casaProxima ) ;
        if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista = LIS_ObterPonteiroAnterior( colunas , &pCasaProxima ) ;
        if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste;
        }

        printf("Obteve casa proxima\n");
        
        *pCasaProxima = ( void * ) &casaAnterior ;
        
        retLista = LIS_ObterPonteiroProximo( colunas , &pCasaAnterior ) ;
        if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste;
        }
        
        *pCasaAnterior = ( void * ) &casaProxima ;

        printf("Acabou destaca casa\n");
        
        return TAB_CondRetOK ;
        
    }

    TAB_tpCondRet TAB_AtribuiNuloCasaAtual( TAB_tppTabuleiro pTabuleiro , int coluna , int linha )
    {
        
        CSA_tppCasa* pCasa ;
        LIS_tppLista linhas  = NULL ;
        LIS_tppLista colunas = NULL ;
        LIS_tpCondRet retLista ;
        
        linhas = pTabuleiro->tabuleiro ;
        
        retLista = LIS_MoveInicio( linhas ) ;
        
        retLista = LIS_AvancarElementoCorrente( linhas , linha ) ;
        if ( retLista == LIS_CondRetNoCorrenteUlt )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetNoCorrentePrim )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista = LIS_ObterValor( linhas , ( void ** ) &colunas ) ;
        if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista = LIS_MoveInicio( colunas ) ;
        
        retLista = LIS_AvancarElementoCorrente( colunas , coluna ) ;
        if ( retLista == LIS_CondRetNoCorrenteUlt )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetNoCorrentePrim )
        {
            return TAB_CondRetNaoExiste ;
        }
        else if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        retLista = LIS_ObterPonteiroValor( colunas , &pCasa ) ;
        if ( retLista == LIS_CondRetListaVazia )
        {
            return TAB_CondRetNaoExiste ;
        } /* if */
        
        *pCasa = NULL ;
        
        return TAB_CondRetOK ;
        
    } /* Fim função: TAB  &Atribui NULL a Casa Atual */

#endif

/********** Fim do módulo de implementação: TAB  Tabuleiro para jogo de xadrez **********/

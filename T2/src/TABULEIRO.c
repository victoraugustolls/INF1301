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
 *     2       lff   05/out/2016 desenvolvimento
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
 *  $TC Tipo de dados: TAB Tabuleiro
 *
 *
 ***********************************************************************/

typedef struct TAB_tagTabuleiro {
    
    CSA_tppCasa tabuleiro [8] [8] ;
    /* Matriz de ponteiros para casas que define o tabuleiro */
    
} TAB_tpTabuleiro ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
 *
 *  Função: TAB  &Criar tabuleiro
 *  ****/

TAB_tpCondRet TAB_CriarTabuleiro( TAB_tppTabuleiro pTabuleiro )
{

    pTabuleiro = NULL ;
    
    pTabuleiro = ( TAB_tpTabuleiro * ) malloc( sizeof( TAB_tpTabuleiro )) ;
    if ( pTabuleiro == NULL )
    {
        return TAB_CondRetFaltouMemoria ;
    } /* if */
    
    return TAB_CondRetOK ;
    
} /* Fim função: TAB  &Criar tabuleiro */

/***************************************************************************
 *
 *  Função: TAB  &Destruir tabuleiro
 *  ****/

TAB_tpCondRet TAB_DestruirTabuleiro( TAB_tppTabuleiro pTabuleiro )
{
    
    int i , j ;
    
    if ( pTabuleiro == NULL )
    {
        return TAB_tpCondRetNaoExiste ;
    } /* if */
    
    for ( i = 0; i < 8 ; i++ )
    {
        for ( j = 0; j < 8 ; j++ )
        {
            CSA_DestruirCasa( pTabuleiro[i][j] ) ;
        } /* for */
    } /* for */
    
    free( pTabuleiro ) ;
    
    return TAB_CondRetOK ;
    
} /* Fim função: TAB  &Destruir tabuleiro */

/***************************************************************************
 *
 *  Função: TAB  &Inserir peça no tabuleiro
 *  ****/

TAB_tpCondRet TAB_InserirPecaTabuleiro( char coluna,
                                        char linha,
                                        char idPeca,
                                        char corPeca,
                                        TAB_tppTabuleiro pTabuleiro )
{
    
    int i , j ;
    CSA_tpCondRet retModCasa ;
    
    /* Converte a linha e a coluna para inteiros */
    i = linha - '0' ;
    j = coluna - 'A' + 1 ;
    
    retModCasa = CSA_InserirPecaCasa( idPeca, corPeca, pTabuleiro[i][j] ) ;
    
    if ( retModCasa == CSA_CondRetFaltouMemoria )
    {
        return TAB_tpCondRetFaltouMemoria ;
    } /* if */
    
    if ( retModCasa == CSA_CondRetNaoExiste )
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

TAB_tpCondRet TAB_MoverPecaTabuleiro( char colInicial,
                                      char linInicial,
                                      char colFinal,
                                      char linFinal,
                                      TAB_tppTabuleiro pTabuleiro )
{
    
    int i , j ;
    CSA_tpCondRet           retModCasa ;
    VMV_tpCondRet           retModDirMov ;
    VMV_tpMovimentoValido   retModMov ;
    VMV_tppConfigDir        pConfigDir ;
    
    /* Converte a linha e a coluna para inteiros */
    i = linha - '0' ;
    j = coluna - 'A' + 1 ;
    
    retModDirMov = VMV_CriarConfigDir ( &pConfigDir, NULL ) ;
    
    /* Pré-processamento para validação do movimento */
    
    /* Obter peça da casa atual */
    
    /* Verificar validade do movimento */
    retModMov = VMV_ChecarMovimentoPeca ( pConfig,
                                           VMV_tpMovimentoValido* movimento_valido,
                                           char peca,
                                           char cor,
                                           void* casa_atual,
                                           void* casa_destino,
                                           void* casas,
                                           int num_casas,
                                           int num_dimensoes,
                                           int (*array_dimensao)(void* casa),
                                           int* array_sinal,
                                           int (*vazio)(void* casa),
                                           int (*inimigo)(void* casa),
                                           int* cond_especiais,
                                           int num_cond_especiais);
    
    retModDirMov = VMV_DestruirConfigDir ( pConfigDir ) ;

    return TAB_CondRetOK ;
    
} /* Fim função: TAB  &Mover peça no tabuleiro */

/***************************************************************************
 *
 *  Função: TAB  &Retirar peça do tabuleiro
 *  ****/

TAB_tpCondRet TAB_RetirarPecaTabuleiro( char coluna,
                                       char linha,
                                       TAB_tppTabuleiro pTabuleiro )
{
    
    int i , j ;
    CSA_tpCondRet retModCasa ;

    /* Converte a linha e a coluna para inteiros */
    i = linha - '0' ;
    j = coluna - 'A' + 1 ;
    
    retModCasa = CSA_RetirarPecaCasa( pTabuleiro[i][j] ) ;
    
    if ( retModCasa == CSA_CondRetNaoExiste )
    {
        return TAB_CondRetCoordNaoExiste ;
    } /* if */
    
    return TAB_CondRetOK ;
    
} /* Fim função: TAB  &Retirar peça do tabuleiro */

/***************************************************************************
 *
 *  Função: TAB  &Obter peça do tabuleiro
 *  ****/

TAB_tpCondRet TAB_ObterPecaTabuleiro( char coluna,
                                      char linha,
                                      char* pIdPeca,
                                      char* pCorPeca,
                                      TAB_tppTabuleiro pTabuleiro )
{
    
    int i , j ;
    CSA_tpCondRet retModCasa ;
    
    /* Converte a linha e a coluna para inteiros */
    i = linha - '0' ;
    j = coluna - 'A' + 1 ;
    
    retModCasa = CSA_ObterPecaCasa( pIdPeca , pCorPeca , pTabuleiro[i][j] ) ;
    
    if ( retModCasa == CSA_CondRetNaoExiste )
    {
        return TAB_CondRetCoordNaoExiste ;
    } /* if */
    
    return TAB_CondRetOK ;
    
} /* Fim função: TAB  &Obter peça do tabuleiro */

/***************************************************************************
 *
 *  Função: TAB  &Obter lista de ameaçantes de uma peça do tabuleiro
 *  ****/

TAB_tpCondRet TAB_ObterListaAmeacantesTabuleiro( char coluna,
                                                 char linha,
                                                 LIS_tppLista pListaAmeacantes,
                                                 TAB_tppTabuleiro pTabuleiro )
{
    
    int i , j ;
    CSA_tpCondRet retModCasa ;
    
    /* Converte a linha e a coluna para inteiros */
    i = linha - '0' ;
    j = coluna - 'A' + 1 ;
    
    retModCasa = CSA_ObterListaAmeacantesCasa( pListaAmeacantes , pTabuleiro[i][j] ) ;
    
    if ( retModCasa == CSA_CondRetNaoExiste )
    {
        return TAB_CondRetCoordNaoExiste ;
    } /* if */
    
    return TAB_CondRetOK ;
    
} /* Fim função: TAB  &Obter lista de ameaçados de uma peça do tabuleiro */

TAB_tpCondRet TAB_ObterListaAmeacadosTabuleiro( char coluna,
                                                char linha,
                                                LIS_tppLista pListaAmeacados,
                                                TAB_tppTabuleiro pTabuleiro )
{
    
    int i , j ;
    CSA_tpCondRet retModCasa ;
    
    /* Converte a linha e a coluna para inteiros */
    i = linha - '0' ;
    j = coluna - 'A' + 1 ;
    
    retModCasa = CSA_ObterListaAmeacadosCasa( pListaAmeacados , pTabuleiro[i][j] ) ;
    
    if ( retModCasa == CSA_CondRetNaoExiste )
    {
        return TAB_CondRetCoordNaoExiste ;
    } /* if */
    
    return TAB_CondRetOK ;
    
} /* Fim função: TAB  &Obter lista de ameaçados de uma peça do tabuleiro */

/********** Fim do módulo de implementação: TAB  Tabuleiro para jogo de xadrez **********/









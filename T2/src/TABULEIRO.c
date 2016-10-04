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
 *     1       lff   04/out/2016 início desenvolvimento
 *
 ***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   "CASA.H"

#define TABULEIRO_OWN
#include "TABULEIRO.h"
#undef TABULEIRO_OWN

/***********************************************************************
 *
 *  $TC Tipo de dados: TAB Elemento do tabuleiro
 *
 *
 ***********************************************************************/

typedef struct tagElemTabuleiro {
    
    void * pCasa ;
    /* Ponteiro para a casa contida no elemento */
    
} tpElemTabuleiro ;

/***********************************************************************
 *
 *  $TC Tipo de dados: TAB Tabuleiro
 *
 *
 ***********************************************************************/

typedef struct TAB_tagTabuleiro {
    
    void tabuleiro [8] [8] ;
    /* Matriz que define o tabuleiro */
    
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
            
        } /* for */
    } /* for */
    
    free( pTabuleiro ) ;
    
    return TAB_CondRetOK ;
    
} /* Fim função: TAB  &Destruir tabuleiro */

/********** Fim do módulo de implementação: TAB  Tabuleiro para jogo de xadrez **********/









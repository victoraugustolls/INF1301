/***************************************************************************
 *
 *  $MCD Módulo de implementação: JGO  Juiz para jogo de xadrez
 *
 *  Arquivo gerado:              JOGO.C
 *  Letras identificadoras:      JGO
 *
 *  $HA Histórico de evolução:
 *     Versão  Autor    Data     Observações
 *     1       iars   03/nov/2016 inicio desenvolvimento
 *
 ***************************************************************************/

#include   <stdio.h>
#include   "TABULEIRO.H"

#define JOGO_OWN
#include "JOGO.H"
#undef JOGO_OWN

struct JGO_tagJuiz
{
    TAB_tppTabuleiro tabuleiro;
};

JGO_tpCondRet JGO_CriarJuiz( JGO_tppJuiz * pJuiz )
{
    *pJuiz = malloc(sizeof(JGO_tagJuiz));

    if(pJuiz == NULL)
    {
        return JGO_CondRetFaltouMemoria;
    }

    pJuiz->tabuleiro = NULL;

    return JGO_CondRetOK;
}

JGO_tpCondRet JGO_DestruirJuiz( JGO_tppJuiz pJuiz )
{
    JGO_TerminarJogo(pJuiz);

    if(pJuiz == NULL)
    {
        return JGO_CondRetNaoExiste;
    }

    free(pJuiz);

    return JGO_CondRetOK;
}

JGO_tpCondRet JGO_IniciarJogo( JGO_tppJuiz pJuiz, char* pathConfig  )
{
    TAB_tpCondRet condRetTabuleiro;

    if( pJuiz->tabuleiro != NULL)
    {
        return JGO_CondRetJogoJaIniciado;
    }

    condRetTabuleiro = TAB_CriarTabuleiro( &(pJuiz->tabuleiro), pathConfig ) ;

    if(condRetTabuleiro == TAB_CondRetFaltouMemoria)
    {
        pJuiz->tabuleiro = NULL;
        return JGO_CondRetFaltouMemoria;     
    }
    return JGO_CondRetOK;
}

JGO_tpCondRet JGO_TerminarJogo( JGO_tppJuiz pJuiz )
{
    if( pJuiz->tabuleiro == NULL)
    {
        return JGO_CondRetJogoNaoIniciado;        
    }

    TAB_DestruirTabuleiro( pJuiz->pTabuleiro ) ;

    pJuiz->tabuleiro = NULL;

    return JGO_CondRetOK;   
}


JGO_tpCondRet JGO_RealizarJogada( JGO_tppJuiz pJuiz, JGO_tpCorJogador corJogadorAtual,
                                                     JGO_tpEventoOcorrido* eventoOcorrido,
                                                     char linhaCasaAtual,
                                                     char colunaCasaAtual,
                                                     char linhaCasaDestino,
                                                     char colunaCasaDestino ) 
{
    TAB_tpCondRet tabCondRet;
    char peca_atual;
    char cor_atual;
    char peca_destino;
    char cor_destino;
    char charCorOposta;
    LIS_tppLista listaLinhas;
    LIS_tppLista listaColunas;

    tabCondRet = TAB_ObterPecaTabuleiro(    colunaCasaAtual ,
                                            linhaCasaAtual ,
                                            &peca_atual ,
                                            &cor_atual ,
                                            pJuiz->pTabuleiro );

    if(tabCondRet == TAB_CondRetCoordNaoExiste)
    {
        return JGO_CondRetMovInvalido;
    }
    if(corJogadorAtual == JGO_JogadorPreto && cor_atual != 'P' )
    {
        return JGO_CondRetMovInvalido;
    }
    else if(corJogadorAtual == JGO_JogadorBranco && cor_atual != 'B' )
    {
        return JGO_CondRetMovInvalido;
    }

    tabCondRet = TAB_ObterPecaTabuleiro(    colunaCasaDestino ,
                                            linhaCasaDestino ,
                                            &peca_destino ,
                                            &cor_destino ,
                                            pJuiz->pTabuleiro );
    if(tabCondRet == TAB_CondRetCoordNaoExiste)
    {
        return JGO_CondRetMovInvalido;
    }
    
    tabCondRet = TAB_MoverPecaTabuleiro( colunaCasaAtual,
                                         linhaCasaAtual,
                                         colunaCasaDestino,
                                         linhaCasaDestino,
                                         pJuiz->pTabuleiro);

    if(tabCondRet == TAB_CondRetCoordNaoExiste)
    {
        return JGO_CondRetMovInvalido
    }
    else if(tabCondRet == TAB_CondRetMovInvalido)
    {
        return JGO_CondRetMovInvalido;
    }
    else if(tabCondRet == TAB_CondRetNaoExiste)
    {
        return JGO_CondRetNaoExiste;
    }
    else if(tabCondRet == TAB_CondRetFalhaArq)
    {
        return JGO_CondRetFalhaArq;
    }
    else if(tabCondRet == TAB_CondRetFaltouMemoria)
    {
        return JGO_CondRetFaltouMemoria;
    }

    tabCondRet TAB_ObterCasasComPeca( &listaLinhas, &listaColunas, 'R')

    charCorOposta = corJogadorAtual == JGO_JogadorPreto?JGO_JogadorBranco:JGO_JogadorPreto;

    tabCondRet = TAB_MoverPecaTabuleiro( colunaCasaDestino,
                                         linhaCasaDestino,
                                         colunaCasaAtual,
                                         linhaCasaAtual,
                                         pJuiz->pTabuleiro);

    tabCondRet = TAB_InserirPecaTabuleiro(  colunaCasaDestino,
                                            linhaCasaDestino ,
                                            peca_destino ,
                                            cor_destino ,
                                            pJuiz->pTabuleiro  ) ;    

    *eventoOcorrido = JGO_Nenhum;
    return JGO_CondRetOK;
}

/********** Fim do módulo de implementação: JGO  Juiz para jogo de xadrez **********/

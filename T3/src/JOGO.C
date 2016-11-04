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
    TAB_tpCondRet condRetTabuleiro;

    *pJuiz = malloc(sizeof(JGO_tagJuiz));

    if(pJuiz == NULL)
    {
        return JGO_CondRetFaltouMemoria;
    }

    condRetTabuleiro = TAB_CriarTabuleiro( pJuiz->tabuleiro ) ;

    if(condRetTabuleiro == TAB_CondRetFaltouMemoria)
    {
        free(pJuiz);
        return JGO_CondRetFaltouMemoria;     
    }

    return JGO_CondRetOK;
}

JGO_tpCondRet JGO_DestruirJuiz( JGO_tppJuiz pJuiz ) ;

JGO_tpCondRet JGO_IniciarJogo( JGO_tppJuiz pJuiz ) ;

JGO_tpCondRet JGO_TerminarJogo( JGO_tppJuiz pJuiz ) ;


JGO_tpCondRet JGO_RealizarJogada( JGO_tppJuiz pJuiz, JGO_tpCorJogador corJogadorAtual,
                                                     JGO_tpEventoOcorrido* eventoOcorrido,
                                                     char linhaCasaAtual,
                                                     char colunaCasaAtual,
                                                     char linhaCasaDestino,
                                                     char colunaCasaDestino ) ;

#undef JOGO_EXT

/********** Fim do módulo de implementação: JGO  Juiz para jogo de xadrez **********/

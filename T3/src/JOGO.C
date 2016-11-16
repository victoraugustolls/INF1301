/***************************************************************************
 *
 *  $MCD Módulo de implementação: JGO  Juiz para jogo de xadrez
 *
 *  Arquivo gerado:              JOGO.C
 *  Letras identificadoras:      JGO
 *
 *  $HA Histórico de evolução:
 *     Versão  Autor    Data     Observações
 *     2       vas    12/nov/2016 correcao de diversos erros de sintaxe
 *     1       iars   03/nov/2016 inicio desenvolvimento
 *
 ***************************************************************************/

#include   <stdio.h>
#include   <memory.h>
#include   <malloc.h>
#include   "TABULEIRO.H"
#include   "LISTA.H"

#define JOGO_OWN
#include "JOGO.H"
#undef JOGO_OWN

struct JGO_tagJuiz
{
    TAB_tppTabuleiro tabuleiro;
};


int isTabuleiroEmXeque( TAB_tppTabuleiro tabuleiroTemp, JGO_tpCorJogador corJogadorAtual);

JGO_tpCondRet JGO_CriarJuiz( JGO_tppJuiz * pJuiz )
{
    *pJuiz = malloc(sizeof(struct JGO_tagJuiz));

    if(pJuiz == NULL)
    {
        return JGO_CondRetFaltouMemoria;
    }

    (*pJuiz)->tabuleiro = NULL;

    return JGO_CondRetOK;
}

JGO_tpCondRet JGO_DestruirJuiz( JGO_tppJuiz pJuiz )
{
    if(pJuiz == NULL)
    {
        return JGO_CondRetNaoExiste;
    }

    JGO_TerminarJogo(pJuiz);

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

    TAB_DestruirTabuleiro( pJuiz->tabuleiro ) ;

    pJuiz->tabuleiro = NULL;

    return JGO_CondRetOK;   
}

JGO_tpCondRet JGO_GetPrintTabuleiro( JGO_tppJuiz pJuiz, char** print )
{
    TAB_tpCondRet tabCondRet;
    if( pJuiz->tabuleiro == NULL)
    {
        return JGO_CondRetJogoNaoIniciado;        
    }

    tabCondRet = TAB_GetPrintTabuleiro( pJuiz->tabuleiro, print );
    if(tabCondRet == TAB_CondRetFaltouMemoria)
    {
        return JGO_CondRetFaltouMemoria;
    }
    return JGO_CondRetOK;
}

int DEBUG = 0;
JGO_tpCondRet JGO_RealizarJogada( JGO_tppJuiz pJuiz, JGO_tpCorJogador corJogadorAtual,
                                                     JGO_tpEventoOcorrido* eventoOcorrido,
                                                     char linhaCasaAtual,
                                                     char colunaCasaAtual,
                                                     char linhaCasaDestino,
                                                     char colunaCasaDestino ) 
{
    TAB_tppTabuleiro tabuleiroTemp;
    TAB_tpCondRet tabCondRet;
    char peca_atual;
    char cor_atual;
    char peca_destino;
    char cor_destino;

    char la, ca, ld, cd;

    JGO_tpCorJogador corJogadorOposta;
    char charCorCorrente;
    char charCorOposta;

    corJogadorOposta = corJogadorAtual==JGO_JogadorPreto?JGO_JogadorBranco:JGO_JogadorPreto;
    charCorCorrente = corJogadorAtual == JGO_JogadorPreto?'P':'B';
    charCorOposta = corJogadorAtual == JGO_JogadorPreto?'B':'P';

    if( pJuiz->tabuleiro == NULL)
    {
        return JGO_CondRetJogoNaoIniciado;        
    }


    tabCondRet = TAB_ObterPecaTabuleiro(    colunaCasaAtual ,
                                            linhaCasaAtual ,
                                            &peca_atual ,
                                            &cor_atual ,
                                            pJuiz->tabuleiro );

    if(tabCondRet == TAB_CondRetCoordNaoExiste)
    {
        printf("Motivo: coordenada casa atual nao existe\n");
        return JGO_CondRetMovInvalido;
    }
    if(corJogadorAtual == JGO_JogadorPreto && cor_atual != 'P' )
    {
        printf("Motivo: cor da peca diferente da cor do jogador passada\n");
        return JGO_CondRetMovInvalido;
    }
    else if(corJogadorAtual == JGO_JogadorBranco && cor_atual != 'B' )
    {
        printf("Motivo: cor da peca diferente da cor do jogador passada\n");
        return JGO_CondRetMovInvalido;
    }

    tabCondRet = TAB_ObterPecaTabuleiro(    colunaCasaDestino ,
                                            linhaCasaDestino ,
                                            &peca_destino ,
                                            &cor_destino ,
                                            pJuiz->tabuleiro );
    if(tabCondRet == TAB_CondRetCoordNaoExiste)
    {
        printf("Motivo: coordenada casa destino nao existe\n");
        return JGO_CondRetMovInvalido;
    }

    tabCondRet = TAB_CopiarTabuleiro(&tabuleiroTemp, pJuiz->tabuleiro);
    if(tabCondRet == TAB_CondRetFaltouMemoria)
    {
        return JGO_CondRetFaltouMemoria;
    }
    
    tabCondRet = TAB_MoverPecaTabuleiro( colunaCasaAtual,
                                         linhaCasaAtual,
                                         colunaCasaDestino,
                                         linhaCasaDestino,
                                         tabuleiroTemp );

    if(tabCondRet == TAB_CondRetCoordNaoExiste)
    {
        printf("Motivo: coordenada nao existe\n");
        return JGO_CondRetMovInvalido;
    }
    else if(tabCondRet == TAB_CondRetMovInvalido)
    {
        printf("Motivo: o movimento dado nao corresponde ao movimento da peca\n");
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

    //--------------------------------------------------
    // Testar se o novo movimento e ivalido pois deixou seu rei em xeque

    DEBUG = 1;
    if(isTabuleiroEmXeque(tabuleiroTemp, corJogadorAtual))
    {
        DEBUG=0;
        printf("Motivo: o movimento deixaria seu rei em xeque\n");
        return JGO_CondRetMovInvalido;
    }
    DEBUG = 0;
    TAB_DestruirTabuleiro(tabuleiroTemp);
    tabCondRet = TAB_MoverPecaTabuleiro( colunaCasaAtual,
                                         linhaCasaAtual,
                                         colunaCasaDestino,
                                         linhaCasaDestino,
                                         pJuiz->tabuleiro );   

    //--------------------------------------------------
    // Caso nao tenha ocorrido um Xeque

    if(!isTabuleiroEmXeque(pJuiz->tabuleiro, corJogadorOposta))
    {
        *eventoOcorrido = JGO_Nenhum;
        return JGO_CondRetOK;
    }

    //--------------------------------------------------
    // A partir daqui devemos descobrir se ocorreu um Xeque ou Xeque Mate
    //--------------------------------------------------

    for(la='1';la<='8';la++)
    {
        for(ca='A';ca<='H';ca++)
        {

            tabCondRet = TAB_ObterPecaTabuleiro(    ca ,
                                                    la ,
                                                    &peca_atual ,
                                                    &cor_atual ,
                                                    pJuiz->tabuleiro ); 
            if(cor_atual == charCorOposta)
            { 
                for(ld='1';ld<='8';ld++)
                {
                    for(cd='A';cd<='H';cd++)
                    {  
                        tabCondRet = TAB_CopiarTabuleiro(&tabuleiroTemp, pJuiz->tabuleiro);
                        if(tabCondRet == TAB_CondRetFaltouMemoria)
                        {
                            return JGO_CondRetFaltouMemoria;
                        }

                        tabCondRet = TAB_MoverPecaTabuleiro( ca,
                                                             la,
                                                             cd,
                                                             ld,
                                                             tabuleiroTemp );
                        if(tabCondRet == TAB_CondRetNaoExiste)
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

                        if(tabCondRet == TAB_CondRetOK)
                        {
                            if(!isTabuleiroEmXeque(tabuleiroTemp, corJogadorOposta))
                            {
                                TAB_DestruirTabuleiro(tabuleiroTemp);
                                *eventoOcorrido = JGO_Xeque;
                                return JGO_CondRetOK;
                            }    
                        }

                        TAB_DestruirTabuleiro(tabuleiroTemp);

                    }
                }
            }
        }
    }

    *eventoOcorrido = JGO_XequeMate;
    return JGO_CondRetOK;

}

int isTabuleiroEmXeque( TAB_tppTabuleiro tabuleiro, JGO_tpCorJogador corJogador)
{
    TAB_tpCondRet tabCondRet;
    char charCorCorrente = corJogador == JGO_JogadorPreto?'P':'B';
    char charCorOposta = corJogador == JGO_JogadorPreto?'B':'P';
    LIS_tpCondRet listaRet;
    LIS_tppLista listaLinhas;
    LIS_tppLista listaColunas;
    LIS_tppLista pListaAmeacantesLinhas;
    LIS_tppLista pListaAmeacantesColunas;
    char* linha;
    char* coluna;
    char peca;
    char cor;

    tabCondRet = TAB_ObterCasasComPeca(     &listaLinhas, 
                                            &listaColunas,
                                            'R', 
                                            charCorCorrente, 
                                            tabuleiro );

    listaRet = LIS_AvancarElementoCorrente(listaLinhas , -64) ;
    listaRet = LIS_AvancarElementoCorrente(listaColunas , -64) ;
    if(listaRet != LIS_CondRetListaVazia)
    {
        while(listaRet != LIS_CondRetNoCorrenteUlt)
        {
            listaRet = LIS_ObterValor( listaLinhas , (void **) &linha ) ;
            listaRet = LIS_ObterValor( listaColunas , (void **) &coluna ) ;

            tabCondRet = TAB_ObterListaAmeacantesTabuleiro(  *coluna ,
                                                             *linha ,
                                                             &pListaAmeacantesLinhas ,
                                                             &pListaAmeacantesColunas ,
                                                             tabuleiro );

            listaRet = LIS_AvancarElementoCorrente(pListaAmeacantesLinhas , -64) ;
            listaRet = LIS_AvancarElementoCorrente(pListaAmeacantesColunas , -64) ;
            if(listaRet != LIS_CondRetListaVazia)
            {
                while(listaRet != LIS_CondRetNoCorrenteUlt)
                {
                    listaRet = LIS_ObterValor( pListaAmeacantesLinhas , (void **) &linha ) ;
                    listaRet = LIS_ObterValor( pListaAmeacantesColunas , (void **) &coluna ) ;

                    tabCondRet = TAB_ObterPecaTabuleiro(    *coluna ,
                                                            *linha ,
                                                            &peca ,
                                                            &cor ,
                                                            tabuleiro );

                    if(cor == charCorOposta)
                    {
                        if(DEBUG)
                        {
                            printf("A peca %c%c na posicao %c%c esta ameacando o rei.\n",peca,cor,*coluna,*linha);
                        }
                        return 1;
                    }

                    listaRet = LIS_AvancarElementoCorrente(pListaAmeacantesLinhas , 1) ;
                    listaRet = LIS_AvancarElementoCorrente(pListaAmeacantesColunas , 1) ;
                }   
            }


            listaRet = LIS_DestruirLista(pListaAmeacantesLinhas);
            listaRet = LIS_DestruirLista(pListaAmeacantesColunas);
            listaRet = LIS_AvancarElementoCorrente(listaLinhas , 1) ;
            listaRet = LIS_AvancarElementoCorrente(listaColunas , 1) ;
        }   
    }
    return 0;
}

/********** Fim do módulo de implementação: JGO  Juiz para jogo de xadrez **********/

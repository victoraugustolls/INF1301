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
#include   "LISTA.H"

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
    char charCorCorrente;
    char charCorOposta;
    int isListaVazia;
    TAB_tpCondRet listaRet;
    LIS_tppLista listaLinhas;
    LIS_tppLista listaColunas;
    LIS_tppLista pListaAmeacantesLinhas;
    LIS_tppLista pListaAmeacantesColunas;
    LIS_tppLista pListaAmeacadosLinhas;
    LIS_tppLista pListaAmeacadosColunas;
    int existeXeque;
    char* linha;
    char* coluna;
    char* linhaAmeacante;
    char* colunaAmeacante;
    char l;
    char c;
    char corAmeacante;
    char pecaAmeacante;
    int existeAmeacanteInimigo;

    if( pJuiz->tabuleiro == NULL)
    {
        return JGO_CondRetJogoNaoIniciado;        
    }


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

    charCorCorrente = corJogadorAtual == JGO_JogadorPreto?'P':'B';
    charCorOposta = corJogadorAtual == JGO_JogadorPreto?'B':'P';

    tabCondRet = TAB_ObterCasasComPeca(     &listaLinhas, 
                                            &listaColunas,
                                            'R', 
                                            charCorCorrente, 
                                            pJuiz->pTabuleiro);

    retLista = LIS_AvancarElementoCorrente(*listaLinhas , -64) ;
    retLista = LIS_AvancarElementoCorrente(*listaColunas , -64) ;
    if(retLista != LIS_CondRetListaVazia)
    {
        while(retLista != LIS_CondRetNoCorrenteUlt)
        {
            retLista = LIS_ObterValor( listaLinhas , (void **) &linha ) ;
            retLista = LIS_ObterValor( listaColunas , (void **) &coluna ) ;

            tabCondRet = TAB_ObterListaAmeacantesTabuleiro(  *coluna ,
                                                             *linha ,
                                                             &pListaAmeacantesLinhas ,
                                                             &pListaAmeacantesColunas ,
                                                             pJuiz->pTabuleiro );

            listaRet = LIS_VerificaVazia(pListaAmeacantesLinhas, &isListaVazia);

            if(isListaVazia==0)
            {
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

                listaRet = LIS_DestruirLista(pListaAmeacantesLinhas);
                listaRet = LIS_DestruirLista(pListaAmeacantesColunas);

                return JGO_CondRetMovInvalido;               
            }           

            listaRet = LIS_DestruirLista(pListaAmeacantesLinhas);
            listaRet = LIS_DestruirLista(pListaAmeacantesColunas);
            retLista = LIS_AvancarElementoCorrente(*listaLinhas , 1) ;
            retLista = LIS_AvancarElementoCorrente(*listaColunas , 1) ;
        }   
    }

    tabCondRet = TAB_ObterCasasComPeca(     &listaLinhas, 
                                            &listaColunas,
                                            'R', 
                                            charCorOposta, 
                                            pJuiz->pTabuleiro);

    retLista = LIS_AvancarElementoCorrente(*listaLinhas , -64) ;
    retLista = LIS_AvancarElementoCorrente(*listaColunas , -64) ;

    if(retLista == LIS_CondRetListaVazia)
    {
        *eventoOcorrido = JGO_Nenhum;
        return JGO_CondRetOK;
    }

    while(retLista != LIS_CondRetNoCorrenteUlt)
    {
        retLista = LIS_ObterValor( listaLinhas , (void **) &linha ) ;
        retLista = LIS_ObterValor( listaColunas , (void **) &coluna ) ;

        tabCondRet = TAB_ObterListaAmeacantesTabuleiro(  *coluna ,
                                                         *linha ,
                                                         &pListaAmeacantesLinhas ,
                                                         &pListaAmeacantesColunas ,
                                                         pJuiz->pTabuleiro );

        listaRet = LIS_VerificaVazia(pListaAmeacantesLinhas, &isListaVazia);

        if(isListaVazia!=0)
        {
            existeXeque = 1;             
        }           

        listaRet = LIS_DestruirLista(pListaAmeacantesLinhas);
        listaRet = LIS_DestruirLista(pListaAmeacantesColunas);
        retLista = LIS_AvancarElementoCorrente(*listaLinhas , 1) ;
        retLista = LIS_AvancarElementoCorrente(*listaColunas , 1) ;
    }

    if(existeXeque == 0)
    {
        *eventoOcorrido = JGO_Nenhum;
        return JGO_CondRetOK;
    }

    retLista = LIS_AvancarElementoCorrente(*listaLinhas , -64) ;
    retLista = LIS_AvancarElementoCorrente(*listaColunas , -64) ;

    while(retLista != LIS_CondRetNoCorrenteUlt)
    {
        retLista = LIS_ObterValor( listaLinhas , (void **) &linha ) ;
        retLista = LIS_ObterValor( listaColunas , (void **) &coluna ) ;

        for(l='1'; l<='8'; l++)
        {
            for(c='A'; c<='H'; H++)
            {
                tabCondRet = TAB_ObterPecaTabuleiro(    c ,
                                                        l ,
                                                        &peca_destino ,
                                                        &cor_destino ,
                                                        pJuiz->pTabuleiro );
                
                tabCondRet = TAB_MoverPecaTabuleiro( *coluna,
                                                     *linha,
                                                     c,
                                                     l,
                                                     pJuiz->pTabuleiro);

                else if(tabCondRet == TAB_CondRetFalhaArq)
                {
                    return JGO_CondRetFalhaArq;
                }
                else if(tabCondRet == TAB_CondRetFaltouMemoria)
                {
                    return JGO_CondRetFaltouMemoria;
                }
                else if(tabCondRet == TAB_CondRetMovInvalido)
                {
                    continue;
                }

                tabCondRet = TAB_ObterListaAmeacantesTabuleiro(  c ,
                                                                 l ,
                                                                 &pListaAmeacantesLinhas ,
                                                                 &pListaAmeacantesColunas ,
                                                                 pJuiz->pTabuleiro );

                retLista = LIS_AvancarElementoCorrente(*pListaAmeacantesLinhas , -64) ;
                retLista = LIS_AvancarElementoCorrente(*pListaAmeacantesColunas , -64) ;

                if(retLista == LIS_CondRetListaVazia)
                {
                    tabCondRet = TAB_MoverPecaTabuleiro( c,
                                                         l,
                                                         *coluna,
                                                         *linha,
                                                         pJuiz->pTabuleiro);

                    tabCondRet = TAB_InserirPecaTabuleiro(  c,
                                                            l ,
                                                            peca_destino ,
                                                            cor_destino ,
                                                            pJuiz->pTabuleiro  ) ;  
                    listaRet = LIS_DestruirLista(pListaAmeacantesLinhas);
                    listaRet = LIS_DestruirLista(pListaAmeacantesColunas);  

                    *eventoOcorrido = JGO_Xeque;
                    return JGO_CondRetOK;  
                }

                existeAmeacanteInimigo = 0;
                while(retLista != LIS_CondRetNoCorrenteUlt)
                {
                    retLista = LIS_ObterValor( pListaAmeacantesLinhas , (void **) &linhaAmeacante ) ;
                    retLista = LIS_ObterValor( pListaAmeacantesColunas , (void **) &colunaAmeacante ) ;


                    tabCondRet = TAB_ObterPecaTabuleiro( colunaAmeacante,
                                                          linhaAmeacante,
                                                          &pecaAmeacante,
                                                          &corAmeacante,
                                                          pJuiz->pTabuleiro );

                    if(corAmeacante == charCorCorrente)
                    {
                        existeAmeacanteInimigo = 1;
                        break;
                    }

                    retLista = LIS_AvancarElementoCorrente(*pListaAmeacantesLinhas , 1) ;
                    retLista = LIS_AvancarElementoCorrente(*pListaAmeacantesColunas , 1) ;
                }

                if(!existeAmeacanteInimigo == 0)
                {
                    tabCondRet = TAB_MoverPecaTabuleiro( c,
                                                         l,
                                                         *coluna,
                                                         *linha,
                                                         pJuiz->pTabuleiro);

                    tabCondRet = TAB_InserirPecaTabuleiro(  c,
                                                            l ,
                                                            peca_destino ,
                                                            cor_destino ,
                                                            pJuiz->pTabuleiro  ) ;  
                    listaRet = LIS_DestruirLista(pListaAmeacantesLinhas);
                    listaRet = LIS_DestruirLista(pListaAmeacantesColunas);  

                    *eventoOcorrido = JGO_Xeque;
                    return JGO_CondRetOK;    
                }                

                tabCondRet = TAB_MoverPecaTabuleiro( c,
                                                         l,
                                                         *coluna,
                                                         *linha,
                                                         pJuiz->pTabuleiro);

                tabCondRet = TAB_InserirPecaTabuleiro(  c,
                                                        l ,
                                                        peca_destino ,
                                                        cor_destino ,
                                                        pJuiz->pTabuleiro  ) ; 

                listaRet = LIS_DestruirLista(pListaAmeacantesLinhas);
                listaRet = LIS_DestruirLista(pListaAmeacantesColunas);               
            }
        }

        retLista = LIS_AvancarElementoCorrente(*listaLinhas , 1) ;
        retLista = LIS_AvancarElementoCorrente(*listaColunas , 1) ;
    }

    *eventoOcorrido = JGO_XequeMate;
    return JGO_CondRetOK;      

}

/********** Fim do módulo de implementação: JGO  Juiz para jogo de xadrez **********/

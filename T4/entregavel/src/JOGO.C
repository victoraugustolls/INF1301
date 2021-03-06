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
#include   <string.h>
#include   "TABULEIRO.H"
#include   "LISTA.H"

#define JOGO_OWN
#include "JOGO.H"
#undef JOGO_OWN

/***** Protótipos das funções encapuladas no módulo *****/

static int isTabuleiroEmXeque( TAB_tppTabuleiro tabuleiroTemp, JGO_tpCorJogador corJogadorAtual);

/***********************************************************************
 *
 *  $TC Tipo de dados: JGO Descritor do jogo
 *
 *
 ***********************************************************************/

struct JGO_tagJuiz
{
    TAB_tppTabuleiro tabuleiro;
};

/***************************************************************************
 *
 *  Função: JGO  &Criar juiz
 *  ****/

JGO_tpCondRet JGO_CriarJuiz( JGO_tppJuiz * pJuiz )
{
    *pJuiz = malloc(sizeof(struct JGO_tagJuiz));

    if(pJuiz == NULL)
    {
        return JGO_CondRetFaltouMemoria;
    }

    (*pJuiz)->tabuleiro = NULL;

    return JGO_CondRetOK;
} /* Fim função: JGO  &Criar juiz */

/***************************************************************************
 *
 *  Função: JGO  &Destruir juiz
 *  ****/

JGO_tpCondRet JGO_DestruirJuiz( JGO_tppJuiz pJuiz )
{
    if(pJuiz == NULL)
    {
        return JGO_CondRetNaoExiste;
    }

    JGO_TerminarJogo(pJuiz);

    free(pJuiz);

    return JGO_CondRetOK;
} /* Fim função: JGO  &Destruir juiz */

/***************************************************************************
 *
 *  Função: JGO  &Iniciar jogo
 *  ****/

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
} /* Fim função: JGO  &Iniciar jogo */

/***************************************************************************
 *
 *  Função: JGO  &Terminar jogo
 *  ****/

JGO_tpCondRet JGO_TerminarJogo( JGO_tppJuiz pJuiz )
{
    if( pJuiz->tabuleiro == NULL)
    {
        return JGO_CondRetJogoNaoIniciado;        
    }

    TAB_DestruirTabuleiro( pJuiz->tabuleiro ) ;

    pJuiz->tabuleiro = NULL;

    return JGO_CondRetOK;   
} /* Fim função: JGO  &Terminar jogo */

/***************************************************************************
 *
 *  Função: JGO  &Pegar print do tabuleiro
 *  ****/

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
} /* Fim função: JGO  &Pegar print do tabuleiro */

/***************************************************************************
 *
 *  Função: JGO  &Pegar print da lista de ameacantes
 *  ****/

JGO_tpCondRet JGO_GetPrintListaAmeacantes( JGO_tppJuiz pJuiz, char linha, char coluna, char** print )
{
    TAB_tpCondRet tabCondRet;
    LIS_tpCondRet listaRet;

    LIS_tppLista pListaAmeacantesLinhas;
    LIS_tppLista pListaAmeacantesColunas;

    char* linha_obtida;
    char* coluna_obtida;

    char stringcat[3] = "A1";

    *print = (char*) malloc(sizeof(char)*100*3);
    if(*print == NULL)
    {
        return JGO_CondRetFaltouMemoria;
    }
    (*print)[0] = '\0';

    if( pJuiz->tabuleiro == NULL)
    {
        return JGO_CondRetJogoNaoIniciado;        
    }

    tabCondRet = TAB_ObterListaAmeacantesTabuleiro( coluna ,
                                                     linha ,
                                                     &pListaAmeacantesLinhas ,
                                                     &pListaAmeacantesColunas ,
                                                     pJuiz->tabuleiro );
    if(tabCondRet == TAB_CondRetNaoExiste)
    {
        return JGO_CondRetNaoExiste;
    }
    else if(tabCondRet == TAB_CondRetCoordNaoExiste)
    {
        return JGO_CondRetMovInvalido;
    }

    listaRet = LIS_AvancarElementoCorrente(pListaAmeacantesLinhas , -64) ;
    listaRet = LIS_AvancarElementoCorrente(pListaAmeacantesColunas , -64) ;
    if(listaRet != LIS_CondRetListaVazia)
    {
        while(listaRet != LIS_CondRetNoCorrenteUlt)
        {
            listaRet = LIS_ObterValor( pListaAmeacantesLinhas , (void **) &linha_obtida ) ;
            listaRet = LIS_ObterValor( pListaAmeacantesColunas , (void **) &coluna_obtida ) ;

            stringcat[0] = *coluna_obtida;
            stringcat[1] = *linha_obtida;

            strcat(*print,stringcat);
            strcat(*print," ");


            listaRet = LIS_AvancarElementoCorrente(pListaAmeacantesLinhas , 1) ;
            listaRet = LIS_AvancarElementoCorrente(pListaAmeacantesColunas , 1) ;
        }   
    }

    return JGO_CondRetOK;
} /* Fim função: JGO  &Pegar print da lista de ameacantes */

/***************************************************************************
 *
 *  Função: JGO  &Pegar print da lista de ameacados
 *  ****/

JGO_tpCondRet JGO_GetPrintListaAmeacados( JGO_tppJuiz pJuiz, char linha, char coluna, char** print )
{
    TAB_tpCondRet tabCondRet;
    LIS_tpCondRet listaRet;

    LIS_tppLista pListaAmeacadosLinhas;
    LIS_tppLista pListaAmeacadosColunas;

    char* linha_obtida;
    char* coluna_obtida;

    char stringcat[3] = "A1";

    *print = (char*) malloc(sizeof(char)*100*3);
    if(*print == NULL)
    {
        return JGO_CondRetFaltouMemoria;
    }
    (*print)[0] = '\0';

    if( pJuiz->tabuleiro == NULL)
    {
        return JGO_CondRetJogoNaoIniciado;        
    }

    tabCondRet = TAB_ObterListaAmeacadosTabuleiro( coluna ,
                                                     linha ,
                                                     &pListaAmeacadosLinhas ,
                                                     &pListaAmeacadosColunas ,
                                                     pJuiz->tabuleiro );
    if(tabCondRet == TAB_CondRetNaoExiste)
    {
        return JGO_CondRetNaoExiste;
    }
    else if(tabCondRet == TAB_CondRetCoordNaoExiste)
    {
        return JGO_CondRetMovInvalido;
    }

    listaRet = LIS_AvancarElementoCorrente(pListaAmeacadosLinhas , -64) ;
    listaRet = LIS_AvancarElementoCorrente(pListaAmeacadosColunas , -64) ;
    if(listaRet != LIS_CondRetListaVazia)
    {
        while(listaRet != LIS_CondRetNoCorrenteUlt)
        {
            listaRet = LIS_ObterValor( pListaAmeacadosLinhas , (void **) &linha_obtida ) ;
            listaRet = LIS_ObterValor( pListaAmeacadosColunas , (void **) &coluna_obtida ) ;

            stringcat[0] = *coluna_obtida;
            stringcat[1] = *linha_obtida;

            strcat(*print,stringcat);
            strcat(*print," ");

            listaRet = LIS_AvancarElementoCorrente(pListaAmeacadosLinhas , 1) ;
            listaRet = LIS_AvancarElementoCorrente(pListaAmeacadosColunas , 1) ;
        }   
    }

    return JGO_CondRetOK;
} /* Fim função: JGO  &Pegar print da lista de ameacados */

int DEBUG = 0;

/***************************************************************************
 *
 *  Função: JGO  &Realizar jogada
 *  ****/

JGO_tpCondRet JGO_RealizarJogada( JGO_tppJuiz pJuiz, JGO_tpCorJogador corJogadorAtual,
                                                     JGO_tpEventoOcorrido* eventoOcorrido,
                                                     char linhaCasaAtual,
                                                     char colunaCasaAtual,
                                                     char linhaCasaDestino,
                                                     char colunaCasaDestino,
                                                     char** mensagem ) 
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

    *mensagem = (char*) malloc(sizeof(char)*300);
    if(*mensagem == NULL)
    {
        return JGO_CondRetFaltouMemoria;
    }
    (*mensagem)[0] = '\0';

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
        strcpy(*mensagem,"Movimento Invalido: coordenada casa atual nao existe\n");
        return JGO_CondRetMovInvalido;
    }
    if(corJogadorAtual == JGO_JogadorPreto && cor_atual != 'P' )
    {
        strcpy(*mensagem,"Movimento Invalido: cor da peca diferente da cor do jogador passada\n");
        return JGO_CondRetMovInvalido;
    }
    else if(corJogadorAtual == JGO_JogadorBranco && cor_atual != 'B' )
    {
        strcpy(*mensagem,"Movimento Invalido: cor da peca diferente da cor do jogador passada\n");
        return JGO_CondRetMovInvalido;
    }

    tabCondRet = TAB_ObterPecaTabuleiro(    colunaCasaDestino ,
                                            linhaCasaDestino ,
                                            &peca_destino ,
                                            &cor_destino ,
                                            pJuiz->tabuleiro );
    if(tabCondRet == TAB_CondRetCoordNaoExiste)
    {
        strcpy(*mensagem,"Movimento Invalido: coordenada casa destino nao existe\n");
        return JGO_CondRetMovInvalido;
    }

    tabCondRet = TAB_CopiarTabuleiro(&tabuleiroTemp, pJuiz->tabuleiro);
    if(tabCondRet == TAB_CondRetFaltouMemoria)
    {
        free(*mensagem);
        return JGO_CondRetFaltouMemoria;
    }
    
    tabCondRet = TAB_MoverPecaTabuleiro( colunaCasaAtual,
                                         linhaCasaAtual,
                                         colunaCasaDestino,
                                         linhaCasaDestino,
                                         tabuleiroTemp );

    if(tabCondRet == TAB_CondRetCoordNaoExiste)
    {
        strcpy(*mensagem,"Movimento Invalido: coordenada nao existe\n");
        return JGO_CondRetMovInvalido;
    }
    else if(tabCondRet == TAB_CondRetMovInvalido)
    {
        strcpy(*mensagem,"Movimento Invalido: o movimento dado nao corresponde ao movimento da peca\n");
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
        free(*mensagem);
        return JGO_CondRetFaltouMemoria;
    }

    //--------------------------------------------------
    // Testar se o novo movimento e ivalido pois deixou seu rei em xeque

    if(isTabuleiroEmXeque(tabuleiroTemp, corJogadorAtual))
    {
        strcpy(*mensagem,"Movimento Invalido: o movimento deixaria seu rei em xeque\n");
        return JGO_CondRetMovInvalido;
    }
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
                            free(*mensagem);
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
                            free(*mensagem);
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

} /* Fim função: JGO  &Realizar jogada */

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
 *
 *  $FC Função: JGO -Verifica xeque
 *
 ***********************************************************************/

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
} /* Fim função: JGO  &Verifica xeque */

/********** Fim do módulo de implementação: JGO  Juiz para jogo de xadrez **********/

/***************************************************************************
 *  $MCI Módulo de implementação: PRNC Módulo principal
 *
 *  Arquivo gerado:              PRINCIPAL
 *
 *  Nome da base de software:    Jogo de Xadrez
 *  Arquivo da base de software: C:\T3\bin\PRINCIPAL.EXE
 *
 *  Projeto: INF 1301 / 1628 AutomatizaÁ„o dos testes de mÛdulos C
 *  Gestor:  LES/DI/PUC-Rio
 *  Autores: lff
 *
 *  $HA Histórico de evolução:
 *     Versão  Autor    Data     ObservaÁıes
 *     1       lff   12/nov/2016 início desenvolvimento
 *
 *  $ED Descrição do módulo
 *     Este módulo contém o programa principal do jogo de xadrez.
 *
 ***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   "JOGO.H"

static const char INICIAR_PARTIDA  [ ] = "iniciar"  ;
static const char JOGAR            [ ] = "jogar"    ;
static const char TERMINAR_PARTIDA [ ] = "terminar" ;
static const char INSERIR_PECA     [ ] = "inserir"  ;
static const char SAIR_JOGO        [ ] = "sair"     ;

char Tabuleiro[8][8][2] ;

/***********************************************************************
 *
 *  $TC Tipo de dados: PRNC Opções do Jogo
 *
 *
 *  $ED Descrição do tipo
 *     Opções que o usuário pode escolher durante a execução do jogo.
 *
 ***********************************************************************/

typedef struct
{
    char nome[20] ;
    /* Nome do Jogador */
    
    JGO_tpCorJogador cor ;
    /* Cor do Jogador */
     
} Jogador ;

/***** Protótipos das funções encapuladas no arquivo *****/

static void ImprimirTabuleiro( ) ;
static void InicializarTabuleiro( ) ;

int main( void ) {
    
    char LinhaInicial , ColunaInicial ;
    char LinhaFinal , ColunaFinal ;

    JGO_tppJuiz Juiz ;
    JGO_tpEventoOcorrido EventoJogada = -1 ;
    JGO_tpCondRet CondRet ;
    
    char OpcaoEscolhida[100] ;
    Jogador JogadorDaVez , JogadorBranco , JogadorPreto ;
    
    JogadorBranco.cor = JGO_JogadorBranco ;
    JogadorPreto.cor = JGO_JogadorPreto ;
    
    /* Exibir logo do programa */
    
    printf( "\n      Jogo de Xadrez\n" ) ;
    printf( "\n---------------------------------------------" ) ;
    
    CondRet = JGO_CriarJuiz( &Juiz ) ;
    if ( CondRet == JGO_CondRetFaltouMemoria )
    {
        printf( "\n      Memoria insuficiente para rodar o jogo\n" ) ;
        return 0 ;
    }
    
    do
    {
        /* Inicializar contexto */

        printf( "\nEscolha uma opcao:\n" ) ;
        printf( "   - Comecar nova partida ( iniciar );\n" ) ;
        printf( "   - Inserir nova peca ( inserir ).)\n" ) ;
        printf( "   - Sair do jogo ( sair ).)\n" ) ;
        printf( "\nDigite a opcao desejada:\n" ) ;
        scanf( "%s" , OpcaoEscolhida );
        
        /* Iniciar partida */
        if ( ! strcmp( OpcaoEscolhida , INICIAR_PARTIDA ) )
        {
            printf( "\n      Digite o nome do quem jogara com as pecas brancas:\n" ) ;
            scanf( "%s" , JogadorBranco.nome );
            printf( "\n      Digite o nome do quem jogara com as pecas pretas:\n" ) ;
            scanf( "%s" , JogadorPreto.nome );
            
            //InicializarTabuleiro( ) ;
            //ImprimirTabuleiro( ) ;
            
            printf( "\n      Jogo iniciado\n" ) ;
            
            CondRet = JGO_IniciarJogo( Juiz , "..\\pecas\\teste_jogo\\config.conf" ) ;
            
            if ( CondRet == JGO_CondRetJogoJaIniciado ) {
                return 0 ;
            }/* if */
            
            JogadorDaVez = JogadorBranco ;
            strcpy( OpcaoEscolhida , JOGAR ) ;
            
            while ( ( EventoJogada != JGO_XequeMate ) &&
                    ( ! strcmp( OpcaoEscolhida , JOGAR ) ) )
            {
                printf( "\n      Jogador da vez: %s\n" , JogadorDaVez.nome ) ;
                
                printf( "\n      Jogar (jogar) ou terminar (terminar) a partida?\n" ) ;
                scanf( "%s" , OpcaoEscolhida ) ;
                
                if ( ! strcmp( OpcaoEscolhida , JOGAR ) )
                {
                    printf( "\n      Casa Inicial:" ) ;
                    printf( "\n      Linha:" ) ;
                    scanf( " %c" , &LinhaInicial ) ;
                    printf( "\n      Coluna:" ) ;
                    scanf( " %c" , &ColunaInicial ) ;
                    
                    printf( "\n      Casa Destino:" ) ;
                    printf( "\n      Linha:" ) ;
                    scanf( " %c" , &LinhaFinal ) ;
                    printf( "\n      Coluna:" ) ;
                    scanf( " %c" , &ColunaFinal ) ;
                    
                    CondRet = JGO_RealizarJogada( Juiz ,
                                                 JogadorDaVez.cor ,
                                                 &EventoJogada ,
                                                 LinhaInicial ,
                                                 ColunaInicial ,
                                                 LinhaFinal ,
                                                 ColunaFinal ) ;
                    
                    if ( CondRet == JGO_CondRetFaltouMemoria )
                    {
                        printf( "\n      Memoria insuficiente para rodar o jogo\n" ) ;
                        printf( "\n      O jogo sera encerrado\n" ) ;
                        return 0 ;
                    }
                    else if ( CondRet == JGO_CondRetFalhaArq )
                    {
                        printf( "\n      Erro inesperado ao abrir arquivos internos do jogo\n" ) ;
                        printf( "\n      O jogo sera encerrado\n" ) ;
                        return 0 ;
                    }
                    else if ( CondRet == JGO_CondRetMovInvalido )
                    {
                        printf( "\n      Jogada invalida\n" ) ;
                    }
                    else
                    {
                        /* Atualizar o tabuleiro impresso */
                        
                        if ( EventoJogada == JGO_XequeMate )
                        {
                            printf( "\n      Jogador %s deixou seu oponente em Xeque-Mate\n" , JogadorDaVez.nome ) ;
                            printf( "\n      %s ganhou, parabens!\n" , JogadorDaVez.nome ) ;
                            
                            strcpy( OpcaoEscolhida , TERMINAR_PARTIDA ) ;
                        } /* if */
                        
                        if ( JogadorDaVez.cor == JGO_JogadorBranco )
                        {
                            JogadorDaVez = JogadorPreto ;
                        }
                        else
                        {
                            JogadorDaVez = JogadorBranco ;
                        } /* if */
                        
                        if ( EventoJogada == JGO_Xeque ) {
                            printf( "\n      Jogador %s esta em Xeque\n" , JogadorDaVez.nome ) ;
                        } /* if */
                    } /* if */
                    
                } /* if */
                
                else if ( ! strcmp( OpcaoEscolhida , TERMINAR_PARTIDA ) )
                {
                    CondRet = JGO_TerminarJogo( Juiz ) ;
                    
                    if ( CondRet == JGO_CondRetJogoNaoIniciado )
                    {
                        printf( "\n      Nenhum jogo foi iniciado\n" ) ;
                    }
                    else
                    {
                        printf( "\n      Jogo terminado\n" ) ;
                    }/* if */
                }
                
                else
                {
                    printf( "\n      Opacao invalida\n" ) ;
                    
                }/* if */
                
            }/* while */
        } /* fim ativa: Iniciar partida */
        
        /* Terminar partida */
        else if ( ! strcmp( OpcaoEscolhida , TERMINAR_PARTIDA ) )
        {
            CondRet = JGO_TerminarJogo( Juiz ) ;
            
            if ( CondRet == JGO_CondRetJogoNaoIniciado )
            {
                printf( "\n      Nenhum jogo foi iniciado\n" ) ;
            }
            else
            {
                printf( "\n      Jogo terminado\n" ) ;
            }/* if */
        } /* fim ativa: Terminar partida */
        
        /* Inserir peça */
        else if ( ! strcmp( OpcaoEscolhida , INSERIR_PECA ) )
        {
            printf( "\n      VICTOR VAI TOMAR NO CU\n" ) ;

        } /* fim ativa: Inserir peça */
        
        else
        {
            printf( "\n      Opacao invalida\n" ) ;
        } /* if */
        
    } while ( strcmp( OpcaoEscolhida , SAIR_JOGO ) ); /* do-while */
    
    printf( "\n      O jogo esta sendo encerrado." ) ;
    printf( "\n      Obrigado por jogar com a gente!\n" ) ;

    JGO_TerminarJogo( Juiz ) ;
    
    JGO_DestruirJuiz( Juiz ) ;
    
    return 0 ;
}

static void ImprimirTabuleiro( )
{
    int i , j ;
    
    printf( "\n       A   B   C   D   E   F   G   H\n" ) ;
    
    for ( i = 0 ; i < 8 ; i++ ) {
        printf( "   %d   " , i + 1 ) ;
        for ( j = 0 ; j < 8 ; j++ ) {
            printf( "%s  " , Tabuleiro[i][j] ) ;
        } /* for */
        printf( "\n" ) ;
    } /* for */
    
    printf( "\n" ) ;
}

static void InicializarTabuleiro( )
{
    int i , j ;
    
    strcpy( Tabuleiro[0][0] , "TP" ) ;
    strcpy( Tabuleiro[0][1] , "CP" ) ;
    strcpy( Tabuleiro[0][2] , "BP" ) ;
    strcpy( Tabuleiro[0][3] , "DP" ) ;
    strcpy( Tabuleiro[0][4] , "RP" ) ;
    strcpy( Tabuleiro[0][5] , "BP" ) ;
    strcpy( Tabuleiro[0][6] , "CP" ) ;
    strcpy( Tabuleiro[0][7] , "TP" ) ;
    
    for ( i = 0 ; i < 8 ; i++ ) {
        strcpy( Tabuleiro[1][i] , "PP" ) ;
    } /* for */
    
    for ( i = 2 ; i < 6 ; i++ ) {
        for ( j = 0 ; j < 8 ; j++ ) {
            strcpy( Tabuleiro[i][j] , ".." ) ;
        } /* for */
    } /* for */
    
    for ( i = 0 ; i < 8 ; i++ ) {
        strcpy( Tabuleiro[6][i] , "PB" ) ;
    } /* for */
    
    strcpy( Tabuleiro[7][0] , "TB" ) ;
    strcpy( Tabuleiro[7][1] , "CB" ) ;
    strcpy( Tabuleiro[7][2] , "BB" ) ;
    strcpy( Tabuleiro[7][3] , "DB" ) ;
    strcpy( Tabuleiro[7][4] , "RB" ) ;
    strcpy( Tabuleiro[7][5] , "BB" ) ;
    strcpy( Tabuleiro[7][6] , "CB" ) ;
    strcpy( Tabuleiro[7][7] , "TB" ) ;
}

/********** Fim do dódulo de implementação: PRNC Módulo principal **********/

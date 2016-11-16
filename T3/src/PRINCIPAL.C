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
static const char TERMINAR_PARTIDA [ ] = "FIM" ;
static const char INSERIR_PECA     [ ] = "inserir"  ;
static const char SAIR_JOGO        [ ] = "FIM"     ;

char Tabuleiro[8][8][2] ;
JGO_tppJuiz Juiz ;

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
static void AtualizarTabuleiro( char LinhaInicial ,
								char ColunaInicial ,
								char LinhaFinal ,
								char ColunaFinal  ) ;

int main( void ) {
	
	char LinhaInicial , ColunaInicial ;
	char LinhaFinal , ColunaFinal ;

	JGO_tpEventoOcorrido EventoJogada = -1 ;
	JGO_tpCondRet CondRet ;
	
	int OpcaoEscolhida ;
	char OpcaoJogada[100] = "jogar" ;
	Jogador JogadorDaVez , JogadorBranco , JogadorPreto ;
	
	JogadorBranco.cor = JGO_JogadorBranco ;
	JogadorPreto.cor = JGO_JogadorPreto ;
	
	/* Exibir logo do programa */
	
	printf( "--------------------\n" ) ;
	printf( "JOGO DE XADREZ\n" ) ;
	printf( "--------------------\n" ) ;
	
	CondRet = JGO_CriarJuiz( &Juiz ) ;
	if ( CondRet == JGO_CondRetFaltouMemoria )
	{
		printf( "\n\tMemoria insuficiente para rodar o jogo\n" ) ;
		return 0 ;
	}
	
	do
	{
		/* Inicializar contexto */
		printf( "Digite a opcao desejada:\n" ) ;
		printf( "(0) - Comecar nova partida\n" ) ;
		printf( "(1) - Inserir nova peca\n" ) ;
		printf( "(2) - Sair do jogo\n" ) ;
		printf( "--------------------\n" ) ;
		printf( "Opcao >> " ) ;
		scanf( " %d" , &OpcaoEscolhida );
		printf( "--------------------\n" ) ;
		
		/* Iniciar partida */
		if ( OpcaoEscolhida == 0 )
		{
			printf( "Digite o nome do quem jogara com as pecas brancas:\n" ) ;
			printf( "Nome >> " ) ;
			scanf( " %s" , JogadorBranco.nome ) ;
			printf( "Digite o nome do quem jogara com as pecas pretas:\n" ) ;
			printf( "Nome >> " ) ;
			scanf( " %s" , JogadorPreto.nome ) ;
			printf( "--------------------\n" ) ;
			printf("JOGADORES\n") ;
			printf( "--------------------\n" ) ;
			printf("Jogador branco: %s\n", JogadorBranco.nome);
			printf("Jogador preto: %s\n", JogadorPreto.nome);
			printf( "--------------------\n" ) ;
			
			// InicializarTabuleiro( ) ;
			//ImprimirTabuleiro( ) ;
			
			printf( "JOGO INICIADO\n" ) ;
			printf( "--------------------\n" ) ;
			
			CondRet = JGO_IniciarJogo( Juiz , "..\\pecas\\default\\config.conf" ) ;
			
			if ( CondRet == JGO_CondRetJogoJaIniciado ) {
				return 0 ;
			}/* if */

			ImprimirTabuleiro( ) ;
			
			JogadorDaVez = JogadorBranco ;
			
			while ( ( EventoJogada != JGO_XequeMate ) &&
					!( strcmp( OpcaoJogada , JOGAR ) ) )
			{
				printf( "Jogador da vez: %s\n" , JogadorDaVez.nome ) ;
				printf( "--------------------\n" ) ;

				printf( "Digite a opcao desejada:\n" ) ;
				printf( "(JOGAR) - Comecar nova partida\n" ) ;
				printf( " (FIM)  - Sair do jogo\n" ) ;
				printf( "--------------------\n" ) ;
				printf( "Opcao >> " ) ;
				scanf( " %s" , OpcaoJogada ) ;
				
				if ( ! strcmp( OpcaoJogada , JOGAR ) )
				{
					printf( "--------------------\n" ) ;
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
							
							OpcaoEscolhida = 2 ;
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
				
				else if ( ! strcmp( OpcaoJogada , TERMINAR_PARTIDA ) )
				{
					printf( "--------------------\n" ) ;
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
					printf( "Opcao invalida!\n" ) ;
					printf( "--------------------\n" ) ;
					strcpy( OpcaoJogada , JOGAR ) ;
					
				}/* if */
				
			}/* while */
		} /* fim ativa: Iniciar partida */
		
		/* Terminar partida */
		else if ( OpcaoEscolhida == 2 )
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
		else if ( OpcaoEscolhida == 1 )
		{
			printf( "Visite o LEIAME.txt do programa e \n" ) ;
			printf( "--------------------\n" ) ;

		} /* fim ativa: Inserir peça */
		
		else
		{
			printf( "Opcao invalida\n" ) ;
		} /* if */
		
	} while ( OpcaoEscolhida != 2 ); /* do-while */
	
	printf( "O jogo esta sendo encerrado.\n" ) ;
	printf( "Obrigado por jogar com a gente!\n" ) ;

	JGO_TerminarJogo( Juiz ) ;
	
	JGO_DestruirJuiz( Juiz ) ;
	
	return 0 ;
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


static void ImprimirTabuleiro(  )
{
	char * estadoTabuleiro ;
	JGO_GetPrintTabuleiro( Juiz , &estadoTabuleiro ) ;
	printf( "%s\n" , estadoTabuleiro ) ;
	free( estadoTabuleiro ) ;
}

static void AtualizarTabuleiro( char LinhaInicial ,
								char ColunaInicial ,
								char LinhaFinal ,
								char ColunaFinal  )
{
	
}

/********** Fim do dódulo de implementação: PRNC Módulo principal **********/

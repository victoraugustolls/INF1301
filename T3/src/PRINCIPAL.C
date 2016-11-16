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

static const char JOGAR            [ ] = "JOGAR" ;
static const char TERMINAR_PARTIDA [ ] = "FIM"   ;

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
static void toUpperCase( char *f ) ;
static void flush_in(  ) ;

int main( void ) {
	
	char LinhaInicial , ColunaInicial ;
	char LinhaFinal , ColunaFinal ;

	JGO_tpEventoOcorrido EventoJogada = -1 ;
	JGO_tpCondRet CondRet ;
	
	int OpcaoEscolhida ;
	char OpcaoJogada[100] = "JOGAR" ;
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
				printf( "Jogador da vez:\n" ) ;
				printf("Nome: %s\n" , JogadorDaVez.nome ) ;
				printf("Cor: %s\n", JogadorDaVez.cor ? "Branco" : "Preto" ) ;
				printf( "--------------------\n" ) ;
				printf( "Digite a opcao desejada:\n" ) ;
				printf( "(JOGAR) - Realizar jogada\n" ) ;
				printf( " (FIM)  - Sair do jogo\n" ) ;
				printf( "--------------------\n" ) ;
				printf( "Opcao >> " ) ;
				scanf( " %s" , OpcaoJogada ) ;
				toUpperCase( OpcaoJogada ) ;
				
				if ( ! strcmp( OpcaoJogada , JOGAR ) )
				{
					printf( "--------------------\n" ) ;
					printf("Digite a casa inicial (Coluna / Linha , ex. H3):\n");
					printf( "Casa >> " ) ;
					scanf( " %c%c" , &ColunaInicial , &LinhaInicial ) ;
					toUpperCase( &ColunaInicial ) ;
					flush_in( ) ;
					printf("%c%c\n", ColunaInicial, LinhaInicial);
					printf("Digite a casa destino (Coluna / Linha , ex. H3):\n");
					printf( "Casa >> " ) ;
					scanf( " %c%c" , &ColunaFinal , &LinhaFinal ) ;
					toUpperCase( &ColunaFinal ) ;
					flush_in( ) ;
					printf("%c%c\n", ColunaFinal, LinhaFinal);
					
					CondRet = JGO_RealizarJogada( Juiz ,
												 JogadorDaVez.cor ,
												 &EventoJogada ,
												 LinhaInicial ,
												 ColunaInicial ,
												 LinhaFinal ,
												 ColunaFinal ) ;
					
					if ( CondRet == JGO_CondRetFaltouMemoria )
					{
						printf( "Memoria insuficiente para rodar o jogo\n" ) ;
						printf( "O jogo sera encerrado\n" ) ;
						return 0 ;
					}
					else if ( CondRet == JGO_CondRetFalhaArq )
					{
						printf( "Erro inesperado ao abrir arquivos internos do jogo\n" ) ;
						printf( "O jogo sera encerrado\n" ) ;
						return 0 ;
					}
					else if ( CondRet == JGO_CondRetMovInvalido )
					{
						printf( "Jogada invalida\n" ) ;
					}
					else
					{
						/* Atualizar o tabuleiro impresso */

						ImprimirTabuleiro( ) ;
						
						if ( EventoJogada == JGO_XequeMate )
						{
							printf( "Jogador %s deixou seu oponente em Xeque-Mate\n" , JogadorDaVez.nome ) ;
							printf( "%s ganhou, parabens!\n" , JogadorDaVez.nome ) ;
							
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
							printf( "Jogador %s esta em Xeque\n" , JogadorDaVez.nome ) ;
						} /* if */
					} /* if */
					
				} /* if */
				
				else if ( ! strcmp( OpcaoJogada , TERMINAR_PARTIDA ) )
				{
					printf( "--------------------\n" ) ;
					CondRet = JGO_TerminarJogo( Juiz ) ;
					
					if ( CondRet == JGO_CondRetJogoNaoIniciado )
					{
						printf( "Nenhum jogo foi iniciado\n" ) ;
					}
					else
					{
						printf( "Jogo terminado\n" ) ;
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
				printf( "Nenhum jogo foi iniciado\n" ) ;
			}
			else
			{
				printf( "Jogo terminado\n" ) ;
			}/* if */
		} /* fim ativa: Terminar partida */
		
		/* Inserir peça */
		else if ( OpcaoEscolhida == 1 )
		{
			printf( "Visite o LEIAME.txt do programa e siga suas instrucoes!\n" ) ;
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

void ImprimirTabuleiro(  )
{
	char * estadoTabuleiro ;
	JGO_GetPrintTabuleiro( Juiz , &estadoTabuleiro ) ;
	printf( "%s\n" , estadoTabuleiro ) ;
	free( estadoTabuleiro ) ;
}

void toUpperCase( char *f )
{
	while( *f != '\0' )
	{
		*f = *f >= 'a' && *f <= 'z' ? *f + 'A' - 'a' : *f ;
		f++ ;
	}/* while */
}

void flush_in(  ) {
    int ch ;
    do {
        ch = fgetc(stdin) ;
    } 
    while (ch != EOF && ch != '\n') ; /* do-while */
}

/********** Fim do dódulo de implementação: PRNC Módulo principal **********/

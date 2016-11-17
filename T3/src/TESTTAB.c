/***************************************************************************
 *  $MCI Módulo de implementação: TTAB Teste tabuleiro
 *
 *  Arquivo gerado:              TESTTAB.c
 *  Letras identificadoras:      TTAB
 *
 *  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
 *  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
 *
 *  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
 *  Gestor:  LES/DI/PUC-Rio
 *  Autores: lff, iars, vas
 *
 *  $HA Histórico de evolução:
 *     Versão  Autor    Data     Observações
 *       3       vas   17/nov/2016 adição dos testes para copia e print do tabuleiro
 *		 2       vas   13/nov/2016 mudaças para nova interface do tabuleiro
 *       1       lff   05/out/2016 início desenvolvimento
 *
 ***************************************************************************/

#include	<string.h>
#include	<stdio.h>
#include	<malloc.h>

#include	"TST_Espc.h"

#include	"Generico.h"
#include	"LerParm.h"

#include	"LISTA.H"
#include	"CASA.H"
#include	"TABULEIRO.H"


static const char CRIAR_TABULEIRO_CMD            [ ] = "=criarTabuleiro"        ;
static const char DESTRUIR_TABULEIRO_CMD         [ ] = "=destruirTabuleiro"     ;
static const char INSERIR_PECA_CMD               [ ] = "=inserirPeca"           ;
static const char MOVER_PECA_CMD                 [ ] = "=moverPeca"             ;
static const char RETIRAR_PECA_CMD               [ ] = "=retirarPeca"           ;
static const char OBTER_CASA_CMD                 [ ] = "=obterCasa"             ;
static const char OBTER_PECA_CMD                 [ ] = "=obterPeca"             ;
static const char COPIA_TAB_CMD                  [ ] = "=copiaTab"              ;
static const char PRINT_TAB_CMD                  [ ] = "=printTab"              ;
static const char OBTER_AMEACANTES_CMD           [ ] = "=obterListaAmeacantes"  ;
static const char OBTER_AMEACADOS_CMD            [ ] = "=obterListaAmeacados"   ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_TABULEIRO 10
#define DIM_VT_CASA 2

TAB_tppTabuleiro pTabuleiro ;
TAB_tppTabuleiro vtTabuleiros[ DIM_VT_TABULEIRO ] ;

/***** Protótipos das funções encapuladas no módulo *****/

static void DestruirValor( void * pDado ) ;

static int CompararValor( void * pDado_1 , void * pDado_2 ) ;

static int IgualValor( void * pDado_1 , void * pDado_2 ) ;

static int ValidarInxTabuleiro( int inxTab , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
 *
 *  $FC Função: TTAB &Testar tabuleiro
 *
 *  $ED Descrição da função
 *     Podem ser criados até 10 tabuleiros, identificados pelos índices 0 a 10
 *
 *     Comandos disponíveis:
 *
 *     =criarTabuleiro           inx    condRetorno
 *	   =destruirTabuleiro        inx    condRetorno
 *     =inserirPeca              inx    colunaInicio linhaInicio colunaFim          linhaFim       condRetorno
 *     =moverPeca                inx    colunaInicio linhaInicio colunaFim          linhaFim       condRetorno
 *     =retirarPeca              inx    coluna       linha       condRetorno
 *     =obterCasa                inx    coluna       linha       nome               cor            condRetorno
 *     =obterPeca                inx    coluna       linha       nome               cor            condRetorno
 *     =copiaTab                 inx    inx2         condRetorno
 *     =printTab                 inx    condRetorno
 *     =obterListaAmeacantes     inx    coluna       linha       conteudoColuna     conteudoLinha  condRetorno
 *     =obterListaAmeacados      inx    coluna       linha       conteudoColuna     conteudoLinha  condRetorno
 *
 ***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	
	int inxTab     = -1 ,
		inxTab2    = -1 , 
		numLidos   = -1 ,
		CondRetEsp = -1 ;
	
	TST_tpCondRet CondRet ;
	
	char charParm1 ,
		 charParm2 ,
		 charParm3 ,
		 charParm4 ;

	char listaCharLinhas[100];
	char listaCharColunas[100];

	char * nomeObtido ;
	char * corObtida  ;
	char * linhaObtida ;
	char * colunaObtida ;
	char * print ;
	char * print2 ;

	char printVazio[ 400 ] = " |A  B  C  D  E  F  G  H  \n--------------------------\n1|VV VV VV VV VV VV VV VV \n2|VV VV VV VV VV VV VV VV \n3|VV VV VV VV VV VV VV VV \n4|VV VV VV VV VV VV VV VV \n5|VV VV VV VV VV VV VV VV \n6|VV VV VV VV VV VV VV VV \n7|VV VV VV VV VV VV VV VV \n8|VV VV VV VV VV VV VV VV \n" ;

	int size_string;

	int i;

	LIS_tppLista listaLinhas ;
	LIS_tppLista listaColunas ;
	
	/* Testar CriarTabuleiro */
	
	if ( strcmp( ComandoTeste , CRIAR_TABULEIRO_CMD ) == 0 )
	{
		numLidos = LER_LerParametros( "ii" , &inxTab ,
									&CondRetEsp ) ;
		
		if ( ( numLidos != 2 )
			|| ( ! ValidarInxTabuleiro( inxTab , VAZIO )))
		{
			return TST_CondRetParm ;
		} /* if */
		
		CondRet = TAB_CriarTabuleiro( &vtTabuleiros[ inxTab ] , "..\\pecas\\teste_tabuleiro\\config.conf" ) ;
		
		return TST_CompararInt( CondRetEsp , CondRet ,
								"Condicao de retorno errada ao criar tabuleiro." ) ;
		
	} /* fim ativa: Testar CriarTabuleiro */
	
	/* Testar DestruirTabuleiro */
	
	else if ( strcmp( ComandoTeste , DESTRUIR_TABULEIRO_CMD ) == 0 )
	{

		numLidos = LER_LerParametros( "ii" , &inxTab ,
									&CondRetEsp ) ;
		
		if ( ( numLidos != 2 ) )
		{
			return TST_CondRetParm ;
		} /* if */
		
		CondRet = TAB_DestruirTabuleiro ( vtTabuleiros[ inxTab ] ) ;

		vtTabuleiros[ inxTab ] = NULL ;
		
		return TST_CompararInt( CondRetEsp , CondRet ,
								"Condicao de retorno errada ao destruir tabuleiro." ) ;
		
	} /* fim ativa: Testar DestruirTabuleiro */
	
	/* Testar InserirPecaTabuleiro */

	else if ( strcmp( ComandoTeste , INSERIR_PECA_CMD ) == 0 )
	{

		numLidos = LER_LerParametros( "icccci" , &inxTab ,
									&charParm1 , &charParm2 ,
									&charParm3 , &charParm4 ,
									&CondRetEsp ) ;

		if ( ( numLidos != 6 ) )
		{
			return TST_CondRetParm ;
		} /* if */

		CondRet = TAB_InserirPecaTabuleiro ( charParm1 , charParm2 ,
											charParm3 , charParm4 ,
											vtTabuleiros[ inxTab ] ) ;

		return TST_CompararInt( CondRetEsp , CondRet ,
								"Condicao de retorno errada ao inserir peca no tabuleiro." ) ;

	} /* fim ativa: Testar InserirPecaTabuleiro */
	
	/* Testar MoverPecaTabuleiro */
	
	else if ( strcmp( ComandoTeste , MOVER_PECA_CMD ) == 0 )
	{

		numLidos = LER_LerParametros( "icccci" , &inxTab ,
									&charParm1 , &charParm2 ,
									&charParm3 , &charParm4 ,
									&CondRetEsp ) ;

		if ( ( numLidos != 6 ) )
		{
			return TST_CondRetParm ;
		} /* if */

		CondRet = TAB_MoverPecaTabuleiro ( charParm1 , charParm2 ,
											charParm3 , charParm4 ,
											vtTabuleiros[ inxTab ] ) ;

		return TST_CompararInt( CondRetEsp , CondRet ,
								"Condicao de retorno errada ao mover peca no tabuleiro." ) ;

	} /* fim ativa: Testar MoverPecaTabuleiro */

	/* Testar RetirarPecaTabuleiro */
	
	else if ( strcmp( ComandoTeste , RETIRAR_PECA_CMD ) == 0 )
	{

		numLidos = LER_LerParametros( "icci" , &inxTab ,
									&charParm1 , &charParm2 ,
									&CondRetEsp ) ;
		
		if ( ( numLidos != 4 ) )
		{
			return TST_CondRetParm ;
		} /* if */
		
		CondRet = TAB_RetirarPecaTabuleiro ( charParm1 , charParm2 ,
											vtTabuleiros[ inxTab ] ) ;
		
		return TST_CompararInt( CondRetEsp , CondRet ,
								"Condicao de retorno errada ao retirar peca no tabuleiro." ) ;
	
	} /* fim ativa: Testar RetirarPecaTabuleiro */
	
	/* Testar ObterCasaTabuleiro */
	
	else if ( strcmp( ComandoTeste , OBTER_CASA_CMD ) == 0 )
	{

		CSA_tppCasa casaObtida ;
		CSA_tpCondRet retCasa ;

		numLidos = LER_LerParametros( "icccci" , &inxTab ,
									&charParm1 , &charParm2 ,
									&charParm3 , &charParm4 ,
									&CondRetEsp ) ;
		
		if ( ( numLidos != 6 ) )
		{
			return TST_CondRetParm ;
		} /* if */

		CondRet = TAB_ObterCasaTabuleiro( charParm1 , charParm2 ,
										&casaObtida , vtTabuleiros[ inxTab ] ) ;

		if ( CondRet )
		{
			return TST_CompararInt( CondRetEsp , CondRet ,
									"Condicao de retorno errada ao obter casa." ) ;
		}

		nomeObtido = ( char * ) malloc( sizeof( char ) ) ;
		corObtida = ( char * ) malloc( sizeof( char ) ) ;

		retCasa = CSA_ObterPecaCasa( nomeObtido , corObtida , casaObtida ) ;

		if ( retCasa )
		{
			free( nomeObtido ) ;
			free( corObtida ) ;
			return TST_NotificarFalha( "A casa não existe." ) ;
		}

		if ( charParm3 != ( *nomeObtido ) )
		{
			free( corObtida ) ;
			return TST_CompararChar( charParm3 , *nomeObtido ,
									"Nome da peca retornada nao corresponde ao nome esperado." ) ;
		}
		else if ( charParm4 != ( *corObtida ) )
		{
			free( nomeObtido ) ;
			return TST_CompararChar( charParm4 , *corObtida ,
									"Cor da peca retornada nao corresponde a cor esperada." ) ;
		} /* if */

		free( nomeObtido ) ;
		free( corObtida ) ;
		
		return TST_CompararInt( CondRetEsp , CondRet ,
								"Condicao de retorno errada ao obter casa." ) ;
	
	} /* fim ativa: Testar ObterCasaTabuleiro */
	
	/* Testar ObterPecaTabuleiro */
	
	else if ( strcmp( ComandoTeste , OBTER_PECA_CMD ) == 0 )
	{

		numLidos = LER_LerParametros( "icccci" , &inxTab ,
									&charParm1 , &charParm2 ,
									&charParm3 , &charParm4 ,
									&CondRetEsp ) ;
		
		if ( ( numLidos != 6 ) )
		{
			return TST_CondRetParm ;
		} /* if */
		
		nomeObtido = ( char * ) malloc( sizeof( char ) ) ;
		corObtida = ( char * ) malloc( sizeof( char ) ) ;
		
		CondRet = TAB_ObterPecaTabuleiro( charParm1 , charParm2 ,
										nomeObtido , corObtida ,
										vtTabuleiros[ inxTab ] ) ;

		if ( CondRet )
		{
			free( nomeObtido ) ;
			free( corObtida ) ;
			return TST_CompararInt( CondRetEsp , CondRet ,
									"Condicao de retorno errada ao obter peca." ) ;
		}
		
		if ( charParm3 != ( *nomeObtido ) )
		{
			free( corObtida ) ;
			return TST_CompararChar( charParm3 , *nomeObtido ,
									"Nome da peca retornada nao corresponde ao nome esperado." ) ;
		}
		else if ( charParm4 != ( *corObtida ) )
		{
			free( nomeObtido ) ;
			return TST_CompararChar( charParm4 , *corObtida ,
									"Cor da peca retornada nao corresponde a cor esperada." ) ;
		} /* if */

		free( nomeObtido ) ;
		free( corObtida ) ;
		
		return TST_CompararInt( CondRetEsp , CondRet ,
								"Condicao de retorno errada ao obter peca." ) ;
		
	} /* fim ativa: Testar ObterPecaTabuleiro */

	/* Testar PrintTabuleiro */
	
	else if ( strcmp( ComandoTeste , PRINT_TAB_CMD ) == 0 )
	{

		numLidos = LER_LerParametros( "ii" , &inxTab ,
									&CondRetEsp ) ;
		
		if ( ( numLidos != 2 ) 
			|| ( ! ValidarInxTabuleiro( inxTab , NAO_VAZIO )))
		{
			return TST_CondRetParm ;
		} /* if */
		
		CondRet = TAB_GetPrintTabuleiro( vtTabuleiros[ inxTab ] , &print  ) ;

		if ( CondRet != TAB_CondRetOK )
		{
			return TST_CompararInt( CondRetEsp , CondRet ,
								"Condicao de retorno errada ao obter print do tabuleiro." ) ;
		} /* if */

		return TST_CompararString( printVazio , print , 
									"Print recebido errado ao obter print do tabuleiro." ) ;
		
	} /* fim ativa: Testar PrintTabuleiro */

	/* Testar CopiaTabuleiro */
	
	else if ( strcmp( ComandoTeste , COPIA_TAB_CMD ) == 0 )
	{

		numLidos = LER_LerParametros( "iii" , &inxTab ,
									&inxTab2 , &CondRetEsp ) ;
		
		if ( ( numLidos != 3 )
			|| ( ! ValidarInxTabuleiro( inxTab , NAO_VAZIO )))
		{
			return TST_CondRetParm ;
		} /* if */
		
		CondRet = TAB_CopiarTabuleiro( &vtTabuleiros[ inxTab2 ] , vtTabuleiros[ inxTab ] ) ;

		if ( CondRet != TAB_CondRetOK )
		{
			return TST_CompararInt( CondRetEsp , CondRet ,
								"Condicao de retorno errada ao copiar tabuleiro." ) ;
		} /* if */

		CondRet = TAB_GetPrintTabuleiro( vtTabuleiros[ inxTab ] , &print ) ;

		if ( CondRet != TAB_CondRetOK )
		{
			return TST_CompararInt( CondRetEsp , CondRet ,
								"Condicao de retorno errada ao obter print do tabuleiro original." ) ;
		} /* if */

		CondRet = TAB_GetPrintTabuleiro( vtTabuleiros[ inxTab2 ] , &print2 ) ;

		if ( CondRet != TAB_CondRetOK )
		{
			return TST_CompararInt( CondRetEsp , CondRet ,
								"Condicao de retorno errada ao obter print do tabuleiro copia." ) ;
		} /* if */

		return TST_CompararString( print , print2 , 
									"Print recebido errado ao copiar tabuleiro." ) ;
		
	} /* fim ativa: Testar CopiaTabuleiro */
	
	/* Testar ObterListaAmeacantesTabuleiro */
	
	else if ( strcmp( ComandoTeste , OBTER_AMEACANTES_CMD ) == 0 )
	{
		LIS_tpCondRet retLista1 ;
		LIS_tpCondRet retLista2 ;
		int found ;

		numLidos = LER_LerParametros( "iccssi" , &inxTab ,
									&charParm1 , &charParm2 ,
									listaCharColunas , listaCharLinhas,
									&CondRetEsp ) ;
		
		if ( ( numLidos != 6 ) )
		{
			return TST_CondRetParm ;
		} /* if */
		
		CondRet = TAB_ObterListaAmeacantesTabuleiro ( charParm1 , charParm2 ,
													&listaLinhas , &listaColunas ,
													vtTabuleiros[ inxTab ] ) ;

		if( CondRet != CondRetEsp )
		{
			return TST_NotificarFalha( "Condicao de retorno errada." ) ;	
		} /* if */

		size_string = strlen( listaCharLinhas ) ;

		retLista1 = LIS_AvancarElementoCorrente( listaLinhas, -100 ) ;
		retLista2 = LIS_AvancarElementoCorrente( listaColunas, -100 ) ;

		if( retLista1 != retLista2 )
		{
			return TST_NotificarFalha( "Erro nas assertivas de TAB_ObterListaAmeacantesTabuleiro." ) ;	
		} /* if */

		if( retLista1 == LIS_CondRetListaVazia )
		{
			if( size_string == 0 )
			{
				return TST_CondRetOK ;
			}
			else
			{
				return TST_NotificarFalha( "As listas nao sao equivalentes." ) ;	
			} /* if */
		} /* if */

		while( retLista1 != LIS_CondRetNoCorrenteUlt )
		{
			retLista1 = LIS_ObterValor( listaLinhas, &linhaObtida ) ;
			retLista2 = LIS_ObterValor( listaColunas, &colunaObtida ) ;

			if( retLista1 != retLista2 )
			{
				return TST_NotificarFalha( "Erro nas assertivas de TAB_ObterListaAmeacantesTabuleiro." ) ;	
			} /* if */

			found = 0 ;

			for( i = 0 ; i < size_string ; i++ )
			{
				if( listaCharLinhas[ i ] == *linhaObtida && listaCharColunas[ i ] == *colunaObtida )
				{
					found = 1 ;
					break ;
				} /* if */
			} /* for */

			if( found == 0 )
			{
				return TST_NotificarFalha( "As listas nao sao equivalentes." ) ;				
			} /* if */

			retLista1 = LIS_AvancarElementoCorrente( listaLinhas, 1 ) ;
			retLista2 = LIS_AvancarElementoCorrente( listaColunas, 1 ) ;

			if( retLista1 != retLista2 )
			{
				return TST_NotificarFalha( "Erro nas assertivas de TAB_ObterListaAmeacantesTabuleiro." ) ;	
			} /* if */
		}

		for( i = 0 ; i < size_string ; i++ )
		{
			found = 0 ;
			retLista1 = LIS_AvancarElementoCorrente( listaLinhas, -100 ) ;
			retLista2 = LIS_AvancarElementoCorrente( listaColunas, -100 ) ;

			while(retLista1 != LIS_CondRetNoCorrenteUlt)
			{
				retLista1 = LIS_ObterValor( listaLinhas, &linhaObtida ) ;
				retLista2 = LIS_ObterValor( listaColunas, &colunaObtida ) ;

				if( listaCharLinhas[ i ] == *linhaObtida && listaCharColunas[ i ] == *colunaObtida )
				{
					found = 1 ;
					break ;
				} /* if */

				retLista1 = LIS_AvancarElementoCorrente( listaLinhas, 1 ) ;
				retLista2 = LIS_AvancarElementoCorrente( listaColunas, 1 ) ;
			} /* while */

			if( found == 0 )
			{
				return TST_NotificarFalha( "As listas nao sao equivalentes." ) ;				
			} /* if */
		} /* for */

		return TST_CondRetOK;		

	} /* fim ativa: Testar ObterListaAmeacantesTabuleiro */

	/* Testar ObterListaAmeacadosTabuleiro */
	
	else if ( strcmp( ComandoTeste , OBTER_AMEACADOS_CMD ) == 0 )
	{
		
		LIS_tpCondRet retLista1 ;
		LIS_tpCondRet retLista2 ;
		int found ;

		numLidos = LER_LerParametros( "iccssi" , &inxTab ,
									&charParm1 , &charParm2 ,
									listaCharColunas , listaCharLinhas,
									&CondRetEsp ) ;
		
		if ( ( numLidos != 6 ) )
		{
			return TST_CondRetParm ;
		} /* if */
		
		CondRet = TAB_ObterListaAmeacadosTabuleiro ( charParm1 , charParm2 ,
													&listaLinhas , &listaColunas ,
													vtTabuleiros[ inxTab ] ) ;

		if( CondRet != CondRetEsp )
		{
			return TST_NotificarFalha( "Condicao de retorno errada." ) ;	
		} /* if */

		size_string = strlen( listaCharLinhas ) ;

		retLista1 = LIS_AvancarElementoCorrente( listaLinhas, -100 ) ;
		retLista2 = LIS_AvancarElementoCorrente( listaColunas, -100 ) ;

		if( retLista1 != retLista2 )
		{
			return TST_NotificarFalha( "Erro nas assertivas de TAB_ObterListaAmeacantesTabuleiro." ) ;	
		} /* if */

		if(retLista1 == LIS_CondRetListaVazia)
		{
			if(size_string==0)
			{
				return TST_CondRetOK;
			}
			else
			{
				return TST_NotificarFalha( "As listas nao sao equivalentes." ) ;	
			} /* if */
		} /* if */

		while(retLista1 != LIS_CondRetNoCorrenteUlt)
		{
			retLista1 = LIS_ObterValor( listaLinhas, &linhaObtida) ;
			retLista2 = LIS_ObterValor( listaColunas, &colunaObtida ) ;

			if( retLista1 != retLista2 )
			{
				return TST_NotificarFalha( "Erro nas assertivas de TAB_ObterListaAmeacantesTabuleiro." ) ;	
			} /* if */

			found = 0 ;

			for( i = 0 ; i < size_string ; i++ )
			{
				if( listaCharLinhas[ i ] == *linhaObtida && listaCharColunas[ i ] == *colunaObtida )
				{
					found = 1 ;
					break ;
				} /* if */
			} /* for */

			if( found == 0 )
			{
				return TST_NotificarFalha( "As listas nao sao equivalentes." ) ;				
			} /* if */

			retLista1 = LIS_AvancarElementoCorrente( listaLinhas, 1 ) ;
			retLista2 = LIS_AvancarElementoCorrente( listaColunas, 1 ) ;

			if( retLista1 != retLista2 )
			{
				return TST_NotificarFalha( "Erro nas assertivas de TAB_ObterListaAmeacantesTabuleiro." ) ;	
			} /* if */

		} /* while */

		for( i = 0 ; i < size_string ; i++ )
		{
			found = 0;
			retLista1 = LIS_AvancarElementoCorrente( listaLinhas, -100 ) ;
			retLista2 = LIS_AvancarElementoCorrente( listaColunas, -100 ) ;

			while(retLista1 != LIS_CondRetNoCorrenteUlt)
			{
				retLista1 = LIS_ObterValor( listaLinhas, &linhaObtida) ;
				retLista2 = LIS_ObterValor( listaColunas, &colunaObtida) ;  

				if(listaCharLinhas[i] == *linhaObtida && listaCharColunas[i] == *colunaObtida)
				{
					found = 1 ;
					break ;
				} /* if */

				retLista1 = LIS_AvancarElementoCorrente( listaLinhas, 1 ) ;
				retLista2 = LIS_AvancarElementoCorrente( listaColunas, 1 ) ;
			} /* while */

			if( found == 0 )
			{
				return TST_NotificarFalha( "As listas nao sao equivalentes." ) ;				
			} /* if */
		} /* for */
		
		return TST_CondRetOK;	
		
	} /* fim ativa: Testar ObterListaAmeacadosTabuleiro */
	
	return TST_CondRetNaoConhec ;
	
} /* Fim funÁ„o: TTAB &Testar tabuleiro */

/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
 *
 *  $FC Função: TTAB -Destruir valor
 *
 ***********************************************************************/

void DestruirValor( void * pDado )
{
	free ( pDado ) ;

} /* Fim Função: TTAB -Destruir valor */


/***********************************************************************
 *
 *  $FC Função: TTAB -Comparar valor
 *
 ***********************************************************************/

int CompararValor( void * pDado_1 , void * pDado_2 )
{
	char * valor_1 = ( char * ) pDado_1 ;
	char * valor_2 = ( char * ) pDado_2 ;
	return strcmp( valor_1 , valor_2 ) ;

} /* Fim função: TTAB -Comparar valor */


/***********************************************************************
 *
 *  $FC Função: TTAB -Igual valor
 *
 ***********************************************************************/

int IgualValor( void * pDado_1 , void * pDado_2 )
{
	char * valor_1 = ( char * ) pDado_1 ;
	char * valor_2 = ( char * ) pDado_2 ;
	return strcmp( valor_1 , valor_2 ) ;

} /* Fim função: TTAB -Igual valor */


/***********************************************************************
*
*  $FC Função: TTAB -Validar indice do tabuleiro
*
***********************************************************************/

int ValidarInxTabuleiro( int inxTab , int Modo )
{

	if ( ( inxTab <  0 ) || ( inxTab >= DIM_VT_TABULEIRO ))
	{
	return FALSE ;
	} /* if */

	if ( Modo == VAZIO )
	{
		if ( vtTabuleiros[ inxTab ] != 0 )
		{
			return FALSE ;
		} /* if */
	} else
	{
		if ( vtTabuleiros[ inxTab ] == 0 )
		{
			return FALSE ;
		} /* if */
	} /* if */

	return TRUE ;

} /* Fim função: TTAB -Validar indice do tabuleiro */


/********** Fim do módulo de implementação: TLIS Teste lista de símbolos **********/

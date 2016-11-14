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
 *		 3       vas   13/nov/2016 mudaças para nova interface do tabuleiro
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
 *     =resetteste
 *           - anula o tabuleiro. Provoca vazamento de memória
 *     =criarTabuleiro           inx    condRetorno
 *	   =destruirTabuleiro        inx    condRetorno
 *     =inserirPeca              inx
 *     =moverPeca                inx    char         condRetorno
 *     =retirarPeca              inx    char         condRetorno
 *     =obterPeca                inx
 *     =obterListaAmeacantes     inx    condRetorno
 *     =obterListaAmeacados      inx    condRetorno
 *
 ***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	
	int inxTab     = -1 , 
		numLidos   = -1 ,
		CondRetEsp = -1 ;
	
	TST_tpCondRet CondRet ;
	
	char charParm1 ,
		 charParm2 ,
		 charParm3 ,
		 charParm4 ;

	char * nomeObtido ;
	char * corObtida  ;
	char * linhaObtida ;
	char * colunaObtida ;
	
	LIS_tppLista listaRet ;
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
		
		CondRet = TAB_CriarTabuleiro( &vtTabuleiros[ inxTab ] , "..\\pecas\\default\\config.conf" ) ;
		
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
	
	/* Testar ObterListaAmeacantesTabuleiro */
	
	else if ( strcmp( ComandoTeste , OBTER_AMEACANTES_CMD ) == 0 )
	{
	
		int i , j , igual ;
		CSA_tppCasa casaTst ;
		CSA_tppCasa vetCasaTst[ 1 ] ;
		CSA_tppCasa casaAtual ;
		CSA_tpCondRet retCasa ;
		LIS_tpCondRet retLista ;

		numLidos = LER_LerParametros( "icci" , &inxTab ,
									&charParm1 , &charParm2 ,
									&CondRetEsp ) ;
		
		if ( ( numLidos != 4 ) )
		{
			return TST_CondRetParm ;
		} /* if */
		
		i = charParm2 - '0' ;
		j = charParm1 - 'A' + 1 ;
		
		retCasa = CSA_CriarCasa( &casaAtual ) ;

		if ( retCasa != CSA_CondRetOK )
		{
			CondRet = TAB_CondRetFaltouMemoria ;
			return TST_CompararInt( CondRetEsp , CondRet ,
									"Condicao de retorno errada ao criar casa na obter lista de ameacantes." ) ;
		} /* if */
		
		retCasa = CSA_CriarCasa( &casaTst ) ;

		if ( retCasa != CSA_CondRetOK )
		{
			CondRet = TAB_CondRetFaltouMemoria ;
			return TST_CompararInt( CondRetEsp , CondRet ,
									"Condicao de retorno errada ao criar casa na obter lista de ameacantes." ) ;
		} /* if */
		
		vetCasaTst[ 0 ] = casaTst ;
		
		CondRet = TAB_ObterCasaTabuleiro( charParm1 , charParm2 ,
										&casaAtual , vtTabuleiros[ inxTab ] ) ;

		if ( CondRet )
		{
			return TST_CompararInt( CondRetEsp , CondRet ,
									"Condicao de retorno errada ao obter casa tabuleiro na obter lista de ameacantes." ) ;
		} /* if */
		
		retCasa = CSA_ModificarListaAmeacantesCasa( vetCasaTst , 1 ,
													casaAtual ) ;

		if ( retCasa )
		{
			CondRet = TAB_CondRetNaoExiste ;
			return TST_CompararInt( CondRetEsp , CondRet ,
									"Condicao de retorno errada ao modificar lista ameacantes da casa na obter lista de ameacantes." ) ;
		} /* if */
		
		retLista = LIS_CriarLista( &listaLinhas , "linh" ,
								DestruirValor , CompararValor ,
								IgualValor ) ;

		if ( retLista )
		{
			CondRet = TAB_CondRetFaltouMemoria ;
			return TST_CompararInt( CondRetEsp , CondRet ,
									"Condicao de retorno errada ao criar lista na obter lista de ameacantes." ) ;
		} /* if */

		retLista = LIS_CriarLista( &listaColunas , "colu" ,
								DestruirValor , CompararValor ,
								IgualValor ) ;

		if ( retLista )
		{
			CondRet = TAB_CondRetFaltouMemoria ;
			return TST_CompararInt( CondRetEsp , CondRet ,
									"Condicao de retorno errada ao criar lista na obter lista de ameacantes." ) ;
		} /* if */
		
		CondRet = TAB_ObterListaAmeacantesTabuleiro ( charParm1 , charParm2 ,
													&listaLinhas , &listaColunas ,
													vtTabuleiros[ inxTab ] ) ;

		printf("Obteve lista ameacantes\n");

		linhaObtida = ( char * ) malloc( sizeof( char ) ) ;
		colunaObtida = ( char * ) malloc( sizeof( char ) ) ;
		
		if ( !CondRet )
		{
			retLista = LIS_ObterValor( listaLinhas , ( void ** ) &linhaObtida ) ;

			if ( retLista == LIS_CondRetListaVazia )
			{
				CondRet = TAB_CondRetNaoExiste ;
				return TST_CompararInt( CondRetEsp , CondRet ,
										"Condicao de retorno errada ao obter lista de ameacantes.7" ) ;
			} /* if */

			retLista = LIS_ObterValor( listaColunas , ( void ** ) &colunaObtida ) ;

			if ( retLista == LIS_CondRetListaVazia )
			{
				CondRet = TAB_CondRetNaoExiste ;
				return TST_CompararInt( CondRetEsp , CondRet ,
										"Condicao de retorno errada ao obter lista de ameacantes.8" ) ;
			} /* if */
            
            CondRet = CSA_CompararCasa( casaAtual , casaTst , &igual ) ;
            if ( CondRet == CSA_CondRetNaoExiste )
            {
                CondRet = TAB_CondRetNaoExiste ;
                return TST_CompararInt( CondRetEsp , CondRet ,
                                "Condicao de retorno errada ao obter lista de ameacantes.9" ) ;
            } /* if */

            if ( igual )
            {
                return TST_CondRetOK ;
            }

        } /* if */
        
        LIS_DestruirLista( listaRet ) ;
        
        return TST_CompararInt( CondRetEsp , CondRet ,
                               "Condicao de retorno errada ao obter lista de ameacantes.10" ) ;
        
    } /* fim ativa: Testar ObterListaAmeacantesTabuleiro */

    /* Testar ObterListaAmeacadosTabuleiro */
    
    else if ( strcmp( ComandoTeste , OBTER_AMEACADOS_CMD ) == 0 )
    {
        
        int i , j , igual ;
        CSA_tppCasa casaTst ;
        CSA_tppCasa vetCasaTst[1] ;
        CSA_tppCasa casaAtual ;

        numLidos = LER_LerParametros( "icci" , &inxTab ,
                                     &charParm1 ,
                                     &charParm2 ,
                                     &CondRetEsp) ;
        
        if ( ( numLidos != 4 ) )
        {
            return TST_CondRetParm ;
        } /* if */
        
        i = charParm2 - '0' ;
        j = charParm1 - 'A' + 1 ;

        CondRet = CSA_CriarCasa( &casaAtual ) ;
        if ( CondRet == CSA_CondRetFaltouMemoria )
        {
            CondRet = TAB_CondRetNaoExiste ;
            return TST_CompararInt( CondRetEsp , CondRet ,
                                   "Condicao de retorno errada ao obter lista de ameacados.1" ) ;
        } /* if */
        
        CondRet = CSA_CriarCasa( &casaTst ) ;
        if ( CondRet == CSA_CondRetFaltouMemoria )
        {
            CondRet = TAB_CondRetNaoExiste ;
            return TST_CompararInt( CondRetEsp , CondRet ,
                                   "Condicao de retorno errada ao obter lista de ameacados.2" ) ;
        } /* if */

        vetCasaTst[0] = casaTst ;
        
        CondRet = TAB_ObterCasaTabuleiro( charParm1 ,
                                         charParm2 ,
                                         &casaAtual ,
                                         vtTabuleiros[ inxTab ] ) ;
        if ( CondRet != TAB_CondRetOK )
        {
            return TST_CompararInt( CondRetEsp , CondRet ,
                                   "Condicao de retorno errada ao obter lista de ameacados.4" ) ;
        } /* if */
        
        CondRet = CSA_ModificarListaAmeacadosCasa( vetCasaTst ,
                                                   1 ,
                                                   casaAtual ) ;
        if ( CondRet == CSA_CondRetNaoExiste )
        {
            CondRet = TAB_CondRetNaoExiste ;
            return TST_CompararInt( CondRetEsp , CondRet ,
                                   "Condicao de retorno errada ao obter lista de ameacados.5" ) ;
        } /* if */
        
        CondRet = LIS_CriarLista( &listaRet ,
                                 "amts" ,
                                 DestruirValor ,
                                 CompararValor ,
                                 IgualValor ) ;
        if ( CondRet == LIS_CondRetFaltouMemoria )
        {
            CondRet = TAB_CondRetNaoExiste ;
            return TST_CompararInt( CondRetEsp , CondRet ,
                            "Condicao de retorno errada ao obter lista de ameacados.6" ) ;
        } /* if */
        
        CondRet = TAB_ObterListaAmeacadosTabuleiro ( charParm1 ,
                                                     charParm2 ,
                                                     &listaRet ,
                                                     &listaRet ,
                                                     vtTabuleiros[ inxTab ] ) ;
        
        if ( CondRet == TAB_CondRetOK )
        {
            CondRet = LIS_ObterValor( listaRet , ( void ** ) &casaAtual ) ;
            if ( CondRet == LIS_CondRetListaVazia )
            {
                CondRet = TAB_CondRetNaoExiste ;
                return TST_CompararInt( CondRetEsp , CondRet ,
                                "Condicao de retorno errada ao obter lista de ameacados.7" ) ;
            } /* if */
            
            CondRet = CSA_CompararCasa( casaAtual , casaTst , &igual ) ;
            if ( CondRet == CSA_CondRetNaoExiste )
            {
                CondRet = TAB_CondRetNaoExiste ;
                return TST_CompararInt( CondRetEsp , CondRet ,
                                "Condicao de retorno errada ao obter lista de ameacados.8" ) ;
            } /* if */
            
            if ( igual )
            {
                return TST_CondRetOK ;
            }
            
        } /* if */
        
        LIS_DestruirLista( listaRet ) ;
        
        return TST_CompararInt( CondRetEsp , CondRet ,
                               "Condicao de retorno errada ao obter lista de ameacados.9" ) ;
        
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

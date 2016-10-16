/***************************************************************************
*  $MCI Módulo de implementação: TCSA Teste casas do tabuleiro
*
*  Arquivo gerado:              TestCSA.c
*  Letras identificadoras:      TCSA
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: vas
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       vas   10/out/2016 início desenvolvimento
*
***************************************************************************/

#include	<string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include	"Casa.h"
#include	"Lista.h"

static const char RESET_PECA_CMD             	 [ ] = "=resetTeste"        	;
static const char CRIAR_CASA_CMD             	 [ ] = "=criarCasa"         	;
static const char INSERE_PECA_CASA_CMD       	 [ ] = "=inserePeca"    	    ;
static const char REMOVE_PECA_CASA_CMD       	 [ ] = "=removePeca"	        ;
static const char OBTER_PECA_CASA_CMD		 	 [ ] = "=obterPeca"				;
static const char COMPARA_CASAS_CMD		 	     [ ] = "=comparaCasas"			;
static const char MODIFICAR_LISTA_AMEACANTE_CMD  [ ] = "=modificarAmeacante"	;
static const char MODIFICAR_LISTA_AMEACADOS_CMD  [ ] = "=modificarAmeacados"	;
static const char OBTER_LISTA_AMEACANTE_CMD  	 [ ] = "=obterAmeacante"		;
static const char OBTER_LISTA_AMEACADOS_CMD  	 [ ] = "=obterAmeacados"		;
static const char DESTROI_CASA_CMD           	 [ ] = "=destroiCasa"       	;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_CASA   10
#define DIM_VALOR     100

CSA_tppCasa vtCasas[ DIM_VT_CASA ] ;
CSA_tppCasa casasTeste[ DIM_VT_CASA ] ;
CSA_tppCasa casasTeste2[ DIM_VT_CASA ] ;
LIS_tppLista listaRecebida ;

/***** Protótipos das funções encapuladas no módulo *****/

  	static void CriarCasasTeste( ) ;

  	static void CriarCasasTeste2( ) ;

  	static int ComparaListaCasas( ) ;

  	static int ComparaCasas( void *pDado_1 ,  CSA_tppCasa pDado_2 ) ;

	static int ValidarInxCasa( int inxCasa , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TCSA &Testar casa
*
*  $ED Descrição da função
*     Podem ser criadas até 10 casas, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetTeste
*           - anula o vetor de casas. Provoca vazamento de memória
*     =criarCasa                    inx    condRetorno
*	  =inserePeca 					inx    nomePeca     corPeca 	  condRetorno
*	  =removePeca                   inx    condRetorno
*     =obterPeca                    inx    nomePeca     corPeca       condRetorno
*	  =comparaCasas 				inx1   inx2 		igualdade     condRetorno
*	  =modificarAmeacante 			inx    condRetorno
*	  =modificarAmeacados 			inx    condRetorno
*	  =obterAmeacante 				inx    igualdade    condRetorno
*	  =obterAmeacados 				inx    igualdade    condRetorno
*     =destroiPeca                  inx    condRetorno
*
***********************************************************************/

	TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
	{

		int inxCasa      = -1 ,
			inxCasa2     = -1 ,
			igualdadeEsp = -1 ,
			numLidos     = -1 ,
			CondRetEsp   = -1 ;

		int igualdade ;

		TST_tpCondRet CondRet ;

		char nomePecaEsp ;
		char corPecaEsp ;

		char * nomePeca ;
		char * corPeca ;

		int i ;

		CriarCasasTeste( ) ;
		CriarCasasTeste2( ) ;

		/* Efetuar reset de teste de casa */

		if ( strcmp( ComandoTeste , RESET_PECA_CMD ) == 0 )
		{

				for( i = 0 ; i < DIM_VT_CASA ; i++ )
			{
			  	vtCasas[ i ] = NULL ;
			} /* for */

			return TST_CondRetOK ;

		} /* fim ativa: Efetuar reset de teste de casa */

		/* Testar CriarCasa */

		else if ( strcmp( ComandoTeste , CRIAR_CASA_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "ii" , &inxCasa ,
										&CondRetEsp) ;

			if ( ( numLidos != 2 )
			  || ( ! ValidarInxCasa( inxCasa , VAZIO )))
			{
			   return TST_CondRetParm ;
			} /* if */

			CondRet = CSA_CriarCasa( &vtCasas[ inxCasa ] ) ;

			return TST_CompararInt( CondRetEsp , CondRet ,
			        				"Condicao de retorno errada ao criar casa." ) ;

		} /* fim ativa: Testar CriarCasa */

		/* Testar Inserir peça na casa */

		else if ( strcmp( ComandoTeste , INSERE_PECA_CASA_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "icci" , &inxCasa ,
										&nomePecaEsp , &corPecaEsp ,
										&CondRetEsp ) ;

			if ( ( numLidos != 4 ) )
			{
			   return TST_CondRetParm ;
			} /* if */

			CondRet = CSA_InserirPecaCasa( nomePecaEsp , corPecaEsp , vtCasas[ inxCasa ] ) ;

			return TST_CompararInt( CondRetEsp , CondRet ,
			        				"Condicao de retorno errada ao inserir peca." ) ;

		} /* fim ativa: Testar Inserir peça na casa */

		/* Testar Remover peça da casa */

		else if ( strcmp( ComandoTeste , REMOVE_PECA_CASA_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "ii" , &inxCasa ,
										&CondRetEsp ) ;

			if ( numLidos != 2 )
			{
			   return TST_CondRetParm ;
			} /* if */

			CondRet = CSA_RetirarPecaCasa( vtCasas[ inxCasa ] ) ;

			return TST_CompararInt( CondRetEsp , CondRet ,
			        				"Condicao de retorno errada ao remover peca." ) ;

		} /* fim ativa: Testar Remover peça da casa */

		/* Testar Obter peça da casa */

		else if ( strcmp( ComandoTeste , OBTER_PECA_CASA_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "icci" , &inxCasa ,
										&nomePecaEsp , &corPecaEsp ,
										&CondRetEsp ) ;

			if ( numLidos != 4 )
			{
			   return TST_CondRetParm ;
			} /* if */

			nomePeca = ( char * ) malloc ( sizeof ( char ) ) ;
			corPeca = ( char * ) malloc ( sizeof ( char ) ) ;

			CondRet = CSA_ObterPecaCasa( &nomePeca , &corPeca , vtCasas[ inxCasa ] ) ;

			if ( CondRetEsp )
			{
			  	return TST_CompararInt( CondRetEsp , CondRet ,
			        					"Casa deveria estar vazia." ) ;
			}/* if */

			if ( nomePecaEsp != *nomePeca )
			{
				return TST_CompararChar( nomePecaEsp , *nomePeca ,
										"Nome da peca recebido errado." ) ;
			}/* if */

			if ( corPecaEsp != *corPeca )
			{
				return TST_CompararChar( corPecaEsp , *corPeca ,
										"Cor da peca recebida errada." ) ;
			}/* if */

			free( nomePeca ) ;
			free( corPeca ) ;

			return TST_CompararInt( CondRetEsp , CondRet ,
			        				"Condicao de retorno errada ao obter peca." ) ;

		} /* fim ativa: Testar Obter peça da casa */

		else if ( strcmp( ComandoTeste , COMPARA_CASAS_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "iiii" , &inxCasa ,
										&inxCasa2 , &igualdadeEsp ,
										&CondRetEsp ) ;

			if ( numLidos != 4 )
			{
			   return TST_CondRetParm ;
			} /* if */

			CondRet = CSA_CompararCasa( vtCasas[ inxCasa ] , vtCasas[ inxCasa2 ] , &igualdade ) ;

			if ( CondRetEsp )
			{
				return TST_CompararInt( CondRetEsp , CondRet ,
			        					"Condicao de retorno errada ao comparar casa." ) ;
			} /* if */


			if ( igualdadeEsp != igualdade )
			{
				return TST_CompararInt( igualdadeEsp , igualdade ,
			        					"Igualdade errada ao comparar casa." ) ;
			}
			else
			{
				return TST_CompararInt( CondRetEsp , CondRet ,
			        					"Condicao de retorno errada ao comparar casa." ) ;
			} /* if */

		} /* fim ativa: Testar Remover peça da casa */

		/* Testar Modificar lista ameacantes */

		else if ( strcmp( ComandoTeste , MODIFICAR_LISTA_AMEACANTE_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "ii" , &inxCasa ,
										&CondRetEsp ) ;

			if ( ( numLidos != 2 )
			  || ( ! ValidarInxCasa( inxCasa , NAO_VAZIO )))
			{
			   return TST_CondRetParm ;
			} /* if */

			CondRet = CSA_ModificarListaAmeacantesCasa( casasTeste , DIM_VT_CASA , vtCasas[ inxCasa ] ) ;

			return TST_CompararInt( CondRetEsp , CondRet ,
			        				"Condicao de retorno errada ao modificar lista ameacantes." ) ;

			} /* fim ativa: Testar Modificar lista ameacantes */

		/* Testar Modificar lista ameacados */

		else if ( strcmp( ComandoTeste , MODIFICAR_LISTA_AMEACADOS_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "ii" , &inxCasa ,
										&CondRetEsp ) ;

			if ( ( numLidos != 2 )
			  || ( ! ValidarInxCasa( inxCasa , NAO_VAZIO )))
			{
			   return TST_CondRetParm ;
			} /* if */

			CondRet = CSA_ModificarListaAmeacadosCasa( casasTeste , DIM_VT_CASA , vtCasas[ inxCasa ] ) ;

			return TST_CompararInt( CondRetEsp , CondRet ,
			        				"Condicao de retorno errada ao modificar lista ameacados." ) ;

		} /* fim ativa: Testar Modificar lista ameacados */

		/* Testar Obter lista ameacantes */

		else if ( strcmp( ComandoTeste , OBTER_LISTA_AMEACANTE_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "iii" , &inxCasa ,
										&igualdadeEsp , &CondRetEsp ) ;

			if ( ( numLidos != 3 )
			  || ( ! ValidarInxCasa( inxCasa , NAO_VAZIO )))
			{
			   return TST_CondRetParm ;
			} /* if */

			CondRet = CSA_ObterListaAmeacantesCasa( &listaRecebida , vtCasas[ inxCasa ] ) ;

			if ( ComparaListaCasas( igualdadeEsp ) )
			{
				return TST_CompararInt( CondRetEsp , CondRet ,
			        				"Condicao de retorno errada ao obter lista ameacantes." ) ;
			} /* if */

			return TST_NotificarFalha( "Lista de ameacantes recebida errada." ) ;

			} /* fim ativa: Testar Obter lista ameacantes */

			/* Testar Obter lista ameacados */

			else if ( strcmp( ComandoTeste , OBTER_LISTA_AMEACADOS_CMD ) == 0 )
			{

				numLidos = LER_LerParametros( "iii" , &inxCasa ,
											&igualdadeEsp , &CondRetEsp ) ;

			if ( ( numLidos != 3 )
			  || ( ! ValidarInxCasa( inxCasa , NAO_VAZIO )))
			{
			   return TST_CondRetParm ;
			} /* if */

			CondRet = CSA_ObterListaAmeacadosCasa( &listaRecebida , vtCasas[ inxCasa ] ) ;

			if ( ComparaListaCasas( igualdadeEsp ) )
			{
				return TST_CompararInt( CondRetEsp , CondRet ,
			        				"Condicao de retorno errada ao obter lista ameacados." ) ;
			} /* if */

			return TST_NotificarFalha( "Lista de ameacados recebida errada." ) ;

		} /* fim ativa: Testar Obter lista ameacados */

		/* Testar Destruir casa */

		else if ( strcmp( ComandoTeste , DESTROI_CASA_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "ii" , &inxCasa ,
										&CondRetEsp ) ;

			if ( numLidos != 2 )
			{
		   		return TST_CondRetParm ;
			} /* if */

			CondRet = CSA_DestruirCasa( vtCasas[ inxCasa ] ) ;

			vtCasas[ inxCasa ] = NULL ;

			return TST_CompararInt( CondRetEsp , CondRet ,
		        					"Condicao de retorno errada ao destruir a casa." ) ;

		} /* fim ativa: Testar Destruir casa */

		return TST_CondRetNaoConhec ;

	} /* Fim função: TCSA &Testar casa */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TCSA -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pDado )
   {

    	free ( pDado ) ;

   } /* Fim função: TCSA -Destruir valor */


/***********************************************************************
*
*  $FC Função: TCSA -Comparar valor
*
***********************************************************************/

   int CompararValor( void * pDado_1 , void * pDado_2 )
   {

     	char * valor_1 = ( char * ) pDado_1 ;
     	char * valor_2 = ( char * ) pDado_2 ;
     	return strcmp( valor_1 , valor_2 ) ;

   } /* Fim função: TCSA -Comparar valor */


/***********************************************************************
*
*  $FC Função: TCSA -Igual valor
*
***********************************************************************/

   int IgualValor( void * pDado_1 , void * pDado_2 )
   {

    	char * valor_1 = ( char * ) pDado_1 ;
    	char * valor_2 = ( char * ) pDado_2 ;
    	return strcmp( valor_1 , valor_2 ) ;

   } /* Fim função: TCSA -Igual valor */


/***********************************************************************
*
*  $FC Função: TCSA -Criar casas de teste
*
***********************************************************************/

   	void CriarCasasTeste( )
   	{

   		int i ;

     	for ( i = 0 ; i < DIM_VT_CASA ; i++ )
     	{
     		CSA_CriarCasa( &casasTeste[ i ] ) ;
     	} /* for */

   	} /* Fim função: TCSA -Criar casas de teste */


/***********************************************************************
*
*  $FC Função: TCSA -Criar casas de teste 2
*
***********************************************************************/

   	void CriarCasasTeste2( )
   	{

   		int i ;

     	for ( i = 0 ; i < DIM_VT_CASA ; i++ )
     	{
     		CSA_CriarCasa( &casasTeste2[ i ] ) ;
     		CSA_InserirPecaCasa( 'P' , 'P' ,  casasTeste2[ i ] ) ;
     	} /* for */

   	} /* Fim função: TCSA -Criar casas de teste 2 */


/***********************************************************************
*
*  $FC Função: TCSA -Comparar Lista com Casas de teste
*
***********************************************************************/

   	int ComparaListaCasas( int igualdade )
   	{

   		int i ;
   		CSA_tppCasa pCasa1 ;

   		if ( igualdade )
   		{
   			for ( i = 0 ; i < DIM_VT_CASA ; i++ )
	     	{
	     		printf("I: %d\n", i);
	     		LIS_ObterValor( listaRecebida , &pCasa1 ) ;
	     		LIS_AvancarElementoCorrente( listaRecebida , 1 ) ;
	     		if ( ComparaCasas( pCasa1 , casasTeste[ i ] ) == FALSE )
	     		{
	     			return FALSE ;
	     		} /* if */	
	     	} /* for */
   		}
   		else
   		{
   			for ( i = 0 ; i < DIM_VT_CASA ; i++ )
	     	{
	     		printf("I: %d\n", i);
	     		LIS_ObterValor( listaRecebida , &pCasa1 ) ;
	     		LIS_AvancarElementoCorrente( listaRecebida , 1 ) ;
	     		if ( ComparaCasas( pCasa1 , casasTeste2[ i ] ) == FALSE )
	     		{
	     			return FALSE ;
	     		} /* if */	
	     	} /* for */
   		} /* if */


    	return TRUE ;

   	} /* Fim função: TCSA -Comparar Lista com Casas de teste */


/***********************************************************************
*
*  $FC Função: TCSA -Comparar casas
*
***********************************************************************/

   	int ComparaCasas( CSA_tppCasa pCasa1 ,  CSA_tppCasa pCasa2 )
   	{

   		int igualdade ;

   		CSA_CompararCasa( pCasa1 , pCasa2 , &igualdade ) ;

   		if ( igualdade )
   		{
   			return TRUE ;
   		}
   		else
   		{
   			return FALSE ;
   		} /* if */

   	} /* Fim função: TCSA -Comparar casas */


/***********************************************************************
*
*  $FC Função: TCSA -Validar indice da casa
*
***********************************************************************/

   	int ValidarInxCasa( int inxCasa , int Modo )
   	{

     	if ( ( inxCasa <  0 ) || ( inxCasa >= DIM_VT_CASA ))
     	{
        	return FALSE ;
     	} /* if */

     	if ( Modo == VAZIO )
     	{
        	if ( vtCasas[ inxCasa ] != 0 )
        	{
           		return FALSE ;
         	} /* if */
      	} else
      	{
         	if ( vtCasas[ inxCasa ] == 0 )
        	{
            	return FALSE ;
         	} /* if */
      	} /* if */

     	return TRUE ;

   	} /* Fim função: TCSA -Validar indice da casa */

/********** Fim do módulo de implementação: TCSA Teste casas do tabuleiro **********/

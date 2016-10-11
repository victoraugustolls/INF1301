/***************************************************************************
*  $MCI Módulo de implementação: TPCA Teste peça de xadrez
*
*  Arquivo gerado:              TestPCA.c
*  Letras identificadoras:      TPCA
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
*     1       vas   06/out/2016 início desenvolvimento
*
***************************************************************************/

#include	<string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Peca.h"

static const char RESET_PECA_CMD             [ ] = "=resetTeste"        ;
static const char CRIAR_PECA_CMD             [ ] = "=criarPeca"         ;
static const char OBTER_NO_CMD               [ ] = "=obterNo"           ;
static const char DESTROI_PECA_CMD           [ ] = "=destroiPeca"       ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_PECA   10
#define DIM_VALOR     100

PCA_tppPeca   vtPecas[ DIM_VT_PECA ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static int ValidarInxPeca( int inxPeca , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TPCA &Testar peça
*
*  $ED Descrição da função
*     Podem ser criadas até 10 peças, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetTeste
*           - anula o vetor de peças. Provoca vazamento de memória
*     =criarPeca                    inx    nomePeca     corPeca       condRetorno
*     =obterNo                      inx    nomePeca     corPeca       condRetorno
*     =destroiPeca                  inx    condRetorno
*
***********************************************************************/

	TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
	{

		int inxPeca    = -1 ,
			numLidos   = -1 ,
			CondRetEsp = -1  ;

		TST_tpCondRet CondRet ;

		char nomePecaEsp ;
		char corPecaEsp ;

		char * nomePeca ;
		char * corPeca ;

		int i ;

		/* Efetuar reset de teste de peça */

		if ( strcmp( ComandoTeste , RESET_PECA_CMD ) == 0 )
		{

			for( i = 0 ; i < DIM_VT_PECA ; i++ )
		{
		  	vtPecas[ i ] = NULL ;
		} /* for */

		return TST_CondRetOK ;

		} /* fim ativa: Efetuar reset de teste de peça */

		/* Testar CriarPeca */

		else if ( strcmp( ComandoTeste , CRIAR_PECA_CMD ) == 0 )
		{

		numLidos = LER_LerParametros( "icci" , &inxPeca ,
									&nomePecaEsp , &corPecaEsp ,
									&CondRetEsp) ;

		if ( ( numLidos != 4 )
		  || ( ! ValidarInxPeca( inxPeca , VAZIO )))
		{
		   return TST_CondRetParm ;
		} /* if */

		nomePeca = ( char * ) malloc ( sizeof ( char ) ) ;
		corPeca = ( char * ) malloc ( sizeof ( char ) ) ;
		*nomePeca = nomePecaEsp ;
		*corPeca = corPecaEsp ;

		CondRet = PCA_CriarPeca( &vtPecas[ inxPeca ] , nomePeca , corPeca ) ;

		free( nomePeca ) ;
		free( corPeca ) ;

		return TST_CompararInt( CondRetEsp , CondRet ,
		        				"Condicao de retorno errada ao criar peca." ) ;

		} /* fim ativa: Testar CriarPeca */

		/* Testar Obter valor da peça */

		else if ( strcmp( ComandoTeste , OBTER_NO_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "icci" , &inxPeca ,
										&nomePecaEsp , &corPecaEsp ,
										&CondRetEsp ) ;

		if ( ( numLidos != 4 )
		  || ( ! ValidarInxPeca( inxPeca , NAO_VAZIO )))
		{
		   return TST_CondRetParm ;
		} /* if */

		nomePeca = ( char * ) malloc ( sizeof ( char ) ) ;
		corPeca = ( char * ) malloc ( sizeof ( char ) ) ;

		CondRet = PCA_ObterValor( vtPecas[ inxPeca ] , &nomePeca , &corPeca ) ;

		if ( CondRetEsp )
		{
		  	return TST_CompararInt( CondRetEsp , CondRet ,
		        					"Peca deveria estar vazia." ) ;
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
		        				"Condicao de retorno errada ao criar peca." ) ;

		} /* fim ativa: Testar Obter valor da peça */

		/* Testar Destruir peça */

		else if ( strcmp( ComandoTeste , DESTROI_PECA_CMD ) == 0 )
		{

			numLidos = LER_LerParametros( "ii" , &inxPeca ,
										&CondRetEsp ) ;

			if ( numLidos != 2 )
			{
		   		return TST_CondRetParm ;
			} /* if */

			CondRet = PCA_DestruirPeca( vtPecas[ inxPeca ] ) ;

			vtPecas[ inxPeca ] = NULL ;

			return TST_CompararInt( CondRetEsp , CondRet ,
		        					"Condicao de retorno errada ao destruir a peca." ) ;

		} /* fim ativa: Testar Destruir peça */

		return TST_CondRetNaoConhec ;

	} /* Fim função: TPCA &Testar peça */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TPCA -Validar indice da peça
*
***********************************************************************/

   	int ValidarInxPeca( int inxPeca , int Modo )
   	{

     	if ( ( inxPeca <  0 ) || ( inxPeca >= DIM_VT_PECA ))
     	{
        	return FALSE ;
     	} /* if */

     	if ( Modo == VAZIO )
     	{
        	if ( vtPecas[ inxPeca ] != 0 )
        	{
           		return FALSE ;
         	} /* if */
      	} else
      	{
         	if ( vtPecas[ inxPeca ] == 0 )
        	{
            return FALSE ;
         	} /* if */
      	} /* if */

     	return TRUE ;

   	} /* Fim função: TPCA -Validar indice da peça */

/********** Fim do módulo de implementação: TPCA Teste peça de xadrez **********/

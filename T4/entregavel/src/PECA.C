/***************************************************************************
*  $MCI Módulo de implementação: PCA  Peças de um jogo de xadrez
*
*  Arquivo gerado:              PECA.c
*  Letras identificadoras:      PCA
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
*     2       vas   10/nov/2016 mudança da estrutura
*     1       vas   06/out/2016 início desenvolvimento
*
***************************************************************************/

#include	<stdio.h>
#include	<memory.h>
#include  	<malloc.h>
#include  	<assert.h>

#define	PECA_OWN
#include "PECA.h"
#undef PECA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: PCA Descritor da peça
*
*
***********************************************************************/

  	typedef struct PCA_tagPeca {

   	    char nomePeca ;
         		/* Nome da peça */

       	char corPeca ;
         		/* Cor da peça */

  	} PCA_tpPeca ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void PCA_EsvaziarPeca( PCA_tppPeca pPeca ) ;

   static void PCA_LimparPeca( PCA_tppPeca pPeca ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: PCA  &Criar peça
*  ****/

   	PCA_tpCondRet PCA_CriarPeca( PCA_tppPeca * pPeca ,
           						char nomePeca ,
             					char corPeca )
   	{

     	PCA_tppPeca pNewPeca = NULL ;

     	pNewPeca = ( PCA_tpPeca * ) malloc ( sizeof ( PCA_tpPeca ) ) ;

     	if ( pNewPeca == NULL )
     	{
     		return PCA_CondRetFaltouMemoria ;
     	}

     	PCA_LimparPeca( pNewPeca ) ;

     	pNewPeca->nomePeca = nomePeca ;
     	pNewPeca->corPeca = corPeca ;

     	*pPeca = pNewPeca ;

     	return PCA_CondRetOK ;

  	} /* Fim função: PCA  &Criar peça */

/***************************************************************************
*
*  Função: PCA  &Copiar peça
*  ****/

    PCA_tpCondRet PCA_CopiarPeca(   PCA_tppPeca * pPeca ,
                                    PCA_tppPeca pecaOriginal)
    {
        return PCA_CriarPeca( pPeca , pecaOriginal->nomePeca, pecaOriginal->corPeca);
        
    } /* Fim função: PCA  &Copiar peça */

/***************************************************************************
*
*  Função: PCA  &Alterar peça
*  ****/

    PCA_tpCondRet PCA_AlterarPeca( PCA_tppPeca pPeca ,
                      			char nomePeca ,
                      			char corPeca )
    {

      	if ( pPeca == NULL )
      	{
        	return PCA_CondRetPecaNaoExiste ;
      	} /* if */

      	pPeca->nomePeca = nomePeca ;
      	pPeca->corPeca = corPeca ;

      	return PCA_CondRetOK ;

    } /* Fim função: PCA  &Alterar peça */

/***************************************************************************
*
*  Função: PCA  &Obter referência para o valor contido no elemento
*  ****/

  	PCA_tpCondRet PCA_ObterValor( PCA_tppPeca pPeca ,
  								char * nomePeca ,
                               	char * corPeca )
  	{

  		if ( pPeca == NULL )
  		{
  			return PCA_CondRetPecaNaoExiste ;
  		} /* if */

     	#ifdef _DEBUG
        	assert( pPeca != NULL ) ;
     	#endif

       	*nomePeca = pPeca->nomePeca ;
       	*corPeca = pPeca->corPeca ;

      	return PCA_CondRetOK ;

   } /* Fim função: PCA  &Obter referência para o valor contido no elemento */

/***************************************************************************
*
*  Função: PCA  &Compara duas peças
*  ****/

    PCA_tpCondRet PCA_ComparaPecas( PCA_tppPeca pPeca_1 ,
                    				PCA_tppPeca pPeca_2 ,
                    				int * igualdade )
    {

      	if ( pPeca_1 == NULL || pPeca_2 == NULL )
        {
          	*igualdade = 0 ;
        	return PCA_CondRetPecaNaoExiste ;
        } /* if */

        if ( pPeca_1->nomePeca == pPeca_2->nomePeca 
        	&& pPeca_1->corPeca == pPeca_2->corPeca )
        {
        	*igualdade = 1 ;
        }
        else
        {
        	*igualdade = 0 ;
        }
        
        return PCA_CondRetOK ;

   } /* Fim função: PCA  &Compara duas peças */

/***************************************************************************
*
*  Função: PCA  &Destruir peça
*  ****/

  	PCA_tpCondRet PCA_DestruirPeca( PCA_tppPeca pPeca )
  	{

     	if ( pPeca == NULL )
     	{
        	return PCA_CondRetPecaNaoExiste ;
     	} /* if */

     	free( pPeca ) ;

     	return PCA_CondRetOK ;

  	} /* Fim função: PCA  &Destruir peça */

/***************************************************************************
*
*  Função: PCA  &Get Print Peca
*  ****/

    PCA_tpCondRet PCA_GetPrintPeca( PCA_tppPeca pPeca, char** print )
    {
        *print = (char*) malloc(sizeof(char)*3);
        if(*print == NULL)
        {
            return PCA_CondRetFaltouMemoria;
        }
        (*print)[0] = pPeca->nomePeca;
        (*print)[1] = pPeca->corPeca;
        (*print)[2] = '\0';
        return PCA_CondRetOK;
    }

/***********************************************************************
*
*  $FC Função: PCA  -Esvaziar a peça
*
***********************************************************************/

   	void PCA_EsvaziarPeca( PCA_tppPeca pPeca )
   	{

      	PCA_LimparPeca( pPeca ) ;

   	} /* Fim função: PCA  -Esvaziar a peça */


/***********************************************************************
*
*  $FC Função: PCA  -Limpar a peça
*
***********************************************************************/

   	void PCA_LimparPeca( PCA_tppPeca pPeca )
   	{
      	pPeca->nomePeca = 'V' ;
      	pPeca->corPeca = 'V' ;

   	} /* Fim função: PCA  -Limpar a peça */

/********** Fim do módulo de implementação: PCA  Peças de um jogo de xadrez **********/

#if ! defined( PECA_ )
#define PECA_
/***************************************************************************
*
*  $MCD Módulo de definição: PCA  Peças de um jogo de xadrez
*
*  Arquivo gerado:              PECA.h
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
*     1       vas   06/out/2016 início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa peças de um jogo de xadrez.
*     Podem existir n peças em operação simultaneamente.
*     As peças são identificadas por um nome e uma cor.
*
***************************************************************************/

#if defined( PECA_OWN )
   #define PECA_EXT
#else
   #define PECA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma peça */

typedef struct PCA_tagPeca * PCA_tppPeca ;


/***********************************************************************
*
*  $TC Tipo de dados: PCA Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da peça
*
***********************************************************************/

  	typedef enum {

       	PCA_CondRetOK = 0 ,
              	/* Concluiu corretamente */

       	PCA_CondRetPecaVazia = 1 ,
              	/* Peça está vazia */

       	PCA_CondRetPecaNaoExiste = 2 ,
       			/* Peça não existe */

       	PCA_CondRetFaltouMemoria = 3 ,
            	/* Faltou memória ao tentar criar um elemento de peça */

  	} PCA_tpCondRet ;


/***********************************************************************
*
*  $FC Função: PCA  &Criar peça
*
*  $ED Descrição da função
*     Cria uma peça do jogo de xadrez.
*
*  $EP Parâmetros
*     pPeca            - ponteiro para peça sendo criada
*     nomePeca         - nome da peça sendo criada
*	    corPeca 		     - cor da peça sendo criada
*
*  $FV Valor retornado
*     PCA_CondRetOK            - peça foi criada corretamente
*     PCA_CondRetFaltouMemoria - ocorreu um erro na criação da peça
*
***********************************************************************/

  	PCA_tpCondRet PCA_CriarPeca( PCA_tppPeca * pPeca ,
            					char * nomePeca ,
								char * corPeca ) ;


/***********************************************************************
*
*  $FC Função: PCA  &Alterar peça
*
*  $ED Descrição da função
*     Altera valor de uma peça do jogo de xadrez.
*
*  $EP Parâmetros
*     pPeca            - ponteiro para peça sendo alterada
*     nomePeca         - novo nome da peça sendo alterada
*	  corPeca 		   - nova cor da peça sendo alterada
*
*  $FV Valor retornado
*     PCA_CondRetOK             - peça foi alterada corretamente
*     PCA_CondRetPecaNaoExiste  - peça não existe
*
***********************************************************************/

  	PCA_tpCondRet PCA_AlterarPeca( PCA_tppPeca pPeca ,
            					char * nomePeca ,
								char * corPeca ) ;


/***********************************************************************
*
*  $FC Função: PCA  &Obter referência para o valor contido no elemento
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido na peça
*
*  $EP Parâmetros
*     pPeca            - ponteiro para a peça de onde se quer o valor
*     nomePeca         - ponteiro para o valor do nome da peça
*     corPeca          - ponteiro para o valor da cor da peça
*
*  $FV Valor retornado
*     PCA_CondRetOK
*     PCA_CondRetPecaVazia
*
***********************************************************************/

  	PCA_tpCondRet PCA_ObterValor( PCA_tppPeca pPeca ,
                               	char ** nomePeca ,
                               	char ** corPeca ) ;


/***********************************************************************
*
*  $FC Função: PCA  &Destruir peça
*
*  $ED Descrição da função
*     Destrói a peça fornecida.
*     O parâmetro ponteiro para a peça não é modificado.
*
*  $EP Parâmetros
*     pPeca            - ponteiro para peça sendo destruída
*
*  $FV Valor retornado
*     PCA_CondRetOK             - destruiu sem problemas
*     PCA_CondRetPecaNaoExiste  - peça não existe
*
***********************************************************************/

  	PCA_tpCondRet PCA_DestruirPeca( PCA_tppPeca pPeca ) ;

#undef PECA_EXT

/********** Fim do módulo de definição: PCA  Peças de um jogo de xadrez **********/

#else
#endif

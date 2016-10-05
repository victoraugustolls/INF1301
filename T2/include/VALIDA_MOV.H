#if ! defined( VALIDA_MOV_ )
#define VALIDA_MOV_
/***************************************************************************
*
*  $MCD Módulo de definição: VMV  Validador de Movimentos
*
*  Arquivo gerado:              VALIDA_MOV.H
*  Letras identificadoras:      VMV
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Tabuleiro de Xadrez
*  Gestor:  LES/DI/PUC-Rio
*  Autores: iars
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       avs   04/out/2016 início desenvolvimento
*
*  $ED Descrição do módulo
*     TODO
*
***************************************************************************/

#if defined( VALIDA_MOV_OWN )
   #define VALIDA_MOV_EXT
#else
   #define VALIDA_MOV_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma configuracao de diretorio de movimento */

typedef struct VMV_configDir * VMV_tppConfigDir;

/***********************************************************************
*
*  $TC Tipo de dados: VMV Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do validador de movimento
*
***********************************************************************/

   typedef enum {

         VMV_CondRetOK = 0 ,
               /* Concluiu corretamente */

         VMV_CondRetErrAberturaArquivo = 1 ,
               /* Ocorreu um erro na leitura do arquivo */

         VMV_CondRetErrFormatoArquivoErrado = 2 ,
               /* Ocorreu um erro na leitura do arquivo */

         VMV_CondRetErrFaltouMemoria = 3,
               /* Ocorreu um erro na leitura do arquivo */

         VMV_CondRetVariavelNaoExistente = 4,
               /* Ocorreu um erro na leitura do arquivo */

         VMV_CondRetErrManuseioArquivo = 5,
               /* Ocorreu um erro na leitura do arquivo */

         VMV_CondRetErrComandoNaoExistente = 6
               /* Ocorreu um erro na leitura do arquivo */

   } VMV_tpCondRet ;

/***********************************************************************
*
*  $TC Tipo de dados: VMV Validez do Movimento
*
*
*  $ED Descrição do tipo
*     Determinação se um movimento é válido ou não
*
***********************************************************************/

   typedef enum {

         VMV_MovimentoValidoNao = 0 ,
               /* O Movimento não é válido */

         VMV_MovimentoValidoSim = 1
               /* O Movimento não é válido */

   } VMV_tpMovimentoValido ;

/***********************************************************************
*
*  $FC Função: VMV  &TODO
*
*  $ED Descrição da função
*     TODO
*
*  $EP Parâmetros
*
*     TODO          - TODO
*     TODO          - TODO
*
*  $FV Valor retornado
*     VMV_CondRetOK            - TODO
*     VMV_CondRetErrArquivoNaoEncontrado            - TODO
*     VMV_CondRetErrFormatoArquivoErrado            - TODO
*
***********************************************************************/

   VMV_tpCondRet VMV_CriarConfigDir (  VMV_tppConfigDir* pConfigDir, const char* pathConfigArq );


/***********************************************************************
*
*  $FC Função: VMV  &TODO
*
*  $ED Descrição da função
*     TODO
*
*  $EP Parâmetros
*
*     TODO          - TODO
*     TODO          - TODO
*
*  $FV Valor retornado
*     VMV_CondRetOK            - TODO
*     VMV_CondRetErrArquivoNaoEncontrado            - TODO
*     VMV_CondRetErrFormatoArquivoErrado            - TODO
*
***********************************************************************/

   VMV_tpCondRet VMV_DestruirConfigDir (  VMV_tppConfigDir pConfigDir );


/***********************************************************************
*
*  $FC Função: VMV  &TODO
*
*  $ED Descrição da função
*     TODO
*
*  $EP Parâmetros
*
*     TODO          - TODO
*     TODO          - TODO
*
*  $FV Valor retornado
*     VMV_CondRetOK            - TODO
*     VMV_CondRetErrArquivoNaoEncontrado            - TODO
*     VMV_CondRetErrFormatoArquivoErrado            - TODO
*
***********************************************************************/

   VMV_tpCondRet VMV_LerTabuleiroInicial (   VMV_tppConfigDir pConfig,
                                             char* pecas, 
                                             char* cores, 
                                             int* num_casas );

/***********************************************************************
*
*  $FC Função: VMV  &TODO
*
*  $ED Descrição da função
*     TODO
*
*  $EP Parâmetros
*
*     TODO          - TODO
*     TODO          - TODO
*
*  $FV Valor retornado
*     VMV_CondRetOK            - TODO
*     VMV_CondRetErrArquivoNaoEncontrado            - TODO
*     VMV_CondRetErrFormatoArquivoErrado            - TODO
*
***********************************************************************/

   VMV_tpCondRet VMV_ChecarMovimentoPeca (   VMV_tppConfigDir pConfig,
                                             VMV_tpMovimentoValido* movimento_valido,
                                             char peca,
                                             char cor, 
                                             void* casa_atual,
                                             void* casa_destino,
                                             void** casas,
                                             int num_casas,
                                             int num_dimensoes,
                                             int (**array_dimensao)(void* casa),
                                             int* array_sinal,
                                             int (*vazio)(void* casa),
                                             int (*inimigo)(void* casa),
                                             int* cond_especiais,
                                             int num_cond_especiais);

#undef VALIDA_MOV_EXT

/********** Fim do módulo de definição: VMV  Lista duplamente encadeada **********/

#else
#endif

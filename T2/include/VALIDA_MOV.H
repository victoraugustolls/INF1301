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

/***********************************************************************
* Nome do arquivo utilizado pelo módulo
***********************************************************************/

static const char CONFIG_FILE_NAME [ ] = "config.conf";

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

         VMV_CondRetErrArquivoNaoEncontrado = 1 ,
               /* Ocorreu um erro na leitura do arquivo */

         VMV_CondRetErrFormatoArquivoErrado = 2 ,
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

   VMV_tpCondRet VMV_LerTabuleiroInicial ( double* pecas, double* cores, double* num_casas );

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

   VMV_tpCondRet VMV_ChecarMovimentoPeca (   VMV_tpMovimentoValido* movimento_valido,
                                             char peca,
                                             char cor, 
                                             void* casa_atual,
                                             void* casa_destino,
                                             void* casas,
                                             int num_casas,
                                             int num_dimensoes,
                                             int (*array_dimensao)(void* casa),
                                             int* array_sinal,
                                             int (*vazio)(void* array_de_casas, int num_casas),
                                             int (*inimigo)(void* array_de_casas, int num_casas),
                                             int* cond_especiais,
                                             int num_cond_especiais);

#undef VALIDA_MOV_EXT

/********** Fim do módulo de definição: VMV  Lista duplamente encadeada **********/

#else
#endif

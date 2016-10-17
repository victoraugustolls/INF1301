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
*     1       iars   04/out/2016 início desenvolvimento
*
*  $ED Descrição do módulo
*     Módulo responsável por checar a validez do movimento de uma peça de uma casa para outra
*     assim como a configuração inicial destas.
*     Essa validez é checada através de uma série de arquivos de definição de peça
*     que definem a lógica do movimento de cada peça.
*
***************************************************************************/

#if defined( VALIDA_MOV_OWN )
   #define VALIDA_MOV_EXT
#else
   #define VALIDA_MOV_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma configuracao de diretorio de movimento */

typedef struct VMV_configDir * VMV_tppConfigDir ;

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
               /* Ocorreu um erro na abertura do arquivo */

         VMV_CondRetErrFormatoArquivoErrado = 2 ,
               /* O arquivo possui uma sintaxe errada */

         VMV_CondRetErrFaltouMemoria = 3 ,
               /* Faltou memória para completar a operação*/

         VMV_CondRetVariavelNaoExistente = 4 ,
               /* A variável utilizada não existe */

         VMV_CondRetErrManuseioArquivo = 5 ,
               /* Ocorreu algum erro na manipulação da posição de leitura do arquivo */

         VMV_CondRetErrComandoNaoExistente = 6
               /* O comando encontrado não existe */

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
               /* O Movimento é válido */

   } VMV_tpMovimentoValido ;

/***********************************************************************
*
*  $FC Função: VMV  &Cria um identificador para o arquivo de configuração
*
*  $ED Descrição da função
*     Dado um diretório, retorna por referência um identificador de um arquivo
*     de configuração.
*
*  $EP Parâmetros
*     pConfigDir          - ponteiro para o identificador de configuração
*     pathConfigArq       - diretório do arquivo
*
*  $FV Valor retornado
*     VMV_CondRetOK                       - Identificador de configuração criado corretamente
*     VMV_CondRetErrFaltouMemoria         - Ocorreu um erro na criação do identificador de configuração
*     VMV_CondRetErrAberturaArquivo       - Erro ao abrir o arquivo de configuração
*     VMV_CondRetErrFormatoArquivoErrado  - Arquivo de configuração foi criado no formato errado
*
***********************************************************************/

   VMV_tpCondRet VMV_CriarConfigDir ( VMV_tppConfigDir * pConfigDir , const char * pathConfigArq ) ;


/***********************************************************************
*
*  $FC Função: VMV  &Destroi o identificador do arquivo de configuração
*
*  $ED Descrição da função
*     Destrói o identificador de configuração.
*
*  $EP Parâmetros
*     pConfigDir          - ponteiro para o identificador de configuração
*
*  $FV Valor retornado
*     VMV_CondRetOK       - Identificador de configuração destruído corretamente
*
***********************************************************************/

   VMV_tpCondRet VMV_DestruirConfigDir ( VMV_tppConfigDir pConfigDir ) ;


/***********************************************************************
*
*  $FC Função: VMV  &Obter estado inicial do tabuleiro
*
*  $ED Descrição da função
*     Dado o identificador de configuração, retorna por referência um vetor de
*     peças e cores do tabuleiro no início. Ambos os vetores tem tamanho também
*     passado como parâmetro
*
*  $EP Parâmetros
*     pConfig       - identificador de configuração
*     pecas         - ponteiro para o vetor de peças
*     cores         - ponteiro para o vetor de cores
*     num_casas     - tamanho do vetor de peças e cores
*
*  $FV Valor retornado
*     VMV_CondRetOK                       - Retornou corretamente o estado inicial do tabuleiro
*     VMV_CondRetErrFaltouMemoria         - Ocorreu um erro ao pegar o estado inicial do tabuleiro
*     VMV_CondRetErrAberturaArquivo       - Erro ao abrir o arquivo de configuração
*     VMV_CondRetErrFormatoArquivoErrado  - Arquivo de configuração foi criado no formato errado
*
***********************************************************************/

   VMV_tpCondRet VMV_LerTabuleiroInicial (   VMV_tppConfigDir pConfig,
                                             char ** pecas, 
                                             char ** cores, 
                                             int * num_casas ) ;

/***********************************************************************
*
*  $FC Função: VMV  &Checar Movimento de Peça
*
*  $ED Descrição da função
*     Função que checa se o movimento de uma peça da casa atual para a casa de destino é válido.
*     Recebe uma série de vetores e funções que auxiliam a identificação da geometria do tabuleiro
*     em questão.
*     Suporta tabuleiros genéricos.
*
*  $EP Parâmetros
*       pConfig              - Arquivo de configuração aberto, com o uso de VMV_CriarConfigDir.
*       movimento_valido     - Retorno que informa se o movimento é válido ou não.
*       peca                 - Nome da peça sendo checada. Deve existir um arquivo com o exato nome
*                              desta peça no diretório definido no arquivo .conf.
*       casa_atual           - Ponteiro para a casa atual do movimento sendo checado
*       casa_destino         - Ponteiro para a casa de destino do movimento sendo checado.
*
*
*       casas                - Vetor com todas as casas do tabuleiro. O ordenamento não é relevante.
*       num_casas            - O número de elementos em casas.
*
*       num_dimensoes        - O número de dimensões e sinais no tabuleiro.
*       array_dimensao       - Vetor de funções em que a iésima função recebem uma 
*                               casa e uma estrutura auxiliar e retorna a iésima dimensão daquela casa
*       array_sinal          - Vetor de inteiros associado à peça em questão sendo analizada.
*                              Usualmente associado à cor da peça, atribuindo um sentido
*                              a cada uma das dimensões.
*
*       vazio                - Função que recebe uma casa e uma estrutura auxiliar e retorna 1 se
*                              a casa em questão está vazia e 0 caso não.
*       inimigo              - Função que recebe uma casa e uma estrutura auxiliar e retorna 1 se
*                              a casa em questão possui um inimigo e 0 caso não.
*
*       cond_especiais       - Vetor com inteiros 1 ou 0 referentes à condições especiais 
*                              relacionadas à peça em questão.
*                              Usualmente utilizado para eventos do tabuleiro, como quando
*                              a peça em questão nunca foi movimentada.
*       num_cond_especiais   - Número de elementos de cond_especiais.
*
*       aux                  - Estrutura auxiliar que será passada como parâmetro para algumas
*                              das funções sendo recebidas como parâmetros.
*
*  $FV Valor retornado
*      VMV_CondRetOK                       - Retornou corretamente o estado inicial do tabuleiro
*      VMV_CondRetErrAberturaArquivo       - Não encontrou o arquivo de definição de movimento da peça
*      VMV_CondRetErrFormatoArquivoErrado  - O formato (sintaxe) do arquivo está incorreto
*      VMV_CondRetVariavelNaoExistente     - Variável utilizada no arquivo não existe
*      VMV_CondRetErrManuseioArquivo       - Erro ao manipular o arquivo em memória
*      VMV_CondRetErrComandoNaoExistente   - Comando lido no arquivo da peça não existente
*
***********************************************************************/

   VMV_tpCondRet VMV_ChecarMovimentoPeca (   VMV_tppConfigDir pConfig ,
                                             VMV_tpMovimentoValido * movimento_valido ,
                                             char peca ,
                                             void * casa_atual ,
                                             void * casa_destino ,
                                             void ** casas ,
                                             int num_casas ,
                                             int num_dimensoes ,
                                             int ( ** array_dimensao ) ( void * casa, void * aux ) ,
                                             int * array_sinal ,
                                             int ( * vazio) ( void * casa, void * aux ) ,
                                             int ( * inimigo ) ( void * casa, void * aux ) ,
                                             int * cond_especiais ,
                                             int num_cond_especiais,
                                             void* aux ) ;

#undef VALIDA_MOV_EXT

/********** Fim do módulo de definição: VMV Validação de Movimento **********/

#else
#endif

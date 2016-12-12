#if ! defined( TABULEIRO_ )
#define TABULEIRO_
/***************************************************************************
 *
 *  $MCD MÛdulo de definição: TAB  Tabuleiro para jogo de xadrez
 *
 *  Arquivo gerado:              TABULEIRO.h
 *  Letras identificadoras:      TAB
 *
 *  Nome da base de software:    Arcabouçoo para a automaçãoo de testes de programas redigidos em C
 *  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
 *
 *  Projeto: INF 1301 / 1628 AutomatizaÁ„o dos testes de módulos C
 *  Gestor:  LES/DI/PUC-Rio
 *  Autores: lff
 *
 *  $HA Histórico de evolução:
 *     Versão  Autor    Data     ObservaÁıes
 *     3       iars  15/nov/2016 copiar tabuleiro e nova interface ameacantes ameacados
 *     2       lff   05/out/2016 desenvolvimento
 *     1       lff   04/out/2016 início desenvolvimento
 *
 *  $ED Descrição do módulo
 *     Implementa um tabuleiro de xadrez composto por n casas.
 *     Pode existir apenas um tabuleiro em operação.
 *
 *     Cada tabuleiro é homogêneo quanto ao tipo dos dados que armazena.
 *     Cada elemento do tabuleiro referencia o valor que contem.
 *
 *     Os ponteiros para os dados são copiados para elementos do tabuleiro.
 *        N„o é copiado o valor apontado por estes ponteiros.
 *
 *     O controle da destruição do valor de um elemento a ser excluído
 *        é realizado por uma função interna do módulo.
 *
 *
 ***************************************************************************/

#if defined( TABULEIRO_OWN )
#define TABULEIRO_EXT
#else
#define TABULEIRO_EXT extern
#endif

#include  "LISTA.H"
#include  "CASA.H"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um tabuleiro */

typedef struct TAB_tagTabuleiro * TAB_tppTabuleiro ;


/***********************************************************************
 *
 *  $TC Tipo de dados: TAB Condições de retorno
 *
 *
 *  $ED Descrição do tipo
 *     Condições de retorno das funções do tabuleiro
 *
 ***********************************************************************/

typedef enum {
    
    TAB_CondRetOK = 0 ,
    /* Concluiu corretamente */
    
    TAB_CondRetNaoExiste = 1 ,
    /* O tabuleiro ou algum dos seus componentes não existe */
    
    TAB_CondRetCoordNaoExiste = 2 ,
    /* A coordenada não existe em tal tabuleiro */
    
    TAB_CondRetMovInvalido = 3 ,
    /* O movimento não é válido em tal tabuleiro */
    
    TAB_CondRetFalhaArq = 4 ,
    /* Falha ao manipular algum arquivo necessário para o tabuleiro */
    
    TAB_CondRetFaltouMemoria = 5
    /* Faltou memória ao tentar criar um elemento do tabuleiro */

    #ifdef _DEBUG
      ,

      TAB_CondRetFalhaNaEstrutura = 6,
      /* Existe uma falha na estrutura do tabuleiro */

      TAB_CondRetFalhaDeturpar = 7,
      /* Não foi possível Deturpar */
    #endif

} TAB_tpCondRet ;

#ifdef _DEBUG

typedef enum {
    
    TAB_ELIMINA_ELEMENTO_CORRENTE = 1,

    TAB_NULL_CASA_SUCESSORA = 2,

    TAB_NULL_CASA_PREDECESSORA = 3,

    TAB_LIXO_CASA_SUCESSORA = 4,

    TAB_LIXO_CASA_PREDECESSORA = 5,
    
    TAB_NULL_CONTEUDO_CASA = 6,

    TAB_ALTERA_TIPO_APONTADO_CASA = 7,

    TAB_DESTACA_CASA_SEM_FREE = 8,
    
    TAB_NULL_PONTEIRO CORRENTE = 9

} TAB_tpDeturpacao ;

  /***********************************************************************
  *
  *  $FC Função: TAB  &Deturpa Tabuleiro
  *
  *  $ED Descrição da função
  *     Deturpa a estrutura do tabuleiro
  *
  *  $EP Par‚metros
  *     pTabuleiro - ponteiro para o tabuleiro a ser verificado
  *     pTabuleiro - tipo da deturpação a ser realizada
  *
  *  $FV Valor retornado
  *     TAB_CondRetOK                - Deturpação realizada com sucesso
  *     TAB_CondRetFalhaDeturpar     - Não foi possível deturpar a estrutura
  *
  ***********************************************************************/

  TAB_tpCondRet TAB_Deturpa( TAB_tppTabuleiro pTabuleiro, TAB_tpDeturpacao tipoDeturpacao );
    
  /***********************************************************************
  *
  *  $FC Função: TAB  &Verificar Estrutura do Tabuleiro
  *
  *  $ED Descrição da função
  *     Verifica a estrutura do tabuleiro.
  *     Especificamente, checa se linhas e colunas possuem 8 elementos e
  *     se o tipo armazenado por cada lista está correto.
  *
  *  $EP Par‚metros
  *     pTabuleiro - ponteiro para o tabuleiro a ser verificado
  *
  *  $FV Valor retornado
  *     TAB_CondRetOK                   - Nao foram encontradas falhas
  *     TAB_CondRetFalhaNaEstrutura     - Foram encontradas falhas
  *
  ***********************************************************************/

  TAB_tpCondRet TAB_VerificaAssertivasEstruturais( TAB_tppTabuleiro pTabuleiro );

#ifdef _DEBUG


/***********************************************************************
 *
 *  $FC Função: TAB  &Criar tabuleiro
 *
 *  $ED Descrição da função
 *     Cria um tabuleiro.
 *
 *  $EP Par‚metros
 *     pTabuleiro - ponteiro para o tabuleiro sendo criado
 *     pathConfig - local do arquivo de configuração de tabuleiro
 *
 *  $FV Valor retornado
 *     TAB_CondRetOK                - criou sem problemas
 *     TAB_CondRetFaltouMemoria     - faltou memória para alocação do tabuleiro
 *     TAB_CondRetFalhaArq          - falha ao manipular arquivo necessário
 *                                      para verificar o movimento
 *
 ***********************************************************************/

TAB_tpCondRet TAB_CriarTabuleiro( TAB_tppTabuleiro * pTabuleiro, char* pathConfig ) ;

/***********************************************************************
 *
 *  $FC Função: TAB  &Copiar tabuleiro
 *
 *  $ED Descrição da função
 *     Cria um tabuleiro igual ao tabuleiro original.
 *     O tabuleiro o qual deseja-se copiar não pode ser nulo.
 *
 *  $EP Parametros
 *     pTabuleiro - ponteiro para o tabuleiro sendo criado
 *     tabuleiroOriginal - tabuleiro original a ser copiado
 *
 *  $FV Valor retornado
 *     TAB_CondRetOK                - criou sem problemas
 *     TAB_CondRetFaltouMemoria     - faltou memória para alocação do tabuleiro
 *     TAB_CondRetFalhaArq          - falha ao manipular arquivo necessário
 *                                      para verificar o movimento
 *
 ***********************************************************************/

TAB_tpCondRet TAB_CopiarTabuleiro( TAB_tppTabuleiro * pTabuleiro, TAB_tppTabuleiro tabuleiroOriginal ) ;


/***********************************************************************
 *
 *  $FC Função: TAB  &Destruir tabuleiro
 *
 *  $ED Descrição da função
 *     Destrói o conteúdo de cada casa do tabuleiro e o próprio tabuleiro.
 *
 *  $EP Parâmetros
 *     pTabuleiro - ponteiro para o tabuleiro a ser destruído
 *
 *  $FV Valor retornado
 *     TAB_CondRetOK            - destruiu sem problemas
 *     TAB_CondRetNaoExiste     - o tabuleiro não existe
 *
 ***********************************************************************/

TAB_tpCondRet TAB_DestruirTabuleiro( TAB_tppTabuleiro pTabuleiro ) ;

/***********************************************************************
 *
 *  $FC Função: TAB  &Inserir peça no tabuleiro
 *
 *  $ED Descrição da função
 *     Insere a peça especificada no tabuleiro na posição também especificada.
 *     Caso exista uma peça na casa passada pelo ponteiro,
 *       ela será substituída pela passada pelos parâmetros.
 *
 *  $EP Parâmetros
 *     coluna     - coordenada da coluna onde a peça será inserida
 *     linha      - coordenada da linha onde a peça será inserida
 *     nomePeca   - identificador da peça que será inserida
 *     corPeca    - cor da peça que será inserida
 *     pTabuleiro - ponteiro para o tabuleiro onde a peça vai ser inserida
 *
 *  $FV Valor retornado
 *     TAB_CondRetOK                - inseriu sem problemas
 *     TAB_CondRetCoordNaoExiste    - coordenada não existe
 *     TAB_CondRetFaltouMemoria     - faltou memória para alocação do tabuleiro
 *
 ***********************************************************************/

TAB_tpCondRet TAB_InserirPecaTabuleiro( char coluna ,
                                        char linha ,
                                        char nomePeca ,
                                        char corPeca ,
                                        TAB_tppTabuleiro pTabuleiro ) ;

/***********************************************************************
 *
 *  $FC Função: TAB  &Mover peça no tabuleiro
 *
 *  $ED Descrição da função
 *     Move a peça presente na posição inicial especificada para
 *       a posição final também especificada.
 *
 *  $EP Parâmetros
 *     colInicial  - coordenada inicial da coluna da peça que será movida
 *     linInicial  - coordenada inicial da linha da peça que será movida
 *     colFinal    - coordenada final da coluna da peça que será movida
 *     linFinal    - coordenada final da linha da peça que será movida
 *     pTabuleiro  - ponteiro para o tabuleiro onde a peça vai ser movida
 *
 *  $FV Valor retornado
 *     TAB_CondRetOK                - moveu sem problemas
 *     TAB_CondRetCoordNaoExiste    - coordenada não existe
 *     TAB_CondRetMovInvalido       - o movimento indicado não é válido
 *     TAB_CondRetNaoExiste         - algum dos elementos usados não existe
 *     TAB_CondRetFalhaArq          - falha ao manipular arquivo necessário
 *                                      para verificar o movimento
 *     TAB_CondRetFaltouMemoria     - faltou memória para alocação da peça
 *
 ***********************************************************************/

TAB_tpCondRet TAB_MoverPecaTabuleiro(  char colInicial ,
                                       char linInicial ,
                                       char colFinal ,
                                       char linFinal ,
                                       TAB_tppTabuleiro pTabuleiro ) ;

/***********************************************************************
 *
 *  $FC Função: TAB  &Retirar peça do tabuleiro
 *
 *  $ED Descrição da função
 *     Retira a peça presente na posição especificada do tabuleiro.
 *
 *  $EP Parâmetros
 *     coluna     - coordenada da coluna onde a peça será retirada
 *     linha      - coordenada da linha onde a peça será retirada
 *     pTabuleiro - ponteiro para o tabuleiro onde a peça vai ser retirada
 *
 *  $FV Valor retornado
 *     TAB_CondRetOK                - retirou sem problemas
 *     TAB_CondRetNaoExiste         - não existe peça na posição
 *     TAB_CondRetCoordNaoExiste    - coordenada não existe
 *
 ***********************************************************************/

TAB_tpCondRet TAB_RetirarPecaTabuleiro( char coluna ,
                                        char linha ,
                                        TAB_tppTabuleiro pTabuleiro ) ;

/***********************************************************************
 *
 *  $FC Função: TAB  &Obter casa do tabuleiro
 *
 *  $ED Descrição da função
 *     Obtém a casa presente na posição especificada do tabuleiro.
 *
 *  $EP Parâmetros
 *     coluna      - coordenada da coluna onde a casa será obtida
 *     linha       - coordenada da linha onde a casa será obtida
 *     pCasa       - casa a ser obtida do tabuleiro
 *     pTabuleiro  - ponteiro para o tabuleiro onde a casa vai ser obtida
 *
 *  $FV Valor retornado
 *     TAB_CondRetOK                - obteve sem problemas
 *     TAB_CondRetNaoExiste         - não existe casa na posição
 *     TAB_CondRetCoordNaoExiste    - coordenada não existe
 *
 ***********************************************************************/

TAB_tpCondRet TAB_ObterCasaTabuleiro( char coluna ,
                                      char linha ,
                                      CSA_tppCasa * pCasa ,
                                      TAB_tppTabuleiro pTabuleiro ) ;

/***********************************************************************
 *
 *  $FC Função: TAB  &Obter peça do tabuleiro
 *
 *  $ED Descrição da função
 *     Obtém a peça presente na posição especificada do tabuleiro.
 *
 *  $EP Parâmetros
 *     coluna      - coordenada da coluna da casa onde a peça será obtida
 *     linha       - coordenada da linha da casa onde a peça será obtida
 *     pNomePeca   - ponteiro para o ponteiro referente ao nome da peça contida na casa
 *     pCorPeca    - ponteiro para o ponteiro referente à cor da peça contida na casa
 *     pTabuleiro  - ponteiro para o tabuleiro onde a peça vai ser obtida
 *
 *  $FV Valor retornado
 *     TAB_CondRetOK                - obteve sem problemas
 *     TAB_CondRetNaoExiste         - não existe peça na posição
 *     TAB_CondRetCoordNaoExiste    - coordenada não existe
 *
 ***********************************************************************/

TAB_tpCondRet TAB_ObterPecaTabuleiro( char coluna ,
                                      char linha ,
                                      char* pNomePeca ,
                                      char* pCorPeca ,
                                      TAB_tppTabuleiro pTabuleiro ) ;

/***********************************************************************
 *
 *  $FC Função: TAB  &Obter lista de ameaçantes de uma peça do tabuleiro
 *
 *  $ED Descrição da função
 *     Obtém a lista de ameaçantes da peça presente na posição especificada do tabuleiro.
 *
 *  $EP Parâmetros
 *     coluna              - coordenada da coluna da peça ameaçada
 *     linha               - coordenada da linha da peça ameaçada
 *     pListaAmeacantesLinhas    - ponteiro para onde a lista de linhas de casas ameaçantes será retornada
 *     pListaAmeacantesColunas    - ponteiro para onde a lista de colunas de ameaçantes será retornada
 *     pTabuleiro          - ponteiro para o tabuleiro onde a peça está sendo ameaçada
 *
 *  $FV Valor retornado
 *     TAB_CondRetOK                - obteve lista sem problemas
 *     TAB_CondRetNaoExiste         - não existe peça na posição
 *     TAB_CondRetCoordNaoExiste    - coordenada não existe
 *
 ***********************************************************************/

TAB_tpCondRet TAB_ObterListaAmeacantesTabuleiro( char coluna ,
                                                 char linha ,
                                                 LIS_tppLista * pListaAmeacantesLinhas ,
                                                 LIS_tppLista * pListaAmeacantesColunas ,
                                                 TAB_tppTabuleiro pTabuleiro ) ;

/***********************************************************************
 *
 *  $FC Função: TAB  &Obter lista de ameaçados de uma peça do tabuleiro
 *
 *  $ED Descrição da função
 *     Obtém a lista de ameaçados da peça presente na posição especificada do tabuleiro.
 *
 *  $EP Parâmetros
 *     coluna              - coordenada da coluna da peça ameaçante
 *     linha               - coordenada da linha da peça ameaçante
 *     pListaAmeacadosLinhas     - ponteiro para onde a lista de linhas de casas ameaçadas será retornada
 *     pListaAmeacadosColunas     - ponteiro para onde a lista de colunas de casas ameaçadas será retornada
 *     pTabuleiro          - ponteiro para o tabuleiro onde a peça está sendo ameaçando
 *
 *  $FV Valor retornado
 *     TAB_CondRetOK                - obteve lista sem problemas
 *     TAB_CondRetCoordNaoExiste    - coordenada não existe
 *
 ***********************************************************************/

TAB_tpCondRet TAB_ObterListaAmeacadosTabuleiro( char coluna ,
                                                char linha ,
                                                LIS_tppLista * pListaAmeacadosLinhas ,
                                                LIS_tppLista * pListaAmeacadosColunas ,
                                                TAB_tppTabuleiro pTabuleiro ) ;

/***********************************************************************
 *
 *  $FC Função: TAB  &Obter Casas Com Peça
 *
 *  $ED Descrição da função
 *     Obtém a lista de casas que possuem a peça definida pelos parâmetros peca e cor.
 *
 *  $EP Parâmetros
 *     pListaCasasLinhas              - lista com todas as linhas das casas com a peça definida
 *     pListaCasasColunas              - lista com todas as colunas das casas com a peça definida
 *     peca                     - nome da peça definida
 *     cor                      - cor da peça definida
 *     pTabuleiro               - ponteiro para o tabuleiro onde a peça está sendo ameaçando
 *
 *  $FV Valor retornado
 *     TAB_CondRetOK                - obteve lista sem problemas
 *
 ***********************************************************************/

TAB_tpCondRet TAB_ObterCasasComPeca( LIS_tppLista * pListaCasasLinhas ,
                                     LIS_tppLista * pListaCasasColunas ,
                                     char peca,
                                     char cor,
                                     TAB_tppTabuleiro pTabuleiro ) ;

/***********************************************************************
*
*  $FC Função: TAB  &Print Tabuleiro
*
*  $ED Descrição da função
*     Retorna a string (alocada dinamicamente) referente ao print do tabuleiro.
*     O tabuleiro o qual deseja-se obter o print não pode ser nulo.
*
*  $EP Parâmetros
*     pTabuleiro            - ponteiro para o tabuleiro
*     print                 - ponteiro para a string
*
*  $FV Valor retornado
*     TAB_CondRetOK             - nao ocorreram problemas
*     TAB_CondRetFaltouMemoria  - faltou memoria
*
***********************************************************************/

TAB_tpCondRet TAB_GetPrintTabuleiro( TAB_tppTabuleiro pTabuleiro, char** print ) ;

#undef TABULEIRO_EXT

/********** Fim do mÛdulo de definiÁ„o: TAB  Tabuleiro para jogo de xadrez **********/

#else
#endif

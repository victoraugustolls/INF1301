#if ! defined( TABULEIRO_ )
#define TABULEIRO_
/***************************************************************************
 *
 *  $MCD MÛdulo de definiÁ„o: TAB  Tabuleiro para jogo de xadrez
 *
 *  Arquivo gerado:              TABULEIRO.h
 *  Letras identificadoras:      TAB
 *
 *  Nome da base de software:    ArcabouÁo para a automaÁ„o de testes de programas redigidos em C
 *  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
 *
 *  Projeto: INF 1301 / 1628 AutomatizaÁ„o dos testes de mÛdulos C
 *  Gestor:  LES/DI/PUC-Rio
 *  Autores: lff
 *
 *  $HA HistÛrico de evoluÁ„o:
 *     Vers„o  Autor    Data     ObservaÁıes
 *     1       lff   04/out/2016 inÌcio desenvolvimento
 *
 *  $ED DescriÁ„o do mÛdulo
 *     Implementa um tabuleiro de xadrez composto por n casas.
 *     Pode existir apenas um tabuleiro em operação.
 *
 *     Cada tabuleiro é homogêneo quanto ao tipo dos dados que armazena.
 *     Cada elemento do tabuleiro referencia o valor que contÈm.
 *
 *     Os ponteiros para os dados s„o copiados para elementos do tabuleiro.
 *        N„o È copiado o valor apontado por estes ponteiros.
 *
 *     O controle da destruiÁ„o do valor de um elemento a ser excluÌdo
 *        È realizado por uma funÁ„o interna do módulo.
 *
 ***************************************************************************/

#if defined( TABULEIRO_OWN )
#define TABULEIRO_EXT
#else
#define TABULEIRO_EXT extern
#endif

/***** DeclaraÁıes exportadas pelo mÛdulo *****/

/* Tipo referÍncia para um tabuleiro */

typedef struct TAB_tagLista * TAB_tppTabuleiro ;


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
    
    TAB_CondRetOK ,
    /* Concluiu corretamente */
    
    TAB_CondRetNaoExiste ,
    /* O tabuleiro não existe */
    
    TAB_CondRetCoordJaPreenchida ,
    /* A coordenada do tabuleiro já está preenchida */
    
    TAB_CondRetCoordNaoExiste ,
    /* A coordenada não existe em tal tabuleiro */
    
    TAB_CondRetMovInvalido ,
    /* A coordenada não existe em tal tabuleiro */
    
    TAB_CondRetFaltouMemoria
    /* Faltou memória ao tentar criar um elemento de lista */
    
} TAB_tpCondRet ;


/***********************************************************************
 *
 *  $FC Função: TAB  &Criar tabuleiro
 *
 *  $ED Descrição da função
 *     Cria um tabuleiro.
 *
 *  $EP Par‚metros
 *     pTabuleiro - ponteiro para o tabuleiro sendo criado
 *
 *  $FV Valor retornado
 *     TAB_CondRetOK                - criou sem problemas
 *     TAB_CondRetFaltouMemoria     - faltou memória para alocação do tabuleiro
 *
 ***********************************************************************/

TAB_tpCondRet TAB_CriarTabuleiro( TAB_tppTabuleiro pTabuleiro ) ;


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
 *
 *  $EP Parâmetros
 *     coluna     - coordenada da coluna onde a peça será inserida
 *     linha      - coordenada da linha onde a peça será inserida
 *     idPeca     - identificador da peça que será inserida
 *     pTabuleiro - ponteiro para o tabuleiro onde a peça vai ser inserida
 *
 *  $FV Valor retornado
 *     TAB_CondRetOK                - inseriu sem problemas
 *     TAB_CondRetCoordJaPreenchida - coordenada já possui uma peça
 *     TAB_CondRetCoordNaoExiste    - coordenada não existe
 *     TAB_CondRetFaltouMemoria     - faltou memória para alocação do tabuleiro
 *
 ***********************************************************************/

TAB_tpCondRet TAB_InserirPecaTabuleiro( char coluna,
                                        int linha,
                                        char idPeca,
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
 *     TAB_CondRetOK                - inseriu sem problemas
 *     TAB_CondRetCoordNaoExiste    - coordenada não existe
 *     TAB_CondRetMovInvalido       - o movimento indicado não é válido
 *     TAB_CondRetFaltouMemoria     - faltou memória para alocação do tabuleiro
 *
 ***********************************************************************/

TAB_tpCondRet TAB_MoverPecaTabuleiro(  char colInicial,
                                       int linInicial,
                                       char colFinal,
                                       int linFinal,
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
 *     TAB_CondRetCoordNaoExiste    - coordenada não existe
 *
 ***********************************************************************/

TAB_tpCondRet TAB_RetirarPecaTabuleiro( char coluna,
                                        int linha,
                                        TAB_tppTabuleiro pTabuleiro ) ;

/***********************************************************************
 *
 *  $FC Função: TAB  &Obter peça do tabuleiro
 *
 *  $ED Descrição da função
 *     Obtém a peça presente na posição especificada do tabuleiro.
 *
 *  $EP Parâmetros
 *     coluna     - coordenada da coluna onde a peça será obtida
 *     linha      - coordenada da linha onde a peça será obtida
 *     idPeca     - identificador da peça a ser obtida do tabuleiro
 *     corPeca    - cor da peça a ser obtida do tabuleiro
 *     pTabuleiro - ponteiro para o tabuleiro onde a peça vai ser obtida
 *
 *  $FV Valor retornado
 *     TAB_CondRetOK                - obteve sem problemas
 *     TAB_CondRetCoordNaoExiste    - coordenada não existe
 *
 ***********************************************************************/

TAB_tpCondRet TAB_ObterPecaTabuleiro( char coluna,
                                        int linha,
                                        char idPeca,
                                        char corPeca,
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
 *     pListaAmeacantes    - ponteiro para onde a lista de ameaçantes será retornada
 *     pTabuleiro          - ponteiro para o tabuleiro onde a peça está sendo ameaçada
 *
 *  $FV Valor retornado
 *     TAB_CondRetOK                - obteve lista sem problemas
 *     TAB_CondRetCoordNaoExiste    - coordenada não existe
 *
 ***********************************************************************/

TAB_tpCondRet TAB_ObterListaAmeacantesTabuleiro( char coluna,
                                                 int linha,
                                                 LIS_tppLista pListaAmeacantes,
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
 *     pListaAmeacados     - ponteiro para onde a lista de ameaçados será retornada
 *     pTabuleiro          - ponteiro para o tabuleiro onde a peça está sendo ameaçando
 *
 *  $FV Valor retornado
 *     TAB_CondRetOK                - obteve lista sem problemas
 *     TAB_CondRetCoordNaoExiste    - coordenada não existe
 *
 ***********************************************************************/

TAB_tpCondRet TAB_ObterListaAmeacantesTabuleiro( char coluna,
                                                int linha,
                                                LIS_tppLista pListaAmeacados,
                                                TAB_tppTabuleiro pTabuleiro ) ;

#undef TABULEIRO_EXT

/********** Fim do mÛdulo de definiÁ„o: TAB  Tabuleiro para jogo de xadrez **********/

#else
#endif

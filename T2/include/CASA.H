#if ! defined( CASA_ )
#define CASA_
/***************************************************************************
 *
 *  $MCD Módulo de definição: CSA  Casa de um tabuleiro para jogo de xadrez
 *
 *  Arquivo gerado:              CASA.h
 *  Letras identificadoras:      CSA
 *
 *  Nome da base de software:    ArcabouÁo para a automaÁ„o de testes de programas redigidos em C
 *  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
 *
 *  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
 *  Gestor:  LES/DI/PUC-Rio
 *  Autores: lff
 *
 *  $HA Histórico de evolução:
 *     Versão  Autor    Data     Observações
 *     1       lff   04/out/2016 início desenvolvimento
 *
 *  $ED Descrição do módulo
 *     Implementa uma casa de um tabuleiro de xadrez.
 *     Podem existir n casas em operação.
 *
 *     Cada casa é homogênea quanto ao tipo dos dados que armazena.
 *     Cada elemento da casa referencia os valores que contém.
 *
 *     Os ponteiros para os dados são copiados para elementos da casa.
 *        Não é copiado o valor apontado por estes ponteiros.
 *
 *     O controle da destruição do valor de um elemento a ser excluÌdo
 *        È realizado por uma função interna do módulo.
 *
 *
 ***************************************************************************/

#if defined( CASA_OWN )
#define CASA_EXT
#else
#define CASA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referÍncia para um tabuleiro */

typedef struct CSA_tagCasa * CSA_tppCasa ;


/***********************************************************************
 *
 *  $TC Tipo de dados: CSA Condições de retorno
 *
 *
 *  $ED Descrição do tipo
 *     Condições de retorno das funções da casa
 *
 ***********************************************************************/

typedef enum {
    
    CSA_CondRetOK ,
    /* Concluiu corretamente */
    
    CSA_CondRetNaoExiste ,
    /* A casa não existe */
    
    CSA_CondRetFaltouMemoria
    /* Faltou memória ao tentar criar um elemento casa */
    
} CSA_tpCondRet ;


/***********************************************************************
 *
 *  $FC Função: CSA  &Criar casa
 *
 *  $ED Descrição da função
 *     Cria uma casa.
 *
 *  $EP Parâmetros
 *     pCasa - ponteiro para a casa sendo criado
 *
 *  $FV Valor retornado
 *     CSA_CondRetOK                - criou sem problemas
 *     CSA_CondRetFaltouMemoria     - faltou memória para alocação da casa
 *
 ***********************************************************************/

CSA_tpCondRet CSA_CriarCasa( CSA_tppTabuleiro pCasa ) ;


/***********************************************************************
 *
 *  $FC Função: CSA  &Destruir casa
 *
 *  $ED Descrição da função
 *     Destrói o conteúdo de uma casa.
 *
 *  $EP Parâmetros
 *     pCasa - ponteiro para a casa a ser destruída
 *
 *  $FV Valor retornado
 *     CSA_CondRetOK            - destruiu sem problemas
 *     CSA_CondRetNaoExiste     - a casa não existe
 *
 ***********************************************************************/

CSA_tpCondRet CSA_DestruirCasa( CSA_tppCasa pCasa ) ;

/***********************************************************************
 *
 *  $FC Função: CSA  &Inserir peça na casa
 *
 *  $ED Descrição da função
 *     Insere a peça especificada na casa recebida pelo ponteiro.
 *
 *  $EP Parâmetros
 *     idPeca     - identificador da peça que será inserida
 *     corPeca    - cor da peça que será inserida
 *     pCasa      - ponteiro para a casa onde a peça vai ser inserida
 *
 *  $FV Valor retornado
 *     CSA_CondRetOK                - inseriu sem problemas
 *     CSA_CondRetNaoExiste         - a casa não existe
 *     CSA_CondRetFaltouMemoria     - faltou memória para alocação da peça
 *
 ***********************************************************************/

CSA_tpCondRet CSA_InserirPecaCasa( char idPeca,
                                   char corPeca,
                                   CSA_tppTabuleiro pCasa ) ;

/***********************************************************************
 *
 *  $FC Função: CSA  &Retirar peça da casa
 *
 *  $ED Descrição da função
 *     Retira a peça presente na posição especificada do tabuleiro.
 *
 *  $EP Parâmetros
 *     pCasa   - ponteiro para a casa da qual a peça vai ser retirada
 *
 *  $FV Valor retornado
 *     CSA_CondRetOK            - retirou sem problemas
 *     CSA_CondRetNaoExiste     - a casa não existe
 *
 ***********************************************************************/

CSA_tpCondRet CSA_RetirarPecaCasa( CSA_tppCasa pCasa ) ;

/***********************************************************************
 *
 *  $FC Função: CSA  &Obter peça da casa
 *
 *  $ED Descrição da função
 *     Obtém a peça presente na casa passada pelo ponteiro.
 *
 *  $EP Parâmetros
 *     pIdPeca     - variável onde o identificador da peça será retornado
 *     pCorPeca    - variável onde a cor da peça será retornada
 *     pCasa       - ponteiro para a casa onde a peça vai ser obtida
 *
 *  $FV Valor retornado
 *     CSA_CondRetOK           - obteve sem problemas
 *     CSA_CondRetNaoExiste    - a casa não existe
 *
 ***********************************************************************/

CSA_tpCondRet CSA_ObterPecaCasa( char* pIdPeca,
                                 char* pCorPeca,
                                 CSA_tppCasa pCasa ) ;

/***********************************************************************
 *
 *  $FC Função: CSA  &Obter lista de ameaçantes de uma casa
 *
 *  $ED Descrição da função
 *     Obtém a lista de ameaçantes da peça presente na casa passada pelo ponteiro.
 *
 *  $EP Parâmetros
 *     pListaAmeacantes    - ponteiro para onde a lista de ameaçantes será retornada
 *     pCasa          - ponteiro para a casa onde a peça está sendo ameaçada
 *
 *  $FV Valor retornado
 *     CSA_CondRetOK           - obteve lista sem problemas
 *     CSA_CondRetNaoExiste    - a casa não existe
 *
 ***********************************************************************/

CSA_tpCondRet CSA_ObterListaAmeacantesCasa( LIS_tppLista pListaAmeacantes,
                                            CSA_tppCasa pCasa ) ;

/***********************************************************************
 *
 *  $FC Função: CSA  &Obter lista de ameaçados de uma casa
 *
 *  $ED Descrição da função
 *     Obtém a lista de ameaçados pela peça presente na casa passada pelo ponteiro.
 *
 *  $EP Parâmetros
 *     pListaAmeacados     - ponteiro para onde a lista de ameaçados será retornada
 *     pTabuleiro          - ponteiro para a casa onde a peça está sendo ameaçada
 *
 *  $FV Valor retornado
 *     CSA_CondRetOK           - obteve lista sem problemas
 *     CSA_CondRetNaoExiste    - a casa não existe
 *
 ***********************************************************************/

CSA_tpCondRet CSA_ObterListaAmeacadosCasa( LIS_tppLista pListaAmeacados,
                                           CSA_tppCasa pCasa ) ;

#undef CASA_EXT

/********** Fim do módulo de definição: CSA  Casa de um tabuleiro para jogo de xadrez **********/

#else
#endif

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
 *     4       vas   12/out/2016 corrigir esvaziar peça da casa
 *     3       lff   11/out/2016 adição de funções de modificar lista
 *     2       lff   10/out/2016 conserto de alguns erros
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

#include   "LISTA.H"

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
    
    CSA_CondRetOK = 0 ,
    /* Concluiu corretamente */
    
    CSA_CondRetNaoExiste = 1 ,
    /* A casa não existe */

    CSA_CondRetVazia = 2 ,
    /* A casa está vazia */
    
    CSA_CondRetFaltouMemoria = 3 ,
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

CSA_tpCondRet CSA_CriarCasa( CSA_tppCasa * pCasa ) ;


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
 *     Insere a peça especificada na casa passada pelo ponteiro.
 *
 *  $EP Parâmetros
 *     nomePeca   - identificador da peça que será inserida
 *     corPeca    - cor da peça que será inserida
 *     pCasa      - ponteiro para a casa onde a peça vai ser inserida
 *
 *  $FV Valor retornado
 *     CSA_CondRetOK                - inseriu sem problemas
 *     CSA_CondRetNaoExiste         - a casa não existe
 *     CSA_CondRetFaltouMemoria     - faltou memoria para inserir peça
 *
 ***********************************************************************/

CSA_tpCondRet CSA_InserirPecaCasa( char nomePeca ,
                                   char corPeca ,
                                   CSA_tppCasa pCasa ) ;

/***********************************************************************
 *
 *  $FC Função: CSA  &Retirar peça da casa
 *
 *  $ED Descrição da função
 *     Retira a peça presente na casa passada pelo ponteiro.
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
 *     pNomePeca   - ponteiro para o ponteiro referente ao nome da peça contina na casa
 *     pCorPeca    - ponteiro para o ponteiro referente à cor da peça contina na casa
 *     pCasa       - ponteiro para a casa onde a peça vai ser obtida
 *
 *  $FV Valor retornado
 *     CSA_CondRetOK           - obteve sem problemas
 *     CSA_CondRetNaoExiste    - a casa não existe
 *
 ***********************************************************************/

CSA_tpCondRet CSA_ObterPecaCasa( char** pNomePeca ,
                                 char** pCorPeca ,
                                 CSA_tppCasa pCasa ) ;

/***********************************************************************
 *
 *  $FC Função: CSA  &Comparar casas
 *
 *  $ED Descrição da função
 *     Compara as casas passadas nos parâmetros e 
 *      retorna (através de outro parâmetro) 1, se forem iguais, e 0, se diferentes.
 *
 *  $EP Parâmetros
 *     pCasa1             - ponteiro para a primeira casa da comparacao
 *	   pCasa2             - ponteiro para a segunda casa da comparacao
 *     igualdade          - ponteiro para o valor da igualdade
 *
 *  $FV Valor retornado
 *     CSA_CondRetOK            - comparou sem problemas
 *     CSA_CondRetNaoExiste     - a casa não existe
 *
 ***********************************************************************/

CSA_tpCondRet CSA_CompararCasa( CSA_tppCasa pCasa1 ,
								CSA_tppCasa pCasa2 ,
								int * igualdade ) ;

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
 *	   CSA_CondRetVazia        - a casa esta vazia
 *
 ***********************************************************************/

CSA_tpCondRet CSA_ObterListaAmeacantesCasa( LIS_tppLista * pListaAmeacantes ,
                                            CSA_tppCasa pCasa ) ;

/***********************************************************************
 *
 *  $FC Função: CSA  &Obter lista de ameaçados de uma casa
 *
 *  $ED Descrição da função
 *     Obtém a lista de ameaçados pela peça presente na casa passada pelo ponteiro.
 *
 *  $EP Parâmetros
 *     pListaAmeacados  - ponteiro para onde a lista de ameaçados será retornada
 *     pCasa            - ponteiro para a casa onde a peça está sendo ameaçada
 *
 *  $FV Valor retornado
 *     CSA_CondRetOK           - obteve lista sem problemas
 *     CSA_CondRetNaoExiste    - a casa não existe
 *
 ***********************************************************************/

CSA_tpCondRet CSA_ObterListaAmeacadosCasa( LIS_tppLista * pListaAmeacados ,
                                           CSA_tppCasa pCasa ) ;

/***********************************************************************
 *
 *  $FC Função: CSA  &Modificar lista de ameaçantes de uma casa
 *
 *  $ED Descrição da função
 *     Modifica a lista de ameaçantes (a peça presente na casa passada pelo ponteiro) adicionando a ela as casas passadas pelo array.
 *
 *  $EP Parâmetros
 *     vetorCasasAmeacantes - vetor de casas ameaçantes a casa passada pelo ponteiro pCasa
 *     qtdCasasAmeacantes  - quantidade de casas no vetor
 *     pCasa                - ponteiro para a casa onde a peça está sendo ameaçada
 *
 *  $FV Valor retornado
 *     CSA_CondRetOK           - modificou lista sem problemas
 *     CSA_CondRetNaoExiste    - a casa não existe
 *
 ***********************************************************************/

CSA_tpCondRet CSA_ModificarListaAmeacantesCasa( CSA_tppCasa * vetorCasasAmeacantes ,
                                                int qtdCasasAmeacantes ,
                                                CSA_tppCasa pCasa ) ;

/***********************************************************************
 *
 *  $FC Função: CSA  &Modificar lista de ameaçados de uma casa
 *
 *  $ED Descrição da função
 *     Modifica a lista de ameaçados (pela peça presente na casa passada pelo ponteiro) adicionando a ela as casas passadas pelo array.
 *
 *  $EP Parâmetros
 *     vetorCasasAmeacadas - vetor de casas ameaçadas pela casa passada pelo ponteiro pCasa
 *     qtdCasasAmeacadas   - quantidade de casas no vetor
 *     pCasa               - ponteiro para a casa onde a peça está ameaçando
 *
 *  $FV Valor retornado
 *     CSA_CondRetOK           - modificou lista sem problemas
 *     CSA_CondRetNaoExiste    - a casa não existe
 *
 ***********************************************************************/

CSA_tpCondRet CSA_ModificarListaAmeacadosCasa( CSA_tppCasa * vetorCasasAmeacadas ,
                                               int qtdCasasAmeacadas ,
                                               CSA_tppCasa pCasa ) ;

#undef CASA_EXT

/********** Fim do módulo de definição: CSA  Casa de um tabuleiro para jogo de xadrez **********/

#else
#endif

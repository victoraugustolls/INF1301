#if ! defined( JOGO_ )
#define JOGO_
/***************************************************************************
 *
 *  $MCD MÛdulo de definiÁ„o: JGO  Juiz para jogo de xadrez
 *
 *  Arquivo gerado:              JOGO.H
 *  Letras identificadoras:      JGO
 *
 *  Projeto: INF 1301 / 1628 AutomatizaÁ„o dos testes de mÛdulos C
 *  Gestor:  LES/DI/PUC-Rio
 *  Autores: lff
 *
 *  $HA HistÛrico de evoluÁ„o:
 *     Vers„o  Autor    Data     ObservaÁıes
 *     1       lff   29/out/2016 inÌcio desenvolvimento
 *
 *  $ED DescriÁ„o do mÛdulo
 *     Implementa um juiz de jogo de xadrez.
 *     Pode existir apenas um juiz em operação.
 *
 *     O Juiz manipula as peças do jogo e apresenta 
 *       a lista dos ameaçantes e ameaçados da peça movimentada.
 *
 *     O controle da destruiÁ„o do valor de um elemento a ser excluÌdo
 *        È realizado por uma funÁ„o interna do módulo.
 *
 *
 ***************************************************************************/

#if defined( JOGO_OWN )
#define JOGO_EXT
#else
#define JOGO_EXT extern
#endif

/***** DeclaraÁıes exportadas pelo mÛdulo *****/

/* Tipo referÍncia para um tabuleiro */

typedef struct JGO_tagJuiz * JGO_tppJuiz ;

/***********************************************************************
 *
 *  $TC Tipo de dados: JGO Condições de retorno
 *
 *
 *  $ED Descrição do tipo
 *     Condições de retorno das funções do juiz
 *
 ***********************************************************************/

typedef enum {
    
    JGO_CondRetOK = 0 ,
    /* Concluiu corretamente */
    
    JGO_CondRetNaoExiste = 1 ,
    /* O juiz ou algum dos componentes do jogo não existe */
    
    JGO_CondRetCoordNaoExiste = 2 ,
    /* A coordenada não existe em tal jogo */
    
    JGO_CondRetMovInvalido = 3 ,
    /* O movimento não é válido em tal jogo */
    
    JGO_CondRetJaCriado = 6 ,
    /* Já existe juiz em operação */

} JGO_tpCondRet ;

/***********************************************************************
 *
 *  $FC Função: JGO  &Criar juiz
 *
 *  $ED Descrição da função
 *     Cria um novo juiz de xadrez.
 *
 *  $EP Par‚metros
 *     pJuiz - ponteiro para o juiz a ser criado
 *
 *  $FV Valor retornado
 *     JGO_CondRetOK                - criou sem problemas
 *     JGO_CondRetFaltouMemoria     - faltou memória para criar o juiz
 *
 ***********************************************************************/

JGO_tpCondRet JGO_CriarJuiz( JGO_tppJuiz * pJuiz ) ;


/***********************************************************************
 *
 *  $FC Função: JGO  &Destruir juiz
 *
 *  $ED Descrição da função
 *     Destrói o juiz de xadrez.
 *
 *  $EP Par‚metros
 *     pJuiz - ponteiro para o juiz a ser destruído
 *
 *  $FV Valor retornado
 *     JGO_CondRetOK                - destruiu sem problemas
 *     JGO_CondRetNaoExiste         - o juiz não existe
 *
 ***********************************************************************/

JGO_tpCondRet JGO_DestruirJuiz( JGO_tppJuiz pJuiz ) ;


/***********************************************************************
 *
 *  $FC Função: JGO  &Iniciar jogo
 *
 *  $ED Descrição da função
 *     Inicia um novo jogo entre dois jogadores.
 *
 *  $EP Par‚metros
 *     pJuiz - ponteiro para o juiz a iniciar o jogo
 *
 *  $FV Valor retornado
 *     JGO_CondRetOK                - iniciou sem problemas
 *     JGO_CondRetFaltouMemoria     - faltou memória para iniciar o jogo
 *
 ***********************************************************************/

JGO_tpCondRet JGO_IniciarJogo( JGO_tppJuiz pJuiz ) ;


/***********************************************************************
 *
 *  $FC Função: JGO  &Terminar jogo
 *
 *  $ED Descrição da função
 *     Termina o jogo.
 *
 *  $EP Parâmetros
 *     pJuiz - ponteiro para o juiz a terminar o jogo
 *
 *  $FV Valor retornado
 *     JGO_CondRetOK            - terminou sem problemas
 *     JGO_CondRetNaoExiste     - o jogo não existe
 *
 ***********************************************************************/

JGO_tpCondRet JGO_TerminarJogo( JGO_tppJuiz pJuiz ) ;


/***********************************************************************
 *
 *  $FC Função: JGO  &Realizar jogada
 *
 *  $ED Descrição da função
 *     Apresenta o tabuleiro na tela e pede para um dos jogadores
 *      realizar o movimento de uma de suas peças. Após o movimento da peça,
 *      apresenta quais ela está ameaçando e quais a estão ameaçando.
 *
 *  $EP Parâmetros
 *     pJuiz - ponteiro para o juiz a terminar o jogo
 *
 *  $FV Valor retornado
 *     JGO_CondRetOK            - realizou sem problemas
 *     JGO_CondRetNaoExiste     - o jogo não existe
 *
 ***********************************************************************/

JGO_tpCondRet JGO_RealizarJogada( JGO_tppJuiz pJuiz ) ;

#undef JOGO_EXT

/********** Fim do mÛdulo de definiÁ„o: JGO  Juiz para jogo de xadrez **********/

#else
#endif

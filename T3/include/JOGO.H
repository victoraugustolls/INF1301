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
    
    JGO_CondRetJaCriado = 4,
    /* Já existe juiz em operação */

    JGO_CondRetFaltouMemoria = 5
    /* Faltou memória */

} JGO_tpCondRet ;

/***********************************************************************
 *
 *  $TC Tipo de dados: JGO Cores dos Jogadores
 *
 *
 *  $ED Descrição do tipo
 *     Cores referentes aos dois tipos de jogadores do jogo: branco e preto
 *
 ***********************************************************************/

typedef enum {
    
    JGO_JogadorPreto = 0 ,
    /* Cor do jogador preto */

    JGO_JogadorBranco = 1
    /* Cor do jogador branco */

} JGO_tpCorJogador ;

/***********************************************************************
 *
 *  $TC Tipo de dados: JGO Eventos do Jogo
 *
 *
 *  $ED Descrição do tipo
 *     Eventos que podem ocorrer durante o movimento de uma peça
 *
 ***********************************************************************/

typedef enum {
    
    JGO_Nenhum = 0 ,
    /* Não ocorreu nenhum evento */

    JGO_Cheque = 1,
    /* Ocorreu um cheque com a jogada */

    JGO_ChequeMate = 2
    /* Ocorreu um cheque-mate com a jogada */

} JGO_tpEventoOcorrido ;


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
 *     JGO_CondRetJaCriado          - já existe juiz em operação
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
 *     corJogadorAtual - a cor do jogador da vez
 *     eventoOcorrido - evento que ocorreu durante a jogada dada
 *     linhaCasaAtual - a linha da casa atual da peça sendo movida
 *     colunaCasaAtual - a coluna da casa atual da peça sendo movida
 *     linhaCasaDestino - a linha da casa atual da peça sendo movida
 *     colunaCasaDestino - a coluna da casa atual da peça sendo movida
 *
 *  $FV Valor retornado
 *     JGO_CondRetOK            - realizou sem problemas
 *     JGO_CondRetNaoExiste     - o jogo não existe
 *     JGO_CondRetMovInvalido - o movimento solicitado nao é valido
 *
 ***********************************************************************/

JGO_tpCondRet JGO_RealizarJogada( JGO_tppJuiz pJuiz, JGO_tpCorJogador corJogadorAtual,
                                                     JGO_tpEventoOcorrido* eventoOcorrido,
                                                     char linhaCasaAtual,
                                                     char colunaCasaAtual,
                                                     char linhaCasaDestino,
                                                     char colunaCasaDestino ) ;

#undef JOGO_EXT

/********** Fim do mÛdulo de definiÁ„o: JGO  Juiz para jogo de xadrez **********/

#else
#endif

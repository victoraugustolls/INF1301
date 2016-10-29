#if ! defined( JUIZ_ )
#define JUIZ_
/***************************************************************************
 *
 *  $MCD MÛdulo de definiÁ„o: JUZ  Juiz para jogo de xadrez
 *
 *  Arquivo gerado:              JUIZ.H
 *  Letras identificadoras:      JUZ
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

#if defined( JUIZ_OWN )
#define JUIZ_EXT
#else
#define JUIZ_EXT extern
#endif

/***** DeclaraÁıes exportadas pelo mÛdulo *****/

/* Tipo referÍncia para um tabuleiro */

typedef struct JUZ_tagJuiz * JUZ_tppJuiz ;

/***********************************************************************
 *
 *  $TC Tipo de dados: JUZ Condições de retorno
 *
 *
 *  $ED Descrição do tipo
 *     Condições de retorno das funções do juiz
 *
 ***********************************************************************/

typedef enum {
    
    JUZ_CondRetOK = 0 ,
    /* Concluiu corretamente */
    
    JUZ_CondRetNaoExiste = 1 ,
    /* O juiz ou algum dos componentes do jogo não existe */
    
    JUZ_CondRetCoordNaoExiste = 2 ,
    /* A coordenada não existe em tal jogo */
    
    JUZ_CondRetMovInvalido = 3 ,
    /* O movimento não é válido em tal jogo */
    
    JUZ_CondRetJaCriado = 6 ,
    /* Já existe juiz em operação */

} JUZ_tpCondRet ;

/***********************************************************************
 *
 *  $FC Função: TAB  &Criar juiz
 *
 *  $ED Descrição da função
 *     Cria um novo juiz de xadrez.
 *
 *  $EP Par‚metros
 *     pJuiz - ponteiro para o juiz a ser criado
 *
 *  $FV Valor retornado
 *     JUZ_CondRetOK                - criou sem problemas
 *     JUZ_CondRetFaltouMemoria     - faltou memória para criar o juiz
 *
 ***********************************************************************/

JUZ_tpCondRet JUZ_CriarJuiz( JUZ_tppJuiz * pJuiz ) ;


/***********************************************************************
 *
 *  $FC Função: TAB  &Destruir juiz
 *
 *  $ED Descrição da função
 *     Destrói o juiz de xadrez.
 *
 *  $EP Par‚metros
 *     pJuiz - ponteiro para o juiz a ser destruído
 *
 *  $FV Valor retornado
 *     JUZ_CondRetOK                - destruiu sem problemas
 *     JUZ_CondRetNaoExiste         - o juiz não existe
 *
 ***********************************************************************/

JUZ_tpCondRet JUZ_DestruirJuiz( JUZ_tppJuiz pJuiz ) ;


/***********************************************************************
 *
 *  $FC Função: TAB  &Iniciar jogo
 *
 *  $ED Descrição da função
 *     Inicia um novo jogo entre dois jogadores.
 *
 *  $EP Par‚metros
 *     pJuiz - ponteiro para o juiz a iniciar o jogo
 *
 *  $FV Valor retornado
 *     JUZ_CondRetOK                - iniciou sem problemas
 *     JUZ_CondRetFaltouMemoria     - faltou memória para iniciar o jogo
 *
 ***********************************************************************/

JUZ_tpCondRet JUZ_IniciarJogo( JUZ_tppJuiz pJuiz ) ;


/***********************************************************************
 *
 *  $FC Função: TAB  &Terminar jogo
 *
 *  $ED Descrição da função
 *     Termina o jogo.
 *
 *  $EP Parâmetros
 *     pJuiz - ponteiro para o juiz a terminar o jogo
 *
 *  $FV Valor retornado
 *     JUZ_CondRetOK            - terminou sem problemas
 *     JUZ_CondRetNaoExiste     - o jogo não existe
 *
 ***********************************************************************/

JUZ_tpCondRet JUZ_TerminarJogo( JUZ_tppJuiz pJuiz ) ;


/***********************************************************************
 *
 *  $FC Função: TAB  &Realizar jogada
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
 *     JUZ_CondRetOK            - realizou sem problemas
 *     JUZ_CondRetNaoExiste     - o jogo não existe
 *
 ***********************************************************************/

JUZ_tpCondRet JUZ_RealizarJogada( JUZ_tppJuiz pJuiz ) ;

#undef JUIZ_EXT

/********** Fim do mÛdulo de definiÁ„o: JUZ  Juiz para jogo de xadrez **********/

#else
#endif

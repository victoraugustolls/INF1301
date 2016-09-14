#if ! defined( ETIQUETA_NOMINAL_ )
#define ETIQUETA_NOMINAL_

/***************************************************************************
*
*  $MCD Módulo de definição: ETI
*
*  Arquivo gerado:              ETIQUETA_NOMINAL.h
*  Letras identificadoras:      ETI
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: vas, lff
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     2       lff   14/set/2016 implementação das funções de impressão e comparação
*     1       vas   13/set/2016 início desenvolvimento
*
*  $ED Descrição do módulo
*
*
***************************************************************************/

#if defined( ETIQUETA_NOMINAL_OWN )
  #define ETIQUETA_NOMINAL_EXT
#else
  #define ETIQUETA_NOMINAL_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

typedef struct ETI_tagEtiquetaNominal * ETI_tppEtiquetaNominal ;


/***********************************************************************
*
*  $FC Função: ETI  &Criar etiqueta nominal
*
*  $ED Descrição da função
*     Cria uma etiqueta nominal contendo as iniciais e o nome.
*
*  $EP Parâmetros
*     pIniciais      - inicial da pessoa em questão
*     pNomeCompleto  - nome completo da pessoa em questão
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a etiqueta nominal.
*     Este ponteiro será utilizado pelas funções que manipulem esta etiqueta nominal.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

ETI_tppEtiquetaNominal ETI_CriarEtiquetaNominal( char* pIniciais, char* pNomeCompleto ) ;


/***********************************************************************
*
*  $FC Função: ETI  &Destruir etiqueta nominal
*
*  $ED Descrição da função
*     Destrói a etiqueta nominal fornecida.
*     O parâmetro ponteiro para a etiqueta nominal não é modificado.
*     Se ocorrer algum erro durante a destruição, a etiqueta nominal resultará
*     estruturalmente incorreta.
*     Obs.: não existe previsão para possíveis falhas de execução.
*
*  $EP Parâmetros
*      pEtiquetaNominal - ponteiro para etiqueta nominal que será destruída.
*
*
***********************************************************************/

void ETI_DestruirEtiquetaNominal( ETI_tppEtiquetaNominal pEtiquetaNominal ) ;

/***********************************************************************
 *
 *  $FC Função: ETI  &Imprimir conteúdo etiqueta nominal
 *
 *  $ED Descrição da função
 *     Imprime o conteúdo da etiqueta nominal fornecida.
 *     O parâmetro ponteiro para a etiqueta nominal não é modificado.
 *     Se ocorrer algum erro durante a impressão, a etiqueta nominal resultará
 *     estruturalmente incorreta.
 *     Obs.: não existe previsão para possíveis falhas de execução.
 *
 *  $EP Parâmetros
 *      pEtiquetaNominal - ponteiro para etiqueta nominal que será imprimida.
 *
 *
 ***********************************************************************/

void ETI_ImprimirConteudoEtiquetaNominal( ETI_tppEtiquetaNominal pEtiquetaNominal ) ;

/***********************************************************************
 *
 *  $FC Função: ETI  &Comparar as iniciais de duas etiquetas nominais
 *
 *  $ED Descrição da função
 *     Compara o membro 'iniciais' da primeira etiqueta nominal fornecida com o da segunda.
 *     Os parâmetros ponteiros e seus membros  para a etiquetas nominais não são modificados.
 *
 *  $EP Parâmetros
 *      pEtiquetaNominal1 - ponteiro para a primeira etiqueta nominal que será comparada.
 *      pEtiquetaNominal2 - ponteiro para a segunda etiqueta nominal que será comparada.
 *
 *  $FV Valor retornado
 *        -1 - pEtiquetaNominal1 vem antes de pEtiquetaNominal2 em uma ordenação alfanumérica
 *             de acordo com o membro 'iniciais' da etiqueta nominal.
 *        0 - pEtiquetaNominal1 vem na mesma posição de pEtiquetaNominal2 em uma ordenação alfanumérica
 *             de acordo com o membro 'iniciais' da etiqueta nominal.
 *        1 - pEtiquetaNominal1 vem depois de pEtiquetaNominal2 em uma ordenação alfanumérica
 *             de acordo com o membro 'iniciais' da etiqueta nominal.
 *        Se algum dos parâmetros for NULL, ele virá antes do não NULL. Logo, caso pEtiquetaNominal1
 *        seja NULL, a função retornará -1, e caso pEtiquetaNominal2 seja NULL, a função retornará 1.
 *        Caso os dois sejam NULL, a função retornará -1.
 *
 ***********************************************************************/

int ETI_CompararIniciaisEtiquetaNominal( ETI_tppEtiquetaNominal pEtiquetaNominal1, ETI_tppEtiquetaNominal pEtiquetaNominal2 ) ;

/***********************************************************************
 *
 *  $FC Função: ETI  &Comparar conteúdo de duas etiquetas nominais
 *
 *  $ED Descrição da função
 *     Compara o conteúdo das duas etiquetas nominais recebidas como parâmetros.
 *     Os parâmetros ponteiros e seus membros  para a etiquetas nominais não são modificados.
 *
 *  $EP Parâmetros
 *      pEtiquetaNominal1 - ponteiro para a primeira etiqueta nominal que será comparada.
 *      pEtiquetaNominal2 - ponteiro para a segunda etiqueta nominal que será comparada.
 *
 *  $FV Valor retornado
 *        0 - pEtiquetaNominal1 não possui o mesmo conteúdo de pEtiquetaNominal2.
 *        1 - pEtiquetaNominal1 possui o mesmo conteúdo depois de pEtiquetaNominal2.
 *
 ***********************************************************************/

int ETI_CompararConteudoEtiquetaNominal(ETI_tppEtiquetaNominal pEtiquetaNominal1, ETI_tppEtiquetaNominal pEtiquetaNominal2) ;


#undef ETIQUETA_NOMINAL_EXT

/********** Fim do módulo de definição: ETI Etiqueta nominal **********/

#else
#endif

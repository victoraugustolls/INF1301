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
*  Autores: vas
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
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
*  $TC Tipo de dados: LIS Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

typedef enum {

      ETI_CondRetOK ,
            /* Concluiu corretamente */

      ETI_CondRetListaVazia ,
            /* A lista n�o cont�m elementos */

      ETI_CondRetFimLista ,
            /* Foi atingido o fim de lista */

      ETI_CondRetNaoAchou ,
            /* N�o encontrou o valor procurado */

      ETI_CondRetFaltouMemoria
            /* Faltou mem�ria ao tentar criar um elemento de lista */

} ETI_tpCondRet ;

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

ETI_tppEtiquetaNominal ETI_CriarEtiquetaNominal(char* pIniciais, char* pNomeCompleto);


/***********************************************************************
*
*  $FC Função: ETI  &Destruir etiqueta nominal
*
*  $ED Descrição da função
*     Destrói a etiqueta nominal fornecida.
*     O parâmetro ponteiro para a etiqueta nominal não é modificado.
*     Se ocorrer algum erro durante a destruição, a etiqueta nominal resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $EP Parâmetros
*      pEtiquetaNominal - ponteiro para etiqueta nominal que será desctuída
*
*  $FV Valor retornado
*     LIS_CondRetOK     - destruiu sem problemas
*
***********************************************************************/

void EIT_DestruirEtiquetaNominal( ETI_tppEtiquetaNominal pEtiquetaNominal ) ;

#undef ETIQUETA_NOMINAL_EXT

/********** Fim do módulo de definição: ETI Etiqueta nominal **********/

#else
#endif

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
*     1       avs   04/out/2016 início desenvolvimento
*
*  $ED Descrição do módulo
*     TODO
*
***************************************************************************/

#if defined( VALIDA_MOV_OWN )
   #define VALIDA_MOV_EXT
#else
   #define VALIDA_MOV_EXT extern
#endif

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

         VMV_CondRetErrLeituraArquivo = 1 ,
               /* Ocorreu um erro na leitura do arquivo */

   } VMV_tpCondRet ;


/***********************************************************************
*
*  $FC Função: VMV  &Criar lista
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*
*     pLista          - ponteiro para a lista sendo criada
*     idLista         - id da lista sendo criada
*     ExcluirValor    - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*     ImprimirValor   - ponteiro para a função que imprime o valor
*                     referenciado pelo módulo.
*                     Ver descrição do módulo.
*     CompararValores - ponteiro para a função que compara o valor
*                     de dois elementos. Deve retornar -1, 0 ou 1.
*                     Ver descrição do módulo.
*     Igual           - ponteiro para a função que compara se o valor
*                     de dois elementos é igual.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     VMV_CondRetOK            - lista foi criada corretamente
*     VMV_CondRetFaltouMemoria - ocorreu um erro na criação da lista
*
***********************************************************************/

   VMV_tpCondRet VMV_CriarLista( VMV_tppLista pLista ,
             char * idLista ,

             void   ( * ExcluirValor ) ( void * pDado ) ,

             int   ( * CompararValores ) ( void * pDado_1, void * pDado_2 ) ,

             int   ( * Igual ) ( void * pDado_1, void * pDado_2 ) ) ;


/***********************************************************************
*
*  $FC Função: VMV  &Destruir lista
*
*  $ED Descrição da função
*     Destrói a lista fornecida.
*     O parâmetro ponteiro para a lista não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $FV Valor retornado
*     VMV_CondRetOK             - destruiu sem problemas
*     VMV_CondRetListaNaoExiste - lista não existe
*
***********************************************************************/

   VMV_tpCondRet VMV_DestruirLista( VMV_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: VMV  &Inserir elemento após
*
*  $ED Descrição da função
*     Insere novo elemento após o elemento corrente.
*     O elemento corrente passará a ser o novo elemento inserido.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     Parâmetros
*        pLista - ponteiro para a lista onde deve ser inserido o elemento
*        pValor - ponteiro para o valor do novo elemento
*                 Pode ser NULL
*           
*
*  $FV Valor retornado
*     Valor retornado
*        VMV_CondRetOK
*        VMV_CondRetFaltouMemoria
*
***********************************************************************/

   VMV_tpCondRet VMV_InserirElementoApos( VMV_tppLista pLista ,
                                          void * pValor        ) ;


/***********************************************************************
*
*  $FC Função: VMV  &Excluir elemento
*
*  $ED Descrição da função
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente será o novo corrente.
*     Se não existir e existir o elemento à direita, este se tornará corrente.
*     Se este também não existir a lista tornou-se vazia.
*
*  $EP Parâmetros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     VMV_CondRetOK
*     VMV_CondRetListaVazia
*
***********************************************************************/

   VMV_tpCondRet VMV_ExcluirElemento( VMV_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: VMV  &Obter referência para o valor contido no elemento
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido no elemento corrente da lista
*
*  $EP Parâmetros
*     pLista           - ponteiro para a lista de onde se quer o valor
*     elementoCorrente - ponteiro para o valor do nó corrente. Pode ser NULL.
*
*  $FV Valor retornado
*     VMV_CondRetOK
*     VMV_CondRetListaVazia
*
***********************************************************************/

   VMV_tpCondRet VMV_ObterValor( VMV_tppLista pLista ,
                                 void * elementoCorrente ) ;


/***********************************************************************
*
*  $FC Função: VMV  &Obter identificador na cabeça da lista
*
*  $ED Descrição da função
*     Obtem a identificação na cabeça da lista
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista de onde se quer o valor
*     idLista - ponteiro para o valor do id da lista
*
*  $FV Valor retornado
*     VMV_CondRetOK
*
***********************************************************************/

   VMV_tpCondRet VMV_ObterId( VMV_tppLista pLista ,
                              char * idLista ) ;


/***********************************************************************
*
*  $FC Função: VMV  &Avançar elemento
*
*  $ED Descrição da função
*     Avança o elemento corrente numElem elementos na lista
*     Se numElem for positivo avança em direção ao final
*     Se numElem for negativo avança em direção ao início
*     numElem pode ser maior do que o númro de elementos existentes na
*               direção desejada
*     Se numElem for zero somente verifica se a lista está vazia
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o número de elementos a andar
*
*  $FV Valor retornado
*     VMV_CondRetOK             - se numElem elementos tiverem sido andados
*     VMV_CondRetNoCorrenteUlt  - chegou ao final da lista antes de avançar
*                               para o próximo elemento
*     VMV_CondRetNoCorrentePrim - chegou no começo da lista antes de retornar
*                               para o elemento anterior
*     VMV_CondRetListaVazia     - se a lista está vazia
*
***********************************************************************/

   VMV_tpCondRet VMV_AvancarElementoCorrente( VMV_tppLista pLista ,
                                              int numElem ) ;


/***********************************************************************
*
*  $FC Função: VMV  &Altera conteudo do nó corrente
*
*  $ED Descrição da função
*     Altera o valor do nó corrente da lista para novo valor.
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*     pValor  - ponteiro para o novo valor do nó corrente
*               Pode ser NULL
*
*  $FV Valor retornado
*     VMV_CondRetOK             - alteração bem sucedida
*     VMV_CondRetListaVazia     - se a lista estiver vazia
*     VMV_CondRetListaNaoExiste - se a lista não existir
*
***********************************************************************/

   VMV_tpCondRet VMV_AlteraValor( VMV_tppLista pLista ,
                                  void * pValor ) ;

#undef VALIDA_MOV_EXT

/********** Fim do módulo de definição: VMV  Lista duplamente encadeada **********/

#else
#endif

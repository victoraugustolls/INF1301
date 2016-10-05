#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD Módulo de definição: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs, iars, vas
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     6       vas   03/out/2016 ajuste das funções para todas terem condições de retorno
*                               e retirada de funções não utilizadas
*     5       iars  14/set/2016 inserção ordenada, procurar valor, imprimir
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa listas genéricas duplamente encadeadas.
*     Podem existir n listas em operação simultaneamente.
*     As listas possuem uma cabeça encapsulando o seu estado.
*
*     Cada lista é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da lista.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*
*     Cada lista referencia uma função que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da lista seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
*     Também devem ser fornecidas uma função de comparação de elementos, uma
*        função que diz quando dois elementos são iguais e uma função que
*        imprime o conteúdo de um elemento.
*
*     A função de comparação deve receber dois elementos e retornar -1, 0 ou 1
*        caso o primeiro elemento deva ser ordenado antes, igualmente ou após
*        o segundo elemento, respectivamente.
*
*     A função de igualdade deve receber dois valores e retornar 0 caso sejam diferentes
*        ou um inteiro diferente de zero caso sejam iguais.
*
***************************************************************************/

#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


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

         LIS_CondRetOK = 0 ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia = 2 ,
               /* A lista não contém elementos */

         LIS_CondRetListaNaoExiste = 3 ,
               /* A lista não existe */

         LIS_CondRetNoCorrenteUlt = 4 ,
               /* Nó corrente é o último */

         LIS_CondRetNoCorrentePrim = 5 ,
               /* Nó corrente é o primeiro */

         LIS_CondRetFaltouMemoria = 6 ,
               /* Faltou memória ao tentar criar um elemento de lista */

   } LIS_tpCondRet ;


/***********************************************************************
*
*  $FC Função: LIS  &Criar lista
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
*     LIS_CondRetOK            - lista foi criada corretamente
*     LIS_CondRetFaltouMemoria - ocorreu um erro na criação da lista
*
***********************************************************************/

   LIS_tpCondRet LIS_CriarLista( LIS_tppLista* pLista ,
             char * idLista ,

             void   ( * ExcluirValor ) ( void * pDado ) ,

             int   ( * CompararValores ) ( void * pDado_1, void * pDado_2 ) ,

             int   ( * Igual ) ( void * pDado_1, void * pDado_2 ) ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Destruir lista
*
*  $ED Descrição da função
*     Destrói a lista fornecida.
*     O parâmetro ponteiro para a lista não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $FV Valor retornado
*     LIS_CondRetOK             - destruiu sem problemas
*     LIS_CondRetListaNaoExiste - lista não existe
*
***********************************************************************/

   LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento após
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
*        LIS_CondRetOK
*        LIS_CondRetFaltouMemoria
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Excluir elemento
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
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Obter referência para o valor contido no elemento
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido no elemento corrente da lista
*
*  $EP Parâmetros
*     pLista           - ponteiro para a lista de onde se quer o valor
*     elementoCorrente - ponteiro para o valor do nó corrente. Pode ser NULL.
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterValor( LIS_tppLista pLista ,
                                 void ** elementoCorrente ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Obter identificador na cabeça da lista
*
*  $ED Descrição da função
*     Obtem a identificação na cabeça da lista
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista de onde se quer o valor
*     idLista - ponteiro para o valor do id da lista
*
*  $FV Valor retornado
*     LIS_CondRetOK
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterId( LIS_tppLista pLista ,
                              char ** idLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Avançar elemento
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
*     LIS_CondRetOK             - se numElem elementos tiverem sido andados
*     LIS_CondRetNoCorrenteUlt  - chegou ao final da lista antes de avançar
*                               para o próximo elemento
*     LIS_CondRetNoCorrentePrim - chegou no começo da lista antes de retornar
*                               para o elemento anterior
*     LIS_CondRetListaVazia     - se a lista está vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Altera conteudo do nó corrente
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
*     LIS_CondRetOK             - alteração bem sucedida
*     LIS_CondRetListaVazia     - se a lista estiver vazia
*     LIS_CondRetListaNaoExiste - se a lista não existir
*
***********************************************************************/

   LIS_tpCondRet LIS_AlteraValor( LIS_tppLista pLista ,
                                  void * pValor ) ;

#undef LISTA_EXT

/********** Fim do módulo de definição: LIS  Lista duplamente encadeada **********/

#else
#endif

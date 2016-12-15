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
*     8       vas   13/nov/2016 adição do protótipo da função de comparar listas
*     7       vas   11/nov/2016 adição da função de lista vazia
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

         #ifdef _DEBUG
            LIS_CondRetFalhaNaEstrutura = 8,
            /* Existe uma falha na estrutura da lista. */
         #endif

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

         LIS_CondRetNaoAchou = 7
               /* Nao encontrou o elemento da lista */

   } LIS_tpCondRet ;


#ifdef _DEBUG
   typedef enum {

         LIS_tpErroEstruturaNenhum = 0,
         LIS_tpErroEstruturaCabecaCorrompida = 1,
         LIS_tpErroEstruturaCorrenteNuloIndevidamente = 2,
         LIS_tpErroEstruturaOrigemNuloIndevidamente = 3,
         LIS_tpErroEstruturaFimNuloIndevidamente = 4,
         LIS_tpErroEstruturaListaVaziaMasElementosNaoNulos = 5,
         LIS_tpErroEstruturaInicioDaListaPossuiAnterior = 6,
         LIS_tpErroEstruturaFimDaListaPossuiProximo = 7,
         LIS_tpErroEstruturaElementoDaListaCorrompido = 8,
         LIS_tpErroEstruturaEncadeamentoIncorretoNaLista = 9,
         LIS_tpErroEstruturaValorArmazenadoNulo = 10,
         LIS_tpErroEstruturaTipoDoValorIncoerente = 11,
         LIS_tpErroEstruturaElementoCorrenteNaoEstaNaLista = 12,
         LIS_tpErroEstruturaNumeroDeElementosIncorreto = 13

   } LIS_tpErroEstrutura ;
#endif


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
*     idLista         - id da lista sendo criada, máximo de 4 caracteres
*     ExcluirValor    - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
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
*  $FC Função: LIS  &Copiar lista
*
*  $ED Descrição da função
*     Copia uma lista genérica duplamente encadeada.
*
*  $EP Parâmetros
*
*     pLista          - ponteiro para a lista sendo criada
*     listaOriginal   - lista original a ser copiada
*
*  $FV Valor retornado
*     LIS_CondRetOK            - lista foi criada corretamente
*     LIS_CondRetFaltouMemoria - ocorreu um erro na criação da lista
*
***********************************************************************/

   LIS_tpCondRet LIS_CopiarLista( LIS_tppLista* pLista , LIS_tppLista listaOriginal, void ( * CopiarElemento ) ( void ** pValor, void* pValorOriginal ) );

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
*           
*
*  $FV Valor retornado
*     Valor retornado
*        LIS_CondRetOK              - inseriu elemento após corretamente
*        LIS_CondRetFaltouMemoria   - ocorreu um erro na inserção do elemento
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
*     LIS_CondRetOK           - excluiu elemento da lista corretamente
*     LIS_CondRetListaVazia   - nó corrente da lista é vazio
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
*     elementoCorrente - ponteiro para o ponteiro referente ao valor do nó corrente
*
*  $FV Valor retornado
*     LIS_CondRetOK           - obteve valor do nó corrente corretamente
*     LIS_CondRetListaVazia   - nó corrente da lista é vazio
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
*     idLista - ponteiro para o ponteiro referente ao valor do id da lista
*
*  $FV Valor retornado
*     LIS_CondRetOK   - obteve o id da lista corretamente
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


/***********************************************************************
*
*  $FC Função: LIS  &Verifica se a lista está vazia
*
*  $ED Descrição da função
*     Verifica se a lista está vazia ou não.
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser verificada
*     vazia   - ponteiro para o valor da condição
*
*  $FV Valor retornado
*     LIS_CondRetOK             - alteração bem sucedida
*     LIS_CondRetListaNaoExiste - se a lista não existir
*
***********************************************************************/

   LIS_tpCondRet LIS_VerificaVazia( LIS_tppLista pLista ,
                                  int * vazia ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Compara duas listas
*
*  $ED Descrição da função
*     Verifica se as duas listas são iguais ou não.
*
*  $EP Parâmetros
*     pLista1   - ponteiro para a primeira lista da comparação
*     pLista2   - ponteiro para a segunda lista da comparação
*     igualdade - ponteiro para o valor da igualdade
*
*  $FV Valor retornado
*     LIS_CondRetOK             - alteração bem sucedida
*     LIS_CondRetListaNaoExiste - se a lista não existir
*
***********************************************************************/

   LIS_tpCondRet LIS_VerificaIgualdade( LIS_tppLista pLista1 ,
                                        LIS_tppLista pLista2 ,
                                        int * igualdade ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Esvazia lista
*
*  $ED Descrição da função
*     Esvazia uma lista sem destrui-la.
*
*  $EP Parâmetros
*     pLista1   - ponteiro para a lista que será esvaziada
*
*  $FV Valor retornado
*     LIS_CondRetOK             - alteração bem sucedida
*     LIS_CondRetListaNaoExiste - se a lista não existir
*
***********************************************************************/

   LIS_tpCondRet LIS_Esvazia( LIS_tppLista pLista ) ;

/***********************************************************************
*
*  $FC Função: LIS  &Procurar elemento contendo valor
*
*  $ED Descrição da função
*     Procura o elemento que referencia o valor dado.
*     A função compara o conteúdo apontado de acordo com função
*       de igualdade passada na criação da lista.
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista onde procura
*     pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK  - se encontrou.
*                      O elemento corrente é o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que contém o ponteiro procurado
*
*     LIS_CondRetNaoAchou - se o ponteiro não foi encontrado
*                      O elemento corrente continua o mesmo
*     LIS_CondRetListaVazia   - se a lista estiver vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor) ;

/***********************************************************************
*
*  $FC Função: LIS  &Move Inicio
*
*  $ED Descrição da função
*     Move o corrente para o primeiro elemento da lista
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista
*
*  $FV Valor retornado
*     LIS_CondRetOK  - Nenhum erro ocorreu
*
***********************************************************************/

   LIS_tpCondRet LIS_MoveInicio( LIS_tppLista pLista ) ;

#ifdef _DEBUG

   /***********************************************************************
   *
   *  $FC Função: LIS  &Tamanho
   *
   *  $ED Descrição da função
   *     Retorna o tamanho da lista.
   *
   *  $EP Parâmetros
   *     pLista  - ponteiro para a lista a ser verificada
   *     tamanhoDaLista   - ponteiro para o valor do tamanho da lista
   *
   *  $FV Valor retornado
   *     LIS_CondRetOK             - retorno bem sucedido
   *     LIS_CondRetListaNaoExiste - se a lista não existir
   *
   ***********************************************************************/

   LIS_tpCondRet LIS_Tamanho( LIS_tppLista pLista ,
                              int * tamanhoDaLista );

#endif
#ifdef _DEBUG

/***********************************************************************
*
*  $FC Função: LIS  &Define o Tipo
*
*  $ED Descrição da função
*     Define o tipo que a lista armazena.
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser verificada
*     identificadorDoTipo   -  identificador do tipo

*  $FV Valor retornado
*     LIS_CondRetOK             - retorno bem sucedido
*     LIS_CondRetListaNaoExiste - se a lista não existir
*
***********************************************************************/

   LIS_tpCondRet LIS_SetTipo( LIS_tppLista pLista ,
                              int identificadorDoTipo );

#endif
#ifdef _DEBUG

/***********************************************************************
*
*  $FC Função: LIS  &Obtem o Tipo
*
*  $ED Descrição da função
*     Obtem o tipo que a lista armazena, armazenando em identificadorDoTipo.
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser verificada
*     identificadorDoTipo   -  identificador do tipo

*  $FV Valor retornado
*     LIS_CondRetOK             - retorno bem sucedido
*     LIS_CondRetListaNaoExiste - se a lista não existir
*
***********************************************************************/

   LIS_tpCondRet LIS_GetTipo( LIS_tppLista pLista ,
                              int* identificadorDoTipo );

#endif
#ifdef _DEBUG

/***********************************************************************
*
*  $FC Função: LIS  &Obter referência para o ponteiro do elemento corrente para o proximo elemento
*
*  $ED Descrição da função
*     Obtem a referência para o ponteiro para o proximo elemento contido no elemento corrente da lista
*
*  $EP Parâmetros
*     pLista           - ponteiro para a lista de onde se quer o ponteiro
*     ponteiroProxElem - ponteiro para o ponteiro referente ao elemento seguinte ao elemento corrente
*
*  $FV Valor retornado
*     LIS_CondRetOK           - obteve ponteiro para o elemento seguinte corretamente
*     LIS_CondRetListaVazia   - nó corrente da lista é vazio
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterPonteiroProximo( LIS_tppLista pLista ,
                                            void *** ponteiroProxElem ) ;

#endif
#ifdef _DEBUG

/***********************************************************************
*
*  $FC Função: LIS  &Obter referência para o ponteiro do elemento corrente para o elemento anterior
*
*  $ED Descrição da função
*     Obtem a referência para o ponteiro para o elemento anterior contido no elemento corrente da lista
*
*  $EP Parâmetros
*     pLista           - ponteiro para a lista de onde se quer o ponteiro
*     ponteiroAntElem - ponteiro para o ponteiro referente ao elemento anterior ao elemento corrente
*
*  $FV Valor retornado
*     LIS_CondRetOK           - obteve ponteiro para o elemento anterior corretamente
*     LIS_CondRetListaVazia   - nó corrente da lista é vazio
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterPonteiroAnterior( LIS_tppLista pLista ,
                                            void *** ponteiroAntElem ) ;

/***********************************************************************
*
*  $FC Função: TAB  &Verificar Estrutura da Lista
*
*  $ED Descrição da função
*     Verifica a estrutura da lista.
*
*  $EP Parametros
*     pLista - ponteiro para a lista a ser verificada
*     erroOcorrido - tipo do erro retornado
*
*  $FV Valor retornado
*     LIS_CondRetOK                   - Nao foram encontradas falhas
*     LIS_CondRetFalhaNaEstrutura     - Foram encontradas falhas
*
***********************************************************************/

   LIS_tpCondRet LIS_VerificaAssertivasEstruturais( LIS_tppLista pLista, LIS_tpErroEstrutura* erroOcorrido, int* numErrosEncontrados );

/***********************************************************************
*
*  $FC Função: LIS  &Obter referência para o ponteiro do elemento corrente para o proximo elemento
*
*  $ED Descrição da função
*     Obtem a referência para o ponteiro para o proximo elemento contido no elemento corrente da lista
*
*  $EP Parâmetros
*     pLista           - ponteiro para a lista de onde se quer o ponteiro
*     ponteiroProxElem - ponteiro para o ponteiro referente ao elemento seguinte ao elemento corrente
*
*  $FV Valor retornado
*     LIS_CondRetOK           - obteve ponteiro para o elemento seguinte corretamente
*     LIS_CondRetListaVazia   - nó corrente da lista é vazio
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterPonteiroProximo( LIS_tppLista pLista ,
                                void *** ponteiroProxElem ) ;

/***********************************************************************
*
*  $FC Função: LIS  &Obter referência para o ponteiro do elemento corrente para o elemento anterior
*
*  $ED Descrição da função
*     Obtem a referência para o ponteiro para o elemento anterior contido no elemento corrente da lista
*
*  $EP Parâmetros
*     pLista           - ponteiro para a lista de onde se quer o ponteiro
*     ponteiroAntElem - ponteiro para o ponteiro referente ao elemento anterior ao elemento corrente
*
*  $FV Valor retornado
*     LIS_CondRetOK           - obteve ponteiro para o elemento anterior corretamente
*     LIS_CondRetListaVazia   - nó corrente da lista é vazio
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterPonteiroAnterior( LIS_tppLista pLista ,
                                          void *** ponteiroAntElem ) ;

/***********************************************************************
*
*  $FC Função: LIS  &Obter referência para o ponteiro para o valor do elemento corrente
*
*  $ED Descrição da função
*     Obtem a referência para o ponteiro para o valor do elemento corrente
*
*  $EP Parâmetros
*     pLista           - ponteiro para a lista de onde se quer o ponteiro
*     ponteiroValor - ponteiro para o ponteiro do valor
*
*  $FV Valor retornado
*     LIS_CondRetOK           - obteve ponteiro corretamente
*     LIS_CondRetListaVazia   - nó corrente da lista é vazio
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterPonteiroValor( LIS_tppLista pLista ,
                                          void *** ponteiroValor ) ;

#endif

#undef LISTA_EXT

/********** Fim do módulo de definição: LIS  Lista duplamente encadeada **********/

#else
#endif

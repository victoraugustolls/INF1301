#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs, iars, vas
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     9       iars  12/dez/2016 adicao do prototipo da funcao de verificacao
*     8       vas   13/nov/2016 adi��o do prot�tipo da fun��o de comparar listas
*     7       vas   11/nov/2016 adi��o da fun��o de lista vazia
*     6       vas   03/out/2016 ajuste das fun��es para todas terem condi��es de retorno
*                               e retirada de fun��es n�o utilizadas
*     5       iars  14/set/2016 inser��o ordenada, procurar valor, imprimir
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa listas gen�ricas duplamente encadeadas.
*     Podem existir n listas em opera��o simultaneamente.
*     As listas possuem uma cabe�a encapsulando o seu estado.
*
*     Cada lista � homog�nea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que cont�m.
*
*     Os ponteiros para os dados s�o copiados para elementos da lista.
*        N�o � copiado o valor apontado por estes ponteiros.
*
*     O controle da destrui��o do valor de um elemento a ser exclu�do
*        � realizado por uma fun��o fornecida pelo usu�rio.
*
*     Cada lista referencia uma fun��o que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A fun��o de libera��o dos valores contidos nos elementos deve
*        assegurar a libera��o de todos os espa�os refer�nciados pelo
*        valor contido em um elemento.
*        Esta fun��o � chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso n�o seja necess�rio desalocar o valor referenciado pelo
*        elemento, o ponteiro para a fun��o de libera��o poder� ser NULL .
*        Caso o elemento da lista seja a �nica �ncora do valor referenciado,
*        esta fun��o deve promover a destrui��o (free) desse valor e
*        de todos os dados nele ancorados.
*
*     Tamb�m devem ser fornecidas uma fun��o de compara��o de elementos, uma
*        fun��o que diz quando dois elementos s�o iguais e uma fun��o que
*        imprime o conte�do de um elemento.
*
*     A fun��o de compara��o deve receber dois elementos e retornar -1, 0 ou 1
*        caso o primeiro elemento deva ser ordenado antes, igualmente ou ap�s
*        o segundo elemento, respectivamente.
*
*     A fun��o de igualdade deve receber dois valores e retornar 0 caso sejam diferentes
*        ou um inteiro diferente de zero caso sejam iguais.
*
***************************************************************************/

#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da lista
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
               /* A lista n�o cont�m elementos */

         LIS_CondRetListaNaoExiste = 3 ,
               /* A lista n�o existe */

         LIS_CondRetNoCorrenteUlt = 4 ,
               /* N� corrente � o �ltimo */

         LIS_CondRetNoCorrentePrim = 5 ,
               /* N� corrente � o primeiro */

         LIS_CondRetFaltouMemoria = 6 ,
               /* Faltou mem�ria ao tentar criar um elemento de lista */

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
         LIS_tpErroEstruturaNumeroDeElementosIncorreto = 13,
         LIS_tpErroEstruturaListaVaziaInconsistente = 14,
         LIS_tpErroEstruturaListaCircular = 15

   } LIS_tpErroEstrutura ;
#endif


/***********************************************************************
*
*  $FC Fun��o: LIS  &Criar lista
*
*  $ED Descri��o da fun��o
*     Cria uma lista gen�rica duplamente encadeada.
*     Os poss�veis tipos s�o desconhecidos a priori.
*     A tipagem � implicita.
*     N�o existe identificador de tipo associado � lista.
*
*  $EP Par�metros
*
*     pLista          - ponteiro para a lista sendo criada
*     idLista         - id da lista sendo criada, m�ximo de 4 caracteres
*     ExcluirValor    - ponteiro para a fun��o que processa a
*                     exclus�o do valor referenciado pelo elemento
*                     a ser exclu�do.
*                     Ver descri��o do m�dulo.
*     CompararValores - ponteiro para a fun��o que compara o valor
*                     de dois elementos. Deve retornar -1, 0 ou 1.
*                     Ver descri��o do m�dulo.
*     Igual           - ponteiro para a fun��o que compara se o valor
*                     de dois elementos � igual.
*                     Ver descri��o do m�dulo.
*
*  $FV Valor retornado
*     LIS_CondRetOK            - lista foi criada corretamente
*     LIS_CondRetFaltouMemoria - ocorreu um erro na cria��o da lista
*
***********************************************************************/

   LIS_tpCondRet LIS_CriarLista( LIS_tppLista* pLista ,
             char * idLista ,

             void   ( * ExcluirValor ) ( void * pDado ) ,

             int   ( * CompararValores ) ( void * pDado_1, void * pDado_2 ) ,

             int   ( * Igual ) ( void * pDado_1, void * pDado_2 ) ) ;



/***********************************************************************
*
*  $FC Fun��o: LIS  &Copiar lista
*
*  $ED Descri��o da fun��o
*     Copia uma lista gen�rica duplamente encadeada.
*
*  $EP Par�metros
*
*     pLista          - ponteiro para a lista sendo criada
*     listaOriginal   - lista original a ser copiada
*
*  $FV Valor retornado
*     LIS_CondRetOK            - lista foi criada corretamente
*     LIS_CondRetFaltouMemoria - ocorreu um erro na cria��o da lista
*
***********************************************************************/

   LIS_tpCondRet LIS_CopiarLista( LIS_tppLista* pLista , LIS_tppLista listaOriginal, void ( * CopiarElemento ) ( void ** pValor, void* pValorOriginal ) );

/***********************************************************************
*
*  $FC Fun��o: LIS  &Destruir lista
*
*  $ED Descri��o da fun��o
*     Destr�i a lista fornecida.
*     O par�metro ponteiro para a lista n�o � modificado.
*     Se ocorrer algum erro durante a destrui��o, a lista resultar�
*     estruturalmente incorreta.
*     OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*  $FV Valor retornado
*     LIS_CondRetOK             - destruiu sem problemas
*     LIS_CondRetListaNaoExiste - lista n�o existe
*
***********************************************************************/

   LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Inserir elemento ap�s
*
*  $ED Descri��o da fun��o
*     Insere novo elemento ap�s o elemento corrente.
*     O elemento corrente passar� a ser o novo elemento inserido.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Par�metros
*     Par�metros
*        pLista - ponteiro para a lista onde deve ser inserido o elemento
*        pValor - ponteiro para o valor do novo elemento
*           
*
*  $FV Valor retornado
*     Valor retornado
*        LIS_CondRetOK              - inseriu elemento ap�s corretamente
*        LIS_CondRetFaltouMemoria   - ocorreu um erro na inser��o do elemento
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Excluir elemento
*
*  $ED Descri��o da fun��o
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente ser� o novo corrente.
*     Se n�o existir e existir o elemento � direita, este se tornar� corrente.
*     Se este tamb�m n�o existir a lista tornou-se vazia.
*
*  $EP Par�metros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     LIS_CondRetOK           - excluiu elemento da lista corretamente
*     LIS_CondRetListaVazia   - n� corrente da lista � vazio
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Obter refer�ncia para o valor contido no elemento
*
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para o valor contido no elemento corrente da lista
*
*  $EP Par�metros
*     pLista           - ponteiro para a lista de onde se quer o valor
*     elementoCorrente - ponteiro para o ponteiro referente ao valor do n� corrente
*
*  $FV Valor retornado
*     LIS_CondRetOK           - obteve valor do n� corrente corretamente
*     LIS_CondRetListaVazia   - n� corrente da lista � vazio
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterValor( LIS_tppLista pLista ,
                                 void ** elementoCorrente ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Obter identificador na cabe�a da lista
*
*  $ED Descri��o da fun��o
*     Obtem a identifica��o na cabe�a da lista
*
*  $EP Par�metros
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
*  $FC Fun��o: LIS  &Avan�ar elemento
*
*  $ED Descri��o da fun��o
*     Avan�a o elemento corrente numElem elementos na lista
*     Se numElem for positivo avan�a em dire��o ao final
*     Se numElem for negativo avan�a em dire��o ao in�cio
*     numElem pode ser maior do que o n�mro de elementos existentes na
*               dire��o desejada
*     Se numElem for zero somente verifica se a lista est� vazia
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o n�mero de elementos a andar
*
*  $FV Valor retornado
*     LIS_CondRetOK             - se numElem elementos tiverem sido andados
*     LIS_CondRetNoCorrenteUlt  - chegou ao final da lista antes de avan�ar
*                               para o pr�ximo elemento
*     LIS_CondRetNoCorrentePrim - chegou no come�o da lista antes de retornar
*                               para o elemento anterior
*     LIS_CondRetListaVazia     - se a lista est� vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Altera conteudo do n� corrente
*
*  $ED Descri��o da fun��o
*     Altera o valor do n� corrente da lista para novo valor.
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista a ser manipulada
*     pValor  - ponteiro para o novo valor do n� corrente
*               Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK             - altera��o bem sucedida
*     LIS_CondRetListaVazia     - se a lista estiver vazia
*     LIS_CondRetListaNaoExiste - se a lista n�o existir
*
***********************************************************************/

   LIS_tpCondRet LIS_AlteraValor( LIS_tppLista pLista ,
                                  void * pValor ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Verifica se a lista est� vazia
*
*  $ED Descri��o da fun��o
*     Verifica se a lista est� vazia ou n�o.
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista a ser verificada
*     vazia   - ponteiro para o valor da condi��o
*
*  $FV Valor retornado
*     LIS_CondRetOK             - altera��o bem sucedida
*     LIS_CondRetListaNaoExiste - se a lista n�o existir
*
***********************************************************************/

   LIS_tpCondRet LIS_VerificaVazia( LIS_tppLista pLista ,
                                  int * vazia ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Compara duas listas
*
*  $ED Descri��o da fun��o
*     Verifica se as duas listas s�o iguais ou n�o.
*
*  $EP Par�metros
*     pLista1   - ponteiro para a primeira lista da compara��o
*     pLista2   - ponteiro para a segunda lista da compara��o
*     igualdade - ponteiro para o valor da igualdade
*
*  $FV Valor retornado
*     LIS_CondRetOK             - altera��o bem sucedida
*     LIS_CondRetListaNaoExiste - se a lista n�o existir
*
***********************************************************************/

   LIS_tpCondRet LIS_VerificaIgualdade( LIS_tppLista pLista1 ,
                                        LIS_tppLista pLista2 ,
                                        int * igualdade ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Esvazia lista
*
*  $ED Descri��o da fun��o
*     Esvazia uma lista sem destrui-la.
*
*  $EP Par�metros
*     pLista1   - ponteiro para a lista que ser� esvaziada
*
*  $FV Valor retornado
*     LIS_CondRetOK             - altera��o bem sucedida
*     LIS_CondRetListaNaoExiste - se a lista n�o existir
*
***********************************************************************/

   LIS_tpCondRet LIS_Esvazia( LIS_tppLista pLista ) ;

/***********************************************************************
*
*  $FC Fun��o: LIS  &Procurar elemento contendo valor
*
*  $ED Descri��o da fun��o
*     Procura o elemento que referencia o valor dado.
*     A fun��o compara o conte�do apontado de acordo com fun��o
*       de igualdade passada na cria��o da lista.
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista onde procura
*     pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK  - se encontrou.
*                      O elemento corrente � o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que cont�m o ponteiro procurado
*
*     LIS_CondRetNaoAchou - se o ponteiro n�o foi encontrado
*                      O elemento corrente continua o mesmo
*     LIS_CondRetListaVazia   - se a lista estiver vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor) ;

/***********************************************************************
*
*  $FC Fun��o: LIS  &Move Inicio
*
*  $ED Descri��o da fun��o
*     Move o corrente para o primeiro elemento da lista
*
*  $EP Par�metros
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
   *  $FC Fun��o: LIS  &Tamanho
   *
   *  $ED Descri��o da fun��o
   *     Retorna o tamanho da lista.
   *
   *  $EP Par�metros
   *     pLista  - ponteiro para a lista a ser verificada
   *     tamanhoDaLista   - ponteiro para o valor do tamanho da lista
   *
   *  $FV Valor retornado
   *     LIS_CondRetOK             - retorno bem sucedido
   *     LIS_CondRetListaNaoExiste - se a lista n�o existir
   *
   ***********************************************************************/

   LIS_tpCondRet LIS_Tamanho( LIS_tppLista pLista ,
                              int * tamanhoDaLista );

#endif
#ifdef _DEBUG

/***********************************************************************
*
*  $FC Fun��o: LIS  &Define o Tipo
*
*  $ED Descri��o da fun��o
*     Define o tipo que a lista armazena.
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista a ser verificada
*     identificadorDoTipo   -  identificador do tipo

*  $FV Valor retornado
*     LIS_CondRetOK             - retorno bem sucedido
*     LIS_CondRetListaNaoExiste - se a lista n�o existir
*
***********************************************************************/

   LIS_tpCondRet LIS_SetTipo( LIS_tppLista pLista ,
                              int identificadorDoTipo );

#endif
#ifdef _DEBUG

/***********************************************************************
*
*  $FC Fun��o: LIS  &Obtem o Tipo
*
*  $ED Descri��o da fun��o
*     Obtem o tipo que a lista armazena, armazenando em identificadorDoTipo.
*  $EP Par�metros
*     pLista  - ponteiro para a lista a ser verificada
*     identificadorDoTipo   -  identificador do tipo

*  $FV Valor retornado
*     LIS_CondRetOK             - retorno bem sucedido
*     LIS_CondRetListaNaoExiste - se a lista n�o existir
*
***********************************************************************/

   LIS_tpCondRet LIS_GetTipo( LIS_tppLista pLista ,
                              int* identificadorDoTipo );

#endif
#ifdef _DEBUG

/***********************************************************************
*
*  $FC Fun��o: LIS  &Obter refer�ncia para o ponteiro do elemento corrente para o proximo elemento
*
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para o ponteiro para o proximo elemento contido no elemento corrente da lista
*
*  $EP Par�metros
*     pLista           - ponteiro para a lista de onde se quer o ponteiro
*     ponteiroProxElem - ponteiro para o ponteiro referente ao elemento seguinte ao elemento corrente
*
*  $FV Valor retornado
*     LIS_CondRetOK           - obteve ponteiro para o elemento seguinte corretamente
*     LIS_CondRetListaVazia   - n� corrente da lista � vazio
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterPonteiroProximo( LIS_tppLista pLista ,
                                            void *** ponteiroProxElem ) ;

#endif
#ifdef _DEBUG

/***********************************************************************
*
*  $FC Fun��o: LIS  &Obter refer�ncia para o ponteiro do elemento corrente para o elemento anterior
*
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para o ponteiro para o elemento anterior contido no elemento corrente da lista
*
*  $EP Par�metros
*     pLista           - ponteiro para a lista de onde se quer o ponteiro
*     ponteiroAntElem - ponteiro para o ponteiro referente ao elemento anterior ao elemento corrente
*
*  $FV Valor retornado
*     LIS_CondRetOK           - obteve ponteiro para o elemento anterior corretamente
*     LIS_CondRetListaVazia   - n� corrente da lista � vazio
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterPonteiroAnterior( LIS_tppLista pLista ,
                                            void *** ponteiroAntElem ) ;

/***********************************************************************
*
*  $FC Fun��o: TAB  &Verificar Estrutura da Lista
*
*  $ED Descri��o da fun��o
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
*  $FC Fun��o: LIS  &Obter refer�ncia para o ponteiro do elemento corrente para o proximo elemento
*
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para o ponteiro para o proximo elemento contido no elemento corrente da lista
*
*  $EP Par�metros
*     pLista           - ponteiro para a lista de onde se quer o ponteiro
*     ponteiroProxElem - ponteiro para o ponteiro referente ao elemento seguinte ao elemento corrente
*
*  $FV Valor retornado
*     LIS_CondRetOK           - obteve ponteiro para o elemento seguinte corretamente
*     LIS_CondRetListaVazia   - n� corrente da lista � vazio
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterPonteiroProximo( LIS_tppLista pLista ,
                                void *** ponteiroProxElem ) ;

/***********************************************************************
*
*  $FC Fun��o: LIS  &Obter refer�ncia para o ponteiro do elemento corrente para o elemento anterior
*
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para o ponteiro para o elemento anterior contido no elemento corrente da lista
*
*  $EP Par�metros
*     pLista           - ponteiro para a lista de onde se quer o ponteiro
*     ponteiroAntElem - ponteiro para o ponteiro referente ao elemento anterior ao elemento corrente
*
*  $FV Valor retornado
*     LIS_CondRetOK           - obteve ponteiro para o elemento anterior corretamente
*     LIS_CondRetListaVazia   - n� corrente da lista � vazio
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterPonteiroAnterior( LIS_tppLista pLista ,
                                          void *** ponteiroAntElem ) ;

/***********************************************************************
*
*  $FC Fun��o: LIS  &Obter refer�ncia para o ponteiro para o valor do elemento corrente
*
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para o ponteiro para o valor do elemento corrente
*
*  $EP Par�metros
*     pLista           - ponteiro para a lista de onde se quer o ponteiro
*     ponteiroValor - ponteiro para o ponteiro do valor
*
*  $FV Valor retornado
*     LIS_CondRetOK           - obteve ponteiro corretamente
*     LIS_CondRetListaVazia   - n� corrente da lista � vazio
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterPonteiroValor( LIS_tppLista pLista ,
                                          void *** ponteiroValor ) ;

/***********************************************************************
*
*  $FC Fun��o: LIS  &Obter refer�ncia para o ponteiro para ponteiro corrente
*
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para o ponteiro para ponteiro corrente
*
*  $EP Par�metros
*     pLista           - ponteiro para a lista de onde se quer o ponteiro
*     ponteiroCorrente - ponteiro para o ponteiro do corrente
*
*  $FV Valor retornado
*     LIS_CondRetOK           - obteve ponteiro corretamente
*     LIS_CondRetListaVazia   - n� corrente da lista � vazio
*
***********************************************************************/
  LIS_tpCondRet LIS_ObterPonteiroCorrente( LIS_tppLista pLista ,
                                          void *** ponteiroCorrente ) ;\

/***********************************************************************
*
*  $FC Fun��o: LIS  &Move Fim
*
*  $ED Descri��o da fun��o
*     Move o corrente para o ultimo elemento da lista
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista
*
*  $FV Valor retornado
*     LIS_CondRetOK  - Nenhum erro ocorreu
*
***********************************************************************/

   LIS_tpCondRet LIS_MoveFim( LIS_tppLista pLista ) ;

#endif

#undef LISTA_EXT

/********** Fim do m�dulo de defini��o: LIS  Lista duplamente encadeada **********/

#else
#endif

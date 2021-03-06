/***************************************************************************
*  $MCI M�dulo de implementa��o: TARV Teste espec�fico para o m�dulo �rvore
*
*  Arquivo gerado:              TESTARV.C
*  Letras identificadoras:      TST
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: C:\LIXO\INSTRUM.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�odulo cont�m as fun��es espec�ficas para o teste de um m�dulo.
*     Mais especificamente, cont�m a fun��o que interpreta os comandos de
*     teste que exercitar�o as fun��es do m�dulo em teste.
*
*     Caso o m�dulo em teste requeira um contexto expl�cito,
*     este contexto dever� ser estabelecido no presente m�dulo.
*
*     Uma poss�vel maneira � incluir comandos de teste que constr�em
*     ou dest�em o contexto.
*     Alterar as fun��es TST_InicializarTeste e TST_TerminarTeste
*     contidas no m�dulo TesteGen deve ser evitado para manter
*     a integridade do arcabou�o ("framework") de teste.
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "CEspDin.h"
#include    "lerparm.h"

#include    "arvore.h"

/* Tabela dos nomes dos comandos de teste espec�ficos */

const char RESET_CMD     [ ] = "=resetarvore" ;
const char CRIAR_ARV_CMD [ ] = "=criar"       ;
const char INS_DIR_CMD   [ ] = "=insdir"      ;
const char INS_ESQ_CMD   [ ] = "=insesq"      ;
const char IR_PAI_CMD    [ ] = "=irpai"       ;
const char IR_ESQ_CMD    [ ] = "=iresq"       ;
const char IR_DIR_CMD    [ ] = "=irdir"       ;
const char OBTER_VAL_CMD [ ] = "=obter"       ;
const char DESTROI_CMD   [ ] = "=destruir"    ;

/* os comandos a seguir somente operam em modo _DEBUG */

const char VER_CABECA_CMD[ ] = "=verificarcabeca" ;
const char VER_ARVORE_CMD[ ] = "=verificararvore" ;
const char VER_MEMORIA_CMD[ ] = "=verificarmemoria" ;
const char DETURPAR_CMD[ ]   = "=deturpar" ;

int estaInicializado = 0 ;

#define DIM_VT_ARVORES  5

void * vtRefArvore[ DIM_VT_ARVORES ] ;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static int VerificarInx( int inxArvore ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TARV &Efetuar opera��es espec�ficas
*
*  $ED Descri��o da fun��o
*     Comandos de teste espec�ficos para testar o m�dulo �rvore:
*
*     Podem ser criadas at� 5 �rvores simultaneamente
*     As �rvores s�o conhecidas pelo seu �ndice de 0 a 4
*
*     =resetarvore
*
*     =criar   <inxArvore>  <Cond ret>
*                   - chama a fun��o ARV_CriarArvore( )
*
*     =insdir  <inxArvore> <Char> <Cond ret>
*                   - chama a fun��o ARV_InserirDireita( )
*                     Obs. nota��o: <Char>  � o valor do par�metro
*                     que se encontra no comando de teste.
*
*     =insesq  <inxArvore> <Char> <Cond ret>
*                   - chama a fun��o ARV_InserirEsquerda( )
*
*     =irpai   <inxArvore> <Cond ret>
*                   - chama a fun��o ARV_IrPai( )
*
*     =iresq   <inxArvore> <Cond ret>
*                   - chama a fun��o ARV_IrEsquerda( )
*
*     =irdir   <inxArvore> <Cond ret>
*                   - chama a fun��o ARV_IrDireita( )
*
*     =obter   <inxArvore> <Char> <Cond ret>
*                   - chama a fun��o ARV_ObterValorCorr( ) e compara
*                     o valor retornado com o valor <Char>
*
*     =destroi <inxArvore> <Cond ret>
*                   - chama a fun��o ARV_DestruirArvore( )
*
*
*     Estes comandos somente podem ser executados se o modulo tiver sido
*     compilado com _DEBUG ligado
*
*     =verificarcabeca       <inxArvore>
*
*     =verificararvore       <inxArvore>
*
*     =verificarmemoria
*
*     =deturpar              <inxArvore> < idCodigoDeturpa >
*
*
*
*     Ver explica��o detalhada em TST_ESPC.H
*
*  $EP Par�metros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver condicoes de retorno em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      ARV_tpCondRet CondRetObtido   = ARV_CondRetOK ;
      ARV_tpCondRet CondRetEsperada = ARV_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      char ValorDado     = '\0' ;

      int  NumLidos      = -1 ;
      int  inxArvore     = -1 ;

      int i ;

      TST_tpCondRet Ret ;

      #ifdef _DEBUG
         int  IntEsperado   = -1 ;
      #endif

      /* Tratar: inicializar contexto */

         if ( strcmp( ComandoTeste , RESET_CMD ) == 0 )
         {

            if ( estaInicializado )
            {
               for( i = 0 ; i < DIM_VT_ARVORES ; i++ )
               {
                  ARV_DestruirArvore( & ( vtRefArvore[ i ] )) ;
               } /* for */
            } /* if */

            for( i = 0 ; i < DIM_VT_ARVORES ; i++ )
            {
               vtRefArvore[ i ] = 0 ;
            } /* for */

            estaInicializado = 1 ;

         } /* fim ativa: Tratar: inicializar contexto */

      /* Testar ARV Criar �rvore */

         else if ( strcmp( ComandoTeste , CRIAR_ARV_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &inxArvore , &CondRetEsperada ) ;
            if ( ( NumLidos != 2 )
              || !VerificarInx( inxArvore ))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_CriarArvore( &( vtRefArvore[ inxArvore ] )) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar �rvore." );

         } /* fim ativa: Testar ARV Criar �rvore */

      /* Testar ARV Adicionar filho � direita */

         else if ( strcmp( ComandoTeste , INS_DIR_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ici" ,
                               &inxArvore , &ValorDado , &CondRetEsperada ) ;
            if ( ( NumLidos != 3 )
              || !VerificarInx( inxArvore ))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_InserirDireita( vtRefArvore[ inxArvore ] , ValorDado ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado inserir �a direita." );

         } /* fim ativa: Testar ARV Adicionar filho � direita */

      /* Testar ARV Adicionar filho � esquerda */

         else if ( strcmp( ComandoTeste , INS_ESQ_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ici" ,
                               &inxArvore , &ValorDado , &CondRetEsperada ) ;
            if ( ( NumLidos != 3 )
              || !VerificarInx( inxArvore ))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_InserirEsquerda( vtRefArvore[ inxArvore ] , ValorDado ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir � esquerda." );

         } /* fim ativa: Testar ARV Adicionar filho � esquerda */

      /* Testar ARV Ir para n� pai */

         else if ( strcmp( ComandoTeste , IR_PAI_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &inxArvore , &CondRetEsperada ) ;
            if ( ( NumLidos != 2 )
              || !VerificarInx( inxArvore ))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_IrPai( vtRefArvore[ inxArvore ] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para pai." );

         } /* fim ativa: Testar ARV Ir para n� pai */

      /* Testar ARV Ir para n� � esquerda */

         else if ( strcmp( ComandoTeste , IR_ESQ_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &inxArvore , &CondRetEsperada ) ;
            if ( ( NumLidos != 2 )
              || !VerificarInx( inxArvore ))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_IrNoEsquerda( vtRefArvore[ inxArvore ] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para esquerda." );

         } /* fim ativa: Testar ARV Ir para n� � esquerda */

      /* Testar ARV Ir para n� � direita */

         else if ( strcmp( ComandoTeste , IR_DIR_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &inxArvore , &CondRetEsperada ) ;
            if ( ( NumLidos != 2 )
              || !VerificarInx( inxArvore ))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_IrNoDireita( vtRefArvore[ inxArvore ] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para direita." );

         } /* fim ativa: Testar ARV Ir para n� � direita */

      /* Testar ARV Obter valor corrente */

         else if ( strcmp( ComandoTeste , OBTER_VAL_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ici" ,
                               &inxArvore , &ValorEsperado , &CondRetEsperada ) ;
            if ( ( NumLidos != 3 )
              || !VerificarInx( inxArvore ))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_ObterValorCorr( vtRefArvore[ inxArvore ] , &ValorObtido ) ;

            Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao obter valor corrente." );

            if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */

            return TST_CompararChar( ValorEsperado , ValorObtido ,
                                     "Conte�do do n� est� errado." ) ;

         } /* fim ativa: Testar ARV Obter valor corrente */

      /* Testar ARV Destruir �rvore */

         else if ( strcmp( ComandoTeste , DESTROI_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &inxArvore ) ;
            if ( ( NumLidos != 1 )
              || !VerificarInx( inxArvore ))
            {
               return TST_CondRetParm ;
            } /* if */

            ARV_DestruirArvore( &( vtRefArvore[ inxArvore ] )) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar ARV Destruir �rvore */

      /* Testar verificador de cabe�a */
      #ifdef _DEBUG

         else if ( strcmp( ComandoTeste , VER_CABECA_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                                          &inxArvore ) ;
            if ( ( NumLidos != 1 )
              || !VerificarInx( inxArvore ))
            {
               return TST_CondRetParm ;
            } /* if */

            return ARV_VerificarCabeca( vtRefArvore[ inxArvore ] ) ;

         } /* fim ativa: Testar verificador de cabe�a */
      #endif

      /* Testar verificador de �rvore */
      #ifdef _DEBUG

         else if ( strcmp( ComandoTeste , VER_ARVORE_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                                          &inxArvore , &CondRetEsperada ) ;
            if ( ( NumLidos != 2 )
              || !VerificarInx( inxArvore ))
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsperada ,
                             ARV_VerificarArvore( vtRefArvore[ inxArvore ] ) ,
                             "Retorno incorreto ao verificar �rvore." ) ;

         } /* fim ativa: Testar verificador de �rvore */
      #endif

      /* Deturpar uma �rvore */
      #ifdef _DEBUG

         else if ( strcmp( ComandoTeste , DETURPAR_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &inxArvore , &IntEsperado ) ;

            if ( ( NumLidos != 2 )
              || !VerificarInx( inxArvore ))
            {
               return TST_CondRetParm ;
            } /* if */

            ARV_Deturpar( vtRefArvore[ inxArvore ] , IntEsperado ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Deturpar uma �rvore */
      #endif

      /* Verificar vazamento de mem�ria */
      #ifdef _DEBUG

         else if ( strcmp( ComandoTeste , VER_MEMORIA_CMD ) == 0 )
         {

            CED_ExibirTodosEspacos( CED_ExibirTodos ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Verificar vazamento de mem�ria */
      #endif

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TARV &Efetuar opera��es espec�ficas */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TARV -Verificar �ndice de �rvore
*
*  $FV Valor retornado
*     0 - inxArvore n�o vale
*     0 - inxArvore vale
*
***********************************************************************/

   int VerificarInx( int inxArvore )
   {

      if ( ( inxArvore <   0 )
        || ( inxArvore >= DIM_VT_ARVORES ))
      {
         return 0 ;
      } /* if */

      return 1 ;

   } /* Fim fun��o: TARV -Verificar �ndice de �rvore */

/********** Fim do m�dulo de implementa��o: TARV Teste espec�fico para o m�dulo �rvore **********/


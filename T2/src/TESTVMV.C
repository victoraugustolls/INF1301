/***************************************************************************
*  $MCI Módulo de implementação: TLIS Teste lista de símbolos
*
*  Arquivo gerado:              TestLIS.c
*  Letras identificadoras:      TLIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs, vas
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     5       vas   14/set/2016 adaptação dos testes para funcionar com a lista modificada
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "VALIDA_MOV.H"



/***** Protótipos das funções encapuladas no módulo *****/


/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Testar lista
*
*  $ED Descrição da função
*     Podem ser criadas até 10 listas, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de listas. Provoca vazamento de memória
*     =criarlista                   inxLista
*     =destruirlista                inxLista
*     =esvaziarlista                inxLista
*     =inselemantes                 inxLista  iniciais   nomeCompleto  paramNULL       CondRetEsp
*     =inselemapos                  inxLista  iniciais   nomeCompleto  paramNULL       CondRetEsp
*     =inselemanord                 inxLista  iniciais   nomeCompleto  paramNull       CondRetEsp
*     =obtervalorelem               inxLista  iniciais   nomeCompleto  CondretPonteiro
*     =excluirelem                  inxLista  CondRetEsp
*     =irinicio                     inxLista
*     =irfinal                      inxLista
*     =avancarelem                  inxLista  numElem    CondRetEsp
*     =procurarvalor                inxLista  iniciais   nomeCompleto  paramNULL       CondRetEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {
      int size = strlen(ComandoTeste);
      size++;
      return TST_CondRetOK;
   }
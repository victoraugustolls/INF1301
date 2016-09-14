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

/***********************************************************************
*
*  $TC Tipo de dados: ETI Descritor da cabeça de etiqueta nominal
*
*
***********************************************************************/

   typedef struct ETI_tagEtiquetaNominal {

         char * iniciais ;
               /* Iniciais da pessoa em questão */

         char * nomeCompleto ;
               /*Nome completo da pessoa em questão */

   } ETI_tpEtiquetaNominal ;

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define ETIQUETA_NOMINAL_OWN
#include "ETIQUETA_NOMINAL.h"
#undef ETIQUETA_NOMINAL_OWN

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: ETI  &Criar etiqueta nominal
*  ****/

ETI_tppEtiqueta ETI_criaEtiquetaNominal( char * iniciais, char * nomeCompleto )
{

    ETI_tpEtiquetaNominal * pEtiquetaNominal = NULL;

    pEtiquetaNominal = ( ETI_tpEtiquetaNominal * ) malloc( sizeof( ETI_tpEtiquetaNominal ));
    if (pEtiquetaNominal == NULL)
    {
      return NULL;
    } /* if */

    return pEtiquetaNominal;
}

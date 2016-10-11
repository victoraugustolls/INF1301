/***************************************************************************
 *
 *  $MCD Módulo de definição: CSA  Casa de um tabuleiro para jogo de xadrez
 *
 *  Arquivo gerado:              CASA.h
 *  Letras identificadoras:      CSA
 *
 *  Nome da base de software:    ArcabouÁo para a automaÁ„o de testes de programas redigidos em C
 *  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
 *
 *  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
 *  Gestor:  LES/DI/PUC-Rio
 *  Autores: lff
 *
 *  $HA Histórico de evolução:
 *     Versão  Autor    Data     Observações
 *     1       lff   10/out/2016 início desenvolvimento
 *
 ***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define CASA_OWN
#include "CASA.H"
#undef CASA_OWN

#include "PECA.H"
#include "LISTA.H"

/***********************************************************************
 *
 *  $TC Tipo de dados: CSA Descritor da casa
 *
 *
 ***********************************************************************/

typedef struct CSA_tagCasa {
    
    PCA_tppPeca peca ;
    /* Ponteiro para a peça contida na casa */
    
    LIS_tppLista listaAmeacantes ;
    /* Ponteiro para a lista de peças ameaçantes a peça contida na casa */
    
    LIS_tppLista listaAmeacados ;
    /* Ponteiro para a lista de peças ameaçado pela peça contida na casa */
    
} CSA_tpCasa ;


/********** Fim do mÛdulo de implementaÁ„o:  CSA  Casa de um tabuleiro para jogo de xadrez
 **********/


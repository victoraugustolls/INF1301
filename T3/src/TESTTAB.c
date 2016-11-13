/***************************************************************************
 *  $MCI Módulo de implementação: TTAB Teste tabuleiro
 *
 *  Arquivo gerado:              TESTTAB.c
 *  Letras identificadoras:      TTAB
 *
 *  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
 *  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
 *
 *  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
 *  Gestor:  LES/DI/PUC-Rio
 *  Autores: lff, iars
 *
 *  $HA Histórico de evolução:
 *     Versão  Autor    Data     Observações
 *     1       lff   05/out/2016 início desenvolvimento
 *
 ***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "LISTA.H"
#include    "CASA.H"
#include    "TABULEIRO.H"


static const char CRIAR_TABULEIRO_CMD            [ ] = "=criarTabuleiro"        ;
static const char DESTRUIR_TABULEIRO_CMD         [ ] = "=destruirTabuleiro"     ;
static const char INSERIR_PECA_CMD               [ ] = "=inserirPeca"           ;
static const char MOVER_PECA_CMD                 [ ] = "=moverPeca"             ;
static const char RETIRAR_PECA_CMD               [ ] = "=retirarPeca"           ;
static const char OBTER_CASA_CMD                 [ ] = "=obterCasa"             ;
static const char OBTER_PECA_CMD                 [ ] = "=obterPeca"             ;
static const char OBTER_AMEACANTES_CMD           [ ] = "=obterListaAmeacantes"  ;
static const char OBTER_AMEACADOS_CMD            [ ] = "=obterListaAmeacados"   ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

TAB_tppTabuleiro   pTabuleiro ;

/***** Protótipos das funções encapuladas no módulo *****/

static void DestruirValor( void * pDado ) ;

static int CompararValor( void * pDado_1 , void * pDado_2 ) ;

static int IgualValor( void * pDado_1 , void * pDado_2 ) ;

/***********************************************************************
 *
 *  $FC Função: TTAB &Testar tabuleiro
 *
 *  $ED Descrição da função
 *     Pode ser criado apenas um tabuleiro.
 *
 *     Comandos disponíveis:
 *
 *     =resetteste
 *           - anula o tabuleiro. Provoca vazamento de memória
 *     =criarTabuleiro           condRetorno
 *     =inserirPeca              inx
 *     =moverPeca                inx    char         condRetorno
 *     =retirarPeca              inx    char         condRetorno
 *     =obterPeca                inx
 *     =obterListaAmeacantes     inx    condRetorno
 *     =obterListaAmeacados      inx    condRetorno
 *
 ***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
    
    int numLidos   = -1 ,
    CondRetEsp = -1  ;
    
    TST_tpCondRet CondRet ;
    
    char charParm1 ;
    char charParm2 ;
    char charParm3 ;
    char charParm4 ;

    char * nomeObtido ;
    char * corObtida ;
    
    LIS_tppLista listaRet ;
    
    /* Testar CriarTabuleiro */
    
    if ( strcmp( ComandoTeste , CRIAR_TABULEIRO_CMD ) == 0 )
    {
        numLidos = LER_LerParametros( "i" , &CondRetEsp ) ;
        
        if ( ( numLidos != 1 ) )
        {
            return TST_CondRetParm ;
        } /* if */

        printf("Vai chamar TAB_CriarTabuleiro\n");
        
        CondRet = TAB_CriarTabuleiro ( &pTabuleiro , "..\\pecas\\default\\config.conf" ) ;

        printf("Condicao de retorno da criar tabuleiro: %d\n", CondRet);
        
        return TST_CompararInt( CondRetEsp , CondRet ,
                                "Condicao de retorno errada ao criar tabuleiro." ) ;
        
    } /* fim ativa: Testar CriarTabuleiro */
    
    /* Testar DestruirTabuleiro */
    
    else if ( strcmp( ComandoTeste , DESTRUIR_TABULEIRO_CMD ) == 0 )
    {

        numLidos = LER_LerParametros( "i" , &CondRetEsp ) ;
        
        if ( ( numLidos != 1 ) )
        {
            return TST_CondRetParm ;
        } /* if */
        
        CondRet = TAB_DestruirTabuleiro ( pTabuleiro ) ;
        
        return TST_CompararInt( CondRetEsp , CondRet ,
                               "Condicao de retorno errada ao destruir tabuleiro." ) ;
        
    } /* fim ativa: Testar DestruirTabuleiro */
    
    /* Testar InserirPecaTabuleiro */
    
    else if ( strcmp( ComandoTeste , INSERIR_PECA_CMD ) == 0 )
    {

        numLidos = LER_LerParametros( "cccci" ,
                                      &charParm1 ,
                                      &charParm2 ,
                                      &charParm3 ,
                                      &charParm4 ,
                                      &CondRetEsp ) ;
        
        if ( ( numLidos != 5 ) )
        {
            return TST_CondRetParm ;
        } /* if */
        CondRet = TAB_InserirPecaTabuleiro ( charParm1 ,
                                             charParm2 ,
                                             charParm3 ,
                                             charParm4 ,
                                             pTabuleiro ) ;

        return TST_CompararInt( CondRetEsp , CondRet ,
                               "Condicao de retorno errada ao inserir peca no tabuleiro." ) ;
        
    } /* fim ativa: Testar InserirPecaTabuleiro */
    
    /* Testar MoverPecaTabuleiro */
    
    else if ( strcmp( ComandoTeste , MOVER_PECA_CMD ) == 0 )
    {

        numLidos = LER_LerParametros( "cccci" ,
                                      &charParm1 ,
                                      &charParm2 ,
                                      &charParm3 ,
                                      &charParm4 ,
                                      &CondRetEsp) ;
        
        if ( ( numLidos != 5 ) )
        {
            return TST_CondRetParm ;
        } /* if */
        CondRet = TAB_MoverPecaTabuleiro ( charParm1 ,
                                           charParm2 ,
                                           charParm3 ,
                                           charParm4 ,
                                           pTabuleiro ) ;
        return TST_CompararInt( CondRetEsp , CondRet ,
                               "Condicao de retorno errada ao mover peca no tabuleiro." ) ;
        
    } /* fim ativa: Testar MoverPecaTabuleiro */

    /* Testar RetirarPecaTabuleiro */
    
    else if ( strcmp( ComandoTeste , RETIRAR_PECA_CMD ) == 0 )
    {

        numLidos = LER_LerParametros( "cci" ,
                                      &charParm1 ,
                                      &charParm2 ,
                                      &CondRetEsp) ;
        
        if ( ( numLidos != 3 ) )
        {
            return TST_CondRetParm ;
        } /* if */
        
        CondRet = TAB_RetirarPecaTabuleiro ( charParm1 ,
                                             charParm2 ,
                                             pTabuleiro ) ;
        
        return TST_CompararInt( CondRetEsp , CondRet ,
                               "Condicao de retorno errada ao retirar peca no tabuleiro." ) ;
        
    } /* fim ativa: Testar RetirarPecaTabuleiro */
    
    /* Testar ObterCasaTabuleiro */
    
    else if ( strcmp( ComandoTeste , OBTER_CASA_CMD ) == 0 )
    {

        CSA_tppCasa casaObtida;
        CSA_tpCondRet csaRet;

        numLidos = LER_LerParametros( "cccci" ,
                                      &charParm1 ,
                                      &charParm2 ,
                                      &charParm3 ,
                                      &charParm4 ,
                                      &CondRetEsp) ;
        
        if ( ( numLidos != 5 ) )
        {
            return TST_CondRetParm ;
        } /* if */
        
        nomeObtido = ( char * ) malloc ( sizeof ( char ) ) ;
        corObtida = ( char * ) malloc ( sizeof ( char ) ) ;

        CondRet = TAB_ObterCasaTabuleiro( charParm1 ,
                                          charParm2 ,
                                          &casaObtida,
                                          pTabuleiro ) ;
        if ( CondRet == TAB_CondRetNaoExiste )
        {
            return TST_NotificarFalha( "A casa não existe." ) ;
        }
        if ( CondRet == TAB_CondRetCoordNaoExiste )
        {
            return TST_NotificarFalha( "A coordenada da casa não existe." ) ;
        }

        csaRet = CSA_ObterPecaCasa( nomeObtido , corObtida , casaObtida ) ;

        if ( csaRet != CSA_CondRetOK )
        {
            return TST_NotificarFalha( "A casa não existe." ) ;
        }
                if ( csaRet != CSA_CondRetOK )
        {
            return TST_NotificarFalha( "A casa não existe." ) ;
        }
        
        if ( charParm3 != ( *nomeObtido ) )
        {
            return TST_CompararString( &charParm3 , nomeObtido ,
                                      "Id da peca retornada nao corresponde ao id esperado." ) ;
        } /* if */
        
        else if ( charParm4 != ( *corObtida ) )
        {
            return TST_CompararString( &charParm4 , corObtida ,
                                      "Cor da peca retornada nao corresponde a cor esperada." ) ;
        } /* if */
        
        return TST_CompararInt( CondRetEsp , CondRet ,
                               "Condicao de retorno errada ao obter casa." ) ;
        
    } /* fim ativa: Testar ObterCasaTabuleiro */
    
    /* Testar ObterPecaTabuleiro */
    
    else if ( strcmp( ComandoTeste , OBTER_PECA_CMD ) == 0 )
    {

        numLidos = LER_LerParametros( "cccci" ,
                                      &charParm1 ,
                                      &charParm2 ,
                                      &charParm3 ,
                                      &charParm4 ,
                                      &CondRetEsp) ;
        
        if ( ( numLidos != 5 ) )
        {
            return TST_CondRetParm ;
        } /* if */
        
        nomeObtido = ( char * ) malloc ( sizeof ( char ) ) ;
        corObtida = ( char * ) malloc ( sizeof ( char ) ) ;
        
        CondRet = TAB_ObterPecaTabuleiro ( charParm1 ,
                                           charParm2 ,
                                           nomeObtido ,
                                           corObtida ,
                                           pTabuleiro ) ;
        
        if ( charParm3 != ( *nomeObtido ) )
        {
            return TST_CompararString( &charParm3 , nomeObtido ,
                                      "Id da peca retornada nao corresponde ao id esperado." ) ;
        } /* if */
        
        else if ( charParm4 != ( *corObtida ) )
        {
            return TST_CompararString( &charParm4 , corObtida ,
                                      "Cor da peca retornada nao corresponde a cor esperada." ) ;
        } /* if */
        
        return TST_CompararInt( CondRetEsp , CondRet ,
                               "Condicao de retorno errada ao obter peca." ) ;
        
    } /* fim ativa: Testar ObterPecaTabuleiro */
    
    /* Testar ObterListaAmeacantesTabuleiro */
    
    else if ( strcmp( ComandoTeste , OBTER_AMEACANTES_CMD ) == 0 )
    {
        
        int i , j , igual ;
        CSA_tppCasa casaTst ;
        CSA_tppCasa vetCasaTst[1] ;
        CSA_tppCasa casaAtual ;

        numLidos = LER_LerParametros( "cci" ,
                                     &charParm1 ,
                                     &charParm2 ,
                                     &CondRetEsp) ;
        
        if ( ( numLidos != 3 ) )
        {
            return TST_CondRetParm ;
        } /* if */
        
        i = charParm2 - '0' ;
        j = charParm1 - 'A' + 1 ;
        
        
        CondRet = CSA_CriarCasa( &casaAtual ) ;

        if ( CondRet == CSA_CondRetFaltouMemoria )
        {
            CondRet = TAB_CondRetNaoExiste ;
            return TST_CompararInt( CondRetEsp , CondRet ,
                                   "Condicao de retorno errada ao obter lista de ameacantes." ) ;
        } /* if */
        
        CondRet = CSA_CriarCasa( &casaTst ) ;
        if ( CondRet == CSA_CondRetFaltouMemoria )
        {
            CondRet = TAB_CondRetNaoExiste ;
            return TST_CompararInt( CondRetEsp , CondRet ,
                            "Condicao de retorno errada ao obter lista de ameacantes." ) ;
        } /* if */
        
        
        CondRet = CSA_InserirPecaCasa( 'V' ,
                                       'V' ,
                                       casaTst ) ;
        if ( CondRet == CSA_CondRetNaoExiste )
        {
            CondRet = TAB_CondRetNaoExiste ;
            return TST_CompararInt( CondRetEsp , CondRet ,
                            "Condicao de retorno errada ao obter lista de ameacantes." ) ;
        } /* if */
        
        
        vetCasaTst[0] = casaTst ;
        
        CondRet = TAB_ObterCasaTabuleiro( charParm1 ,
                                          charParm2 ,
                                          &casaAtual ,
                                          pTabuleiro ) ;
        if ( CondRet != TAB_CondRetOK )
        {
            return TST_CompararInt( CondRetEsp , CondRet ,
                                   "Condicao de retorno errada ao obter lista de ameacantes." ) ;
        } /* if */
        
        
        CondRet = CSA_ModificarListaAmeacantesCasa( vetCasaTst ,
                                                    1 ,
                                                    casaAtual ) ;
        if ( CondRet == CSA_CondRetNaoExiste )
        {
            CondRet = TAB_CondRetNaoExiste ;
            return TST_CompararInt( CondRetEsp , CondRet ,
                                   "Condicao de retorno errada ao obter lista de ameacantes." ) ;
        } /* if */
        
        
        CondRet = LIS_CriarLista( &listaRet ,
                                  "amts" ,
                                  DestruirValor ,
                                  CompararValor ,
                                  IgualValor ) ;
        if ( CondRet == LIS_CondRetFaltouMemoria )
        {
            CondRet = TAB_CondRetNaoExiste ;
            return TST_CompararInt( CondRetEsp , CondRet ,
                            "Condicao de retorno errada ao obter lista de ameacantes." ) ;
        } /* if */
        
        
        CondRet = TAB_ObterListaAmeacantesTabuleiro ( charParm1 ,
                                                      charParm2 ,
                                                      &listaRet ,
                                                      &listaRet ,
                                                      pTabuleiro ) ;
        
        if ( CondRet == TAB_CondRetOK )
        {
            CondRet = LIS_ObterValor( listaRet , ( void ** ) &casaAtual ) ;
            if ( CondRet == LIS_CondRetListaVazia )
            {
                CondRet = TAB_CondRetNaoExiste ;
                return TST_CompararInt( CondRetEsp , CondRet ,
                                "Condicao de retorno errada ao obter lista de ameacantes." ) ;
            } /* if */
            
            CondRet = CSA_CompararCasa( casaAtual , casaTst , &igual ) ;
            if ( CondRet == CSA_CondRetNaoExiste )
            {
                CondRet = TAB_CondRetNaoExiste ;
                return TST_CompararInt( CondRetEsp , CondRet ,
                                "Condicao de retorno errada ao obter lista de ameacantes." ) ;
            } /* if */

            if ( igual )
            {
                return TST_CondRetOK ;
            }

        } /* if */
        
        LIS_DestruirLista( listaRet ) ;
        
        return TST_CompararInt( CondRetEsp , CondRet ,
                               "Condicao de retorno errada ao obter lista de ameacantes." ) ;
        
    } /* fim ativa: Testar ObterListaAmeacantesTabuleiro */

    /* Testar ObterListaAmeacadosTabuleiro */
    
    else if ( strcmp( ComandoTeste , OBTER_AMEACADOS_CMD ) == 0 )
    {
        
        int i , j , igual ;
        CSA_tppCasa casaTst ;
        CSA_tppCasa vetCasaTst[1] ;
        CSA_tppCasa casaAtual ;

        numLidos = LER_LerParametros( "cci" ,
                                     &charParm1 ,
                                     &charParm2 ,
                                     &CondRetEsp) ;
        
        if ( ( numLidos != 3 ) )
        {
            return TST_CondRetParm ;
        } /* if */
        
        i = charParm2 - '0' ;
        j = charParm1 - 'A' + 1 ;

        CondRet = CSA_CriarCasa( &casaAtual ) ;
        if ( CondRet == CSA_CondRetFaltouMemoria )
        {
            CondRet = TAB_CondRetNaoExiste ;
            return TST_CompararInt( CondRetEsp , CondRet ,
                                   "Condicao de retorno errada ao obter lista de ameacantes." ) ;
        } /* if */
        
        CondRet = CSA_CriarCasa( &casaTst ) ;
        if ( CondRet == CSA_CondRetFaltouMemoria )
        {
            CondRet = TAB_CondRetNaoExiste ;
            return TST_CompararInt( CondRetEsp , CondRet ,
                                   "Condicao de retorno errada ao obter lista de ameacantes." ) ;
        } /* if */

        CondRet = CSA_InserirPecaCasa( 'V' ,
                                      'V' ,
                                      casaTst ) ;
        if ( CondRet == CSA_CondRetNaoExiste )
        {
            CondRet = TAB_CondRetNaoExiste ;
            return TST_CompararInt( CondRetEsp , CondRet ,
                                   "Condicao de retorno errada ao obter lista de ameacantes." ) ;
        } /* if */

        vetCasaTst[0] = casaTst ;
        
        CondRet = TAB_ObterCasaTabuleiro( charParm1 ,
                                         charParm2 ,
                                         &casaAtual ,
                                         pTabuleiro ) ;
        if ( CondRet != TAB_CondRetOK )
        {
            return TST_CompararInt( CondRetEsp , CondRet ,
                                   "Condicao de retorno errada ao obter lista de ameacantes." ) ;
        } /* if */
        
        CondRet = CSA_ModificarListaAmeacadosCasa( vetCasaTst ,
                                                   1 ,
                                                   casaAtual ) ;
        if ( CondRet == CSA_CondRetNaoExiste )
        {
            CondRet = TAB_CondRetNaoExiste ;
            return TST_CompararInt( CondRetEsp , CondRet ,
                                   "Condicao de retorno errada ao obter lista de ameacantes." ) ;
        } /* if */
        
        CondRet = LIS_CriarLista( &listaRet ,
                                 "amts" ,
                                 DestruirValor ,
                                 CompararValor ,
                                 IgualValor ) ;
        if ( CondRet == LIS_CondRetFaltouMemoria )
        {
            CondRet = TAB_CondRetNaoExiste ;
            return TST_CompararInt( CondRetEsp , CondRet ,
                            "Condicao de retorno errada ao obter lista de ameacantes." ) ;
        } /* if */
        
        CondRet = TAB_ObterListaAmeacadosTabuleiro ( charParm1 ,
                                                     charParm2 ,
                                                     &listaRet ,
                                                     &listaRet ,
                                                     pTabuleiro ) ;
        
        if ( CondRet == TAB_CondRetOK )
        {
            CondRet = LIS_ObterValor( listaRet , ( void ** ) &casaAtual ) ;
            if ( CondRet == LIS_CondRetListaVazia )
            {
                CondRet = TAB_CondRetNaoExiste ;
                return TST_CompararInt( CondRetEsp , CondRet ,
                                "Condicao de retorno errada ao obter lista de ameacantes." ) ;
            } /* if */
            
            CondRet = CSA_CompararCasa( casaAtual , casaTst , &igual ) ;
            if ( CondRet == CSA_CondRetNaoExiste )
            {
                CondRet = TAB_CondRetNaoExiste ;
                return TST_CompararInt( CondRetEsp , CondRet ,
                                "Condicao de retorno errada ao obter lista de ameacantes." ) ;
            } /* if */
            
            if ( igual )
            {
                return TST_CondRetOK ;
            }
            
        } /* if */
        
        LIS_DestruirLista( listaRet ) ;
        
        return TST_CompararInt( CondRetEsp , CondRet ,
                               "Condicao de retorno errada ao obter lista de ameacantes." ) ;
        
    } /* fim ativa: Testar ObterListaAmeacadosTabuleiro */
    
    return TST_CondRetNaoConhec ;
    
} /* Fim funÁ„o: TLIS &Testar lista */

/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
 *
 *  $FC Função: TLIS -Destruir valor
 *
 ***********************************************************************/

void DestruirValor( void * pDado )
{
    free ( pDado ) ;
    
} /* Fim Função: TLIS -Destruir valor */


/***********************************************************************
 *
 *  $FC Função: TLIS -Comparar valor
 *
 ***********************************************************************/

int CompararValor( void * pDado_1 , void * pDado_2 )
{
    char * valor_1 = ( char * ) pDado_1 ;
    char * valor_2 = ( char * ) pDado_2 ;
    return strcmp( valor_1 , valor_2 ) ;
    
} /* Fim função: TLIS -Comparar valor */


/***********************************************************************
 *
 *  $FC Função: TLIS -Igual valor
 *
 ***********************************************************************/

int IgualValor( void * pDado_1 , void * pDado_2 )
{
    char * valor_1 = ( char * ) pDado_1 ;
    char * valor_2 = ( char * ) pDado_2 ;
    return strcmp( valor_1 , valor_2 ) ;
    
} /* Fim função: TLIS -Igual valor */


/********** Fim do mÛdulo de implementaÁ„o: TLIS Teste lista de sÌmbolos **********/

/***************************************************************************
 *  $MCI Módulo de implementação: TJGO Teste jogo
 *
 *  Arquivo gerado:              TESTJGO.C
 *  Letras identificadoras:      TJGO
 *
 *  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
 *  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
 *
 *  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
 *  Gestor:  LES/DI/PUC-Rio
 *  Autores: lff, iars, vas
 *
 *  $HA Histórico de evolução:
 *     Versão  Autor    Data     Observações
 *     2       vas   12/nov/2016 correcao de diversos erros de sintaxe
 *     1       lff   05/nov/2016 início desenvolvimento
 *
 ***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "JOGO.H"


static const char CRIAR_JUIZ_CMD            [ ] = "=criarJuiz"        ;
static const char DESTRUIR_JUIZ_CMD         [ ] = "=destruirJuiz"     ;
static const char INICIAR_JOGO_CMD          [ ] = "=iniciarJogo"      ;
static const char TERMINAR_JOGO_CMD         [ ] = "=terminarJogo"     ;
static const char REALIZAR_JOGADA_CMD       [ ] = "=realizarJogada"   ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

JGO_tppJuiz   pJuiz ;

/***********************************************************************
 *
 *  $FC Função: TJGO &Testar jogo
 *
 *  $ED Descrição da função
 *
 *     Comandos disponíveis:
 *
 *     =resetteste
 *           - anula o jogo. Provoca vazamento de memória
 *     =criarJuiz           condRetorno
 *     =destruirJuiz        condRetorno
 *     =iniciarJogo         condRetorno
 *     =terminarJogo        condRetorno
 *     =realizarJogada      lAtual  cAtual  lDestino  cDestino  corJog  evento  condRetorno
 *
 ***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
    
    int numLidos = -1 ,
    CondRetEsp = -1 ;
    
    TST_tpCondRet CondRet ;
    
    char linhaAtual ;
    char colunaAtual ;
    char linhaDestino ;
    char colunaDestino ;
    char pathArqConfig[100] ;
    JGO_tpEventoOcorrido EveOcor , EveOcorEsp ;
    JGO_tpCorJogador JgAtual ;
    
    /* Testar CriarJuiz */
    
    if ( strcmp( ComandoTeste , CRIAR_JUIZ_CMD ) == 0 )
    {
        numLidos = LER_LerParametros( "i" , &CondRetEsp ) ;
        
        if ( ( numLidos != 1 ) )
        {
            return TST_CondRetParm ;
        } /* if */
        
        CondRet = JGO_CriarJuiz ( &pJuiz ) ;
        
        return TST_CompararInt( CondRetEsp , CondRet ,
                                "Condicao de retorno errada ao criar juiz." ) ;
        
    } /* fim ativa: Testar CriarJuiz */
    
    /* Testar DestruirJuiz */
    
    else if ( strcmp( ComandoTeste , DESTRUIR_JUIZ_CMD ) == 0 )
    {

        numLidos = LER_LerParametros( "i" , &CondRetEsp ) ;
        
        if ( ( numLidos != 1 ) )
        {
            return TST_CondRetParm ;
        } /* if */
        
        CondRet = JGO_DestruirJuiz ( pJuiz ) ;

        pJuiz = NULL ;
        
        return TST_CompararInt( CondRetEsp , CondRet ,
                               "Condicao de retorno errada ao destruir juiz." ) ;
        
    } /* fim ativa: Testar DestruirJuiz */
    
    /* Testar IniciarJogo */
    
    if ( strcmp( ComandoTeste , INICIAR_JOGO_CMD ) == 0 )
    {
        numLidos = LER_LerParametros( "si" , pathArqConfig , &CondRetEsp ) ;

        printf("%s\n", pathArqConfig);
        
        if ( ( numLidos != 2 ) )
        {
            return TST_CondRetParm ;
        } /* if */
        
        CondRet = JGO_IniciarJogo ( pJuiz , pathArqConfig ) ;
        
        return TST_CompararInt( CondRetEsp , CondRet ,
                               "Condicao de retorno errada ao iniciar jogo." ) ;
        
    } /* fim ativa: Testar IniciarJogo */
    
    /* Testar TerminarJogo */
    
    if ( strcmp( ComandoTeste , TERMINAR_JOGO_CMD ) == 0 )
    {
        numLidos = LER_LerParametros( "i" , &CondRetEsp ) ;
        
        if ( ( numLidos != 1 ) )
        {
            return TST_CondRetParm ;
        } /* if */
        
        CondRet = JGO_TerminarJogo ( pJuiz ) ;
        
        return TST_CompararInt( CondRetEsp , CondRet ,
                               "Condicao de retorno errada ao terminar jogo." ) ;
        
    } /* fim ativa: Testar TerminarJogo */
    
    /* Testar RealizarJogada */
    
    if ( strcmp( ComandoTeste , REALIZAR_JOGADA_CMD ) == 0 )
    {
        numLidos = LER_LerParametros( "cccciii" ,
                                      &colunaAtual ,
                                      &linhaAtual ,
                                      &colunaDestino ,
                                      &linhaDestino ,
                                      &JgAtual ,
                                      &EveOcorEsp ,
                                      &CondRetEsp ) ;
        
        if ( ( numLidos != 7 ) )
        {
            return TST_CondRetParm ;
        } /* if */
        
        CondRet = JGO_RealizarJogada ( pJuiz ,
                                       JgAtual ,
                                       &EveOcor ,
                                       linhaAtual ,
                                       colunaAtual ,
                                       linhaDestino ,
                                       colunaDestino ) ;

        if ( CondRet )
        {
            return TST_CompararInt( CondRetEsp , CondRet ,
                                "Condicao de retorno errada ao realizar jogada." ) ;
        } /* if */
        
        if ( EveOcor != EveOcorEsp )
        {
            return TST_CondRetOK;
            return TST_CompararInt( EveOcorEsp , EveOcor ,
                                    "Evento Ocorrido errado ao realizar jogada." ) ;
        } /* if */
        
        return TST_CompararInt( CondRetEsp , CondRet ,
                                "Condicao de retorno errada ao realizar jogada." ) ;
        
    } /* fim ativa: Testar RealizarJogada */
    
    return TST_CondRetNaoConhec ;
    
} /* Fim funÁ„o: TJGO &Testar jogo */


/********** Fim do mÛdulo de implementaÁ„o: TJGO Teste jogo **********/

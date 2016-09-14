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
*     2       lff   14/set/2016 codificação das funções de impressão e comparação
*     1       vas   13/set/2016 início desenvolvimento
*
*  $ED Descrição do módulo
*
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define ETIQUETA_NOMINAL_OWN
#include "ETIQUETA_NOMINAL.H"
#undef ETIQUETA_NOMINAL_OWN


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

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: ETI  &Criar etiqueta nominal
*  ****/

ETI_tppEtiquetaNominal ETI_CriarEtiquetaNominal( char* pIniciais, char* pNomeCompleto )
{

    ETI_tpEtiquetaNominal * pEtiquetaNominal = NULL;

    pEtiquetaNominal = ( ETI_tpEtiquetaNominal * ) malloc( sizeof( ETI_tpEtiquetaNominal ));
    if ( pEtiquetaNominal == NULL )
    {
      return NULL;
    } /* if */

    if ( pIniciais != NULL )
    {
      pEtiquetaNominal->iniciais = ( char* ) malloc( strlen(pIniciais) + 1 ) ;
      strcpy( pEtiquetaNominal->iniciais, pIniciais ) ;
    } else
    {
      pEtiquetaNominal->iniciais = NULL; 
    } /* if */

    if ( pNomeCompleto != NULL )
    {
      pEtiquetaNominal->nomeCompleto = ( char* ) malloc( strlen(pNomeCompleto) + 1 ) ;
      strcpy( pEtiquetaNominal->nomeCompleto, pNomeCompleto ) ;
    } else
    {
      pEtiquetaNominal->nomeCompleto = NULL; 
    } /* if */

    return pEtiquetaNominal;

} /* Fim função: ETI  &Criar etiqueta nominal */

/***************************************************************************
*
*  Função: ETI  &Destruir etiqueta nominal
*  ****/

void ETI_DestruirEtiquetaNominal( ETI_tppEtiquetaNominal pEtiquetaNominal )
{
    #ifdef _DEBUG
      assert( pEtiquetaNominal != NULL ) ;
    #endif

    if ( pEtiquetaNominal->iniciais != NULL )
    {
      free( pEtiquetaNominal->iniciais ) ;
    } /* if */

    if ( pEtiquetaNominal->nomeCompleto != NULL )
    {
      free( pEtiquetaNominal->nomeCompleto ) ;
    } /* if */
    pEtiquetaNominal->iniciais = NULL;
    pEtiquetaNominal->nomeCompleto = NULL;
    free(pEtiquetaNominal);

} /* Fim função: ETI  &Destruir etiqueta nominal */

/***************************************************************************
 *
 *  Função: ETI  &Imprimir conteúdo etiqueta nominal
 *  ****/

void ETI_ImprimirConteudoEtiquetaNominal( ETI_tppEtiquetaNominal pEtiquetaNominal )
{
    printf("Conteudo da etiqueta nominal:\n");
    
    if (pEtiquetaNominal == NULL)
    {
        printf("O ponteiro e nulo.\n");
    }
    else
    {
        if (pEtiquetaNominal->iniciais == NULL)
        {
            printf("Iniciais:  NULL\n");
        }
        else
        {
            printf("Iniciais:  %s\n", pEtiquetaNominal->iniciais);
        }/* if */
        
        if (pEtiquetaNominal->iniciais == NULL)
        {
            printf("Nome completo:  NULL\n");
        }
        else
        {
            printf("Nome completo:  %s\n", pEtiquetaNominal->nomeCompleto);
        }/* if */
    }/* if */
    
} /* Fim função: ETI  &Imprimir conteúdo etiqueta nominal */

/***************************************************************************
 *
 *  Função: ETI  &Comparar as iniciais de duas etiquetas nominais
 *  ****/

int ETI_CompararIniciaisEtiquetaNominal( ETI_tppEtiquetaNominal pEtiquetaNominal1, ETI_tppEtiquetaNominal pEtiquetaNominal2 )
{
    int i=0, dif;
    
    /* Tratar etiqueta nominal nula */
    if (pEtiquetaNominal1 == NULL)
    {
        return -1;
    }/* if */
    
    if (pEtiquetaNominal2 == NULL)
    {
        return 1;
    }/* if */
    
    /* fim ativa: Tratar etiqueta nominal nula */
    
    while (pEtiquetaNominal1->iniciais[i] != '\0')
    {
        dif = pEtiquetaNominal1->iniciais[i] - pEtiquetaNominal2->iniciais[i];
        if (dif<0)
        {
            return -1;
        }/* if */
        
        if (dif>0)
        {
            return 1;
        }/* if */
        
        if (dif == pEtiquetaNominal1->iniciais[i])
        {
            return 1;
        }/* if */
        
    }/* while */
    
    if (pEtiquetaNominal2->iniciais[i] != '\0')
    {
        return -1;
    }/* if */
    
    return 0;

} /* Fim função: ETI  &Comparar as iniciais de duas etiquetas nominais */

/***********************************************************************
 *
 *  $FC Função: ETI  &Comparar conteúdo de duas etiquetas nominais
 *  ****/

int ETI_CompararConteudoEtiquetaNominal(ETI_tppEtiquetaNominal pEtiquetaNominal1, ETI_tppEtiquetaNominal pEtiquetaNominal2)
{
    /* Tratar etiqueta nominal nula */
    if ((pEtiquetaNominal1 == NULL) && (pEtiquetaNominal2 == NULL))
    {
        return 1;
    }
    else
    {
        if ((pEtiquetaNominal1 == NULL) || (pEtiquetaNominal2 == NULL))
        {
            return 0;
        }/* if */
    }/* if */
    
    /* fim ativa: Tratar etiqueta nominal nula */
    
    /* Tratar membro 'iniciais' nulo */
    if ((pEtiquetaNominal1->iniciais == NULL) && (pEtiquetaNominal2->iniciais == NULL))
    {
        if ((pEtiquetaNominal1->nomeCompleto == NULL) && (pEtiquetaNominal2->nomeCompleto == NULL))
        {
            return 1;
        }
        else
        {
            if ((pEtiquetaNominal1->nomeCompleto == NULL) || (pEtiquetaNominal2->nomeCompleto == NULL))
            {
                return 0;
            }
            else
            {
                if (strcmp(pEtiquetaNominal1->nomeCompleto, pEtiquetaNominal2->nomeCompleto) != 0)
                {
                    return 0;
                }/* if */
                
                return 1;
            }/* if */
            
        }/* if */
        
    }
    else {
        if ((pEtiquetaNominal1->iniciais == NULL) || (pEtiquetaNominal2->iniciais == NULL))
        {
            return 0;
        }/* if */
        
    }/* if */
    
    /* fim ativa: Tratar membro 'iniciais' nulo */
    
    /* Tratar membro 'nomeCompleto' nulo */
    if ((pEtiquetaNominal1->nomeCompleto == NULL) && (pEtiquetaNominal2->nomeCompleto == NULL))
    {
        if ((pEtiquetaNominal1->iniciais == NULL) && (pEtiquetaNominal2->iniciais == NULL))
        {
            return 1;
        }
        else
        {
            if ((pEtiquetaNominal1->iniciais == NULL) || (pEtiquetaNominal2->iniciais == NULL))
            {
                return 0;
            }
            else
            {
                if (strcmp(pEtiquetaNominal1->iniciais, pEtiquetaNominal2->iniciais) != 0)
                {
                    return 0;
                }/* if */
                
                return 1;
            }/* if */
            
        }/* if */
        
    }
    else {
        if ((pEtiquetaNominal1->nomeCompleto == NULL) || (pEtiquetaNominal2->nomeCompleto == NULL))
        {
            return 0;
        }/* if */
        
    }/* if */
    
    /* fim ativa: Tratar membro 'nomeCompleto' nulo */
    
    if (strcmp(pEtiquetaNominal1->iniciais, pEtiquetaNominal2->iniciais) == 0)
    {
        if (strcmp(pEtiquetaNominal1->nomeCompleto, pEtiquetaNominal2->nomeCompleto) == 0)
        {
            return 1;
        }/* if */
        
    }/* if */
    
    return 0;
    
} /* Fim função: ETI  &Comparar conteúdo de duas etiquetas nominais */

/********** Fim do módulo de implementação: ETI Etiqueta nominal **********/

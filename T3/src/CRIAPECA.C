/***************************************************************************
 *
 *  $MCD Módulo de implementação: CRP  Módulo de Criação de Peça
 *
 *  Arquivo gerado:              CRP.h
 *  Letras identificadoras:      CRP
 *
 *  Nome da base de software:    ArcabouÁo para a automaÁ„o de testes de programas redigidos em C
 *  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
 *
 *  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
 *  Autores: iars

 *  $HA Histórico de evolução:
 *     Versão  Autor    Data     Observações
 *     1       iars   10/out/2016 início desenvolvimento
 *
 ***************************************************************************/

#include   <stdio.h>
#include   <dirent.h>

#define PECAS_DIR "..\\pecas\\default\\pecas"

/***** Protótipos das funções encapuladas no módulo *****/


/***************************************************************************
 *
 *  Função: CRP  &Criar peça
 *  ****/

int main( int argc, char* argv )
{
    DIR *dir;

    struct dirent *ent;
    // Code To Print All Files in a Directory
    // http://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
    if ((dir = opendir (PECAS_DIR)) != NULL) {
      /* print all the files and directories within directory */
      while ((ent = readdir (dir)) != NULL) {
        printf ("%s\n", ent->d_name);
      }
      closedir (dir);
    } else {
      /* could not open directory */
      printf("ERRO FATAL: Nao foi possível abrir a pasta %s.",PECAS_DIR);
      return 1;
    }
} /* Fim função: CRP */

/***************************************************************************

/********** Fim do módulo de Criação de Peças **********/


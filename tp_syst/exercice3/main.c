#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/ipc.h>
#include <errno.h>
#include <fcntl.h>

int main()
{
    int n;
    // on crée un fichier

    FILE *file = fopen("matrice","w+");
    printf("Entrez le rang de la matrice carré : ");
    scanf("%d",&n);
    printf("\n");

    //On crée une matrice selon laquelle on stock les éléments

    int M[n][n];
    //écriture du rang de la matrice dans file
    fprintf(file,"%d\n",n);
    printf("Entrez les valeurs de la matrice \n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("Entrez M[%d][%d] : ",i,j);
            scanf("%d",&M[i][j]);
           // printf("%s",M[i][j]);
           fprintf(file,"%d\t",M[i][j]);

        }

        fprintf(file,"%s","\n");
    }



    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            i=-1;
            j=-1;
            if()

        }
    }

    fclose(file);

   return 0;
}
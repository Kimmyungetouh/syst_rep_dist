
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc,char** argv)
{
    pid_t pid1,pid2,pid3;
    int status;
    pid1=fork();
    char **argp= {"Q",NULL};
    if(pid1<0)
    {
        perror("Erreur de création du processus 1");
        exit(EXIT_FAILURE);
    }
    if(pid1==0)
    {
        execv("./Q",argp);
       
    }
    else
    {
        pid2=fork();
       // char** argp={"./Q",NULL,NULL};
        if(pid2<0)
        {
            perror("Erreur de création du processus 2");
            exit(EXIT_FAILURE);
        }
        if(pid2==0)
        {
            execv("./Q",argp);
             pid1=wait(&status);
            
        }
        else
        {
            pid3=fork();
            //char** argp={"./Q",NULL,NULL};
            if(pid3<0)
            {
                perror("Erreur dans la création du processus 3");
                exit(EXIT_FAILURE);
            }
            if(pid3==0)
            {
                execv("./Q",argp);
                pid1=wait(&status);
                pid2=wait(&status);
            }
            else
            {
                pid1 = wait(&status);
                pid2 = wait(&status);
                pid3 = wait(&status);
                printf("Statut de l'arret du fils  %d 😁️\n", pid1);
                printf("Statut de l'arret du fils  %d 😐️\n", pid2);
                printf("Statut de l'arret du fils  %d 😁️\n", pid3);
            }
        }
    }a
    return 0;
}


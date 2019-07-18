/*
 * sans titre.c
 * 
 * Copyright 2019 ACE <ace@BLANK>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 *myunggodwin@gmail.com
 * 
 * 
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h> 
#include <sys/shm.h>  
#include <sys/sem.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>           
#include <sys/stat.h>      
#include <semaphore.h>

int main()
{
	int n;
	printf("Entrez la dimension de la matrice : ");
	scanf("%d",&n);
	/*int n,i,j,k;
	int M[n][n];
	printf("Entrez la dimension de la matrice : ");
	printf("Entrez les valeurs de la matrice : ");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("M[%d][%d] \t",&M[i][j]);
		}
	}
	scanf("%d",&n);*/
    pid_t pid1,pid2,pid3;
    int status;
	key_t key = ftok("shmfile",65);

    int a = 0; // shared data (la variable partagée)

    // On demande au system de creer la memoire partagee 
    int shmid = shmget(key,1024,0666|IPC_CREAT); 
    // on attache la memoire partagee a str
    int **mat = (int**) shmat(shmid,(void*)0,0); 
    // ecriture de 0 dans la mémoire partagée
   // mat=M;
    
    for(i=0;i<n;i++)
    {
		for(j=0;j<n;j++){
			for(k=0;k<n;k++)
			{
				mat[i][j] += M[i][j] * M[j][i];
			}
		}
	}
	pid1=fork();
   // char **argp= {"p1",NULL};
    if(pid1<0)
    {
        perror("Erreur de création du processus 1");
        exit(EXIT_FAILURE);
    }
    if(pid1==0)
    {
		sleep(3);
        execv("./p1",NULL);
       
    }
    else
    {
        pid2=fork();
       // char** argp={"./p",NULL,NULL};
        if(pid2<0)
        {
            perror("Erreur de création du processus 2");
            exit(EXIT_FAILURE);
        }
        if(pid2==0)
        {
			sleep(1);
            execv("./p",NULL);
             pid1=wait(&status);
            
        }
        else
        {
            pid3=fork();
            //char** argp={"./p",NULL,NULL};
            if(pid3<0)
            {
                perror("Erreur dans la création du processus 3");
                exit(EXIT_FAILURE);
            }
            if(pid3==0)
            {
				sleep(5);
                execv("./p",NULL);
                pid1=wait(&status);
                pid2=wait(&status);
            }
            else
            {
                pid1 = wait(&status);
                pid2 = wait(&status);
                pid3 = wait(&status);
                printf("çà vient\n");
                printf("Statut de l'arret du fils  %d 😁️\n", pid1);
                printf("Statut de l'arret du fils  %d 😐️\n", pid2);
                printf("Statut de l'arret du fils  %d 😁️\n", pid3);
                printf("Valeur dans la mémoire partagée %d\n",atoi(str));
            }
        }
    }
    shmdt(mat);
    //destruction de la mémoire
    shmctl(shmid,IPC_RMID,NULL);
    
	return 0;
}


/*
 * sol2.c
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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
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
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>


union semun {
   int  val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INF
                              (Linux-specific) */
};


int main(int argc, char *argv[])
{
    pid_t pid1, pid2,pid3;
    int status; // le status des fils
    union semun sem_arg; // paramètre pour configurer le semaphore
    // Argument du premier processus
    char *argp1[] = {"w", NULL, NULL};
    // clé pour le semaphore 
    key_t sem_key = ftok("semfile",75);
    // on demande au system de nous créer le semaphore
    int semid = semget(sem_key, 1, 0666|IPC_CREAT);

    // la valeur du semaphore est initialisée à 1
    sem_arg.val = 1;
    if(semctl(semid, 0, SETVAL, sem_arg)==-1){
       perror("semctl");
       exit(1);
    }
    
    // clé pour la mémoire protégée
    key_t key = ftok("shmfile",65);

    int a = 0; // shared data (la variable partagée)

    // On demande au system de creer la memoire partagee 
    int shmid = shmget(key,1024,0666|IPC_CREAT); 
    // on attache la memoire partagee a str
    char *str = (char*) shmat(shmid,(void*)0,0); 
    // ecriture de 0 dans la mémoire partagée
    sprintf(str, "%d", a);

    //création du premier processus (pour lancer le process w)
    pid1 = fork();
    if(pid1 < 0){
          perror("Erreur de création du processus\n");
          exit(EXIT_FAILURE);
    }

    if(pid1 == 0){
        execv("./q", NULL);
    }

    else{
        // creation du second processus pour lancer r
        //char *argp2[] = {"Q1", NULL, NULL};
        pid2 = fork();
        sleep(4);
        if(pid2 < 0){
          perror("Erreur de création du second processus\n");
          pid1 = wait(&status);
          exit(EXIT_FAILURE);
        }

        if(pid2 == 0){
            execv("./q", NULL);
        }

        else{
			// char *argp3[] = {"q", NULL, NULL};
        pid3 = fork();
        sleep(4);
        if(pid3 < 0){
          perror("Erreur de création du processus 3\n");
          pid1 = wait(&status);
          pid2 = wait(&status);
          exit(EXIT_FAILURE);
        }

        if(pid3 == 0){
            execv("./q", NULL);
        }
        else{
                // On attend la fin des deux processus
                pid1 = wait(&status);
                printf("Status de l'arret du fils %d %d\n", status, pid1);
                pid2 = wait(&status);
                printf("Status de l'arret du fils %d %d\n", status, pid2);
				pid3 = wait(&status);
                printf("Status de l'arret du fils %d %d\n", status, pid3);
                // on lit la dernière valeur de la variable partagée
                a = atoi(str);
                printf("Valeur Finale de a = %d\n", a);
                //le processus détache str de la mémoire partagée 
                shmdt(str); 
                // destruction de la mémoire 
                shmctl(shmid,IPC_RMID,NULL);
                // des truction du semaphore
                if(semctl(semid, 0, IPC_RMID, NULL) == -1){
                   perror("semctl");
                   exit(1);
                }	
        }

        
    } 
    
}
return 0;
}

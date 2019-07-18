/*
 * q.c
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




#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <sys/sem.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

#define ITER 100

union semun {
   int  val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INF
                              (Linux-specific) */
};

int main() 
{ 
  // on genere la clé de la mémoire partagée
  key_t key = ftok("shmfile",65); 
  int i;
  int a = 0; // shared data
  struct sembuf sb = {0, 0, 0}; 
  union semun sem_arg;

  // clé pour le semaphore 
  key_t sem_key = ftok("semfile",75);
  // on demande au system de nour créer le semaphore
  int semid = semget(sem_key, 1, 0666);
    

  // shmget returns an identifier in shmid 
  int shmid = shmget(key,1024,0666); 
  // shmat to attach to shared memory 
  char *str = (char*) shmat(shmid,(void*)0,0); 


  for(i=0; i < ITER; i++){
     // tentative de verrou du semaphore
     sb.sem_op = -1;
     if(semop(semid, &sb,1) == -1){
       perror("sempo");
       exit(1);
     }
     
     for(i=0;i<ITER;i++)
     {
		 a = atoi(str);
		 a++;
		 sprintf(str, "%d", a);
	 }
  /*   // lecture de a
     a = atoi(str);
     printf("Proc w %d %d\n", getpid(), a);
     // modification de a
     a = a + 1;
     sleep(a);
     // ecriture de a
     sprintf(str, "%d", a);*/
     // déverrouillage du semaphore
     sb.sem_op = 1;
     if(semop(semid, &sb,1) == -1){
       perror("sempo");
       exit(1);
     } 
  }	
  //detach from shared memory 
  shmdt(str); 
  return 0; 
} 

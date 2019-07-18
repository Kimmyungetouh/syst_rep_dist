
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <sys/sem.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>         
#include <sys/stat.h>       




int main(int argc,char** argv) 
{ 
	int i,j,k,n;
  // on genere la clé de la mémoire partagée
  key_t key = ftok("shmfile",65); 
  int i;
  int a = 0; // shared data

    

  // shmget returns an identifier in shmid 
  int shmid = shmget(key,1024,0666); 
  // shmat to attach to shared memory 
  int **mat = (int**) shmat(shmid,(void*)0,0); 
  

 M=mat;
 
  for(i=0;i<n;i++)
    {
		for(j=0;j<n;j++){
			for(k=0;k<n;k++)
			{
				mat[i][j] += M[i][j] * M[j][i];
			}
		}
	}
     
     
     printf("Proc w %d %d\n", getpid(), a);
     // modification de a
    // sleep(4);
    
  //detach from shared memory 
  shmdt(mat); 
  return 0; 
} 


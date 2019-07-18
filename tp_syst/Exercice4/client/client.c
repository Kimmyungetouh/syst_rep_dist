

#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define GREETING "BONJOUR SERVEUR"
int main(int argc, char *argv[]){
   int cfd; // socket du client
   int success; // etat de la connection
   int port;
   FILE *file;
   char c;
   struct sockaddr_in srv_addr; // socket addr du serveur 

   if(argc!=4){
     printf("USAGE: ./client <serveur_ip_addr> <serveur_port> <nom_du_fichier>\n");
     exit(-1);
   }
    char *nameFile = argv[3];
   cfd = socket(AF_INET, SOCK_STREAM, 0); // création de la socket
   if (cfd < 0){ // Une erreur s'est produite la socket n'a pas pu être créer
      printf("Le SE n'a pas pu créer la socket %d\n", cfd);
      exit(-1);
   }
   /* donne une identite a la socket. 
    * AF_INET pour dire que c'est le protocole TCP qui sera utilisé
    * SRV_PORT est le port du serveur distant que le client desire contacter
    * SRV_ADDR est l'adresse du serveur distant que le client desire contacter
    * */
   port = atoi(argv[2]);

   srv_addr.sin_family = AF_INET;
   srv_addr.sin_port = htons (port);
   inet_aton(argv[1], (struct in_addr *)&srv_addr.sin_addr.s_addr);

   /* connexion au serveur 
    * A l'aide de la fonction connect() on se connecte au serveur distant
    * on utilise pour cela la socket qui a été créée par l'SE du client 
    * on utilise aussi l'identité du serveur qui vient d'être construite */ 
   success = connect(cfd, (struct sockaddr *) &srv_addr,
                 sizeof(struct sockaddr_in));
   if(success < 0){ // la connexion a echouée
      printf("Impossible de se connecter au serveur %s:%d error %d\n", 
               argv[1], port, success);
      exit(-1);
   }
   /* */
   send(cfd, nameFile, sizeof(nameFile), 0);
   sleep(5);
    file = fopen("fichier", "r");
    if(file != NULL)
    {
      do
      {
        c = fgetc(file);
        send(cfd, &c, sizeof(c), 0);
      }while(c!=EOF); 
    } 
    else
    {
      
    }  
   //send(cfd, " Bonjour", sizeof("Bonjour"), 0);
     
   //send(cfd, GREETING, sizeof(GREETING), 0);

   /* Après avoir dit bonjour au serveur nous demandons au SE de libérer
    * la socket */
   close(cfd);
   return(0);
}


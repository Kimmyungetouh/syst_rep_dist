# syst_rep_dist

Exo 1

création avec des processus avec fork() et execv()

Exo2

1) La valeur est variable

2) Il faut bloquer des processus pour qu'un seul travaille et les autres attendent la fin pour agir.
Utilisation de semaphore

3) 300 est la bonne solution

Exo3

1) Eviter que les processus écrivent dans un désordre

2) utiliser un marqueur et verrouiller chaque case i,j pour l'occuper que par un seul processus, lecture dans un fichier, utilisation de de sémaphore et de 3 mémoires partagées;
3)

Exo 4

1) envoie et réception de fichiern
2) le client envoie le fichier par bytes sur le serveur en ayant envoyé le nom, le serveur crée un fichier de meme nom et écrit par bytes le fichier  dans celui après avoir envoyé ok au client qui attend cette réponse avant d'écrire par bytes sur le socket auquel le serveur lit. 

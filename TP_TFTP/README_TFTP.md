# TP Synthèse Informatique Majeure
## TP 2 - Client TFTP

**1. Utilisation des arguments passés à la ligne de commande des programmes gettftp et puttftp**

On récupère d'abord les informations sur la requête (nom de serveur et de fichier) sur la commande
des programmes gettftp et puttftp. Pour cela nous récupérons les informations passés en
arguments, avec le nom du serveur passé en argv[1] et le nom du fichier passé en argv[2].

<img width="164" alt="image" src="https://github.com/Im4dENSEA/TPSyntheseInfo/assets/146735291/3ebf4c7b-8c20-4b92-a851-bcd0928f852e">

**2.Appel à getaddrinfo pour obtenir l'adresse du serveur**

On utilise la fonction **getaddrinfo** pour obtenir l'adresse du serveur. Cette fonction prend un argument *hints* qui pointe sur une structure addrinfo qui est décrite
ci-dessous : 

<img width="257" alt="image" src="https://github.com/Im4dENSEA/TPSyntheseInfo/assets/146735291/c6047bc1-3c69-4aad-ba86-649f22448c59">

Cette structure liste les critères de sélection des structures d'adresses de sockets renvoyée dans la liste pointé par l'argument *res* dans la fonction **getaddrinfo**.
Si *hints* n'est pas NULL alors il pointe sur une truct addrinfo dont les membres à spécifier sont ai_family, ai_socktype et ai_protocol.

Ici l'on souhaite obtenir l'adresse du serveur donc char *node = serveur. 
La fonction *memset* permet d'allouer un espace de la mémoire

<img width="258" alt="image" src="https://github.com/Im4dENSEA/TPSyntheseInfo/assets/146735291/f69ba043-cb1a-40fd-8d1d-3c8aed69d84f">

**3.Réservation d'un socket de connexion vers le serveur**

On crée une connexion réservant un socket vers le serveur à l'aide de la fonction socket. 

<img width="253" alt="image" src="https://github.com/Im4dENSEA/TPSyntheseInfo/assets/146735291/36aad146-3fc7-4f97-ab0b-acbaaada9206">

<img width="374" alt="image" src="https://github.com/Im4dENSEA/TPSyntheseInfo/assets/146735291/45fe7142-a982-4fbf-9fac-bfcd5f5b1cb6">

**4 . Pour gettftp**
**a) Construction d'une requête en lecture (RRQ) correctement formée, et envoi au serveur.**

On cherche  à envoyer une requête en lecture au serveur afin de recevoir du serveur le fichier demandé. On va donc construire une Read Request (RRQ) selon la norme RFC 1350

<img width="377" alt="image" src="https://github.com/Im4dENSEA/TPSyntheseInfo/assets/146735291/d2476648-3f99-409b-9e2d-7b43302be178">

Cette requête est un tableau dont les deux premiers élements sont le Opcode 01 permettant d'identifier le paquet comme un paquet RRQ. On indique la fin du nom de fichier en fermant avec 0. On inscrit le mode choisi (ici « octet ») caractère par caractère et on ferme avec 0.
Nous obtenons ainsi dans notre fonction :

<img width="370" alt="image" src="https://github.com/Im4dENSEA/TPSyntheseInfo/assets/146735291/d29c5626-8c37-4bb0-ac83-80a84a75183f">

Lorsque l'on teste notre programme dans le terminal, on obtient les nombres d'octets correspondant à ceux attendus : 
<img width="316" alt="image" src="https://github.com/Im4dENSEA/TPSyntheseInfo/assets/146735291/9438bc64-7ba6-43ba-90b8-c7e65ea5f981">

**b) Réception d’un fichier constitué d’un seul paquet de données (DAT) et son acquittement (ACK)**

Ici, il faut récupérer dans un premier temps un unique paquet DATA dont la constitution est donnée ainsi dans la norme RFC 1350 : 

<img width="296" alt="image" src="https://github.com/Im4dENSEA/TPSyntheseInfo/assets/146735291/b6e116df-73a4-4728-9811-8eb7639c9693">

Les deux premiers éléments du tableau sont 03, ce qui permet d'identifier le paquet comme un paquet DATA. Le Block est composé de deux bits qu'on renverra au serveur, ce
qui nous permettra de lui indiquer que l'on a bien reçu le paquet DATA.

On récupère ensuite le paquet avec la fonction *recvfrom*, on envoie ensuite un paquet ACK pour informer le serveur de labonne réception du paquet DATA à l'aide de la fonction *sendto* .

Le paquet ACK est décrit de la manière suivante : 

<img width="218" alt="image" src="https://github.com/Im4dENSEA/TPSyntheseInfo/assets/146735291/1ae37688-66a1-46d4-87a9-7ae5bf2be939">

On pense à prendre Opcode 04 pour indiquer qu'il s'agit d'un paquet ACK et on reprend la partie Block du paquet DATA.

<img width="335" alt="image" src="https://github.com/Im4dENSEA/TPSyntheseInfo/assets/146735291/1bbcb1dc-9910-403e-a031-957c5363594d">

**c) Réception d’un fichier constitué de plusieurs paquets de données (DAT) et leurs acquittements respectifs (ACK)**

On cherche maintenant à réceptionner un fichier sans se limiter à la taille de notre buffer. Le serveur nous enverra donc l'information sous la forme de plusieurs paquets DATA. On répondra à chaque paquet DATA par un paquet ACK afin de notifier le serveur de notre bonne réception des données. On réécrit donc le code précédent afin de l'adapter à la nouvelle situation. On ajoute une boucle while afin de capturer tous les paquets DATA que le serveur nous envoie, etconstruire puis envoyer le paquet ACK correspondant.

On vérifie bien sur le terminal que l'on obtient ce qui est attendu : 

<img width="295" alt="image" src="https://github.com/Im4dENSEA/TPSyntheseInfo/assets/146735291/814306be-fcd9-4c4d-b81b-4029bf99cd5d">

De même avec Wireshark, on vérifie que la trame contient bien ce qui est attendu :

<img width="506" alt="image" src="https://github.com/Im4dENSEA/TPSyntheseInfo/assets/146735291/f0b40ea7-98e1-4418-995a-28a388cea88d">

On constate qu'on retrouve bien le fichier, toutefois il semble il y avoir du bruit ce qui perturbe légèrement la lecture de celui-ci sur la trame.









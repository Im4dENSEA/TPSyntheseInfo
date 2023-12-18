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




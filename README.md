# TP Synthèse Informatique Majeure
## TP 1 - EnseaSH

0 . Mise en place de l'environnement de développement 

Création du fichier "fonctions.h" contenant les différentes commandes et retour console du shell servant de fichier
de configuration pour les prochaines questions.

<img width="359" alt="image" src="https://github.com/Im4dENSEA/TPSyntheseInfo/assets/146735291/b8153274-d756-42c8-8e43-e0a5fe815619">


**Question 1** 


![image](https://github.com/Im4dENSEA/TPSyntheseInfo/assets/146735291/131f62d7-4b0b-42c5-a1d7-1b3efa76d208)

Dans notre fichier "fonctions.h" on définit le message d'accueil dans la variable WELCOME ainsi
que l'invite de commande "enseash %" dans la variable PROMPT.

 A l'aide de la fonction __write__, on affiche le message.
 La fonction __write__ prend en entrée trois arguments :
 - STDOUT_FILENO : descripteur de fichier ouvert
 - Un pointeur vers une zone mémoire
 - Le nombre de caractères à afficher


**Question 2**


![image](https://github.com/Im4dENSEA/TPSyntheseInfo/assets/146735291/122cf2ea-32aa-40f9-88db-bfdeaf8b6eec)

On utilise les fonctions précédentes ainsi qu'une boucle while pour afficher les messages dans l'invite de commande.
Afin que les commandes puissent être comprise

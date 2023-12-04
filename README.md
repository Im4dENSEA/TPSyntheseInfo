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
Afin que les commandes puissent être comprise, on créer un tableau de chaines de caractère afin de recopier la commande en supprimant 
le dernier caractère.


<img width="373" alt="image" src="https://github.com/Im4dENSEA/TPSyntheseInfo/assets/146735291/4bef2b74-99f2-4020-a566-2c9df1de987f">

**Question 3**


<img width="428" alt="image" src="https://github.com/Im4dENSEA/TPSyntheseInfo/assets/146735291/1cd4a0ea-9ad3-47b0-826e-73de2a932c8e">

Dans le fichier q3.c, on programme la commande exit pour quitter le shell.
Tant que la commande "exit" n'est pas entrée par l'utilisateur, on éxecute le fils. L'entrée de la commande "exit" entraine l'éxécution d'une instruction "kill" qui arrête le processus.

<img width="281" alt="image" src="https://github.com/Im4dENSEA/TPSyntheseInfo/assets/146735291/5b6de963-c3bf-4770-b600-8b9d58acff89">

**Question 4**


<img width="437" alt="image" src="https://github.com/Im4dENSEA/TPSyntheseInfo/assets/146735291/7322ba66-d5b4-4051-bdb0-f36063385b8c">




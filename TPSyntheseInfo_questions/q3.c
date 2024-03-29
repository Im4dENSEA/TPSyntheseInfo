
#include "fonctions.h"

int main(void){
	char commande[SIZE_MAX];
	int commande_size;
	int pid;
	int status;
	int test;
	
	
	write(STDOUT_FILENO, EXIT_PROMPT, strlen(EXIT_PROMPT));
	while(1){
		//write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
		
		commande_size = read(STDOUT_FILENO, commande, SIZE_MAX);
		char*cmd = malloc(commande_size*sizeof(char));
		cmd=strncpy(cmd, commande, commande_size-1);
		
		test = strcmp(EXIT, cmd); //On compare chaque caractère avec l'invite de commande
		if (test==0){ // Si le test de comparaison est vérifié, alors on affiche le message de sortie
			write(STDOUT_FILENO, BYE, strlen(BYE));
			kill(getpid(),SIGINT); //Pour cesser le processus
		}
		
	
		pid = fork();
		if(pid==0){
			write(STDOUT_FILENO, commande, commande_size);

			execlp(cmd, cmd, NULL);
		} else {
			wait(&status);
		}
	}
}


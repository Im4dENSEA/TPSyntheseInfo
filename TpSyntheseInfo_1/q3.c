
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
		
		test = strcmp(EXIT, cmd);
		if (test==0){
			write(STDOUT_FILENO, BYE, strlen(BYE));
			kill(getpid(),SIGINT);
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


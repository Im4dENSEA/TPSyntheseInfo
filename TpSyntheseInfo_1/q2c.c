#include "fonctions.h"

int main(void){
	char commande[SIZE_MAX];
	int commande_size;
	int pid;
	int status;
	
	
	write(STDOUT_FILENO, EXIT_PROMPT, strlen(EXIT_PROMPT));
	while(1){
		//write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
		
		commande_size = read(STDOUT_FILENO, commande, SIZE_MAX);
		char*cmd = malloc(commande_size*sizeof(char));
		cmd=strncpy(cmd, commande, commande_size-1); 
		
		
		pid = fork();
		if(pid==0){
			write(STDOUT_FILENO, commande, commande_size);

			execlp(cmd, cmd, NULL);
		} else {
			wait(&status);
		}
	}
}

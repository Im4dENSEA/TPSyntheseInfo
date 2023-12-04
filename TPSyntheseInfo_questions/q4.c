#include "fonctions.h"

int main(void){
	// Déclaration des variables utiles
	char commande[SIZE_MAX]={0};
	char display[SIZE_MAX]={0};
	int commande_size;
	int pid; 
	int status; 
	int test;
	
	write(STDOUT_FILENO,WELCOME,strlen(WELCOME));
	write(STDOUT_FILENO,PROMPT,strlen(PROMPT));
	
	while(1)
	{
		commande_size=read(STDOUT_FILENO, commande, SIZE_MAX);
		
		commande[commande_size-1]='\0';
		
		test=strcmp(EXIT,commande);
		if(test==0 || commande_size==0)
		{
			write(STDOUT_FILENO,BYE,strlen(BYE));
			kill(getpid(),SIGINT);
		}
		
		pid=fork();
		if (pid==0){
			printf("id pid child %d \n",getpid()); // on recupère le pid 
			sleep(20); // pour nous laisser le temps de kill le processus 
			execlp(commande,commande,NULL);
		}
		
		else{
			wait(&status);
			if(WIFSIGNALED(status)){
				sprintf(display,"%s%d%s", PROMPT_SIG,WTERMSIG(status),END_PROMPT); // retourne la valeur du kill qui à tué le child 
				write(STDOUT_FILENO,display,strlen(display));
			}
			else {
				if(WIFEXITED(status))
				sprintf(display,"%s%d%s",PROMPT_EXIT, WEXITSTATUS(status),END_PROMPT); // retourne la valeur de l'exit du child
				write(STDOUT_FILENO,display,strlen(display));
			}
		}
	}
}

			

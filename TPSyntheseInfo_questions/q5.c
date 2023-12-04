#include "fonctions.h"

int main(void){
	// Déclaration des variables utiles
	char commande[SIZE_MAX]={0};
	char display[SIZE_MAX]={0};
	int commande_size;
	int pid; 
	int status; 
	int test;
	struct timespec timestart; 
	struct timespec timestop;
	
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
		clock_gettime(CLOCK_REALTIME, &timestart);
		int time = (timestop.tv_nsec - timestart.tv_nsec)/1e6;
		pid=fork();
		if (pid==0){
			printf("id pid child %d \n",getpid()); // on recupère le pid 
			execlp(commande,commande,NULL);
		}
		
		else{
			wait(&status);
			if(WIFSIGNALED(status)){
				sprintf(display, "%s%d%s%d%s%s", EXIT_PROMPT, WSTOPSIG(status), "|", time, "ms", END_PROMPT);// retourne la valeur du kill qui à tué le child et le temps d'éxécution 
				write(STDOUT_FILENO,display,strlen(display));
			}
			else {
				if(WIFEXITED(status))
				sprintf(display, "%s%d%s%d%s%s", EXIT_PROMPT, WSTOPSIG(status), "|", time, "ms", END_PROMPT);// retourne la valeur de l'exit du child et le temps d'éxécution 
				write(STDOUT_FILENO,display,strlen(display));
			}
		}
	}
}

			

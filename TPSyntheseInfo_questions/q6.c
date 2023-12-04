#include "fonctions.h"

int main(void){
	char commande[SIZE_MAX] = {0};
	char display[SIZE_MAX] = {0};
	int commande_size;
	int pid;
	int status;
	int test;
	struct timespec timestart;
	struct timespec timestop;
	
	write(STDOUT_FILENO, WELCOME, strlen(WELCOME));
	write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
	
	while(1){
		commande_size = read(STDOUT_FILENO, commande, SIZE_MAX);
		
		commande[commande_size-1] = '\0';
		
		test = strcmp(EXIT, commande);
		if(test==0 || commande_size==0){
			write(STDOUT_FILENO, BYE, strlen(BYE));
			kill(getpid(),SIGINT);
		}
		
			clock_gettime(CLOCK_REALTIME, &timestart);
		
		pid = fork();
		if(pid==0){
			//execution du fils
			char * argv[MAX_ARG]={NULL};
			int i = 0;
			
			//appel a strtok pour le calcul de argv[]
			argv[0] = strtok(commande, " ");
			
			//boucle while
			while (argv[i] != NULL){
				i++;
				argv[i] = strtok(NULL, " ");
			}
			execvp(argv[0], argv);
			
			//ce qui suit ne s'éxécute que si le exelcp n'a pas fonctionné
			write(STDOUT_FILENO, ERR, strlen(ERR));
			kill(getpid(),SIGINT);
		} else {
			//execution du père
			wait(&status);
			clock_gettime(CLOCK_REALTIME, &timestop);
			int time = (timestop.tv_nsec - timestart.tv_nsec)/1000000;
			if(WIFSIGNALED(status)){
				sprintf(display, "%s%d%s%d%s%s", PROMPT_SIG, WSTOPSIG(status), "|", time, "ms", END_PROMPT);
				write(STDOUT_FILENO, display, strlen(display));
			} else {
				if(WIFEXITED(status)){
					sprintf(display, "%s%d%s%d%s%s", PROMPT_EXIT, WSTOPSIG(status), "|", time, "ms", END_PROMPT);
					write(STDOUT_FILENO, display, strlen(display));
				}
			}
		}
	}	
}

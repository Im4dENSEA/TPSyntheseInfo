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
	
	//message d'accueil
	write(STDOUT_FILENO, WELCOME, strlen(WELCOME));
	write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
	
	while(1){
		//lecture de l'invite de commande
		commande_size = read(STDOUT_FILENO, commande, SIZE_MAX);
		
		//effacer le dernier élément pour que la commande fonctionne
		commande[commande_size-1] = '\0';
		
		//sortir du processus à la commande "exit" ou ctrl+d
		test = strcmp(EXIT, commande);
		if(test==0 || commande_size==0){
			write(STDOUT_FILENO, BYE, strlen(BYE));
			kill(getpid(),SIGINT);
		}
		
		clock_gettime(CLOCK_REALTIME, &timestart);
		
		pid = fork();
		if(pid==0){
			//execution du fils
			char * left;
			char * right;
			char * argv[MAX_ARG]={NULL};
			int i = 0;
			int fd;
		// premier appel à strtok pour trouver une redirection si il y en a une
			//recherche ">" ou "<"
			
			//si redirection : 
			//1-on ouvre le fichier avec les bons attributs
			//2-on ferme le flux de sortie / d'entrée avec dup2
			//3-on exécute comme avant
			
			left= strtok(commande, ">");
			right = strtok(NULL, ">");
			if (right != NULL) {
				fd = open(right, O_CREAT|O_WRONLY|O_CLOEXEC, S_IRWXO|S_IRWXG|S_IRWXU); //1
				dup2(fd, STDOUT_FILENO); //2
				strcpy(commande, left); //3
			}
			left = strtok(commande, "<");
			right = strtok(NULL, "<");
			if (right != NULL) {
				fd = open(right, O_RDWR|O_CLOEXEC, S_IRWXO|S_IRWXG|S_IRWXU); //1
				dup2(fd, STDIN_FILENO); //2
				strcpy(commande, right); //3
			}	
			argv[0] = strtok(commande, " ");
			while (argv[i] != NULL){
				i++;
				argv[i] = strtok(NULL, " ");
			}
			execvp(argv[0], argv);
			
			write(STDOUT_FILENO, ERR, strlen(ERR));
			kill(getpid(),SIGINT);
			} else {
			//execution du père
			wait(&status);
			clock_gettime(CLOCK_REALTIME, &timestop);
			int time = (timestop.tv_nsec - timestart.tv_nsec)/1e6;
			if(WIFSIGNALED(status)){
				sprintf(display, "%s%d%s%d%s%s",PROMPT_SIG, WSTOPSIG(status), "|", time, "ms", END_PROMPT);
				write(STDOUT_FILENO, display, strlen(display));
			} else {
				if(WIFEXITED(status)){
					sprintf(display, "%s%d%s%d%s%s",PROMPT_EXIT, WSTOPSIG(status), "|", time, "ms", END_PROMPT);
					write(STDOUT_FILENO, display, strlen(display));
				}
			}
		}
	}	
}

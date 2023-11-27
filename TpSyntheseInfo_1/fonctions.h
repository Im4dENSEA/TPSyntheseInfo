#include <string.h>
#include <stdio.h>  
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>


#define WELCOME "Bienvenue dans le Shell ENSEA\n Pour quitter, tapez 'exit'"
#define PROMPT "$ ./enseash"
#define EXIT_PROMPT "enseash %"
#define SIZE_MAX 255
#define EXIT "exit"
#define BYE "Ciao Bye ENSEA \n"
#define ERR " Command doesn't exist, do you want to continue ? \n " 
#define PROMPT_SIG "enseash [sign : "
#define PROMPT_EXIT "enseash [exit: "

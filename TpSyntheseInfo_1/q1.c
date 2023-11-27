#include "fonctions.h"

int main(void){
	write(STDOUT_FILENO, WELCOME, strlen(WELCOME));
	write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}

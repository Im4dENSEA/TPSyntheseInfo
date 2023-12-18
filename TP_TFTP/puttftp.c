#include "fonctions.h"

//Fonction principale
int main (int argc, char * argv[]){
	//nom du prog dans argv[0]
	//premier argument dans argv [1]
	//argc = nb d'arguments tot
	int fileName_Size;
	char * serverName=argv[1];
	char * file=argv[2];
	int port;
	
	//verif du nb d'arg d'entrée
	if (argc != 3) {
		printf(ERROR_MSG, argv[0]);
		exit(EXIT_FAILURE);
	}
		
	//récuperation des données
	serverName = strtok(argv[1], ":");
	
	
	struct addrinfo hints,*result;
	memset(&hints,0,sizeof(struct addrinfo));
	hints.ai_family=AF_INET;//ipv4
	hints.ai_socktype=SOCK_DGRAM;
	hints.ai_flags= 0;
	hints.ai_protocol= IPPROTO_UDP;
	
	int res=getaddrinfo(serverName,"1069",&hints,&result);
	if (res) {
		fprintf(stderr,"getaddrinfo :%s\n",gai_strerror(res));
		exit(1);
	}
	else{
		printf("La connexion a bien été établie \n");
	}
	
	//Réservation d'un socket vers le serveur
	int sfd = socket(result->ai_family,result->ai_socktype,result->ai_protocol);
	if (sfd==-1)
	{
		fprintf(stderr,"Création d'une erreur \n");
		exit(EXIT_FAILURE);
	}

// Construction de la requête WRQ
	
	char WRQ[50];
	char*mode1="octet";
	
	strcpy(WRQ+2,file);
	
	WRQ[2+strlen(file)]=0;
	
	strcpy(WRQ+strlen(file)+1,mode1);
	
	WRQ[2+strlen(file)+1+strlen(mode1)]=0;
	
	int lenWRQ=2+strlen(file)+1+strlen(mode1)+1;
	
	
	int nsent=sendto(sfd,WRQ,lenWRQ,0,result->ai_addr,result->ai_addrlen);
	printf("WRQ Sent : %d octets \n",nsent);
	if (nsent==-1)
	{
		perror("error sur le sendto");
		exit(EXIT_FAILURE);
	}
	
	
	// Question 5B 
	// on crée un buffer destiné à recevoir les données du serveur 
	
	char data[MAX_BUF_RECEIVE];
	data[0]=0;
	data[1]=3;
	data[2]=0;
	data[3]=1;
	
	
	char ack[MAX_BUF_RECEIVE];
	int nack=recvfrom(sfd,ack,MAX_BUF_RECEIVE,0,result->ai_addr,&(result->ai_addrlen));
	if(nack==-1)
	{
		perror("error sur le sendto");
		exit(EXIT_FAILURE);
	}
	printf("ACK sent. \n");
	int ndata=sendto(sfd,WRQ,lenWRQ,0,result->ai_addr,result->ai_addrlen);
	
}

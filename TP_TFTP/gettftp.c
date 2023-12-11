#include "fonctions.h"

//Fonction principale
int main (int argc, char * argv[]){
	//nom du prog dans argv[0]
	//premier argument dans argv [1]
	//argc = nb d'arguments tot
	int portASCII_size;
	char * serverName=argv[1];
	char * portASCII=argv[2];
	int port;
	
	//verif du nb d'arg d'entrée
	if (argc != 3) {
		printf(ERROR_MSG, argv[0]);
		exit(EXIT_FAILURE);
	}
	
	
	//récuperation des données
	serverName = strtok(argv[1], ":");
	portASCII = strtok(NULL, ":");
	
	if (portASCII == NULL){
		portASCII = malloc(3);
		portASCII = "69";
		port = 69;
	} else {
		port = atoi(portASCII);
	}
	
	struct addrinfo hints,*result;
	memset(&hints,0,sizeof(struct addrinfo));
	hints.ai_family=AF_INET;//ipv4
	hints.ai_socktype=SOCK_DGRAM;
	hints.ai_flags= 0;
	hints.ai_protocol= IPPROTO_UDP;
	
	int res=getaddrinfo(serverName,portASCII,&hints,&result);
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
		fprintf(stderr,"Création erreur \n");
		exit(EXIT_FAILURE);
	}
	
	//Construction d'une requête (RRQ)
	char RRQ[50];
	char * mode="octet";
	portASCII_size=read(STDOUT_FILENO, portASCII, strlen(portASCII));
	portASCII[portASCII_size-1]='\0';
	RRQ[0]=0;
	RRQ[1]=1;
	
	strncpy(RRQ + 2,portASCII, strlen(portASCII));
	RRQ[2+strlen(portASCII)]= 0;
	strncpy(RRQ + 2 + strlen(portASCII) + 1,mode,strlen(mode));
	RRQ[2 + strlen(portASCII) + strlen(mode) + 1]=0;
	int lenRRQ = 2 + strlen(portASCII) + 1+ strlen(mode) +1;
	
	int num_sent=sendto(sfd,RRQ,lenRRQ,0, result->ai_addr,result->ai_addrlen);
	printf("lenRRQ %d", lenRRQ);
	printf("RRQ sent :%d bytes \n",num_sent);
	if (num_sent==-1){
		perror("error sendto");
		exit(EXIT_FAILURE);		
}
	
	char buf[MAX_BUF_RECEIVE];
	int f = open(portASCII, O_WRONLY | O_CREAT, 0777);
	
	int nread = recvfrom(sfd,buf,MAX_BUF_RECEIVE,0,result->ai_addr, &(result->ai_addrlen));
	
	write(f,buf,nread);
	
	//Paquet (ACK)
	char ACK[4];
	ACK[0]=0;
	ACK[1]=4;
	ACK[2]=buf[2];
	ACK[3]=buf[3];
	
	int noctsent=sendto(sfd,ACK,4,0,(struct sockaddr *)result->ai_addr, (result->ai_addrlen));
	if (noctsent == -1) {
		perror("error sendto");
		exit(EXIT_FAILURE);
	}
	printf("ACK sent.\n");

	printf("\nRequested file %S successfully downloaded!\n",MAX_BUF_RECEIVE);
}
	
	
	
	
	
	
	
	

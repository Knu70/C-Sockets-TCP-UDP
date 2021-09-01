#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main()
{

int sockfd;
struct sockaddr_in servidor, cliente;
int tam=sizeof(struct sockaddr);
char respuesta[10] = "OK ";
char mensaje[100];

if ((sockfd=socket(AF_INET, SOCK_STREAM, 0))==-1)
{
	perror("Error en creación socket");
	exit(-1);
}
servidor.sin_family=AF_INET;
inet_aton("10.0.2.15", &servidor.sin_addr);
servidor.sin_port=htons(22000);
memset(&servidor.sin_zero, '\0', 8);

if (bind(sockfd, (struct sockaddr *)&servidor, sizeof(struct sockaddr))==-1)
{
	perror("Error en bind");
	exit(-1);
}


printf("Escuchando....\n"); fflush(stdout);

if (listen(sockfd, 1)==-1)
{
	perror("Error listen");
	exit(-1);
}



if ((sockfd=accept(sockfd, (struct sockaddr *)&cliente, &tam))==-1)
{
	perror("error accept");
	exit(-1);
}
else
{
	printf("Conectado cliente %s por el puerto %d", inet_ntoa(cliente.sin_addr), ntohs(cliente.sin_port));
	fflush(stdout);
	if (recv(sockfd, mensaje, 100, 0)==-1)
	{
		perror("Error al recibir los datos");
		exit(-1);	
	}
	else
	{
		printf("\n%s\n", mensaje);
		
		if (send(sockfd, respuesta, 10, 0)==-1) // Envio de mensaje recibido correctamente
		{
			perror("Error de envio");
			exit(-1);
		}
		
	}
	
}




close(sockfd);

}

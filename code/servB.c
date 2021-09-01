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
int sockfd2, sockfdcliente;
struct sockaddr_in servidor, cliente;
int tam=sizeof(struct sockaddr);
char ciudad[100];
char sensor[15];
char medida[5];
char respuesta[10] = "OK ";
char respuesta2[10];

if ((sockfd=socket(AF_INET, SOCK_DGRAM, 0))==-1)
{
	perror("Error en creación socket"); exit(-1);
}

servidor.sin_family=AF_INET;
inet_aton("10.0.2.15", &servidor.sin_addr);
servidor.sin_port=htons(22000);
memset(&servidor.sin_zero, '\0', 8);

if (bind(sockfd, (struct sockaddr *)&servidor, sizeof(struct sockaddr))==-1)
{
	perror("Error en asociar la ip/puerto"); exit(-1);
}

/*
*/


printf("\nEsperando sensor...\n");

//printf("Esperando ciudad...\n"); 
memset(ciudad,'\0',100);
if(recvfrom(sockfd, ciudad, 100, 0, (struct sockaddr *)&cliente, &tam)==-1)
{
	perror("Error en la recepcion\n"); exit(-1);
	
}
printf("Mensaje recibido desde %s:%d ciudad:%s\n", inet_ntoa(cliente.sin_addr), ntohs(cliente.sin_port), ciudad);

//printf("Esperando por sensor...\n"); fflush(stdout);
memset(sensor,'\0',15);
if(recvfrom(sockfd, sensor, 15, 0, (struct sockaddr *)&cliente, &tam)==-1)
{
	perror("Error en la recepcion\n"); exit(-1);
	
}
printf("Mensaje recibido desde %s:%d sensor:%s\n", inet_ntoa(cliente.sin_addr), ntohs(cliente.sin_port), sensor);

//printf("Esperando por medida...\n"); fflush(stdout);
memset(medida,'\0',5);
if(recvfrom(sockfd, medida, 5, 0, (struct sockaddr *)&cliente, &tam)==-1)
{
	perror("Error en la recepcion\n"); exit(-1);
	
}
printf("Mensaje recibido desde %s:%d medida:%s\n", inet_ntoa(cliente.sin_addr), ntohs(cliente.sin_port), medida);

int tamRespuesta=strlen(respuesta);
if(sendto(sockfd, respuesta, tamRespuesta, 0, (struct sockaddr *)&cliente, tam)==-1)
{
	perror("Error en el envio\n"); exit(-1);
}



int num = atoi(medida);
char polucion[15] ="Polución";
char temperatura[15] ="Temperatura";
char humedad[15] ="Humedad";

printf("\n %s",ciudad); 
printf("\n %s",sensor); 
printf("\n %s \n",medida); 


char mensaje[100];
sprintf(mensaje, "%s:%s:%s:%s", inet_ntoa(cliente.sin_addr), ciudad, sensor, medida);
printf("\n%s\n", mensaje);


if(strcmp(sensor, polucion)==0)
{
	if(num >= 0 && num <= 200)
	{
		//envia a servA
		if ((sockfd2=socket(AF_INET, SOCK_STREAM, 0))==-1)
		{
			perror("Error en la creación del socket\n");
		}

		if (connect(sockfd2, (struct sockaddr *)&servidor, sizeof(struct sockaddr))==-1)
		{
			perror("Error conexión\n");
		}

		if (send(sockfd2, mensaje, 100, 0)==-1)
		{
			perror("Error envio");
			exit(-1);
		}
		if ((tam=recv(sockfd2, respuesta2, 10, 0))==-1)
		{
			perror("Error recepción mensaje\n");
		}
		else
			printf("\n%s\n", respuesta2);
	}
	else
	printf("\n Dato no valido");
}
else if(strcmp(sensor, temperatura)==0)
{
	if(num >= (-20) && num <= 50)
	{
		//envia a servA
		if ((sockfd2=socket(AF_INET, SOCK_STREAM, 0))==-1)
		{
			perror("Error en la creación del socket\n");
		}

		if (connect(sockfd2, (struct sockaddr *)&servidor, sizeof(struct sockaddr))==-1)
		{
			perror("Error conexión\n");
		}

		if (send(sockfd2, mensaje, 100, 0)==-1)
		{
			perror("Error envio");
			exit(-1);
		}
		if ((tam=recv(sockfd2, respuesta2, 10, 0))==-1)
		{
			perror("Error recepción mensaje\n");
		}
		else
			printf("\n%s\n", respuesta2);
	}
	else
	printf("\n Dato no valido");
}
else if(strcmp(sensor, humedad)==0)
{
	if(num >= 0 && num <= 100)
	{
		//envia a servA
		if ((sockfd2=socket(AF_INET, SOCK_STREAM, 0))==-1)
		{
			perror("Error en la creación del socket\n");
		}

		if (connect(sockfd2, (struct sockaddr *)&servidor, sizeof(struct sockaddr))==-1)
		{
			perror("Error conexión\n");
		}

		if (send(sockfd2, mensaje, 100, 0)==-1)
		{
			perror("Error envio");
			exit(-1);
		}
		if ((tam=recv(sockfd2, respuesta2, 10, 0))==-1)
		{
			perror("Error recepción mensaje\n");
		}
		else
			printf("\n%s\n", respuesta2);
	}
	else
	printf("\n Dato no valido");
}
else 
	printf("\n Tipo de sensor no reconocido");


if(close(sockfd)==-1)
{
	perror("Error en la close\n"); exit(-1);
}

}

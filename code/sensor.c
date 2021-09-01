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
struct sockaddr_in servidor;
char ciudad[100];
char sensor[15];
char medida[5];
char respuesta[10];
int tam=sizeof(struct sockaddr);

if ((sockfd=socket(AF_INET, SOCK_DGRAM, 0))==-1)
{
	perror("Error en la creación del socket\n");
}

servidor.sin_family=AF_INET;
servidor.sin_port=htons(22000);
inet_aton("10.0.2.15", &servidor.sin_addr);
memset(&servidor.sin_zero, '\0', 8);

//pide por pantalla la ciudad
printf("\n Introduce la ciudad: "); fflush(stdout);
memset(ciudad, '0', 100);
fgets(ciudad, 100, stdin);

//envia la ciudad
int tamCiudad=strlen(ciudad);
if(sendto(sockfd, ciudad, tamCiudad, 0, (struct sockaddr *)&servidor, tam)==-1)
{
	perror("Error en el envio\n"); exit(-1);
}


//pide por pantalla tipo de sensor
/*printf("\n Introduce el tipo de sensor (pulución-temperatura-humedad): "); fflush(stdout);
memset(sensor, '0', 100);
fgets(sensor, 100, stdin);
*/
int opc;

    	printf("\n Introduce el tipo de sensor:");
        printf("\n   1. Polución" );
        printf("\n   2. Temperatura");
        printf("\n   3. Humedad\n");
        
        scanf( "%d", &opc );

        /* Inicio del anidamiento */

        switch ( opc )
        {
            case 1: strcpy(sensor, "Polución");
                    break;

            case 2: strcpy(sensor, "Temperatura");
                    break;

            case 3: strcpy(sensor, "Humedad");
            		break;
         }

//envia el tipo de sensor
int tamTipoSensor=strlen(sensor);
if(sendto(sockfd, sensor, tamTipoSensor, 0, (struct sockaddr *)&servidor, tam)==-1)
{
	perror("Error en el envio\n"); exit(-1);
}


//pide por pantalla la medida
printf("\n Introduce la medida: "); fflush(stdout);
//fgets(medida, 10, stdin);
scanf("%s", medida);

//envia la medida
//sprintf(medida,"%d",nMedida);
int tamMedida=strlen(medida);
if(sendto(sockfd, medida, tamMedida, 0, (struct sockaddr *)&servidor, tam)==-1)
{
	perror("Error en el envio\n"); exit(-1);
}

printf("Esperando echo...\n"); fflush(stdout);
if(recvfrom(sockfd, respuesta, 10, 0, (struct sockaddr *)&servidor, &tam)==-1)
{
	perror("Error en la recepcion\n"); exit(-1);
	
}
printf("mensaje echo: %s\n", respuesta); fflush(stdout);


if(close(sockfd)==-1)
{
	perror("Error en la close\n"); exit(-1);
}

}

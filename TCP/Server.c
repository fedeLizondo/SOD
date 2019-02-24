#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include "utils.h"

int main(int argc, char const *argv[])
{
    struct sockaddr_in direccionServidor;
	direccionServidor.sin_family = AF_INET;
	direccionServidor.sin_addr.s_addr = INADDR_ANY;
	direccionServidor.sin_port = htons(1500);

	int servidor = socket(AF_INET, SOCK_STREAM, 0);

	int activado = 1;
	setsockopt(servidor, SOL_SOCKET, SO_REUSEADDR, &activado, sizeof(activado));
	
	if (bind(servidor, (void*) &direccionServidor, sizeof(direccionServidor)) != 0) {
		perror("Falló el bind");
		return 1;
	}

	printf("Estoy escuchando\n");
	listen(servidor, 100);

	//------------------------------

	struct sockaddr_in direccionCliente;
	unsigned int len;
	int cliente = accept(servidor, (void*) &direccionCliente, &len);

	printf("Recibí una conexión en %d!!\n", cliente);
	send(cliente, "Hola NetCat!", 13, 0);
	send(cliente, ":)\n", 4, 0);
	
    char* buffer = malloc(1024);

	int i = 0;
	while (1) {
        //int bytesRecibidos = read(cliente, buffer, 1024);
	    //if (bytesRecibidos <= 0) {
		//        return 1;
        //}
        //buffer[bytesRecibidos] = '\0';
        //if (bytesRecibidos > 0) {
        //printf("Me llegaron %d bytes con %s", bytesRecibidos, buffer);
        //}
        i++;
        char unidad[24];
        sprintf(unidad," Hola mundo %d",i);
        write(cliente,unidad,12 +  sizeof(int));
	}


	free(buffer);

    return EXIT_SUCCESS;
}

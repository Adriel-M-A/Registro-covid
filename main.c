#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h> 
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "includes/includes.h"
#include "src/controlador/controladores.h"

int main(int argc, char *argv[]){
    
	if(!init_config(argv[POS_CONFIG])) exit(-1);

	int opc = 0;

	do{
		opc = menuPrincipal();
		
		if (opc){	//se eligio una opcion del menu principal

			system("cls");
			opc = controlMenuBase(opc);

			if (opc == 0) break;	//se quiere salir de un submenu
			else if (opc != -1){	//distinto de -1: realizar accion, igual a -1: volver para atras de un submenu

				if(menuRepeticion() == 2) break; //1: realizar otra opcion (atras), 2: salir del programa  
			}
		}
		else break;	//se quiere salir del menu principal, salir del programa
		system("cls");
	} while (1);
	
	return 0;
}

#include "../../includes/includes.h"
#include <string.h>
#include <stdlib.h>

/* ------------------------------------------------------------------------------------------------
* En este .c se busca tener implementados todas las operaciones para validar un tipo de datos
-------------------------------------------------------------------------------------------------*/

//valida que el ingreso de una cadena no este vacia
void validarDato(char str[], char palabra[]){
	int opc = 0;
	do
	{
		opc = 0;
		printf("%s: ", palabra);
		gets(str);
		if(str[0] == '\0'){
			opc = 1;
			printf("Error: espacio en blanco\n");
		}	
	} while (opc);
}

//valida que una cadena numerica sea enteramente numerica 
int validarInt(char num[]){

    int i = 0;

    for (; i < strlen(num); i++)
    {
        if(!isdigit(num[i]) ) return 0;
    }

    return 1;
}

//valida que el ingreso de una cadena no este vacia y sea solo numerica
int validarEntero(char palabra[]){

	char str[MAX20];
	int opc = 0;
	do
	{
		opc = 0;
		validarDato(str, palabra);
		if (!validarInt(str)){
			opc = 1;
			printf("Error: solo debe ingresar caracteres numericos\n");	
		}
	} while (opc);

	opc = atoi(str);

	return opc;
}

//valida que un numero estre dentro de un rango
int validarRango(int num, int min, int max){

	if(num < min || num > max){
		printf("Error: debe ingresar entre %d y %d\n", min, max);
		return 1;
	}
	
	return 0;
}

//valida que una cadena sea enteramente de caracteres no numericos
int validarString(char str[]){
	int i = 0;
	
    for (; i < strlen(str); i++)
    {
        if(isdigit(str[i]) ) {
			printf("Error: ingresar solo caracteres no numericos\n");
			return 0;
		}
    }

    return 1;
}

//pedir cadena y validar que no este vacia y no tenga numeros. casos(nombres, apellidos)
void validarCadenaSinNumeros(char str[], char palabra[]){
	do
	{
		validarDato(str, palabra);
	} while (!validarString(str));
}

//validar que una cadena no este vacia sea numerica y que el codigo ya exista
//retorna el codigo postal no existente
int validarCodPostExiste(){

	obj_Localidad *loc;
	loc =  Localidad_new();
	int opc = 0, codigo_postal = 0;
	char str[MAX50];

	do
	{
		opc = 0;
		codigo_postal = validarEntero("Codigo Postal");

		if(loc->findbykey(loc, codigo_postal) != NOT_FOUND)
		{
			printf("Error: codigo postal ya existe\n");
			opc = 1;
		}
	} while (opc);

	destroyObj(loc);
	return codigo_postal;
}

//validar que una cadena no este vacia sea numerica y que el codigo exista
//retorna el codigo postal existente
int validarCodPostNoExiste(){
	obj_Localidad *loc;
	loc = Localidad_new();
	int opc = 0, codigo_postal = 0;
	char str[MAX50];

	do
	{
		opc = 0;
		codigo_postal = validarEntero("Codigo Postal");

		if(loc->findbykey(loc, codigo_postal) == NOT_FOUND)
		{
			printf("Error: no existe una localidad con ese codigo postal\n");
			opc = 1;
		}
	} while (opc);

	destroyObj(loc);
	return codigo_postal;
}

//valida que una cadena sea una fecha
int validarFecha(char *fecha){
	
	int meses[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	char *str;
	char *token = "-";
	int error = 1;
	
	str = strtok(fecha, token);
	char *anio = str;
	int anioInt = atoi(anio);
	if((anioInt< 1900) || (anioInt > 2100)){ printf("Error: anio fuera de los rangos (1900-2100)\n"); error = 0;}
	
	str = strtok(NULL, token);
	char *mes = str;
	int mesInt = atoi(mes);
	if((mesInt < 1) || (mesInt > 12)){ printf("Error: mes fuera de los rangos (1-12)\n"); error = 0;}
	
	str = strtok(NULL, token);
	char *dia = str;
	int diaInt = atoi(dia);
	if((diaInt > meses[mesInt - 1]) || (diaInt < 1)){ printf("Error: dia %d no existe en el mes %d\n", diaInt, mesInt); error = 0;}

	sprintf(fecha, "%s-%s-%s", anio, mes, dia);

	return error ? 1 : 0;
}

int validarDNINoExiste(){
	
	obj_Enfermero *enf;
	enf = Enfermero_new();
	
	int opc, num = 0;
	
	do{
		opc = 0;
		num = validarEntero("DNI");
		if(enf->findbykey(enf,num) != NOT_FOUND){
			printf("Error: ya existe un enfermero con el DNI ingresado\n");
			opc = 1;
		}
	}while(opc);
	destroyObj(enf);
	return num;
}

int validarCodTipoVacuna(){
	obj_TipoVacuna *tvac;
	tvac = TipoVacuna_new();
	int opc, num;
	do{
		opc = 0;
		num = validarEntero("Codigo del Tipo de Vacuna");
		if(tvac->findbykey(tvac, num) == NOT_FOUND){
			printf("Error: no existe el codigo del tipo de vacuna\n");
			opc = 1;
		}
	}while(opc);
	return num;
}
//-----------------------------------------------
//Validadores de menus
//-----------------------------------------------
/* Se controla que los datos ingresados sean de tipo numerico (char) (1..max) recivido y se retorna el valor (int) aprobado.
Ingreso: valores (1..max).
Retorno: valor ingresdo validado entre (1..max).*/
int validarOpcMenu(int max){

    int opcInt = 0;

    do
    {
		printf("\n");
		opcInt = validarEntero("Ingresar numero opcion");
		
		if(!validarRango(opcInt, 1, max)) break; //salir del bucle 
        
    } while (1);

    return opcInt;
}

//se controla si se quiere salir o volver para atras de un menu
//se hace para que todos tengan el mismo valor de retorno para una de estas dos opciones
int controlAtrasSalir(int num, int max){
    if(num == max - 1) return - 1; 	//Atras
    else if(num == max) return 0; 	//Salir
	else return num;				//opcion normal
}

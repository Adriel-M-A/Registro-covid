#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------------------------
void logActividades(char *str1, char *str2){
	
	FILE *archivo;
	char nombre[50];
	char str[150];
	char extencion[] = ".txt";
	
	sprintf(str, "Log/log%s", extencion);
	//strcat(str, strcat(nombre, extencion));
	
	archivo = fopen(str, "a");
	fprintf(archivo, "%s | [%s] %s", getFechaHora(),str1, str2);
	
	fflush(archivo);
	fclose(archivo);
}
//----------------------------------------------------
void diaSiguiente(char *fecha){

	int meses[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	char *str;
	char *token = "-";

	str = strtok(fecha, token);
	char *anio = str;
	int anioInt = atoi(anio);

	str = strtok(NULL, token);
	char *mes = str;
	int mesInt = atoi(mes);

	str = strtok(NULL, token);
	char *dia = str;
	int diaInt = atoi(dia);

	if (meses[mesInt-1] > diaInt) diaInt++;
	else if (meses[mesInt-1] == diaInt) {

		diaInt = 1; 
		if (mesInt == 12){

			mesInt == 1;
			anioInt++;
		}
		else mesInt++;
	}

	if(diaInt < 10) sprintf(dia, "0%d", diaInt);
	else sprintf(dia, "%d", diaInt);
	if(mesInt < 10) sprintf(mes, "0%d", mesInt);
	else sprintf(mes, "%d", mesInt);
	sprintf(fecha, "%s-%s-%s", anio, mes, dia);
}

void horaSiguiente(char *h){
	
	char *str;
	char *token = ":";
	
	str = strtok(h, token);
	char *hora = str;
	int horaInt = atoi(hora);
	
	str = strtok(NULL, token);
	char *minutos = str;
	int minutosInt = atoi(minutos);

	if(minutosInt < 60){
		minutosInt+=20;
		if(minutosInt == 60){
			minutosInt = 0;
			horaInt++;
		}if(horaInt == 16) horaInt = 8;
	}
	
	if(minutosInt < 10) sprintf(minutos, "0%d", minutosInt);
	else sprintf(minutos, "%d", minutosInt);
	if(horaInt < 10) sprintf(hora, "0%d", horaInt);
	else sprintf(hora, "%d", horaInt);
	sprintf(h, "%s:%s:00", hora, minutos);

}
//----------------------------------------------------
//devualve una palabra con la inicial en mayuscula y lo demas en minuscula. casos (Nombre o Apellido)
void mayus(char *str){

	strlwr(str);	//palabra con todo minuscula 
	str[0]-= ' ';	//primer caracter mayuscula
}
//----------------------------------------------------

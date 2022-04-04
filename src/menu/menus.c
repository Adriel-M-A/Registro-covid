#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "../validaciones/validacion.h"

/* ------------------------------------------------------------------------------------------------
* En este .c se busca tener implementados todos los menus necesarios para la utilizacion del proyecto
* La implementacion inicial de cada uno de los menus es similar. Se muestran las opciones y se devuelve 
* el numero de la opcion ingresada/elegida.
-------------------------------------------------------------------------------------------------*/


//-----------------------------------------------
//* Menus extras
//-----------------------------------------------

int menuTipoVacuna(int MAX_OPC){
    
    printf("\n[ Ingresar id del tipo de vacuna ]\n"); 
    
    return validarOpcMenu(MAX_OPC);
}

int menuCrearArchivo(){

    int MAX_OPC = 2;
    
    printf("\n[ Crear un Archivo de la Lista? 1) Si, 2) No ]\n"); 
    
    return validarOpcMenu(MAX_OPC);
}

// menu para controlar cuando se ingresos mal un dato 
int menuErrorGenerico(){

    int MAX_OPC = 2;
    
    printf("\n[ Error al ingresar dato, reintentar? 1) Si, 2) No ]\n"); 
    
    return validarOpcMenu(MAX_OPC);
}

int menuOpcionActualizar(){

    int MAX_OPC = 2;
    
    printf("\n[ Actualizar otro dato? 1) Si, 2) No ]\n"); 
    
    return validarOpcMenu(MAX_OPC);
}

int menuActualizarDatos(char *str){

    int MAX_OPC = 9;
    
    printf("\n[ Que tipo de dato desea modificar? ]\n");
    printf("%s", str);
    
    return validarOpcMenu(MAX_OPC);
}

int menuIngresarObjeto(char *str){
	
	int MAX_OPC = 2;
	
	printf("\n[ Ingresar mas %s 1) Si 2) No ]\n", str);
	
	return validarOpcMenu(MAX_OPC);
}

int menuRepeticion(){

    int MAX_OPC = 2;
    
    printf("\n[ Realizar otra operacion 1) Si, 2) No ]\n"); 
    
    return validarOpcMenu(MAX_OPC);
}
//-----------------------------------------------
//* Menus de ordenamiento de Objetos
//-----------------------------------------------
// menu para controlar con que parametro de tipo de vacuna ordenar 

int menuOrdenamientoTurno(){
	int MAX_OPC = 2;
    
    printf("\n[ Ordenar por. 1) Fecha 2) Codigo ]\n"); 
    
    return validarOpcMenu(MAX_OPC);
}

int menuOrdenamientoTipoVacuna(){

    int MAX_OPC = 2;
    
    printf("\n[ Ordenar por. 1) Nombre 2) Codigo ]\n"); 
    
    return validarOpcMenu(MAX_OPC);
}

int menuFormaListadoTurnos(){

    int MAX_OPC = 2;
    
    printf("\n[ Listar 1) Todos 2) Vacunado con Sputnik V ]\n"); 
    
    return validarOpcMenu(MAX_OPC);
}

int menuFormaListadoPacientes(){

    int MAX_OPC = 3;
    
    printf("\n[ Listar 1) Todos 2) Todos los Vacunados 3) Trelew/Rawson/PuertoMadryn ]\n"); 
    
    return validarOpcMenu(MAX_OPC);
}

int menuOrdenamientoEnfermero(){

    int MAX_OPC = 4;
    
    printf("\n[ Ordenar por. 1) DNI 2) Nombre 3) Apellido 4) Matricula ]\n"); 
    
    return validarOpcMenu(MAX_OPC);
}

// menu para controlar con que parametro de localidad ordenar 
int menuOrdenamientoLocalidad(){

    int MAX_OPC = 2;
    
    printf("\n[ Ordenar por. 1) Nombre 2) Codigo Postal ]\n"); 
    
    return validarOpcMenu(MAX_OPC);
}

int menuOrdenamientoCentroAtencion(){

    int MAX_OPC = 2;
    
    printf("\n[ Ordenar por. 1) Nombre 2) Codigo Postal ]\n"); 
    
    return validarOpcMenu(MAX_OPC);
}

int menuOrdenamientoVacuna(){

    int MAX_OPC = 2;
    
    printf("\n[ Ordenar por. 1) Codigo 2) Fecha Vencimiento ]\n"); 
    
    return validarOpcMenu(MAX_OPC);
}

int menuOrdenamientoPaciente(){

    int MAX_OPC = 3;
    
    printf("\n[ Ordenar por. 1) Nombre 2) Apellido 3) DNI ]\n"); 
    
    return validarOpcMenu(MAX_OPC);
}
// menu para controlar de que forma se quiere ordenar una lista (Ascendente, Descendente)
int menuFormaListado(){

    int MAX_OPC = 2;
    
    printf("\n[ Forma de Listar 1) Ascendente, 2) Descendente ]\n"); 
    
    return validarOpcMenu(MAX_OPC);
}
//-----------------------------------------------
//* Menus del menu Principal
//-----------------------------------------------
int menuListados(){
	
	int MAX = 9;

    printf("[ Menu de Listados ]\n");
    printf("[ 1. Listar Turnos ]\n"); //dado un centro de atencion y una fecha
    printf("[ 2. Listar Localidades ]\n");
    printf("[ 3. Listar Enfermeros ]\n");
    printf("[ 4. Listar Paciente ]\n");
    printf("[ 5. Listar Tipos de Vacunas ]\n");
    printf("[ 6. Listar Vacunas ]\n");
    printf("[ 7. Listar Centros de Atencion ]\n");

    printf("[ 8. Atras ]\n");
    printf("[ 9. Salir ]\n");

    int opc = validarOpcMenu(MAX);
    
    return controlAtrasSalir(opc, MAX);
}

int menuActualizaciones(){

    int MAX = 9;

    printf("[ Menu de Actualizaciones ]\n");
    printf("[ 1. Pacientes ]\n");
    printf("[ 2. Enfermeros ]\n");
    printf("[ 3. Centros de atencion ]\n");
    printf("[ 4. Vacunas ]\n");
    printf("[ 5. Tipo de Vacunas ]\n");
    printf("[ 6. Turnos ]\n");
    printf("[ 7. Localidades ]\n");

    printf("[ 8. Atras ]\n");
    printf("[ 9. Salir ]\n");

    int opc = validarOpcMenu(MAX);
    
    return controlAtrasSalir(opc, MAX);
}

int menuIngresos(){

    int MAX = 8;

    printf("[ Menu de Ingresos ]\n");
    printf("[ 1. Enfermeros ]\n");
    printf("[ 2. Centros de atencion ]\n");
    printf("[ 3. Vacunas ]\n");
    printf("[ 4. Tipo de Vacunas ]\n");
    printf("[ 5. Turnos ]\n");
    printf("[ 6. Localidades ]\n");

    printf("[ 7. Atras ]\n");
    printf("[ 8. Salir ]\n");

    int opc = validarOpcMenu(MAX);
    
    return controlAtrasSalir(opc, MAX);
}

//*------------------------------------------------------------------------------------------------

int menuPrincipal(){
	
	int MAX = 5;

    printf("[ Menu de opciones ]\n");
    printf("[ 1. Ingresar ]\n");
    printf("[ 2. Actualizaciones ]\n");
    printf("[ 3. Listados ]\n");
    printf("[ 4. Vacunar ]\n");

    printf("[ 5. Salir ]\n");

    int num = validarOpcMenu(MAX);
        
    return (num == MAX)? 0 : num;   //opcion salida
}

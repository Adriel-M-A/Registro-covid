#include "../../includes/includelib.h"
#include "localidad.h"
#include "../menu/menus.h"
#include "../validaciones/validacion.h"
#include "../operacion/operaciones.h"
#include <string.h>

THIS(obj_Localidad)// crea definicion de funcion this para este modulo. .. Macro en config.h

// Retorna la cadena que se tiene que escribir en el Archivo que contiene la lista de localidades
char *stringLocalidad(void *self){
	
	obj_Localidad *obj=this(self);
	char cadena[MAX150] = {};

	sprintf(cadena, "Codigo Postal: %d, Localidad: %s \n", 
	obj->getId(obj), 
	obj->getNombre(obj)
	);
	
	char *str = cadena;

	return str;
}
//----------------------------------------------------
void crearArchivoDeLista(void *list, int size){

	FILE *archivo;
	char nombre[MAX50];
	char str[MAX150] = "Listas/";
	char extencion[] = ".txt";

	printf("Ingresar nombre del archivo: ");
	gets(nombre);

	strcat(str, strcat(nombre, extencion));	//"Listas/nombre_archivo.txt"

	archivo = fopen(str, "w");
	int i;
	void *itm;

	for(i=0;i<size;++i)
	{
		itm = ((Object **)list)[i];    
		fprintf(archivo, stringLocalidad(itm)); 
	}
	fflush(archivo);
	fclose(archivo);
}
//----------------------------------------------------
//Comparadores de Localidad
//----------------------------------------------------
int compara_CadenaAscLocalidad (const void * o1,const void * o2)
{
    obj_Localidad *loc1 = *((obj_Localidad **)o1) ; 
    obj_Localidad *loc2 = *((obj_Localidad **)o2) ; 
    return strcmp(loc1->getNombre(loc1), loc2->getNombre(loc2));
}

int compara_CadenaDescLocalidad (const void * o1,const void * o2)
{
    obj_Localidad *loc1 = *((obj_Localidad **)o1) ; 
    obj_Localidad *loc2 = *((obj_Localidad **)o2) ; 
    return strcmp(loc1->getNombre(loc1), loc2->getNombre(loc2)) * -1;
}

int compara_CodigoAscLocalidad(const void *l1, const void * l2)
{
    obj_Localidad *loc1 =  *((obj_Localidad **)l1);
    obj_Localidad *loc2 =  *((obj_Localidad **)l2);
    
    return (loc1->getId(loc1) - loc2->getId(loc2));
}

int compara_CodigoDescLocalidad(const void *l1, const void * l2)
{
    obj_Localidad *loc1 =  *((obj_Localidad **)l1);
    obj_Localidad *loc2 =  *((obj_Localidad **)l2);
    
    return (loc1->getId(loc1) - loc2->getId(loc2))*-1;
}
//----------------------------------------------------
void ordenamientoLocalidad(void *list, int size){

	if (menuOrdenamientoLocalidad() == 1)
	{
		if(menuFormaListado() == 1) qsort(list, size, sizeof(obj_Localidad*), compara_CadenaAscLocalidad);
		else qsort(list, size, sizeof(obj_Localidad*), compara_CadenaAscLocalidad);
	}
	else
	{
		if(menuFormaListado() == 1) qsort(list, size, sizeof(obj_Localidad*), compara_CodigoAscLocalidad);
		else qsort(list, size, sizeof(obj_Localidad*), compara_CodigoDescLocalidad);
	}
}
//----------------------------------------------------
void listarLocalidades(int flag){

  	obj_Localidad *loc;
	loc =  Localidad_new();
	
	void *itm, *list;
	int i=0,size=0;

	size = loc->findAll(loc,&list,NULL);

	if(flag) ordenamientoLocalidad(list, size);
	
	for(i=0;i<size;++i)
	{
		itm = ((Object **)list)[i];    
		((Object *)itm)->toString(itm);
	}
	
	if (flag)
	{
		if(menuCrearArchivo() == 1) crearArchivoDeLista(list, size);
	}
	
	// librerar memoria
	destroyObjList(list,size);  // liberar listado, cada instacia creada en el listado
	destroyObj(loc);
}

void ingresarLocalidad(){

	obj_Localidad *loc;
	loc =  Localidad_new();
	
	char str[MAX50];
	int codigo_postal;
	int opc = 0;

	codigo_postal = validarCodPostExiste();
	loc->setId(loc, codigo_postal);

	validarCadenaSinNumeros(str, "Nombre");
	loc->setNombre(loc, str);
	
	if(!loc->saveObj(loc)) printf("Ocurrio un error al ingresar localidad: \n %s \n",getLastError());
	else printf("Ingreso de Localidad realizado exitosamente!\n");
	
	logActividades("Ingresar Localidad", stringLocalidad(loc));
	
	destroyObj(loc);
}

void actualizarLocalidad(){

	obj_Localidad *loc;
	loc =  Localidad_new();
	int codigo_postal = 0;
	
	listarLocalidades(0);

	printf("\nIngresar codigo postal de localidad a modificar: ");
	scanf(" %d", &codigo_postal);
	
	if(loc->findbykey(loc,codigo_postal) != NOT_FOUND)
	{
		logActividades("Actualizar Localidad Antes", stringLocalidad(loc));
		fflush(stdin);	
		char nombre[MAX30];
		printf("Nombre actual: %s\n", loc->getNombre(loc));
		printf("Ingresar nuevo nombre de la localidad: ");
		gets(nombre);
		loc->setNombre(loc, nombre);
		
		if  (loc->saveObj(loc))
			printf("Actualizacion de localidad realizada exitosamente!\n");
		
	}else printf("Codigo postal ingresado no valido: %d", codigo_postal);
	
	logActividades("Actualizar Localidad Despues", stringLocalidad(loc));
	
	fflush(stdin);
	destroyObj(loc); // liberar Recurso
}
//----------------------------------------------------
static void toString_LocalidadImpl(void *self)
{
     obj_Localidad *obj=this(self);
     printf("Codigo Postal: %d  Nombre: %s \n",
	 obj->getId(obj),
	 obj->getNombre(obj)
	 );
}
//----------------------------------------------------
//implementacion de getters
//----------------------------------------------------
static int getIdLocalidad_Impl(void *self)
{
  return *( (int *) getValue(self,POS_ID));
}
//----------------------------------------------------
static char *getNombreLocalidad_Impl(void *self)
{
  return  (char *) getValue(self,POS_DESCRIPCION);
}
//----------------------------------------------------
//implementacion setters
//----------------------------------------------------
static void setIdLocalidad_Impl(void *self,int val)
{ 
	setValue(self,POS_ID,&val);
}
//----------------------------------------------------
static void setNombreLocalidad_Impl(void *self,char *descripcion_Localidad)
{ 
	setValue(self,POS_DESCRIPCION,descripcion_Localidad);
}
//----------------------------------------------------
//implementacion de relaciones
//----------------------------------------------------
/// ....
//----------------------------------------------------
//implementacion constructor
//----------------------------------------------------
static void *init_Localidad(void *self)
{
  obj_Localidad *obj 	  = this(self);
  obj->ds  				  = &table_Localidad;
  obj->constructor 		  = Localidad_new;
  obj->sizeObj 			  = sizeof(obj_Localidad*);
  //incializacion de la interfaz de la entidad  
  obj->toString    		  = toString_LocalidadImpl;
  // Inicializar handlers de getters y setters
  /// getters
  obj->getId  	  		  = getIdLocalidad_Impl;
  obj->getNombre		  = getNombreLocalidad_Impl;  
  /// setters  
  obj->setId     		  = setIdLocalidad_Impl;
  obj->setNombre   		  = setNombreLocalidad_Impl;  
  return obj;
}
//----------------------------------------------------
//constructor de Localidad
obj_Localidad *Localidad_new()
{
  return (obj_Localidad *)init_obj(sizeof(obj_Localidad), init_Localidad);
}
//----------------------------------------------------

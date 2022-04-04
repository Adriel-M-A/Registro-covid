#include "../../includes/includelib.h"
#include "tipo_vacuna.h"
#include "../vacuna/vacuna.h"
#include "../operacion/operaciones.h"
#include <string.h>

THIS(obj_TipoVacuna)// crea definicion de funcion this para este modulo. .. Macro en config.h
//----------------------------------------------------
// Retorna la cadena que se tiene que escribir en el Archivo que contiene la lista de localidades
char *stringTipoVacuna(void *self){
	
	obj_TipoVacuna *obj=this(self);
	char cadena[MAX150] = {};

	sprintf(cadena, "ID: %d, Nombre: %s, Cantidad de dosis: %d \n",
	obj->getId(obj),
	obj->getNombre(obj),
	obj->getCantidadDosis(obj)
	);
	
	char *str = cadena;

	return str;
}
//----------------------------------------------------
void crearArchivoTipoVacuna(void *list, int size){

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
		fprintf(archivo, stringTipoVacuna(itm)); 
	}
	fclose(archivo);
}
//----------------------------------------------------
//Comparadores de Tipo Vacuna
//----------------------------------------------------
int compara_NombreAscTipoVacuna (const void * o1,const void * o2)
{
    obj_TipoVacuna *tvac1 = *((obj_TipoVacuna **)o1) ; 
    obj_TipoVacuna *tvac2 = *((obj_TipoVacuna **)o2) ; 
    return strcmp(tvac1->getNombre(tvac1), tvac2->getNombre(tvac2));
}

int compara_NombreDescTipoVacuna (const void * o1,const void * o2)
{
    obj_TipoVacuna *tvac1 = *((obj_TipoVacuna **)o1) ; 
    obj_TipoVacuna *tvac2 = *((obj_TipoVacuna **)o2) ; 
    return strcmp(tvac1->getNombre(tvac1), tvac2->getNombre(tvac2)) * -1;
}

int compara_CodigoAscTipoVacuna(const void *l1, const void * l2)
{
    obj_TipoVacuna *tvac1 =  *((obj_TipoVacuna **)l1);
    obj_TipoVacuna *tvac2 =  *((obj_TipoVacuna **)l2);
    
    return (tvac1->getId(tvac1) - tvac2->getId(tvac2));
}

int compara_CodigoDescTipoVacuna(const void *l1, const void * l2)
{
    obj_TipoVacuna *tvac1 =  *((obj_TipoVacuna **)l1);
    obj_TipoVacuna *tvac2 =  *((obj_TipoVacuna **)l2);
    
    return (tvac1->getId(tvac1) - tvac2->getId(tvac2))*-1;
}
//----------------------------------------------------
void ordenamientoTipoVacuna(void *list, int size){

	if (menuOrdenamientoTipoVacuna() == 1)
	{
		if(menuFormaListado() == 1) qsort(list, size, sizeof(obj_TipoVacuna*), compara_NombreAscTipoVacuna);
		else qsort(list, size, sizeof(obj_TipoVacuna*), compara_NombreDescTipoVacuna);
	}
	else
	{
		if(menuFormaListado() == 1) qsort(list, size, sizeof(obj_TipoVacuna*), compara_CodigoAscTipoVacuna);
		else qsort(list, size, sizeof(obj_TipoVacuna*), compara_CodigoDescTipoVacuna);
	}
}
//----------------------------------------------------
void listarTipoVacunas(int flag){

	obj_TipoVacuna *tvac;
	tvac = TipoVacuna_new();

	void *itm, *list;
	int i=0,size=0;

	size = tvac->findAll(tvac,&list,NULL);

	if(flag) ordenamientoTipoVacuna(list, size);

	for(i=0;i<size;++i)
	{
		itm = ((Object **)list)[i];    
		((Object *)itm)->toString(itm);
	}

	if(flag) if(menuCrearArchivo() == 1) crearArchivoTipoVacuna(list, size);


	// librerar memoria
	destroyObjList(list,size);  // liberar listado, cada instacia creada en el listado
	destroyObj(tvac);
} 

void ingresarTipoVacuna(){

	obj_TipoVacuna *tvac;
	tvac = TipoVacuna_new();
	int num = 0;
	char str[MAX120];
	
	do{
		
		validarDato(str, "Nombre");
		mayus(str);
		tvac->setNombre(tvac, str);
		
		num = validarEntero("Dosis");
		tvac->setCantidadDosis(tvac, num);
		
		if(!tvac->saveObj(tvac))
			printf("Ocurrio un error al agregar Tipo de Vacuna:\n%s\n",getLastError());
	  
		else printf("Ingreso de Tipo de Vacuna realizada exitosamente!\n");

		logActividades("Ingresar Tipo Vacuna", stringTipoVacuna(tvac));
		
	}while(menuIngresarObjeto("Tipos de Vacunas") == 1);
			
	destroyObj(tvac);
}

void actualizarTipoVacuna(){

	obj_TipoVacuna *tvac;
	tvac = TipoVacuna_new();

	int id = 0, num = 0;
	
	id = validarEntero("ID tipo vacuna");
	char str[MAX120];
	
	if(tvac->findbykey(tvac, id) != NOT_FOUND)
	{	
		logActividades("Actualizar Tipo Vacuna Antes", stringTipoVacuna(tvac));
		do{
			
			switch(menuActualizarDatos("\n1)Nombre \n2)Cantidad de dosis\n")){
				case 1: validarDato(str, "Nombre"); mayus(str);tvac->setNombre(tvac, str); break;
				case 2: num = validarEntero("Dosis"); tvac->setCantidadDosis(tvac, num); break; 
			}

		}while(menuOpcionActualizar() == 1);
		
		if(tvac->saveObj(tvac))
		{
			printf("Actualizacion de tipo de vacuna realizada exitosamente!\n");
		}
		logActividades("Actualizar Tipo Vacuna Despues", stringTipoVacuna(tvac));

	}else{
		printf("Id ingresado no valido: %d\n");
	}
	destroyObj(tvac); // liberar Recurso
}
//----------------------------------------------------
static void toString_TipoVacunaImpl(void *self)
{
	obj_TipoVacuna *obj=this(self);
	printf("TipoVacuna_id: %d  TipoVacuna: %s \n",
	obj->getId(obj),
	obj->getNombre(obj)
	);
}
//----------------------------------------------------
//implementacion de getters
//----------------------------------------------------
static int getIdTipoVacuna_Impl(void *self)
{ return *( (int *) getValue(self,POS_ID)); }
//----------------------------------------------------
static char *getNombreTipoVacuna_Impl(void *self)
{ return  (char *) getValue(self,POS_NOMBRE_TV); }
//----------------------------------------------------
static int getCantidadDosis_Impl(void *self)
{ return *( (int *) getValue(self,POS_CANT_DOSIS_TV)); }
//----------------------------------------------------
//implementacion setters
//----------------------------------------------------
static void setIdTipoVacuna_Impl(void *self,int val)
{ setValue(self,POS_ID,&val); }
//----------------------------------------------------
static void setNombreTipoVacuna_Impl(void *self,char *nombre_TipoVacuna)
{ setValue(self,POS_NOMBRE_TV,nombre_TipoVacuna); }
//----------------------------------------------------
static void setCantidadDosis_Impl(void *self,int val)
{ setValue(self,POS_CANT_DOSIS_TV,&val); }
//----------------------------------------------------
//implementacion de relaciones
//----------------------------------------------------
obj_Vacuna *getVacuna_Impl(int idTvac){

	obj_Vacuna *vac; vac = Vacuna_new();

	if (vac->findbykey(vac, idTvac) != NOT_FOUND)
	{
		return vac;
	}
	
	return vac = NULL;
}
//----------------------------------------------------
//implementacion constructor
//----------------------------------------------------
static void *init_TipoVacuna(void *self)
{
  obj_TipoVacuna *obj 	  = this(self);
  obj->ds  				  = &table_TipoVacuna;
  obj->constructor 		  = TipoVacuna_new;
  obj->sizeObj 			  = sizeof(obj_TipoVacuna*);
  //incializacion de la interfaz de la entidad  
  obj->toString    		  = toString_TipoVacunaImpl;
  // Inicializar handlers de getters y setters
  /// getters
  obj->getId    		  = getIdTipoVacuna_Impl;
  obj->getNombre		  = getNombreTipoVacuna_Impl;  
  obj->getCantidadDosis   = getCantidadDosis_Impl;
  /// setters  
  obj->setId    		  = setIdTipoVacuna_Impl;
  obj->setNombre   		  = setNombreTipoVacuna_Impl;  
  obj->setCantidadDosis   = setCantidadDosis_Impl;
  return obj;
}
//----------------------------------------------------
//constructor de TipoVacuna
obj_TipoVacuna *TipoVacuna_new()
{
  return (obj_TipoVacuna *)init_obj(sizeof(obj_TipoVacuna), init_TipoVacuna);
}
//----------------------------------------------------

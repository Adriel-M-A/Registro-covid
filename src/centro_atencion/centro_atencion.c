#include "../../includes/includelib.h"
#include "../localidad/localidad.h"
#include "../operacion/operaciones.h"
#include "centro_atencion.h"
#include <string.h>

THIS(obj_CentroAtencion)// crea definicion de funcion this para este modulo. .. Macro en config.h
//----------------------------------------------------
// Retorna la cadena que se tiene que escribir en el Archivo que contiene la lista de centros de atencion
char *stringCentro(void *self){
	
	obj_CentroAtencion *obj=this(self);
	obj_Localidad *loc;
	loc = obj->getLocalidadObj(obj);
	char cadena[MAX150] = {};

	sprintf(cadena, "id: %d\tCons: %s \tDom: %s\tTel: %s - Loc: %s\n",
     obj->getId(obj),
     obj->getNombre(obj),
     obj->getDomicilio(obj),
     obj->getTelefono(obj),
     loc->getNombre(loc)
	);
	
	char *str = cadena;
	destroyObj(loc);
	return str;
}
//----------------------------------------------------
void crearArchivoCentro(void *list, int size){

	FILE *archivo;
	char nombre[MAX50];
	char str[MAX150] = "Listas/";
	char extencion[] = ".txt";

	printf("Ingresar nombre del archivo: ");
	gets(nombre);
	
	strcat(str, strcat(nombre, extencion));
	
	archivo = fopen(str, "w");
	int i;
	void *itm;

	for(i=0;i<size;++i)
	{
		itm = ((Object **)list)[i];    
		fprintf(archivo, stringCentro(itm)); 
	}
	fflush(archivo);
	fclose(archivo);
}
//----------------------------------------------------
//Comparadores de Centro de Atencion
//----------------------------------------------------
int compara_StrAscCentro(const void * o1,const void * o2)
{
    obj_CentroAtencion *ctr1 = *((obj_CentroAtencion **)o1) ; 
    obj_CentroAtencion *ctr2 = *((obj_CentroAtencion **)o2) ; 
    return strcmp(ctr1->getNombre(ctr1), ctr2->getNombre(ctr2));
}

int compara_StrDescCentro(const void * o1,const void * o2)
{
    obj_CentroAtencion *ctr1 = *((obj_CentroAtencion **)o1) ; 
    obj_CentroAtencion *ctr2 = *((obj_CentroAtencion **)o2) ; 
    return strcmp(ctr1->getNombre(ctr1), ctr2->getNombre(ctr2)) * -1;
}

int compara_CodigoAscCentro(const void *l1, const void * l2)
{
    obj_CentroAtencion *ctr1 =  *((obj_CentroAtencion **)l1);
    obj_CentroAtencion *ctr2 =  *((obj_CentroAtencion **)l2);
    
    return (ctr1->getId(ctr1) - ctr2->getId(ctr2));
}

int compara_CodigoDescCentro(const void *l1, const void * l2)
{
    obj_CentroAtencion *ctr1 =  *((obj_CentroAtencion **)l1);
    obj_CentroAtencion *ctr2 =  *((obj_CentroAtencion **)l2);
    
    return (ctr1->getId(ctr1) - ctr2->getId(ctr2))*-1;
}
//----------------------------------------------------
void ordenamientoCentroAtencion(void *list, int size){

	if (menuOrdenamientoCentroAtencion() == 1)
	{
		if(menuFormaListado() == 1) qsort(list, size, sizeof(obj_CentroAtencion*), compara_StrAscCentro);
		else qsort(list, size, sizeof(obj_CentroAtencion*), compara_StrDescCentro);
	}
	else
	{
		if(menuFormaListado() == 1) qsort(list, size, sizeof(obj_CentroAtencion*), compara_CodigoAscCentro);
		else qsort(list, size, sizeof(obj_CentroAtencion*), compara_CodigoDescCentro);
	}
}
//----------------------------------------------------
void listarCentroDeAtencion(int flag){
	
	obj_CentroAtencion *ctr;
	ctr = CentroAtencion_new();

	void *itm, *list;;
	int i=0,size=0;

	size = ctr->findAll(ctr,&list,NULL);

	if(flag) ordenamientoCentroAtencion(list, size);

	for(i=0;i<size;++i)
	{
		itm = ((Object **)list)[i];    
		((Object *)itm)->toString(itm);
	}

	if(flag) if(menuCrearArchivo() == 1) crearArchivoCentro(list, size);

	// librerar memoria
	destroyObjList(list,size);  // liberar listado, cada instacia creada en el listado
	destroyObj(ctr);
}

void ingresarCentroAtencion(){
	
	obj_CentroAtencion *ctr;
	ctr = CentroAtencion_new();
	
	char str[MAX120];
	int num = 0;	
	
	do{
		validarDato(str, "Nombre");
		mayus(str);
		ctr->setDenominacion(ctr, str);
		
		validarDato(str, "Domicilio");
		ctr->setDomicilio(ctr, str);
		
		num = validarEntero("Telefono");
		itoa(num, str, 10);
		ctr->setTelefono(ctr, str);
		
		num = validarCodPostNoExiste();
		ctr->setCodPostal(ctr, num);
	
	}while (menuIngresarObjeto("Centros de Atencion") == 1);
	if(ctr->saveObj(ctr))
		printf("Ingreso de centro de atencion realizada exitosamente!\n");

	logActividades("Ingresar Centro Atencion", stringCentro(ctr));
	
	destroyObj(ctr);
	
}

void acualizarCentroAtencion(){
	
	obj_CentroAtencion *ctr;
	ctr = CentroAtencion_new();
	char str[MAX120];
	int num, codigo;
	
	listarCentroDeAtencion(0);

	codigo = validarEntero("ID del Centro de Atencion");
	
	if(ctr->findbykey(ctr, codigo) != NOT_FOUND){

		logActividades("Actualizar Centro Atencion Antes", stringCentro(ctr));

		do{
			switch(menuActualizarDatos("\n1)Nombre \n2)Domicilio \n3)Telefono \n4)Codigo Postal"))
			{
				case 1: validarDato(str, "Nombre"); mayus(str); ctr->setDenominacion(ctr, str); break;
				case 2: validarDato(str, "Domicilio"); ctr->setDomicilio(ctr, str); break;
				case 3: num = validarEntero("Telefono");
						itoa(num, str, 10);
						ctr->setTelefono(ctr, str);
				case 4: num = validarCodPostNoExiste(); ctr->setCodPostal(ctr, num); break;
			}
		}while(menuOpcionActualizar() == 1);
		if(ctr->saveObj(ctr))
			printf("Actualizacion de centro de atencion realizada exitosamente!\n");
		
		logActividades("Actualizar Centro Atencion Despues", stringCentro(ctr));
	}

	destroyObj(ctr);
}
//----------------------------------------------------
static void toString_CentroAtencionImpl(void *self)
{
  	 obj_CentroAtencion *obj=this(self);     
     obj_Localidad *loc;
     loc = obj->getLocalidadObj(obj);
     printf("id: %d\tCons: %s \tDom: %s\tTel: %s - Loc: %s\n",
     obj->getId(obj),
     obj->getNombre(obj),
     obj->getDomicilio(obj),
     obj->getTelefono(obj),
     loc->getNombre(loc)
     );
}
//----------------------------------------------------
//implementacion de getters
//----------------------------------------------------
static int getIdCentroAtencion_Impl(void *self)
{ return *( (int *) getValue(self,POS_ID)); }
//----------------------------------------------------
static char *getNombreCentroAtencion_Impl(void *self)
{ return  (char *) getValue(self,POS_NOMBRE_CENTRO); }
//----------------------------------------------------
static char *getDomicilioCentroAtencion_Impl(void *self)
{ return  (char *) getValue(self,POS_DOMICILIO_CENTRO); }
//----------------------------------------------------
static char *getTelefonoCentroAtencion_Impl(void *self)
{ return  (char *) getValue(self,POS_TELEFONO_CENTRO); }
//----------------------------------------------------
static int getCodPostalCentroAtencion_Impl(void *self)
{ return *( (int *) getValue(self,POS_CODPOSTAL_CENTRO)); }
//----------------------------------------------------
//implementacion setters
//----------------------------------------------------
static void setIdCentroAtencion_Impl(void *self,int val)
{ setValue(self,POS_ID,&val); }
//----------------------------------------------------
static void setNombreCentroAtencion_Impl(void *self,char *nombre)
{ setValue(self,POS_NOMBRE_CENTRO,nombre); }
//----------------------------------------------------
static void setDomicilioCentroAtencion_Impl(void *self,char *domicilio)
{ setValue(self,POS_DOMICILIO_CENTRO,domicilio); }
//----------------------------------------------------
static void setTelefonoCentroAtencion_Impl(void *self,char *telefono)
{ setValue(self,POS_TELEFONO_CENTRO,telefono); }
//----------------------------------------------------
static void setCodPostalCentroAtencion_Impl(void *self,int val)
{ setValue(self,POS_CODPOSTAL_CENTRO,&val); }
//----------------------------------------------------
static void destroyInternalCentroAtencion_Impl(void *self)
{
	obj_CentroAtencion *obj = this(self);	
	if(obj->localidad!=NULL){
		destroyObj(obj->localidad);
		obj->localidad = NULL;	
	}
	  
}
//----------------------------------------------------
//implementacion de relaciones
//----------------------------------------------------
obj_Localidad *getLocalidadCentroAtencionObj_Impl(void *self)
{
    obj_CentroAtencion *obj = this(self);    
    obj->localidad = Localidad_new();
    if(obj->localidad->findbykey(obj->localidad,obj->getCodPostal(obj))!=NOT_FOUND)
	{
		return obj->localidad;
	}
    return NULL;
}
//----------------------------------------------------
//implementacion constructor
//----------------------------------------------------
static void *init_CentroAtencion(void *self)
{
  obj_CentroAtencion *obj  = this(self);  
  //incializacion de la interfaz de la entidad  
  obj->ds               	= &table_CentroAtencion;
  obj->constructor      	= CentroAtencion_new;
  obj->sizeObj          	= sizeof(obj_CentroAtencion*);
  obj->localidad 	    	= NULL;  
  obj->toString         	= toString_CentroAtencionImpl;    
  // Inicializar handlers de getters y setters
  /// getters
  obj->getId  				= getIdCentroAtencion_Impl;
  obj->getNombre  		   	= getNombreCentroAtencion_Impl;
  obj->getDomicilio     	= getDomicilioCentroAtencion_Impl;
  obj->getTelefono      	= getTelefonoCentroAtencion_Impl;
  obj->getCodPostal			= getCodPostalCentroAtencion_Impl;
  /// setters  
  obj->setId 				= setIdCentroAtencion_Impl;
  obj->setDenominacion  	= setNombreCentroAtencion_Impl;
  obj->setDomicilio     	= setDomicilioCentroAtencion_Impl;
  obj->setTelefono      	= setTelefonoCentroAtencion_Impl;
  obj->setCodPostal			= setCodPostalCentroAtencion_Impl;
  // implementar detroy internal para liberar recursos  
  obj->destroyInternal 		= destroyInternalCentroAtencion_Impl;
  //---- acceso a relaciones  
  obj->getLocalidadObj 		= getLocalidadCentroAtencionObj_Impl;    
  return obj;
}
//----------------------------------------------------
//constructor de CentroAtencion
obj_CentroAtencion *CentroAtencion_new()
{
  return (obj_CentroAtencion *)init_obj(sizeof(obj_CentroAtencion), init_CentroAtencion);
}
//----------------------------------------------------

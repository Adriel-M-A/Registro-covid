#include "../../includes/includelib.h"
#include "../tipo_vacuna/tipo_vacuna.h"
#include "../operacion/operaciones.h"
#include "vacuna.h"
#include <string.h>

THIS(obj_Vacuna)// crea definicion de funcion this para este modulo. .. Macro en config.h
//----------------------------------------------------
// Retorna la cadena que se tiene que escribir en el Archivo que contiene la lista de localidades
char *stringVacuna(void *self){
	
	obj_Vacuna *obj=this(self);
	char cadena[MAX150] = {};
	obj_TipoVacuna *tv = obj->getTipoVacunaObj(obj);
	
	sprintf(cadena, "id:%d - L:%s - FV:%s - CantDosis:%.1f - Marca: %s\n", 
	obj->getVacunaId(obj),
	obj->getLote(obj),
	obj->getFechaVenc(obj),
	obj->getCantidad(obj),
	tv->getNombre(tv));
	
	char *str = cadena;
	destroyObj(tv);
	
	return str;
}
//----------------------------------------------------
void crearArchivoVacuna(void *list, int size){

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
		fprintf(archivo, stringVacuna(itm)); 
	}
	fclose(archivo);
}
//----------------------------------------------------
//Comparadores de Localidad
//----------------------------------------------------
int compara_FechaVencimientoAsc (const void * o1,const void * o2)
{
    obj_Vacuna *vac1 = *((obj_Vacuna **)o1) ; 
    obj_Vacuna *vac2 = *((obj_Vacuna **)o2) ; 
    return strcmp(vac1->getFechaVenc(vac1), vac2->getFechaVenc(vac2));
}

int compara_FechaVencimientoDes (const void * o1,const void * o2)
{
    obj_Vacuna *vac1 = *((obj_Vacuna **)o1) ; 
    obj_Vacuna *vac2 = *((obj_Vacuna **)o2) ; 
    return strcmp(vac1->getFechaVenc(vac1), vac2->getFechaVenc(vac2)) * -1;
}

int compara_CodigoAscVacuna(const void *l1, const void * l2)
{
    obj_Vacuna *vac1 =  *((obj_Vacuna **)l1);
    obj_Vacuna *vac2 =  *((obj_Vacuna **)l2);
    
    return (vac1->getVacunaId(vac1) - vac2->getVacunaId(vac2));
}

int compara_CodigoDescVacuna(const void *l1, const void * l2)
{
    obj_Vacuna *vac1 =  *((obj_Vacuna **)l1);
    obj_Vacuna *vac2 =  *((obj_Vacuna **)l2);
    
    return (vac1->getVacunaId(vac1) - vac2->getVacunaId(vac2))*-1;
}
//----------------------------------------------------
void ordenamientoVacuna(void *list, int size){

	if (menuOrdenamientoVacuna() == 1)
	{
		if(menuFormaListado() == 1) qsort(list, size, sizeof(obj_Vacuna*), compara_CodigoAscVacuna);
		else qsort(list, size, sizeof(obj_Vacuna*), compara_CodigoDescVacuna);
	}
	else
	{
		if(menuFormaListado() == 1) qsort(list, size, sizeof(obj_Vacuna*), compara_FechaVencimientoAsc);
		else qsort(list, size, sizeof(obj_Vacuna*), compara_FechaVencimientoDes);
	}
}
//----------------------------------------------------
void listarVacunas(int flag){

	obj_Vacuna *vac;
	vac = Vacuna_new();
	
	void *itm, *list;
	int i=0,size=0;

	size = vac->findAll(vac,&list,NULL);

	if(flag) ordenamientoVacuna(list, size);

	for(i=0;i<size;++i)
	{
		itm = ((Object **)list)[i];    
		((Object *)itm)->toString(itm);
	}

	if(flag) if(menuCrearArchivo() == 1) crearArchivoVacuna(list, size);

	// librerar memoria
	destroyObjList(list,size);  // liberar listado, cada instacia creada en el listado
	destroyObj(vac);
}

void ingresarVacuna(){

	obj_Vacuna *vac;
	vac = Vacuna_new();

	char str[MAX120];
	int num = 0;
	do{		
		
		num = validarEntero("Lote");
		itoa(num, str, 10);
		vac->setLote(vac, str);
		
		do
		{
			validarDato(str, "Fecha de Vencimiento (AAAA-MM-DD)");
			
		} while (!validarFecha(str));
		vac->setFechaVenc(vac, str);
		
		
		num = validarCodTipoVacuna();
		vac->setCodTipoVacuna(vac, num);
		
		num = validarEntero("Cantidad");
		vac->setCantidad(vac, num);
		
		if(vac->saveObj(vac))
			printf("Vacuna ingresada exitosamente\n");
		else printf("Error: al ingresar vacuna");

		logActividades("Ingresar Vacuna", stringVacuna(vac));

	}while(menuIngresarObjeto("Vacunas") == 1);
	
	destroyObj(vac);
}

void actualizarVacuna(){

	obj_Vacuna *vac;
	vac = Vacuna_new();
	int num, opc;
	
	num = validarEntero("Codigo");
	char str[MAX30];
	
	if(vac->findbykey(vac, num) != NOT_FOUND){
		obj_TipoVacuna *tvac;
		
		logActividades("Actualizar Vacuna Antes", stringVacuna(vac));

		do{
			switch(menuActualizarDatos("\n1)Lote \n2)Fecha de vencimiento \n3)Codigo de tipo vacuna \n4)Cantidad")){
				
				case 1: num = validarEntero("Lote"); itoa(num, str, 10); vac->setLote(vac, str); break;
				case 2: do
						{
							validarDato(str, "Fecha Vencimiento (AAAA-MM-DD)");
						} while (!validarFecha(str));
						vac->setFechaVenc(vac, str);
						break;
				
				case 3: num = validarCodTipoVacuna(); vac->setCodTipoVacuna(vac, num); break;
				case 4: num = validarEntero("Cantidad"); vac->setCantidad(vac, num); break;
			}
		}while(menuOpcionActualizar() == 1);
	
		if(vac->saveObj(vac))
			printf("Vacuna actualizada exitosamente\n");
		else printf("Error: al actualizar vacuna");

		logActividades("Actualizar Vacuna Despues", stringVacuna(vac));	

	}else{
		printf("Codigo de vacuna incorrecto\n");
	}
	destroyObj(vac);
}

static void toString_VacunaImpl(void *self)
{
	obj_Vacuna *obj=this(self);
	obj_TipoVacuna *tv = obj->getTipoVacunaObj(obj) ;
	printf("id:%d - L:%s - FV:%s - CantDosis:%.1f - Marca: %s\n", 
	obj->getVacunaId(obj),
	obj->getLote(obj),
	obj->getFechaVenc(obj),
	obj->getCantidad(obj),
	tv->getNombre(tv));
}
//----------------------------------------------------
//implementacion de getters
//----------------------------------------------------
static int getVacunaId_Impl(void *self)
{ return *( (int *) getValue(self,POS_ID)); }
//----------------------------------------------------
static char *getLoteVacuna_Impl(void *self)
{ return  (char *) getValue(self,POS_LOTE_V); }
//----------------------------------------------------
static char *getFechaVencVacuna_Impl(void *self)
{ return  (char *) getValue(self,POS_FVENC_V); }
//----------------------------------------------------
static int getCodTipoVacuna_Impl(void *self)
{ return *( (int *) getValue(self,POS_COD_TIPO_V)); }
//----------------------------------------------------
static float getCantidadVacuna_Impl(void *self)
{ return *( (float *) getValue(self,POS_CANT_V)); }
//----------------------------------------------------
//implementacion setters
//----------------------------------------------------
static void setVacunaId_Impl(void *self,int val)
{ setValue(self,POS_ID,&val); }
//----------------------------------------------------
static void setLoteVacuna_Impl(void *self,char *lote_Vacuna)
{ setValue(self,POS_LOTE_V,lote_Vacuna); }
//----------------------------------------------------
static void setFechaVencVacuna_Impl(void *self,char *fechaVenc_Vacuna)
{ setValue(self,POS_FVENC_V,fechaVenc_Vacuna); }
//----------------------------------------------------
static void setCodTipoVacuna_Impl(void *self,int val)
{ setValue(self,POS_COD_TIPO_V,&val); }
//----------------------------------------------------
static void setCantidadVacuna_Impl(void *self,float val)
{ setValue(self,POS_CANT_V,&val); }
//----------------------------------------------------
//implementacion de relaciones
//----------------------------------------------------
obj_TipoVacuna *getTipoVacunaObj_Impl(void *self)
{    
	
    obj_Vacuna *obj = this(self);
    obj->tipo_vacuna = TipoVacuna_new();
	
	if(obj->tipo_vacuna->findbykey(obj->tipo_vacuna, obj->getCodTipoVacuna(obj))!= NOT_FOUND)
    {
        return obj->tipo_vacuna;
    }
    return obj->tipo_vacuna = NULL;
}
//----------------------------------------------------
static void destroyInternalVac_Impl(void *self)
{
    obj_Vacuna *obj = this(self);
    if(obj->tipo_vacuna!=NULL)
    {
        destroyObj(obj->tipo_vacuna);
        obj->tipo_vacuna = NULL;
    }
}
//----------------------------------------------------
//implementacion constructor
//----------------------------------------------------
static void *init_Vacuna(void *self)
{
  obj_Vacuna *obj 	  = this(self);
  obj->ds  				  = &table_Vacuna;
  obj->constructor 		  = Vacuna_new;
  obj->sizeObj 			  = sizeof(obj_Vacuna*);
  obj->tipo_vacuna		  = NULL;
  //incializacion de la interfaz de la entidad  
  obj->toString    		  = toString_VacunaImpl;
  // Inicializar handlers de getters y setters
  /// getters
  obj->getVacunaId  	  = getVacunaId_Impl;
  obj->getLote  	  	  = getLoteVacuna_Impl;
  obj->getFechaVenc		  = getFechaVencVacuna_Impl;
  obj->getCodTipoVacuna   = getCodTipoVacuna_Impl;
  obj->getCantidad 		  = getCantidadVacuna_Impl;
  obj->getTipoVacunaObj	  = getTipoVacunaObj_Impl;

  /// setters  
  obj->setVacunaId     	  = setVacunaId_Impl;
  obj->setLote			  = setLoteVacuna_Impl;
  obj->setFechaVenc		  = setFechaVencVacuna_Impl;
  obj->setCodTipoVacuna   = setCodTipoVacuna_Impl;
  obj->setCantidad		  = setCantidadVacuna_Impl;
   // implementar detroy internal para liberar recursos  
  obj->destroyInternal 	  = destroyInternalVac_Impl;
  //---- acceso a relaciones  
  obj->getTipoVacunaObj   = getTipoVacunaObj_Impl;  
  return obj;
}
//----------------------------------------------------
//constructor de Vacuna
obj_Vacuna *Vacuna_new()
{ return (obj_Vacuna *)init_obj(sizeof(obj_Vacuna), init_Vacuna); }
//----------------------------------------------------

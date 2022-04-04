#include "../../includes/includelib.h"
#include "../localidad/localidad.h"
#include "../operacion/operaciones.h"
#include "enfermero.h"
#include <string.h>

THIS(obj_Enfermero)// crea definicion de funcion this para este modulo. .. Macro en config.h
//----------------------------------------------------
// Retorna la cadena que se tiene que escribir en el Archivo que contiene la lista de localidades
char *stringEnfermero(void *self){
	
	obj_Enfermero *obj=this(self);
	char cadena[MAX150] = {};
	obj_Localidad *loc = obj->getLocalidadObj(obj);
	sprintf(cadena, "Enfermero MAT: %s  -  DNI: %d  -  ApyNom: %s, %s  -  Localidad: %s\n",	 
	 obj->getMatricula(obj),
	 obj->getDni(obj),
	 obj->getApellido(obj),
	 obj->getNombres(obj),
	 loc->getNombre(loc)
	 );
	
	char *str = cadena;
	destroyObj(loc);
	return str;
}
//----------------------------------------------------
void crearArchivoEnfermero(void *list, int size){

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
		fprintf(archivo, stringEnfermero(itm)); 
	}
	fflush(archivo);
	fclose(archivo);
}
//----------------------------------------------------
//Comparadores de Localidad
//----------------------------------------------------
int compara_MatriculaAscEnfermero (const void * o1,const void * o2)
{
    obj_Enfermero *enf1 = *((obj_Enfermero **)o1) ; 
    obj_Enfermero *enf2 = *((obj_Enfermero **)o2) ; 
    return strcmp(enf1->getMatricula(enf1), enf2->getMatricula(enf2));
}

int compara_MatriculaDescEnfermero (const void * o1,const void * o2)
{
    obj_Enfermero *enf1 = *((obj_Enfermero **)o1) ; 
    obj_Enfermero *enf2 = *((obj_Enfermero **)o2) ; 
    return strcmp(enf1->getMatricula(enf1), enf2->getMatricula(enf2)) * -1;
}

int compara_ApellidoAscEnfermero (const void * o1,const void * o2)
{
    obj_Enfermero *enf1 = *((obj_Enfermero **)o1) ; 
    obj_Enfermero *enf2 = *((obj_Enfermero **)o2) ; 
    return strcmp(enf1->getApellido(enf1), enf2->getApellido(enf2));
}

int compara_ApellidoDescEnfermero (const void * o1,const void * o2)
{
    obj_Enfermero *enf1 = *((obj_Enfermero **)o1) ; 
    obj_Enfermero *enf2 = *((obj_Enfermero **)o2) ; 
    return strcmp(enf1->getApellido(enf1), enf2->getApellido(enf2)) * -1;
}

int compara_NombreAscEnfermero (const void * o1,const void * o2)
{
    obj_Enfermero *enf1 = *((obj_Enfermero **)o1) ; 
    obj_Enfermero *enf2 = *((obj_Enfermero **)o2) ; 
    return strcmp(enf1->getNombres(enf1), enf2->getNombres(enf2));
}

int compara_NombreDescEnfermero (const void * o1,const void * o2)
{
    obj_Enfermero *enf1 = *((obj_Enfermero **)o1) ; 
    obj_Enfermero *enf2 = *((obj_Enfermero **)o2) ; 
    return strcmp(enf1->getNombres(enf1), enf2->getNombres(enf2)) * -1;
}

int compara_DocAscEnfermero(const void *l1, const void * l2)
{
    obj_Enfermero *enf1 =  *((obj_Enfermero **)l1);
    obj_Enfermero *enf2 =  *((obj_Enfermero **)l2);
    
    return (enf1->getDni(enf1) - enf2->getDni(enf2));
}

int compara_DocDescEnfermero(const void *l1, const void * l2)
{
    obj_Enfermero *enf1 =  *((obj_Enfermero **)l1);
    obj_Enfermero *enf2 =  *((obj_Enfermero **)l2);
    
    return (enf1->getDni(enf1) - enf2->getDni(enf2))*-1;
}
//----------------------------------------------------
void ordenamientoEnfermero(void *list, int size){

	switch (menuOrdenamientoEnfermero())
	{
	case 1: //documento
		if(menuFormaListado() == 1) qsort(list, size, sizeof(obj_Enfermero*), compara_DocAscEnfermero);
		else qsort(list, size, sizeof(obj_Enfermero*), compara_DocDescEnfermero);
		break;
	
	case 2:	//nombre
		if(menuFormaListado() == 1) qsort(list, size, sizeof(obj_Enfermero*), compara_NombreAscEnfermero);
		else qsort(list, size, sizeof(obj_Enfermero*), compara_NombreDescEnfermero);
		break;

	case 3:	//apellido
		if(menuFormaListado() == 1) qsort(list, size, sizeof(obj_Enfermero*), compara_ApellidoAscEnfermero);
		else qsort(list, size, sizeof(obj_Enfermero*), compara_ApellidoDescEnfermero);
		break;
	
	case 4:
		if(menuFormaListado() == 1) qsort(list, size, sizeof(obj_Enfermero*), compara_MatriculaAscEnfermero);
		else qsort(list, size, sizeof(obj_Enfermero*), compara_MatriculaDescEnfermero);
		break;
	}
}
//----------------------------------------------------
void listarEnfermeros(int flag){

  	obj_Enfermero *enf;
  	enf = Enfermero_new();
	
	void *itm, *list;
	int i=0,size=0;
	char criterio[MAX_SQL];

	switch (2)
	{
	case 1: size = enf->findAll(enf,&list,NULL); break;
	
	case 2:
		sprintf(criterio, "nro_documento in (select nro_doc_enfermero from turno_vacuna where fecha>'%s')", "2021-05-11");
		size = enf->findAll(enf,&list,criterio); break;
	}

	if(flag) ordenamientoEnfermero(list, size);

	for(i=0;i<size;++i)
	{
		itm = ((Object **)list)[i];    
		((Object *)itm)->toString(itm);
	}

	if(flag) if(menuCrearArchivo() == 1) crearArchivoEnfermero(list, size);

	// librerar memoria
	destroyObjList(list,size);  // liberar listado, cada instacia creada en el listado
	destroyObj(enf);
}

void ingresarEnfermero(){

	obj_Enfermero *enf;
	enf = Enfermero_new();
	int nro_documento;
	int opc = 0;
	
	char str[MAX120];
	int num = 0;	
	do{
		
		num = validarDNINoExiste();	
		enf->setDni(enf, num);
	
		validarCadenaSinNumeros(str, "Nombre");
		mayus(str);
		enf->setNombres(enf, str);
		
		validarCadenaSinNumeros(str, "Apellido");
		mayus(str);
		enf->setApellido(enf, str);
	
		validarDato(str, "Domicilio");
		enf->setDomicilio(enf, str);
	
		num = validarEntero("Telefono");
		itoa(num, str, 10);
		enf->setTelefono(enf, str);
	
		num = validarCodPostNoExiste();
		enf->setCodPostal(enf, num);
		
		num = validarEntero("Matricula");
		itoa(num, str, 10);
		enf->setMatricula(enf, str);
		
		if(!enf->saveObj(enf)) printf("Ocurrio un error al agregar Enfermero:\n %s \n",getLastError());
		
		else printf("Ingreso de Enfermero realizado exitosamente!\n");

		logActividades("Ingresar Enfermero", stringEnfermero(enf));
				
	}while(menuIngresarObjeto("Enfermeros") == 1);
	
	destroyObj(enf);
}

void actualizarEnfermero(){

	obj_Enfermero *enf;
	enf = Enfermero_new();
	
	char str[MAX120];
	int num = 0, nro_documento = 0;

	listarEnfermeros(0);
	printf("\n");

	nro_documento = validarEntero("DNI");
	
	if(enf->findbykey(enf,nro_documento) != NOT_FOUND)
	{

		logActividades("Actualizar Enfermero Antes", stringEnfermero(enf));

		do
		{
			switch (menuActualizarDatos("\n1)Nombre \n2)Apellido \n3)Domicilio \n4)Telefono \n5)Codigo Postal \n6)Matricula"))
			{
			case 1: validarCadenaSinNumeros(str, "Nombre"); mayus(str); enf->setNombres(enf, str); break;
			case 2: validarCadenaSinNumeros(str, "Apellido"); mayus(str); enf->setApellido(enf, str); break;
			case 3: validarDato(str, "Domicilio"); enf->setDomicilio(enf, str); break;
			case 4: num = validarEntero("Telefono");
					itoa(num, str, 10);
					enf->setTelefono(enf, str);
					break;
			case 5: num = validarCodPostNoExiste(); enf->setCodPostal(enf, num); break;
			case 6: num = validarEntero("Matricula");
					itoa(num, str, 10);
					enf->setMatricula(enf, str);
					break;
			}
		} while (menuOpcionActualizar() == 1);
	}else{
		printf("Error: no existe el enfermero\n");
	}	
	if(!enf->saveObj(enf)){
		printf("Ocurrio un error al agregar Enfermero:\n %s \n",getLastError());
	}
	else{
		printf("Ingreso de Enfermero realizado exitosamente!\n");	
	}

	logActividades("Actualizar Enfermero Despues", stringEnfermero(enf));

	destroyObj(enf);
}
//----------------------------------------------------
static void toString_EnfermeroImpl(void *self)
{
     obj_Enfermero *obj=this(self);     
     obj_Localidad *loc = obj->getLocalidadObj(obj);
     printf("Enfermero MAT: %s  -  DNI: %d  -  ApyNom: %s, %s  -  Localidad: %s\n",	 
	 obj->getMatricula(obj),
	 obj->getDni(obj),
	 obj->getApellido(obj),
	 obj->getNombres(obj),
	 loc->getNombre(loc)
	 );
}
//----------------------------------------------------
//implementacion de getters
//----------------------------------------------------
static int getDniEnfermero_Impl(void *self)
{ return *( (int *) getValue(self,POS_ID)); }
//----------------------------------------------------
static char *getNombresEnfermero_Impl(void *self)
{ return  (char *) getValue(self,POS_NOMBRES_PROF); }
//----------------------------------------------------
static char *getApellidoEnfermero_Impl(void *self)
{ return  (char *) getValue(self,POS_APELLIDO_PROF); }
//----------------------------------------------------
static char *getDomicilioEnfermero_Impl(void *self)
{ return  (char *) getValue(self,POS_DOMICILIO_PROF); }
//----------------------------------------------------
static char *getTelefonoEnfermero_Impl(void *self)
{ return  (char *) getValue(self,POS_TELEFONO_PROF); }
//----------------------------------------------------
static char *getMatriculaEnfermero_Impl(void *self)
{ return  (char *) getValue(self,POS_MATRICULA_PROF); }
//----------------------------------------------------
static int getCodPostalEnfermero_Impl(void *self)
{ return *( (int *) getValue(self,POS_COD_LOC_PROF)); }
//----------------------------------------------------
//implementacion setters
//----------------------------------------------------
static void setDniEnfermero_Impl(void *self,int val)
{ setValue(self,POS_ID,&val); }
//----------------------------------------------------
static void setApellidoEnfermero_Impl(void *self,char *apellido_Enfermero)
{ setValue(self,POS_APELLIDO_PROF,apellido_Enfermero); }
//----------------------------------------------------
static void setNombresEnfermero_Impl(void *self,char *nombres_Enfermero)
{ setValue(self,POS_NOMBRES_PROF,nombres_Enfermero); }
//----------------------------------------------------
static void setDomicilioEnfermero_Impl(void *self,char *domicilio_Enfermero)
{ setValue(self,POS_DOMICILIO_PROF,domicilio_Enfermero); }
//----------------------------------------------------
static void setTelefonoEnfermero_Impl(void *self,char *telefono_Enfermero)
{ setValue(self,POS_TELEFONO_PROF,telefono_Enfermero); }
//----------------------------------------------------

static void setMatriculaEnfermero_Impl(void *self,char *mat_Enfermero)
{ setValue(self,POS_MATRICULA_PROF,mat_Enfermero); }
//----------------------------------------------------
static void setCodPostalEnfermero_Impl(void *self,int val)
{ setValue(self,POS_COD_LOC_PROF,&val); }
//----------------------------------------------------
static void destroyInternalProf_Impl(void *self)
{
	obj_Enfermero *obj = this(self);	
	if(obj->localidad!=NULL)
	  destroyObj(obj->localidad);
}
//----------------------------------------------------
//implementacion de relaciones
//----------------------------------------------------
/// ....
obj_Localidad *getLocalidadEnfermeroObj_Impl(void *self)
{
    obj_Enfermero *obj = this(self);    
    obj->localidad = Localidad_new();
    if(obj->localidad->findbykey(obj->localidad,obj->getCodPostal(obj))!=NOT_FOUND)
	{
		return obj->localidad;
	}
    return obj->localidad = NULL;
}
//----------------------------------------------------
//implementacion constructor
//----------------------------------------------------
static void *init_Enfermero(void *self)
{
  obj_Enfermero *obj    = this(self);
  obj->ds  			      = &table_Enfermero;
  obj->constructor 	      = Enfermero_new;
  obj->sizeObj 		      = sizeof(obj_Enfermero*);
  //incializacion de la interfaz de la entidad
  obj->toString    		  = toString_EnfermeroImpl;
  obj->localidad 	      = NULL;
  // Inicializar handlers de getters y setters
  /// getters    
  obj->getDni             = getDniEnfermero_Impl;
  obj->getApellido        = getApellidoEnfermero_Impl;
  obj->getNombres         = getNombresEnfermero_Impl;
  obj->getDomicilio       = getDomicilioEnfermero_Impl;
  obj->getTelefono        = getTelefonoEnfermero_Impl;
  obj->getMatricula       = getMatriculaEnfermero_Impl;
  obj->getCodPostal    	  = getCodPostalEnfermero_Impl;
  obj->getLocalidadObj    = getLocalidadEnfermeroObj_Impl;  
  /// setters    
  obj->setDni             = setDniEnfermero_Impl;
  obj->setApellido        = setApellidoEnfermero_Impl;
  obj->setNombres         = setNombresEnfermero_Impl;
  obj->setDomicilio       = setDomicilioEnfermero_Impl;
  obj->setTelefono        = setTelefonoEnfermero_Impl;
  obj->setMatricula       = setMatriculaEnfermero_Impl;
  obj->setCodPostal       = setCodPostalEnfermero_Impl;  
  // implementar detroy internal para liberar recursos  
  obj->destroyInternal 	  = destroyInternalProf_Impl;
  //---- acceso a relaciones  
  obj->getLocalidadObj 	  = getLocalidadEnfermeroObj_Impl;
  return obj;
}
//----------------------------------------------------
//constructor de Enfermero
obj_Enfermero *Enfermero_new()
{
  return (obj_Enfermero *)init_obj(sizeof(obj_Enfermero), init_Enfermero);
}
//----------------------------------------------------

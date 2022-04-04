#include "../../includes/includelib.h"
#include "../localidad/localidad.h"
#include "../operacion/operaciones.h"
#include "../validaciones/validacion.h"
#include "paciente.h"
#include <string.h>

THIS(obj_Paciente)// crea definicion de funcion this para este modulo. .. Macro en config.h
//----------------------------------------------------
// Retorna la cadena que se tiene que escribir en el Archivo que contiene la lista de localidades
char *stringPaciente(void *self){
	
	obj_Paciente *obj=this(self);
	char cadena[MAX150] = {};
	obj_Localidad *loc = obj->getLocalidadObj(obj);
	
	sprintf(cadena, "DNI: %d  - ApyNom: %s, %s - FNac: %s - Localidad: %s\n",
	 obj->getDni(obj),
	 obj->getApellido(obj),
	 obj->getNombres(obj),
	 obj->getFechaNac(obj),	 
	 loc->getNombre(loc)
	 );
	char *str = cadena;
	destroyObj(loc);
	return str;
}
//----------------------------------------------------
void crearArchivoPaciente(void *list, int size){

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
		fprintf(archivo, stringPaciente(itm)); 
	}
	fclose(archivo);
}
//----------------------------------------------------
//Comparadores de Paciente
//----------------------------------------------------
int compara_NombreAscPaciente (const void * o1,const void * o2)
{
    obj_Paciente *pac1 = *((obj_Paciente **)o1) ; 
    obj_Paciente *pac2 = *((obj_Paciente **)o2) ; 
    return strcmp(pac1->getNombres(pac1), pac2->getNombres(pac2));
}

int compara_NombreDescPaciente (const void * o1,const void * o2)
{
    obj_Paciente *pac1 = *((obj_Paciente **)o1) ; 
    obj_Paciente *pac2 = *((obj_Paciente **)o2) ; 
    return strcmp(pac1->getNombres(pac1), pac2->getNombres(pac2)) * -1;
}

int compara_ApellidoAscPaciente (const void * o1,const void * o2)
{
    obj_Paciente *pac1 = *((obj_Paciente **)o1) ; 
    obj_Paciente *pac2 = *((obj_Paciente **)o2) ; 
    return strcmp(pac1->getApellido(pac1), pac2->getApellido(pac2));
}

int compara_ApellidoDescPaciente (const void * o1,const void * o2)
{
    obj_Paciente *pac1 = *((obj_Paciente **)o1) ; 
    obj_Paciente *pac2 = *((obj_Paciente **)o2) ; 
    return strcmp(pac1->getApellido(pac1), pac2->getApellido(pac2)) * -1;
}

int compara_DniAscPaciente(const void *l1, const void * l2)
{
    obj_Paciente *pac1 =  *((obj_Paciente **)l1);
    obj_Paciente *pac2 =  *((obj_Paciente **)l2);
    
    return (pac1->getDni(pac1) - pac2->getDni(pac2));
}

int compara_DniDescPaciente(const void *l1, const void * l2)
{
    obj_Paciente *pac1 =  *((obj_Paciente **)l1);
    obj_Paciente *pac2 =  *((obj_Paciente **)l2);
    
    return (pac1->getDni(pac1) - pac2->getDni(pac2)) *-1;
}
//----------------------------------------------------
void ordenamientoPaciente(void *list, int size){

	switch (menuOrdenamientoPaciente())
	{
	case 1:	//Nombre
		if(menuFormaListado() == 1) qsort(list, size, sizeof(obj_Paciente*), compara_NombreAscPaciente);
		else qsort(list, size, sizeof(obj_Paciente*), compara_NombreDescPaciente);
		break;

	case 2: //Apellido
		if(menuFormaListado() == 1) qsort(list, size, sizeof(obj_Paciente*), compara_ApellidoAscPaciente);
		else qsort(list, size, sizeof(obj_Paciente*), compara_ApellidoDescPaciente);
		break;
		
	case 3:	//Numero de documento
		if(menuFormaListado() == 1) qsort(list, size, sizeof(obj_Paciente*), compara_DniAscPaciente);
		else qsort(list, size, sizeof(obj_Paciente*), compara_DniDescPaciente);
		break;
	}
}
//----------------------------------------------------
void listarPacientes(int flag){

  	obj_Paciente *pac; pac = Paciente_new();
	//obj_TurnoVacuna *tv; tv = TurnoVacuna_new();

	void *itm, *list;
	int i=0,size=0;
	char criterio[MAX_SQL];

	switch (menuFormaListadoPacientes())
	{
		case 1: size = pac->findAll(pac,&list,NULL); break;
	
		case 2:
			sprintf(criterio, "nro_documento in (select nro_doc_paciente from turno_vacuna where asistio=TRUE)");
			size = pac->findAll(pac,&list,criterio); break;

		case 3:
			sprintf(criterio, "cod_postal=9100 or cod_postal=9103 or cod_postal=9120");
			size = pac->findAll(pac,&list,criterio); break;
	}

	if(flag) ordenamientoPaciente(list, size);

	for(i=0;i<size;++i)
	{
		itm = ((Object **)list)[i];    
		((Object *)itm)->toString(itm);
	}

	if (flag) if(menuCrearArchivo() == 1) crearArchivoPaciente(list, size);
	
	// librerar memoria
	destroyObjList(list,size);  // liberar listado, cada instacia creada en el listado
	destroyObj(pac);
} 

void ingresarPaciente(int dni){
	
	obj_Paciente *pac;
	pac = Paciente_new();

	char str[MAX120];
	int num = 0;	

	pac->setDni(pac, dni);

	validarCadenaSinNumeros(str, "Nombre");
	mayus(str);
	pac->setNombres(pac, str);
	
	validarCadenaSinNumeros(str, "Apellido");
	mayus(str);
	pac->setApellido(pac, str);

	validarDato(str, "Domicilio");
	pac->setDomicilio(pac, str);

	num = validarEntero("Telefono");
	itoa(num, str, 10);
	pac->setTelefono(pac, str);

	num = validarCodPostNoExiste();
	pac->setCodPostal(pac, num);

	do
	{
		num = validarEntero("Es de Riesgo?");
	} while (validarRango(num, 0, 1));
	pac->setDeRiesgo(pac, num);
	
	pac->setVacunado(pac, 0);

	do
	{
		validarDato(str, "Fecha Nacimiento (AAAA-MM-DD)");
	} while (!validarFecha(str));
	pac->setFechaNac(pac, str);

	validarDato(str, "Observaciones");
	pac->setObservaciones(pac, str);
	
	if(!pac->saveObj(pac))
		printf("Ocurrio un error al agregar paciente:\n %s \n",getLastError());

	else printf("Ingreso de Paciente realizado exitosamente!\n");

	logActividades("Ingresar Paciente", stringPaciente(pac));

}

void actualizarPaciente(){

	obj_Paciente *pac;
	pac = Paciente_new();
	
	char str[MAX120];
	int num = 0, nro_documento = 0;

	nro_documento = validarEntero("DNI");
	
	if(pac->findbykey(pac,nro_documento) != NOT_FOUND)
	{

		logActividades("Actualizar Paciente Antes", stringPaciente(pac));

		do
		{
			switch (menuActualizarDatos("\n1)Nombre \n2)Apellido \n3)Domicilio \n4)Telefono \n5)Codigo Postal \n6)Es de Riesgo? \n7)Vacunado? \n8)Fecha de nacimiento \n9)Observaciones"))
			{
			case 1: validarCadenaSinNumeros(str, "Nombre"); mayus(str); pac->setNombres(pac, str); break;
			case 2: validarCadenaSinNumeros(str, "Apellido"); mayus(str); pac->setApellido(pac, str); break;
			case 3: validarDato(str, "Domicilio"); pac->setDomicilio(pac, str); break;
			case 4: num = validarEntero("Telefono");
					itoa(num, str, 10);
					pac->setTelefono(pac, str);
					break;
			case 5: num = validarCodPostNoExiste(); pac->setCodPostal(pac, num); break;
			case 6: do
					{
						num = validarEntero("Es de Riesgo?");
					} while (validarRango(num, 0, 1));
					pac->setDeRiesgo(pac, num);
					break;

			case 7: do
					{
						num = validarEntero("Vacunado?");
					} while (validarRango(num, 0, 1));
					pac->setVacunado(pac, num);
					break;

			case 8: do
					{
						validarDato(str, "Fecha Nacimiento (AAAA-MM-DD)");
					} while (!validarFecha(str));
					pac->setFechaNac(pac, str);
					break;

			case 9: validarDato(str, "Observaciones"); pac->setObservaciones(pac, str); break;
			}
		} while (menuOpcionActualizar() == 1);
		
		
		if  (pac->saveObj(pac))
			printf("Actualizacion de paciente realizada exitosamente!\n");
		
		else printf("No se puedo actualizat paciente.\n");

		logActividades("Actualizar Paciente Antes", stringPaciente(pac));

		destroyObj(pac); // liberar Recurso
	}
}
//----------------------------------------------------
static void toString_PacienteImpl(void *self)
{
     obj_Paciente *obj=this(self); 
     obj_Localidad *loc = obj->getLocalidadObj(obj);
     printf("DNI: %d  - ApyNom: %s, %s - FNac: %s - Localidad: %s\n",
	 obj->getDni(obj),
	 obj->getApellido(obj),
	 obj->getNombres(obj),
	 obj->getFechaNac(obj),	 
	 loc->getNombre(loc)
	 );
}
//----------------------------------------------------
//implementacion de getters
//----------------------------------------------------
static int getDniPaciente_Impl(void *self)
{ return *((int *) getValue(self,POS_ID)); }
//----------------------------------------------------
static char *getNombresPaciente_Impl(void *self)
{ return  (char *) getValue(self,POS_NOMBRES_PAC); }
//----------------------------------------------------
static char *getApellidoPaciente_Impl(void *self)
{ return  (char *) getValue(self,POS_APELLIDO_PAC); }
//----------------------------------------------------
static char *getFechaNacPaciente_Impl(void *self)
{ return  (char *) getValue(self,POS_FNAC_PAC); }
//----------------------------------------------------
static char *getDomicilioPaciente_Impl(void *self)
{ return  (char *) getValue(self,POS_DOMICILIO_PAC); }
//----------------------------------------------------
static char *getTelefonoPaciente_Impl(void *self)
{ return  (char *) getValue(self,POS_TELEFONO_PAC); }
//----------------------------------------------------
static int getCodPostalPaciente_Impl(void *self)
{ return *( (int *) getValue(self,POS_COD_POSTAL_PAC)); }
//----------------------------------------------------
static int getDeRiesgoPaciente_Impl(void *self)
{ return *( (int *) getValue(self,POS_DE_RIESGO_PAC)); }
//----------------------------------------------------
static int getVacunadoPaciente_Impl(void *self)
{ return *( (int *) getValue(self,POS_VACUNADO_PAC)); }
//----------------------------------------------------
static char *getObservacionesPaciente_Impl(void *self)
{ return  (char *) getValue(self,POS_OBS_PAC); }
//----------------------------------------------------
//implementacion setters
//----------------------------------------------------
static void setDniPaciente_Impl(void *self,int val)
{ setValue(self,POS_ID,&val); }
//----------------------------------------------------
static void setNombresPaciente_Impl(void *self,char *nombres_Paciente)
{ setValue(self,POS_NOMBRES_PAC,nombres_Paciente); }
//----------------------------------------------------
static void setApellidoPaciente_Impl(void *self,char *apellido_Paciente)
{ setValue(self,POS_APELLIDO_PAC,apellido_Paciente); }
//----------------------------------------------------
static void setFechaNacPaciente_Impl(void *self,char *f_nac_Paciente)
{ setValue(self,POS_FNAC_PAC,f_nac_Paciente); }
//----------------------------------------------------
static void setDomicilioPaciente_Impl(void *self,char *domicilio_Paciente)
{ setValue(self,POS_DOMICILIO_PAC,domicilio_Paciente); }
//----------------------------------------------------
static void setTelefonoPaciente_Impl(void *self,char *telefono_Paciente)
{ setValue(self,POS_TELEFONO_PAC,telefono_Paciente); }
//----------------------------------------------------
static void setCodPostalPaciente_Impl(void *self,int val)
{ setValue(self,POS_COD_POSTAL_PAC,&val); }
//----------------------------------------------------
static void setDeRiesgoPaciente_Impl(void *self,int val)
{ setValue(self,POS_DE_RIESGO_PAC,&val); }
//----------------------------------------------------
static void setVacunadoPaciente_Impl(void *self,int val)
{ setValue(self,POS_VACUNADO_PAC,&val); }
//----------------------------------------------------
static void setObservacionesPaciente_Impl(void *self,char *obs)
{ setValue(self,POS_OBS_PAC,obs); }
//----------------------------------------------------
static void destroyInternalPac_Impl(void *self)
{
	obj_Paciente *obj = this(self);	
	if(obj->localidad!=NULL)
	  destroyObj(obj->localidad);
}
//----------------------------------------------------
//implementacion de relaciones
//----------------------------------------------------
/// ....
obj_Localidad *getLocalidadPacienteObj_Impl(void *self)
{
    obj_Paciente *obj = this(self);    
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
static void *init_Paciente(void *self)
{
  obj_Paciente *obj     = this(self);  
  obj->ds  			    = &table_Paciente;
  obj->constructor 	    = Paciente_new;
  obj->sizeObj 		    = sizeof(obj_Paciente*);
  obj->localidad 	    = NULL;  
  //incializacion de la interfaz de la entidad
  obj->toString    		= toString_PacienteImpl;
  // Inicializar handlers de getters y setters
  /// getters
  obj->getDni  	  		= getDniPaciente_Impl;  
  obj->getNombres 		= getNombresPaciente_Impl;
  obj->getApellido 		= getApellidoPaciente_Impl;
  obj->getFechaNac  	= getFechaNacPaciente_Impl;
  obj->getDomicilio 	= getDomicilioPaciente_Impl;
  obj->getTelefono 		= getTelefonoPaciente_Impl;    
  obj->getCodPostal 	= getCodPostalPaciente_Impl;  
  obj->getDeRiesgo 		= getDeRiesgoPaciente_Impl;  
  obj->getVacunado   	= getVacunadoPaciente_Impl;  
  obj->getObservaciones	= getObservacionesPaciente_Impl;
  obj->getLocalidadObj = getLocalidadPacienteObj_Impl;  
  /// setters  
  obj->setDni     		= setDniPaciente_Impl;    
  obj->setNombres 		= setNombresPaciente_Impl;
  obj->setApellido 		= setApellidoPaciente_Impl;
  obj->setFechaNac 		= setFechaNacPaciente_Impl;
  obj->setDomicilio 	= setDomicilioPaciente_Impl;
  obj->setTelefono 		= setTelefonoPaciente_Impl;  
  obj->setCodPostal     = setCodPostalPaciente_Impl;
  obj->setDeRiesgo      = setDeRiesgoPaciente_Impl;
  obj->setVacunado      = setVacunadoPaciente_Impl;
  obj->setObservaciones = setObservacionesPaciente_Impl;
  // implementar detroy internal para liberar recursos  
  obj->destroyInternal 	= destroyInternalPac_Impl;
  //---- acceso a relaciones  
  obj->getLocalidadObj 	= getLocalidadPacienteObj_Impl;  
  return obj;
}
//----------------------------------------------------
//constructor de Paciente
obj_Paciente *Paciente_new()
{
  return (obj_Paciente *)init_obj(sizeof(obj_Paciente), init_Paciente);
}
//----------------------------------------------------

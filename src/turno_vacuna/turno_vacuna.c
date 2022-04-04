#include "../../includes/includelib.h"
#include "../localidad/localidad.h"
#include "../centro_atencion/centro_atencion.h"
#include "../paciente/paciente.h"
#include "../enfermero/enfermero.h"
#include "../tipo_vacuna/tipo_vacuna.h"
#include "../operacion/operaciones.h"
#include "../vacuna/vacuna.h"
#include "turno_vacuna.h"
#include <string.h>

#define MAXTURNOS 3

THIS(obj_TurnoVacuna)// crea definicion de funcion this para este modulo. .. Macro en config.h

//----------------------------------------------------
char *stringTurno(void *self){
	
	obj_TurnoVacuna *obj=this(self);
	char cadena[MAX150] = {};
	
	sprintf(cadena, "ID: %d, DNI Paciente: %d, DNI Enfermero: %d, Fecha: %s, Hora: %s, Cod Centro: %d\n",
	obj->getId(obj),
	obj->getDocPaciente(obj),
	obj->getDocEnfermero(obj),
	obj->getFecha(obj),
	obj->getHora(obj),
	obj->getCodCentroAtencion(obj)
	);
	
	char *str = cadena;

	return str;
}
//----------------------------------------------------
void crearArchivoDeTurno(void *list, int size){

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
		fprintf(archivo, stringTurno(itm)); 
	}
	fflush(archivo);
	fclose(archivo);
}
//----------------------------------------------------
int compara_CadenaAscTurno (const void * o1,const void * o2)
{
    obj_TurnoVacuna *turno1 = *((obj_TurnoVacuna **)o1) ; 
    obj_TurnoVacuna *turno2 = *((obj_TurnoVacuna **)o2) ; 
    return strcmp(turno1->getFecha(turno1), turno2->getFecha(turno2));
}

int compara_CadenaDescTurno (const void * o1,const void * o2)
{
    obj_TurnoVacuna *turno1 = *((obj_TurnoVacuna **)o1) ; 
    obj_TurnoVacuna *turno2 = *((obj_TurnoVacuna **)o2) ; 
    return strcmp(turno1->getFecha(turno1), turno2->getFecha(turno2))* -1;
}

int compara_CodigoAscTurno(const void *l1, const void * l2)
{
    obj_TurnoVacuna *turno1 =  *((obj_TurnoVacuna **)l1);
    obj_TurnoVacuna *turno2 =  *((obj_TurnoVacuna **)l2);
    
    return (turno1->getId(turno1) - turno2->getId(turno2));
}

int compara_CodigoDescTurno(const void *l1, const void * l2)
{
    obj_TurnoVacuna *turno1 =  *((obj_TurnoVacuna **)l1);
    obj_TurnoVacuna *turno2 =  *((obj_TurnoVacuna **)l2);
    return (turno1->getId(turno1) - turno2->getId(turno2)) *-1;
}
//----------------------------------------------------
void ordenamientoTurno(void *list, int size){

	if (menuOrdenamientoTurno() == 1)
	{
		if(menuFormaListado() == 1) qsort(list, size, sizeof(obj_TurnoVacuna*), compara_CadenaAscTurno);
		else qsort(list, size, sizeof(obj_TurnoVacuna*), compara_CadenaDescTurno);
	}
	else
	{
		if(menuFormaListado() == 1) qsort(list, size, sizeof(obj_TurnoVacuna*), compara_CodigoAscTurno);
		else qsort(list, size, sizeof(obj_TurnoVacuna*), compara_CodigoDescTurno);
	}
}
//----------------------------------------------------
void horaDisponible(void *listTurno, int size, char *hora, char *fecha){
	
	obj_TurnoVacuna *turnoControl;
	turnoControl = TurnoVacuna_new();
	char hora1[MAXFECHA], hora2[MAXFECHA], hora3[MAXFECHA];
	
	turnoControl = ((obj_TurnoVacuna **)listTurno)[size - 3];
	strcpy(hora3, turnoControl->getHora(turnoControl));
	
	turnoControl = ((obj_TurnoVacuna **)listTurno)[size - 2];
	strcpy(hora2, turnoControl->getHora(turnoControl));
	
	turnoControl = ((obj_TurnoVacuna **)listTurno)[size - 1];
	strcpy(hora1, turnoControl->getHora(turnoControl));
	
	if (!strcmp(hora1, hora2) && !strcmp(hora1, hora3))	//mismo horario
	{
		strcpy(hora, hora1);
		if(!strcmp(hora, "15:40:00"))
			diaSiguiente(fecha);	
		
		horaSiguiente(hora);
	}
	
	destroyObj(turnoControl);
}
//----------------------------------------------------
int agregarEnfermero(int dni, int codigo_postal){

	obj_Enfermero *enf; enf = Enfermero_new();

	void *listEnf;
	char criterio[MAX_SQL];

	sprintf(criterio, "cod_postal=%d", codigo_postal);
	int sizeEnf = enf->findAll(enf, &listEnf, criterio); //lista de enfermeros
	int i;
	
	if(dni != 0){
		for (i = 0; i < sizeEnf; i++)	//enfermero siguiente
		{
			enf = ((obj_Enfermero **)listEnf)[i];
			if (enf->getDni(enf) == dni) break;
		}
	}
	
	if ((i == (sizeEnf-1)) || (dni == 0))	//usamos el primero de la lista si nos devuelve el ultimo
	{
		enf = ((obj_Enfermero **)listEnf)[0];
	}
	else	//sino usamos el siguiente
	{
		enf = ((obj_Enfermero **)listEnf)[i + 1];
	}
	
	CLEAR(criterio, MAX_SQL);
	int dni_aux = enf->getDni(enf);
	destroyObjList(listEnf, sizeEnf);
	
	return dni_aux;
}
// devuelvo el ultimo turno asociado a un centro de atencion valido para la localidad del paciente
obj_TurnoVacuna *ultimoTurno(int cod_postal_pac){

	obj_CentroAtencion *ctr; ctr = CentroAtencion_new();
	obj_TurnoVacuna *turno; turno = TurnoVacuna_new();

	void *listCtr, *listTurno, *itm;
	char criterio[MAX_SQL];
	
	//lista de centros de atencion con el mismo codigo postal del paciente
	sprintf(criterio, "cod_postal=%d", cod_postal_pac);
	int sizeCtr = ctr->findAll(ctr, &listCtr, criterio);

	CLEAR(criterio, MAX_SQL);

	char *fecha = getFecha();
	diaSiguiente(fecha);

	int i, sizeTurno = 0;
	for (i = sizeCtr - 1; i >= 0; i--)	// centro de atencion que no tenga todos los turno llenos
	{
		ctr = ((obj_CentroAtencion **)listCtr)[i];
		
		if(!strcmp("Domingo", getDiaFecha(fecha)))
			diaSiguiente(fecha);
			
		//lista de turnos segun el centro de atencion, el dia siguiente al actual y ante ultima hora antes de cerrar
		sprintf(criterio, "cod_centro_a=%d and fecha='%s'", ctr->getId(ctr), fecha);
		sizeTurno = turno->findAll(turno, &listTurno, criterio);
		
		if(sizeTurno < MAXTURNOS) break;
		if(i == sizeCtr)	// caso en el que todos los centro de atencion esten ocupados ese dia
		{
			i = sizeCtr - 1;
			diaSiguiente(fecha);	//dia siguiente al siguiente
		}
	}
	if(sizeTurno == 0){
		turno->setDocEnfermero(turno, 0);
		turno->setCodCentroAtencion(turno, ctr->getId(ctr));
		turno->setFecha(turno, fecha);
		turno->setHora(turno, "08:00:00");
	}
	else
	{
		turno = ((obj_TurnoVacuna **)listTurno)[sizeTurno-1];
	}
	
	if(sizeCtr > 0) destroyObjList(listCtr, sizeCtr);
	
	return turno;
}

int buscarVacuna(){

	obj_TipoVacuna *tvac; tvac = TipoVacuna_new();
	obj_Vacuna *vac; vac = Vacuna_new();
	listarTipoVacunas(0);

	void *list;
	
	int size = tvac->findAll(tvac, &list, NULL);

	int idTvac = menuTipoVacuna(size);

	int i;
	for (i = 0; i < size; i++)
	{
		tvac = ((obj_TipoVacuna **)list)[i];

		if (tvac->getId(tvac) == idTvac) break;
	}
	
	vac = (obj_Vacuna *)getVacuna_Impl(idTvac);
	
	int idVac = vac->getVacunaId(vac);
	
	destroyObj(vac);
	destroyObj(tvac);

	return idVac;
}

int validarTurno(int dni_Pac){

	obj_TurnoVacuna *turnoControl; turnoControl = TurnoVacuna_new();
	char criterio[MAX_SQL];
	void *listPac;

	sprintf(criterio, "nro_doc_paciente=%d", dni_Pac);
	int sizePac = turnoControl->findAll(turnoControl, &listPac, criterio);
	int dosis = 1;
		
	if(sizePac != 0){
		turnoControl = ((obj_TurnoVacuna **)listPac)[sizePac - 1];
		dosis = turnoControl->getNroDosis(turnoControl) + 1;
	}
	
	obj_Vacuna *vac; vac = Vacuna_new();
	vac = turnoControl->getVacunaObj(turnoControl);    //vacuna del ultimo paciente
	    
	obj_TipoVacuna *tvac; tvac = TipoVacuna_new();
	tvac = vac->getTipoVacunaObj(vac);    //tipo de vacuna de la vacuna del ultimo paciente

	int dosisTvac = tvac->getCantidadDosis(tvac);

	destroyObj(tvac);
	destroyObj(vac);

	return (dosis <= dosisTvac)? dosis : 0;
}
//----------------------------------------------------
void ingresarTurno(){

	obj_TurnoVacuna *turno; turno = TurnoVacuna_new();
	obj_TurnoVacuna *turnoControl; turnoControl = TurnoVacuna_new();
	obj_Paciente *pac; pac = Paciente_new();
	
	char criterio[MAX_SQL];
	
	int dni_Pac = validarEntero("DNI del paciente");
	if(pac->findbykey(pac, dni_Pac) == NOT_FOUND) ingresarPaciente(dni_Pac);
	
	void *listPac, *turnoPac;

	int turnosTotales = turnoControl->findAll(turnoControl, &listPac, NULL);
	int dosis = 0, idVac = 1, asistio = 0;

	void *listPac2;

	sprintf(criterio, "nro_doc_paciente=%d", dni_Pac);
	int sizePac = turnoControl->findAll(turnoControl, &listPac2, criterio);

	if (turnosTotales && sizePac) 
	{
		dosis = validarTurno(dni_Pac);
		turnoControl = ((obj_TurnoVacuna **)listPac2)[sizePac-  1];
		idVac = turnoControl->getCodVacuna(turnoControl);
		asistio = turnoControl->getAsistio(turnoControl);
	}
	else
	{
		idVac = buscarVacuna();
		dosis = 1;
		asistio = 1;
	}

	if(dosis && asistio){
		
		turno->setDocPaciente(turno, dni_Pac);

		pac = turno->getPacienteObj(turno);	//paciente actual asigando al turno
		int codigoPostal = pac->getCodPostal(pac);

		//ultimo turno agendado
		turnoControl = ultimoTurno(codigoPostal);

		int centroId = turnoControl->getCodCentroAtencion(turnoControl);		
		turno->setCodCentroAtencion(turno, centroId);

		//enfermero del ultimo turno
		int dni_enf = turnoControl->getDocEnfermero(turnoControl);
		
		char hora[MAXFECHA], fecha[MAXFECHA];
		strcpy(hora, turnoControl->getHora(turnoControl));
		strcpy(fecha, turnoControl->getFecha(turnoControl));
		
		void *listTurno;
		sprintf(criterio, "cod_centro_a=%d and fecha='%s'",centroId, fecha);
		int size = turnoControl->findAll(turnoControl, &listTurno, criterio);
		
		int dni_enfermero = 0;
		
		if (size >= 3)
		{	//ultimos tres turnos
			horaDisponible(listTurno, size, hora, fecha);
			dni_enfermero = agregarEnfermero(dni_enf, codigoPostal);
			turno->setDocEnfermero(turno, dni_enfermero);
		}
		else
		{
			dni_enfermero = agregarEnfermero(dni_enf, codigoPostal);
			turno->setDocEnfermero(turno, dni_enfermero);
		}
		
		turno->setHora(turno, hora);
		turno->setFecha(turno, fecha);
		turno->setCodVacuna(turno, idVac);
		turno->setNroDosis(turno, dosis);
		turno->setAsistio(turno, false);
		
		if(turno->saveObj(turno)){
			printf("\nTurno ingresado correctamente\n");
			printf("\nDatos del turno: \n");
			turno->toString(turno);
		}else{
			printf("\nError al ingresar el turno\n");
		}
		logActividades("Ingresar Turno Vacuna", stringTurno(turno));
	}
	else
	{
		printf("El paciente ya completo sus dosis o no asistio a su turno anterior");
	}

	destroyObj(turnoControl);
	destroyObj(pac);
	
}

void registrarVacunacion(){

	obj_Paciente *pac; pac = Paciente_new();
	obj_TurnoVacuna *turno; turno = TurnoVacuna_new();

	char criterio[MAX_SQL];
	
	int dni_Pac = validarEntero("DNI del paciente");
	
	if(pac->findbykey(pac, dni_Pac) != NOT_FOUND) 
	{
		void *listPac, *turnoPac;
		sprintf(criterio, "nro_doc_paciente=%d", dni_Pac);
		int sizePac = turno->findAll(turno, &listPac, criterio);

		turno = ((obj_TurnoVacuna **)listPac)[sizePac - 1];

		char fecha[MAXFECHA];
		strcpy(fecha, turno->getFecha(turno));

		if (!turno->getAsistio(turno) && !strcmp(fecha, getFecha()))
		{
			turno->setAsistio(turno, 1);
			pac->setVacunado(pac, 1);

			if(!pac->saveObj(pac)) printf("Ocurrio un error al vacunar el paciente:\n %s \n",getLastError());
			else printf("El Paciente se vacuno exitosamente!\n");
			
			turno->isNewObj = false;
			if(turno->saveObj(turno)); 
			else printf("\nError alctualizar el turno\n");		
		}
		else
		{
			printf("El paciente ya esta vacunado, se vencio el plazo de vacunacion o todavia no es el dia de su vacunacion\n");
		}

		destroyObj(turno);
	}
	else
	{
		printf("ERROR: El paciente no existe \n");
	}

	destroyObj(pac);
}

void actualizarTurno(){
	obj_TurnoVacuna *turno; turno = TurnoVacuna_new();
	obj_TurnoVacuna *turnoControl; turnoControl = TurnoVacuna_new();
	obj_Paciente *pac; pac = Paciente_new();
	
	char criterio[MAX_SQL];
	void *listPac, *listCtr;
	
	int dni_Pac = validarEntero("DNI del paciente");
	if(pac->findbykey(pac, dni_Pac) != NOT_FOUND){
		
		sprintf(criterio, "nro_doc_paciente=%d", dni_Pac);
		int sizePac = turno->findAll(turno, &listPac, criterio);

		//ultimo turno del paciente, el cual tenemos que modificar
		turno = ((obj_TurnoVacuna **)listPac)[sizePac - 1];
		
		logActividades("Actualizar Turno Vacuna Antes", stringTurno(turno));

		if (!turno->getAsistio(turno))
		{
			//ultimo turno aprtir de lcentro de atencion del paciente
			turnoControl = ultimoTurno(pac->getCodPostal(pac));

			char horaControl[MAXFECHA], fecha[MAXFECHA];
			strcpy(horaControl, turnoControl->getHora(turnoControl));
			strcpy(fecha, turnoControl->getFecha(turnoControl));
			
			int doc_enf = agregarEnfermero(turnoControl->getDocEnfermero(turnoControl), pac->getCodPostal(pac));
			
			turno->setDocEnfermero(turno, doc_enf);
			
			void *listTurno;
			sprintf(criterio, "cod_centro_a=%d and fecha='%s'",turnoControl->getCodCentroAtencion(turnoControl), fecha);
			int size = turnoControl->findAll(turnoControl, &listTurno, criterio);

			char hora[MAXFECHA];
			
			if(size >= 3) horaDisponible(listTurno, size, hora, fecha);
			else strcpy(hora, "08:00:00");
		
			turno->setHora(turno, hora);
			turno->setFecha(turno, fecha);
			
			if(turno->saveObj(turno)) printf("Turno actualizado correctamente\n");
			else printf("\nError alctualizar el turno\n");	
			
			logActividades("Actualizar Turno Vacuna Despues", stringTurno(turno));

			destroyObj(turnoControl);
		}
		else printf("No se puede actualizar paciente ya vacunado\n");		

	}else{
		printf("No existe el paciente\n");
	}

	destroyObj(turno);	
	destroyObj(pac);
	
}

void listarTurnos(int flag){

  	obj_TurnoVacuna *turno;
	turno = TurnoVacuna_new();
	
	void *itm, *list;
	int i=0,size=0;

	switch (menuFormaListadoTurnos())
	{
		case 1: size = turno->findAll(turno,&list,NULL); break;
	
		case 2: size= turno->findAll(turno, &list,"asistio=TRUE and cod_vacuna in(select vac.codigo from vacunas vac inner join  tipo_vacuna tvac on tvac.codigo=vac.cod_tipo_vacuna where tvac.nombre='Sputnik V'  )"); break;
	}

	if(flag) ordenamientoTurno(list, size);
	
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
	destroyObj(turno);
}
//----------------------------------------------------
static void toString_TurnoVacunaImpl(void *self)
{
    obj_TurnoVacuna *obj=this(self);
    printf("ID: %d, DNI Paciente: %d, DNI Enfermero: %d, Fecha: %s, Hora: %s, Cod Centro: %d\n",
	obj->getId(obj),
	obj->getDocPaciente(obj),
	obj->getDocEnfermero(obj),
	obj->getFecha(obj),
	obj->getHora(obj),
	obj->getCodCentroAtencion(obj)
	);
}
//----------------------------------------------------
//implementacion de getters
//----------------------------------------------------
static int getIdTurnoVacuna_Impl(void *self)
{ return *( (int *) getValue(self,POS_ID)); }
//----------------------------------------------------
static int getCodVacuna_Impl(void *self)
{ return *( (int *) getValue(self,POS_COD_VACUNA_T)); }
//----------------------------------------------------
static int getCodCentroAtencion_T_Impl(void *self)
{ return *( (int *) getValue(self,POS_COD_CENTRO_A_T)); }
//----------------------------------------------------
static int getNroDosis_T_Impl(void *self)
{ return *( (int *) getValue(self,POS_NRO_DOSIS_T)); }
//----------------------------------------------------
static int getCodPaciente_T_Impl(void *self)
{ return *( (int *) getValue(self,POS_DOC_PACIENTE_T)); }
//----------------------------------------------------
static int getCodEnfermero_T_Impl(void *self)
{ return *( (int *) getValue(self,POS_DOC_ENFERMERO_T)); }
//----------------------------------------------------
static char *getFecha_T_Impl(void *self)
{ return  (char *) getValue(self,POS_FECHA_T); }
//----------------------------------------------------
static char *getHora_T_Impl(void *self)
{ return  (char *) getValue(self,POS_HORA_T); }
//----------------------------------------------------
static int getAsistio_T_Impl(void *self)
{ return  *((int *) getValue(self,POS_ASISTIO_T)); }
//----------------------------------------------------
//implementacion setters
//----------------------------------------------------
static void setIdTurnoVacuna_Impl(void *self,int val)
{ setValue(self,POS_ID,&val); }
//----------------------------------------------------
static void setAsistio_T_Impl(void *self,int val)
{ setValue(self, POS_ASISTIO_T, &val); }
//----------------------------------------------------
static void setNroDosis_T_Impl(void *self,int val)
{ setValue(self, POS_NRO_DOSIS_T, &val); }
//----------------------------------------------------
static void setCodVacuna_T_Impl(void *self,int val)
{ setValue(self, POS_COD_VACUNA_T, &val); }
//----------------------------------------------------
static void setCodCentroAtencion_T_Impl(void *self,int val)
{ setValue(self,POS_COD_CENTRO_A_T,&val); }
//----------------------------------------------------
static void setDocPaciente_T_Impl(void *self,int val)
{ setValue(self,POS_DOC_PACIENTE_T,&val); }
//----------------------------------------------------
static void setDocEnfermero_T_Impl(void *self,int val)
{ setValue(self,POS_DOC_ENFERMERO_T,&val); }
//----------------------------------------------------
static void setFecha_T_Impl(void *self,char *fecha)
{ setValue(self,POS_FECHA_T,fecha); }
//----------------------------------------------------
static void setHora_T_Impl(void *self,char *hora)
{ setValue(self,POS_HORA_T,hora); }
//----------------------------------------------------
static void destroyInternalTurnoVacuna_Impl(void *self)
{
	obj_TurnoVacuna *obj = this(self);
	if(obj->paciente != NULL){
		destroyObj(obj->paciente);
		obj->paciente = NULL;
	}	
	if(obj->enfermero != NULL){
		destroyObj(obj->enfermero);
		obj->enfermero = NULL;
	}
	if(obj->centro_atencion != NULL){
		destroyObj(obj->centro_atencion);
		obj->centro_atencion = NULL;
	}
	if(obj->vacuna != NULL){
		destroyObj(obj->vacuna);
		obj->vacuna = NULL;
	}
		
}	
//----------------------------------------------------
//implementacion de relaciones
//----------------------------------------------------
obj_Paciente *getPacienteTurnoVacunaObj_Impl(void *self)
{
	obj_TurnoVacuna *turno = this(self);
	turno->paciente = Paciente_new();
	if(turno->paciente->findbykey(turno->paciente, turno->getDocPaciente(turno))!=NOT_FOUND)
	{
    	return turno->paciente;
	}

	return turno->paciente = NULL;
}
//----------------------------------------------------
obj_Enfermero *getEnfermeroTurnoVacunaObj_Impl(void *self)
{
	obj_TurnoVacuna *turno = this(self);
	turno->enfermero = Enfermero_new();
	if(turno->enfermero->findbykey(turno->enfermero, turno->getDocEnfermero(turno))!=NOT_FOUND)
	{
    	return turno->enfermero;
	}

	return turno->enfermero = NULL;
}
//----------------------------------------------------
obj_CentroAtencion *getCentroAtencionTurnoVacunaObj_Impl(void *self)
{
	obj_TurnoVacuna *turno = this(self);
	turno->centro_atencion = CentroAtencion_new();
	if(turno->centro_atencion->findbykey(turno->centro_atencion, turno->getCodCentroAtencion(turno))!=NOT_FOUND)
	{
    	return turno->centro_atencion;
	}

	return turno->centro_atencion = NULL;
}
//----------------------------------------------------
    
obj_Vacuna *getVacunaTurnoVacunaObj_Impl(void *self)
{
	obj_TurnoVacuna *turno = this(self);
	turno->vacuna = Vacuna_new();
	if(turno->vacuna->findbykey(turno->vacuna, turno->getCodVacuna(turno))!=NOT_FOUND)
	{
    	return turno->vacuna;
	}

	return turno->vacuna = NULL;
}
//----------------------------------------------------
//implementacion constructor
//----------------------------------------------------
static void *init_TurnoVacuna(void *self)
{
  obj_TurnoVacuna *obj  = this(self);
  obj->ds                     = &table_TurnoVacuna;
  obj->constructor            = TurnoVacuna_new;
  obj->sizeObj                = sizeof(obj_TurnoVacuna*);
  //incializacion de la interfaz de la entidad
  obj->toString               = toString_TurnoVacunaImpl;
  obj->paciente				  = NULL;
  obj->enfermero		  	  = NULL;
  obj->vacuna				  = NULL;
  // Inicializar handlers de getters y setters
  /// getters
  obj->getId = getIdTurnoVacuna_Impl;
  obj->getCodVacuna			  =getCodVacuna_Impl;  
  obj->getNroDosis			  =getNroDosis_T_Impl;
  obj->getCodCentroAtencion   = getCodCentroAtencion_T_Impl;
  obj->getDocPaciente         = getCodPaciente_T_Impl;
  obj->getDocEnfermero  	  = getCodEnfermero_T_Impl;
  obj->getFecha               = getFecha_T_Impl;  
  obj->getHora                = getHora_T_Impl;
  obj->getAsistio			  = getAsistio_T_Impl;
    /// setters  
  obj->setId 				  = setIdTurnoVacuna_Impl;
  obj->setAsistio			  = setAsistio_T_Impl; 
  obj->setCodVacuna			  =setCodVacuna_T_Impl;
  obj->setNroDosis			  =setNroDosis_T_Impl;
  obj->setCodCentroAtencion   = setCodCentroAtencion_T_Impl;
  obj->setDocPaciente         = setDocPaciente_T_Impl;
  obj->setDocEnfermero  	  = setDocEnfermero_T_Impl;
  obj->setFecha               = setFecha_T_Impl;  
  obj->setHora                = setHora_T_Impl;
  // implementar detroy internal para liberar recursos
  obj->destroyInternal        = destroyInternalTurnoVacuna_Impl;
  //---- acceso a relaciones    
  obj->getCentroAtencionObj	  = getCentroAtencionTurnoVacunaObj_Impl;
  obj->getPacienteObj		  = getPacienteTurnoVacunaObj_Impl;
  obj->getEnfermeroObj  	  = getEnfermeroTurnoVacunaObj_Impl;
  obj->getVacunaObj			  = getVacunaTurnoVacunaObj_Impl;
  return obj;
}
//----------------------------------------------------
//constructor de TurnoVacuna
obj_TurnoVacuna *TurnoVacuna_new()
{
  return (obj_TurnoVacuna *)init_obj(sizeof(obj_TurnoVacuna), init_TurnoVacuna);
}
//----------------------------------------------------

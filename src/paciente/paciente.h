#ifndef PAC_INCLUDED
	#define PAC_INCLUDED
	#define CNT_COL_PAC 10	
	#define POS_NOMBRES_PAC 1
	#define POS_APELLIDO_PAC 2
	#define POS_FNAC_PAC 3	
	#define POS_DOMICILIO_PAC 4
	#define POS_TELEFONO_PAC 5
	#define POS_COD_POSTAL_PAC 6
	#define POS_DE_RIESGO_PAC 7
	#define POS_VACUNADO_PAC 8
	#define POS_OBS_PAC 9
	//----------------------------------------------------
	typedef struct {	    
		IOBJECT	 // crea definicion de propiedades comunes a Object .. Macro en orm.h     
	    //-- getters	    
		getPropertyIntPtr   getDni;
		getPropertyCharPtr  getNombres;
		getPropertyCharPtr  getApellido;		
		getPropertyCharPtr  getFechaNac;
		getPropertyCharPtr  getDomicilio;
		getPropertyCharPtr  getTelefono;
		getPropertyIntPtr   getCodPostal;
		getPropertyIntPtr   getDeRiesgo;
		getPropertyIntPtr   getVacunado;
		getPropertyCharPtr  getObservaciones;
	    //-- setters
		setPropertyIntPtr   setDni;
		setPropertyCharPtr  setNombres;
		setPropertyCharPtr  setApellido;		
		setPropertyCharPtr  setFechaNac;
		setPropertyCharPtr  setDomicilio;
		setPropertyCharPtr  setTelefono;
		setPropertyIntPtr   setCodPostal;
		setPropertyIntPtr   setDeRiesgo;
		setPropertyIntPtr   setVacunado;
		setPropertyCharPtr  setObservaciones;
		// getter de objeto relacionado
		getLocalidadObjPtr  getLocalidadObj;	    
	    obj_Localidad *localidad;
	}obj_Paciente;
	// funcionalidad publica que se implementa en Paciente.c
	extern obj_Paciente *Paciente_new ();
	// meta data para acceder a las Pacientes - definicion de las columnas de la tabla
	static Column cols_Paciente[CNT_COL_PAC]=
	{ 
	//definicion del mapeo, por cada columna de la tabla con los atributos del pseudobjeto.
	// nombre de la columna, tipo, tamaño, si es clave, si es autonumerado.
	{"nro_documento",t_int,sizeof(int),true,false},	
	{"nombres",t_varchar,(sizeof(char)*MAX80)+1,false,false},
	{"apellido",t_varchar,(sizeof(char)*MAX90)+1,false,false},	
	{"fecha_nac",t_date,(sizeof(char)*MAXFECHA)+1,false,false},	
	{"domicilio",t_varchar,(sizeof(char)*MAX120)+1,false,false},
	{"telefono",t_varchar,(sizeof(char)*MAX20)+1,false,false},
	{"cod_postal",t_int,sizeof(int),false,false},
	{"de_riesgo",t_bool,sizeof(int),false,false},
	{"vacunado",t_bool,sizeof(int),false,false},
	{"observaciones",t_varchar,(sizeof(char)*MAXOBS)+1,false,false},
	};
	// plantilla para la Paciente.
	//static Table table_Paciente={"paciente",CNT_COL_PAC,0, cols_Paciente,NULL};
	static Table table_Paciente={"pacientes",CNT_COL_PAC,0, cols_Paciente,NULL};
	typedef obj_Paciente *(*getPacienteObjPtr)(void *self);
#endif

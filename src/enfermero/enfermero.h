#ifndef PROF_INCLUDED
#define PROF_INCLUDED
#define CNT_COL_PROF 7
	
	#define POS_NOMBRES_PROF 1
	#define POS_APELLIDO_PROF 2
	#define POS_DOMICILIO_PROF 3
	#define POS_TELEFONO_PROF 4
	#define POS_MATRICULA_PROF 5
	#define POS_COD_LOC_PROF 6
	
	//----------------------------------------------------
	typedef struct {	    
		IOBJECT	 // crea definicion de propiedades comunes a Object .. Macro en orm.h     
	    //-- getters	    
		getPropertyIntPtr  getDni;
		getPropertyCharPtr getNombres;
		getPropertyCharPtr getApellido;
		getPropertyCharPtr getDomicilio;
		getPropertyCharPtr getTelefono;
		getPropertyCharPtr getMatricula;
		getPropertyIntPtr  getCodPostal;
	    //-- setters	    
	    setPropertyIntPtr  setDni;
	    setPropertyCharPtr setNombres;
		setPropertyCharPtr setApellido;
	    setPropertyCharPtr setDomicilio;
	    setPropertyCharPtr setTelefono;
	    setPropertyIntPtr  setCodPostal;
	    setPropertyCharPtr setMatricula;
	    // getter de objeto relacionado
	    getLocalidadObjPtr getLocalidadObj;	    
	    obj_Localidad *localidad;
	}obj_Enfermero;
	// funcionalidad publica que se implementa en Enfermero.c
	extern obj_Enfermero *Enfermero_new ();
	// meta data para acceder a las Enfermeros - definicion de las columnas de la tabla
	static Column cols_Enfermero[CNT_COL_PROF]=
	{ 
	//definicion del mapeo, por cada columna de la tabla con los atributos del pseudobjeto.
	// nombre de la columna, tipo, tama�o, si es clave, si es autonumerado.
	{"nro_documento",t_int,sizeof(int),true,false},	
	{"nombres",t_varchar,(sizeof(char)*MAX90)+1,false,false},
	{"apellido",t_varchar,(sizeof(char)*MAX50)+1,false,false},
	{"domicilio",t_varchar,(sizeof(char)*MAX)+1,false,false},
	{"telefono",t_varchar,(sizeof(char)*MAX20)+1,false,false},
	{"matricula",t_varchar,(sizeof(char)*MAX20)+1,false,false},
	{"cod_postal",t_int,sizeof(int),false,false},
	};
	// plantilla para la Enfermero.
	//static Table table_Enfermero={"profesional",CNT_COL_PROF,0, cols_Enfermero,NULL};
	static Table table_Enfermero={"enfermeros",CNT_COL_PROF,0, cols_Enfermero,NULL};
	typedef obj_Enfermero *(*getEnfermeroObjPtr)(void *self);
#endif

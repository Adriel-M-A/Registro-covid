#ifndef CENT_A_INCLUDED
	#define CENT_A_INCLUDED
	#define CNT_COL_CENT_A 5
	#define POS_NOMBRE_CENTRO 1
	#define POS_DOMICILIO_CENTRO 2
	#define POS_TELEFONO_CENTRO 3
	#define POS_CODPOSTAL_CENTRO 4
	//----------------------------------------------------
	typedef struct {		
		IOBJECT	 // crea definicion de propiedades comunes a Object .. Macro en orm.h  	
		//-- getters
		getPropertyIntPtr  getId;
		getPropertyCharPtr getNombre;
		getPropertyCharPtr getDomicilio;
		getPropertyCharPtr getTelefono;	
		getPropertyIntPtr  getCodPostal;
		//-- setters
		setPropertyIntPtr  setId;
		setPropertyCharPtr setDenominacion;
		setPropertyCharPtr setDomicilio;
		setPropertyCharPtr setTelefono;	
		setPropertyIntPtr  setCodPostal;
		// getter de objeto relacionado
		getLocalidadObjPtr getLocalidadObj;	    
	    obj_Localidad *localidad;
	}obj_CentroAtencion;
	// funcionalidad publica que se implementa en Consultorio.c
	extern obj_CentroAtencion *CentroAtencion_new();
	// meta data para acceder a los Consultorios - definicion de las columnas de la tabla
	static Column cols_CentroAtencion[CNT_COL_CENT_A]=
	{ 
	//definicion del mapeo, por cada columna de la tabla con los atributos del pseudobjeto.
	// nombre de la columna, tipo, tamaño, si es clave, si es autonumerado.
	{"codigo",t_int,sizeof(int),true,true}, 
	{"nombre",t_varchar,(sizeof(char)*MAX60)+1,false,false},
	{"domicilio",t_varchar,(sizeof(char)*MAX90)+1,false,false},
	{"telefono",t_varchar,(sizeof(char)*MAX20)+1,false,false},
	{"cod_postal",t_int,sizeof(int),false,false},
	};
	// plantilla para Centro de Atencion.
	static Table table_CentroAtencion={"centro_atencion",CNT_COL_CENT_A,0, cols_CentroAtencion,NULL};
	typedef obj_CentroAtencion *(*getCentroAtencionObjPtr)(void *self);
#endif

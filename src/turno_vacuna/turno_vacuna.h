#ifndef TURNO_VAC_INCLUDED
	#define TURNO_VAC_INCLUDED
	#define CNT_COL_TURNO_VAC 9
	#define POS_FECHA_T 1
	#define POS_HORA_T 2
	#define POS_DOC_PACIENTE_T 3
	#define POS_DOC_ENFERMERO_T 4
	#define POS_ASISTIO_T 5
	#define POS_COD_CENTRO_A_T 6
	#define POS_NRO_DOSIS_T 7
	#define POS_COD_VACUNA_T 8
	
	//----------------------------------------------------
	typedef struct {	    
		IOBJECT	 // crea definicion de propiedades comunes a Object .. Macro en orm.h     
	    //-- getters
	    getPropertyIntPtr       getId;
	    getPropertyCharPtr      getFecha;  //formato: yyyy-mm-dd
	    getPropertyCharPtr      getHora;  //formato:  HH:mm:ss
	    getPropertyIntPtr       getDocPaciente;
	    getPropertyIntPtr       getDocEnfermero;
	    getPropertyIntPtr       getAsistio;
	    getPropertyIntPtr       getCodCentroAtencion;
	    getPropertyIntPtr       getNroDosis;
	    getPropertyIntPtr       getCodVacuna;
	    //-- setters
	    setPropertyIntPtr       setId;
	    setPropertyCharPtr      setFecha;
	    setPropertyCharPtr      setHora;
	    setPropertyIntPtr       setDocPaciente;
		setPropertyIntPtr       setDocEnfermero;
		setPropertyIntPtr       setAsistio;
		setPropertyIntPtr       setCodCentroAtencion;
		setPropertyIntPtr       setNroDosis;
		setPropertyIntPtr       setCodVacuna;
		// getter de objeto relacionado
	    getPacienteObjPtr       getPacienteObj;
	    getEnfermeroObjPtr      getEnfermeroObj;
	    getCentroAtencionObjPtr getCentroAtencionObj;
		getVacunaObjPtr 	    getVacunaObj;
		obj_Paciente 			*paciente;
	    obj_Enfermero 			*enfermero;
		obj_CentroAtencion 		*centro_atencion;
		obj_Vacuna 				*vacuna;	
	}obj_TurnoVacuna;
	// funcionalidad publica que se implementa en TurnoVacuna.c
	extern obj_TurnoVacuna *TurnoVacuna_new();
	// meta data para acceder a las TurnoVacunas - definicion de las columnas de la tabla
	static Column cols_TurnoVacuna[CNT_COL_TURNO_VAC]=
	{ 
	//definicion del mapeo, por cada columna de la tabla con los atributos del pseudobjeto.
	// nombre de la columna, tipo, tamaño, si es clave, si es autonumerado.
	{"codigo",t_int,sizeof(int),true,true}, 
	{"fecha",t_varchar,(sizeof(char)*MAX10)+1,false,false},
	{"hora",t_varchar,(sizeof(char)*MAX10)+1,false,false},
	{"nro_doc_paciente",t_int,sizeof(int),false,false},
	{"nro_doc_enfermero",t_int,sizeof(int),false,false},
	{"asistio",t_bool,sizeof(int),false,false},    	
	{"cod_centro_a",t_int,sizeof(int),false,false},	
	{"nro_dosis",t_int,sizeof(int),false,false},
	{"cod_vacuna",t_int,sizeof(int),false,false},
	};
	// plantilla para la TurnoVacuna.
	static Table table_TurnoVacuna={"turno_vacuna",CNT_COL_TURNO_VAC,0, cols_TurnoVacuna,NULL};
#endif

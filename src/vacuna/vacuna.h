#ifndef VAC_INCLUDED
	#define VAC_INCLUDED
	#define CNT_COL_VAC 5
	#define POS_LOTE_V 1
	#define POS_FVENC_V 2
	#define POS_COD_TIPO_V 3
	#define POS_CANT_V 4
	//----------------------------------------------------
	typedef struct {
		IOBJECT	  // crea definicion de propiedades comunes a Object .. Macro en orm.h  
	    //-- getters
	    getPropertyIntPtr   getVacunaId;
		getPropertyCharPtr  getLote;
		getPropertyCharPtr  getFechaVenc;
		getPropertyIntPtr   getCodTipoVacuna;
		getPropertyFloatPtr getCantidad;
	    //-- setters
	    setPropertyIntPtr   setVacunaId;
	    setPropertyCharPtr  setLote;
		setPropertyCharPtr  setFechaVenc;
		setPropertyIntPtr   setCodTipoVacuna;
		setPropertyFloatPtr setCantidad;
		// getter de objeto relacionado
		getTipoVacunaObjPtr getTipoVacunaObj;	    
	    obj_TipoVacuna *tipo_vacuna;
	}obj_Vacuna;
	// funcionalidad publica que se implementa en Vacuna.c
	extern obj_Vacuna *Vacuna_new ();
	// meta data para acceder a las Vacunas - definicion de las columnas de la tabla
	static Column cols_Vacuna[CNT_COL_VAC]=
	{ 
	//definicion del mapeo, por cada columna de la tabla con los atributos del pseudobjeto.
	// nombre de la columna, tipo, tamaño, si es clave, si es autonumerado.
	{"codigo",t_int,sizeof(int),true,true}, 
	{"lote",t_varchar,(sizeof(char)*MAX10)+1,false,false},
	{"fecha_venc",t_varchar,(sizeof(char)*MAXFECHA)+1,false,false},
	{"cod_tipo_vacuna",t_int,sizeof(int),false,false}, 
	{"cantidad",t_float,sizeof(float),false,false}, 
	};
	// plantilla para la Vacuna.
	static Table table_Vacuna={"vacunas",CNT_COL_VAC,0, cols_Vacuna,NULL};
	// generar PunteroGenerico para usar puntero funcion que obtenga pseudoObjeto Vacuna
	typedef obj_Vacuna *(*getVacunaObjPtr)(void *self);
#endif

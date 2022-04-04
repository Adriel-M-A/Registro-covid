#ifndef TIPO_VAC_INCLUDED
	#define TIPO_VAC_INCLUDED
	#define CNT_COL_TIPO_VAC 3
	#define POS_NOMBRE_TV 1
	#define POS_CANT_DOSIS_TV 2
	//----------------------------------------------------
	typedef struct {
		IOBJECT	 // crea definicion de propiedades comunes a Object .. Macro en orm.h     
	    //-- getters
	    getPropertyIntPtr  getId;
		getPropertyCharPtr getNombre;
		getPropertyIntPtr  getCantidadDosis;
	    //-- setters
	    setPropertyIntPtr  setId;
		setPropertyCharPtr setNombre;  
		setPropertyIntPtr  setCantidadDosis;
	}obj_TipoVacuna;
	// funcionalidad publica que se implementa en TipoVacuna.c
	extern obj_TipoVacuna *TipoVacuna_new ();
	// meta data para acceder a las TipoVacunas - definicion de las columnas de la tabla
	static Column cols_TipoVacuna[CNT_COL_TIPO_VAC]=
	{ 
	//definicion del mapeo, por cada columna de la tabla con los atributos del pseudobjeto.
	// nombre de la columna, tipo, tamaño, si es clave, si es autonumerado.
	{"codigo",t_int,sizeof(int),true,true}, 
	{"nombre",t_varchar,(sizeof(char)*MAX90)+1,false,false},
	{"cant_dosis",t_int,sizeof(int),false,false}, 
	};
	// plantilla para la TipoVacuna.
	static Table table_TipoVacuna={"tipo_vacuna",CNT_COL_TIPO_VAC,0, cols_TipoVacuna,NULL};
	// generar PunteroGenerico para usar puntero funcion que obtenga pseudoObjeto TipoVacuna
	typedef obj_TipoVacuna *(*getTipoVacunaObjPtr)(void *self);
#endif

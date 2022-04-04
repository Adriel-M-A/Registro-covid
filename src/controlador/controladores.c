#include "../../includes/includes.h"
#include "../menu/menus.h"

// control de opciones del menu de listados
void controladorListados(int opc){

	switch (opc)
	{
		case 1: listarTurnos(1); break;
		case 2: listarLocalidades(1); break;
		case 3: listarEnfermeros(1); break;
		case 4: listarPacientes(1); break;
		case 5: listarTipoVacunas(1); break;
		case 6: listarVacunas(1); break;
		case 7: listarCentroDeAtencion(1); break;
		default: printf("Esta funcionalidad no esta implementada");	break;
	}
}

// control de opciones del menu de actualizaciones
void controladorActualizaciones(int opc){
	
	switch (opc)
	{
		case 1: actualizarPaciente(); break;
		case 2: actualizarEnfermero(); break;
		case 3: acualizarCentroAtencion(); break;
		case 4: actualizarVacuna(); break;
		case 5: actualizarTipoVacuna(); break;
		case 6: actualizarTurno(); break;
		case 7: actualizarLocalidad(); break;
		default: printf("Esta funcionalidad no esta implementada");	break;
	}
}

// control de opciones del menu de ingresos
void controladorIngresos(int opc){
	
	switch (opc)
	{
		case 1: ingresarEnfermero(); break;
		case 2: ingresarCentroAtencion(); break;
		case 3: ingresarVacuna(); break;
		case 4: ingresarTipoVacuna(); break;
		case 5: ingresarTurno(); break;
		case 6: ingresarLocalidad(); break;
		default: printf("Esta funcionalidad no esta implementada");	break;
	}
}

int controlSubMenus(int opc, int opc_submenu){
	
	if(opc_submenu > 0){					//si se cumple se quiere salir
		switch (opc)
		{
			case 1: controladorIngresos(opc_submenu); break;
			case 2: controladorActualizaciones(opc_submenu); break;
			case 3: controladorListados(opc_submenu); break;
		}
	}

	return opc_submenu;
}

int controlMenuBase(int opc){
	
	int opc_submenu = 0;

	switch (opc)
	{
	case 1: opc_submenu = menuIngresos(); break;
	case 2: opc_submenu = menuActualizaciones(); break;
	case 3: opc_submenu = menuListados(); break;
	case 4: registrarVacunacion(); break;
	}
	
	if(opc != 4) opc = controlSubMenus(opc, opc_submenu);

	return opc;
}

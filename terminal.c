#include "operaciones.h"
#include "terminal.h"
#include "splay.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
	
void mostrar_asistente_generacion_contrasena(){
	
	/* Función destinada a llamar a las funciones de generación de contraseña
	 * 
	 * Entradas: Ninguna
	 * Salidas: Ninguna
	 * Restricciones: Ninguna																				*/
	
		generar_contrasena();
		
		
	}

void mostrar_asistente_contenido(){
	
	/* Función destinada a llamar a las funciones de acceso a mostrar contenido del arbol de splay
	 * 
	 * Entradas: Ninguna
	 * Salidas: Ninguna
	 * Restricciones: Ninguna																				*/
	
		
		mostrar_contenido();
	
	
	
	}	

void mostrar_asistente_obtencion_contrasena(){
	
	/* Función destinada a llamar a las funciones de obtención de contraseña
	 * 
	 * Entradas: Ninguna
	 * Salidas: Ninguna
	 * Restricciones: Ninguna																				*/
	
		obtener_contrasena();
	
	}
	
void mostrar_asistente_borrado_contrasena(){
	
	/* Función destinada a llamar a las funciones encargadas de borrado de contraseña
	 * 
	 * Entradas: Ninguna
	 * Salidas: Ninguna
	 * Restricciones: Ninguna																				*/
	
		borrar_contrasena();
	
	}

void mostrar_asistente_guardado_archivo() {

    guardar_archivo();

}

void mostrar_asistente_cargado_archivo() {

    cargar_archivo();

}
	
	

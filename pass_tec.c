#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "terminal.h"

int main(){
	
	/* Función principal del programa, destinada a capturar comando y redigirirlos a funciones de asistencia
	 * en terminal
	 * 
	 * Entradas: Ninguna
	 * Salidas: Ninguna
	 * Restricciones: Ninguna																				*/
	

	while(1){ // Inicio de ciclo de captura de comando 
		
			char comando[50]; // Declaracion de variable
			
			printf("\n\n============================== [ Administrador de contraseñas PASS-TEC ] ==============================\n\n\n");
			
			printf(">>> Digite la acción que desea realizar: ");
			
			
			fgets(comando, 50, stdin); // Captura de char y la transfiere a variable comando
			
			if(strcmp(comando, "generar_contrasena\n") == 0){ // Caso comando concuerde con generar_contrasena
				
				
				
				mostrar_asistente_generacion_contrasena();

				
			}
			else if(strcmp(comando, "mostrar_contenido\n") == 0){ // Caso comando concuerde con mostrar_contenido
				
				
				mostrar_asistente_contenido();
			
			
			}
			else if(strcmp(comando, "obtener_contrasena\n") == 0){ // Caso comando concuerde con obtener_contrasena
				
				
				mostrar_asistente_obtencion_contrasena();
				
			
			}
			else if(strcmp(comando, "borrar_contrasena\n") == 0){ // Caso comando concuerde con borrar_contrasena
				
				
				mostrar_asistente_borrado_contrasena();
				
			
			}
			else if(strcmp(comando, "guardar_archivo\n") == 0) {

                mostrar_asistente_guardado_archivo();

            }
            else if(strcmp(comando, "cargar_archivo\n") == 0) {

                mostrar_asistente_cargado_archivo();

            }
			else if(strcmp(comando, "ayuda\n") == 0){ // Caso comando concuerde con ayuda
				
				printf("\n\n");
				printf("             | = = = = = = = = = = = = = = = = = A Y U D A = = = = = = = = = = = = = = = = = = = |\n");
				printf("             |                                                                                   |\n");
				printf("             |   generar_contrasena: Generar una nueva contraseña para plataforma.               |\n");
				printf("             |   mostrar_contenido: Imprime en consola contenido de nodos del árbol sin          |\n");
				printf("             |                      incluir contraseña mediante recorrido preorden.              |\n");
				printf("             |   obtener_contrasena: Buscar contraseña en el sistema por medio de identificador  |\n");
				printf("             |   guardar_archivo: Guardar estado de sistema en archivo de texto (.txt)           |\n");
				printf("             |   cargar_archivo: Cargar estado previo del sistema en archivo de texto (.txt)     |\n");
				printf("             |   borrar_contrasena: Borrar contrasena almacenada del sistema.                    |\n");
				printf("             |   ayuda: Imprimir en consola comandos disponibles                                 |\n");
				printf("             |   acerca_de: Imprimir en consola parámetros del programa, curso y desarrolladores |\n");
				printf("             |                                                                                   |\n");
				printf("             | = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = |\n");
				
				
				
			}
			else if(strcmp(comando, "acerca_de\n") == 0){
				
				
				system("clear"); //Limpia la pantalla de terminal
            
				printf("               | = = = = = = = = = = = = = = = = = A B O U T = = = = = = = = = = = = = = = = = |\n");
				printf("               |                                                                               |\n");
				printf("               |                      Administrador de Contraseñas PASS-TEC                    |\n");
				printf("               |                                                                               |\n");
				printf("               |   Administra las contraseñas de las distintas plataformas que tengas.         |\n");
				printf("               |   consultalas y borralas, Puedes elegir el largo de contraseña y si quieres   |\n");
				printf("               |   incluir símbolos y mayúsculas. La contraseña se guarda cifrada para mayor   |\n");
				printf("               |   seguridad                                                                   |\n");
				printf("               |                                                                               |\n");
				printf("               |   Instituto Tecnológico de Costa Rica                                         |\n");
				printf("               |   Estructuras de Datos II Semestre 2018                                       |\n");
				printf("               |   II Proyecto Programado                                                      |\n");
				printf("               |                                                                               |\n");
				printf("               |   Desarrolladores                                                             |\n");
				printf("               |   Natán Fernández de Castro - 2017105774                                      |\n");
				printf("               |   Pablo Venegas Sánchez - 2018083497                                          |\n");
				printf("               | = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = |\n");
			
			
			}
			else if(strcmp(comando, "salir\n") == 0){ // Caso comando concuerde con salir
				
				
				printf("\n\n");
				printf("\t\t\t\t   >>> [ Programa CERRADO ] <<<\n\n");
				break;
				
				
			}
			else{
				
				printf(">>> [ Comando INVÁLIDO ] <<<");
				
				system("clear"); //Limpia la pantalla de terminal
				
			}
			
			printf("\n\n");
		}


	return 0;

}

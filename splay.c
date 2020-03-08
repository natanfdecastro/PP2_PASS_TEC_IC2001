#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "splay.h"



Arbol *nuevoNodo(Info* nuevaInfo){
		
	/* Función encargada de crear un nuevo nodo para el árbol binario, reservar memoria 
	 * y apuntar sus hijos a NULL
	 * 
	 * Entradas: struct tipo Info que contiene la información a acoplar al nuevo nodo en el árbol
	 * Salidas: struct nodo tipo Arbol
	 * Restricciones: Ninguna																		*/
		
		Arbol* nodo  = (Arbol*)malloc(sizeof(Arbol)); // Se reserva memoria para el nuevo nodo
		
		nodo -> info = nuevaInfo; // Se acopla la información al nuevo nodo 
		
		nodo -> izquierda = nodo -> derecha = NULL; // Se apuntan ambos hijos (izquierda, derecha) a NULL
		
		return(nodo); // Se retorna el nodo creado
	
	
	}  

Arbol *rotacionDerecha(Arbol *nodo_rotar){
	
		/* Función encargada rotar un nodo hacia la derecha (ZIG) y retornarlo
		 * 
		 * Entradas: Nodo a rotar
		 * Salidas: Nodo rotado
		 * Restricciones: Ninguna																	 */
	
		//printf("ZIG\n");
	
		Arbol *nodo_rotado = nodo_rotar -> izquierda; // Se inicializa struct Arbol para Nodo Rotado
		
		nodo_rotar -> izquierda = nodo_rotado -> derecha; // Se transfiere los hijos de la derecha del 
														 // nodo antiguo a la izquierda del nodo nuevo
		
		nodo_rotado -> derecha = nodo_rotar; // Se transfiere a la derecha del nuevo nodo el nodo antiguo
		
		return nodo_rotado; // Se retorna el nodo rotado 
	
}

Arbol *rotacionIzquierda(Arbol *nodo_rotar){
	
		/* Función encargada rotar un nodo hacia la izquierda (ZAG) y retornarlo
		 * 
		 * Entradas: Nodo a rotar
		 * Salidas: Nodo rotado
		 * Restricciones: Ninguna																	 */
		
		//printf("ZAG\n");
		
		Arbol *nodo_rotado = nodo_rotar -> derecha; // Se inicializa struct Arbol para Nodo Rotado
		
		nodo_rotar -> derecha = nodo_rotado -> izquierda; // Se transfiere los hijos de la izquierda del 
													     // nodo antiguo a la derecha del nodo nuevo
													     
		nodo_rotado -> izquierda = nodo_rotar; // Se transfiere a la izquierda del nuevo nodo el nodo antiguo
		
		return nodo_rotado; // Se retorna el nodo rotado 

}

Arbol *splay(Arbol *raiz, Info* nuevaInfo){
	
		/* Función encargada de biselar el árbol binario, ya sea, cuando se inserta, se busca o 
		 * se borra un nodo
		 * 
		 * Entradas: Árbol binario y struct con información
		 * Salidas: Árbol biselado
		 * Restricciones: Ninguna																	 */
		
		// Raíz es nula o la información es la misma presente en la raíz se para la recursividad
		if(raiz == NULL || raiz -> info -> identificador == nuevaInfo -> identificador) return raiz;
		
		// Información se encuentra en el subarbol izquierdo
		if( raiz -> info -> identificador > nuevaInfo -> identificador){
				
				// Informacion no esta en el arbol
				if (raiz -> izquierda == NULL) return raiz;
				
				// Zig-Zig (Izquierda - Izquierda)
				if (raiz -> izquierda -> info -> identificador > nuevaInfo -> identificador){
					
						//printf("Zig-Zig\n");	
						// Recursivamente mandamos la información como raiz de izquierda-izquierda
						raiz -> izquierda -> izquierda = splay(raiz -> izquierda -> izquierda, nuevaInfo);
						
						// Se hace la primera rotacion de la raiz, la segunda rotación se hace después
						raiz = rotacionDerecha(raiz);
					
					
				}
				
				//Zag-Zig [Izquierda - Derecha]
				else if (raiz -> izquierda -> info -> identificador < nuevaInfo -> identificador){
					
					//printf("Zag-Zig\n");
					
					// Primero recursivamente se trae la información como raíz de izquierda-derecha
					raiz -> izquierda -> derecha = splay(raiz -> izquierda -> derecha, nuevaInfo);
					
					// Se hace la primera rotacion para raiz -> izquierda
					if (raiz -> izquierda -> derecha != NULL)
					
						raiz -> izquierda = rotacionIzquierda(raiz -> izquierda);
				
				}
				
				// Se hace la segunda rotacion para la raiz 
				return (raiz -> izquierda == NULL)? raiz: rotacionDerecha(raiz);
		
		}
		
		else { // Información se encuentra en el subárbol derecho
			
			// Información no está en el arbol, se termina
			if (raiz -> derecha == NULL) return raiz;
			
			// Zig-Zag (Derecha-Izquierda)
			if (raiz -> derecha -> info -> identificador > nuevaInfo -> identificador){
				
				//printf("\nZIG-ZAG");
				// Se trae la información como raiz de derecha -izquierda
				raiz -> derecha -> izquierda = splay(raiz -> derecha -> izquierda, nuevaInfo);
				
				// Se hace primera rotación de la raíz -> derecha
				if (raiz -> derecha -> izquierda != NULL)
					
					raiz -> derecha = rotacionDerecha(raiz -> derecha);
			
			}
			
			// Zag-Zag (Derecha-Derecha)
			else if (raiz -> derecha -> info -> identificador < nuevaInfo -> identificador){
				
				//printf("Zag-Zag\n");
				
				raiz -> derecha -> derecha = splay(raiz -> derecha -> derecha, nuevaInfo);
				
				raiz = rotacionIzquierda(raiz);
			
			
			}
			
			// Se hace la segunda rotación para la raíz
			return (raiz -> derecha == NULL)? raiz: rotacionIzquierda(raiz);
		
		}

}
	

Arbol *insertar_nodo(Arbol *raiz, Info *nuevaInfo){
	
		/* Función encargada de insertar un nodo nuevo, llama a función crear nodo y se validan casos
		 * de rotación
		 * 
		 * Entradas: Árbol binario y struct con información
		 * Salidas: Nodo insertado
		 * Restricciones: Ninguna																	 */
	
		// Caso árbol vacío
		if (raiz == NULL) return nuevoNodo(nuevaInfo);
			
		// Se trae el nodo hoja más cercana a la raíz
		raiz = splay(raiz, nuevaInfo);
		
		// Caso que la información ya esté presente, la retorna
		if (raiz -> info == nuevaInfo) return raiz;
		
		// Aloca la memoria para un nuevo nodo 
		Arbol *nuevo_nodo = nuevoNodo(nuevaInfo);
		
		// Si el identificador en la raíz es más grande, se hace a la raiz hijo derecho
		// de nuevoNodo y se copia el hijo izquierdo a la raíz de nuevoNodo
		if (raiz -> info -> identificador > nuevaInfo -> identificador){
			
				nuevo_nodo -> derecha = raiz; // Se transfiere la raiz a la derecha de nuevoNodo
				
				nuevo_nodo -> izquierda = raiz -> izquierda; // Se tranfiere a la izquierda de nuevoNodo
															 // la izquierda de la raiz
				
				raiz -> izquierda = NULL; // Se iguala a NULL la izquierda de la raiz
		
		}
		
		else{
			
				nuevo_nodo -> izquierda = raiz;
				
				nuevo_nodo -> derecha = raiz -> derecha;
				
				raiz -> derecha = NULL;
		
		}
	
		return nuevo_nodo;
	
}


Arbol *buscar_contrasena(Arbol *raiz, Info *nuevaInfo){
	
		/* Función encargada de buscar contraseña en un nodo dado del árbol binario, se bisela el árbol.
		 * 
		 * Entradas: Árbol binario y struct con información
		 * Salidas: Árbol biselado y en la raíz el nodo encontrado sea el caso.
		 * Restricciones: Ninguna																	 */
		 
		return splay(raiz, nuevaInfo);
		
	
}

Arbol *borrado_splay(Arbol *raiz, Info *nuevaInfo){
	
		/* Función encargada de borrar contraseña que el usuario haya ingresado
		 * 
		 * Entradas: Árbol binario y struct con información
		 * Salidas: Árbol biselado con contraseña borrada sea el caso que la encuentre
		 * Restricciones: Ninguna																	 */
	
		Arbol *nodo_Borrar; // Se declara struct temp tipo Arbol
		
		if (!raiz) return NULL; // caso que no haya información en el árbol binario
		
		raiz = splay(raiz, nuevaInfo); // Se bisela el árbol y se iguala raíz al resultado 
		
		// Caso que la contraseña no esté presente, retorna la raiz y muestra mensaje de error
		if (nuevaInfo -> identificador != raiz -> info -> identificador){
			
				printf(" Número de identificador de registro INVÁLIDO\n");
				
				return raiz; // Retorna la raíz
				
		}
		
		if (!raiz -> izquierda){ // Caso que la raíz no tenga hijo en la izquierda equivalente a NULL
			
				nodo_Borrar = raiz; // Se copia la información de la raíz al nodo a borrar
				
				raiz = raiz -> derecha; // La raíz va a contener su hijo a la derecha
			
		}
		else{
			
				nodo_Borrar = raiz; // Se copia la información de la raíz al nodo a borrar
				
				raiz = splay(raiz -> izquierda, nuevaInfo); // raiz va a ser el resultado de biselación de su hijo izquierdo
			
				raiz -> derecha = nodo_Borrar -> derecha; // raiz va a contener al hijo que contenía a la derecha al principio
		
		
		}
		
		free(nodo_Borrar); // Se libera en memoria la información, es decir se borra 
		
		return raiz; // Se retorna el árbol


}


void preOrden(Arbol *raiz){
		
		/* Función encargada de recorrer el árbol binario mediante recorrido preorden
		 * 
		 * Entradas: Árbol binario 
		 * Salidas: Impresión del recorrido del árbol
		 * Restricciones: Que el árbol binario contenga información							 */
	
		if (raiz != NULL){ // Validación
			
			printf("\t\t\t====================================================\n");
			printf("\t\t\t Identificador: %d\n", raiz -> info -> identificador);
			printf("\t\t\t Plataforma: %s", raiz -> info -> plataforma);
			printf("\t\t\t Usuario: %s", raiz -> info -> usuario);
			//printf("\t\t\t Usuario: %s", raiz -> info -> texto_cifrado);
			printf("\t\t\t====================================================\n");

			
			preOrden(raiz -> izquierda); // Llamada recursiva a recorrer subárbol izquierdo
			preOrden(raiz -> derecha);	// Llamada recursiva a recorrer subárbol derecho
			
		}
	
}


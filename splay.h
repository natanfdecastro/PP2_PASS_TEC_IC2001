
/* Archivo de encabezado .h destinado a declaraciones de structs además de permisos de acceso a funciones
 * presentes en archivo splay.c 
 * 
 * Entradas: Ninguna
 * Salidas: Ninguna
 * Restricciones: Ninguna																				*/
 
typedef struct nodoArbol{
	
	struct informacion *info;
	struct nodoArbol *derecha;
	struct nodoArbol *izquierda;
	
	
}Arbol;


typedef struct informacion{
	
	int identificador;
	char plataforma[50];
	char usuario[50];
	//Cifrado
	unsigned char texto_cifrado[128];
	int largo_texto_cifrado;
	
}Info;

Arbol *insertar_nodo(Arbol *raiz, Info *nuevaInfo);

Arbol *buscar_contrasena(Arbol *raiz, Info *nuevaInfo);

Arbol *borrado_splay(Arbol *raiz, Info *nuevaInfo);

void preOrden(Arbol *raiz);






	

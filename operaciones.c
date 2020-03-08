#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include "splay.h"
#include "terminal.h"
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

// Declaración de variables globales

Arbol *arbolSplay;

char alfabeto[75];

int identificador = 0;

FILE *archivo;

static void handleErrors(void) { // Función de manejo de errores con respecto a la encripción
	
	  ERR_print_errors_fp(stderr);
	  
	  abort();
  
}


void generar_informacion(unsigned char *texto_cifrado, int largo_texto_cifrado){
	
	
	/* Función destinada a capturar la información requerida en el nodo a crear, acoplarla a struct nuevaInfo 
	 * para luego llamar a función encargada inserción en el árbol
	 * 
	 * Entradas: Char con contraseña generada, entero con largo de contraseña
	 * Salidas: Nodo insertado en arbol con la información ingresada y contraseña generada
	 * Restricciones: Ninguna																				*/
	 
	 char buffer[100];
	
	int c; // Se debe limpiar la línea luego de haber hecho scanf para propósitos de manejo de terminal
	
	/* Limpieza de línea */
	while ((c = getchar()) != '\n' && c != EOF); 
	
	
	Info *nuevaInfo = malloc(sizeof(Info)); // Se aloca memoria para struct tipo Info
	
	// Se captura el char para la plataforma que el usuario desea
	
	printf(">>> Digite la PLATAFORMA asociada a la contraseña: ");
	
	fgets(nuevaInfo -> plataforma, 50, stdin); 
	
	buffer[strcspn(buffer, "\n")] = 0;
	
	 // Se captura el char para el nombre de usuario que el usuario desea
	
	printf(">>> Digite el NOMBRE DE USUARIO para almacenar con la contraseña: ");
	
	fgets(nuevaInfo -> usuario, 50, stdin);
	
	buffer[strcspn(buffer, "\n")] = 0;
	
	// Se copia pass (contraseña generada) a variable contraseña en nuevaInfo 
	
	strcpy(nuevaInfo -> texto_cifrado, texto_cifrado); 
	
	nuevaInfo -> largo_texto_cifrado = largo_texto_cifrado;
	
	// Se aumenta el identificador en uno
	
	identificador++; 
	
	// Se copia el identificador a nuevaInfo
	
	nuevaInfo -> identificador = identificador; 

	
	// Se llama a función inserta nodo y se actualiza arbol binario 
	
	arbolSplay = insertar_nodo(arbolSplay, nuevaInfo); 
	
	system("clear"); //Limpia la pantalla de terminal
	
	printf("\n\t\t\t  >>> [ Contraseña GENERADA y ALMACENADA con Éxito ] <<<\n");
	

}

static void desencriptar(unsigned char *texto_cifrado, int largo_texto_cifrado) {
	
	/* Función destinada a recibir el texto cifrado y el largo de texto cifrado dentro
	 * encriptarlo mediante del nodo encontrado dentro de árbol splay para obtener contraseña 
	 * utiliza librería de encripción-desencripción de OpenSSL, utiliza encripción simétrica AES 
	 * 
	 * Entradas: unsigned char texto_cifrado y entero largo_texto_cifrado
	 * Salidas: Impresión String texto descifrado
	 * Restricciones: Ninguna																				*/
		
	/* Llave 256 bit*/
	unsigned char *key = (unsigned char *)"01234567890123456789012345678901";
	
	/* Vector Inicialización 128 bit */
	unsigned char *iv = (unsigned char *)"0123456789012345";
	
	/* char sin signo  para almacenar texto se le da tamaño de 128 ya que puede tomar valores grandes*/
	unsigned char plaintext[128];
	
	EVP_CIPHER_CTX *ctx;
	
	int len;
	
	int plaintext_len;
	
	/* Create and initialise the context */
	if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();
	
	/* Se inicializa la operación de desencripción. Tomar en cuenta tamaño de llave y VI son apropiados 
	 * para el cifrado */
	if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
	handleErrors();
	
	/* Se provee el mensaje a ser descriptado, en este caso el texto cifrado. Se obtiene la salida 
	 * del texto plano. */
	if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, texto_cifrado, largo_texto_cifrado))
	handleErrors();
	plaintext_len = len;
	
	/* Se finaliza la desencripción. Se escriben bytes siguientes en el texto plano */
	if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) handleErrors();
	plaintext_len += len;
	
	/* Se libera */
	EVP_CIPHER_CTX_free(ctx);
	
	/* Se limpia el final de línea del texto plano desencriptado (basura) */
	plaintext[plaintext_len] = '\0';
	
	/* Se mustra el texto desencriptado, la contraseña como tal */
	printf("\t\t\t  ====================================================\n");
	printf("\t\t\t   Contraseña Generada: %s\n", plaintext);
	printf("\t\t\t  ====================================================\n");	
		  
}

static void encriptar(char *pass){
	
	/* Función destinada a recibir el char generado para contraseña y encriptarlo mediante
	 * librería de encripción-desencripción de OpenSSL, utiliza encripción simétrica AES 
	 * 
	 * Entradas: Char con contraseña generada
	 * Salidas: Unsigned char de texto cifrado y el largo del texto cifrado
	 * Restricciones: Ninguna																				*/
	
	/* Llave 256 bit*/
	unsigned char *key = (unsigned char *)"01234567890123456789012345678901";
	
	/* Vector Inicialización 128 bit */
	unsigned char *iv = (unsigned char *)"0123456789012345";
	
	unsigned char texto_cifrado[128];
	
	/* Contraseña para ser encriptada, se maneja como texto_plano */
	char *plaintext = NULL;	
	
	plaintext = (char*)calloc(126, sizeof(char));
	
	strcpy(plaintext, pass);
	
	//printf("Texto a cifrar: %s\n", plaintext);
	
	int plaintext_len = strlen ((char *)plaintext);
	
	EVP_CIPHER_CTX *ctx;
	
	int len;
	
	int largo_texto_cifrado;
	
	/* Se inicializa la operación de encripción */
	if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();
	
	/* Tomar en cuenta tamaño de llave y VI son apropiados 
	 * para el cifrado  */
	if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
	handleErrors();
	
	/* Se provee el texto a ser encriptado, y se obtiene la encripción como salida */
	if(1 != EVP_EncryptUpdate(ctx, texto_cifrado, &len, plaintext, plaintext_len))
	handleErrors();
	
	largo_texto_cifrado = len;
	
	/* Se finaliza la encripción. */
	if(1 != EVP_EncryptFinal_ex(ctx, texto_cifrado + len, &len)) handleErrors();
	largo_texto_cifrado += len;
	
	/* Se libera */
	EVP_CIPHER_CTX_free(ctx);
	
	/* Se imprime el encriptado */
	//printf("Ciphertext is:\n");
	//BIO_dump_fp (stdout, (const char *)texto_cifrado, largo_texto_cifrado);
	
	/* Llamada a función de generación de información */
	generar_informacion(texto_cifrado, largo_texto_cifrado);
	  
}


static void crear_alfabeto(){
	
	/* Función destinada a generar el alfabeto dependiendo de los casos que el usuario desee la contraseña
	 * con mayúsculas, símbolos o no lo desee. El alfabeto se crea para cifrar la contraseña posteriormente.
	 * 
	 * Entradas: Ninguna
	 * Salidas: Alfabeto con arreglo de caracteres
	 * Restricciones: Ingresar opciones correctamente Si | No																				*/
	
	
	// Declaracion de variables
	char incluir_mayusculas[10];
	char incluir_simbolos[10];

	
	printf(">>> Incluir mayúsculas Si | No: "); // Se captura la opcion de anadir mayusculas o no
	
	fgets(incluir_mayusculas, 10, stdin); 
	
	printf(">>> Incluir símbolos Si | No: "); // Se captura la opcion de anadir simbolos o no
	
	fgets(incluir_simbolos, 10, stdin);
	
	
	/*------------------ Caso Ninguno ------------------*/
	
	if(strcmp(incluir_mayusculas, "No\n") == 0 && strcmp(incluir_simbolos, "No\n") == 0){
		
		
		char lower[50];
		
		strcpy(lower, "abcdefghijklmnopqrstuvwxyz0123456789");
		
		
		
		
		//printf("%s\n", lower);
		
		
		memcpy(alfabeto, lower, sizeof(alfabeto));	
				
	}
	
	/*------------------ Caso Simbolos -------------------*/
	
	else if(strcmp(incluir_mayusculas, "No\n") == 0 && strcmp(incluir_simbolos, "Si\n") == 0){
		
		char lower_simbol[75];       // Arreglo con alfabeto de minusculas y simbolos

		strcpy(lower_simbol, "abcdefghijklmnopqrstuvwxyz0123456789@#$%&*");
		
		memcpy(alfabeto, lower_simbol, sizeof(alfabeto));
	
	}
	
	/*------------------ Caso Mayusculas ------------------*/
	
	else if(strcmp(incluir_mayusculas, "Si\n") == 0 && strcmp(incluir_simbolos, "No\n") == 0){
		
		char upper_lower[75]; // Arreglo con alfabeto de mayusculas y minusculas

		strcpy(upper_lower, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
		//printf("%s\n", upper_lower);
		
		memcpy(alfabeto, upper_lower, sizeof(alfabeto));
		
	}
	
	/*------------------ Caso Mayusculas & Simbolos -----------------*/
	
	else if(strcmp(incluir_mayusculas, "Si\n") == 0 && strcmp(incluir_simbolos, "Si\n") == 0){
		
		
		// Arreglo con alfabeto de mayusculas, minusculas y simbolos
		char upper_lower_simbol[75]; 
		
		strcpy(upper_lower_simbol, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789@#$%&*");

		
		//printf("%s\n", upper_lower_simbol);
			
		memcpy(alfabeto, upper_lower_simbol, sizeof(alfabeto));
	
    }
    	
    else { 
	
		printf(" =====>>>> Opción INVÁLIDA: Digite correctamente las opciones <<<<=====\n");
		crear_alfabeto();
	
	
	}
    		
    	
	//printf("Alfabeto a utilizar: %s\n", alfabeto);
		
}


void generar_contrasena(){
	
	/* Función destinada a generar la contraseña como tal, le solicita al usuario el largo de contraseña 
	 * que desea 
	 * 
	 * Entradas: Ninguna
	 * Salidas: Contraseña y alfabeto generado
	 * Restricciones: Ninguna																				*/
	
	crear_alfabeto(); // Llamada a función crear alfabeto
	
	// Declaración de variables
	int largo_contrasena; 
	int aleatorio;
	
	printf(">>> Digite el LARGO de contraseña que desea: ");
	
	scanf("%d", &largo_contrasena); // Se captura el entero para largo de contraseña
	
	char pass[largo_contrasena];
	char temp[5];
	
	strcpy(temp, ""); // Se limpian las variables antes de utilizarlas
	strcpy(pass, "");
	
	srand(time(NULL));   
		
	for(int i = 0; i < largo_contrasena; i ++){ // Se itera sobre le el arreglo alfabeto
			

		aleatorio = rand() % (strlen(alfabeto)) + 0; // Se guarda número aleatorio generado en variable aleatorio    
		
		strncpy(temp, &alfabeto[aleatorio], 1);	// Se copia el caracter en la posicion del número aleatorio en temp
		temp[strlen(temp) - 2] = '\0'; // Se limpia la variable temp
		
		
		strcat(pass, temp);	// Se concatena variables temp y pass
	 
	}
	
	encriptar(pass); // Llamada a función encriptar
	
}

void mostrar_contenido(){
	
	/* Función destinada a llamada de recorrido preorden para el árbol binario
	 * 
	 * Entradas: Ninguna
	 * Salidas: Ninguna
	 * Restricciones: Ninguna 									    		*/
	 
		system("clear"); //Limpia la pantalla de terminal
	
		preOrden(arbolSplay); // Llamada a recorrido preorden del árbol binario
	
}

void obtener_contrasena(){
	
	/* Función destinada mostrar la contraseña almacenada en el nodo junto con la plataforma y el usuario
	 * 
	 * Entradas: Ninguna
	 * Salidas: Contraseña mostrada y biselación del árbol
	 * Restricciones: Ingresar identificador presente en el árbol							    		*/
	
	int comparador_identificador; // Declaración de entero
	
	Info *nuevaInfo = malloc(sizeof(Info)); // Se aloca memoria para struct tipo Info
	
	printf(">>> Digite el IDENTIFICADOR de la contraseña que desea obtener: ");
	
	scanf("%d", &comparador_identificador); // Se captura el identificador que el usuario desea
	
	nuevaInfo -> identificador = comparador_identificador; // Se copia al struct tipo Info el identificador que se desea
	
	int c; // Se debe limpiar la línea luego de haber hecho scanf para propósitos de manejo de terminal
	
	/* Limpieza de línea */
	while ((c = getchar()) != '\n' && c != EOF); 
	
	arbolSplay = buscar_contrasena(arbolSplay, nuevaInfo); // Llamada a función buscar_contraseña y se actualiza el árbol binario
	
	// Se imprime el resultado de la búsqueda
	
	system("clear"); //Limpia la pantalla de terminal
	
	printf("\t\t\t---------------------------------------------------------\n");
	printf("\t\t\t  Plataforma: %s", arbolSplay -> info -> plataforma);
	printf("\t\t\t---------------------------------------------------------\n");
	printf("\t\t\t  Usuario: %s", arbolSplay -> info -> usuario);
	printf("\t\t\t---------------------------------------------------------\n");
	printf("\t\t\t  Identificador: %d\n", arbolSplay -> info -> identificador);
	printf("\t\t\t---------------------------------------------------------\n"); 
	printf("\n");
	
	// Se llama a desencriptar el contenido cifrado para mostrar la contraseña
	
	desencriptar(arbolSplay -> info -> texto_cifrado, arbolSplay -> info -> largo_texto_cifrado);
	



	
}

void borrar_contrasena(){
	
	/* Función destinada mostrar la contraseña almacenada en el nodo junto con la plataforma y el usuario
	 * 
	 * Entradas: Ninguna
	 * Salidas: Contraseña borrada junto con su información y biselación del árbol
	 * Restricciones: Ingresar identificador presente en el árbol							    		*/
	
	// Declaración de variable
	int comparador_identificador;
	
	Info *nuevaInfo = malloc(sizeof(Info)); // Se reserva memoria para struct tipo Info
	
	printf(">>> Digite el IDENTIFICADOR de la contraseña que desea borrar: ");
	
	scanf("%d", &comparador_identificador); // Se captura el identificador que ingresa el usuario
	
	nuevaInfo -> identificador = comparador_identificador; // Se copia a struct nuevaInfo
	
	int c; // Se debe limpiar la línea luego de haber hecho scanf para propósitos de manejo de terminal
	
	/* Limpieza de línea */
	while ((c = getchar()) != '\n' && c != EOF); 
	
	arbolSplay = borrado_splay(arbolSplay, nuevaInfo); // Se llama a la función de borrado de la contraseña 
													   // y se actualiza el árbol
	system("clear"); //Limpia la pantalla de terminal
	
	printf("\n\t\t\t      >>> [ Contraseña BORRADA con Éxito ] <<<\n");
	

}

void guardar_info(Arbol *raiz) {
	
    if(raiz != NULL) {
        
        fprintf(archivo, "%d", raiz -> info -> identificador);
        fputs("||", archivo);
        fputs(raiz -> info -> plataforma, archivo);
        fputs("||", archivo);
        fputs(raiz -> info -> usuario, archivo);
        fputs("||", archivo);
        fputs(raiz -> info -> texto_cifrado, archivo);
        fputs("||", archivo);
        fprintf(archivo, "%d", raiz -> info -> largo_texto_cifrado);
        fputs("||", archivo);

        guardar_info(raiz -> izquierda);
        guardar_info(raiz -> derecha);
        
    }
    
}

void guardar_archivo() {

    archivo = fopen("arbol.txt", "w+");
    if(archivo == NULL) {
        printf("Se ha producido un error al crear el archivo, porfavor intentelo de nuevo");
    }
    else {
        guardar_info(arbolSplay);
        fputs("END", archivo);
        printf("El archivo \"arbol.txt\" ha sido creado con exito");
        fclose(archivo);
    }

}

void cargar_archivo() {
	
    archivo = fopen("arbol.txt", "r");
    
    if(archivo == NULL) {
		
        printf("Se ha producido un error al cargar el archivo, porfavor intentelo de nuevo");
        
    }
    else {
		
        int identificador;
	    char plataforma[50];
	    char usuario[50];
	    unsigned char texto_cifrado[128];
        int largo_texto_cifrado;

        char str_identificador[5];
        char str_largo_texto_cifrado[5];

        char linea[400];
        char *ptr;
        
        fgets(linea, 400, archivo);
        
        while(strcmp(linea, "END") != 0) {

            ptr = strtok(linea,"||");
            strcpy(str_identificador, ptr);
            identificador = atoi(str_identificador);

            ptr = strtok(NULL,"||");
            strcpy(plataforma, ptr);

            ptr = strtok(NULL,"||");
            strcpy(usuario, ptr);

            ptr = strtok(NULL,"||");
            strcpy(texto_cifrado, ptr);

            ptr = strtok(NULL,"||");
            strcpy(str_largo_texto_cifrado, ptr);
            largo_texto_cifrado = atoi(str_largo_texto_cifrado);

            //Prints para debugear
            printf("%d\n", identificador);
            printf("%s\n", plataforma);
            printf("%s\n", usuario);
            printf("%s\n", alfabeto);

            //Reset
            strcpy(linea, "");
            ptr = NULL;

            strcpy(str_identificador, "");
            strcpy(plataforma, "");
	        strcpy(usuario, "");
            strcpy(alfabeto, "");

            fgets(linea, 400, archivo);
            
        }
        
        fclose(archivo);
        
    }
}




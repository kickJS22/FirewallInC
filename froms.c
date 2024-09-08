#include <stdio.h> //Para las func normales de c
#include <sys/socket.h> // Para las func del socket
#include <netinet/in.h> // Para el manejo de puertos y direcciones
#include <string.h> //Para crear cadenas mas facilmente
#include <stdlib.h> //Para manejar algunos errores
		    
int main(){
	int serverFileDes, socket;
	// struct Tipo de dato que funciona como un objeto o grupo de variables que estan relacionadas de alguna forma, se define la estructura y despues una variable dentro de programa que va a contener esa estructura adentro https://www.w3schools.com/c/c_structs.php
	
	// En este caso socketaddr_in define una serie de variables que a las cuales vamos a acceder y modificar a traves de address
	struct sockaddr_in address;

	//Socket option	
	int opt = 1;

	//Length of address
	int addrlen = sizeof(address);

	//Creamos el file descriptor del socket, traduce las operaciones que realizamos para transmitirlas al socket
	//Le asignamos al server el valor del socket con esos parametros y si es igual a 0 quiere decir que el socket no se inicio
	//int socket(int domain, int type, int protocol)
	//domain: AF_INET, para comunicaciones con ipv4
	//type: SOCK_STREAM, para usar TCP
	//protocol: para usar Internet Protocol, IP
	//https://www.geeksforgeeks.org/socket-programming-cc/
	if((serverFileDes = socket(AF_INET, SOCK_STREAM, 0)) == 0){
		perror("El socket fallo");
		exit(EXIT_FAILURE)
	}

//setsockopt(int socket, int level, int option_name, const void *option_value, socklen_t option_length); sirve para setear opciones en el socket, aca comprobamos que no esten estas opciones especificas usandose
	//socket:serverFileDes, nuestro servidor para el file descriptor
	//level: SOL_SOCKET, para manejar ipv4
	//option_name: SO_REUSEADDR | SO_REUSEPORT, para reutilizar el address o el puerto, se una en un caso de usar bind para hacer mas de una peticion antes de cerrar la conexion
	//const void *option_value: con el &opt le pasamos la direccion en memoria de la variable, el * significa que definimos una variable de la cual no tenemos el tamaño antes, por eso despues le pasamos el tamaño real que tiene en la siguiente opcion
	//socklen_t option_length: sizeof(opt) le pasamos el valor que finalmente tiene la variable
	if(setsockopt(serverFileDes,SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		perror("Fallo al setar la opcion del socket");
		close(serverFileDes);
		exit(EXIT_FAILURE);
	}


	
	// Usamos las variable definidas en el struct antes
/* struct sockaddr_in {
    	 short            sin_family;   // e.g. AF_INET
    	 unsigned short   sin_port;     // e.g. htons(3490)
    	 struct in_addr   sin_addr;     // see struct in_addr, below
    	 char             sin_zero[8];  // zero this if you want to	
	};*/
	// family: ipv4 con AF_INET
	//sin_addr es otra estructura a su vez, el parametro INADDR_ANY lo que hace el unir la direccion a cualquier interfaz, ya sea localhost en el 127.0.0.0 o cualquier otra
	//sin_port, asigna a ese puerto nuestro servidor, con el htons convierte los bytes del int a su direccion que entienda la red(network)
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(8080);

	//Unimos el socket al puerto 8080 forzadamente
	//int bind(int socket, const struct sockaddr *address, socklen_t address_len);
	//socket: serverFileDes
	//const struct sockaddr, 
	//struct sockaddr {
        //  sa_family_t sa_family;
        //       char        sa_data[14];
        //}
	//designamos una variable que va a contener las variables de la estructura sockaddr, la cual con * especificamos que no conocemos el temaño que va a tener, y con & referenciamos el lugar que va a ocupar la variable
	//addrlen: sizeof(address), le pasamos el tamaño de la variable creada
	if(bind(serverFileDes, (struct sockaddr *)&address, sizeof(address) < 0)) {
		perror("No se puedo bindear el puerto");
		close(serverFileDes);
		exit(EXIT_FAILURE)
	}











	//Definimos un array buffer en el cual incializamos todos los elementos a 0, se usa para definir la cantidad de bytes que vamos a leer de un archivo
	char buffer[1024] = {0};
	//Genera un bucle infinito pq 1 siempre va a ser verdadero, 1 = True, 0 = False. seria lo mismo que pone while(True)
	while(1) {
	}


}

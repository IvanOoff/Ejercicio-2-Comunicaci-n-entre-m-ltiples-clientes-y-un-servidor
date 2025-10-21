#include "utils.h"
#include <iostream>
#include <string>
#include <thread>
#include <list>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

using namespace std;

// Funcion que recibirÃ¡ los mensajes.
void manejarCliente(int socket_C, int id) {

	// Varibles.
        char buffer[1024];
        bool activeClient = true;

        while(activeClient) {
                int mensajes_R = recv(socket_C, buffer, sizeof(buffer), 0);

        // Comprobamos que no se desconectÃ³ el cliente.
        if(mensajes_R <= 0){
                cout << "CLIENTE DESCONECTADO"<<endl;
                activeClient = false;
                break;
        }

        cout<<id <<". "<<buffer<<endl;
        string resp = "Servidor: mensaje recibido correspondiente de cliente" + to_string(id);
        send(socket_C, resp.c_str(), resp.length(), 0);

        }
        close(socket_C);
}

int main(int argc, char** argv)
{

const int clientes_max = 5;
const int puerto = 5000;
int clientesCont = 0;

vector<thread> clientesHilos;
int sockk = socket(AF_INET, SOCK_STREAM, 0);

struct sockaddr_in server_direction;
server_direction.sin_family = AF_INET;
server_direction.sin_addr.s_addr = INADDR_ANY;
server_direction.sin_port = htons(puerto);

// Bind
if(bind(sockk,(struct sockaddr*)&server_direction, sizeof(server_direction)) < 0) {
	cerr <<"ERROR!"<<endl;
	close(sockk);
	return 1;
}

cout << "Conexion exitosa en el puerto: " << puerto<< endl;

// Llamamos a listen.
if(listen(sockk, 10) < 0){
	cerr <<"ERROR"<<endl;
	close(sockk);
	return 1;
}
cout<<"Servidor escuchando en el puerto 5000"<<endl;


for(int k = 0; k < clientes_max;k++){

struct sockaddr_in client_direction;
socklen_t client_tam = sizeof(client_direction);

int socket_C = accept(sockk, (struct sockaddr*)&client_direction, &client_tam);

cout<<"Conexion exitosa!"<<endl;

if(socket_C < 0) {
	cerr<<"ERROR"<<endl;
}

clientesCont++;

thread hiloCliente(manejarCliente, socket_C, clientesCont);
clientesHilos.push_back(move(hiloCliente));
}

// JOIN
for(auto& hiloCliente : clientesHilos){
	if(hiloCliente.joinable()){
		hiloCliente.join();
	}

}

close(sockk);

cout<<"FIN"<<endl;
return 0;

}

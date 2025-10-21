#include "utils.h"
#include <string>
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

int main(int argc,char** argv)
{

// Creamos el socket.
int sockkt = socket(AF_INET,SOCK_STREAM,0);

// Definimos la direccion IP y el puerto.
const int puerto = 5000;
const char* ip = "127.0.0.1";
//const char* m = "oli";
bool active = true;

// Antes de mandar el mensaje, conectamos con el servidor.
struct sockaddr_in addr_S;
addr_S.sin_family = AF_INET;
addr_S.sin_port = htons(puerto);
inet_pton(AF_INET, ip, &addr_S.sin_addr);

if(connect (sockkt, (struct sockaddr*)&addr_S, sizeof(addr_S)) < 0){
	cerr << "ERROR" <<endl;
	close(sockkt);
	return 1;
}


while(active){
// Cojemos ele mensaje del usuario.
string user_m;

// Lo pedimos por terminal.
cout<<"Introduce un mensaje para el servidor: ";
getline(cin, user_m);

if(user_m == "exit"){
	cout<<"EXIT...."<<endl;
	break;
}

// Mandamos el mensaje
send(sockkt, user_m.c_str(), user_m.length(), 0);
cout<<"Mensaje enviado desde cliente: " << user_m<<endl;

// Recibimos la repuesta con recv.
char buffer[1024];
int mensaje_recibido = recv(sockkt, buffer, sizeof(buffer), 0);

if(mensaje_recibido > 0) {
	cout << "Servidor dice: " << buffer << endl;

}
}
close(sockkt);
return 0;
}

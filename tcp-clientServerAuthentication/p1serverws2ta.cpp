// the server process

#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <map>
#include <string>
using namespace std;

#define BUFLENGTH 512
#define PORT 8888

int main() {

	WSADATA wsa;
	SOCKET s, sio; // sockets for the server and the connected session
	int len;
	int slen;
	char buffer[BUFLENGTH];
	char message[BUFLENGTH];
	struct sockaddr_in server, sio_other; // structures for the server and the client
	map<string, string> inputValidation;


	slen = sizeof(sio_other);
	WSAStartup(MAKEWORD(2, 2), &wsa);
    s = socket(AF_INET, SOCK_STREAM, 0);
	memset((char *)&sio_other, 0, slen);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	bind(s, (struct sockaddr *) &server, sizeof(server));

	listen(s, 1); // listen to an incoming request from the client

	sio = accept(s, (struct sockaddr *) &sio_other, &slen); // accpet the incoming request

	
	inputValidation["Alice"] = "aaaaaaaaaa";
	inputValidation["Bob"] = "bbbbbbbbb";
	inputValidation["Cindy"] = "cccccccccc";
	inputValidation["David"] = "ddddddddd";
	inputValidation["Eve"] = "eeeeeeeeee";
	inputValidation["Frank"] = "ffffffffff";
	inputValidation["George"] = "gggggggggg";
	
	
	for (;;) {
		
			string username;
			string password;
			printf("Waiting for data ...\n");
			fflush(stdout);
			while (1){
			memset(buffer, '\0', BUFLENGTH);

			len = recv(sio, (char *)&buffer, BUFLENGTH, 0);

			//printf("message received: ");
			printf("username received: ");
			puts(buffer);
			send(sio, buffer, len, 0);
			username = string(buffer);

			memset(buffer, '\0', BUFLENGTH);
			len = recv(sio, (char *)&buffer, BUFLENGTH, 0);
			printf("password received: ");
			puts(buffer);
			send(sio, buffer, len, 0);
			password = string(buffer);

			if (inputValidation.count(username) != 0 && inputValidation[username] == password){

				memset(buffer, '\0', BUFLENGTH);
				//len = recv(sio, (char *)&buffer, BUFLENGTH, 0);
				string s = "Success!";
				for (int i = 0; i < s.length(); i++){
					buffer[i] = s[i];
				}


				puts(buffer);
		
				send(sio, buffer, BUFLENGTH, 0);
				

			}
			else {
				memset(buffer, '\0', BUFLENGTH);
			
				string s = "Failed!";
				for (int i = 0; i < s.length(); i++){
					buffer[i] = s[i];

				}
			
				puts(buffer);

				send(sio, buffer, BUFLENGTH, 0);

			}
			shutdown(sio, 2);
			closesocket(sio);
		}
		
	}

	shutdown(sio, 2);
	closesocket(sio);
	WSACleanup();

	return 0;
}
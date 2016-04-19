// the server process

#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <map>
#include <string>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <assert.h>
using namespace std;

#define BUFLENGTH 512
#define PORT 8888

int main() {


	map<string, string> inputValidation;

	
	
	inputValidation["Alice"] = "aaaaaaaaaa";
	inputValidation["Bob"] = "bbbbbbbbb";
	inputValidation["Cindy"] = "cccccccccc";
	inputValidation["David"] = "ddddddddd";
	inputValidation["Eve"] = "eeeeeeeeee";
	inputValidation["Frank"] = "ffffffffff";
	inputValidation["George"] = "gggggggggg";
	
	
	for (;;) {
		WSADATA wsa;
		SOCKET s, sio; 
		int len;
		int slen;
		char buffer[BUFLENGTH];
		char message[BUFLENGTH];
		struct sockaddr_in server, sio_other;
		


		slen = sizeof(sio_other);
		WSAStartup(MAKEWORD(2, 2), &wsa);
		s = socket(AF_INET, SOCK_STREAM, 0);
		memset((char *)&sio_other, 0, slen);
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = INADDR_ANY;
		server.sin_port = htons(PORT);

		bind(s, (struct sockaddr *) &server, sizeof(server));

		listen(s, 1); 

		sio = accept(s, (struct sockaddr *) &sio_other, &slen); 
		
			string username;
			string password;
			printf("Waiting for data ...\n");
			printf("220 service ready for new user \n");
			fflush(stdout);
			memset(buffer, '\0', BUFLENGTH);
			len = recv(sio, (char *)&buffer, BUFLENGTH, 0);
			printf("username received: ");
			puts(buffer);
			username = string(buffer);
		
			
		   string st = "331 user name OK";
			for (int i = 0; i < st.length(); i++){
				buffer[i] = st[i];
			}
			puts(buffer);
			send(sio, buffer, BUFLENGTH, 0);
		

			memset(buffer, '\0', BUFLENGTH);
			len = recv(sio, (char *)&buffer, BUFLENGTH, 0);
			printf("password received: ");
			puts(buffer);
			password = string(buffer);
	


			if (inputValidation.count(username) != 0 && inputValidation[username] == password){

				memset(buffer, '\0', BUFLENGTH);
			
				string stIII = " 230 user login OK";
				for (int i = 0; i < stIII.length(); i++){
					buffer[i] = stIII[i];
				}


				puts(buffer);

				send(sio, buffer, BUFLENGTH, 0);

		
				len = recv(sio, (char *)&buffer, BUFLENGTH, 0);
				printf("port received: ");
				puts(buffer);
				memset(buffer, '\0', BUFLENGTH);
			
				string stIV = "225 data connection ready";
				for (int i = 0; i < stIV.length(); i++){
					buffer[i] = stIV[i];
				}
				puts(buffer);
				send(sio, buffer, BUFLENGTH, 0);




				//

				
				//memset(buffer, '\0', BUFLENGTH);
				len = recv(sio, (char *)&buffer, BUFLENGTH, 0);
				
				char pathSrc[BUFLENGTH];
				int pLen;
				for (pLen = 0; pLen < len; pLen++){
					pathSrc[pLen] = buffer[pLen];
				}
				recv(sio, (char *)&buffer, BUFLENGTH, 0);
				recv(sio, (char *)&buffer, BUFLENGTH, 0);
			






				FILE *fp;
				while (1){
					recv(sio, (char *)&buffer, BUFLENGTH, 0);
					if (buffer != "done"){
						break;
					}
				
				}
				
				fp = fopen(pathSrc, "w");
				fwrite(buffer, strlen(buffer), 1, fp);
				fclose(fp);
				

			
				char byte[BUFLENGTH];
			    string stVI = "All bytes were received ";
				for (int i = 0; i < stVI.length(); i++){
					byte[i] = stVI[i];
				}
				send(sio, byte, BUFLENGTH, 0);
				

				printf("the file was received successfully \n");
				break;

			}
			else {
				memset(buffer, '\0', BUFLENGTH);
			
				string stIII = "Failed! Wrong username or password. Please re-enter your username and password";
				int length = stIII.length();
				for (int i = 0; i < length; i++){
					buffer[i] = stIII[i];

				}
			
				puts(buffer);

				send(sio, buffer, length, 0);
				

			}
			



		
			shutdown(sio, 2);
			closesocket(sio);
			WSACleanup();
			fflush(stdout);
		
	}
	
	
	
	return 0;
}
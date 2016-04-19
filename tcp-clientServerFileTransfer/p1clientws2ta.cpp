// the client process

#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <map>
#include <string>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <assert.h>
#include <setjmp.h>
#include <windows.h>
#include <fstream>

#define TRY do{ jmp_buf ex_buf__; if( !setjmp(ex_buf__) ){
#define CATCH } else {
#define ETRY } }while(0)
#define THROW longjmp(ex_buf__, 1)
using namespace std;

#define SERVER "127.0.0.1"
#define BUFLENGTH 512
#define PORT 8888


int main() {

	for (;;) {
	
		WSADATA wsa;
		struct sockaddr_in si_other;
		int slen = sizeof(si_other);
		int s;
		int len;

		char username[BUFLENGTH];
		char password[BUFLENGTH];
		char portNumber[BUFLENGTH];
		char fileType[BUFLENGTH];
		char pathSrc[BUFLENGTH];
		char pathDest[BUFLENGTH];
		char buffer[BUFLENGTH];

		WSAStartup(MAKEWORD(2, 2), &wsa);

		s = socket(AF_INET, SOCK_STREAM, 0);

		memset((char *)&si_other, 0, slen);

		si_other.sin_family = AF_INET;
		si_other.sin_addr.s_addr = inet_addr(SERVER);
		si_other.sin_port = htons(PORT);

		connect(s, (struct sockaddr *) &si_other, slen);



		printf("Enter a username: ");
		gets_s(username);

		send(s, username, strlen(username), 0); 

		recv(s, (char *)&buffer, BUFLENGTH, 0);

	
		puts(buffer); 
		

	
		printf("Enter a password: ");
		gets_s(password);
		send(s, password, strlen(password), 0);






		recv(s, (char *)&buffer, BUFLENGTH, 0);
		printf("");
		puts(buffer);
		string check = (string)buffer;
		if (check != "Failed! Wrong username or password. Please re-enter your username and password"){
			printf("Enter the port number: ");
			gets_s(portNumber);

			
			send(s, portNumber, strlen(password), 0);

			memset(buffer, '\0', BUFLENGTH);
			recv(s, (char *)&buffer, BUFLENGTH, 0);
			printf("");
			puts(buffer);
			memset(buffer, '\0', BUFLENGTH);
		
			FILE *fp;
			int n = 2;
			do {
				TRY{

				    printf("Enter a source path: ");
					gets_s(pathSrc);
					fp = fopen(pathSrc, "r");
				

					if (fp == NULL){
					
						THROW;
						
					}
					
					n = 3;
					
					
			}
				CATCH{
					printf("Your file path is wrong. Please enter a valid path. (such as C:/xx/../hi.txt) \n ");
				}
				ETRY;
			
			} while (n < 3);

			FILE *fi;

			int m = 2;
			do {
				TRY{

				printf("Enter a destination path: ");
				gets_s(pathDest);
				const char *path = pathDest;
				ofstream file(path);
				fi = fopen(path, "r");


				if (fi == NULL){

					THROW;

				}

				m = 3;
				send(s, pathDest, BUFLENGTH, 0);

			}
				CATCH{
					printf("Your file path is wrong. Please enter a valid path. (such as C:/xx/../hi.txt) \n ");
				}
				ETRY;

			} while (m < 3);




			printf("Please enter the file type: ");
			gets_s(fileType);


			send(s, fileType, strlen(fileType), 0);
			char ready[BUFLENGTH];
			string stV = "File transfer ready";
			for (int i = 0; i < stV.length(); i++){
				ready[i] = stV[i];
			}
			puts(ready);

			send(s, ready, BUFLENGTH, 0);
			
			while (!feof(fp)){
				fread(buffer, BUFLENGTH, 1, fp);
				send(s, buffer, sizeof(buffer), 0);
			
			}
			send(s, "done", BUFLENGTH, 0);
			fclose(fp);

			memset(buffer, '\0', BUFLENGTH); 
			recv(s, (char *)&buffer, BUFLENGTH, 0);
			puts(buffer);
			printf("the file was sent successfully\n");
			printf("226 closing data connection. Server has also been closed. Please start a new server process! \n");
			printf("220 service ready for new user");
			break;
			//

		}

		
		
		
		shutdown(s, 2);
		closesocket(s);
		WSACleanup();
	
		
	}

	
	exit(0);
}
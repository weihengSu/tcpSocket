// the client process

#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <map>
using namespace std;

#define SERVER "127.0.0.1"
#define BUFLENGTH 512
#define PORT 8888

int main() {

	WSADATA wsa;
	struct sockaddr_in si_other;
	int slen = sizeof(si_other);
	int s;
	int len;
	//char message[BUFLENGTH];
	char username[BUFLENGTH];
	char password[BUFLENGTH];
	char buffer[BUFLENGTH];





	WSAStartup(MAKEWORD(2, 2), &wsa);

	s = socket(AF_INET, SOCK_STREAM, 0);

	memset((char *)&si_other, 0, slen);

	si_other.sin_family = AF_INET;
	si_other.sin_addr.s_addr = inet_addr(SERVER);
	si_other.sin_port = htons(PORT);

	connect(s, (struct sockaddr *) &si_other, slen); // make a connection to the server

	for (;;) {
	
		printf("Enter a username: ");
		gets_s(username);

		send(s, username, strlen(username), 0); // send a message to the server

		memset(buffer, '\0', BUFLENGTH);
		recv(s, (char *)&buffer, BUFLENGTH, 0); // receive a message from the server

		printf("Echo username received: ");
		puts(buffer);


	
		printf("Enter a password: ");
		gets_s(password);
		send(s, password, strlen(password), 0);
		memset(buffer, '\0', BUFLENGTH);
		recv(s, (char *)&buffer, BUFLENGTH, 0);
		printf("Echo password received: ");
		puts(buffer);

		recv(s, (char *)&buffer, BUFLENGTH, 0);
		printf("Authentication Status:  ");
		puts(buffer);
		shutdown(s, 2);
		closesocket(s);
		WSACleanup();
		break;
	}

	shutdown(s, 2);
	closesocket(s);
	WSACleanup();

	exit(0);
}
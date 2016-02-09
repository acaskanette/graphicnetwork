#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include <SDL_net.h>

class ClientMain {

public:
	IPaddress ip;		/* Server address */
	TCPsocket sd;		/* Socket descriptor */
	int quit, len;
	char buffer[512];
	std::string input;

	ClientMain();
	~ClientMain();

};
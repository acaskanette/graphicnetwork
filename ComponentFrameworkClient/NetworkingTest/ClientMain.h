#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#include <SDL_net.h>


typedef union {
	SDL_Event eventName;
	char buffer[sizeof(SDL_Event)];
} SDL_Event_NETWORK_TRANSMITABLE;


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
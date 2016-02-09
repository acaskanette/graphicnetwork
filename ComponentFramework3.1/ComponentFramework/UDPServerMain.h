#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include <SDL_net.h>

typedef union {
	SDL_Event eventName;
	char buffer[sizeof(SDL_Event)];
} SDL_Event_NETWORK_TRANSMITABLE;


class UDPServerMain
{
public:
	UDPServerMain();
	~UDPServerMain();

	SDL_Event Listen();


private:
	UDPsocket sd;       /* Socket descriptor */
	UDPpacket *p;       /* Pointer to packet memory */

};


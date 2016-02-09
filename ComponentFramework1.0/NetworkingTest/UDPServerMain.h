#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL_net.h>

class UDPServerMain
{
public:
	UDPServerMain();
	~UDPServerMain();


private:
	UDPsocket sd;       /* Socket descriptor */
	UDPpacket *p;       /* Pointer to packet memory */

};


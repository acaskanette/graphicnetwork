#pragma once

#include "NetworkDefines.h"


class UDPServerMain
{
public:
	UDPServerMain();
	~UDPServerMain();

	SDL_Event e;  // Last event received	
	bool Listen();  // returns true if an event was received, stores the event in e

private:
	UDPsocket socketDescriptor;
	UDPpacket *packet;

};


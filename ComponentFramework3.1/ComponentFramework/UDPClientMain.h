#pragma once

#include "NetworkDefines.h"


class UDPClientMain
{
public:
	UDPClientMain();
	~UDPClientMain();

	SDL_Event e;	// Last event received from SDL
	bool Listen();	// Listens for an event and stores it in e
	void Send();	// Sends the event across the network 

private:

	UDPsocket socketDescriptor;
	IPaddress serverAddress;
	UDPpacket *packet;
		
};


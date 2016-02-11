#pragma once

#include "NetworkDefines.h"


class UDPServerMain
{
public:
	UDPServerMain();
	~UDPServerMain();

	SDL_Event e;  // Last event received	
	bool Listen();  // returns true if an event was received, stores the event in e
	// To be implemented
	// returns 0 if nothing received
	// int ReceiveData(void *data_, uint32 sizeOfData_) {
	//	SDL_UDP_recv(sd,p);
	//	memcpy_s( data_, sizeOfData_, p->data, p->len);                          // threadsafe copying of data between buffers
	//  //        destination <-size  source   <-size
	// }

	// Call above with:
	// udpnet->ReceiveData(&SDLEvent, sizeof(SDL_Event));


	// void SendData (const void *data_, const Uint32 sizeOfData_) {
	//		// Set up ports, IP, etc..
	//		memcpy_s(p->data, p->len, data_, sizeOfData_);
	//
	//
	// }

	// int Broadcast(SDLEvent) { }


private:
	UDPsocket socketDescriptor;
	UDPpacket *packet;

};


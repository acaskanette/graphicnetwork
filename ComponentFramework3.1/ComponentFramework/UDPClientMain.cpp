#include "UDPClientMain.h"


UDPClientMain::UDPClientMain()
{
	
	std::cout << "SDLNet Client Begin: " << std::endl;

	// Initializes SDL_Net
	if (SDLNet_Init() < 0)
	{
		std::cout << "SDLNet_Init error: " << SDLNet_GetError() << std::endl;		
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "SDLNet Initialized..." << std::endl;		
	}

	// Open a socket and store in sd
	if (!(socketDescriptor = SDLNet_UDP_Open(0)))
	{
		std::cout << "SDLNet_UDP_Open error: " << SDLNet_GetError() << std::endl;		
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "UDP Connection Opened..." << std::endl;		
	}

	// Create host
	if (SDLNet_ResolveHost(&serverAddress, "localhost", 0x1A2B))
	{
		std::cout << "SDLNet_ResolveHost error: " << SDLNet_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "Host resolved...." << std::endl;		
	}

	// Set packet size
	if (!(packet = SDLNet_AllocPacket(512)))
	{
		std::cout << "SDLNet_AllocPacket error: " << SDLNet_GetError() << std::endl;		
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "Packet size set..." << std::endl;		
	}

	std::cout << "SDLNet Client Load Complete" << std::endl;

		
}


UDPClientMain::~UDPClientMain()
{
	SDLNet_FreePacket(packet);
	SDLNet_Quit();

}


bool UDPClientMain::Listen() {


	// std::cout << "Client Listening for events to send..." << std::endl;	
		
	if (SDL_PollEvent(&e)) {		
		// std::cout << "Client found new event to send..." << std::endl;
		return true;
	}

	return false; // No new events

}




void UDPClientMain::Send() {
	
	SDL_Event_NETWORK_TRANSMITABLE netEvent;

	netEvent.eventName = e;
	
	// std::cout << "Creating packet..." << std::endl;
	
	// Copy over event data
	for (int i = 0; i < sizeof(SDL_Event); i++) {
		*(packet->data + i) = *(netEvent.buffer + i);
	}

	// Construct Packet
	packet->address.host = serverAddress.host;	// Set host
	packet->address.port = serverAddress.port;	// Set port
	packet->len = sizeof(SDL_Event);

	SDLNet_UDP_Send(socketDescriptor, -1, packet); // Sends packet on the channel, -1

	std::cout << "Event sent: " << netEvent.eventName.type << std::endl;
}
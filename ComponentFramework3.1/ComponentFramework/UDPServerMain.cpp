#include "UDPServerMain.h"


UDPServerMain::UDPServerMain()
{
				
		int quit;

		/* Initialize SDL_net */
		if (SDLNet_Init() < 0)	{
			std::cout << "SDLNet_Init error: " << SDLNet_GetError() << std::endl;			
			exit(EXIT_FAILURE);
		}
		else {
			std::cout << "SDLNet_Initialized..." << std::endl;
		}

		/* Open a socket */
		if (!(socketDescriptor = SDLNet_UDP_Open(0x1A2B))) {

			std::cout << "SDLNet_UDP_Open error: " << SDLNet_GetError() << std::endl;			
			exit(EXIT_FAILURE);
		}
		else {
			std::cout << "SDLNet UDP port opened..." << std::endl;
		}

		/* Make space for the packet */
		if (!(packet = SDLNet_AllocPacket(512)))	{
			std::cout << "SDLNet_AllocPacket error: " << SDLNet_GetError() << std::endl;		
			exit(EXIT_FAILURE);
		}
		else {
			std::cout << "SDLNet packet size set..." << std::endl;
		}
		

		
		
}



UDPServerMain::~UDPServerMain()
{

	
	SDLNet_FreePacket(packet);
	SDLNet_Quit();
}


// returns true if a new event is on the server
bool UDPServerMain::Listen() {
			

		// std::cout << "SDLNet listening for packet..." << std::endl;
		// Wait for and receive a packet, stored in p
		if (SDLNet_UDP_Recv(socketDescriptor, packet))
		{

			// make a union event
			SDL_Event_NETWORK_TRANSMITABLE netEvent;
			// set its buffer to the value of the data
			for (int i = 0; i < sizeof(SDL_Event); i++) {
				netEvent.buffer[i] = packet->data[i];
			}
			// make a concrete event
			e = netEvent.eventName;
			// debug log its type
			std::cout << "Received SDL Event Type: " << netEvent.eventName.type << std::endl;
			

			return true; // new event!
						
		}

		return false;		// No new event
	
}

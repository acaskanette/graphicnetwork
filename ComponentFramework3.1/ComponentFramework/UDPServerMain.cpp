#include "UDPServerMain.h"


UDPServerMain::UDPServerMain()
{
				
		int quit;

		/* Initialize SDL_net */
		if (SDLNet_Init() < 0)
		{
			printf("SDLNet_Init: %s\n", SDLNet_GetError());
			exit(EXIT_FAILURE);
		}

		/* Open a socket */
		if (!(sd = SDLNet_UDP_Open(0x1A2B)))
		{
			printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
			exit(EXIT_FAILURE);
		}

		/* Make space for the packet */
		if (!(p = SDLNet_AllocPacket(512)))
		{
			fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
			exit(EXIT_FAILURE);
		}

		

		
		
}



UDPServerMain::~UDPServerMain()
{

	/* Clean and exit */
	SDLNet_FreePacket(p);
	SDLNet_Quit();
}

SDL_Event UDPServerMain::Listen() {

	/* Main loop */
	bool quit = false;
	while (!quit)
	{
		/* Wait a packet. UDP_Recv returns != 0 if a packet is coming */
		if (SDLNet_UDP_Recv(sd, p))
		{

			// make a union event
			SDL_Event_NETWORK_TRANSMITABLE netE;
			// set its buffer to the value of the data
			for (int i = 0; i < sizeof(SDL_Event); i++) {
				netE.buffer[i] = p->data[i];
			}
			// make a concrete event
			SDL_Event e = netE.eventName;
			// debug log its type
			std::cout << "Received SDL Event Type: " << e.type << std::endl;
			// return the event
			return e;
						
		}
	}


}

#include "UDPClientMain.h"


UDPClientMain::UDPClientMain()
{


	int quit;	

	/* Initialize SDL_net */
	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	else {
		printf("SDLNet Initialized.");
	}

	/* Open a socket on random port */
	if (!(sd = SDLNet_UDP_Open(0)))
	{
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	else {
		printf("UDP Connection Opened");
	}

	/* Resolve server name  */
	if (SDLNet_ResolveHost(&srvadd, "localhost", 0x1A2B))
	{
		//fprintf(stderr, "SDLNet_ResolveHost(%s %d): %s\n", argv[1], atoi(argv[2]), SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	else {
		printf("Host resolved.");
	}

	/* Allocate memory for the packet */
	if (!(p = SDLNet_AllocPacket(512)))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	else {
		printf("Packet size set");
	}

	/* Main loop */
	//quit = 0;
	SDL_Event event_;
	while (SDL_PollEvent(&event_)) {
		
		SDL_Event_NETWORK_TRANSMITABLE netEvent;

		netEvent.eventName = event_;

		printf("Fill the buffer\n>");
		for (int i = 0; i < sizeof(SDL_Event); i++) {
			*(p->data+i) = *(netEvent.buffer+i);
		}

		std::cout << "Event sent: " << netEvent.eventName.type << std::endl;

		p->address.host = srvadd.host;	/* Set the destination host */
		p->address.port = srvadd.port;	/* And destination port */
		p->len = sizeof(SDL_Event);

		SDLNet_UDP_Send(sd, -1, p); /* This sets the p->channel */
		printf("Packet sent");
		
	}

	SDLNet_FreePacket(p);
	SDLNet_Quit();

	
}


UDPClientMain::~UDPClientMain()
{
}
#include "ClientMain.h"

ClientMain::ClientMain() {
	
	

	// Initialize SDL_net
	if (SDLNet_Init() < 0)
	{
		printf("SDL failed to initialize");
		exit(EXIT_FAILURE);
	}


	/* NULL implies this is a server */
	if (SDLNet_ResolveHost(&ip, "142.214.198.36", 0x2B1A) < 0)
	{
		printf("SDL_net failed to resolve host");
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "IP Set up ip: " << std::hex << ip.host << ":" << std::hex << ip.port << std::endl;
		//printf("IP Set up on port: 9998\n\n");
	}

	
	// Open a connection with the IP provided (listen on the host's port)
	if (!(sd = SDLNet_TCP_Open(&ip)))
	{
		std::cout << "Failed to connect to ip: " << std::hex << ip.host << ":" << std::hex << ip.port << std::endl;
		//printf("Failed to open Port");
		exit(EXIT_FAILURE);
	}

	/* Send messages */
	quit = 0;
	while (!quit)
	{
		printf("Write something:\n>");
		std::getline(std::cin, input);
		
		//std::cin >> buffer;
		//scanf("%s", buffer);

		//len = input.length();
		//if (SDLNet_TCP_Send(sd, (void *)input.c_str(), input.length()+1) < len) // send this info over the net, returns how many bytes
		//{
		//	//fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
		//	exit(EXIT_FAILURE);
		//}
		
		SDL_Event e;

		e.type = 25;

		SDL_Event_NETWORK_TRANSMITABLE eventToSend;
		eventToSend.eventName = e;
		std::cout << "Client sends SDL Event Type: " << e.type << std::endl;
		len = sizeof(eventToSend);
		if (SDLNet_TCP_Send(sd, (void *)eventToSend.buffer, sizeof(eventToSend)) < len)
		{
			exit(EXIT_FAILURE);
		}

		if (input == "exit" || input == "quit")
			quit = 1;
		
	}

	SDLNet_TCP_Close(sd);
	SDLNet_Quit();

}

ClientMain::~ClientMain() {
	// Destroy heap variables (none)
}
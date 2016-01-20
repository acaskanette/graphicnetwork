#include "ClientMain.h"

ClientMain::ClientMain() {
	
	// Initialize SDL_net
	if (SDLNet_Init() < 0)
	{
		printf("SDL failed to initialize");
		exit(EXIT_FAILURE);
	}

	
	// Open a connection with the IP provided (listen on the host's port) */
	if (!(sd = SDLNet_TCP_Open(&ip)))
	{
		printf("Failed to open Port");
		exit(EXIT_FAILURE);
	}

	/* Send messages */
	quit = 0;
	while (!quit)
	{
		printf("Write something:\n>");
		std::cin >> buffer;
		//scanf("%s", buffer);

		len = strlen(buffer) + 1;
		if (SDLNet_TCP_Send(sd, (void *)buffer, len) < len) // send this info over the net, returns how many bytes
		{
			//fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
			exit(EXIT_FAILURE);
		}

		if (strcmp(buffer, "exit") == 0)
			quit = 1;
		if (strcmp(buffer, "quit") == 0)
			quit = 1;
	}

	SDLNet_TCP_Close(sd);
	SDLNet_Quit();

}

ClientMain::~ClientMain() {
	// Destroy heap variables (none)
}
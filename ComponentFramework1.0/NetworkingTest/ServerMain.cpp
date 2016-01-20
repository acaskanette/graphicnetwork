#include "ServerMain.h"


ServerMain::ServerMain()
{
	TCPsocket sd, csd; /* Socket descriptor, Client socket descriptor */
	IPaddress ip, *remoteIP;
	int quit, quit2;
	char buffer[512];



	if (SDLNet_Init() < 0)
	{
		printf("SDL_net failed to Initialize");
		exit(EXIT_FAILURE);
	}

	/* NULL implies this is a server */
	if (SDLNet_ResolveHost(&ip, NULL, 9998) < 0)
	{
		printf("SDL_net failed to resolve host");
		exit(EXIT_FAILURE);
	}
	else {
		printf("IP Set up on port 9998\n\n");
	}

	/* Open a connection with the IP provided (listen on the host's port) */
	if (!(sd = SDLNet_TCP_Open(&ip)))
	{
		//fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	else {
		printf("Now listening for connection on port 9998\n\n");
	}

	/* Wait for a connection, send data and term */
	quit = 0;
	while (!quit)
	{
		/* This check the sd if there is a pending connection.
		* If there is one, accept that, and open a new socket for communicating */
		if ((csd = SDLNet_TCP_Accept(sd)))
		{
			/* Now we can communicate with the client using csd socket
			* sd will remain opened waiting other connections */

			/* Get the remote address */
			if ((remoteIP = SDLNet_TCP_GetPeerAddress(csd)))
				/* Print the address, converting in the host format */
				printf("Host connected: %x %d\n", SDLNet_Read32(&remoteIP->host), SDLNet_Read16(&remoteIP->port));
			//else
			// fprintf(stderr, "SDLNet_TCP_GetPeerAddress: %s\n", SDLNet_GetError());

			quit2 = 0;
			while (!quit2)
			{
				if (SDLNet_TCP_Recv(csd, buffer, 512) > 0)
				{
					printf("Client say: %s\n", buffer);

					if (strcmp(buffer, "exit") == 0)	// lexicon graphical difference is nothing, they're same string
					{
						quit2 = 1;
						printf("Terminate connection\n");
					}
					if (strcmp(buffer, "quit") == 0)	/* Quit the program */
					{
						quit2 = 1;
						quit = 1;
						printf("Quit program\n");
					}
				}
			}

			/* Close the client socket */
			SDLNet_TCP_Close(csd);
		}
	}

	SDLNet_TCP_Close(sd);
	SDLNet_Quit();
}


ServerMain::~ServerMain()
{
}
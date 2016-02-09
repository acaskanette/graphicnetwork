#include <iostream>
#include "GameSceneManager.h"
#include "Debug.h"
#include <iostream>

using namespace GAME;

int main(int argc, char* argcs[]) {


	/// c11: This is evaluated at compile time, if void* != 4 then
	/// this must be a 64-bit build - just a quick test
	/// All my libraries are 32bit
	static_assert(sizeof(void*) == 4, "This program is not ready for 64-bit build");


	Debug::Init();

	char query;
	bool isServer;

	std::cout << "Type y for server: ";
	std::cin >> query; 
	isServer = (query == 'y');

	
	GameSceneManager::getInstance()->Run(isServer);
	exit(0);
}
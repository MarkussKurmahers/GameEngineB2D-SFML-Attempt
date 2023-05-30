/* This sample project uses Box2D to add physical properties to objects rendered
using SFML. It pays particular attention to the issue of scaling management, and
handling conversions between subsystems which operate using different coordinate
systems. */

#include "GameEngine.h"
#include "Common.h"


using namespace std;
int main()
{
	GameEngine* myGame = new GameEngine();

	bool running = true;                  

	while (running)
	{
		running = myGame->Update();
	}

	delete myGame;
	return 0;

}
#include "GameEngine.h"
#include "GameObject.h"
#include "PhysicsSubsystem.h"
#include "InputSubsystem.h"
#include "GraphicsSubsystem.h"
#include "EventQueue.h"
#include "AudioSubsystem.h"


/*
The constructor initializes the event queue, game objects vector, and subsystems vector. It also creates a network subsystem and adds several other subsystems to the subsystems vector.
Then it calls the SetupDemo() function.
The destructor deletes all subsystems, game objects, event queue, and network subsystem objects.
The Update() function updates all subsystems and checks for any events in the event queue.
If an event is found with the type of "Exit", the function returns false, otherwise it continues to check if the event has any systems. If it does not, the event is deleted from the queue.
The SetupDemo() function reads from a JSON file called test1.json and processes the data to create game objects with physics and graphics components.
It first reads the top level keys and separates them into "objectKeys" and "dataKeys". It then reads each object key and gets their second level keys.
The function then creates a game object for each object key, and adds physics and graphics components to the object if it is an obstacle or player object.
The physics and graphics components are initialized with the appropriate data from the JSON file.
*/



GameEngine::GameEngine()
{
	eventQueue = new EventQueue();
	gameObjects = new std::vector<GameObject*>;
	subsystems = new std::vector<Subsystem*>;
	networksubsystem = new NetworkSubsystem(eventQueue, gameObjects);

	PhysicsSubsystem* physicsSystem = new PhysicsSubsystem(eventQueue, gameObjects);
	GraphicsSystem* graphicsSystem = new GraphicsSystem(eventQueue, gameObjects);
	InputSubsystem* inputSubsystem = new InputSubsystem(eventQueue, gameObjects);
	AudioSubsystem* audioSubsystem = new AudioSubsystem(eventQueue, gameObjects);

	subsystems->push_back(physicsSystem);
	subsystems->push_back(graphicsSystem);
	subsystems->push_back(inputSubsystem);
	subsystems->push_back(audioSubsystem);

	networksubsystem->Start();

	SetupDemo();
}

GameEngine::~GameEngine()
{

	for (int i = 0; i < subsystems->size(); i++)
	{
		delete subsystems->at(i);
	}

	for (int i = 0; i < gameObjects->size(); i++)
	{
		delete gameObjects->at(i);
	}

	subsystems->clear();
	gameObjects->clear();

	delete subsystems;
	delete gameObjects;
	delete eventQueue; //Cleaning everything up
	delete networksubsystem;
}

int GameEngine::Update()
{
	int i;

	for (i = 0; i < subsystems->size(); i++)
	{
		subsystems->at(i)->Update();
	}
	networksubsystem->Update();

	int eQSize = eventQueue->events.size();

	if (eQSize > 0)
	{
		for (i = 0; i < eQSize; i++)
		{
			if (eventQueue->events[i]->type == EventType::Exit)
			{
				return false;
			}

			if (eventQueue->events[i]->systems.size() == 0)
			{
				delete eventQueue->events[i];
				eventQueue->events.erase(eventQueue->events.begin() + i);
			}
		}
	}

	return true;
}




void GameEngine::SetupDemo()
{
	std::ifstream fileStream("test1.json"); // Json file opening
	Json::Value fileData;
	fileStream >> fileData;
	fileStream.close();

	Json::Value::Members topLevelKeys = fileData.getMemberNames();
	std::vector<std::string> dataKeys, objectKeys;


	for (int i = 0; i < topLevelKeys.size(); i++)
	{
		if (fileData[topLevelKeys[i]].size() > 0)
		{
			objectKeys.push_back(topLevelKeys[i]);
		}
		else
		{
			dataKeys.push_back(topLevelKeys[i]);
		}
	}

	std::string levelName;

	std::vector<Json::Value::Members*> secondLevelKeys;

	for (int i = 0; i < objectKeys.size(); i++)
	{
		Json::Value::Members* temp = new Json::Value::Members;


		*temp = fileData[objectKeys[i]].getMemberNames();

		secondLevelKeys.push_back(temp);
	}


	for (int i = 0; i < objectKeys.size(); i++)
	{
		std::string objname = objectKeys[i];
		gameObjects->push_back(new GameObject(objname));
		
		if (!gameObjects->back()->getName().find("Obstacle"))
		{
			PhysicsComponent obstaclePhysics(gameObjects->back(), subsystems->at(0));
			GraphicsComponent obstacleGraphics(gameObjects->back(), subsystems->at(1));


			if(fileData[objname]["SetShape"].asString() == "Rectangle")
			{
				obstacleGraphics.SetShapeRectangle();

				float _x = fileData[objname]["RectSizeX"].asFloat();
				float _y = fileData[objname]["RectSizeY"].asFloat();

				obstacleGraphics.SetRectShapeSize(sf::Vector2f(_x, _y));
			}
			else if(fileData[objname]["SetShape"].asString() == "Circle")
			{
				obstacleGraphics.SetShapeCircle();
				float rad = fileData[objname]["Radius"].asFloat();
			   obstacleGraphics.SetRadius(rad);
			}
		

			if (fileData[objname]["SetShapeColor"].asString() == "Green")
			{
				obstacleGraphics.SetShapeColor(sf::Color::Green);
			}
			else if (fileData[objname]["SetShapeColor"].asString() == "Magenta")
			{
				obstacleGraphics.SetShapeColor(sf::Color::Magenta);

			}

			std::string texPath = fileData[objname]["LoadTex"].asString();
			obstacleGraphics.SetTexture(texPath);

		
			float _x = fileData[objname]["PositionX"].asFloat();
			float _y = fileData[objname]["PositionY"].asFloat();
			obstacleGraphics.SetPosition(sf::Vector2f(_x,_y));


			float start_x = fileData[objname]["StartSizeX"].asFloat();
			float start_y = fileData[objname]["StartSizeY"].asFloat();
			float size_x = fileData[objname]["StartPositionX"].asFloat();
			float size_y = fileData[objname]["StartPositionY"].asFloat();

			obstaclePhysics.SetStartSize(b2Vec2(start_x, start_y));
			obstaclePhysics.SetStartPosition(b2Vec2(size_x, size_y));

			obstaclePhysics.Start();

			gameObjects->back()->addComponent(subsystems->at(0)->addComponent(&obstaclePhysics));
			gameObjects->back()->addComponent(subsystems->at(1)->addComponent(&obstacleGraphics));

		}




		if (!gameObjects->back()->getName().find("Player"))
		{
			PhysicsComponent playerPhysics(gameObjects->back(), subsystems->at(0));
			GraphicsComponent playerGraphics(gameObjects->back(), subsystems->at(1));
			InputComponent playerInput(gameObjects->back(), subsystems->at(2));
			AudioComponent playerAudio(gameObjects->back(), subsystems->at(3));

			if (fileData[objname]["SetShape"].asString() == "Rectangle")
			{
				playerGraphics.SetShapeRectangle();

				float _x = fileData[objname]["RectSizeX"].asFloat();
				float _y = fileData[objname]["RectSizeY"].asFloat();

				playerGraphics.SetRectShapeSize(sf::Vector2f(_x, _y));
			}
			else if (fileData[objname]["SetShape"].asString() == "Circle")
			{
				playerGraphics.SetShapeCircle();
				float rad = fileData[objname]["Radius"].asFloat();
				playerGraphics.SetRadius(rad);
			}


			if (fileData[objname]["SetShapeColor"].asString() == "Green")
			{
				playerGraphics.SetShapeColor(sf::Color::Green);
			}
			else if (fileData[objname]["SetShapeColor"].asString() == "Magenta")
			{
				playerGraphics.SetShapeColor(sf::Color::Magenta);

			}

			float _x = fileData[objname]["PositionX"].asFloat();
			float _y = fileData[objname]["PositionY"].asFloat();
			playerGraphics.SetPosition(sf::Vector2f(_x, _y));

			std::string texPath = fileData[objname]["LoadTex"].asString();
			playerGraphics.SetTexture(texPath);

			float start_x = fileData[objname]["StartSizeX"].asFloat();
			float start_y = fileData[objname]["StartSizeY"].asFloat();
			float size_x = fileData[objname]["StartPositionX"].asFloat();
			float size_y = fileData[objname]["StartPositionY"].asFloat();

			playerPhysics.SetStartSize(b2Vec2(start_x, start_y));
			playerPhysics.SetStartPosition(b2Vec2(size_x, size_y));

			playerPhysics.Start();


			std::string path = fileData[objname]["LoadMusic"].asString();
			playerAudio.LoadMusic(path);
			playerAudio.PlayMusic();

			


			gameObjects->back()->addComponent(subsystems->at(0)->addComponent(&playerPhysics));
			gameObjects->back()->addComponent(subsystems->at(1)->addComponent(&playerGraphics));
			gameObjects->back()->addComponent(subsystems->at(2)->addComponent(&playerInput));
			gameObjects->back()->addComponent(subsystems->at(3)->addComponent(&playerAudio));


		}



	}


	for (int i = 0; i < secondLevelKeys.size(); i++)
	{
		delete secondLevelKeys[i];
	}

	secondLevelKeys.clear();
}

#pragma once
#include "Common.h"
#include "NetworkSubystem.h"
class Subsystem;
class EventQueue;
class GameObject;

//Game engine class is the core component of the engine to be running, where all of the "action" is happening in GameEngine.cpp


class GameEngine
{
public:
	GameEngine();
	~GameEngine();
	int Update();
	void SetupDemo();

private:
	std::vector<Subsystem*>* subsystems;
	std::vector<GameObject*>* gameObjects;
	EventQueue* eventQueue;
	NetworkSubsystem* networksubsystem;
};
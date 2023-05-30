#pragma once

#include "Common.h"

class EventQueue;
class GameObject;
class Component;

class Subsystem
{
public:
	Subsystem(SubsystemType type_, EventQueue* eQ_, std::vector<GameObject*>* gameObjects_) : type(type_), eQ(eQ_), gameObjects(gameObjects_) {};
	Subsystem(const Subsystem& other) : type(other.type), eQ(other.eQ), gameObjects(other.gameObjects) {};

	inline SubsystemType getType() { return type; }
	inline EventQueue* getEQ() { return eQ; }
	inline std::vector<GameObject*>* getGameObjects() { return gameObjects; }

	virtual void Update() = 0;
	virtual Component* addComponent(Component* component_) = 0;
	virtual int getNumComponents() = 0;

protected:
	const SubsystemType type;
	EventQueue* eQ;
	std::vector<GameObject*>* gameObjects;
};
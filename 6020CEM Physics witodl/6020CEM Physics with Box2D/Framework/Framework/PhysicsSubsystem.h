#pragma once

#include "Common.h"
#include "ParentSubsystem.h"
#include "PhysicsComponent.h"


class PhysicsSubsystem : public Subsystem // hold the b2world
{
public:
	PhysicsSubsystem(EventQueue* eQ_, std::vector<GameObject*>* gameObjects_) : Subsystem(SubsystemType::Physics, eQ_, gameObjects_) {
		components = new std::vector<PhysicsComponent>;
		components->reserve(MAX_ENTITIES);
	};
	PhysicsSubsystem(const PhysicsSubsystem& other) : Subsystem(other) { components->reserve(MAX_ENTITIES); };

	Component* addComponent(Component* component_);
	inline void removeComponent(int i_) { components->erase(components->begin() + i_); }
	inline Component* getComponent(int i_) { return &(components->at(i_)); }

	void Update(); // every frame updates what to do
	inline int getNumComponents() { return components->size(); }
	inline b2World* GetWorld() { return world; }
	


private:
	std::vector<PhysicsComponent>* components;
	// values to make sure, that the world is actually moving overtime
	float timeStep = 1.0f / 60.0f; 
	int velocityIterations = 6;
	int positionIterations = 2;


	b2Vec2 gravity = b2Vec2(0, 0);
	b2World* world = new b2World(gravity);
};
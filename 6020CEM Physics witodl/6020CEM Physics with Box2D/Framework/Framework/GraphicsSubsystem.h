#pragma once

#include "Common.h"
#include "ParentSubsystem.h"
#include "GraphicsComponent.h"

class GraphicsSystem : public Subsystem
{
public:
	GraphicsSystem(EventQueue* eQ_, std::vector<GameObject*>* gameObjects_) : Subsystem(SubsystemType::Graphics, eQ_, gameObjects_) {
		components = new std::vector<GraphicsComponent>;
		components->reserve(MAX_ENTITIES);
		window = new sf::RenderWindow(sf::VideoMode(800, 600), "Mk Engine");
	};
	GraphicsSystem(const GraphicsSystem& other) : Subsystem(other), window(other.window) { components->reserve(MAX_ENTITIES); };

	Component* addComponent(Component* component_);
	inline void removeComponent(int i_) { components->erase(components->begin() + i_); }
	inline Component* getComponent(int i_) { return &(components->at(i_)); }

	void Update(); // every frame updates what to do
	inline int getNumComponents() { return components->size(); }
	sf::RenderWindow* GetWindow() { return window; }//change name

private:
	std::vector<GraphicsComponent>* components;
	sf::RenderWindow* window;
};


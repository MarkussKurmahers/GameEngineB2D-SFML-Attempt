#pragma once
#include "Common.h"

class Component;

class GameObject
{
public:

	//a static variable to keep track of the total number of GameObjects
	static int objectCount;
	//constructors for GameObjects, which can take a name, components, or both
	GameObject();
	GameObject(std::string name_);
	GameObject(std::string name_, std::unordered_map<ComponentType, Component*> components_);
	GameObject(const GameObject& other);
	//destructor
	~GameObject();

	GameObject& operator=(const GameObject& other);
	//function for adding component
	void addComponent(Component* component_);
	//getters and setters, as described in function names
	Component* getComponent(ComponentType type_);
	inline std::string getName() { return *name; };
	inline int getObjectID() { return objectID; };
	inline void setName(std::string name_) { *name = name_; }

	inline void setColor(sf::Color color) {};

private:
	//variables 
	int objectID;
	std::string* name;
	std::unordered_map<ComponentType, Component*> components;
};
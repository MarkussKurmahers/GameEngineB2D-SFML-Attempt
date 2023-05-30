#include "GameObject.h"
#include "Component.h"


GameObject::GameObject()
{
	name = new std::string();
	objectID = objectCount;
	objectCount++;
}

GameObject::GameObject(std::string name_)
{
	name = new std::string();
	objectID = objectCount;
	*name = name_;
	objectCount++;
}

GameObject::GameObject(std::string name_, std::unordered_map<ComponentType, Component*> components_)
{
	objectID = objectCount;
	*name = name_;
	components = components_;
	objectCount++;
}

GameObject::GameObject(const GameObject& other) : objectID(other.objectID), name(other.name), components(other.components) {}; // memcopy replacement components

GameObject::~GameObject()
{
	delete name;
}

GameObject& GameObject::operator=(const GameObject& other)
{
	if (this == &other)
		return *this;

	GameObject a(other);
	return a;
}

/*
 * addCOmponent is a short but crucial function. We take in a pointer to a
 * Component, check the component's type, and insert a pair (a connection
 * between that type and that specific pointer) onto our components map.
 */

void GameObject::addComponent(Component* component_)
{
	components.insert({ component_->getType(), component_ });
}

/*
 * Here, we can pass in a ComponentType - say, ComponentType::Physics, and
 * return the pointer to that component - very useful when it comes to processing
 * events.
 */

Component* GameObject::getComponent(ComponentType type_)
{
	auto it = components.find(type_);
	return it->second;
}

int GameObject::objectCount = 0;
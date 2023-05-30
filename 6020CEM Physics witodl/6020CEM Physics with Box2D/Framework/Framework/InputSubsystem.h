#pragma once

#include "Common.h"
#include "ParentSubsystem.h"
#include "InputComponent.h"

class InputSubsystem : public Subsystem
{
public:
	InputSubsystem(EventQueue* eQ_, std::vector<GameObject*>* gameObjects_) : Subsystem(SubsystemType::Input, eQ_, gameObjects_) {
		components = new std::vector<InputComponent>;
		components->reserve(MAX_ENTITIES);
	};
	InputSubsystem(const InputSubsystem& other) : Subsystem(other) { components->reserve(MAX_ENTITIES); };

	Component* addComponent(Component* component_);
	inline void removeComponent(int i_) { components->erase(components->begin() + i_); }
	inline Component* getComponent(int i_) { return &(components->at(i_)); }

	void Update();
	inline int getNumComponents() { return components->size(); }

private:
	std::vector<InputComponent>* components;
};


#pragma once

#include "Common.h"
#include "Component.h"

// the Inputcomponent.h is one of the more vanilla components
class InputComponent : public Component
{
public:
	inline InputComponent(GameObject* myObject_, Subsystem* mySystem_) : Component(ComponentType::Input, myObject_, mySystem_) {};
	inline InputComponent(const InputComponent& other) : Component(other) {};

	InputComponent& operator=(const InputComponent& other);

	void Update();

private:
	
};
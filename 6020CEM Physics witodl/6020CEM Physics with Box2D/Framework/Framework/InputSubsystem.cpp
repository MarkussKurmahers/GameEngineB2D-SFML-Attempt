#pragma once

#include "InputSubsystem.h"
#include "EventQueue.h"

Component* InputSubsystem::addComponent(Component* component_)
{
	if (component_->getType() == ComponentType::Input)
	{
		InputComponent* temp = static_cast<InputComponent*>(component_);
		components->push_back(*temp);
		return &(components->back());
	}
	else
	{
		std::cout << "Tried to push a non-Input component to the Input subsystem wot" << std::endl;
		return nullptr;
	}
}

void InputSubsystem::Update()
{
	for (int i = 0; i < components->size(); i++)
	{
		components->at(i).Update();
	}

	int eQsize = eQ->events.size();

	if (eQsize > 0)
	{
		Event* temp;

		for (int i = 0; i < eQsize; i++)
		{
			temp = eQ->events[i];

			for (int j = 0; j < temp->systems.size(); j++)
			{
				if (temp->systems[j] == type)
				{
					auto it = eQ->functionMap.find(type);

					auto it2 = it->second->find(temp->type);

					it2->second(temp);

					temp->systems.erase(temp->systems.begin() + j);

					if (temp->systems.size() == 0)
					{
						delete eQ->events[i];
						eQ->events.erase(eQ->events.begin() + i);
					}
				}
			}
		}
	}
}
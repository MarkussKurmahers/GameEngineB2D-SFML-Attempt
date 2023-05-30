#pragma once
#include "PhysicsSubsystem.h"
#include "EventQueue.h"

Component* PhysicsSubsystem::addComponent(Component* component_)
{
	if (component_->getType() == ComponentType::Physics)
	{
		PhysicsComponent* temp = static_cast<PhysicsComponent*>(component_);
		components->push_back(*temp);
		return &(components->back());
	}
	else
	{
		std::cout << "Tried to push a non-physics component to the physics subsystem wot" << std::endl;
		return nullptr;
	}
}


void PhysicsSubsystem::Update()
{


	world->Step(timeStep, velocityIterations, positionIterations);
	


	for (int i = 0; i < components->size(); i++)
	{
		components->at(i).Update();
	}

	/* After this, we check the event queue. */

	int eQsize = eQ->events.size();

	if (eQsize > 0)
	{
		Event* temp;

		for (int i = 0; i < eQsize; i++)
		{
			/* If there's an event, we check it out, and see if it's
			 * something this subsystem cares about (== type).
			 */

			temp = eQ->events[i];

			for (int j = 0; j < temp->systems.size(); j++)
			{
				if (temp->systems[j] == type)
				{
					/* If we care about it, we know we'll have a function
					 * to deal with it somewhere in the eventQueue. We'll
					 * look into that in more detail in EventQueue.h
					 */

					auto it = eQ->functionMap.find(type);

					auto it2 = it->second->find(temp->type);

					/* We find our function and pass in the event as its
					 * parameter. We then pop our subsystem off the event's
					 * subsystem list, so we don't react to it twice!
					 */

					it2->second(temp);

					temp->systems.erase(temp->systems.begin() + j);

					/* If we were the last subsystem to react to the event,
					 * we remove it from the event queue entirely, to save
					 * memory. 
					 */

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
#include "EventQueue.h"
#include "GameObject.h"
#include "PhysicsComponent.h"
/*
 * In this CPP file, I define all of the Physics event response functions.
 * You can see them below.
 */
// The functions below handle the movements , where the linear velocity is called for specific movement, if the name of the object is player

void PhysicsHandleMoveUp(Event* event_)
{
	
	for (int i = 0; i < event_->objects.size(); i++)
	{
		GameObject* temp = event_->objects[i]; 
	
		if (temp->getName() == "Player")
		{
			Component* ptr = temp->getComponent(ComponentType::Physics); 
			PhysicsComponent* tempphysics = static_cast<PhysicsComponent*>(ptr);
			tempphysics->SetLinearVelocity(b2Vec2(0, -5));
			//tempphysics->SetLinearDamping(0.3);

		}

	}
}

void PhysicsHandleMoveLeft(Event* event_)
{
	for (int i = 0; i < event_->objects.size(); i++)
	{
		GameObject* temp = event_->objects[i];

		if (temp->getName() == "Player")
		{
			Component* ptr = temp->getComponent(ComponentType::Physics);
			PhysicsComponent* tempphysics = static_cast<PhysicsComponent*>(ptr);
			tempphysics->SetLinearVelocity(b2Vec2(-5, 0));
			//tempphysics->SetLinearDamping(0.3);
		}

	}

}

void PhysicsHandleMoveDown(Event* event_)
{
	for (int i = 0; i < event_->objects.size(); i++)
	{
		GameObject* temp = event_->objects[i];

		if (temp->getName() == "Player")
		{
			Component* ptr = temp->getComponent(ComponentType::Physics);
			PhysicsComponent* tempphysics = static_cast<PhysicsComponent*>(ptr);
			tempphysics->SetLinearVelocity(b2Vec2(0, 5));
			//tempphysics->SetLinearDamping(0.3);
		}

	}

}

void PhysicsHandleMoveRight(Event* event_)
{
	for (int i = 0; i < event_->objects.size(); i++)
	{
		GameObject* temp = event_->objects[i];

		if (temp->getName() == "Player")
		{
			Component* ptr = temp->getComponent(ComponentType::Physics);
			PhysicsComponent* tempphysics = static_cast<PhysicsComponent*>(ptr);
			tempphysics->SetLinearVelocity(b2Vec2(5, 0));
			//tempphysics->SetLinearDamping(0.3);
		}

	}

}

void PhysicsHandleMoveUpLeft(Event* event_)
{
	for (int i = 0; i < event_->objects.size(); i++)
	{
		GameObject* temp = event_->objects[i];

		if (temp->getName() == "Player")
		{
			Component* ptr = temp->getComponent(ComponentType::Physics);
			PhysicsComponent* tempphysics = static_cast<PhysicsComponent*>(ptr); // Something not working
			tempphysics->SetLinearVelocity(b2Vec2(-10, -10));
			//tempphysics->SetLinearDamping(0.3);
		}

	}

}


/* Here's where we initialise the map(s). Note that we're initialising one
 * map for each subsystem, because it reduces our search time for finding the
 * right function, than having all of the subsystems in one long map. Once
 * we've got the map associated with our subsystem, we check in that map for
 * the right EventType, and that provides us with the desired function.
 */
void EventQueue::InitialiseFunctionMaps()
{
	std::unordered_map<EventType, void(*)(Event*)>* physicsMap = new std::unordered_map<EventType, void(*)(Event*)>;

	physicsMap->insert({ EventType::MoveUp, &PhysicsHandleMoveUp });
	physicsMap->insert({ EventType::MoveLeft, &PhysicsHandleMoveLeft });
	physicsMap->insert({ EventType::MoveDown, &PhysicsHandleMoveDown });
	physicsMap->insert({ EventType::MoveRight, &PhysicsHandleMoveRight });

	functionMaps.push_back(physicsMap);
	functionMap.insert({ SubsystemType::Physics, physicsMap });

}

void EventQueue::popEvent(Event* event_)
{
	for (int i = 0; i < events.size(); i++)
	{
		if (events[i] == event_)
		{
			delete events[i];
			events.erase(events.begin() + i);
		}
	}
}


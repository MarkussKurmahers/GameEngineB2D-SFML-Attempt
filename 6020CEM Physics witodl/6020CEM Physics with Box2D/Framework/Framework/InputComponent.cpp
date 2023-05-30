#pragma once

#include "InputComponent.h"
#include "GameObject.h"
#include "InputSubsystem.h"
#include "EventQueue.h"
#include "GraphicsSubsystem.h"

inline InputComponent& InputComponent::operator=(const InputComponent& other)
{
	if (this == &other)
	{
		return *this;
	}

	memcpy(this, &other, sizeof(other));
	return *this;
}

void InputComponent::Update()
{
	//std::cout << "The IO component of the " << myObject->getName() << " Game Object is being updated!" << std::endl;
	
	std::vector<GameObject*> objects;
	std::vector<SubsystemType> systems;
	Event* event = new Event();
	int i;


	sf::Event e;

	GameObject* ptr = getMyObject(); 
	Subsystem* systemptr = ptr->getComponent(ComponentType::Graphics)->getMySystem();//accessing graphics sub system by chosing the component type graphics
	GraphicsSystem* tempgraphics = static_cast<GraphicsSystem*>(systemptr); //this is to access different components through the parent classes

	sf::RenderWindow* window = tempgraphics->GetWindow();

	window->pollEvent(e);


	if (e.type == sf::Event::Closed) { 
		window->close();
	}
	
	//Below is the input system, where I attempted making the input system to move diagonally, but was stuck with crashes.
	// The input system works for each key, to move up, down , left, right
	//

	if (e.type == sf::Event::KeyPressed) 
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
		{
			for (i = 0; i < mySystem->getGameObjects()->size(); i++)
			{
			objects.push_back(mySystem->getGameObjects()->at(i));
			}
			//adding the Physics subsystem
			systems.push_back(SubsystemType::Physics);
			//assigning the objects and systems vectors to the event
			event->assignObjects(objects);
			event->assignSystems(systems);
			//assigning the MoveUp event type to the event
			event->assignType(EventType::MoveUp);
			//adding the event to the event queue
			mySystem->getEQ()->events.push_back(event);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			for (i = 0; i < mySystem->getGameObjects()->size(); i++)
			{
				objects.push_back(mySystem->getGameObjects()->at(i));
			}
			systems.push_back(SubsystemType::Physics);
			event->assignObjects(objects);
			event->assignSystems(systems);
			event->assignType(EventType::MoveDown);
			mySystem->getEQ()->events.push_back(event);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			for (i = 0; i < mySystem->getGameObjects()->size(); i++)
			{
				objects.push_back(mySystem->getGameObjects()->at(i));
			}
			systems.push_back(SubsystemType::Physics);
			event->assignObjects(objects);
			event->assignSystems(systems);
			event->assignType(EventType::MoveRight);
			mySystem->getEQ()->events.push_back(event);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			for (i = 0; i < mySystem->getGameObjects()->size(); i++)
			{
				objects.push_back(mySystem->getGameObjects()->at(i));
			}
			systems.push_back(SubsystemType::Physics);
			event->assignObjects(objects);
			event->assignSystems(systems);
			event->assignType(EventType::MoveLeft);
			mySystem->getEQ()->events.push_back(event);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			for (i = 0; i < mySystem->getGameObjects()->size(); i++)
			{
				objects.push_back(mySystem->getGameObjects()->at(i));
			}
			systems.push_back(SubsystemType::Physics);
			event->assignObjects(objects);
			event->assignSystems(systems); // Something not working
			event->assignType(EventType::MoveUpLeft); // new event type for diagonal movement attempt
			mySystem->getEQ()->events.push_back(event);
		}

	}
	else
	{
		delete event; // ridiculous memory leak fix
	}

	
		
	
}
#pragma once
#include "GraphicsComponent.h"
#include "GameObject.h"
#include "PhysicsComponent.h"
inline GraphicsComponent& GraphicsComponent::operator=(const GraphicsComponent& other)
{
	if (this == &other)
	{
		return *this;
	}

	memcpy(this, &other, sizeof(other));
	return *this;
}

void GraphicsComponent::Update()
{
	//std::cout << "The graphics component of " << myObject->getName() << " is updating" << std::endl;
	//gets object and physics component
	GameObject* obj = getMyObject();
	Component* comp = obj->getComponent(ComponentType::Physics);
	PhysicsComponent* physicscomp = static_cast<PhysicsComponent*>(comp);
	//get physics position and set shape position accordingly
	b2Vec2 physicsPos = physicscomp->GetPosition();
	float physicsRot = physicscomp->GetRotation();

	rotation = -(physicsRot * 180 / b2_pi); // rotation formula
	Shape->setPosition(Position.x + physicsPos.x,Position.y + physicsPos.y);// setting position
	Shape->setRotation(rotation);// setting rotation
	
	
	
}
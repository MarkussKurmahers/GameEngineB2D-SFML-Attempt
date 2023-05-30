#pragma once

#include "PhysicsComponent.h"
#include "GameObject.h"
#include "PhysicsSubsystem.h"

inline PhysicsComponent& PhysicsComponent::operator=(const PhysicsComponent& other)
{
	if (this == &other)
	{
		return *this;
	}

	memcpy(this, &other, sizeof(other));
	return *this;
}

void PhysicsComponent::Start()
{
	Subsystem* temp = getMySystem();
	PhysicsSubsystem* tempphysics = static_cast<PhysicsSubsystem*>(temp); 
	//set up the body definition and create a body with it in the physics world
	BodyDef.type = b2_dynamicBody;
	BodyDef.position.Set(startpos.x, startpos.y);
	Body = tempphysics->GetWorld()->CreateBody(&BodyDef);
	//set up the shape of the fixture and its density and friction
	Shape.SetAsBox(startsize.x, startsize.y); //try to use polygons
	FixtureDef.shape = &Shape;   
	FixtureDef.density = 1.0f; 
	FixtureDef.friction = 1.0; 

	Body->CreateFixture(&FixtureDef);
	
	
}

void PhysicsComponent::Update()
{
	//std::cout << "The physics component of " << myObject->getName() << " is updating" << std::endl;
	Body->SetLinearDamping(0.1f);//set damping, so the object doesnt move forward all the time 
	Body->SetAngularDamping(0.001f);
}


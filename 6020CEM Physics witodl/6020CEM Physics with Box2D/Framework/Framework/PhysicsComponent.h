#pragma once

#include "Common.h"
#include "Component.h"

/*
 * PhysicsComponent is our most vanilla component, demonstrating a component which
 * updates every tick.
 */

class PhysicsComponent : public Component // this holds the physics bits of gameobjects and not b2world
{
public:
	inline PhysicsComponent(GameObject* myObject_, Subsystem* mySystem_) : Component(ComponentType::Physics, myObject_, mySystem_) {};
	inline PhysicsComponent(const PhysicsComponent& other) : Component(other), Body(other.Body) {};

	PhysicsComponent& operator=(const PhysicsComponent& other);
	void Start();
	void Update();
	inline void SetStartPosition(b2Vec2 pos) { startpos = pos; } // Different set and get functions, which determine the speed, position, size and damping for the objects, that are made seen on screen  
	inline void SetStartSize(b2Vec2 size) { startsize = b2Vec2(size.x/2.f, size.y/2.f); }
	inline void SetLinearVelocity(b2Vec2 value) { Body->SetLinearVelocity(value); }
	inline b2Vec2 GetPosition() { return Body->GetPosition(); }
	inline void SetLinearDamping(float value) { Body->SetLinearDamping(value); }
	inline b2Vec2 GetStartSize() { return startsize; };
	inline float GetRotation() { return Body->GetAngle(); }
	
	// g_rotation = -(p_rotation * 180/b2_pi)

private:
	// Different variables for physics
	b2Body* Body;
	b2Vec2 startpos, startsize;
	// add static 
	b2BodyDef BodyDef;
	b2PolygonShape Shape;
	b2FixtureDef FixtureDef;
	

};
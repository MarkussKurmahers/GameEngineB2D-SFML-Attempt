#pragma once
#include "Common.h"


class GameObject;
class Subsystem;




class Component {
public:
    //constructor that takes a ComponentType, a pointer to a GameObject, and a pointer to a Subsystem
	inline Component(ComponentType type_, GameObject* myObject_, Subsystem* mySystem_) : type(type_), myObject(myObject_), mySystem(mySystem_) {};
    //copy constructor that takes another Component and creates a new Component with the same data
	inline Component(const Component& other) : type(other.type), myObject(other.myObject), mySystem(other.mySystem) {};
    //a function to get the ComponentType of this Component
	inline const ComponentType getType() { return type; }
    //a function to get the GameObject that the Component belongs to
	inline GameObject* getMyObject() { return myObject; }
    //a function to get the Subsystem that the Component belongs to
	inline Subsystem* getMySystem() { return mySystem; }
    //a virtual function that must be implemented by subclasses to update the Component
	virtual void Update() = 0;

protected:
    //variables 
	const ComponentType type;
	GameObject* myObject;
	Subsystem* mySystem;
};
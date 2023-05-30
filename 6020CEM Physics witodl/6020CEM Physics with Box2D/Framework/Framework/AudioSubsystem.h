#pragma once

#include "Common.h"
#include "ParentSubsystem.h"
#include "AudioComponent.h"


// The subsystems mainly work the same way, as I will explain here


class AudioSubsystem : public Subsystem 
{
public:
	//constructor initializes the components vector
	AudioSubsystem(EventQueue* eQ_, std::vector<GameObject*>* gameObjects_) : Subsystem(SubsystemType::Audio, eQ_, gameObjects_) {
		components = new std::vector<AudioComponent>;
		components->reserve(MAX_ENTITIES);
	};
	//copy constructor copies the Subsystem and initializes the components vector
	AudioSubsystem(const AudioSubsystem& other) : Subsystem(other) { components->reserve(MAX_ENTITIES); };

	Component* addComponent(Component* component_); // adds a new component and retirms a pointer to it
	inline void removeComponent(int i_) { components->erase(components->begin() + i_); } //erases a component from the subsystem by its index
	inline Component* getComponent(int i_) { return &(components->at(i_)); }//returns a pointer to a component by its index

	void Update(); // every frame updates what to do
	inline int getNumComponents() { return components->size(); } // returns number of components in the subsystem


private:
	std::vector<AudioComponent>* components; // vector of Audiocomponents

};

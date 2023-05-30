#pragma once

#include "AudioComponent.h"
#include "GameObject.h"
#include "AudioSubsystem.h"

//this is an inline function for the AudioComponent class that overrides the assignment operator, This type of class is in all of the components cpps.
//it takes in a reference to another AudioComponent object 'other' and assigns it to the current object

inline AudioComponent& AudioComponent::operator=(const AudioComponent& other)
{
	if (this == &other)
	{
		return *this;
	}
	//copying the contents of other to the current object using the memcpy function
	memcpy(this, &other, sizeof(other));
	return *this;
}

void AudioComponent::Start()
{
	

}

void AudioComponent::Update()
{
	//std::cout << "The Audio component of " << myObject->getName() << " is updating" << std::endl;
	
}


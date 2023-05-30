#pragma once

#include "Common.h"
#include "Component.h"

/*
 * Audio is one of our most vanilla component
 * 
 */

class AudioComponent : public Component 
{
public:

    //constructor that takes a pointer to a GameObject and a Subsystem and passes them to the Component base class constructor
	inline AudioComponent(GameObject* myObject_, Subsystem* mySystem_) : Component(ComponentType::Audio, myObject_, mySystem_) {  };
	//copy constructor that takes another AudioComponent and creates a new AudioComponent with the same data, copy constructors are used a lot in the project
	inline AudioComponent(const AudioComponent& other) : Component(other), music(other.music) {};
	//assignment operator that takes another AudioComponent and sets this AudioComponent data to be the same as the other
	AudioComponent& operator=(const AudioComponent& other);

    //loading a file for music from a given file path and set it as the audio component music
	inline void LoadMusic(std::string LoadPath) {
		if (!music->openFromFile(LoadPath))         
		{
			std::cout << "did not load music" << std::endl;
		}
	}
    //plays the audio component music
	inline void PlayMusic() { music->play(); };
    //component start and update functions, called on start and update
	void Start();
	void Update();


private:

    // pointer to an sf::Music object
	sf::Music* music = new sf::Music; // only ogg no mp3
};
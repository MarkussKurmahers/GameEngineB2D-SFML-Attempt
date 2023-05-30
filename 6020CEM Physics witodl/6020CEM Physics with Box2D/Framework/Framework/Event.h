#pragma once
#include "Common.h"

class GameObject;

/*
 * The Event class is basically a placeholder for everything we need in order to
 * resolve a specific event. It holds the memory addresses of any game objects that
 * are relevant to the event, it holds the list of systems who'll need to react to
 * the event, and we can add any other information we feel is necessary to the
 * resolution of the event.
 *
 */

class Event {
public:
	Event(EventType type_, std::vector<GameObject*> objects_, std::vector<SubsystemType> systems_) : type(type_), objects(objects_), systems(systems_) {};

	Event() { type = EventType::Unassigned; }

	Event(const Event& other) : type(other.type), objects(other.objects), systems(other.systems) {};

	Event& operator=(const Event& other) { if (this == &other) return *this; Event a(other.type, other.objects, other.systems); return a; };

	inline void assignType(EventType type_) { type = type_; }
	inline void assignObjects(std::vector<GameObject*> objects_) { objects = objects_; }
	inline void assignSystems(std::vector<SubsystemType> systems_) { systems = systems_; }

	EventType type;
	std::vector<GameObject*> objects;
	std::vector<SubsystemType> systems;

};
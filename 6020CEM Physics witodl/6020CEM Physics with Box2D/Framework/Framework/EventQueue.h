#pragma once
#include "Common.h"
#include "Event.h"


class EventQueue
{
public:
	//a constructor that initialises the function maps
	EventQueue() { InitialiseFunctionMaps(); }
	//a vector of pointers to Events in the queue
	std::vector<Event*> events;

	//removes the specified Event pointer from the queue
	void popEvent(Event* event_);
	//map of function pointers to handle Events
	std::unordered_map<SubsystemType, std::unordered_map<EventType, void(*)(Event*)>*> functionMap;
	//initiates the function maps 
	void InitialiseFunctionMaps();
	//a vector of pointers to the function maps
	std::vector< std::unordered_map<EventType, void(*)(Event*)>*> functionMaps;
};
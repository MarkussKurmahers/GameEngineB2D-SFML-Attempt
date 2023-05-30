#pragma once
#include "Common.h"
#include "ParentSubsystem.h"

//Defining a 2D vector struct with two float values

struct Vector2 {
	float x;
	float y;
};
//defining a struct for physics data, including a packet type and an array of two Vector2 positions
struct PhysicsData {
	int packetType = 1;
	Vector2 positions[2];
};
// defining different structs with different variables
struct ClientData {
	int packetType = 0;
	int clientIndex;
};

struct ClientPacket {
	int clientIndex;
	Vector2 position;
};



class NetworkSubsystem
{
public:
	NetworkSubsystem(EventQueue* eQ_, std::vector<GameObject*>* gameObjects_)  {
	//initializing positions
		Pos = b2Vec2(0, 0);
		OtherPos = b2Vec2(OtherPos);
		// initalizing pointers to enet structs
		client = new ENetHost(); 
		peer = new ENetPeer();
		serverData = new PhysicsData;
		clientData = new ClientData;
		packetType = new int;
		clientPacket = new ClientPacket;
		dataPacket = new ENetPacket();
		newPosition = new Vector2;
	};
	//destructor, destroying ENet structs and deinitializing
	~NetworkSubsystem() {
		enet_host_destroy(client);
		atexit(enet_deinitialize);
	};

	void Start();
	void Update();
	// public variables for positions for different gameobjects 
	b2Vec2 Pos,OtherPos;


private:
	//private variables for ENet structs and pointers to data
	ENetAddress address;
	ENetHost* client;
	ENetPeer* peer;
	ENetEvent enetEvent;
	Vector2* newPosition;
	PhysicsData* serverData;
	ClientData* clientData;
	int* packetType;
	ClientPacket* clientPacket;
	ENetPacket* dataPacket;
	int clientIndex = -1;
};

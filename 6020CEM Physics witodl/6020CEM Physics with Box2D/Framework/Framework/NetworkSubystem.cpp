#include "NetworkSubystem.h"


/*
In Start(), the ENet library is initialized and a client is created. The client is set to connect to the local host on port 1234.
If there is an error during initialization or if the client is unable to connect to the specified host, an error message is printed to the console.
In Update(), the enet_host_service() function is used to handle any incoming network events on the client.
If a packet is received, the packet type is checked to determine its contents. If the packet type is 0, it contains client data that is stored in a buffer called clientData.
If the packet type is 1, it contains physics data that is stored in a buffer called serverData.
The position of other clients in the game is then updated based on the received physics data.
*/



void NetworkSubsystem::Start()
{
	if (enet_initialize() != 0)
	{
		std::cout << "Enet failed to initialise!" << std::endl;
	}


	client = enet_host_create(NULL, 1, 2, 0, 0);

	if (client == NULL)
	{
		std::cout << "Client failed to initialise!" << std::endl;
	}

	enet_address_set_host(&address, "localhost");
	address.port = 1234;


	peer = enet_host_connect(client, &address, 2, 0);

	if (peer == NULL) {
		std::cout << "No available peers for initializing an ENet connection." << std::endl;;
	}

	*packetType = -1;


	
}

void NetworkSubsystem::Update()
{
	if (enet_host_service(client, &enetEvent, 0) > 0)
	{
		switch (enetEvent.type) {
		case ENET_EVENT_TYPE_RECEIVE:

			memcpy(packetType, enetEvent.packet->data, sizeof(int));

			if (*packetType == 0)
			{
				std::cout << "Packet Received!\n";
				memcpy(clientData, enetEvent.packet->data, sizeof(ClientData));
				clientIndex = clientData->clientIndex;
			}
			else if (*packetType == 1)
			{
				memcpy(serverData, enetEvent.packet->data, sizeof(PhysicsData));
				for (int i = 0; i < 2; i++)
				{
					if (i != clientIndex)
					{
						Pos = b2Vec2(serverData->positions[i].x, serverData->positions[i].y);
					}
				}
			}

			//break;
			std::cout << "Packet received!\n";
			memcpy(newPosition, enetEvent.packet->data, enetEvent.packet->dataLength);
			std::cout << newPosition->x << "," << newPosition->y << "\n";
			Pos = b2Vec2(newPosition->x, newPosition->y);
			break;
		}
	}

	
	/*	
		clientPacket->clientIndex = clientIndex;
		clientPacket->position.x = OtherPos.x;
		clientPacket->position.y = OtherPos.y;

		dataPacket = enet_packet_create(clientPacket, sizeof(ClientPacket), ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, dataPacket);
	*/

		
	

}

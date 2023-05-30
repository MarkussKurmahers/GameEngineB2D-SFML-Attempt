#pragma once
#include <unordered_map>
#include <vector>
#include <array>
#include <iostream>
#include <string>
#include <Box2D/Box2D.h>
#include <SFML\Graphics.hpp>
#include <stdlib.h>
#include <SFML/Audio.hpp>
#include <map>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <math.h>
#include <enet\enet.h>


//Common.h holds most includes coming from packages and different enum classes, as well as max entity count
// in order to avoid certain errors and this makes lives easier, by just having o include Common.h

enum class EventType { MoveUp, MoveUpLeft, MoveUpRight,  MoveDown, MoveDownLeft, MoveDownRight, MoveLeft, MoveRight, Exit, Unassigned };
enum class SubsystemType { Graphics, Physics, Input, Audio ,AI, Unassigned };
enum class ComponentType { Graphics, Physics, Input, Audio,AI, Unassigned };
enum class BehaviourType { Patrol, Hunt, Unassigned }; // not that necessary right now

#define MAX_ENTITIES 3
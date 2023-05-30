#pragma once
#include "Common.h"
#include "Component.h"

class GraphicsComponent : public Component
{
public:

	inline GraphicsComponent(GameObject* myObject_, Subsystem* mySystem_) : Component(ComponentType::Graphics, myObject_, mySystem_) {
		circle = new sf::CircleShape();
		rectangleShape = new sf::RectangleShape();
		texture = new sf::Texture();
		//Shape = new sf::Shape();
	};
	inline GraphicsComponent(const GraphicsComponent& other) : Component(other), circle(other.circle), rectangleShape(other.rectangleShape), texture(other.texture), Shape(other.Shape) {};

	GraphicsComponent& operator=(const GraphicsComponent& other);

	void Update();

	// Types of getter and setter functions in order to achieve functionality, when creating something in Gameengine.cpp
	sf::CircleShape* GetCircle() { return circle; };
	sf::Shape* GetShape() { return Shape; };
	inline void SetRadius(float _radius) { circle->setRadius(_radius); circle->setOrigin(_radius, _radius); };
	inline void SetPosition(sf::Vector2f pos) { Position = pos; };

	inline void SetShapeColor(sf::Color color) { Shape->setFillColor(color); };
	inline void SetRectShapeSize(sf::Vector2f size) { rectangleShape->setSize(size); rectangleShape->setOrigin(size.x/2.f, size.y/2.f); };

	inline void SetShapeCircle() { Shape = circle; };
	inline void SetShapeRectangle() { Shape = rectangleShape; };

	

	inline void SetTexture(std::string path) {
		texture->loadFromFile(path);
		Shape->setTexture(texture);
	};
	
private:
	sf::CircleShape* circle; // addition
	sf::RectangleShape* rectangleShape; //addition
	sf::Shape* Shape; //placeholder
	std::string TexturePath;// possibly add textures later
	sf::Texture* texture;
	sf::Vector2f Position;
	float rotation;
	
};
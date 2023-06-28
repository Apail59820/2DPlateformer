#pragma once

#include <SFML/Graphics.hpp>

class GWorldObject
{
public :

	virtual ~GWorldObject() {

	}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	
	sf::FloatRect GetCollision() const
	{
		return m_collisionBox;
	}

private : 
	sf::Sprite m_sprite;
	sf::Texture m_texture;

	sf::FloatRect m_collisionBox;
	
};
#pragma once

#include <SFML/Graphics.hpp>

#include "Debug.hpp"

class GActor
{
public :

	virtual ~GActor() 
	{
		Dbg::Log("[GActor.GActor]\t:\tGActor Virtual DTor called.");
	}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual void SetWindowRef(sf::RenderWindow* _window)
	{
		m_window = _window;
	}

protected : 

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::RenderWindow* m_window;

private :

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_sprite, states);
    }

};
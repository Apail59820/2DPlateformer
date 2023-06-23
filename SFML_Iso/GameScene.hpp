#pragma once

#include "GActor.hpp"
#include <vector>
#include <map>

#include "Debug.hpp"

class GScene
{
public :
	
	enum Action { Attack, UseItem };

	virtual ~GScene()
	{
		Dbg::Log("[GScene.Gscene]\t:\tGscene Virtual DTor Called.");
	}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual void LoadActors() = 0;

	virtual void SetWindowRef(sf::RenderWindow* _window)
	{
		m_window = _window;
	}

protected : 

	std::map<sf::Keyboard::Key, Action> m_keyBindings;

	std::vector<std::shared_ptr<GActor>> m_gameActors;

	sf::RenderWindow* m_window;
};
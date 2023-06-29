#pragma once

#include "GActor.hpp"
#include <vector>
#include <map>

#include <tmx/MapLoader.hpp>

#include "Debug.hpp"

class GScene
{
public :

	virtual ~GScene()
	{
		Dbg::Log("[GScene.Gscene]\t:\tGscene Virtual DTor Called.");
	}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual void LoadActors() = 0;

	void SetWindowRef(sf::RenderWindow* _window)
	{
		m_window = _window;
	}

protected : 

	std::vector<std::shared_ptr<GActor>> m_gameActors;

	sf::RenderWindow* m_window;

	std::shared_ptr<tmx::MapLoader> m_mapLoader;
};
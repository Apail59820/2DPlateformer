#pragma once

#include <SFML/Graphics.hpp>
#include "ProcessEvents.hpp"

#include "GPlayerActor.hpp"
#include "Scenes.hpp"

class GameEngineCore
{
public :

	GameEngineCore();

	void Init();

	void Update();
	void Render();

	bool IsRunning();

	void LoadScene();

private : 

	int m_windowWidth;
	int m_windowHeight;
	std::string m_windowTitle;

	sf::RenderWindow m_window;

	EventsCore m_eventsCore;
	
	std::unique_ptr<GScene> m_currentScene;
};
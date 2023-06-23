#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>

#include "Debug.hpp"
#include "EventManager.hpp"


class EventsCore
{
public :

	void Init(sf::RenderWindow* pWindow);

	/*
		Event structs are used to avoid creating structs in memory every tick.
		Because events are processed in the main GameCore loop.
		So when we finish polling events, we have to clear the structs to avoid keeping previous values.
	*/
	void ResetMemberStructs();

	void EnableKeyboardReading();
	void DisableKeyboardReading();

	void ProcessEvents();

	GWindowEvent* PGetWindowEvents() const;

	std::string GetUserKeyboardTextEntered() const;

private :

	sf::Event m_eventLog;
	sf::RenderWindow* m_pParentWindow;

	GWindowEvent m_sWindowEvent;
	GMouseEvent m_sMouseEvent;
	GKeyboardEvent m_sKeyboardEvent;

	std::string m_keyboardInput;
	bool m_isKeyboardListening;
};
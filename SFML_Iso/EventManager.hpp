#pragma once

#include <SFML/Graphics.hpp>


struct GWindowEvent
{
	bool Closed = false;
	bool Resized = false;
	bool GainedFocus = false;
	bool LostFocus = false;
	int newSizeHeight = 0;
	int newSizeWidth = 0;
};

struct GMouseEvent
{
	bool WheelScrolled = false;
	sf::Mouse::Wheel WheelType = static_cast<sf::Mouse::Wheel>(0);

	int Wheel_x = 0;
	int Wheel_y = 0;
	float WheenMovement = 0.0f;
};

struct GKeyboardEvent
{
	bool TextEntered = false;
	char LastCharacterEntered = 0;

	bool KeyPressed = false;
	bool KeyReleased = false;
	sf::Keyboard::Key KeyCode = static_cast<sf::Keyboard::Key>(0);

	bool CtrlKeyState = false;
	bool AltKeyState = false;
	bool ShiftKeyState = false;
	bool SystemKeyState = false;
};

namespace EventManager
{
	inline	GWindowEvent	*WindowEvent   = nullptr;
	inline	GMouseEvent		*MouseEvent    = nullptr;
	inline	GKeyboardEvent  *KeyboardEvent = nullptr;
}
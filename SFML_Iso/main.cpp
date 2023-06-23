#include <iostream>
#include <SFML/Graphics.hpp>

#include "GameCore.hpp"

int main()
{
	GameEngineCore gameEngineCore;

	gameEngineCore.Init();

	while (gameEngineCore.IsRunning())
	{
		gameEngineCore.Update();
		gameEngineCore.Render();
	}

	return 0;
}
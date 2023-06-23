#pragma once

#include "GameScene.hpp"
#include "GPlayerActor.hpp"

#include <iostream>

#include "Debug.hpp"

class SpawnScene : public GScene
{
public :

	SpawnScene();
	~SpawnScene();


	void Init();
	void Update();
	void Render();

	void LoadActors();

};
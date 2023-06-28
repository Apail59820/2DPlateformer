#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "GActor.hpp"
#include "GPlayerActorAnim_structs.hpp"

#include "Debug.hpp"
#include "EventManager.hpp"
#include "Utils.hpp"

class GPlayerActor : public GActor
{
public : 
	
	GPlayerActor();
	~GPlayerActor();

	void Init();
	void Update();
	void Render();

private :

	enum Dir {P_MOVE_RIGHT, P_MOVE_LEFT};

	void PlayAnimation();
	void ProcessPlayerInputEvents();

	void Attack();
	void Move();

	GAnim * m_currentAnimation, *m_previousAnimation;
	std::vector<GAnim*> m_animationQueue;


	sf::Vector2i m_spriteSize, m_spriteSheetSize;
	sf::Vector2i m_spriteOccurences;

	bool m_bIsMoving;
	int m_currentAttack;


	bool m_bStoppedMoving;   //////////////////
	bool m_bStartedMoving;   // For Animation to play correctly
	bool m_bIsAttacking;     //////////////////


	float m_moveSpeed;
	float m_currentSpeed;
	float m_maxSpeed;

	Dir m_movementDirection;

	int m_currentAnimFrame;
	sf::Vector2i m_currentAnimFramePos;

	sf::Clock m_animClock;
	sf::Clock m_timeSinceLastAttack;
};
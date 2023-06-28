#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Audio.hpp>


#include "GActor.hpp"
#include "GPlayerActorAnim_structs.hpp"

#include "Debug.hpp"
#include "EventManager.hpp"
#include "Utils.hpp"
#include "GWorld.h"

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
	void CheckCollisions();

	void Attack();
	void Move();

	sf::SoundBuffer m_sSwordSwoosh[3];
	sf::Sound m_sSound_Emitter;


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

	float m_gravityForce;
	float m_currentGravityForceApplied;
	float m_maxGravityForceApplication;

	Dir m_movementDirection;

	int m_currentAnimFrame;
	sf::Vector2i m_currentAnimFramePos;

	sf::Clock m_animClock;
	sf::Clock m_timeSinceLastAttack;

	sf::RectangleShape m_collisionBox;
};
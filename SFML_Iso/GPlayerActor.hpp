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
	bool IsColliding();
	bool IsGrounded();

	void Attack();
	void Move();
	void Jump();

	sf::SoundBuffer m_sSwordSwoosh[3];
	sf::Sound m_sSound_Emitter;


	GAnim * m_currentAnimation, *m_previousAnimation;
	std::vector<GAnim*> m_animationQueue;


	sf::Vector2i m_spriteSize, m_spriteSheetSize;
	sf::Vector2i m_spriteOccurences;

	sf::Vector2f m_previousPos, m_outerCollisionPreviousPos;

	bool m_bIsMoving;
	bool m_bIsGrounded;
	bool m_bIsColliding;
	bool m_bIsJumping;

	int m_currentAttack;


	bool m_bStoppedMoving;   //////////////////
	bool m_bStartedMoving;   // For Animation to play correctly
	bool m_bHasJumped;
	bool m_bWasRunningBeforeJumping;
	bool m_bIsAttacking;     //////////////////


	float m_moveSpeed, m_jumpHeight, m_jumpForce, m_jumpForceApplied;
	sf::Vector2f m_velocity;
	float m_maxSpeed;

	float m_gravityForce;
	float m_currentGravityForceApplied;
	float m_maxGravityForceApplication;

	Dir m_movementDirection;

	int m_currentAnimFrame;
	sf::Vector2i m_currentAnimFramePos;

	sf::Clock m_animClock;
	sf::Clock m_timeSinceLastAttack;

	sf::RectangleShape m_outerCollisionBox;

	sf::Vector2f m_groundedPoint;
};
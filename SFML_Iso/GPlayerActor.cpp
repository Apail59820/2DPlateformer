#include "GPlayerActor.hpp"


GPlayerActor::GPlayerActor()
{
	m_currentAnimation = &GPlayerActor_Anim::JUMP;
	m_previousAnimation = nullptr;

	m_velocity = sf::Vector2f(0.0f, 0.0f);
	m_moveSpeed = 0.005f;
	m_maxSpeed = 0.09f;
	m_jumpForce = 0.005f;
	m_jumpHeight = 1.9f;

	m_jumpForceApplied = 0.0f;
	m_currentGravityForceApplied = 0.0f;
	m_gravityForce = 0.002f;
	m_maxGravityForceApplication = 0.15f;

	m_currentAttack = 0;

	m_bIsMoving = false;
	m_bStoppedMoving = true;
	m_bStartedMoving = false;
	m_bIsAttacking = false;
	m_bIsJumping = false;
	m_bWasRunningBeforeJumping = false;

	m_movementDirection = P_MOVE_RIGHT;

	m_spriteSize = sf::Vector2i(50, 37);
	m_spriteOccurences = sf::Vector2i(7, 16);

	m_spriteSheetSize = sf::Vector2i(m_spriteSize.x * m_spriteOccurences.x,
									 m_spriteSize.y * m_spriteOccurences.y);


	m_currentAnimFrame = m_currentAnimation->Start;

	Dbg::Log("[GPlayerActor]     :     GPlayerActor CTOR called.");
}

GPlayerActor::~GPlayerActor()
{
	Dbg::Log("[GPlayerActor]     :     GPlayerActor DTOR called.");
}

void GPlayerActor::Init()
{
	std::string t_TexturePath = "../Assets/Player/psheet.png";
	std::string s_SoundBufferPaths[3] = {"../Assets/Sounds/sword_swoosh_01.mp3",
		                                 "../Assets/Sounds/sword_swoosh_02.mp3",
		                                 "../Assets/Sounds/sword_swoosh_03.mp3" };

	for (auto i = 0; i < 3; ++i)
	{
		if (!m_sSwordSwoosh[i].loadFromFile(s_SoundBufferPaths[i])) {
			Dbg::Log("[GPlayerActor.Init]     :     Could not load sound (\'%s\').", s_SoundBufferPaths[i]);
		}
	}

	if (!m_texture.loadFromFile(t_TexturePath))
		Dbg::Log("[GPlayerActor.Init]     :     Could not load texture (\'%s\').", t_TexturePath);


	m_sprite.setPosition(sf::Vector2f(100, 100));
	m_sprite.setOrigin(sf::Vector2f(static_cast<float>(m_spriteSize.x) / 2, static_cast<float>(m_spriteSize.y) / 2));
	m_sprite.setTexture(m_texture);

	// So it wont print the whole sprite sheet on the first frame
	m_sprite.setTextureRect(sf::IntRect((m_spriteSize.x * GPlayerActor_Anim::IDLE.Start),
		                                (m_spriteSize.y * abs(GPlayerActor_Anim::IDLE.Start / m_spriteOccurences.x)), 
		                                 m_spriteSize.x, m_spriteSize.y));

	m_outerCollisionBox.setSize(sf::Vector2f(10,24));
}

void GPlayerActor::Update()
{ 
	if (m_timeSinceLastAttack.getElapsedTime().asMilliseconds() >= 1200)
	{
		m_currentAttack = 0;
		m_timeSinceLastAttack.restart();
	}

	
	m_outerCollisionBox.setPosition(
	sf::Vector2f(m_sprite.getPosition().x - 5,
				 m_sprite.getPosition().y - 11)
	);

	m_groundedPoint = sf::Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y + 18);

	if (NGWorld::GMap != nullptr && NGWorld::GMap)
	{
		NGWorld::GMap->updateQuadTree(m_outerCollisionBox.getGlobalBounds());
	}

	ProcessPlayerInputEvents();
	PlayAnimation();
	Move();
}

void GPlayerActor::Render()
{
	m_window->draw(m_sprite);
}

void GPlayerActor::PlayAnimation()
{
	if (m_animClock.getElapsedTime().asMilliseconds() <= 100)
		return;

	m_animClock.restart();

	if (m_animationQueue.size() && m_currentAnimation->IsSkippable)
	{
		m_currentAnimation = m_animationQueue[0];
		m_animationQueue.erase(m_animationQueue.begin());
		m_currentAnimFrame = m_currentAnimation->Start;
	}

	if (m_currentAnimFrame < m_currentAnimation->Stop)
		++m_currentAnimFrame;
	else
	{
		if (m_currentAnimation->isLoop)
		{
			if (!m_animationQueue.size())
			{
				m_currentAnimFrame = m_currentAnimation->Start;
			}
			else
			{
				m_previousAnimation = m_currentAnimation;
				m_currentAnimation = m_animationQueue[0];
				m_animationQueue.erase(m_animationQueue.begin());
				m_currentAnimFrame = m_currentAnimation->Start;
			}
		}
		else
		{
			if (GPlayerActor_AnimSequence::GetNextAnim(m_currentAnimation->AnimStateID)->AnimStateID == GPlayerActor_AnimStates::PreviousState)
			{
				if (m_previousAnimation) {
					m_currentAnimation = m_previousAnimation;
				}
				else
				{
					Dbg::Log("[GPlayerActor.PlayAnimation]\t:\t m_previousAnimation is NULLPTR. Switching to idle.");
					m_currentAnimation = &GPlayerActor_Anim::IDLE;
					m_currentAnimFrame = m_currentAnimation->Start;
				}
			}
			else
			{
				m_currentAnimation = GPlayerActor_AnimSequence::GetNextAnim(m_currentAnimation->AnimStateID);
				m_currentAnimFrame = m_currentAnimation->Start;
			}
		}
	}

	m_currentAnimFramePos.x = m_spriteSize.x * m_currentAnimFrame;
	m_currentAnimFramePos.y = m_spriteSize.y * abs(m_currentAnimFrame / m_spriteOccurences.x);

	while (m_currentAnimFramePos.x >= m_spriteSheetSize.x) {
		m_currentAnimFramePos.x -= m_spriteSheetSize.x;
	}



	m_sprite.setTextureRect(sf::IntRect(m_currentAnimFramePos.x, m_currentAnimFramePos.y, m_spriteSize.x, m_spriteSize.y));
}

void GPlayerActor::ProcessPlayerInputEvents()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
		m_bIsMoving = true;
		m_movementDirection = P_MOVE_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		m_bIsMoving = true;
		m_movementDirection = P_MOVE_RIGHT;
	}
	else {
		m_bIsMoving = false;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		Jump();
	
	if (EventManager::KeyboardEvent->KeyPressed)
	{
		if (EventManager::KeyboardEvent->KeyCode == sf::Keyboard::E)
			if (!m_bIsMoving)
				Attack();
	}
}

bool GPlayerActor::IsColliding()
{
    if (NGWorld::GMap != nullptr && NGWorld::GMap)
	{
		const auto& layers = NGWorld::GMap->getLayers();

		for (const auto& layer : layers)
		{
			if (layer.name == "Collision")
			{
				for (const auto& object : layer.objects)
				{
					if (object.getAABB().intersects(m_outerCollisionBox.getGlobalBounds()))
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool GPlayerActor::IsGrounded()
{
	if (NGWorld::GMap != nullptr && NGWorld::GMap)
	{
		const auto& layers = NGWorld::GMap->getLayers();

		for (const auto& layer : layers)
		{
			if (layer.name == "Collision")
			{
				for (const auto& object : layer.objects)
				{
					if (object.contains(m_groundedPoint)) {
						return true;
					}
				}
			}
		}
	}

	return false;
}

void GPlayerActor::Move()
{
	if (!IsGrounded() && !m_bIsJumping)
	{
		m_currentGravityForceApplied = utils::Lerp(m_currentGravityForceApplied, m_maxGravityForceApplication, m_gravityForce);

		if (m_currentGravityForceApplied > m_maxGravityForceApplication) {
			m_currentGravityForceApplied = m_maxGravityForceApplication;
		}


		m_sprite.move(0, m_currentGravityForceApplied);
	}
	else
	{
		if (m_bIsJumping)
		{
			if (!m_bHasJumped)
			{
				m_currentAnimation = &GPlayerActor_Anim::JUMP;
				m_currentAnimFrame = m_currentAnimation->Start;
				m_bHasJumped = true;
			}
			m_jumpForceApplied = utils::Lerp(m_jumpForceApplied, m_jumpHeight, m_jumpForce);
			m_sprite.move(0, -m_jumpForceApplied);
			if (m_jumpForceApplied >= m_jumpHeight - 1.0f)
			{
				
				m_jumpForceApplied = 0.0f;
				m_bIsJumping = false;
				m_bHasJumped = false;
				if (m_bWasRunningBeforeJumping)
				{
					if (!m_animationQueue.size())
						m_animationQueue.push_back(&GPlayerActor_Anim::RUN);
				}
				else
				{
					if (!m_animationQueue.size())
						m_animationQueue.push_back(&GPlayerActor_Anim::IDLE);
				}
			}
		}

		m_velocity.y = 0.0f;
		m_currentGravityForceApplied = .0f;
	}

	if (!m_bIsMoving)
	{
		if (m_currentAnimation != &GPlayerActor_Anim::IDLE && !m_bStoppedMoving)
		{
			if (m_currentAnimation->IsSkippable)
			{
				m_currentAnimation = &GPlayerActor_Anim::IDLE;
				m_currentAnimFrame = m_currentAnimation->Start;
				
			}
			else
			{
				if (!m_animationQueue.size())
					m_animationQueue.push_back(&GPlayerActor_Anim::IDLE);
			}
			m_bStoppedMoving = true;
			m_bStartedMoving = false;
		}

		m_velocity.x = 0.0f;
		return;
	}

	m_bStoppedMoving = false;

	if (m_currentAnimation != &GPlayerActor_Anim::RUN && !m_bStartedMoving)
	{
		if (m_currentAnimation->IsSkippable)
		{
			m_currentAnimation = &GPlayerActor_Anim::RUN;
			m_currentAnimFrame = m_currentAnimation->Start;
		}
		else
		{
			if(!m_animationQueue.size())
				m_animationQueue.push_back(&GPlayerActor_Anim::RUN);

		}
		m_bStartedMoving = true;
	}

	m_velocity.x = utils::Lerp(abs(m_velocity.x), m_maxSpeed, m_moveSpeed);
	
	//collision prediction
	m_outerCollisionPreviousPos = m_outerCollisionBox.getPosition();
	m_outerCollisionBox.move(m_movementDirection == P_MOVE_LEFT ? -m_velocity.x * 4: m_velocity.x * 4, 0.0f);
	m_bIsColliding = IsColliding();
	m_outerCollisionBox.setPosition(m_outerCollisionPreviousPos);


	if (m_bIsColliding)
		m_velocity.x = 0.0f;
		

	switch (m_movementDirection)
	{
	case P_MOVE_LEFT:
		m_velocity.x = -m_velocity.x;
		m_sprite.setScale(-1.0f, 1.0f);
		break;
	case P_MOVE_RIGHT:
		m_sprite.setScale(1.0f, 1.0f);
		break;
	default:
		Dbg::Log("[-] [GPlayerActor::Move]\t:\tUnknown value for \'_dir\'");
		break;
	}


	
	m_sprite.move(m_velocity);
}

void GPlayerActor::Attack()
{
	if (m_timeSinceLastAttack.getElapsedTime().asMilliseconds() >= 200)
	{
		if (m_currentAttack == 0 || m_currentAttack == 2)
		{
			m_currentAttack = 1;
			m_currentAnimation = &GPlayerActor_Anim::ATK1;
			m_currentAnimFrame = m_currentAnimation->Start;
			m_sSound_Emitter.setBuffer(m_sSwordSwoosh[std::rand() % 3 ]);
			m_sSound_Emitter.play();
			m_timeSinceLastAttack.restart();
		} 
		else if (m_currentAttack == 1)
		{
			m_currentAnimation = &GPlayerActor_Anim::ATK2;
			m_currentAnimFrame = m_currentAnimation->Start;
			m_currentAttack = 2;
			m_sSound_Emitter.setBuffer(m_sSwordSwoosh[std::rand() % 3]);
			m_sSound_Emitter.play();
			m_timeSinceLastAttack.restart();
		}
	}
}

void GPlayerActor::Jump()
{
	if (!m_bIsJumping && IsGrounded()) {
		m_bIsJumping = true;
		m_bWasRunningBeforeJumping = m_bIsMoving;
	}
}

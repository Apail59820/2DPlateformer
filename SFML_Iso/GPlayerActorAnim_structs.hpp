#pragma once

#include "GAnimation.hpp"

namespace GPlayerActor_AnimStates
{
	enum PlayerAnimations { Idle, SwordIdle, Run, SCrouch_Sword, Crouch, SwordCrouch, Atk1, Atk2, Atk3, Jump, SwordDraw, SwordSheathe, PreviousState};
}

namespace GPlayerActor_Anim
{
	inline GAnim IDLE			{ 0, 3, true, false, false, GPlayerActor_AnimStates::Idle, true};
	inline GAnim SWORD_IDLE     { 61, 63, true , false, false, GPlayerActor_AnimStates::SwordIdle, true };

	inline GAnim RUN			{ 8, 13, true, false, false, GPlayerActor_AnimStates::Run, true };

	inline GAnim CROUCH			{ 4, 7, true, false, false, GPlayerActor_AnimStates::Crouch, true};

	inline GAnim S_CROUCH_SWORD { 61, 62, false, false, false, GPlayerActor_AnimStates::SCrouch_Sword, false };
	inline GAnim SWORD_CROUCH   { 63, 65, true, false, false, GPlayerActor_AnimStates::SwordCrouch, true };

	inline GAnim ATK1			{ 42, 47, false, false, false, GPlayerActor_AnimStates::Atk1, true };
	inline GAnim ATK2			{ 48, 52, false, false, false, GPlayerActor_AnimStates::Atk2, true };
	inline GAnim ATK3			{ 55, 58, false, false, false, GPlayerActor_AnimStates::Atk3, false };

	inline GAnim JUMP			{ 16, 21, false, false, false, GPlayerActor_AnimStates::Jump, false };
	  
	inline GAnim SWORD_DRAW	    { 69, 73, false, false, false,GPlayerActor_AnimStates::SwordDraw, false };
	inline GAnim SWORD_SHEATHE	{ 74, 76, false, false, false, GPlayerActor_AnimStates::SwordSheathe, false };

	inline GAnim PREVIOUS_STATE{ 0, 0, false, false, false, GPlayerActor_AnimStates::PreviousState, false  };
}

namespace GPlayerActor_AnimSequence
{
	inline GAnim* GetNextAnim(int /*GPlayerActor_AnimStates::PlayerAnimations*/ current_State)
	{
		switch (current_State)
		{
		case GPlayerActor_AnimStates::SCrouch_Sword:
			return &GPlayerActor_Anim::SWORD_CROUCH;
			break;
		case GPlayerActor_AnimStates::Atk1:
			return &GPlayerActor_Anim::SWORD_IDLE;
			break;
		case GPlayerActor_AnimStates::Atk2:
			return &GPlayerActor_Anim::SWORD_IDLE;
			break;
		case GPlayerActor_AnimStates::Atk3:
			return &GPlayerActor_Anim::SWORD_IDLE;
			break;
		case GPlayerActor_AnimStates::Jump:
			return &GPlayerActor_Anim::PREVIOUS_STATE;
			break;
		case GPlayerActor_AnimStates::SwordIdle:
			return &GPlayerActor_Anim::SWORD_SHEATHE;
			break;
		default:
			Dbg::Log("[GPlayerActor_AnimSequence::GetNextAnim]\t:\tCurrent State is Loopable, switching to IDLE state.");
			return &GPlayerActor_Anim::IDLE;
			break;
		}
	}
}

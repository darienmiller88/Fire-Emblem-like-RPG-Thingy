#pragma once
#include "Skill.h"

class Unit;

class Aether : public Skill{
	public:
		Aether();
		void setSkillLikelyHood(const Unit &player);
		void activate(Unit &player, Unit &enemy) override;
};


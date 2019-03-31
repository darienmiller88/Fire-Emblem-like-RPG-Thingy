#pragma once
#include "Skill.h"

class RendHeaven : public Skill{
	public:
		RendHeaven();
		void setSkillLikelyHood(const Unit &player) override;
		void activate(const Unit &player, Unit &enemy) override;
};


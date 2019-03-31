#pragma once
#include "Skill.h"

class Sol : public Skill{
	public:
		Sol();
		void setSkillLikelyHood(const Unit &player) override;
		void activate(Unit &player, Unit &enemy) override;
};


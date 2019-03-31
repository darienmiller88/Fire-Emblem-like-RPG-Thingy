#pragma once
#include "Skill.h"

class Vengeance : public Skill{
	public:
		Vengeance();
		void setSkillLikelyHood(const Unit &player) override;
		void activate(const Unit &player, Unit &enemy) override;
};


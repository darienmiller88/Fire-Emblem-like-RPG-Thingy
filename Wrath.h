#pragma once
#include "Skill.h"

class Wrath : public Skill{
	public:
		Wrath();
		bool isActivated(const Unit &player) const override;
		void setSkillLikelyHood(const Unit &player) override;
		void activate(Unit &player, Unit &enemy) override;
	private:
		bool wasSkilledActivated;
};


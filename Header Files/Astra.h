#ifndef ASTRA_H
#define ASTRA_H
#include "Skill.h"
#include <iostream>

class Astra : public Skill{
	public:
		Astra();
		void setSkillLikelyHood(const Unit &player) override;
		void activate(const Unit &player, Unit &enemy) override;
};

#endif
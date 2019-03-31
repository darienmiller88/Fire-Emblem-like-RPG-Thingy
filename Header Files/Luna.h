#ifndef LUNA_H
#define LUNA_H

#include "Skill.h"

class Luna : public Skill{
	public:
		Luna();
		void setSkillLikelyHood(const Unit &player) override;
		void activate(const Unit &player, Unit &enemy) override;
};

#endif // !1




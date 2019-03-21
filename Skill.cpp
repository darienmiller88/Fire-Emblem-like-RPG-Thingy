#include "Skill.h"
#include <iostream>
Skill::Skill(const std::string &skillName, const skillType &s) : skillName(skillName), s(s) {
}

int Skill::getLikelyHood() const{
	return likelyHood;
}

std::string Skill::getSkillName() const{
	return skillName;
}

skillType Skill::getSkillType() const{
	return s;
}

void Skill::activate(Unit &player, Unit &enemy)
{
}

void Skill::activate(const Unit &player, Unit &enemy)
{
}

bool Skill::isActivated(const Unit & player) const{
	return random(0, 100) < likelyHood;
}

int Skill::random(int min, int max) const{
	std::random_device seed;
	std::default_random_engine rnGen(seed());
	std::uniform_int_distribution<int> dist(min, max);

	return dist(rnGen);
}

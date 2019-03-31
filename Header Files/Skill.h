#ifndef SKILL_H
#define SKILL_H

//a forward declaration for the Unit class is needed here to prevent a circular dependency whereby a Skill subclass includes Skill.h, Unit.h
//includes every skill, and then Skill.h tries to include Unit.h.
class Unit;

#include <string>
#include <random>

//In this simulator of Fire Emblem, there will be two different types of skills which will allow the Unit.cpp to know which activate()
//member function in this file to call. The activate() function  that takes two mutable Unit objects will be overridden by a "TWO_WAY_COMBAT"
//Skill subclass and The activate() function that takes a const Unit and a mutable unit will be overridden by a "ONE_WAY_COMBAT" Skill subclass.
enum class skillType {
	ONE_WAY_COMBAT, TWO_WAY_COMBAT
};

/*
* This abstract class will serve as a template for subsequent subclasses to use to define the basic functionality of what a Fire Emblem skill
* is.
*/
class Skill{
	public:
		Skill(const std::string &skillName, const skillType &s);
		int getLikelyHood() const;
		std::string getSkillName() const;
		skillType getSkillType() const;
		
		virtual void activate(Unit &player, Unit &enemy);
		virtual void activate(const Unit &player, Unit &enemy);
		virtual bool isActivated(const Unit &player) const;
		virtual void setSkillLikelyHood(const Unit &player) = 0;
	protected:
		int random(int min, int max) const;
		int likelyHood;
		std::string skillName;
		skillType s;
};

#endif // !1


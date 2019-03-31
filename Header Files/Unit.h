#ifndef UNIT_H
#define UNIT_H

#include "Aether.h"
#include "Astra.h"
#include "Luna.h"
#include "RendHeaven.h"
#include "Sol.h"
#include "Vengeance.h"
#include "Wrath.h"
#include "Weapon.h"
#include <array>
#include <random>
#include <iostream>
#include <memory>

/*
* Enum to determine whether or not a unit is an "enemy" or "player". I could have chose to forgo this hacky solution by making the Unit class
* abstract, and making a player and enemy class inherit from it, but since they do virtually the same things aside from how they level up,
* this would have been less code, and less files. 
*/
enum class unitTypes {
	ENEMY, PLAYER
};

/**
* This class will serve as a template for what defines a playable and fightable "Unit". Units will be able to attack other units, level up
*
*@ author Darien Miller
*
*/
class Unit{
	public:
		Unit(const std::string &name, const Weapon &weapon, const unitTypes &type, const Skill &s);
		//Unit &operator = (const Unit &otherUnit);
		int getCurrentHP() const;
		int getMaxHp() const;
		void levelUp();
		int getLevel() const;
		void attack(Unit &unit);
		int getTotalAttack() const;
		void addToCriticalRate(int newCritRate);
		void takeDamage(int damage);
		void recoverHP(int amountToRecover);
		std::string getName() const;
		std::array<int, 7> getStats() const;
		int getDamageDealtToEnemy(const Unit &enemy) const;
		bool calculateHit(const Unit &enemy) const;
		bool calculateCriticalHit(const Unit &enemy) const;
		friend std::ostream &operator << (std::ostream &os, const Unit &u);
	private:
		void activateUnitSkill(Unit &enemy);
		void adjustStatsAfterWeaponTriangle(Unit &enemy);
		int random(int min, int max) const;
		void calculateStats();
		std::string name;
		std::array<int, 7> stats;
		std::array<int, 7> growthRates;
		Skill *skill;
		Weapon weapon;
		const unitTypes type;
		const int MAX_HP;
		int level, hp, avoid, criticalAvoid, hitRate, totalAttack, criticalRate, criticalChance, exp;
		static int turnNumber;
};

#endif
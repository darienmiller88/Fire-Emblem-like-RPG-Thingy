#include "Unit.h"
#include <type_traits>
#include <memory>

int Unit::turnNumber = 1;

Unit::Unit(const std::string &name, const Weapon &weapon, const unitTypes &type, const Skill &s) : name(name), weapon(weapon),  type(type),
MAX_HP(100), hp(MAX_HP), level(1){

	for (int i = 0; i < stats.size(); i++) {
		stats[i] = random(20, 30);
		growthRates[i] = random(55, 80);
	}

	calculateStats();
	skill = const_cast<Skill*> (&s);
	skill -> setSkillLikelyHood(*this);
}


/*
Unit & Unit::operator=(const Unit &otherUnit){
	if (this != &otherUnit) {
		hp = otherUnit.hp;
		name = otherUnit.name;
		stats = otherUnit.stats;
		level = otherUnit.level;
		//skill = std::make_unique<Skill>(otherUnit.skill).get();

	}
	return *this;
}
*/


//Function to level up a player after killing an enemy. The if statement (this == playerAddress) refers to me only wanting tp print out 
//level up feedback to the screen when the player levels up, not the enemy (as this function will be shared
void Unit::levelUp(){
	std::array<std::string, 7> statNames{ "att", "mag", "skl", "spd", "lck", "def", "res" };

	hp = MAX_HP;//reset hp back to what it was before the battle
	hp += random(15, 20);

	if (type == unitTypes::PLAYER) {
		level++;
		std::cout << "Leveled up! level: " << level << "\n";
		std::cout << "HP went up by " << hp - MAX_HP << "!\n";
	}

	for (int i = 0; i < stats.size(); i++){
		if (random(0, 100) < growthRates[i]) {
			int statBuff = random(2, 4);
			if(type == unitTypes::PLAYER)
				std::cout << statNames[i] << " went up by " << statBuff << "!\n";
			stats[i] += random(2, 4);
		}
	}
}

int Unit::getLevel() const{
	return level;
}

int Unit::getCurrentHP() const{
	return hp;
}

int Unit::getMaxHp() const{
	return MAX_HP;
}

//This function will handle the entire battle phase between the player and the enemy
void Unit::attack(Unit &enemy){

	std::cout << "turn: " << turnNumber << "\n";
	std::cout << name << " attacked " << enemy.name << "!\n";

	//On the first turn, and only the first turn (as doing so after the first turn is unnecessary) calculate the player and the
	//enemy's stats after factoring in the weapon triangle bonus.
	adjustStatsAfterWeaponTriangle(enemy);
	
	//In Fire Emblem, a unit will double attack if their speed is at least points higher than the enemy.
	int amountOfAttacks = (this->stats[3] - enemy.getStats()[3] >= 5) ? 2 : 1 ;
	for (size_t i = 0; i < amountOfAttacks && enemy.hp > 0; i++)
	{
		if (skill->isActivated(*this))
			activateUnitSkill(enemy);
		else if (calculateHit(enemy) && calculateCriticalHit(enemy)) {
			std::cout << name << " landed a crit and dealt " << (totalAttack - enemy.stats[5]) * 3 << " damage!\n";
			enemy.hp -= (totalAttack - enemy.stats[5]) * 3;
		}else if(calculateHit(enemy)){
			std::cout << name << " dealt " << (totalAttack - enemy.stats[5]) << " damage!\n";
			enemy.hp -= (totalAttack - enemy.stats[5]);
		}else
			std::cout << name << " missed their attack! :(\n";
	}
	
	
	std::cout << name << " has " << hp << " hp left and " << enemy.name << " has " << enemy.hp << " left\n\n";
	 
	//base case. When either the player or enemy has died, end the recursive call
	if (enemy.hp <= 0) {
		std::cout << enemy.name << " is dead!\n";
		if (type == unitTypes::PLAYER) {
			std::cout << name << " leveled up!\n";
			levelUp();
		}
			
		return;
	}

	turnNumber++;

	enemy.attack(*this);
}

int Unit::getTotalAttack() const{
	return totalAttack;
}

void Unit::addToCriticalRate(int newCritRate){
	criticalRate += newCritRate;
}

void Unit::takeDamage(int damage){
	hp -= damage;
}

void Unit::recoverHP(int amountToRecover){
	hp += amountToRecover;
}

std::string Unit::getName() const{
	return name;
}

std::array<int, 7> Unit::getStats() const{
	return stats;
}

int Unit::getDamageDealtToEnemy(const Unit &enemy) const{
	return totalAttack - enemy.stats[5];
}

void Unit::activateUnitSkill(Unit &enemy){
	//in the Skill abstract class, there are two virtual activate functions, one that takes two mutable Unit objects, and another one that
	//takes a const Unit and a mutable unit. We need to know which one to call, so we must check the what type of skill "skill" is, whether
	//or not it is a "ONE_WAY_COMBAT" or a "TWO_WAY_COMBAT".
	if (skill->getSkillType() == skillType::ONE_WAY_COMBAT)
		skill->activate(std::as_const(*this), enemy);
	else
		skill->activate(*this, enemy);
}

//on turn one, adjust the stats of both the player and the enemy to reflect the bonuses added or subtracted by the weapon triangle
void Unit::adjustStatsAfterWeaponTriangle(Unit &enemy){
	if (turnNumber == 1) {
		weapon.determineWeaponTriangleBonus(enemy.weapon.getWeaponType());
		enemy.weapon.determineWeaponTriangleBonus(this->weapon.getWeaponType());
		calculateStats();
		enemy.calculateStats();
	}
}

int Unit::random(int min, int max) const{
	std::random_device seed;
	std::default_random_engine rnGen(seed());
	std::uniform_int_distribution<int> dist(min, max);

	return dist(rnGen);
}

void Unit::calculateStats(){
	int &att = stats[0], &mag = stats[1], &skl = stats[2], &spd = stats[3], &lck = stats[4], &def = stats[5], &res = stats[6];
	
	avoid = (spd * 2) + lck;
	criticalAvoid = lck / 2;
	hitRate = weapon.getAccuracy() + (skl * 2) + (lck / 2);
	criticalRate = skl + weapon.getCritical();
	totalAttack = att + weapon.getMight();
}

bool Unit::calculateHit(const Unit &enemy)const{
	//std::cout << "hit rate: " << hitRate - enemy.avoid << "%\n";
	return ((random(0, 100) + random(0, 100)) / 2) < hitRate - enemy.avoid;
}

bool Unit::calculateCriticalHit(const Unit &enemy) const{
	//std::cout << "critical hit: " << criticalRate - unit.criticalAvoid << "%\n";
	return random(0, 100) < criticalRate - enemy.criticalAvoid;
}

std::ostream & operator<<(std::ostream & os, const Unit & u){
	std::array<std::string, 7> statNames{"att", "mag", "skl", "spd", "lck", "def", "res"};

	std::cout << u.name << "'s hp: " << u.hp << "\n";
	
	for (int i = 0; i < statNames.size(); i++)
		os << statNames[i] << ": " << u.stats[i] << "\n";

	os << "Avoid: " << u.avoid << "\n";
	os << "hitRate: " << u.hitRate << "\n";
	os << "critical avoid: " << u.criticalAvoid << "\n";
	os << "critical rate: " << u.criticalRate << "\n";
	os << "Weapon: " << u.weapon << "\n";

	return os;
}

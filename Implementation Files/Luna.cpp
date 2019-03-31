#include "Luna.h"
#include "Unit.h"
#include <typeinfo>
#include <iostream>

Luna::Luna() : Skill(std::string(typeid(Luna).name()).substr(6), skillType::ONE_WAY_COMBAT) {
}

void Luna::setSkillLikelyHood(const Unit &player){
	likelyHood = player.getStats()[2] * 1.5;
}

void Luna::activate(const Unit &player, Unit &enemy){
	//When Luna is activated, the player will deal direct damage to the enemy, ignoring their defense
	std::cout << player.getName() << " activated " << skillName << "!\n";

	if (player.calculateHit(enemy) and player.calculateCriticalHit(enemy)) {
		std::cout << player.getName() << " landed a crit and dealt " << player.getTotalAttack() * 3 << " damage!\n\n";
		enemy.takeDamage(player.getTotalAttack() * 3);
	}else if (player.calculateHit(enemy)) {
		std::cout << player.getName() << " dealt " << player.getTotalAttack() << " damage!\n\n";
		enemy.takeDamage(player.getTotalAttack());
	}else 
		std::cout << player.getName() << " missed their attack!\n\n";
}

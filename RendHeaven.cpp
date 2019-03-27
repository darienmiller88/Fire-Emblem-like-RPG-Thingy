#include "RendHeaven.h"
#include "Unit.h"
#include <typeinfo>
#include <iostream>

RendHeaven::RendHeaven() : Skill(std::string(typeid(RendHeaven).name()).substr(6), skillType::ONE_WAY_COMBAT) {
}

void RendHeaven::setSkillLikelyHood(const Unit &player){
	likelyHood = player.getStats()[2] * 2;
}

//When Rend Heaven activates, it will add half of the enemy's attack power to the total amount of damage dealt to the enemy.
void RendHeaven::activate(const Unit & player, Unit & enemy){
	std::cout << player.getName() << " activated " << skillName << "!\n";

	if (player.calculateHit(enemy) and player.calculateCriticalHit(enemy)) {
		std::cout << player.getName() << " landed a crit and dealt " << (player.getDamageDealtToEnemy(enemy) + (enemy.getStats()[0] / 2)) * 3 
			<< " damage!\n\n";
		enemy.takeDamage((player.getDamageDealtToEnemy(enemy) + (enemy.getStats()[0] / 2) ) * 3);
	}
	else if (player.calculateHit(enemy)) {
		std::cout << player.getName() << " dealt " << (player.getDamageDealtToEnemy(enemy) + (enemy.getStats()[0] / 2)) << " damage!\n\n";
		enemy.takeDamage(player.getDamageDealtToEnemy(enemy) + (enemy.getStats()[0] / 2));
	}
	else
		std::cout << player.getName() << " missed their attack!\n\n";
}

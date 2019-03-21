#include "Vengeance.h"
#include "Unit.h"
#include <typeinfo>
#include <iostream>

Vengeance::Vengeance() : Skill(std::string(typeid(Vengeance).name()).substr(6), skillType::ONE_WAY_COMBAT) {
}

void Vengeance::setSkillLikelyHood(const Unit &player){
	likelyHood = player.getStats()[2] * 2;
}

//When vengeance is activated, the player will deal half of the amount of damage they took as additional damage. 
void Vengeance::activate(const Unit &player, Unit &enemy){
	int damage = player.getDamageDealtToEnemy(enemy) + ((player.getMaxHp() - player.getCurrentHP()) / 2);

	std::cout << player.getName() << " activated " << skillName << "!\n";

	if (player.calculateHit(enemy) and player.calculateCriticalHit(enemy)) {
		std::cout << player.getName() << " landed a crit and dealt " << damage * 3 << " damage!\n\n";
		enemy.takeDamage(damage * 3);
	}
	else if (player.calculateHit(enemy)) {
		std::cout << player.getName() << " dealt " << damage << " damage!\n\n";
		enemy.takeDamage(damage);
	}
	else
		std::cout << player.getName() << " missed their attack!\n\n";
}

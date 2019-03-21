#include "Sol.h"
#include "Unit.h"
#include <typeinfo>


Sol::Sol() : Skill( std::string(typeid(Sol).name()).substr(6), skillType::TWO_WAY_COMBAT ) {
}

void Sol::setSkillLikelyHood(const Unit &player){
	likelyHood = player.getStats()[2];
}

void Sol::activate(Unit &player, Unit &enemy){
	std::cout << player.getName() << " activated " << skillName << "!\n";

	int damage = player.getDamageDealtToEnemy(enemy), recovery;
	if (player.calculateHit(enemy) and player.calculateCriticalHit(enemy)) {
		std::cout << player.getName() << " landed a crit and dealt " << damage * 3 << " damage!\n";
		recovery = (damage > enemy.getCurrentHP() ) ? enemy.getCurrentHP() : damage * 3;
		player.recoverHP(recovery);
		std::cout << player.getName() << " recovered " << recovery << " hp!\n";
		enemy.takeDamage(damage * 3);
	}
	else if (player.calculateHit(enemy)) {
		std::cout << player.getName() << " and dealt " << damage << " damage!\n";
		recovery = (damage > enemy.getCurrentHP()) ? enemy.getCurrentHP() : damage;
		player.recoverHP(recovery);
		std::cout << player.getName() << " recovered " << recovery << " hp!\n";
		enemy.takeDamage(damage);
	}
	else
		std::cout << player.getName() << " missed their attack!\n";
}



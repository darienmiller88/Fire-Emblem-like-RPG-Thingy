#include "Astra.h"
#include "Unit.h"

Astra::Astra() : Skill(std::string(typeid(Astra).name()).substr(6), skillType::ONE_WAY_COMBAT){

}

void Astra::setSkillLikelyHood(const Unit &player){
	likelyHood = player.getStats()[2];
}

void Astra::activate(const Unit &player, Unit &enemy){
	std::cout << player.getName() << " activated " << skillName << ", Oh no!\n";
	
	int damage = player.getDamageDealtToEnemy(enemy);
	for (size_t i = 0; i < 5 && enemy.getCurrentHP() > 0; i++){

		//if the player lands a hit AND lands a crit, perform the crit against the enemy. 
		if (player.calculateHit(enemy) && player.calculateCriticalHit(enemy)) {
			std::cout << player.getName() << " landed a crit and dealt " << damage * 3 << " damage!\n" ;
			enemy.takeDamage(damage * 3);
		}

		//if the player managed to land a hit, but failed to crit, simply land a regular hit.
		else if (player.calculateHit(enemy)) {
			std::cout << player.getName() << " dealt " << damage << " damage!\n";
			enemy.takeDamage(damage);
		}

		//otherwise, the playerRef will miss their attack.
		else
			std::cout << "Attack missed!\n";

	}

	std::cout << "\n";
}
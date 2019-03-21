#include "Aether.h"
#include "Luna.h"
#include "Sol.h"
#include "Unit.h"
#include <typeinfo>
#include <iostream>
#include <type_traits>

Aether::Aether() : Skill(std::string(typeid(Aether).name()).substr(6), skillType::TWO_WAY_COMBAT) {

}

void Aether::setSkillLikelyHood(const Unit & player){
	likelyHood = player.getStats()[2] / 2;
}

void Aether::activate(Unit &player, Unit &enemy){
	Luna l;
	Sol s;

	std::cout << "YOU ACITVATED " << skillName << " HOLY SHIT!\n";
	s.activate(player, enemy);

	//If activating Sol did not take kill the enemy, activate Luna. Otherwise, end the function call as the enemy is already dead.
	if(enemy.getCurrentHP() > 0)
		l.activate(player, enemy);
}


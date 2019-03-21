#include "Wrath.h"
#include "Unit.h"

Wrath::Wrath() : Skill(std::string(typeid(Wrath).name()).substr(6), skillType::TWO_WAY_COMBAT), wasSkilledActivated(false) {	
}

//Wrath is a skill that only activates a single time, so the activation condition is slightly different compared to the other ones. This skill
//will only activated if it hasn't been acivated before, or if the wasSkillActivated variable was false. In this case, Wrath activates when
//the players HP is less or equal half their max HP.
bool Wrath::isActivated(const Unit &player) const{
	return player.getMaxHp() / player.getCurrentHP() >= 2 && !wasSkilledActivated;
}

//Unlike the other skills, there is no "likelyhood" of Wrath acitivating due to it haivng a differen activation condition.
void Wrath::setSkillLikelyHood(const Unit &player) {
	likelyHood = 0;
}

void Wrath::activate(Unit &player, Unit &enemy) {
	std::cout << player.getName() << " activated " << skillName << ", Oh no!\n";
	
	player.addToCriticalRate(50);

	if (player.calculateHit(enemy) && player.calculateCriticalHit(enemy)) {
		std::cout << player.getName() << " landed a crit and dealt " << (player.getDamageDealtToEnemy(enemy)) * 3 << " damage!\n";
		enemy.takeDamage(player.getDamageDealtToEnemy(enemy) * 3);
	}
	else if (player.calculateHit(enemy)) {
		std::cout << player.getName() << " dealt " << (player.getDamageDealtToEnemy(enemy)) << " damage!\n";
		enemy.takeDamage(player.getDamageDealtToEnemy(enemy));
	}
	else
		std::cout << player.getName() << " missed their attack! :(\n";

	//wrath is a skill that we only want to activate one time, so we need a boolean to let the activation function know when to return true,
	//or false to the Unit.cpp file.
	wasSkilledActivated = true;
}

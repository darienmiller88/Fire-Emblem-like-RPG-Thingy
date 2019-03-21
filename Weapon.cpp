#include "Weapon.h"

Weapon::Weapon(const std::string & weaponName, const weaponTypes &type, int accuracy, int might, int critical) : accuracy(accuracy),
might(might), weaponName(weaponName), critical(critical), WEAPON_TRIANGLE_BONUS(15), bonus(0), mightModification(0), type(type){
}

std::string Weapon::getName() const{
	return weaponName;
}

weaponTypes Weapon::getWeaponType() const{
	return type;
}

void Weapon::updateWeapon(){
	accuracy += 10;
	might += 5;
	critical += 10;
}

int Weapon::getAccuracy() const{
	return accuracy + bonus;
}

int Weapon::getMight() const{
	return might + mightModification;
}

int Weapon::getCritical() const{
	return critical;
}

void Weapon::determineWeaponTriangleBonus(const weaponTypes &enemyWeaponType){
	/*The weapon triangle works like rock, paper, scissors. Swords beat Axes, Axes beat Lances, and Lances beat swords. If
	you are at a weapon triangle advantage, your bonus will be reduced, and vice versa, increased. This if statement will 
	check to if the unit attacking is at a weapon triangle disadvantange against another unit.*/

	if (type == weaponTypes::SWORD && enemyWeaponType == weaponTypes::LANCE || type == weaponTypes::AXE &&
		enemyWeaponType == weaponTypes::SWORD || type == weaponTypes::LANCE && enemyWeaponType == weaponTypes::AXE) {
		bonus = -WEAPON_TRIANGLE_BONUS;
		mightModification = -2;
	}	
	else if (type == weaponTypes::SWORD && enemyWeaponType == weaponTypes::AXE || type == weaponTypes::AXE &&
		enemyWeaponType == weaponTypes::LANCE || type == weaponTypes::LANCE && enemyWeaponType == weaponTypes::SWORD) {
		bonus = WEAPON_TRIANGLE_BONUS;
		mightModification = 2;
	}
	else{ 
		bonus = 0;
		mightModification = 0;
	}
		
}

std::ostream & operator<<(std::ostream &os, const Weapon &w){
	os << "Weapon name: " << w.weaponName << "\n";
	os << "Weapon might: " << w.might << "\n";
	os << "Weapon accuracy: " << w.accuracy << "\n";
	os << "Weapon critical: " << w.critical << "\n";

	return os;
}

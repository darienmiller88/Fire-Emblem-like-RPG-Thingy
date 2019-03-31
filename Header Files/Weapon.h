#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <iostream>

enum class weaponTypes{
	AXE, SWORD, LANCE
};

class Weapon{
	public:
		Weapon(const std::string &weaponName, const weaponTypes &type, int accuracy, int might, int critical);
		std::string getName() const;
		weaponTypes getWeaponType() const;
		void updateWeapon();
		int getAccuracy() const;
		int getMight() const;
		int getCritical() const;
		void determineWeaponTriangleBonus(const weaponTypes &type);
		friend std::ostream &operator << (std::ostream &os, const Weapon &w);
	private:
		std::string weaponName;
		weaponTypes type;
		const int WEAPON_TRIANGLE_BONUS;
		int bonus;
		int mightModification;
		int accuracy; //weapon accuracy %
		int might; // weapon power
		int critical; //critical rate
};

#endif
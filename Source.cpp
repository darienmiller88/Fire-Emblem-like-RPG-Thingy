#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <fstream>
#include "Unit.h"
using namespace std;

void addSkills(vector< unique_ptr<Skill> > &skills);
void readInWeapons(ifstream &infile, vector<Weapon> &weapons);
void readInEnemies(vector<Unit> &enemies, vector<Weapon> &weapons, vector< unique_ptr<Skill> > &skills);
int random(int min, int max);
void buffConsecutiveEnemies(vector<Unit> &enemies);
void playGame( vector<Unit> &enemies, const vector<Weapon> &weapons, const vector< unique_ptr<Skill> > &skills);

int main() {
	vector< unique_ptr<Skill> > skills;
	vector<Weapon> weapons;
	vector<Unit> enemies;
	ifstream infile("Weapons.txt");

	addSkills(skills);
	readInWeapons(infile, weapons);
	readInEnemies(enemies, weapons, skills);
	playGame(enemies, weapons, skills);
	
}

void playGame(vector<Unit> &enemies, const vector<Weapon> &weapons, const vector< unique_ptr<Skill> > &skills) {
	
	//choose a random index in the polymorphic vector, and assign the address of the managed object by the unique pointer to the Skill pointers
	Unit player("Darien", weapons[random(0, weapons.size() - 1)], unitTypes::PLAYER, *skills[random(0, skills.size() - 1)].get());
	//Unit enemy = enemies.back();

	//Have the player attack the first enemy, and if they kill them, continue battling the rest.
	//player.attack(enemies.back());
	while (!enemies.empty() && player.getCurrentHP() > 0){
		player.attack(enemies.back());
		enemies.pop_back();
		system("pause");
		system("cls");
	} 

	cout << "You killed: " << player.getLevel()  - 1 << " enemies! Wow :D\n";

	//cout << player << "\n" << enemy << endl;
}

//function to add each of skills to a polymorphic vector.
void addSkills(vector<unique_ptr<Skill>> &skills){
	skills.push_back( unique_ptr<Skill>(make_unique<Aether>()) );
	skills.push_back( unique_ptr<Skill>(make_unique<Astra>()) );
	skills.push_back( unique_ptr<Skill>(make_unique<Luna>()) );
	skills.push_back( unique_ptr<Skill>(make_unique<RendHeaven>()) );
	skills.push_back( unique_ptr<Skill>(make_unique<Sol>()) );
	skills.push_back( unique_ptr<Skill>(make_unique<Vengeance>()) );
	skills.push_back( unique_ptr<Skill>(make_unique<Wrath>()) );

}

void readInWeapons(ifstream &infile, vector<Weapon> &weapons){
	auto determineWeaponType = [](const string &weaponType) {

		//I hate the way I did this, but I can't think of another way to associate a particular enum constant with a weapon type on a text
		//file unfortunately :/
		if (weaponType == "axe")
			return weaponTypes::AXE;
		else if (weaponType == "lance")
			return weaponTypes::LANCE;
		else 
			return weaponTypes::SWORD;
	};

	string weaponName, weaponType;
	int accuracy, might, critical;

	while (infile >> weaponName) {
		infile >> weaponType >> accuracy >> might >> critical;
		weapons.push_back(Weapon(weaponName, determineWeaponType(weaponType), accuracy, might, critical));
	}
}

void readInEnemies(vector<Unit> &enemies, vector<Weapon> &weapons, vector< unique_ptr<Skill> > &skills) {
	enemies.push_back(Unit("MKLeo", weapons[random(0, weapons.size() - 1)], unitTypes::ENEMY, *(skills[random(0, skills.size() - 1)].get())));
	enemies.push_back(Unit("Salem", weapons[random(0, weapons.size() - 1)], unitTypes::ENEMY, *(skills[random(0, skills.size() - 1)].get())));
	enemies.push_back(Unit("ZeRo", weapons[random(0, weapons.size() - 1)], unitTypes::ENEMY, *(skills[random(0, skills.size() - 1)].get())));
	enemies.push_back(Unit("Nairo", weapons[random(0, weapons.size() - 1)], unitTypes::ENEMY, *(skills[random(0, skills.size() - 1)].get())));
	enemies.push_back(Unit("Dabuz", weapons[random(0, weapons.size() - 1)], unitTypes::ENEMY, *(skills[random(0, skills.size() - 1)].get())));

	buffConsecutiveEnemies(enemies);
}

//Increase the level of each enemy relative to their position in the vector of enemies
void buffConsecutiveEnemies(vector<Unit> &enemies) {
	for (size_t i = 1; i < enemies.size(); i++){
		for (size_t amountToLevelUp = 0; amountToLevelUp < enemies.size() - 1 - i; amountToLevelUp++)
			enemies[i].levelUp();
	}
}

int random(int min, int max){
	random_device seed;
	default_random_engine rnGen(seed());
	uniform_int_distribution<int> dist(min, max);

	return dist(rnGen);
}

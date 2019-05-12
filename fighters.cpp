#include "fighters.h"
#include <iostream>
bool seed_set = false;
int fighter_num = 0;

int Fighter::roll(int dice){
	return rand() % dice;
}

Fighter::Fighter(const string& name){
	if (!seed_set) {
		srand(time(NULL));
		seed_set = true;
	}
	this->name = name;
	this->offensePoints = (rand() % (50 - 25 + 1)) + 25; //randomise
	this->defensePoints = (rand() % (50 - 25 + 1)) + 25; //randomise
	fighter_num++;
}

const void Fighter::showStats(){
	cout << "Fighter: " << this->name << endl;
	cout << "Class description: " << description << endl;
	cout << "HP: " << this->healthPoints << endl;
	cout << "ATK: " << this->offensePoints << endl;
	cout << "DEF: " << this->defensePoints << endl;
	cout << endl;
}

Warrior::Warrior(const string & name) : Fighter(name){
	description = "Warriors are brute forces trained to deal huge hits. (Special: 1 in 6 chance to crit)";
}

double Warrior::specialAttack(){
	return 2.0;
}

double Warrior::specialDefense(){
	return 1.0;
}

Ninja::Ninja(const string & name) : Fighter(name){
	description = "Trained in the high arts of stealth, Ninjas operate from the shadows. (Special: 1 in 6 chance to evade dmg)";
}

double Ninja::specialAttack(){
	return 1.0;
}

double Ninja::specialDefense(){
	return 0.0;
}

Mage::Mage(const string & name) : Fighter(name){
	description = "A scholar of arcane arts. (Special: 1 in 3 chance to release Meteor strike. Has to recharge after use)";
}

double Mage::specialAttack(){
	return 3.0;
}

double Mage::specialDefense(){
	return 1.0;
}

Cultist::Cultist(const string & name) : Fighter(name){
	description = "Praying to an ancient terrifying deity, the cultist drains energy from pain. (Special: Heals from dealing damage)";
}

double Cultist::specialAttack(){
	return 0.2;
}

double Cultist::specialDefense(){
	return 1.0;
}

void create(Fighter * arena[]){
	string name;
	int num;
	cout << "Choose your name: ";
	cin >> name;
	cout << "Choose your class: " << endl << "1. Warrior" << endl << "2. Ninja" << endl << "3. Mage" << endl << "4. Cultist" << endl << ": ";
	cin >> num;
	switch (num){
	case 1:
		arena[0] = new Warrior(name);
		break;
	case 2:
		arena[0] = new Ninja(name);
		break;
	case 3:
		arena[0] = new Mage(name);
		break;
	case 4:
		arena[0] = new Cultist(name);
		break;
	default:
		cout << "That is not a valid class...";
		break;
	}
}

void lastManStanding(Fighter * arena[]){
	int arena_size = fighter_num;
	int a = rand() % fighter_num;
	int b = rand() % fighter_num;

	while (arena_size > 1){
		a = rand() % fighter_num;
		b = rand() % fighter_num;
		while (arena[a] == nullptr || a == b){
			a = rand() % fighter_num;
		}
		while (arena[b] == nullptr || a == b){
			b = rand() % fighter_num;
		}
		fight(arena, a, b);
		if (arena[a] == nullptr || arena[b] == nullptr){
			arena_size--;
		}
	}
}

void fight(Fighter * arena[], int a, int b){
	while (arena[a] != nullptr && arena[b] != nullptr){
		arena[a]->attack(*arena[b]);
		if (arena[a]->dead){
			//delete(arena[a]);
			arena[a] = nullptr;
		}
		else if (arena[b]->dead){
			//delete(arena[b]);
			arena[b] = nullptr;
		}
		else {
			fight(arena, b, a);
		}
	}


}

void Fighter::attack(Fighter & defender){
	int dmg = rand() % (this->offensePoints + 1);
	int roll = Fighter::roll(6);

	if (this->recharge == 0) {
		if (this->specialAttack() == 3){
			roll = Fighter::roll(3);
		}

		cout << this->name << " attacks " << defender.name << "!" << endl;
		if (roll == 0 && this->specialAttack() != 0.2){
			dmg = dmg * this->specialAttack();
			if (this->specialAttack() == 2){
				cout << this->name << " goes for a critical Hit!" << endl;
			}
			else if (this->specialAttack() == 3){
				cout << this->name << " Summons a meteor strike!" << endl;
				this->recharge = 1;
			}
		}

		roll = Fighter::roll(6);
		//specialDefense used as evade mechanic - Ninja has 0, if roll is true, ninja midigates dmg
		if (roll == 0){
			dmg *= defender.specialDefense();
			if (defender.specialDefense() == 0){
				cout << defender.name << " evades the Strike!" << endl;
			}
		}
		// attacker deals dmg to defender
		if (dmg > 0){
			defender.healthPoints -= dmg;
			cout << defender.name << " took " << dmg << " damage. " << endl;
			if (this->specialAttack() == 0.2){
				this->healthPoints += dmg * this->specialAttack();
				cout << this->name << " leeches life from " << defender.name << endl;
			}
		}
		else {
			cout << defender.name << " took no damage. " << endl;
		}

		// hp check
		if (defender.healthPoints <= 0){
			defender.dead = true;
			cout << defender.name << " died from the attack." << endl;
		}
	}
	else{
		cout << this->name << " has to rekindle his spirit." << endl;
		this->recharge = 0;
	}
	// counter attack
	if (!defender.dead){
		if (defender.recharge == 0){
			cout << defender.name << " goes for a counter attack! " << endl;
			int counter = rand() % (defender.defensePoints + 1);
			roll = Fighter::roll(6);
			if (this->specialAttack() == 3){
				roll = Fighter::roll(3);
			}
			// Warriors are able to crit on counter hits
			if (roll == 0 && defender.specialAttack() != 0.2){
				counter *= defender.specialAttack();
				if (defender.specialAttack() == 2){
					cout << defender.name << " goes for a critical counter hit!" << endl;
				}
				else if (defender.specialAttack() == 3){
					cout << this->name << " Counters with a meteor strike!" << endl;
					this->recharge = 1;
				}
			}
			roll = Fighter::roll(6);
			if (roll == 0){
				counter *= this->specialDefense();
				if (this->specialDefense() == 0){
					cout << this->name << " evades the Strike!" << endl;
				}
			}
			if (counter > 0){
				cout << this->name << " took " << counter << " damage. " << endl;
				this->healthPoints -= counter;
				if (defender.specialAttack() == 0.2){
					defender.healthPoints += counter * defender.specialAttack();
					cout << defender.name << " leeches life from " << this->name << endl;
				}
			}
			else{
				cout << this->name << " took no damage. " << endl;
			}

			if (this->healthPoints <= 0){
				this->dead = true;
				cout << this->name << " died from the counter-attack." << endl;
			}
		}
		else{
			cout << defender.name << " has to rekindle his spirit." << endl;
			defender.recharge = 0;
		}
	}
	cout << endl;
}

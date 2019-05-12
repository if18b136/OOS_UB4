#include <cstdlib>
#include <ctime>
#include <iostream>
#include "fighters.h"
using namespace std;

#ifndef TESTS

int main(){
	Fighter* fighters[10];
	for (int i = 0; i < 10; i++) fighters[i] = nullptr;
	int num=0, a=0, b=0, c=0;
	string name;
	cout << "Welcome to the fight club!" << endl << "Menu: " << endl;
	while (num != 6) {
		cout << "1. Create Fighter (10 max.)." << endl << "2. Let two fighters compete." << endl << "3. Last Man Standing." << endl << "4. Delete Fighter." << endl << "5. Show all Fighters." << endl << "6. Quit." << endl << ": ";
		cin >> num;
		switch (num) {
		case 1:
			create(fighters);
			break;
		case 2:
			cout << "Enter 1. contestant." << endl << ": ";
			cin >> a;
			cout << "Enter 2. contestant." << endl << ": ";
			cin >> b;
			fight(fighters, a-1, b-1);
			break;
		case 3:
			lastManStanding(fighters);
			break;
		case 4:
			cout << "Which Fighter shall be deleted? " << endl << ": ";
			cin >> c;
			fighters[c-1] = nullptr;
			cout << "Done." << endl;
			break;
		case 5:
			for (int i = 0; i < 10; i++) {
				if (fighters[i] != nullptr) {
					fighters[i]->showStats();
				}
			}
			break;
		case 6:
			cout << "Bye." << endl;
			return 0;
		default:
			cout << "That command does not exist." << endl;
		}
	}
	
	
	return 0;
}
#endif // !TESTS

#include <cstdlib>
#include <ctime>
#include <iostream>
#include "fighters.h"
using namespace std;

#ifndef TESTS

int main() {
	Fighter* fighters[10];
	for (int i = 0; i < 10; i++) fighters[i] = nullptr;

	fighters[0] = new Warrior("Warrior");
	fighters[1] = new Ninja("Ninja");

	for (int i = 0; i < 10; i++) {
		if (fighters[i] != nullptr) {
			cout << fighters[i]->name << endl;
		}
	}
	lastManStanding(fighters);

	//int survivors = 0;

	//for (int i = 0; i < 10; i++) {
	//	if (fighters[i] != nullptr) {
	//		survivors++;
	//	}
	//}
	//
	for (int i = 0; i < 10; i++) {
		if (fighters[i] != nullptr) {
			delete(fighters[i]);
		}
	}
	return 0;
}
#endif // !TESTS

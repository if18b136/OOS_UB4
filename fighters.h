#pragma once
#include<string>
#include <cstdlib>
#include <ctime>
#ifndef FIGHTERS_H_include
#define FIGHTERS_H
using namespace std;

class Fighter
{

#ifdef TESTS
public:
#else
protected:
#endif
	int healthPoints = 100;
	int offensePoints;
	int defensePoints;
	string description;
public:
	bool dead = false;
	string name;
	Fighter(const string&);
	virtual ~Fighter() {};
	virtual double specialAttack() = 0;
	virtual double specialDefense() = 0;
	void attack(Fighter&);
	const void showStats();
	int roll(int dice);
private:
	int recharge = 0;
};

class Warrior : public Fighter
{
public:
	Warrior(const string&);
	virtual ~Warrior() {};
	double specialAttack();
	double specialDefense();
};

class Ninja : public Fighter
{
public:
	Ninja(const string&);
	virtual ~Ninja() {};
	double specialAttack();
	double specialDefense();
};

class Cultist : public Fighter
{
public:
	Cultist(const string&);
	virtual ~Cultist() {};
	double specialAttack();
	double specialDefense();
};

class Mage : public Fighter
{
public:
	Mage(const string&);
	virtual ~Mage() {};
	double specialAttack();
	double specialDefense();
private:
	int recharge;
};

void create(Fighter* []);
void fight(Fighter* [], int, int);
void pick(Fighter* []);
void lastManStanding(Fighter* []);
void view(Fighter* []);
#endif

#pragma once
#include "Location.h"
#include "RabbitPen.h"

#include <random>

class Rabbit
{
public:
	Rabbit();
	void RabbitInitial(std::mt19937& rng);
	Rabbit(Location& newlocation, Rabbit& momrabbit, Rabbit& newrabbit,  std::mt19937& rng);
	 ///////////////////////
	/*   Getter funcs    */
   ///////////////////////
	const bool GetGender() const;
	const bool IsInfected() const;
	const int getAge() const;
	const Location GetLoc() const;
	void KillTheRabbit();
	void RabbitAgeIncrementer();
	void ResetForBreeding();
	bool DidSheBreed();

	  //////////////////////////////////
	 /*      Main member functions   */
	///////////////////////////////////
	void GetInfected();
	void DrawBunny(RabbitPen& rabbitpen);
	void Move(Location& new_loc);
private:
	Location loc;
	bool isMale;
	bool isVampire;
	int age;
	bool isdead;
	bool didSheBreed = false;
};
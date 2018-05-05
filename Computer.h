#include <iostream>
#include "Player.h"
#include <stdlib.h>
#include <time.h>
#pragma once

using namespace std;

#define DASH "-"

class Computer: public Player
{
public:
	Computer(string name, int score=0) : Player(name,score) //Base class called
	{
		Name = name;
		Score = score;
	}

	virtual int PickOfDeck(const Cards& deck) const;// Player class method overridden

	virtual int CardNeedToDiscard () const;  		//A random card of the AI is discarded

	virtual void DisplayMeld () const; 				//This will show the AI's melded cards

	virtual vector<int> SecondMeld () const;  		//This is when it is the chance of the player to meld cards; All will first check if it can can meld cards of same rank however, if it cannot, melded cards of same suit and consecutive value will be tested

	void Gplay (Cards& deck);  						//unique methods of the AI are from overriding GamePlay from the Player class

	int RankConvert (const string& index) const;  	//Conversion to integer from string

	string RetrieveSuit (const string& index) const;  //Returns card suit
};
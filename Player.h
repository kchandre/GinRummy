#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include "Cards.h"
#pragma once

using namespace std;

#define PickFromDeck -1
#define ifYes 1
#define TermNumber -1
#define OffsetR 2
#define numeralCards 5
#define faceCardPoints 10
#define AcePt 15
#define EMPTY 0
#define numCheck 2
#define next1 1
#define next2 2

class Player
{
public:
	// Init-constructor, gets the player name and 
	Player(string name, int score = 0);

	// Returns the player's name
	virtual string GetName() const;

	// Returns the player's score
	virtual int GetScore() const;

	// Returns the size of the player's hand
	virtual int GetSize() const;

	// Calculates the players score
	// Adds up the score of the player's melded cards
	// Then subtracts the cards left in the player's hand
	virtual void CalcScore();

	// Returns the Value of the hand at number
	virtual string GetHandVal(const int& number) const;

	// Inserts card into the hand at the end of the handS
	virtual void InsertCard(const string& card);

	// Displays the hand
	void ShowHand() const;

	// Determine what deck the player will pick from 
	virtual int PickDeck(const Cards& deck) const;

	// Determines what card the player will discard
	virtual int CardToDiscard () const;

	// Sorts the players hand
	void OrgHand();

	// Returns the card at this location
	virtual string ReturnCard (const int& number) const;

	// Pops the card at number from the Hand
	virtual void RemoveCard (const int& number);

	// Display the melded cards
	virtual void DisplayMeld () const;

	// Populates melded cards and organizes them!
	virtual void PopMeld (const vector<int>& CardSpotsIWillMeld);

	// Enters this method because the player wants to meld cards
	virtual vector<int> SecondMeld () const;

	// Call this function after each hand, need to reset the cards you have to 0!
	virtual void ClearHandMeld();

	// Populates a vector of the cards that the player will meld from their own hand
	vector<int> CardTMeld() const;

	// The main game play for the game, iterates through each turn of every hand
	virtual void Play (Cards& deck, const vector<string>& compsMeldedCards, const string& compsName);

	// Must insert the cards from player's choice all the way up to the end of the pile into the player's hand
	// Called if the player wants to pick from the pick up pile
	virtual void PickFromPile (Cards& deck, const int& choice);

	// Discards the card in the player's hand at spot cardSpot
	virtual void Discard (Cards& deck, const int& cardSpot);

	// Retruns a vector of the computer's melded cards
	virtual vector<string> ReturnMeldCards () const;

	// Returns a vector of the card locations that the player wants to meld
	vector<int> FetchMeldIndex () const;

protected:
	string Name;
	int Score;
	vector<string> MeldedCards;
	vector<string> Hand;
};
#pragma once
#include <iostream>
#include <vector>
#include <string> 
#include <algorithm>
#include <ctime>

using namespace std;

#define DECK_SIZE 52
#define CARDS_PER_PLAYER 7
#define NumRanks 13
#define Numsuits 4
#define OffsetR 2
#define ONE 1
#define TEN "10"
#define JACK "11"
#define QUEEN "12"
#define KING "13"
#define ACE "14"
#define DIAMOND "-D"
#define SPADE "-S"
#define CLUB "-C"
#define HEART "-H"

//enumerate rank for card generation
//TODO change 
enum Rank{
	Two,Three,Four,Five,
	Six,Seven,Eight,Nine,Ten,
	Jack,Queen,King,Ace
};

//enumerate suit
enum Suit{
	D,H,S,C
};


//changed function order 
class Cards
{
public:

	void InitializeDeck(); 			//generate deck
	void DeckShuffle();				//shuffle deck
	void CardPop(); 				//pulls card off top of deck
	int DeckSize() const;			//return size of deck
	int GetPFromPile() const;		//return size of pick up stack
	void AdjPick();					//generate pick up from stack
	void PopPick();					//pop off pick up pile
	string TopCard () const;		//return top card from deck

	void DispAvailCards() const;					//display cards
	string RetCard(const int& number) const; 		//get card in deck at number
	string pickFromPile(const int& number) const;	//return card @ number
	void InsertPick(const string& card);			//insert card at end of pick pile

private:
	vector<string> Deck;
	vector<string> FromPile;
};
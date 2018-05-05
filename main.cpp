#include <iostream>
#include <vector>

#include "Player.h"
#include "Cards.h"
#include "Computer.h"

using namespace std;


#define winScore 500
#define numTwoToNine 5
#define TenThroughKing 10
#define AcePt 15
#define CardDelt 11
#define DECK_SIZE 52
#define EMPTY 0
#define TermNumber -1
#define OffsetR 2
#define oddEven 2
#define ifYes 1

//rules of the game
void outputIntroduction();

// win state, goodbye
void outputEnding(Player& player, Computer& comp);

//deals cards(popoff) computer -> player till full
void dealDeck(Player& player, Computer& comp, Cards& deck, int count);

//scores and round ouput
void ScoreOutput(Player& user, Computer& comp, int roundCount);


int main (){

	//greetings/rules/prompt for name
	outputIntroduction();
	
	//name
	string name;
	cout << "\nEnter your name: ";
	getline(cin, name);
	Player user(name);

	//computer name
	cout << "\nEnter a name for the computer: ";
	getline(cin,name);
	Computer comp(name);
	cout << "\n";

	//round count
	unsigned int roundCount = EMPTY;

	//continues until winning score is reached
	while ( (user.GetScore() < winScore) && (comp.GetScore() < winScore) ){

		ScoreOutput(user,comp,roundCount);	//score outpput

		//cards-initialize & shuffle
		Cards deck;
		deck.InitializeDeck();	
		deck.DeckShuffle();		//shuffle

		//empty hands and melds
		user.ClearHandMeld();
		comp.ClearHandMeld();

		//deal
		dealDeck(user,comp,deck,roundCount);
	
		//TODO fix this 
		//switch player dealt to 
		unsigned int count = roundCount;

		//play while both players have cards
		while ( (user.GetSize() > EMPTY) && (comp.GetSize() > EMPTY) && (deck.DeckSize() > EMPTY) ){
		
			//call through hand
			if (count % oddEven == EMPTY) { user.Play(deck,comp.ReturnMeldCards(),comp.GetName()); }
			
			else { comp.Gplay(deck); }		//computer

			count++;
		}
		
		//increment round after each round
		roundCount++;

		//pull & calc scores
		int playerScore = user.GetScore();
		int initCompScore = comp.GetScore();
		user.CalcScore();
		comp.CalcScore();

		//TODO output
		cout << "Points scored \n" << user.GetName() << ": " << user.GetScore() - playerScore << "\n";
		cout << comp.GetName() << ": " << comp.GetScore() - initCompScore << "\n\n";
	}
	
	//winner
	outputEnding(user,comp);

	//pause for output
	system("pause");
	return 0;
}


//output for rules and greeting
void outputIntroduction()
{
	cout << endl << endl;
	cout << "Welcome to Gin Rummy \n";
	cout << "This variation is called Straight Gin \n\n";

	// List the rules





	cout << "RULES: (bicycle)" << endl;
	cout << "THE PACK: \n";
	cout << "The standard 52-card pack is used. \n\n";

	cout << "OBJECT OF THE GAME:\n" <<
		"To lay matched number sets of 3 or 4 and/or \n"
		"sequences of 3 or more cards of the same suit to be the \n"
		"first player to obtain 500 total net points.\n\n";

	cout << "Rank of Cards" << endl;
	cout << "	Ace (high or low), K, Q, J, 10, 9, 8, 7, 6, 5, 4, 3, 2, A." << endl << endl;

	cout << "CARD VALUES/SCORING" << endl;
	cout << "Score points by laying down and laying off cards as in regular Rummy," << endl;
	cout << "in matched number sets of 3 or 4, and in sequences of 3 or more cards of the same suit." << endl << endl;

	cout << "When any player gets rid of all his cards, the play immediately ends. " << endl;
	cout << "Each player’s score is then figured as follows:" << endl;
	cout << "The player is credited with the " << endl;
	cout << "point value of all cards that the player has showing on the table. From this figure " << endl;
	cout << "is subtracted the point value of all cards remaining in his hand. " << endl;
	cout << "The difference is added or subtracted from the player’s score." << endl << endl;

	cout << "THE DEAL" << endl;
	cout << "Deal seven cards to each player (except in the two player game, in which each player receives 13 cards). " << endl;
	cout << "Place undealt cards face down in the center of the table, forming the stock. " << endl;
	cout << "The top card is turned face up and is placed beside the stock as the up card to start" << endl;
	cout << "the discard pile. The discard pile should be slightly spread, so that players can readily see" << endl;
	cout << "all the cards it contains." << endl << endl;

	cout << "THE PLAY" << endl;
	cout << "Each player, beginning with the player to the left of the dealer," << endl;
	cout << "may draw either the top card of the stock or any card from the discard pile." << endl;
	cout << "There are two conditions when drawing a card from the discard pile:" << endl;
	cout << "1) the player must take all the cards above the selected card" << endl;
	cout << "2) the drawn card must immediately be used, either by laying it down" << endl;
	cout << " in a set or by laying it off on a set already on the table." << endl;
	cout << "The remaining cards taken with the discard may be melded in the same turn or simply added to the player’s hand." << endl << endl;

	cout << "Each player in turn, after drawing but before discarding," << endl;
	cout << "may lay down any matched set or may lay off any card that matches a set already on the table." << endl;
	cout << "Cards that are laid off are kept on the table in front of the player. " << endl;
	cout << "Sequences may not “go round the corner”; thus, A, K, Q or A, 2, 3 may be melded, but not K, A, 2." << endl << endl;








cout << "Points are tallied at the end of each hand.\n" << endl;

cout <<
		"Points per card are as follows:\n" <<
		Rank(0) + OffsetR << " ... " << Rank(8) + OffsetR << " --> " << numTwoToNine << " points\n" <<
		Rank(9) + OffsetR << " ... " << Rank(11) + OffsetR << " --> " << TenThroughKing << " points\n" <<
		Rank(12) + OffsetR << " --> " << AcePt << " points. \n\n";


cout << "if the score limit is reached at the same time, the player with more points at the end of the round wins" << endl << endl;
cout << "When setting a meld, say what cards you want to meld in descending order." << endl << endl;
}

void outputEnding(Player& player, Computer& comp)
{
	cout << "Score:\n" << player.GetName() << ": " << player.GetScore() << "\n" << comp.GetName() << ": " << comp.GetScore() << "\n\n";

	// Whichever player has the higher score wins
	if ( player.GetScore() >= comp.GetScore() )
		cout << "Congratulations, " << player.GetName() << "! you won!";
	else
		cout << "Sorry, " << comp.GetName() << " won.";

}

void dealDeck(Player& user, Computer& comp, Cards& deck, int count)
{
	if (count % oddEven == EMPTY)	// Deal to user first
	{
		unsigned int i = EMPTY;
		while (i < oddEven*CardDelt)
		{
			user.InsertCard(deck.TopCard());
			deck.CardPop();
			i++;
			comp.InsertCard(deck.TopCard());
			deck.CardPop();
			i++;
		}
		deck.AdjPick();
	} else							// Deal to computer first
	{
		unsigned int j = EMPTY;
		while (j < oddEven*CardDelt)
		{
			comp.InsertCard(deck.TopCard());
			deck.CardPop();
			j++;
			user.InsertCard(deck.TopCard());
			deck.CardPop();
			j++;
		}
		deck.AdjPick();
	}
}

void ScoreOutput(Player& user, Computer& comp, int roundCount)
{
	cout << "Round: " << roundCount << "\n" <<
		"Current score: " << user.GetScore() << "\n" <<
		comp.GetName() << "'s score: " << comp.GetScore() << "\n\n";
}
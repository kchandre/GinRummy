#include "Computer.h"

int Computer::PickOfDeck(const Cards& deck) const
{
	int i = EMPTY; 
	while (i < GetSize() - 1)
	{
		int value1 = RankConvert(Hand[i]);  	//Gets ranks from both card values
		int value2 = RankConvert(Hand[i+next1]);


		if (value1 == value2)   				//if cards contain same value, AI gets a different card from pick pile
		{
			for (int j = 0; j < deck.GetPFromPile(); j++)  //if values are same, the index of pick from pile will be returned
			{
				int ValueCompare = RankConvert(deck.pickFromPile(j));

				if (value1 == ValueCompare)
					return j;
			}
		}
		i++;
	}

	return PickFromDeck;   //The AI proceeds to get a card from the top of the deck only if none of the other terms were met
}

int Computer::CardNeedToDiscard () const
{
	int compHandSize = GetSize();

	srand(time(NULL));

	int cardToDiscard = rand() % compHandSize;

	return cardToDiscard;
}

void Computer::DisplayMeld () const
{
	cout << Name << "'s melded cards: \n";
	for (unsigned int i = 0; i < MeldedCards.size(); i++)
		cout << Hand[i] << " ";
	cout << "\n\n";
}

vector<int> Computer::SecondMeld () const
{
	vector<int> CompMeld;

	unsigned int i = EMPTY; //This checks value of meld cards, if they have equal value
	while (i < Hand.size() - numCheck)
	{

		int value1 = RankConvert(Hand[i]);
		int value2 = RankConvert(Hand[i+next1]); //Conversion of integers from card rank
		int value3 = RankConvert(Hand[i+next2]);

		if (value1 == value2 && value1 == value3)  //The 3 cards are evaluated to see if they contain the same rank value, if true AI will meld
		{
			CompMeld.push_back(i+next2);
			CompMeld.push_back(i+next1);
			CompMeld.push_back(i);


			i = Hand.size() - numCheck;
		} else
			i++;
	}

	if (CompMeld.size() == EMPTY) //only used when meld was not successful based on same rank
	{
		unsigned int j = EMPTY;
		while (j < Hand.size() - numCheck)
		{
			int value1 = RankConvert(Hand[j]);
			int value2 = RankConvert(Hand[j+next1]);
			int value3 = RankConvert(Hand[j+next2]);  //Conversion of integers from card rank


			if (value3 == value2 + 1 && value2 == value1 + 1)  //This evaluates if the cards are consecutive in value
			{
				string cardSuit1 = RetrieveSuit(Hand[j]);
				string cardSuit2 = RetrieveSuit(Hand[j+next1]);
				string cardSuit3 = RetrieveSuit(Hand[j+next2]);
					
				if (cardSuit1 == cardSuit2 && cardSuit2 == cardSuit3)  //This evaluates whether the cards all contain the same suit; if true the AI will meld and the location of the cards will be added to the vector with the locations of the cards
				{
					CompMeld.push_back(j+next2);
					CompMeld.push_back(j+next1);
					CompMeld.push_back(j);
					j = Hand.size() - numCheck;
				} else
					j++;
			} else
				j++;
		}
	}

	return CompMeld;
}

void Computer::Gplay (Cards& deck)
{
	cout << Name << "'s turn!\n";
	
	OrgHand();

	
	int choice = PickOfDeck(deck);  //Occurs when AI must decide what cards to choose

	if (choice != PickFromDeck)		//Happens when getting card from pick pile
	{
		PickFromPile(deck,choice);
			
		OrgHand();  				//called when AI has to remove a card from hand

		PopMeld(SecondMeld());   	//fills Ai's new cards (melded)

	} else {	
		InsertCard(deck.TopCard());  //This is when you take the top card of the deck
		deck.CardPop();
	}

	OrgHand();


	if(GetSize() > EMPTY)
		Discard(deck,CardNeedToDiscard());  //AI discards a card

	cout << "\n";
}

int Computer::RankConvert (const string& index) const
{
	string cardRank = index.substr(0,index.find(DASH));  //Gets substring from beginning of index , thus getting the card's rank 
	
	int value = atoi(cardRank.c_str());   				 //This is a conversion to integer from ranks of the cards
	

	return value;
}

string Computer::RetrieveSuit (const string& index) const
{
	string suit = index.substr(index.find(DASH)+next1,index.size() - (index.find(DASH)+next1));
	return suit;  //This is the rank from retrieving the substring to end of the string
}

#include "Player.h"

Player::Player(string name, int score){
	Name = name;
	Score = score;
}

string Player::GetName() const{
	return Name;
}

int Player::GetScore() const{
	
	return Score;
}

void Player::CalcScore(){

	for (unsigned int i = 0; i < MeldedCards.size(); i++){
		string cardRank = MeldedCards[i].substr(0,MeldedCards[i].find('-'));
		
		int value = atoi(cardRank.c_str());

		if (value < Rank(8) + OffsetR)
			Score += numeralCards;
		else if (value >= Rank(8) + OffsetR && value <= Rank(11) + OffsetR)
			Score += faceCardPoints;
		else 
			Score += AcePt;
	}
	
	for (unsigned int i = 0; i < Hand.size(); i++)
	{
		string cardRank = Hand[i].substr(0,Hand[i].find('-'));
		
		int value = atoi(cardRank.c_str());

		if (value < Rank(8) + OffsetR)
			Score -= numeralCards;
		else if (value >= Rank(8) + OffsetR && value <= Rank(11) + OffsetR)
			Score -= faceCardPoints;
		else 
			Score -= AcePt;
	}
}

int Player::GetSize() const
{
	return Hand.size();
}

string Player::GetHandVal(const int& number) const
{
	return Hand[number];
}

void Player::InsertCard(const string& card)
{
	Hand.push_back(card);
}

void Player::ShowHand() const
{
	cout << "Your hand:\n";
	for (unsigned int i = 0; i < Hand.size(); i++)
		cout << Hand[i] << " ";
	cout << "\n";
}

int Player::PickDeck(const Cards& deck) const
{
	int choice;
	cout << "Would you like to pick up from the pick up pile? ";
	cin >> choice;

	// They want to use cards from the pick up pile to meld
	if (choice == ifYes)
	{
		int firstDeckLocation;
		
		cout << "\nWhat is the bottom card location you wish to pick up from the deck? ";
		cin >> firstDeckLocation;

		while (firstDeckLocation < 0 || firstDeckLocation >= deck.GetPFromPile())
		{
			cout << "Invalid location. Try again: ";
			cin >> firstDeckLocation;
		}

		return firstDeckLocation;		// Must return the location that they want to initially pick from 
	} else
	{
		// They want to pick from the deck
		return PickFromDeck;
	}
}

int Player::CardToDiscard () const
{
	int cardToDiscard;

	cout << "Which card would you like to discard? ";
	cin >> cardToDiscard;

	while (cardToDiscard < EMPTY || cardToDiscard >= GetSize())
	{
		cout << "That's an invalid index. Try again! ";
		cin >> cardToDiscard;
	}

	return cardToDiscard;
}

void Player::OrgHand(){
	sort(Hand.begin(),Hand.end());
}

string Player::ReturnCard (const int& number) const
{
	return Hand[number];
}

void Player::RemoveCard (const int& number)
{
	Hand.erase(Hand.begin() + number);
}

void Player::DisplayMeld () const
{
	cout << "Your melded cards: \n";
	for (unsigned int i = 0; i < MeldedCards.size(); i++)
	{
		cout << MeldedCards[i];
		if (i < MeldedCards.size() - 1)
			cout << " ";
	}
	cout << "\n\n";
}

void Player::PopMeld (const vector<int>& CardSpotsIWillMeld)
{
	// Want to populate 
	for (unsigned int i = 0; i < CardSpotsIWillMeld.size(); i++)
	{
		int locale = CardSpotsIWillMeld[i];
		string card = ReturnCard(locale);
		MeldedCards.push_back(card);	
		RemoveCard(locale);
	}
	// Then sorts the melded cards!
	sort(MeldedCards.begin(),MeldedCards.end());
}

vector<int> Player::SecondMeld () const
{
	// Then must determine if they can meld cards after picking up or not
	int answer;
	cout << "\nWould you like to meld? ";
	cin >> answer;
	
	vector<int> cardsToMeld;

	if (answer == ifYes)
		cardsToMeld = FetchMeldIndex();
	
	return cardsToMeld;
}

void Player::ClearHandMeld()
{
	Hand.clear();
	MeldedCards.clear();
}

vector<int> Player::CardTMeld() const
{
	vector<int> cardsIWillMeld;
	cout << "\n";
	ShowHand();
		
	cardsIWillMeld = FetchMeldIndex();

	return cardsIWillMeld;
}

void Player::Play (Cards& deck, const vector<string>& compsMeldedCards, const string& compsName)
{
	cout << "Your turn!\n\n";

	cout << "Current pick up pile:\n";		// X represents the top of the deck
	deck.DispAvailCards();					// Show the player's what they are working with

	OrgHand();
	ShowHand();
	cout << "\n";
	// Show the player the melded cards
	DisplayMeld();
	
	cout << compsName << "'s melded cards: \n";
	for (unsigned int i = 0; i < compsMeldedCards.size(); i++)
		cout << compsMeldedCards[i] << " ";
	cout << "\n\n";

	// First must choose cards to pick up
	int choice = PickDeck(deck);

	if (choice != PickFromDeck)	// Picking from the pick up pile
	{
		PickFromPile(deck,choice);
			
		OrgHand();

		// Populate the players newly melded cards
		PopMeld(CardTMeld());

		cout << "\n";
		DisplayMeld();
	} else {	// Picking up from the top of the deck
		InsertCard(deck.TopCard());
		deck.CardPop();
	
		// Only need to ask them to meld if they didn't want to the first time
		// This populates the users melded cards with a vector of cards that they are allowed to meld
		if (GetSize() > EMPTY)
		{
			cout << "\n";
			OrgHand();
			ShowHand();
			PopMeld(SecondMeld());
		}
	}
	
	cout << "\n";

	// Finally, must discard a card
	if(GetSize() > EMPTY)
	{
		OrgHand();
		ShowHand();
		cout << "\n";
		Discard(deck,CardToDiscard());
	}

	cout << "\n";
}

void Player::PickFromPile (Cards& deck, const int& choice)
{
	for (int i = deck.GetPFromPile()-next1; i >= choice; i--)
	{
		InsertCard(deck.pickFromPile(i));	// Insert the card into their hand
		deck.PopPick();							// Remove that card from the pile
	}
}

void Player::Discard (Cards& deck, const int& cardSpot)
{
	deck.InsertPick(ReturnCard(cardSpot));	// First insert the card into the pick from pile
	RemoveCard(cardSpot);									// Then pop the card out of the user's hand
}

vector<string> Player::ReturnMeldCards () const
{
	return MeldedCards;
}

vector<int> Player::FetchMeldIndex () const
{
	vector<int> cardsToMeld;
	int location = EMPTY;

	cout << "\nWhich cards from your hand do you want to meld?\n";

	while (location != TermNumber)
	{
		cin >> location;
		if (location != TermNumber)
			cardsToMeld.push_back(location);
	}

	return cardsToMeld;
}
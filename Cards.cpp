#include "Cards.h"

void Cards::InitializeDeck(){

	//for the number of cards in the deck assign ranks and suits
	for (int r = 0; r < NumRanks; r++){
		for (int s = 0; s < Numsuits; s++){
		
			string card;
			
			//pulls card rank from Rank()
			Rank CardFace = Rank(r);
			
			//TODO changable structure
			switch (CardFace){
			
			case(Two):
			case(Three):
			case(Four):
			case(Five):
			case(Six):
			case(Seven):
			case(Eight):
			case(Nine):	card += CardFace + OffsetR + '0';
				break;
				
			case(Ten):
				card = TEN;
				break;
				
			case(Jack):
				card = JACK;
				break;
				
			case(Queen):
				card = QUEEN;
				break;
				
			case(King):
				card = KING;
				break;
				
			case(Ace):
				card = ACE;
			}
			
			//assigns suit within the for loop
			Suit DisplayAvailCards = Suit(s);
			
			//face cards
			switch (DisplayAvailCards)
			{
			case(D):
				card.append(DIAMOND);
				break;
				
			case(H):
				card.append(HEART);
				break;
				
			case(S):
				card.append(SPADE);
				break;
				
			case(C):
				card.append(CLUB);
			}
			
			//push card onto the deck like a stack 
			Deck.push_back(card);
		}
	}
}

/*shuffles the deck using a random number generated from a random number from ctime */
void Cards::DeckShuffle(){
	srand ( unsigned ( time(0) ) );
	random_shuffle(Deck.begin(),Deck.end());
}

/* displays all cards on the pile using a for loop with a side effect */
void Cards::DispAvailCards() const {
	for (unsigned int i = 0; i < FromPile.size(); i++)
		cout << FromPile[i] << " ";
	cout << "\n\n";
}


/*returns Deck  */
string Cards::RetCard(const int& num) const {
	return Deck[num];
}

//TODO check removes from vector 
void Cards::CardPop() {
	Deck.pop_back();
}

//get size
int Cards::DeckSize() const{
	return Deck.size();
}

void Cards::AdjPick(){
	int number = Deck.size() - ONE;
	string copy = Deck[number];
	Deck.pop_back();
	FromPile.push_back(copy);
}

//extends cards through getPickFromPileSize
int Cards::GetPFromPile() const{
	return FromPile.size();
}

//Extends getpickfromPile
string Cards::pickFromPile(const int& number) const{
	return FromPile[number];
}

//Extends insert into pick from pile
void Cards::InsertPick(const string& card){
	FromPile.push_back(card);
}

//pop back pile
void Cards::PopPick(){
	FromPile.pop_back();
}

//locates top card in deck 
string Cards::TopCard () const{
	return Deck[DeckSize()-ONE];
}
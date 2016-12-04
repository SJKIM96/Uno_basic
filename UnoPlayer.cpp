#include "UnoPlayer.h"


UnoPlayer::UnoPlayer()
{
}

UnoPlayer::~UnoPlayer()
{
}
void UnoPlayer::populate(int num, Bag <shared_ptr<Card>> &bag)
{
	for (int i = 0; i < num; i++)
	{//populate cards and increment number of cards
		hand.insert(bag.getOne());
		amount_of_card++;
	}
}
void UnoPlayer::print_hand()
{
	for (int i = 1; i <= hand.getLength(); i++)
		cout << *hand.retrieve(i) << " | "; // print number of hand
	cout << endl;
}

Card UnoPlayer::retrieve(int pos) const
{// get the card value
	return *hand.retrieve(pos);
}
void UnoPlayer::check(Stack<shared_ptr<Card>> &a, Card temp, Queue<shared_ptr<Card>> &deck)
{
	for (int i = 1; i <= amount_of_card; i++)
	{//check if they have same denomination
		if (temp.getDenomination() == (*hand.retrieve(i)).getDenomination())
		{
			cout << name << "  found a match! They played " << (*hand.retrieve(i)) << endl;
			a.push(hand.remove(i)); // put it in face up
			amount_of_card--; // decrement number of card you have from hand 
			if (amount_of_card == 1)//yell uno if the player has one card left
				cout << name << " yells UNO!" << endl;
			return;
		}	
	}

	for (int i = 1; i <= amount_of_card; i++)
	{// check if it has same suit
		if (temp.getSuit() == (*hand.retrieve(i)).getSuit())
		{
			cout << name << "  found a match! They played " << (*hand.retrieve(i)) << endl;
			a.push(hand.remove(i));// put it in faceup
			amount_of_card--;//decrement number of card you have from hand
			if (amount_of_card == 1)
				cout << name << " yells UNO!" << endl;
			return;
		}
	}
	// if they didnt find any match 
	cout << name << " did not find a match. They drew a card" << endl;
	hand.insert(deck.dequeue());// draw one card
	amount_of_card++;// increment number of card
	
}

int UnoPlayer::Getsize() const
{//return size
	return amount_of_card;
}

bool UnoPlayer::isempty() const
{// check if its empty
	return (amount_of_card == 0);
}
void UnoPlayer::Setname(string input, int num)
{//set name 
	this ->name = input +to_string(num);
}

string UnoPlayer::Getname() const
{//get name
	return name;
}
#include "UnoGame.h"

UnoGame::UnoGame(int ppl = num_of_players)
{
	Bag <shared_ptr<Card>> bag(40);
	number_of_player = ppl;
	player = new UnoPlayer[ppl];
	for (int i = 0; i < number_of_player; i++)
		player[i].Setname("player " , i+1);
	Suit s[] = { Red, Yellow, Green, Blue };
	Denomination d[] = { N1, N2, N3, N4, N5 };
	for (int k = 0; k < 2; k++)
	{//duplicate all number
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				bag.add(make_shared<Card>(s[i], d[j])); // add all the available cards
			}
		}
	}
	for (int i = 0; i < ppl; i++)
	{//get defined number of cards in the bag
		player[i].populate(num_of_cards, bag);
	}
	while (!(bag.isEmpty())) //move all the remaining cards to deck
		deck.enqueue(bag.getOne());
	face_up_cards.push(deck.dequeue());//flip the first deck
}


UnoGame::~UnoGame()
{
	delete[] player; // delete dma players
}



void UnoGame::print()
{
	for (int i = 0; i <number_of_player; i++)
	{
		player[i].Getname(); // get players name
		player[i].print_hand();// call print function at player
	}
}

void UnoGame::play()
{
	bool solved = true; // dont break until its false
	while (solved)
	{
		for (int i = 0; i < number_of_player; i++)
		{
			cout << "Face up card" << endl;
			cout << *face_up_cards.peek() << endl;// print which card is the face up card now
			//user name+ hand
			cout << player[i].Getname();
			player[i].print_hand();
			//check if it matches
			player[i].check(face_up_cards, *(face_up_cards.peek()), deck);
			//check if the player finished all the card in the hand  
			if (player[i].isempty())
			{
				cout << player[i].Getname() << "  has crushed their enemies in UNO (not even close)" << endl;
				solved = false;// break the while loop
				break;
			}
			//check if the deck is empty
			if (deck.isEmpty())
			{
				cout << "The deck has been repopulated" << endl;
				shared_ptr<Card> contain = face_up_cards.pop();//save the top card 
				while (!face_up_cards.isEmpty())
					deck.enqueue(face_up_cards.pop());//push all the left over to the deck
				face_up_cards.push(contain);//put the top card back
			}
		}
	}
}
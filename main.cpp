#include "UnoGame.h"

using namespace std;
template <class T>
void sortUsingOLF(List<shared_ptr<Card>>& hand)
{
	OrderedList<shared_ptr <Card>, T> temp;
	for (unsigned i = 1; i <= hand.getLength(); i++)
		temp.insert(hand.retrieve(i));
	for (unsigned i = 1; i <= hand.getLength(); i++)
		hand.replace(i, temp.retrieve(i));
}

void populate(Bag<shared_ptr<Card>> &bag)
{
	// make a bag add all the cards to it
	Suit s[] = { Red, Yellow, Green, Blue };
	Denomination d[] = { N1, N2, N3, N4, N5 };
	for (int k = 0; k < 2; k++)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 5; j++)
				bag.add(make_shared<Card>(s[i], d[j])); // add all the available cards
		}
	}
}



int main()
{
	srand((unsigned int)time(NULL));
	cout << "how many players: ";
	int ppl;
	cin >> ppl;
	UnoGame game(ppl);
	game.print();
	game.play();

	return 0;
}
#pragma once
#include <memory>
#include "OrderedList.h"
#include "Card.h"
#include "Bag.h"
#include "Stack.h"
#include "Queue.h"
class UnoPlayer
{
private:
	string name;
	OrderedList<shared_ptr<Card>> hand;
	int amount_of_card = 0;
public:
	UnoPlayer();
	~UnoPlayer();
	void populate(int num, Bag <shared_ptr<Card>> &bag);
	void print_hand();
	Card retrieve(int pos)const ;
	void check(Stack<shared_ptr<Card>>& a, Card temp, Queue<shared_ptr<Card>> &deck);
	int Getsize() const;
	void Setname(string input, int num);
	string Getname() const;
	bool isempty() const;
};


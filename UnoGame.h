#pragma once
#include <iostream>
#include <memory>
#include <time.h>
#include "LinkedList.h"
#include "Bag.h"
#include "OrderedList.h"
#include "UnoPlayer.h"
#include "Card.h"
#include "Stack.h"
#include "Queue.h"

#define num_of_players 3
#define num_of_cards 7

class UnoGame
{
private:
	UnoPlayer * player;
	Stack<shared_ptr<Card>> face_up_cards;
	Queue<shared_ptr<Card>> deck;
	int number_of_player;

public:
	UnoGame(int ppl);
	~UnoGame();
	void print();
	void play();
};


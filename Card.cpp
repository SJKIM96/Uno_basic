#include "Card.h"


Card::Card( Suit suit, Denomination deno)
{
	m_suit = suit;
	m_denomination = deno;
}


Card::~Card()
{
}

char Card::toCharSuit()
{
	if (m_suit == Red)   return 'R';
	else if (m_suit == Blue)    return 'B';
	else if (m_suit == Green)   return 'G';
	else                       return 'Y';
}

char Card::toCharDenomination()
{
	if (m_denomination == N1)
		return '1';
	else if (m_denomination == N2)	
		return '2';
	else if (m_denomination == N3)	
		return '3';
	else if (m_denomination == N4)	
		return '4';
	else if (m_denomination == N5)	
		return '5';
	else                          
		return 'a';
}

ostream& operator<<(ostream& os, const Card &c) {
	int suit = c.getSuit();
	int demo = c.getDenomination();
	
	switch (suit) {
	case 1:
		os <<  " Red ";
		break;
	case 2:
		os <<  " Yellow";
		break;
	case 3:
		os << " Green";
		break;
	default:
		os << " Blue";
	}
	os << demo;
	return os;
}
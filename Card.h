#pragma once
#include <iostream>
using namespace std;
//user definition
enum Suit { Red = 1, Yellow = 2, Green = 3, Blue = 4 };
enum Denomination { N1 =1, N2 = 2, N3 = 3, N4 = 4, N5 = 5};

//copied card from lab 9
class Card
{
private:
	Suit m_suit;
	Denomination m_denomination;
	
public:
	Card(Suit suit, Denomination deno);
	~Card();
	friend std::ostream& operator<<(std::ostream& os, const Card &c);
	inline Suit getSuit(void) const { return m_suit; }
	inline Denomination getDenomination(void) const { return m_denomination; }
	char toCharSuit(void); // returns a char that "describes" card's suit
	char toCharDenomination(void); // returns a char that "describes" card's denomination
};


inline bool operator<(const Card& a, const Card& b) {
	if (a.getSuit() == b.getSuit())
		return (a.getDenomination()<b.getDenomination());
	else                           
		return (a.getSuit()<b.getSuit());
}
inline bool operator>(const Card& a, const Card& b) {
	if (a.getSuit() == b.getSuit()) 
		return (a.getDenomination()>b.getDenomination());
	else                            
		return (a.getSuit()>b.getSuit());
}

// checks equality of suits and denominations for two cards
inline bool operator==(Card& a, Card& b) 
{ 
	return (a.getDenomination() == b.getDenomination() && a.getSuit() == b.getSuit()); 
}



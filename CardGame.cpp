#include <iostream>
#include <array>
#include <cstdlib>
#include <ctime>


enum Suit
{
	CLUB,
	DIAMOND,
	HEART,
	SPADE,
	MAX_SUIT
};


enum Rank
{
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
	ACE,
	MAX_RANK
};


enum BlackjackResult
{
	BLACKJACK_PLAYER_WIN,
	BLACKJACK_DEALER_WIN,
	BLACKJACK_DRAW
};


struct Card
{
	Suit suit_;
	Rank rank_;
};


void printCard(Card const &card)
{
	switch (card.rank_)
	{
	case TWO:
		std::cout << "2";	break;
	case THREE:
		std::cout << "3";	break;
	case FOUR:
		std::cout << "4";	break;
	case FIVE:
		std::cout << "5";	break;
	case SIX:
		std::cout << "6";	break;
	case SEVEN:
		std::cout << "7";	break;
	case EIGHT:
		std::cout << "8";	break;
	case NINE:
		std::cout << "9";	break;
	case TEN:
		std::cout << "10";	break;
	case JACK:
		std::cout << "J";	break;
	case QUEEN:
		std::cout << "Q";	break;
	case KING:
		std::cout << "K";	break;
	case ACE:
		std::cout << "A";	break;
	default:
		std::cout << "Unknown";	break;
	}

	switch (card.suit_)
	{
	case CLUB:
		std::cout << "C";	break;
	case DIAMOND:
		std::cout << "D";	break;
	case HEART:
		std::cout << "H";	break;
	case SPADE:
		std::cout << "S";	break;
	default:
		std::cout << "Unknown";	break;
	}
}


void printDeck(std::array<Card, 52> const &deck)
{
	for (const Card element: deck)
	{
		printCard(element);
		std::cout << ' ';
	}
	std::cout << std::endl;
}


void swapCard(Card &card1, Card &card2)
{
	Card temp = card1;
	card1 = card2;
	card2 = temp;
}


int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}


void shuffleDeck(std::array<Card, 52>& deck)
{
	for (int i = 0; i < 52; i++)
		swapCard(deck[i], deck[getRandomNumber(0, 51)]);
}


void shuffleAndPrintDeck(std::array<Card, 52>& deck)
{
	shuffleDeck(deck);
	printDeck(deck);
}


int getCardValue(Card &card)
{
	switch (card.rank_)
	{
	case TWO:
		return 2;	break;
	case THREE:
		return 3;	break;
	case FOUR:
		return 4;	break;
	case FIVE:
		return 5;	break;
	case SIX:
		return 6;	break;
	case SEVEN:
		return 7;	break;
	case EIGHT:
		return 8;	break;
	case NINE:
		return 9;	break;
	case TEN:
	case JACK:
	case QUEEN:
	case KING:
		return 10;	break;
	case ACE:
		return 11;	break;
	default:
		return -1;	break;
	}
}


BlackjackResult playBlackjack(std::array<Card, 52> & deck)
{
	Card* cardPtr = &deck[0];
	int dealerScore=0;
	int playerScore = 0;


	dealerScore += getCardValue(*cardPtr++);
	
	playerScore += getCardValue(*cardPtr++);

	int cardValue = getCardValue(*cardPtr++);						//If an ACE falls out, we decide what to add to the result 1 or 11.
	if (cardValue == 11)
		playerScore += ((playerScore <= 10) ? 11 : 1);
	else
		playerScore += cardValue;

	std::string answer;

	while (playerScore <= 21)
	{
		std::cout << "Player`s score: " << playerScore << std::endl;
		std::cout << "Do you want to hit or stand?	";
		std::cin >> answer;
		
		if (answer == "hit")
		{
			cardValue = getCardValue(*cardPtr++);					//If an ACE falls out, we decide what to add to the result 1 or 11.
			if (cardValue == 11)
				playerScore += ((playerScore <= 10) ? 11 : 1);
			else
				playerScore += cardValue;
		}
			
		if (answer == "stand")
			break;
	}
	
	if (playerScore > 21)
	{
		std::cout << "Player`s score: " << playerScore << std::endl;
		return BLACKJACK_DEALER_WIN;
	}
		
	while (dealerScore < 17)
	{
		cardValue = getCardValue(*cardPtr++);						//If an ACE falls out, we decide what to add to the result 1 or 11.
		if (cardValue == 11)
			dealerScore += ((dealerScore <= 10) ? 11 : 1);
		else
			dealerScore += cardValue;
	}
		

	std::cout << "Dealer`s score: " << dealerScore << std::endl;
	if (dealerScore > 21)
		return BLACKJACK_PLAYER_WIN;

	if (playerScore > dealerScore)
		return BLACKJACK_PLAYER_WIN;
	else if (playerScore == dealerScore)
		return BLACKJACK_DRAW;
	else
		return BLACKJACK_DEALER_WIN;	
}


int main()
{
	srand(static_cast<unsigned int>(time(0)));
	rand();

	std::array<Card, 52> deck;
	int numberOfCard = 0;
	for (int rank = 0; rank < MAX_RANK; rank++)
	{
		for (int suit = 0; suit < MAX_SUIT; suit++)
		{
			deck[numberOfCard].rank_ = static_cast<Rank>(rank);
			deck[numberOfCard].suit_ = static_cast<Suit>(suit);
			numberOfCard++;
		}
	}
	
	shuffleDeck(deck);
	
	switch (playBlackjack(deck))
	{
	case BLACKJACK_DEALER_WIN:
		std::cout << "You lose.";	break;
	case BLACKJACK_PLAYER_WIN:
		std::cout << "You win!";	break;
	case BLACKJACK_DRAW:
		std::cout << "Draw!";	break;
	default:
		break;
	}
}


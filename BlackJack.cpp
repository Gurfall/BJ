
#include <iostream>
#include <array>
#include <ctime> 
#include <cstdlib> 
#include <cassert>
#include "Deck.cpp"

#define Lose 0
#define Win 1
#define Draw 2






char getPlayerChoice()
{
	
	char choice;
	do
	{
		std::cout << "(h) to hit, or (s) to stand: ";
		std::cin >> choice;
		if (choice != 'h' && choice != 's')//проверка ввода игрока
		{
			std::cin.clear(); 
			std::cin.ignore(32767, '\n'); 
			continue;
		}
		break;
	} while (true);

	return choice;
}
int playBlackjack(Deck& deck)
{
	

	int playerTotal =0;
	int dealerTotal = 0;

	// Дилер получает одну карту
	dealerTotal += deck.dealCard().getCardValue();
	// Игрок получает две карты
	playerTotal += deck.dealCard().getCardValue();
	playerTotal += deck.dealCard().getCardValue();
	// Игрок начинает
	while (1)
	{
		std::cout << "You have: " << playerTotal << '\n';
		char choice = getPlayerChoice();
		if (choice == 's')
			break;

		playerTotal += deck.dealCard().getCardValue();

		
	}
	// Смотрим, не проиграл ли игрок
	if (playerTotal > 21)
	{
		std::cout << "You have: " << playerTotal << '\n';
		return Lose;
	}

	// Если игрок не проиграл (у него не больше 21 очка), тогда дилер получает карты до тех пор, пока у него в сумме будет не меньше 17 очков
	while (dealerTotal < 17)
	{
		dealerTotal += deck.dealCard().getCardValue();
	}
	std::cout << "dealer have : " << dealerTotal << std::endl;
	// Если у дилера больше 21, то он проиграл, а игрок выиграл
	if (dealerTotal > 21)
		return Win ;

	if (playerTotal == dealerTotal)
		return Draw;
	else if (playerTotal > dealerTotal)
		return Win;
	else
		return Lose;
}
int main()
{	
	srand(static_cast<unsigned int>(time(0))); 
	rand(); // делаем сброс первого случайного числа

	Deck deck;

	std::string newGameChoise;
	do
	{	
		deck.shuffleDeck();// перемешиваем колоду перед игрой
		switch (playBlackjack(deck))// начинаем игру и сообщаем результат
		{
		case Lose: 
			std::cout << "You lose!\n";
			break;
		case Win: 
			std::cout << "You win!\n"; 
			break;
		default:
			std::cout << "Draw!\n";
			break; 
		}
		

		std::cout << "Do you want play one more game? (yes/no)" << std::endl;// предлагаем сыграть еще 1 игру
		while (true)// простая проверка на ввод
		{
			std::cin >> newGameChoise;
			if (newGameChoise == "yes" || newGameChoise == "no")
				
				break;
			else
				std::cout << "repeat the input" << std::endl;
		}	
	} while (newGameChoise != "no");

	return 0;
}
// CardGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>

enum class CardSuit
{
    club,
    diamond,
    heart,
    spade,

    max_suits
};

enum class CardRank
{
    rank_2,
    rank_3,
    rank_4,
    rank_5,
    rank_6,
    rank_7,
    rank_8,
    rank_9,
    rank_10,
    jack,
    queen,
    king,
    ace,

    max_ranks
};

struct Card {
    CardRank rank{};
    CardSuit suit{};
};

void printCard(const Card& card)
{
    switch (card.rank)
    {
        case CardRank::rank_2:      std::cout << '2';   break;
        case CardRank::rank_3:      std::cout << '3';   break;
        case CardRank::rank_4:      std::cout << '4';   break;
        case CardRank::rank_5:      std::cout << '5';   break;
        case CardRank::rank_6:      std::cout << '6';   break;
        case CardRank::rank_7:      std::cout << '7';   break;
        case CardRank::rank_8:      std::cout << '8';   break;
        case CardRank::rank_9:      std::cout << '9';   break;
        case CardRank::rank_10:     std::cout << 'T';   break;
        case CardRank::jack:        std::cout << 'J';   break;
        case CardRank::queen:       std::cout << 'Q';   break;
        case CardRank::king:        std::cout << 'K';   break;
        case CardRank::ace:         std::cout << 'A';   break;
        default:
            std::cout << '?';
            break;
    }

    switch (card.suit)
    {
        case CardSuit::club:       std::cout << 'C';   break;
        case CardSuit::diamond:    std::cout << 'D';   break;
        case CardSuit::heart:      std::cout << 'H';   break;
        case CardSuit::spade:      std::cout << 'S';   break;
        default:
            std::cout << '?';
            break;
    }
}


int main()
{
    std::cout << "Hello World!\n";
}

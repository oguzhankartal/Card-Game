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

int main()
{
    std::cout << "Hello World!\n";
}

// CardGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <array>
#include <algorithm> // for std::shuffle
#include <ctime> // for std::time
#include <random> // for std::mt19937
#include <cassert>

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

struct Player {
    int score{};
};

constexpr int g_maximumScore{ 21 };
constexpr int g_minimumDealerScore{ 17 };

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

using deck_type = std::array<Card, 52>;
using index_type = deck_type::size_type;

deck_type createDeck()
{
    deck_type deck{};

    index_type index{ 0 };

    for (int suit{ 0 }; suit < static_cast<int>(CardSuit::max_suits); ++suit)
    {
        for (int rank{ 0 }; rank < static_cast<int>(CardRank::max_ranks); ++rank)
        {
            deck[index].suit = static_cast<CardSuit>(suit);
            deck[index].rank = static_cast<CardRank>(rank);
            ++index;
        }
    }

    return deck;
}

void printDeck(const deck_type& deck)
{
    for (const auto& card : deck)
    {
        printCard(card);
        std::cout << ' ';
    }

    std::cout << '\n';
}

void shuffleDeck(deck_type& deck)
{
    static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr) };

    std::shuffle(deck.begin(), deck.end(), mt);
}

int getCardValue(const Card& card)
{
    switch (card.rank)
    {
    case CardRank::rank_2:        return 2;
    case CardRank::rank_3:        return 3;
    case CardRank::rank_4:        return 4;
    case CardRank::rank_5:        return 5;
    case CardRank::rank_6:        return 6;
    case CardRank::rank_7:        return 7;
    case CardRank::rank_8:        return 8;
    case CardRank::rank_9:        return 9;
    case CardRank::rank_10:       return 10;
    case CardRank::jack:     return 10;
    case CardRank::queen:    return 10;
    case CardRank::king:     return 10;
    case CardRank::ace:      return 11;
    default:
        assert(false && "should never happen");
        return 0;
    }
}

bool playerWantsHit()
{
    while (true)
    {
        std::cout << "(h) to hit, or (s) to stand: ";
        char ch{};
        std::cin >> ch;

        switch (ch) 
        {
        case 'h':
            return true;
        case 's':
            return false;
        }
    }
}

// Returns true if the player went bust. False otherwise.
bool playerTurn(const deck_type& deck, index_type& nextCardIndex, Player& player)
{
    while (true)
    {
        if (player.score > g_maximumScore)
        {
            std::cout << "You busted!\n";
            return true;
        }
        else
        {
            if (playerWantsHit())
            {
                int cardValue{ getCardValue(deck.at(nextCardIndex++)) };
                player.score += cardValue;
                std::cout << "You were dealt a " << cardValue << " and now have " << player.score << '\n';
            }
            else
            {
                return false;
            }
        }
    }
}

// Returns true if the dealer went bust. False otherwise.
bool dealerTurn(const deck_type& deck, index_type& nextCardIndex, Player& dealer)
{
    while (dealer.score < g_minimumDealerScore)
    {
        int cardValue{ getCardValue(deck.at(nextCardIndex++)) };
        dealer.score += cardValue;
        std::cout << "The dealer turned up a " << cardValue << " and now has " << dealer.score << '\n';
    }

    if (dealer.score > g_maximumScore)
    {
        std::cout << "The dealer busted!\n";
        return true;
    }

    return false;
}

bool playBlackjack(const deck_type& deck)
{
    index_type nextCardIndex{ 0 };

    Player dealer{ getCardValue(deck.at(nextCardIndex++)) };

    std::cout << "The dealer is showing: " << dealer.score << '\n';

    Player player{ getCardValue(deck.at(nextCardIndex)) + getCardValue(deck.at(nextCardIndex + 1)) };

    nextCardIndex += 2;

    std::cout << "You have: " << player.score << '\n';

    if (playerTurn(deck, nextCardIndex, player)) 
    {
        // playerTurn returns true if player went bust.
        return false;
    }

    if (dealerTurn(deck, nextCardIndex, dealer))
    {
        // dealerTurn returns true if dealer went bust.
        // Thus, the player wins.
        return true;
    }

    return (player.score > dealer.score);
}


int main()
{
    auto deck{ createDeck() };

    shuffleDeck(deck);

    if (playBlackjack(deck))
    {
        std::cout << "You win!\n";
    }
    else
    {
        std::cout << "You lose!\n";
    }

    return 0;
}

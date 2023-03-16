#include <iostream>
#include <array>
#include <algorithm>
#include <random>
#include <ctime>

/*Card ranks and suits*/
enum class Ranks
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
    Jack,
    Queen,
    King,
    Ace,
    max_ranks
};

enum class Suits
{
    Club,
    Diamond,
    Heart,
    Spade,
    max_suits
};

struct Card
{
    Suits suit{};
    Ranks rank{};
};


// Print Card to the user
void printCard(const Card& card)
{
    switch(card.rank)
    {
        case Ranks::rank_2: std::cout << "2";break;
        case Ranks::rank_3: std::cout << "3";break;
        case Ranks::rank_4: std::cout << "4";break;
        case Ranks::rank_5: std::cout << "5";break;
        case Ranks::rank_6: std::cout << "6";break;
        case Ranks::rank_7: std::cout << "7";break;
        case Ranks::rank_8: std::cout << "8";break;
        case Ranks::rank_9: std::cout << "9";break; 
        case Ranks::rank_10: std::cout << "10"; break;
        case Ranks::Jack: std::cout << "J";break;
        case Ranks::Queen: std::cout << "Q";break;
        case Ranks::King: std::cout << "K";break;
        case Ranks::Ace: std::cout << "A";break;
    }

    switch(card.suit)
    {
        case Suits::Club: std::cout << "C";break;
        case Suits::Diamond: std::cout << "D";break;
        case Suits::Heart: std::cout << "H";break;
        case Suits::Spade: std::cout << "S";break;
    } 
}

// Create type alias with using
using Deck = std::array<Card, 52>;
using Index = Deck::size_type;



// Create Deck of 52 cards
Deck createDeck()
{
    Deck deck{};
    Index index{0};

    for (int suit{0}; suit < static_cast<int>(Suits::max_suits); ++suit)
    {
        for (int rank{0}; rank < static_cast<int>(Ranks::max_ranks); ++rank)
        {
            deck[index].rank = static_cast<Ranks>(rank);
            deck[index].suit = static_cast<Suits>(suit);
            ++index;
        }
    }
    return deck;
}

// Shuffle deck using MT 
void shuffleDeck(Deck& deck)
{
    std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    std::shuffle(deck.begin(), deck.end(), mt);
}


// Get card value 
int getCardValue(const Card& card)
{
    switch(card.rank)
    {
        case Ranks::rank_2: return 2; break;
        case Ranks::rank_3: return 3; break;
        case Ranks::rank_4: return 4; break;
        case Ranks::rank_5: return 5; break;
        case Ranks::rank_6: return 6; break;
        case Ranks::rank_7: return 7; break;
        case Ranks::rank_8: return 8; break;
        case Ranks::rank_9: return 9; break;
        case Ranks::rank_10: return 10; break;
        case Ranks::Jack: return 11; break;
        case Ranks::Queen: return 12; break;
        case Ranks::King: return 13; break;
        case Ranks::Ace: return 14; break;
        default: return 0;
    }
}

void printDeck(const Deck& deck)
{
    for (const auto& card : deck)
    {
        printCard(card);
        std::cout << " "; 
    }
}

bool playerPlay()
{
    while (true)
    {
        char ch{};
        std::cin >> ch;

        if (ch == 'g')
        {
            return true;
        }
        return false;
    }
}

bool playWar(const Deck& deck)
{
    // Split deck // doesnt work !
    Deck playerDeck{};
    Deck compDeck{};
    for (int i{0}, j{26}; i < 26; ++i, ++j)
    {
        playerDeck[i] = deck[i];
        compDeck[i] = deck[j]; 
    }
    printDeck(deck);
    std::cout << '\n';
    printDeck(playerDeck);
    std::cout << '\n';
    printDeck(compDeck);


    while (true)
    {

        std::cout << "Press 'g' to lay your card!";
        if (playerPlay())
        {
            std::cout << "Game on!" << std::endl;
        }
        else
        {
            std::cout << "Wrong key!" << std::endl;
        }
    }
}

int main()
{
    auto deck{ createDeck() };
    shuffleDeck(deck);


    playWar(deck);

    return 0;
}
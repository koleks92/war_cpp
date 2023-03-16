#include <iostream>
#include <array>
#include <algorithm>
#include <random>
#include <ctime>
#include <limits>

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
        case Ranks::rank_2: std::cout << "2 of ";break;
        case Ranks::rank_3: std::cout << "3 of ";break;
        case Ranks::rank_4: std::cout << "4 of ";break;
        case Ranks::rank_5: std::cout << "5 of ";break;
        case Ranks::rank_6: std::cout << "6 of ";break;
        case Ranks::rank_7: std::cout << "7 of ";break;
        case Ranks::rank_8: std::cout << "8 of ";break;
        case Ranks::rank_9: std::cout << "9 of ";break; 
        case Ranks::rank_10: std::cout << "10 of "; break;
        case Ranks::Jack: std::cout << "Jack of ";break;
        case Ranks::Queen: std::cout << "Queen of ";break;
        case Ranks::King: std::cout << "King of ";break;
        case Ranks::Ace: std::cout << "Ace of ";break;
    }

    switch(card.suit)
    {
        case Suits::Club: std::cout << "Clubs";break;
        case Suits::Diamond: std::cout << "Diamonds";break;
        case Suits::Heart: std::cout << "Hearts";break;
        case Suits::Spade: std::cout << "Spades";break;
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

// Ask to lay a card
bool playerPlay()
{
    while (true)
    {
        std::cout << "Press 'g' to lay your card! ";
        char ch{};
        std::cin >> ch;

        if (ch == 'g' || ch == 'G')
        {
            return true;
        }
        return false;
    }
}

// Ask if wanna play the game
bool playAgain()
{
    char ch;
    std::cout << "Do you want to play again (y/n)? ";
    std::cin >> ch;
    if (ch == 'y' || ch == 'Y')
    {
        system("clear");
        return true;
    }
    else
    {
        system("clear");
        return false;
    }
}

bool fight(Deck& deck)
{
    while (true)
    {
        system("clear");
        shuffleDeck(deck);
        int howMany{};
        while (true)
        {
            std::cout << "How many cards ? (2-8) ";
            std::cin >> howMany;
            if (!std::cin)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max());
            }
            else if (howMany > 8 | howMany < 2)
            {
                std::cout << "Number is too big or too small!" << '\n';
            }
            else
            {
                break;
            }

        }
        int playerValue{};
        int computerValue{};

        std::cout << "Player got: ";
        for (int i{0}; i < howMany; ++i)
        {
            printCard(deck[i]);
            playerValue += getCardValue(deck[i]);
            std::cout << " || ";
        }
        std::cout << '\n' << "With total value of " << playerValue << '\n';

        std::cout << "Computer got: ";
        for (int i{25}; i < (howMany + 25); ++i)
        {
            printCard(deck[i]);
            computerValue += getCardValue(deck[i]);
            std::cout << " || ";
        }
        std::cout << '\n' << "With total value of " << computerValue << '\n';

        if (playerValue > computerValue)
        {
            std::cout << "Player won 8 points!" << '\n';
            return true;
        }
        else if (computerValue > playerValue)
        {
            std::cout << "Computer won 8 points!" << '\n';
            return false;
        }
        else
        {
            std::cout << "Tie!" << '\n' << "Let's do it again!" << '\n';
            continue;
        }
    }
}


// Main game function
bool playWar(Deck& deck)
{   // Total amount of won games
    int playerWins{0};
    int computerWins{0};
    // Current game scores and card index
    int playerScore{0};
    int computerScore{0};
    Index initIndex{0};
    // Shuffle the deck
    shuffleDeck(deck);

    // Welcome message and clear the screen
    system("clear");
    std::cout << "Welcome to WAR game !" << '\n';
    std::cout << "Game was created by koleks92" << '\n';
    std::cout << "Enjoy!" << '\n';
   
    while (true)
    {
        if (playerPlay())
        {
            system("clear");
            std::cout << "Player has: ";
            printCard(deck[initIndex]);
            std::cout << '\n' << "Computer has: ";
            printCard(deck[initIndex + 1]);
            std::cout << '\n';
            if (getCardValue(deck[initIndex]) > getCardValue(deck[initIndex+1]))
            {
                playerScore += 2;
                std::cout << "Player gets 2 points" << '\n';
                std::cout << "Player " << playerScore << " || " << "Computer " << computerScore << '\n';

            }
            else if (getCardValue(deck[initIndex]) < getCardValue(deck[initIndex+1]))
            {
                computerScore += 2;
                std::cout << "Computer gets 2 points" << '\n';
                std::cout << "Player " << playerScore << " || " << "Computer " << computerScore << '\n';
            }
            else
            {
                std::cout << "It's a fight !" << '\n' << "Do you dare to fight(y/n) ? ";
                char ch{};
                std::cin >> ch;
                if (ch == 'y' || ch == 'Y')
                {
                    if (fight(deck))
                    {
                        playerScore += 8;
                    }
                    else
                    {
                        computerScore += 8;
                    }
                }
                else
                {
                std::cout << "Player " << playerScore << " || " << "Computer " << computerScore << '\n';
                ++playerScore;
                ++computerScore;
                }
            }

            initIndex += 2;
            // When hits the end of the deck 
            if (initIndex >= 52)
            {
                system("clear");
                std::cout << "Player has " << playerScore << " and Computer has " << computerScore << '\n';
                if (playerScore > computerScore)
                {
                    ++playerWins;
                    std::cout << "Player won this game !" << '\n';
                }
                else if (computerScore > playerScore)
                {
                    ++computerWins;
                    std::cout << "Computer won this game !" << '\n';
                }
                else
                {
                    std::cout << "It's a tie !" << '\n';
                }
                if (playAgain())
                {
                    // Reset current game scores and shuffle the deck
                    computerScore = 0;
                    playerScore = 0;
                    initIndex = 0;
                    shuffleDeck(deck);
                    continue;
                }
                else
                {
                    std::cout << "Player won " << playerWins << " times!" << '\n';
                    std::cout << "Computer won " << computerWins << " times!" << '\n';
                    std::cout << "Thanks for playing !" << '\n';
                }
                return false;
            }  
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
    playWar(deck);

    return 0;
}
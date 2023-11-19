#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

enum Rank {
    ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
};

enum Suit {
    HEARTS, DIAMONDS, CLUBS, SPADES
};

struct Card {
    Rank rank;
    Suit suit;
};

void displayCard(const Card& card) {
    std::cout << "Card: ";
    switch (card.rank) {
        case ACE: std::cout << "Ace"; break;
        case JACK: std::cout << "Jack"; break;
        case QUEEN: std::cout << "Queen"; break;
        case KING: std::cout << "King"; break;
        default: std::cout << static_cast<int>(card.rank);
    }

    std::cout << " of ";
    switch (card.suit) {
        case HEARTS: std::cout << "Hearts"; break;
        case DIAMONDS: std::cout << "Diamonds"; break;
        case CLUBS: std::cout << "Clubs"; break;
        case SPADES: std::cout << "Spades"; break;
    }

    std::cout << std::endl;
}

Card drawCard() {
    Card card;
    card.rank = static_cast<Rank>(1 + rand() % 13);  // Random rank between 1 and 13
    card.suit = static_cast<Suit>(rand() % 4);      // Random suit between 0 and 3
    return card;
}

bool isHigher(const Card& first, const Card& second) {
    return static_cast<int>(first.rank) < static_cast<int>(second.rank);
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    int score = 0;
    char choice;

    do {
        Card currentCard = drawCard();
        Card nextCard = drawCard();

        std::cout << "Current Card:\n";
        displayCard(currentCard);

        do {
            std::cout << "Will the next card be higher or lower? (h/l): ";
            std::cin >> choice;

            if (choice != 'h' && choice != 'l') {
                std::cout << "Please enter a correct option ('h' or 'l').\n";
            }
        } while (choice != 'h' && choice != 'l');

        std::cout << "Next Card:\n";
        displayCard(nextCard);

        if ((choice == 'h' && isHigher(currentCard, nextCard)) || (choice == 'l' && !isHigher(currentCard, nextCard))) {
            std::cout << "Correct! You gain " << static_cast<int>(nextCard.rank) << " points.\n";
            score += static_cast<int>(nextCard.rank);
        } else {
            std::cout << "Incorrect! You lose " << static_cast<int>(nextCard.rank) << " points.\n";
            score -= static_cast<int>(nextCard.rank);
        }

        std::cout << "Your current score: " << score << "\n";
        std::cout << "Do you want to continue? (y/n): ";
        std::cin >> choice;

    } while (choice == 'y');

    std::cout << "Your final score is: " << score << "\n";
    std::cout << "Press Enter to exit...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();  // Wait for the user to press Enter before closing

    return 0;
}

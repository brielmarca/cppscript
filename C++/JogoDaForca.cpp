#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <map>
#include <algorithm>
#include <cctype>
using namespace std;

// Function to clear the prompt/terminal
void clearScreen() {
    #ifdef _WIN32
        system("cls"); // For Windows
    #else
        system("clear"); // For Linux/macOS
    #endif
}

// Function to display the current state of the hangman
void displayHangman(int mistakes) {
    const vector<string> hangmanStages = {
        "  +---+\n      |\n      |\n      |\n     ===",
        "  +---+\n  O   |\n      |\n      |\n     ===",
        "  +---+\n  O   |\n  |   |\n      |\n     ===",
        "  +---+\n  O   |\n /|   |\n      |\n     ===",
        "  +---+\n  O   |\n /|\\  |\n      |\n     ===",
        "  +---+\n  O   |\n /|\\  |\n /    |\n     ===",
        "  +---+\n  O   |\n /|\\  |\n / \\  |\n     ==="
    };
    cout << hangmanStages[mistakes] << endl;
}

// Function to choose a random word from a category
string chooseWord(const map<string, vector<string>>& categories, string& selectedCategory) {
    srand(static_cast<unsigned>(time(0)));
    auto it = next(categories.begin(), rand() % categories.size());
    selectedCategory = it->first;
    return it->second[rand() % it->second.size()];
}

// Function to display game statistics
void displayStats(int gamesPlayed, int gamesWon) {
    cout << "\n--- Statistics ---\n";
    cout << "Games played: " << gamesPlayed << "\n";
    cout << "Games won: " << gamesWon << "\n";
    cout << "Win rate: " << (gamesPlayed > 0 ? (gamesWon * 100.0 / gamesPlayed) : 0) << "%\n";
}

// Function to check if a letter is valid
bool isValidLetter(char letter) {
    return isalpha(letter);
}

// Function to display the hidden word with guessed letters
void displayHiddenWord(const string& hiddenWord, const vector<char>& attemptedLetters) {
    cout << "\nWord: " << hiddenWord << "\n";
    cout << "Attempted letters: ";
    for (char letter : attemptedLetters) cout << letter << " ";
    cout << "\n";
}

// Main game function
void playHangman() {
    const map<string, vector<string>> categories = {
        {"Animals", {"dog", "cat", "elephant", "tiger", "alligator"}},
        {"Countries", {"brazil", "portugal", "canada", "germany", "japan"}},
        {"Technology", {"computer", "internet", "programming", "keyboard", "python"}}
    };

    int gamesPlayed = 0, gamesWon = 0;
    char playAgain;

    do {
        clearScreen(); // Clear the prompt before starting a new game

        string selectedCategory;
        string word = chooseWord(categories, selectedCategory);
        string hiddenWord(word.size(), '_');
        int mistakes = 0;
        const int maxMistakes = 6;
        vector<char> attemptedLetters;

        cout << "\n--- Hangman Game ---\n";
        cout << "Category: " << selectedCategory << "\n";

        while (mistakes < maxMistakes && hiddenWord != word) {
            displayHiddenWord(hiddenWord, attemptedLetters);
            displayHangman(mistakes);

            cout << "Enter a letter: ";
            char guess;
            cin >> guess;
            guess = tolower(guess);

            if (!isValidLetter(guess)) {
                cout << "Invalid input. Please enter a valid letter.\n";
                continue;
            }

            if (find(attemptedLetters.begin(), attemptedLetters.end(), guess) != attemptedLetters.end()) {
                cout << "You already tried this letter. Try another one.\n";
                continue;
            }

            attemptedLetters.push_back(guess);

            if (word.find(guess) != string::npos) {
                for (size_t i = 0; i < word.size(); ++i) {
                    if (word[i] == guess) {
                        hiddenWord[i] = guess;
                    }
                }
            } else {
                mistakes++;
                cout << "Incorrect letter! You have " << maxMistakes - mistakes << " attempts left.\n";
            }
        }

        if (hiddenWord == word) {
            cout << "\nCongratulations! You guessed the word: " << word << "\n";
            gamesWon++;
        } else {
            cout << "\nToo bad! The word was: " << word << "\n";
        }

        gamesPlayed++;
        displayStats(gamesPlayed, gamesWon);

        cout << "\nDo you want to play again? (y/n): ";
        cin >> playAgain;
        playAgain = tolower(playAgain);

    } while (playAgain == 'y');

    cout << "\nThanks for playing! See you next time!\n";
}

int main() {
    playHangman();
    return 0;
}
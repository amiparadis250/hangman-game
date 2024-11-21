#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm> // For std::find
#include <cctype>    // For toupper() and tolower()
using namespace std;

// Function to display the current state of the word and incorrect guesses
void displayGame(const string& word, const string& guessedWord, const vector<char>& incorrectGuesses, int guessesLeft) {
    cout << "\nWord: ";
    for (char ch : guessedWord) {
        cout << ch << " ";
    }
    cout << "\nIncorrect Guesses: ";
    for (char ch : incorrectGuesses) {
        cout << ch << " ";
    }
    cout << "\nGuesses Left: " << guessesLeft << "\n";
}

// Function to check if the player has won
bool isWordGuessed(const string& word, const string& guessedWord) {
    return word == guessedWord;
}

// Main Hangman game logic
void playHangman() {
    // Predefined list of words
    vector<string> wordList = {"teacher", "hangman", "computer", "programming", "science", "gameplay", "library", "coding"};

    // Randomly select a word from the list
    srand(time(0));
    string word = wordList[rand() % wordList.size()];

    // Prepare the guessed word (initially filled with underscores)
    string guessedWord(word.size(), '_');

    // Variables to keep track of incorrect guesses and remaining guesses
    vector<char> incorrectGuesses;
    int maxGuesses = 6;
    int guessesLeft = maxGuesses;

    // Welcome message
    cout << "Welcome to Hangman!\n";

    // Game loop
    while (guessesLeft > 0) {
        // Display the game state
        displayGame(word, guessedWord, incorrectGuesses, guessesLeft);

        // Take the player's guess
        cout << "Guess a letter: ";
        char guess;
        cin >> guess;
        guess = tolower(guess);

        // Validate input
        if (!isalpha(guess)) {
            cout << "Invalid input! Please enter a letter.\n";
            continue;
        }

        // Check if the letter was already guessed
        if (guessedWord.find(guess) != string::npos || 
            std::find(incorrectGuesses.begin(), incorrectGuesses.end(), guess) != incorrectGuesses.end()) {
            cout << "You already guessed that letter! Try again.\n";
            continue;
        }

        // Process the guess
        bool correctGuess = false;
        for (size_t i = 0; i < word.size(); i++) {
            if (word[i] == guess) {
                guessedWord[i] = guess;
                correctGuess = true;
            }
        }

        // If the guess is incorrect, update the incorrect guesses and reduce guesses left
        if (!correctGuess) {
            incorrectGuesses.push_back(guess);
            guessesLeft--;
        }

        // Check win condition
        if (isWordGuessed(word, guessedWord)) {
            cout << "\nCongratulations! You guessed the word \"" << word << "\" correctly!\n";
            return;
        }
    }

    // If the loop ends, the player lost
    cout << "\nGame Over! You ran out of guesses. The correct word was \"" << word << "\".\n";
}

int main() {
    char playAgain;

    do {
        playHangman();
        cout << "\nDo you want to play again? (y/n): ";
        cin >> playAgain;
        playAgain = tolower(playAgain);
    } while (playAgain == 'y');

    cout << "Thanks for playing Hangman!\n";
    return 0;
}

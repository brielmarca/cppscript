#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <iomanip>
#include <limits>

using namespace std;

// Função para limpar o buffer de entrada
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Função para converter uma string para minúsculas
string toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Função para exibir o menu
void displayMenu() {
    cout << "\n=== Text Analyzer ===\n";
    cout << "1. Load text file\n";
    cout << "2. Show statistics\n";
    cout << "3. Show unique words\n";
    cout << "4. Show most frequent word\n";
    cout << "5. Generate word frequency histogram\n";
    cout << "6. Exit\n";
    cout << "Choose an option: ";
}

// Função para limpar a tela do console
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Função para carregar o arquivo e processar as palavras
bool loadFile(const string& filename, vector<string>& words, map<string, int>& wordFrequency, set<string>& uniqueWords, int& totalWords, int& totalSentences, int& totalLines) {
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file: " << filename << "\n";
        return false;
    }

    words.clear();
    wordFrequency.clear();
    uniqueWords.clear();
    totalWords = 0;
    totalSentences = 0;
    totalLines = 0;

    set<string> commonWords = { "o", "a", "e", "de", "do", "da", "em", "no", "na", "que", "com" };
    string line;

    while (getline(file, line)) {
        totalLines++;
        string word;
        for (char ch : line) {
            if (isalpha(ch) || ch == '\'') {
                word += tolower(ch);
            } else if (ch == '.' || ch == '!' || ch == '?') {
                totalSentences++;
            } else if (!word.empty()) {
                if (commonWords.find(word) == commonWords.end()) {
                    words.push_back(word);
                    wordFrequency[word]++;
                    uniqueWords.insert(word);
                }
                word.clear();
            }
        }
        if (!word.empty() && commonWords.find(word) == commonWords.end()) {
            words.push_back(word);
            wordFrequency[word]++;
            uniqueWords.insert(word);
        }
    }
    totalWords = words.size();
    return true;
}

// Função principal
int main() {
    vector<string> words;
    map<string, int> wordFrequency;
    set<string> uniqueWords;
    int totalWords = 0, totalSentences = 0, totalLines = 0;
    string filename;

    while (true) {
        displayMenu();
        int choice;
        cin >> choice;

        if (choice == 6) {
            cout << "Exiting the program. Goodbye!\n";
            break;
        }

        switch (choice) {
            case 1: {
                cout << "Enter the filename: ";
                cin >> filename;
                if (loadFile(filename, words, wordFrequency, uniqueWords, totalWords, totalSentences, totalLines)) {
                    cout << "File loaded successfully.\n";
                }
                break;
            }
            case 2: {
                cout << "Total words: " << totalWords << "\n";
                cout << "Total sentences: " << totalSentences << "\n";
                cout << "Total lines: " << totalLines << "\n";
                break;
            }
            case 3: {
                cout << "Unique words:\n";
                for (const string& word : uniqueWords) {
                    cout << word << "\n";
                }
                break;
            }
            case 4: {
                if (wordFrequency.empty()) {
                    cout << "No words to analyze.\n";
                    break;
                }
                auto mostFrequent = max_element(wordFrequency.begin(), wordFrequency.end(),
                    [](const pair<string, int>& a, const pair<string, int>& b) {
                        return a.second < b.second;
                    });
                cout << "Most frequent word: " << mostFrequent->first << " (" << mostFrequent->second << " occurrences)\n";
                break;
            }
            case 5: {
                if (wordFrequency.empty()) {
                    cout << "No words to analyze.\n";
                    break;
                }
                cout << "Word frequency histogram:\n";
                for (const auto& pair : wordFrequency) {
                    cout << setw(15) << pair.first << ": " << string(pair.second, '*') << "\n";
                }
                break;
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
                clearInput();
                break;
            }
        }

        // Limpa a tela após cada operação
        cout << "\nPress Enter to continue...";
        clearInput();
        clearScreen();
    }

    return 0;
}
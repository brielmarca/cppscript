#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <limits> // Para limpar o buffer de entrada

using namespace std;

// Function to generate a secure password
string generatePassword(int length, bool includeUppercase, bool includeNumbers, bool includeSpecials) {
    const string lowercase = "abcdefghijklmnopqrstuvwxyz";
    const string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string numbers = "0123456789";
    const string specials = "!@#$%^&*()-_=+[]{}|;:,.<>?";
    string availableCharacters = lowercase;

    if (includeUppercase) availableCharacters += uppercase;
    if (includeNumbers) availableCharacters += numbers;
    if (includeSpecials) availableCharacters += specials;

    if (availableCharacters.empty()) {
        throw invalid_argument("No character set selected to generate the password.");
    }

    string password;
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> distribution(0, availableCharacters.size() - 1);

    for (int i = 0; i < length; ++i) {
        password += availableCharacters[distribution(generator)];
    }

    return password;
}

// Function to "encrypt" a password (simple simulation)
string encryptPassword(const string& password) {
    string encryptedPassword;
    for (char c : password) {
        encryptedPassword += static_cast<char>(c + 3); // Shift character 3 positions in ASCII
    }
    return encryptedPassword;
}

// Function to save the password to a file
void savePassword(const string& password, const string& filename) {
    ofstream file(filename, ios::app); // Open file in append mode
    if (file.is_open()) {
        file << password << endl;
        file.close();
        cout << "Password successfully saved to " << filename << "!" << endl;
    } else {
        cerr << "Error opening file " << filename << "!" << endl;
    }
}

// Function to clear the input buffer
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Function to convert "yes" or "no" to boolean
bool yesNoToBool(const string& input) {
    if (input == "yes" || input == "y" || input == "YES" || input == "Y") {
        return true;
    } else if (input == "no" || input == "n" || input == "NO" || input == "N") {
        return false;
    } else {
        throw invalid_argument("Invalid input. Please enter 'yes' or 'no'.");
    }
}

// Function to display the main menu
void displayMenu() {
    cout << "\n=== Password Generator ===\n";
    cout << "1. Generate and Save Password\n";
    cout << "2. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    try {
        int choice;
        while (true) {
            displayMenu();

            // Validate user input for the choice
            while (!(cin >> choice) || choice < 1 || choice > 2) {
                cout << "Invalid input. Please choose 1 or 2: ";
                clearInput();
            }

            if (choice == 2) {
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            }

            int length;
            string includeUppercase, includeNumbers, includeSpecials;
            string filename;

            // Get password length
            cout << "Enter the password length: ";
            while (!(cin >> length) || length <= 0) {
                cout << "Invalid input. Password length must be greater than 0: ";
                clearInput();
            }

            // Get character set preferences
            cout << "Include uppercase letters? (yes/no): ";
            while (cin >> includeUppercase) {
                try {
                    bool includeUpper = yesNoToBool(includeUppercase);
                    break;
                } catch (const invalid_argument& e) {
                    cout << e.what() << " Please enter 'yes' or 'no': ";
                    clearInput();
                }
            }

            cout << "Include numbers? (yes/no): ";
            while (cin >> includeNumbers) {
                try {
                    bool includeNum = yesNoToBool(includeNumbers);
                    break;
                } catch (const invalid_argument& e) {
                    cout << e.what() << " Please enter 'yes' or 'no': ";
                    clearInput();
                }
            }

            cout << "Include special characters? (yes/no): ";
            while (cin >> includeSpecials) {
                try {
                    bool includeSpec = yesNoToBool(includeSpecials);
                    break;
                } catch (const invalid_argument& e) {
                    cout << e.what() << " Please enter 'yes' or 'no': ";
                    clearInput();
                }
            }

            // Get filename to save the password
            cout << "Enter the filename to save the password: ";
            cin >> filename;

            // Generate and display the password
            string generatedPassword = generatePassword(length, yesNoToBool(includeUppercase), yesNoToBool(includeNumbers), yesNoToBool(includeSpecials));
            cout << "Generated Password: " << generatedPassword << endl;

            // Encrypt the password
            string encryptedPassword = encryptPassword(generatedPassword);
            cout << "Encrypted Password: " << encryptedPassword << endl;

            // Save the encrypted password to the file
            savePassword(encryptedPassword, filename);
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
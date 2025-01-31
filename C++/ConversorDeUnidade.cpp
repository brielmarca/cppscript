#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib> // For system()

using namespace std;

// Function to clear the input buffer
void clearInput() {
    cin.clear(); // Clear error state of cin
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line
}

// Function to convert units
double convert(double value, double factor, double offset = 0) {
    return value * factor + offset;
}

// Function to convert units in the reverse direction
double convertInverse(double value, double factor, double offset = 0) {
    return (value - offset) / factor;
}

// Function to display the menu
void displayMenu() {
    cout << "\n=== Unit Converter ===\n";
    cout << "1. Celsius to Fahrenheit\n";
    cout << "2. Fahrenheit to Celsius\n";
    cout << "3. Kilometers to Miles\n";
    cout << "4. Miles to Kilometers\n";
    cout << "5. Kilograms to Pounds\n";
    cout << "6. Pounds to Kilograms\n";
    cout << "7. Exit\n";
    cout << "Choose an option: ";
}

// Function to clear the console screen
void clearScreen() {
    #ifdef _WIN32
        system("cls"); // For Windows
    #else
        system("clear"); // For Linux/macOS
    #endif
}

int main() {
    // Constants for conversion factors
    const double CELSIUS_TO_FAHRENHEIT_FACTOR = 9.0 / 5.0;
    const double CELSIUS_TO_FAHRENHEIT_OFFSET = 32;
    const double KILOMETERS_TO_MILES_FACTOR = 0.621371;
    const double KILOGRAMS_TO_POUNDS_FACTOR = 2.20462;

    int choice;
    double value;

    while (true) {
        displayMenu();

        // Validate user input for the choice
        while (!(cin >> choice) || choice < 1 || choice > 7) {
            cout << "Invalid input. Please choose a number between 1 and 7: ";
            clearInput();
        }

        // Exit the program if the choice is 7
        if (choice == 7) {
            cout << "Exiting the program. Goodbye!\n";
            break;
        }

        // Ask for the value to convert
        cout << "Enter the value to convert: ";
        while (!(cin >> value)) {
            cout << "Invalid input. Please enter a numeric value: ";
            clearInput();
        }

        // Perform the conversion based on the chosen option
        switch (choice) {
            case 1:
                cout << value << " Celsius is " << fixed << setprecision(2)
                     << convert(value, CELSIUS_TO_FAHRENHEIT_FACTOR, CELSIUS_TO_FAHRENHEIT_OFFSET)
                     << " Fahrenheit.\n";
                break;
            case 2:
                cout << value << " Fahrenheit is " << fixed << setprecision(2)
                     << convertInverse(value, CELSIUS_TO_FAHRENHEIT_FACTOR, CELSIUS_TO_FAHRENHEIT_OFFSET)
                     << " Celsius.\n";
                break;
            case 3:
                cout << value << " kilometers is " << fixed << setprecision(2)
                     << convert(value, KILOMETERS_TO_MILES_FACTOR)
                     << " miles.\n";
                break;
            case 4:
                cout << value << " miles is " << fixed << setprecision(2)
                     << convertInverse(value, KILOMETERS_TO_MILES_FACTOR)
                     << " kilometers.\n";
                break;
            case 5:
                cout << value << " kilograms is " << fixed << setprecision(2)
                     << convert(value, KILOGRAMS_TO_POUNDS_FACTOR)
                     << " pounds.\n";
                break;
            case 6:
                cout << value << " pounds is " << fixed << setprecision(2)
                     << convertInverse(value, KILOGRAMS_TO_POUNDS_FACTOR)
                     << " kilograms.\n";
                break;
        }

        // Clear the screen after displaying the result
        clearScreen();
    }

    return 0;
}
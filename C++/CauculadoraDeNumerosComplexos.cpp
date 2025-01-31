#include <iostream>
#include <cmath>
#include <limits> // For clearing the input buffer

using namespace std;

// Class to represent complex numbers
class Complex {
private:
    double real; // Real part
    double imag; // Imaginary part

public:
    // Constructor
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    // Getters
    double getReal() const { return real; }
    double getImag() const { return imag; }

    // Setters
    void setReal(double r) { real = r; }
    void setImag(double i) { imag = i; }

    // Method to display the complex number in rectangular form
    void displayRectangular() const {
        cout << real << " + " << imag << "i" << endl;
    }

    // Method to display the complex number in polar form
    void displayPolar() const {
        double magnitude = sqrt(real * real + imag * imag);
        double angle = atan2(imag, real) * 180 / M_PI; // Convert radians to degrees
        cout << "Magnitude: " << magnitude << ", Angle: " << angle << "°" << endl;
    }

    // Operator overloading for complex number operations
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
    }

    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;
        if (denominator == 0) {
            throw invalid_argument("Division by zero is not allowed.");
        }
        return Complex((real * other.real + imag * other.imag) / denominator,
                       (imag * other.real - real * other.imag) / denominator);
    }
};

// Function to clear the input buffer
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Function to display the menu
void displayMenu() {
    cout << "\n=== Complex Number Calculator ===\n";
    cout << "1. Addition\n";
    cout << "2. Subtraction\n";
    cout << "3. Multiplication\n";
    cout << "4. Division\n";
    cout << "5. Exit\n";
    cout << "Choose an option: ";
}

// Function to read a complex number from the user
Complex readComplex(const string& prompt) {
    double real, imag;
    char plus, i;
    cout << prompt << " (in the format a + bi): ";
    while (!(cin >> real >> plus >> imag >> i) || plus != '+' || i != 'i') {
        cout << "Invalid format. Please enter in the format a + bi: ";
        clearInput();
    }
    return Complex(real, imag);
}

// Function to clear the screen
void clearScreen() {
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Unix/Linux/macOS
#endif
}

int main() {
    try {
        int choice;
        while (true) {
            displayMenu();

            // Validate user input
            while (!(cin >> choice) || choice < 1 || choice > 5) {
                cout << "Invalid input. Please choose an option from 1 to 5: ";
                clearInput();
            }

            if (choice == 5) {
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            }

            // Read two complex numbers
            Complex num1 = readComplex("Enter the first complex number");
            Complex num2 = readComplex("Enter the second complex number");

            Complex result;

            // Perform the chosen operation
            switch (choice) {
                case 1:
                    result = num1 + num2;
                    cout << "Addition result: ";
                    break;
                case 2:
                    result = num1 - num2;
                    cout << "Subtraction result: ";
                    break;
                case 3:
                    result = num1 * num2;
                    cout << "Multiplication result: ";
                    break;
                case 4:
                    try {
                        result = num1 / num2;
                        cout << "Division result: ";
                    } catch (const invalid_argument& e) {
                        cerr << "Error: " << e.what() << endl;
                        continue;
                    }
                    break;
                default:
                    cout << "Invalid option." << endl;
                    continue;
            }

            // Display the result in rectangular and polar forms
            cout << "\nRectangular Form: ";
            result.displayRectangular();
            cout << "Polar Form: ";
            result.displayPolar();

            // Pause and clear the screen
            cout << "\nPress Enter to continue...";
            clearInput(); // Wait for the user to press Enter
            clearScreen(); // Clear the screen
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
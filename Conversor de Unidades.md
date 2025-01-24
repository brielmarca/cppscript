	#include <iostream>
	#include <iomanip>
	#include <limits>
	
	void clearInput() {
	    std::cin.clear();
	    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	
	double convert(double value, double factor, double offset = 0) {
	    return value * factor + offset;
	}
	
	void displayMenu() {
	    std::cout << "\nUnit Converter\n";
	    std::cout << "1. Celsius to Fahrenheit\n";
	    std::cout << "2. Kilometers to Miles\n";
	    std::cout << "3. Kilograms to Pounds\n";
	    std::cout << "4. Exit\n";
	    std::cout << "Choose an option: ";
	}
	
	int main() {
	    int choice;
	    do {
	        displayMenu();
	        while (!(std::cin >> choice) || choice < 1 || choice > 4) {
	            std::cout << "Invalid input. Please enter a number between 1 and 4: ";
	            clearInput();
        }

        if (choice == 4) {
            std::cout << "Exiting the program. Goodbye!\n";
            break;
        }

        double value;
        std::cout << "Enter the value to convert: ";
        while (!(std::cin >> value)) {
            std::cout << "Invalid input. Please enter a numeric value: ";
            clearInput();
        }

        double result;
        switch (choice) {
            case 1:
                result = convert(value, 9.0 / 5.0, 32);
                std::cout << value << " Celsius is " << std::fixed << std::setprecision(2) << result << " Fahrenheit.\n";
                break;
            case 2:
                result = convert(value, 0.621371);
                std::cout << value << " kilometers is " << std::fixed << std::setprecision(2) << result << " miles.\n";
                break;
            case 3:
                result = convert(value, 2.20462);
                std::cout << value << " kilograms is " << std::fixed << std::setprecision(2) << result << " pounds.\n";
                break;
        }
 

    return 0;
}

#include <iostream>
#include <vector>
#include <fstream>
#include <vector>
#include <limits> // For clearing the input buffer

using namespace std;

// Class to represent a product
class Product {
private:
    int id;
    string name;
    int quantity;
    double price;

public:
    // Constructor
    Product(int id = 0, string name = "", int quantity = 0, double price = 0.0)
        : id(id), name(name), quantity(quantity), price(price) {}

    // Getters
    int getId() const { return id; }
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }

    // Setters
    void setQuantity(int q) { quantity = q; }
    void setPrice(double p) { price = p; }

    // Display product details
    void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Quantity: " << quantity << ", Price: $" << price << endl;
    }
};

// Function to clear the input buffer
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Function to display the menu
void displayMenu() {
    cout << "\n=== Inventory Management System ===\n";
    cout << "1. Add Product\n";
    cout << "2. Remove Product\n";
    cout << "3. List Products\n";
    cout << "4. Search Product by ID\n";
    cout << "5. Search Product by Name\n";
    cout << "6. Generate Low Stock Report\n";
    cout << "7. Save Inventory to File\n";
    cout << "8. Load Inventory from File\n";
    cout << "9. Exit\n";
    cout << "Choose an option: ";
}

// Function to check if an ID already exists
bool isIdExists(const vector<Product>& inventory, int id) {
    for (const auto& product : inventory) {
        if (product.getId() == id) {
            return true;
        }
    }
    return false;
}

// Function to add a product to the inventory
void addProduct(vector<Product>& inventory) {
    int id, quantity;
    string name;
    double price;

    cout << "Enter product ID: ";
    while (!(cin >> id) || isIdExists(inventory, id)) {
        if (isIdExists(inventory, id)) {
            cout << "Product ID already exists. Please enter a unique ID: ";
        } else {
            cout << "Invalid input. Please enter a number: ";
        }
        clearInput();
    }

    cout << "Enter product name: ";
    clearInput();
    getline(cin, name);

    cout << "Enter product quantity: ";
    while (!(cin >> quantity)) {
        cout << "Invalid input. Please enter a number: ";
        clearInput();
    }

    cout << "Enter product price: ";
    while (!(cin >> price)) {
        cout << "Invalid input. Please enter a number: ";
        clearInput();
    }

    inventory.push_back(Product(id, name, quantity, price));
    cout << "Product added successfully!\n";
}

// Function to remove a product from the inventory
void removeProduct(vector<Product>& inventory) {
    int id;
    cout << "Enter product ID to remove: ";
    while (!(cin >> id)) {
        cout << "Invalid input. Please enter a number: ";
        clearInput();
    }

    auto it = inventory.begin();
    while (it != inventory.end()) {
        if (it->getId() == id) {
            it = inventory.erase(it);
            cout << "Product removed successfully!\n";
            return;
        } else {
            ++it;
        }
    }

    cout << "Product not found.\n";
}

// Function to list all products in the inventory
void listProducts(const vector<Product>& inventory) {
    if (inventory.empty()) {
        cout << "Inventory is empty.\n";
        return;
    }

    for (const auto& product : inventory) {
        product.display();
    }
}

// Function to search for a product by ID
void searchById(const vector<Product>& inventory) {
    int id;
    cout << "Enter product ID to search: ";
    while (!(cin >> id)) {
        cout << "Invalid input. Please enter a number: ";
        clearInput();
    }

    for (const auto& product : inventory) {
        if (product.getId() == id) {
            product.display();
            return;
        }
    }

    cout << "Product not found.\n";
}

// Function to search for a product by name
void searchByName(const vector<Product>& inventory) {
    string name;
    cout << "Enter product name to search: ";
    clearInput();
    getline(cin, name);

    bool found = false;
    for (const auto& product : inventory) {
        if (product.getName() == name) {
            product.display();
            found = true;
        }
    }

    if (!found) {
        cout << "Product not found.\n";
    }
}

// Function to generate a low stock report
void generateLowStockReport(const vector<Product>& inventory) {
    int threshold;
    cout << "Enter low stock threshold: ";
    while (!(cin >> threshold)) {
        cout << "Invalid input. Please enter a number: ";
        clearInput();
    }

    bool found = false;
    for (const auto& product : inventory) {
        if (product.getQuantity() < threshold) {
            product.display();
            found = true;
        }
    }

    if (!found) {
        cout << "No products with low stock.\n";
    }
}

// Function to save inventory to a file
void saveInventory(const vector<Product>& inventory, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& product : inventory) {
            file << product.getId() << "," << product.getName() << "," << product.getQuantity() << "," << product.getPrice() << "\n";
        }
        file.close();
        cout << "Inventory saved to " << filename << " successfully!\n";
    } else {
        cerr << "Error opening file for saving.\n";
    }
}

// Function to load inventory from a file
void loadInventory(vector<Product>& inventory, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        inventory.clear();
        string line;
        while (getline(file, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);

            if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
                int id = stoi(line.substr(0, pos1));
                string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
                int quantity = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
                double price = stod(line.substr(pos3 + 1));

                inventory.push_back(Product(id, name, quantity, price));
            }
        }
        file.close();
        cout << "Inventory loaded from " << filename << " successfully!\n";
    } else {
        cerr << "Error opening file for loading.\n";
    }
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
    vector<Product> inventory;
    string filename = "inventory.txt";

    try {
        int choice;
        while (true) {
            displayMenu();

            // Validate user input
            while (!(cin >> choice) || choice < 1 || choice > 9) {
                cout << "Invalid input. Please choose an option from 1 to 9: ";
                clearInput();
            }

            switch (choice) {
                case 1:
                    addProduct(inventory);
                    break;
                case 2:
                    removeProduct(inventory);
                    break;
                case 3:
                    listProducts(inventory);
                    break;
                case 4:
                    searchById(inventory);
                    break;
                case 5:
                    searchByName(inventory);
                    break;
                case 6:
                    generateLowStockReport(inventory);
                    break;
                case 7:
                    saveInventory(inventory, filename);
                    break;
                case 8:
                    loadInventory(inventory, filename);
                    break;
                case 9:
                    cout << "Exiting the program. Goodbye!\n";
                    return 0;
                default:
                    cout << "Invalid option.\n";
            }

            // Pause and clear the screen
            cout << "\nPress Enter to continue...";
            clearInput();
            cin.get(); // Wait for the user to press Enter
            clearScreen();
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
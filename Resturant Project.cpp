#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Structure to hold menu item information
struct MenuItem {
    string name;
    int price;
};

// Function to display the menu
void displayMenu(vector<MenuItem>& menu) {
    cout << "Menu:\n";
    for (int i = 0; i < menu.size(); i++) {
        cout << i + 1 << ". " << menu[i].name << " - Rs." << menu[i].price << endl;
    }
}

// Function to load menu items from file
void loadMenu(vector<MenuItem>& menu) {
    ifstream file("menu.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name;
        int price;
        ss >> ws; // Skip whitespace
        getline(ss, name, ',');  // Extract name until comma
        ss >> price;  // Extract price
        menu.push_back({name, price});
    }
    file.close();
}

// Function to save menu items to file
void saveMenu(vector<MenuItem>& menu) {
    ofstream file("menu.txt");
    for (auto& item : menu) {
        file << item.name << "," << item.price << endl;
    }
    file.close();
}

// Function for admin to manage the menu
void adminPanel(vector<MenuItem>& menu) {
    int choice;
    do {
        cout << "\nAdmin Panel:\n";
        cout << "1. Add New Item\n";
        cout << "2. Remove Item\n";
        cout << "3. Update Item Price\n";
        cout << "4. Show Menu\n";
        cout << "5. Exit Admin Panel\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            int price;
            cout << "Enter food name: ";
            cin >> ws; // to clear any leading whitespace
            getline(cin, name);
            cout << "Enter price: ";
            cin >> price;
            menu.push_back({name, price});
            saveMenu(menu);
            cout << "Item added successfully.\n";
        } else if (choice == 2) {
            int itemIndex;
            displayMenu(menu);
            cout << "Enter the item number to remove: ";
            cin >> itemIndex;
            if (itemIndex >= 1 && itemIndex <= menu.size()) {
                menu.erase(menu.begin() + itemIndex - 1);
                saveMenu(menu);
                cout << "Item removed successfully.\n";
            } else {
                cout << "Invalid item number.\n";
            }
        } else if (choice == 3) {
            int itemIndex;
            displayMenu(menu);
            cout << "Enter the item number to update: ";
            cin >> itemIndex;
            if (itemIndex >= 1 && itemIndex <= menu.size()) {
                int newPrice;
                cout << "Enter the new price: ";
                cin >> newPrice;
                menu[itemIndex - 1].price = newPrice;
                saveMenu(menu);
                cout << "Price updated successfully.\n";
            } else {
                cout << "Invalid item number.\n";
            }
        } else if (choice == 4) {
            displayMenu(menu);
        } else if (choice == 5) {
            cout << "Exiting Admin Panel.\n";
        } else {
            cout << "Invalid choice.\n";
        }
    } while (choice != 5);
}

// Function to handle customer order
void customerOrder(vector<MenuItem>& menu, string name) {
    int choice, quantity, total = 0;
    char con = 'N';
    do {
        displayMenu(menu);
        cout << "Enter your choice (1-" << menu.size() << "): ";
        cin >> choice;

        if (choice >= 1 && choice <= menu.size()) {
            cout << "Enter the quantity: ";
            cin >> quantity;
            int itemPrice = menu[choice - 1].price * quantity;
            total += itemPrice;
            cout << menu[choice - 1].name << " (Quantity: " << quantity << ") added to your bill. Subtotal: Rs." << itemPrice << endl;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }

        cout << "Do you want to order anything else? (Y/N): ";
        cin >> con;
    } while (con == 'Y' || con == 'y');
    
    cout << "Total Bill: Rs." << total << endl;
    cout << "Thanks " << name << " for dining with us!" << endl;
}

// Function to handle customer login
void customerLogin(vector<MenuItem>& menu) {
    string name;
    cout << "Enter Your Name: ";
    cin >> name;
    customerOrder(menu, name);
}

// Function for Main Menu (Choose between Customer and Admin)
void mainMenu(vector<MenuItem>& menu) {
    int userType;
    do {
        cout << "\nWelcome to Our Restaurant!" << endl;
        cout << "1. Customer\n";
        cout << "2. Admin\n";
        cout << "3. Exit\n";
        cout << "Enter your role (1 or 2): ";
        cin >> userType;

        if (userType == 1) {
            customerLogin(menu);
        } else if (userType == 2) {
            adminPanel(menu);
        } else if (userType == 3) {
            cout << "Exiting the system. Thank you!" << endl;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    } while (userType != 3); // Continue running the menu until user exits
}

// Main function
int main() {
    vector<MenuItem> menu;

    // Load menu from file or initialize with default items
    loadMenu(menu);

    if (menu.empty()) {  // If the menu is empty, load default items
        menu.push_back({"Pizza", 950});
        menu.push_back({"Zinger Burger", 250});
        menu.push_back({"Chicken Burger", 220});
        menu.push_back({"Club Sandwich", 180});
        menu.push_back({"Chicken Sandwich", 160});
        menu.push_back({"Chicken Roll", 70});
        menu.push_back({"Roll Paratha", 180});
        menu.push_back({"Fries", 100});
        menu.push_back({"Mango Juice", 150});
        menu.push_back({"Orange Juice", 150});
        saveMenu(menu);  // Save default items to the file
    }

    // Show the main menu
    mainMenu(menu);

    return 0;
}


#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

struct Product {
    char name[50];
    double price;
    int stock;
    char category[20];
};

Product* inventory = nullptr;
int productCount = 0;

void loadFromFile(const char* filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Error: Unable to open the inventory file!\n";
        return;
    }
    productCount = 0;
    string line;
    while (getline(file, line)) {
        productCount++;
    }
    file.clear();
    file.seekg(0, ios::beg);

    delete[] inventory;
    inventory = new Product[productCount];

    int index = 0;
    while (getline(file, line) && index < productCount) {
        istringstream iss(line);
        string temp;
        getline(iss, temp, ':'); iss.getline(inventory[index].name, 50, ',');
        getline(iss, temp, ':'); iss >> inventory[index].price; iss.ignore();
        getline(iss, temp, ':'); iss >> inventory[index].stock; iss.ignore();
        getline(iss, temp, ':'); iss.getline(inventory[index].category, 20);
        index++;
    }
    file.close();
}

void showInventory() {
    if (productCount == 0) {
        cout << "Inventory is empty!\n";
        return;
    }
    cout << "\nCurrent Inventory:\n";
    for (int i = 0; i < productCount; i++) {
        cout << "Product: " << inventory[i].name << " | Price: " << inventory[i].price
             << " | Stock: " << inventory[i].stock << " | Category: " << inventory[i].category << "\n";
    }
}

void addProduct() {
    Product* newInventory = new Product[productCount + 1];
    for (int i = 0; i < productCount; i++) {
        newInventory[i] = inventory[i];
    }
    cout << "Enter product name: "; cin.ignore(); cin.getline(newInventory[productCount].name, 50);
    cout << "Enter price: "; cin >> newInventory[productCount].price;
    cout << "Enter stock quantity: "; cin >> newInventory[productCount].stock;
    cout << "Enter category: "; cin.ignore(); cin.getline(newInventory[productCount].category, 20);

    delete[] inventory;
    inventory = newInventory;
    productCount++;
    cout << "Product added successfully!\n";
}

void modifyProduct() {
    char name[50];
    cout << "Enter product name to modify: "; cin.ignore(); cin.getline(name, 50);
    for (int i = 0; i < productCount; i++) {
        if (strcmp(inventory[i].name, name) == 0) {
            cout << "Enter new price: "; cin >> inventory[i].price;
            cout << "Enter new stock quantity: "; cin >> inventory[i].stock;
            cout << "Product details updated!\n";
            return;
        }
    }
    cout << "Product not found!\n";
}

void removeProduct() {
    char name[50];
    cout << "Enter product name to remove: "; cin.ignore(); cin.getline(name, 50);
    for (int i = 0; i < productCount; i++) {
        if (strcmp(inventory[i].name, name) == 0) {
            for (int j = i; j < productCount - 1; j++) {
                inventory[j] = inventory[j + 1];
            }
            productCount--;
            cout << "Product removed from inventory!\n";
            return;
        }
    }
    cout << "Product not found!\n";
}
void saveToFile(const char* filename) {

    ofstream file(filename);
    if (!file) {
        cout << "Error: Unable to save the inventory!\n";
        return;
    }
    for (int i = 0; i < productCount; i++) {
        file << "Name: " << inventory[i].name << ", Price: " << inventory[i].price
             << ", Stock: " << inventory[i].stock << ", Category: " << inventory[i].category << "\n";
    }
    file.close();
    cout << "Inventory saved successfully!\n";
}

int main() {
    const char* filename = "inventory.txt";
    loadFromFile(filename);
    int option;
    do {
        cout << "\nInventory Management System\n";
        cout << "1. View Inventory\n";
        cout << "2. Add Product\n";
        cout << "3. Modify Product\n";
        cout << "4. Remove Product\n";
        cout << "5. Save and Exit\n";
        cout << "Select an option: ";
        cin >> option;
        switch (option) {
            case 1: showInventory(); break;
            case 2: addProduct(); break;
            case 3: modifyProduct(); break;
            case 4: removeProduct(); break;
            case 5: saveToFile(filename); break;
            default: cout << "Invalid option! Try again.\n";
        }
    } while (option != 5);

    delete[] inventory;
    return 0;
}

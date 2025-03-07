#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring> // strcmp function ke liye

using namespace std;

// Structure jo inventory item ka format define karta hai
struct Item {
    char name[50];
    double price; 
    int quantity; 
    char category[20]; 
};

Item* inventory = nullptr; // Dynamically allocated inventory array ka pointer bnaya ha yha
int inventorySize = 0; // Inventory me items ki tadaad

// Function jo inventory file se load karega
void loadInventory(const char* filename) {
    ifstream file(filename); // File ko read mode me open karna
    if (!file) {
        cout << "Error opening file!\n";
        return;
    }
    inventorySize = 0;
    string line;
    while (getline(file, line)) {
        inventorySize++; // Items ki tadaad count karna
    }
    file.clear(); // EOF flag ko clear karna
    file.seekg(0, ios::beg); // File pointer ko shuru me wapas lana

    delete[] inventory; // Pehle se allocated memory free karna
    inventory = new Item[inventorySize]; // Nai memory allocate karna

    int index = 0;
    while (getline(file, line) && index < inventorySize) {
        istringstream iss(line);
        string temp;
        getline(iss, temp, ':'); iss.getline(inventory[index].name, 50, ',');
        getline(iss, temp, ':'); iss >> inventory[index].price; iss.ignore();
        getline(iss, temp, ':'); iss >> inventory[index].quantity; iss.ignore();
        getline(iss, temp, ':'); iss.getline(inventory[index].category, 20);
        index++;
    }
    file.close(); // File ko close karna
}

// Function jo inventory display karega
void displayInventory() {
    if (inventorySize == 0) {
        cout << "Inventory is empty!\n";
        return;
    }
    for (int i = 0; i < inventorySize; i++) {
        cout << "Name: " << inventory[i].name << ", Price: " << inventory[i].price
             << ", Quantity: " << inventory[i].quantity << ", Category: " << inventory[i].category << "\n";
    }
}

// Function jo naya item add karega
void addItem() {
    Item* newInventory = new Item[inventorySize + 1]; // New memory allocate karna
    for (int i = 0; i < inventorySize; i++) {
        newInventory[i] = inventory[i]; // Pehle se mojood items ko copy karna
    }
    cout << "Enter item name: "; cin.ignore(); cin.getline(newInventory[inventorySize].name, 50);
    cout << "Enter price: "; cin >> newInventory[inventorySize].price;
    cout << "Enter quantity: "; cin >> newInventory[inventorySize].quantity;
    cout << "Enter category: "; cin.ignore(); cin.getline(newInventory[inventorySize].category, 20);

    delete[] inventory; // Purani memory free karna
    inventory = newInventory; // Nai memory point karna
    inventorySize++; // Inventory ka size barhana
    cout << "Item added successfully!\n";
}

// Function jo kisi item ko update karega
void updateItem() {
    char name[50];
    cout << "Enter the item name to update: "; cin.ignore(); cin.getline(name, 50);
    for (int i = 0; i < inventorySize; i++) {
        if (strcmp(inventory[i].name, name) == 0) { // Item ka naam check karna
            cout << "Enter new price: "; cin >> inventory[i].price;
            cout << "Enter new quantity: "; cin >> inventory[i].quantity;
            cout << "Item updated successfully!\n";
            return;
        }
    }
    cout << "Item not found!\n";
}

// Function jo kisi item ko delete karega
void deleteItem() {
    char name[50];
    cout << "Enter the item name to delete: "; cin.ignore(); cin.getline(name, 50);
    for (int i = 0; i < inventorySize; i++) {
        if (strcmp(inventory[i].name, name) == 0) {
            for (int j = i; j < inventorySize - 1; j++) {
                inventory[j] = inventory[j + 1]; // Items ko left shift karna
            }
            inventorySize--; // Inventory ka size kam karna
            cout << "Item deleted successfully!\n";
            return;
        }
    }
    cout << "Item not found!\n";
}

// Function jo inventory ko file me save karega
void saveInventory(const char* filename) {
    ofstream file(filename); // File ko write mode me open karna
    if (!file) {
        cout << "Error opening file!\n";
        return;
    }
    for (int i = 0; i < inventorySize; i++) {
        file << "Name: " << inventory[i].name << ", Price: " << inventory[i].price
             << ", Quantity: " << inventory[i].quantity << ", Category: " << inventory[i].category << "\n";
    }
    file.close(); // File ko close karna
    cout << "Inventory saved successfully!\n";
}

int main() {
    const char* filename = "inventory.txt"; // File ka naam
    loadInventory(filename); // Inventory file se load karna
    int choice;
    do {
        cout << "\n1. Display Inventory\n";
        cout << "2. Add New Item\n";
        cout << "3. Update Item\n";
        cout << "4. Delete Item\n";
        cout << "5. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: displayInventory(); break;
            case 2: addItem(); break;
            case 3: updateItem(); break;
            case 4: deleteItem(); break;
            case 5: saveInventory(filename); break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);
    
    delete[] inventory; // Allocated memory free karna
    return 0;
}
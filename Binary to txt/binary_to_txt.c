#include <stdio.h>
#include <stdlib.h>

// Structure jo binary file ke data ka format define karta hai
typedef struct {
    char name[50];
    double price;
    int quantity;
    char category[20];
} Item;

// Function to convert binary file to text
void convert_to_text(const char *binaryFile, const char *textFile) {
    FILE *bin = fopen(binaryFile, "rb");
    FILE *txt = fopen(textFile, "w");

    if (!bin || !txt) {
        printf("Error opening file!\n");
        return;
    }

    Item item;
    while (fread(&item, sizeof(Item), 1, bin)) {
        fprintf(txt, "Name: %s, Price: %.2f, Quantity: %d, Category: %s\n",
                item.name, item.price, item.quantity, item.category);
    }

    fclose(bin);
    fclose(txt);
    printf("Binary file successfully converted to text file!\n");
}

// Function to find the item with the highest price
void find_highest_price(const char *binaryFile) {
    FILE *bin = fopen(binaryFile, "rb");
    if (!bin) {
        printf("Error opening file!\n");
        return;
    }

    Item item, highest;
    highest.price = 0.0;

    while (fread(&item, sizeof(Item), 1, bin)) {
        if (item.price > highest.price) {
            highest = item;
        }
    }

    fclose(bin);
    printf("Item with highest price : %s , Price : %.2f\n", highest.name, highest.price);
}

// Function to find the item with the highest quantity
void find_highest_quantity(const char *binaryFile) {
    FILE *bin = fopen(binaryFile, "rb");
    if (!bin) {
        printf("Error opening file!\n");
        return;
    }

    Item item, highest;
    highest.quantity = 0;

    while (fread(&item, sizeof(Item), 1, bin)) {
        if (item.quantity > highest.quantity) {
            highest = item;
        }
    }

    fclose(bin);
    printf("Item with highest quantity : %s , Quantity : %d\n", highest.name, highest.quantity);
}

int main() {
    const char *binaryFile = "inventory.bin";
    const char *textFile = "inventory.txt";

    convert_to_text(binaryFile, textFile);
    find_highest_price(binaryFile);
    find_highest_quantity(binaryFile);

    return 0;
}

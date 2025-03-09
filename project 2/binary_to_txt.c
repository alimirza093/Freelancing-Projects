#include <stdio.h>
#include <stdlib.h>

// Structure defining the format of each record in the binary file
struct Product {
    char name[50];
    double price;
    int quantity;
    char category[20];
};

// Function to convert a binary file to a text file
void convertBinaryToText(const char *binaryFile, const char *textFile) {
    FILE *bin = fopen(binaryFile, "rb");
    FILE *txt = fopen(textFile, "w");

    if (!bin || !txt) {
        printf("Error: Unable to open the file!\n");
        return;
    }

    struct Product item;
    while (fread(&item, sizeof(struct Product), 1, bin)) {
        fprintf(txt, "Name: %s | Price: %.2f | Quantity: %d | Category: %s\n", 
                item.name, item.price, item.quantity, item.category);
    }

    fclose(bin);
    fclose(txt);
    printf("Binary file successfully converted to text file!\n");
}

// Function to find the most expensive product
void findMostExpensiveProduct(const char *binaryFile) {
    FILE *bin = fopen(binaryFile, "rb");
    if (!bin) {
        printf("Error: Cannot access the file!\n");
        return;
    }

    struct Product item, highest;
    highest.price = 0.0;

    while (fread(&item, sizeof(struct Product), 1, bin)) {
        if (item.price > highest.price) {
            highest = item;
        }
    }

    fclose(bin);
    printf("Most Expensive Item: %s | Price: %.2f\n", highest.name, highest.price);
}

// Function to find the product with the highest quantity
void findProductWithMaxStock(const char *binaryFile) {
    FILE *bin = fopen(binaryFile, "rb");
    if (!bin) {
        printf("Error: Unable to read the file!\n");
        return;
    }

    struct Product item, maxStock;
    maxStock.quantity = 0;

    while (fread(&item, sizeof(struct Product), 1, bin)) {
        if (item.quantity > maxStock.quantity) {
            maxStock = item;
        }
    }

    fclose(bin);
    printf("Item with Maximum Quantity: %s | Quantity: %d\n", maxStock.name, maxStock.quantity);
}

int main() {
    const char *binaryFile = "inventory.bin";
    const char *textFile = "inventory.txt";

    convertBinaryToText(binaryFile, textFile);
    findMostExpensiveProduct(binaryFile);
    findProductWithMaxStock(binaryFile);

    return 0;
}

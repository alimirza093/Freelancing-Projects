#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Item structure define kia ha
typedef struct {
    char name[50];
    float price;
    int quantity;
} Item;

int main() {
    // Binary file create ki ha yha me na
    FILE *bin = fopen("inventory.bin", "wb");
    // File open nahi ho raha to error message show kary ga
    if (!bin) {
        printf("Error opening file!\n");
        return 1;
    }

    // Sample inventory data
    // ye 4 items ka data ha
    Item items[] = {
        {"Apple", 2.50, 10},
        {"Banana", 1.20, 20},
        {"Mango", 3.75, 5},
        {"Orange", 2.00, 15}
    };

    // Binary file me data write kia ha yha
    fwrite(items, sizeof(Item), 4, bin);
    // File close ki ha yha
    fclose(bin);
    printf("Binary file 'inventory.bin' created successfully!\n");

    // Ab file ko read karna start kar rahy hain
    bin = fopen("inventory.bin", "rb");
    if (!bin) {
        printf("Error opening file!\n");
        return 1;
    }
    // File ko read kar k data display krwa rhy ha yha pr
    printf("\nInventory Data:\n");
    Item item;
    while (fread(&item, sizeof(Item), 1, bin)) {
        printf("Name: %s, Price: %.2f, Quantity: %d\n", item.name, item.price, item.quantity);
    }
    fclose(bin);

    // Ab highest price aur highest quantity wale items find kar rahy hain
    bin = fopen("inventory.bin", "rb");
    if (!bin) {
        printf("Error opening file!\n");
        return 1;
    }

    // Highest price item find karna
    Item highestPriceItem;
    highestPriceItem.price = 0.0;
    rewind(bin);
    while (fread(&item, sizeof(Item), 1, bin)) {
        if (item.price > highestPriceItem.price) {
            highestPriceItem = item;
        }
    }
    printf("\nHighest Price Item: %s (%.2f)\n", highestPriceItem.name, highestPriceItem.price);

    // Highest quantity item find karna
    Item highestQuantityItem;
    highestQuantityItem.quantity = 0;
    rewind(bin);
    while (fread(&item, sizeof(Item), 1, bin)) {
        if (item.quantity > highestQuantityItem.quantity) {
            highestQuantityItem = item;
        }
    }
    printf("Highest Quantity Item: %s (%d)\n", highestQuantityItem.name, highestQuantityItem.quantity);

    fclose(bin);
    return 0;
}


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITEMS 100

typedef struct {
    int id;
    char name[50];
    int quantity;
    float price;
} Item;

Item inventory[MAX_ITEMS];
int itemCount = 0;

// Function prototypes
void menu();
void addItem();
void viewItems();
void updateItem();
void deleteItem();
void searchItem();
void sortItems();
void saveInventory();
void loadInventory();
void calculateTotalValue();

// Main function
int main() {
    loadInventory(); // Load inventory from file on startup

    int choice;
    while (1) {
        menu();
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addItem(); break;
            case 2: viewItems(); break;
            case 3: updateItem(); break;
            case 4: deleteItem(); break;
            case 5: searchItem(); break;
            case 6: sortItems(); break;
            case 7: calculateTotalValue(); break;
            case 8: saveInventory(); printf("Inventory saved. Exiting...\n"); exit(0);
            default: printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
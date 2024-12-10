
    Item newItem;
    newItem.id = itemCount + 1; // Auto-generate ID

    printf("\nEnter item name: ");
    scanf(" %[^\n]", newItem.name);
    printf("Enter quantity: ");
    scanf("%d", &newItem.quantity);
    printf("Enter price: ");
    scanf("%f", &newItem.price);

    inventory[itemCount++] = newItem;
    printf("Item added successfully!\n");
}

// View all items
void viewItems() {
    if (itemCount == 0) {
        printf("\nNo items in inventory.\n");
        return;
    }

    printf("\n====== Inventory Items ======\n");
    printf("ID\tName\t\tQuantity\tPrice\n");
    printf("-----------------------------------------\n");

    for (int i = 0; i < itemCount; i++) {
        printf("%d\t%-15s\t%d\t\t%.2f\n",
               inventory[i].id, inventory[i].name,
               inventory[i].quantity, inventory[i].price);
    }
}

// Update an item
void updateItem() {
    int id, newQuantity;
    float newPrice;

    if (itemCount == 0) {
        printf("\nNo items in inventory to update.\n");
        return;
    }

    printf("\nEnter the ID of the item to update: ");
    scanf("%d", &id);

    if (id < 1 || id > itemCount) {
        printf("Invalid item ID!\n");
        return;
    }

    printf("Enter new quantity: ");
    scanf("%d", &newQuantity);
    printf("Enter new price: ");
    scanf("%f", &newPrice);

    inventory[id - 1].quantity = newQuantity;
    inventory[id - 1].price = newPrice;

    printf("Item updated successfully!\n");
}

// Delete an item
void deleteItem() {
    int id;

    if (itemCount == 0) {
        printf("\nNo items in inventory to delete.\n");
        return;
    }

    printf("\nEnter the ID of the item to delete: ");
    scanf("%d", &id);

    if (id < 1 || id > itemCount) {
        printf("Invalid item ID!\n");
        return;
    }

    for (int i = id - 1; i < itemCount - 1; i++) {
        inventory[i] = inventory[i + 1];
    }

    itemCount--;
    printf("Item deleted successfully!\n");

    // Reassign IDs to maintain consistency
    for (int i = 0; i < itemCount; i++) {
        inventory[i].id = i + 1;
    }
}

// Search for an item by name
void searchItem() {
    char searchName[50];
    printf("\nEnter the name of the item to search: ");
    scanf(" %[^\n]", searchName);

    printf("\nResults:\n");
    printf("ID\tName\t\tQuantity\tPrice\n");
    printf("-----------------------------------------\n");

    int found = 0;
    for (int i = 0; i < itemCount; i++) {
        if (strstr(inventory[i].name, searchName)) {
            printf("%d\t%-15s\t%d\t\t%.2f\n",
                   inventory[i].id, inventory[i].name,
                   inventory[i].quantity, inventory[i].price);
            found = 1;
        }
    }

    if (!found) {
        printf("No items found with the name '%s'.\n", searchName);
    }
}

// Sort items
void sortItems() {
    int choice;
    printf("\nSort by:\n1. Name\n2. Quantity\n3. Price\nEnter choice: ");
    scanf("%d", &choice);

    for (int i = 0; i < itemCount - 1; i++) {
        for (int j = 0; j < itemCount - i - 1; j++) {
            int swap = 0;

            if (choice == 1 && strcmp(inventory[j].name, inventory[j + 1].name) > 0) {
                swap = 1;
            } else if (choice == 2 && inventory[j].quantity > inventory[j + 1].quantity) {
                swap = 1;
            } else if (choice == 3 && inventory[j].price > inventory[j + 1].price) {
                swap = 1;
            }

            if (swap) {
                Item temp = inventory[j];
                inventory[j] = inventory[j + 1];
                inventory[j + 1] = temp;
            }
        }
    }

    printf("Items sorted successfully!\n");
}

// Save inventory to file
void saveInventory() {
    FILE *file = fopen("inventory.txt", "w");
    if (!file) {
        printf("Error saving inventory!\n");
        return;
    }

    for (int i = 0; i < itemCount; i++) {
        fprintf(file, "%d,%s,%d,%.2f\n", inventory[i].id, inventory[i].name,
                inventory[i].quantity, inventory[i].price);
    }

    fclose(file);
    printf("Inventory saved to file.\n");
}

// Load inventory from file
void loadInventory() {
    FILE *file = fopen("inventory.txt", "r");
    if (!file) {
        printf("No inventory file found. Starting fresh.\n");
        return;
    }

    itemCount = 0;
    while (fscanf(file, "%d,%49[^,],%d,%f\n", &inventory[itemCount].id,
                  inventory[itemCount].name, &inventory[itemCount].quantity,
                  &inventory[itemCount].price) != EOF) {
        itemCount++;
    }

    fclose(file);
    printf("Inventory loaded from file.\n");
}

// Calculate total inventory value
void calculateTotalValue() {
    float totalValue = 0;

    for (int i = 0; i < itemCount; i++) {
        totalValue += inventory[i].quantity * inventory[i].price;
    }

    printf("\nTotal Inventory Value: $%.2f\n", totalValue);
}

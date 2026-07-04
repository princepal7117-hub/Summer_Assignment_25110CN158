/*Write a program to Create inventory
management system.*/

#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 100
#define LOW_STOCK_THRESHOLD 10

struct Item {
    int itemId;
    char name[50];
    char category[30];
    int quantity;
    float price;
    int isActive;
};

struct Transaction {
    int itemId;
    char type[10]; // "IN" or "OUT"
    int quantity;
    float amount;
};

struct Item items[MAX_ITEMS];
struct Transaction transactions[500];
int itemCount = 0;
int transactionCount = 0;
int nextItemId = 1;

// ---------- Lookup helpers ----------

int findItemIndex(int itemId) {
    for (int i = 0; i < itemCount; i++) {
        if (items[i].isActive && items[i].itemId == itemId) {
            return i;
        }
    }
    return -1;
}

void logTransaction(int itemId, const char *type, int quantity, float amount) {
    if (transactionCount >= 500) return; // simple cap for this demo

    struct Transaction t;
    t.itemId = itemId;
    strcpy(t.type, type);
    t.quantity = quantity;
    t.amount = amount;
    transactions[transactionCount++] = t;
}

// ---------- Core operations ----------

void addItem() {
    if (itemCount >= MAX_ITEMS) {
        printf("Inventory is full!\n");
        return;
    }

    struct Item it;
    it.itemId = nextItemId++;
    getchar();

    printf("Enter Item Name: ");
    fgets(it.name, 50, stdin);
    it.name[strcspn(it.name, "\n")] = '\0';

    printf("Enter Category: ");
    fgets(it.category, 30, stdin);
    it.category[strcspn(it.category, "\n")] = '\0';

    printf("Enter Initial Quantity: ");
    scanf("%d", &it.quantity);

    printf("Enter Unit Price: ");
    scanf("%f", &it.price);

    it.isActive = 1;
    items[itemCount++] = it;

    if (it.quantity > 0) {
        logTransaction(it.itemId, "IN", it.quantity, it.quantity * it.price);
    }

    printf("Item added successfully! Item ID: %d\n", it.itemId);
}

void displayAll() {
    int found = 0;
    printf("\n%-6s %-20s %-15s %-10s %-10s %-8s\n",
           "ID", "Name", "Category", "Quantity", "Price", "Status");
    printf("--------------------------------------------------------------------\n");

    for (int i = 0; i < itemCount; i++) {
        if (items[i].isActive) {
            printf("%-6d %-20s %-15s %-10d %-10.2f %-8s\n",
                   items[i].itemId, items[i].name, items[i].category,
                   items[i].quantity, items[i].price,
                   items[i].quantity <= LOW_STOCK_THRESHOLD ? "LOW" : "OK");
            found = 1;
        }
    }

    if (!found) {
        printf("No items in inventory.\n");
    }
}

void searchByName() {
    char keyword[50];
    getchar();
    printf("Enter name keyword to search: ");
    fgets(keyword, 50, stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    int found = 0;
    printf("\nSearch Results:\n");
    for (int i = 0; i < itemCount; i++) {
        if (items[i].isActive && strstr(items[i].name, keyword) != NULL) {
            printf("ID: %d | Name: %s | Category: %s | Qty: %d | Price: %.2f\n",
                   items[i].itemId, items[i].name, items[i].category,
                   items[i].quantity, items[i].price);
            found = 1;
        }
    }

    if (!found) {
        printf("No items matched your search.\n");
    }
}

void viewItem() {
    int itemId;
    printf("Enter Item ID: ");
    scanf("%d", &itemId);

    int index = findItemIndex(itemId);
    if (index == -1) {
        printf("Item ID %d not found.\n", itemId);
        return;
    }

    printf("\n--- Item Details ---\n");
    printf("ID       : %d\n", items[index].itemId);
    printf("Name     : %s\n", items[index].name);
    printf("Category : %s\n", items[index].category);
    printf("Quantity : %d\n", items[index].quantity);
    printf("Price    : %.2f\n", items[index].price);
    printf("Stock Value: %.2f\n", items[index].quantity * items[index].price);
    printf("Status   : %s\n", items[index].quantity <= LOW_STOCK_THRESHOLD ? "LOW STOCK" : "OK");
}

void stockIn() {
    int itemId, quantity;

    printf("Enter Item ID: ");
    scanf("%d", &itemId);

    int index = findItemIndex(itemId);
    if (index == -1) {
        printf("Item ID %d not found.\n", itemId);
        return;
    }

    printf("Enter quantity to add: ");
    scanf("%d", &quantity);

    if (quantity <= 0) {
        printf("Invalid quantity. Must be positive.\n");
        return;
    }

    items[index].quantity += quantity;
    logTransaction(itemId, "IN", quantity, quantity * items[index].price);

    printf("Stock updated. New quantity: %d\n", items[index].quantity);
}

void stockOut() {
    int itemId, quantity;

    printf("Enter Item ID: ");
    scanf("%d", &itemId);

    int index = findItemIndex(itemId);
    if (index == -1) {
        printf("Item ID %d not found.\n", itemId);
        return;
    }

    printf("Enter quantity to remove: ");
    scanf("%d", &quantity);

    if (quantity <= 0) {
        printf("Invalid quantity. Must be positive.\n");
        return;
    }

    if (quantity > items[index].quantity) {
        printf("Insufficient stock. Available: %d\n", items[index].quantity);
        return;
    }

    items[index].quantity -= quantity;
    logTransaction(itemId, "OUT", quantity, quantity * items[index].price);

    printf("Stock updated. New quantity: %d\n", items[index].quantity);

    if (items[index].quantity <= LOW_STOCK_THRESHOLD) {
        printf("WARNING: Stock is now LOW (threshold: %d)\n", LOW_STOCK_THRESHOLD);
    }
}

void updateItem() {
    int itemId;
    printf("Enter Item ID to update: ");
    scanf("%d", &itemId);

    int index = findItemIndex(itemId);
    if (index == -1) {
        printf("Item ID %d not found.\n", itemId);
        return;
    }

    getchar();

    printf("Enter new Name: ");
    fgets(items[index].name, 50, stdin);
    items[index].name[strcspn(items[index].name, "\n")] = '\0';

    printf("Enter new Category: ");
    fgets(items[index].category, 30, stdin);
    items[index].category[strcspn(items[index].category, "\n")] = '\0';

    printf("Enter new Price: ");
    scanf("%f", &items[index].price);

    printf("Item updated successfully! (Use Stock In/Out to change quantity)\n");
}

void deleteItem() {
    int itemId;
    printf("Enter Item ID to delete: ");
    scanf("%d", &itemId);

    int index = findItemIndex(itemId);
    if (index == -1) {
        printf("Item ID %d not found.\n", itemId);
        return;
    }

    items[index].isActive = 0;
    printf("Item deleted successfully!\n");
}

void lowStockReport() {
    int found = 0;
    printf("\n--- Low Stock Report (threshold: %d) ---\n", LOW_STOCK_THRESHOLD);
    printf("%-6s %-20s %-10s\n", "ID", "Name", "Quantity");
    printf("----------------------------------------\n");

    for (int i = 0; i < itemCount; i++) {
        if (items[i].isActive && items[i].quantity <= LOW_STOCK_THRESHOLD) {
            printf("%-6d %-20s %-10d\n", items[i].itemId, items[i].name, items[i].quantity);
            found = 1;
        }
    }

    if (!found) {
        printf("No items are low on stock.\n");
    }
}

void inventoryValueReport() {
    float totalValue = 0;
    int totalItems = 0;

    for (int i = 0; i < itemCount; i++) {
        if (items[i].isActive) {
            totalValue += items[i].quantity * items[i].price;
            totalItems++;
        }
    }

    printf("\n--- Inventory Value Report ---\n");
    printf("Total Distinct Items : %d\n", totalItems);
    printf("Total Inventory Value: %.2f\n", totalValue);
}

void transactionHistory() {
    int itemId;
    printf("Enter Item ID: ");
    scanf("%d", &itemId);

    if (findItemIndex(itemId) == -1) {
        printf("Item ID %d not found.\n", itemId);
        return;
    }

    int found = 0;
    printf("\n--- Transaction History for Item %d ---\n", itemId);
    printf("%-6s %-10s %-10s\n", "Type", "Quantity", "Amount");
    printf("--------------------------------\n");

    for (int i = 0; i < transactionCount; i++) {
        if (transactions[i].itemId == itemId) {
            printf("%-6s %-10d %-10.2f\n",
                   transactions[i].type, transactions[i].quantity, transactions[i].amount);
            found = 1;
        }
    }

    if (!found) {
        printf("No transactions found for this item.\n");
    }
}

int main() {
    int choice;

    do {
        printf("\n===== INVENTORY MANAGEMENT SYSTEM =====\n");
        printf("1.  Add Item\n");
        printf("2.  Display All Items\n");
        printf("3.  Search Item by Name\n");
        printf("4.  View Item Details\n");
        printf("5.  Stock In (Add Quantity)\n");
        printf("6.  Stock Out (Remove Quantity)\n");
        printf("7.  Update Item Info\n");
        printf("8.  Delete Item\n");
        printf("9.  Low Stock Report\n");
        printf("10. Inventory Value Report\n");
        printf("11. Transaction History\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:  addItem(); break;
            case 2:  displayAll(); break;
            case 3:  searchByName(); break;
            case 4:  viewItem(); break;
            case 5:  stockIn(); break;
            case 6:  stockOut(); break;
            case 7:  updateItem(); break;
            case 8:  deleteItem(); break;
            case 9:  lowStockReport(); break;
            case 10: inventoryValueReport(); break;
            case 11: transactionHistory(); break;
            case 12: printf("Exiting program. Goodbye!\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 12);

    return 0;
}
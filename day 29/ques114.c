/*Write a program to Create menu-driven array
operations system.*/

#include <stdio.h>

#define MAX_SIZE 100

int arr[MAX_SIZE];
int size = 0;

// ---------- Basic operations ----------

void inputArray() {
    printf("Enter number of elements (max %d): ", MAX_SIZE);
    scanf("%d", &size);

    if (size > MAX_SIZE) {
        size = MAX_SIZE;
        printf("Capped to maximum of %d elements.\n", MAX_SIZE);
    }

    printf("Enter %d elements:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Array stored successfully!\n");
}

void displayArray() {
    if (size == 0) {
        printf("Array is empty.\n");
        return;
    }

    printf("Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void insertElement() {
    if (size >= MAX_SIZE) {
        printf("Array is full!\n");
        return;
    }

    int value, position;
    printf("Enter value to insert: ");
    scanf("%d", &value);
    printf("Enter position (1 to %d): ", size + 1);
    scanf("%d", &position);

    if (position < 1 || position > size + 1) {
        printf("Invalid position.\n");
        return;
    }

    // Shift elements to the right to make space
    for (int i = size; i >= position; i--) {
        arr[i] = arr[i - 1];
    }

    arr[position - 1] = value;
    size++;

    printf("Element inserted successfully!\n");
    displayArray();
}

void deleteElement() {
    if (size == 0) {
        printf("Array is empty.\n");
        return;
    }

    int position;
    printf("Enter position to delete (1 to %d): ", size);
    scanf("%d", &position);

    if (position < 1 || position > size) {
        printf("Invalid position.\n");
        return;
    }

    // Shift elements to the left to fill the gap
    for (int i = position - 1; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }

    size--;

    printf("Element deleted successfully!\n");
    displayArray();
}

// ---------- Search operations ----------

void linearSearch() {
    if (size == 0) {
        printf("Array is empty.\n");
        return;
    }

    int key;
    printf("Enter value to search: ");
    scanf("%d", &key);

    for (int i = 0; i < size; i++) {
        if (arr[i] == key) {
            printf("Element %d found at position %d.\n", key, i + 1);
            return;
        }
    }

    printf("Element %d not found in the array.\n", key);
}

void binarySearch() {
    if (size == 0) {
        printf("Array is empty.\n");
        return;
    }

    // Work on a sorted copy so original array order isn't disturbed
    int temp[MAX_SIZE];
    for (int i = 0; i < size; i++) temp[i] = arr[i];

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (temp[j] > temp[j + 1]) {
                int t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }
    }

    int key;
    printf("Enter value to search: ");
    scanf("%d", &key);

    int low = 0, high = size - 1, found = 0;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (temp[mid] == key) {
            printf("Element %d found (array searched in sorted order).\n", key);
            found = 1;
            break;
        } else if (temp[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (!found) {
        printf("Element %d not found in the array.\n", key);
    }
}

// ---------- Sorting operations ----------

void bubbleSortAscending() {
    if (size == 0) {
        printf("Array is empty.\n");
        return;
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }

    printf("Array sorted in ascending order.\n");
    displayArray();
}

void bubbleSortDescending() {
    if (size == 0) {
        printf("Array is empty.\n");
        return;
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }

    printf("Array sorted in descending order.\n");
    displayArray();
}

// ---------- Analytical operations ----------

void reverseArray() {
    if (size == 0) {
        printf("Array is empty.\n");
        return;
    }

    int start = 0, end = size - 1;
    while (start < end) {
        int t = arr[start];
        arr[start] = arr[end];
        arr[end] = t;
        start++;
        end--;
    }

    printf("Array reversed.\n");
    displayArray();
}

void findMinMax() {
    if (size == 0) {
        printf("Array is empty.\n");
        return;
    }

    int min = arr[0], max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }

    printf("Minimum: %d\n", min);
    printf("Maximum: %d\n", max);
}

void sumAndAverage() {
    if (size == 0) {
        printf("Array is empty.\n");
        return;
    }

    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }

    printf("Sum    : %d\n", sum);
    printf("Average: %.2f\n", (float)sum / size);
}

void countEvenOdd() {
    if (size == 0) {
        printf("Array is empty.\n");
        return;
    }

    int evenCount = 0, oddCount = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) evenCount++;
        else oddCount++;
    }

    printf("Even numbers: %d\n", evenCount);
    printf("Odd numbers : %d\n", oddCount);
}

void removeDuplicates() {
    if (size == 0) {
        printf("Array is empty.\n");
        return;
    }

    int result[MAX_SIZE];
    int resultSize = 0;

    for (int i = 0; i < size; i++) {
        int isDuplicate = 0;
        for (int j = 0; j < resultSize; j++) {
            if (arr[i] == result[j]) {
                isDuplicate = 1;
                break;
            }
        }
        if (!isDuplicate) {
            result[resultSize++] = arr[i];
        }
    }

    for (int i = 0; i < resultSize; i++) {
        arr[i] = result[i];
    }
    size = resultSize;

    printf("Duplicates removed.\n");
    displayArray();
}

int main() {
    int choice;

    do {
        printf("\n===== ARRAY OPERATIONS MENU =====\n");
        printf("1.  Input Array\n");
        printf("2.  Display Array\n");
        printf("3.  Insert Element\n");
        printf("4.  Delete Element\n");
        printf("5.  Linear Search\n");
        printf("6.  Binary Search\n");
        printf("7.  Sort Ascending\n");
        printf("8.  Sort Descending\n");
        printf("9.  Reverse Array\n");
        printf("10. Find Min & Max\n");
        printf("11. Sum & Average\n");
        printf("12. Count Even & Odd\n");
        printf("13. Remove Duplicates\n");
        printf("14. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:  inputArray(); break;
            case 2:  displayArray(); break;
            case 3:  insertElement(); break;
            case 4:  deleteElement(); break;
            case 5:  linearSearch(); break;
            case 6:  binarySearch(); break;
            case 7:  bubbleSortAscending(); break;
            case 8:  bubbleSortDescending(); break;
            case 9:  reverseArray(); break;
            case 10: findMinMax(); break;
            case 11: sumAndAverage(); break;
            case 12: countEvenOdd(); break;
            case 13: removeDuplicates(); break;
            case 14: printf("Exiting program. Goodbye!\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 14);

    return 0;
}
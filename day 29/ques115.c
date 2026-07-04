/*Write a program to Create menu-driven
string operations system.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 200

char str[MAX_LEN];

// ---------- Basic operations ----------

void inputString() {
    getchar(); // clear leftover newline from previous scanf
    printf("Enter a string: ");
    fgets(str, MAX_LEN, stdin);
    str[strcspn(str, "\n")] = '\0';
    printf("String stored successfully!\n");
}

void displayString() {
    printf("Current string: \"%s\"\n", str);
}

void findLength() {
    printf("Length of string: %d\n", (int)strlen(str));
}

void reverseString() {
    int len = strlen(str);
    char reversed[MAX_LEN];

    for (int i = 0; i < len; i++) {
        reversed[i] = str[len - 1 - i];
    }
    reversed[len] = '\0';

    printf("Reversed string: %s\n", reversed);
}

void toUpperCase() {
    char result[MAX_LEN];
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        result[i] = toupper((unsigned char)str[i]);
    }
    result[len] = '\0';

    printf("Uppercase: %s\n", result);
}

void toLowerCase() {
    char result[MAX_LEN];
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        result[i] = tolower((unsigned char)str[i]);
    }
    result[len] = '\0';

    printf("Lowercase: %s\n", result);
}

// ---------- Analytical operations ----------

void checkPalindrome() {
    int len = strlen(str);
    int isPalindrome = 1;

    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            isPalindrome = 0;
            break;
        }
    }

    if (isPalindrome) {
        printf("\"%s\" is a palindrome.\n", str);
    } else {
        printf("\"%s\" is NOT a palindrome.\n", str);
    }
}

void countVowelsConsonants() {
    int vowels = 0, consonants = 0;
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        char ch = tolower((unsigned char)str[i]);
        if (isalpha((unsigned char)ch)) {
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
                vowels++;
            } else {
                consonants++;
            }
        }
    }

    printf("Vowels    : %d\n", vowels);
    printf("Consonants: %d\n", consonants);
}

void countWords() {
    int len = strlen(str);
    int wordCount = 0;
    int inWord = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] != ' ' && str[i] != '\t') {
            if (!inWord) {
                wordCount++;
                inWord = 1;
            }
        } else {
            inWord = 0;
        }
    }

    printf("Word count: %d\n", wordCount);
}

void charFrequency() {
    int count[256] = {0};
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        count[(unsigned char)str[i]]++;
    }

    printf("Character frequencies:\n");
    for (int i = 0; i < 256; i++) {
        if (count[i] > 0 && i != ' ') {
            printf("'%c' : %d\n", i, count[i]);
        }
    }
}

void firstNonRepeating() {
    int count[256] = {0};
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        count[(unsigned char)str[i]]++;
    }

    for (int i = 0; i < len; i++) {
        if (count[(unsigned char)str[i]] == 1) {
            printf("First non-repeating character: '%c'\n", str[i]);
            return;
        }
    }

    printf("No non-repeating character found.\n");
}

// ---------- Modification operations ----------

void removeSpaces() {
    char result[MAX_LEN];
    int len = strlen(str);
    int j = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] != ' ') {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';

    printf("Without spaces: %s\n", result);
}

void removeDuplicateChars() {
    int seen[256] = {0};
    char result[MAX_LEN];
    int len = strlen(str);
    int j = 0;

    for (int i = 0; i < len; i++) {
        unsigned char ch = (unsigned char)str[i];
        if (!seen[ch]) {
            seen[ch] = 1;
            result[j++] = str[i];
        }
    }
    result[j] = '\0';

    printf("Without duplicates: %s\n", result);
}

void findAndReplace() {
    char target, replacement;
    printf("Enter character to find: ");
    scanf(" %c", &target);
    printf("Enter replacement character: ");
    scanf(" %c", &replacement);

    char result[MAX_LEN];
    strcpy(result, str);
    int len = strlen(result);
    int replacedCount = 0;

    for (int i = 0; i < len; i++) {
        if (result[i] == target) {
            result[i] = replacement;
            replacedCount++;
        }
    }

    printf("After replacement: %s\n", result);
    printf("Replaced %d occurrence(s).\n", replacedCount);
}

void compressString() {
    int len = strlen(str);

    if (len == 0) {
        printf("String is empty.\n");
        return;
    }

    char result[MAX_LEN * 2];
    int resultIndex = 0;
    int count = 1;

    for (int i = 1; i <= len; i++) {
        if (i < len && str[i] == str[i - 1]) {
            count++;
        } else {
            result[resultIndex++] = str[i - 1];
            char countStr[12];
            sprintf(countStr, "%d", count);
            for (int j = 0; countStr[j] != '\0'; j++) {
                result[resultIndex++] = countStr[j];
            }
            count = 1;
        }
    }
    result[resultIndex] = '\0';

    printf("Compressed string: %s\n", result);
}

// ---------- Comparison operation (needs a second string) ----------

void checkAnagram() {
    char str2[MAX_LEN];
    getchar();
    printf("Enter second string to compare: ");
    fgets(str2, MAX_LEN, stdin);
    str2[strcspn(str2, "\n")] = '\0';

    int count[256] = {0};
    int len1 = strlen(str);
    int len2 = strlen(str2);

    if (len1 != len2) {
        printf("NOT anagrams (different lengths).\n");
        return;
    }

    for (int i = 0; i < len1; i++) {
        count[(unsigned char)tolower(str[i])]++;
    }
    for (int i = 0; i < len2; i++) {
        count[(unsigned char)tolower(str2[i])]--;
    }

    int isAnagram = 1;
    for (int i = 0; i < 256; i++) {
        if (count[i] != 0) {
            isAnagram = 0;
            break;
        }
    }

    if (isAnagram) {
        printf("\"%s\" and \"%s\" ARE anagrams.\n", str, str2);
    } else {
        printf("\"%s\" and \"%s\" are NOT anagrams.\n", str, str2);
    }
}

int main() {
    int choice;
    strcpy(str, ""); // start with an empty string

    do {
        printf("\n===== STRING OPERATIONS MENU =====\n");
        printf("Current string: \"%s\"\n", str);
        printf("1.  Input/Change String\n");
        printf("2.  Display String\n");
        printf("3.  Find Length\n");
        printf("4.  Reverse String\n");
        printf("5.  Convert to Uppercase\n");
        printf("6.  Convert to Lowercase\n");
        printf("7.  Check Palindrome\n");
        printf("8.  Count Vowels & Consonants\n");
        printf("9.  Count Words\n");
        printf("10. Character Frequency\n");
        printf("11. First Non-Repeating Character\n");
        printf("12. Remove Spaces\n");
        printf("13. Remove Duplicate Characters\n");
        printf("14. Find & Replace Character\n");
        printf("15. Compress String\n");
        printf("16. Check Anagram (with another string)\n");
        printf("17. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:  inputString(); break;
            case 2:  displayString(); break;
            case 3:  findLength(); break;
            case 4:  reverseString(); break;
            case 5:  toUpperCase(); break;
            case 6:  toLowerCase(); break;
            case 7:  checkPalindrome(); break;
            case 8:  countVowelsConsonants(); break;
            case 9:  countWords(); break;
            case 10: charFrequency(); break;
            case 11: firstNonRepeating(); break;
            case 12: removeSpaces(); break;
            case 13: removeDuplicateChars(); break;
            case 14: findAndReplace(); break;
            case 15: compressString(); break;
            case 16: checkAnagram(); break;
            case 17: printf("Exiting program. Goodbye!\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 17);

    return 0;
}
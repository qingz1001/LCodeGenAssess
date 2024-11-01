#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS 6

const char *numbers[] = {
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
    "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen",
    "eighteen", "nineteen", "twenty", "a", "both", "another", "first", "second", "third"
};

const int values[] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 1, 2, 1, 1, 2, 3
};

int main() {
    char sentence[100];
    fgets(sentence, sizeof(sentence), stdin);
    sentence[strcspn(sentence, "\n")] = '\0'; // Remove newline character

    char *words[MAX_WORDS];
    int num_words = 0;

    // Tokenize the sentence into words
    char *token = strtok(sentence, " ");
    while (token != NULL && num_words < MAX_WORDS) {
        words[num_words++] = token;
        token = strtok(NULL, " ");
    }

    int digits[MAX_WORDS];
    int num_digits = 0;

    // Convert words to corresponding numbers and calculate their squared modulo 100
    for (int i = 0; i < num_words; i++) {
        for (int j = 0; j < sizeof(numbers) / sizeof(numbers[0]); j++) {
            if (strcmp(words[i], numbers[j]) == 0) {
                int value = values[j];
                int squared = (value * value) % 100;
                digits[num_digits++] = squared;
                break;
            }
        }
    }

    // Sort the digits to find the smallest permutation
    for (int i = 0; i < num_digits - 1; i++) {
        for (int j = i + 1; j < num_digits; j++) {
            if (digits[i] > digits[j]) {
                int temp = digits[i];
                digits[i] = digits[j];
                digits[j] = temp;
            }
        }
    }

    // Form the smallest number from the sorted digits
    int result = 0;
    for (int i = 0; i < num_digits; i++) {
        if (digits[i] < 10) {
            result = result * 10 + digits[i];
        } else {
            result = result * 100 + digits[i];
        }
    }

    printf("%d\n", result);

    return 0;
}
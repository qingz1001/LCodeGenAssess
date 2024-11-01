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

int find_value(const char *word) {
    for (int i = 0; i < sizeof(numbers) / sizeof(numbers[0]); i++) {
        if (strcmp(word, numbers[i]) == 0) {
            return values[i];
        }
    }
    return -1;
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    char sentence[100];
    fgets(sentence, sizeof(sentence), stdin);

    char *words[MAX_WORDS];
    int num_words = 0;

    char *token = strtok(sentence, " \n");
    while (token != NULL && num_words < MAX_WORDS) {
        words[num_words++] = token;
        token = strtok(NULL, " \n");
    }

    int digits[MAX_WORDS];
    int num_digits = 0;

    for (int i = 0; i < num_words; i++) {
        int value = find_value(words[i]);
        if (value != -1) {
            int square = value * value % 100;
            digits[num_digits++] = square;
        }
    }

    qsort(digits, num_digits, sizeof(int), compare);

    if (num_digits == 0) {
        printf("0\n");
        return 0;
    }

    char result[20] = {0};
    for (int i = 0; i < num_digits; i++) {
        char temp[3];
        sprintf(temp, "%02d", digits[i]);
        strcat(result, temp);
    }

    // Remove leading zeros
    int start = 0;
    while (result[start] == '0' && result[start + 1] != '\0') {
        start++;
    }

    printf("%s\n", result + start);

    return 0;
}
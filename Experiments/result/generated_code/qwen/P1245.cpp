#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 20
#define MAX_PHONE_NUMBER_LENGTH 100

const char* phone_to_letters[] = {
    "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};

int is_valid_word(const char* word, const char* phone_number) {
    int len = strlen(word);
    if (len != strlen(phone_number)) return 0;
    for (int i = 0; i < len; ++i) {
        int digit = phone_number[i] - '0';
        int letter_index = word[i] - 'a';
        if (letter_index >= 3 && letter_index <= 8) {
            if (strchr(phone_to_letters[digit], word[i]) == NULL) return 0;
        } else {
            return 0;
        }
    }
    return 1;
}

void translate_phone_number(int n, const char* phone_number, const char* words[], int max_words) {
    int found = 0;
    for (int i = 0; i < n; ++i) {
        if (is_valid_word(words[i], phone_number)) {
            if (!found) {
                printf("%s", words[i]);
                found = 1;
            } else {
                printf(" %s", words[i]);
            }
        }
    }
    if (!found) {
        printf("No Solutions!");
    }
    printf("\n");
}

int main() {
    int n;
    scanf("%d", &n);
    char phone_number[MAX_PHONE_NUMBER_LENGTH];
    scanf("%s", phone_number);

    char words[MAX_WORDS][MAX_WORD_LENGTH + 1];
    for (int i = 0; i < n; ++i) {
        scanf("%s", words[i]);
    }

    translate_phone_number(n, phone_number, words, n);

    return 0;
}
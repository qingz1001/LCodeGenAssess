#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LEN 1005

int is_name(char *word) {
    if (!isupper(word[0])) return 0;
    for (int i = 1; word[i] && !ispunct(word[i]); i++) {
        if (isupper(word[i])) return 0;
    }
    return 1;
}

int count_names(char *sentence) {
    int count = 0;
    char *word = strtok(sentence, " ");
    while (word) {
        if (is_name(word)) count++;
        word = strtok(NULL, " ");
    }
    return count;
}

int main() {
    int N;
    scanf("%d\n", &N);

    char input[MAX_LEN];
    fgets(input, MAX_LEN, stdin);
    input[strcspn(input, "\n")] = 0;

    char *sentence = strtok(input, ".?!");
    while (sentence) {
        printf("%d\n", count_names(sentence));
        sentence = strtok(NULL, ".?!");
    }

    return 0;
}
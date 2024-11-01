#include <stdio.h>
#include <ctype.h>
#include <string.h>

int is_name(char *word) {
    if (!isupper(word[0])) return 0;
    for (int i = 1; word[i]; i++) {
        if (!islower(word[i])) return 0;
    }
    return 1;
}

int count_names_in_sentence(char *sentence) {
    int count = 0;
    char *word = strtok(sentence, " ");
    while (word != NULL) {
        if (is_name(word)) count++;
        word = strtok(NULL, " ");
    }
    return count;
}

int main() {
    int N;
    scanf("%d", &N);
    getchar(); // consume the newline character after the number

    char sentences[1001];
    fgets(sentences, sizeof(sentences), stdin);

    char *sentence = strtok(sentences, ".?!");
    while (sentence != NULL) {
        printf("%d\n", count_names_in_sentence(sentence));
        sentence = strtok(NULL, ".?!");
    }

    return 0;
}
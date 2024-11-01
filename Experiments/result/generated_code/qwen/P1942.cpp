#include <stdio.h>
#include <string.h>

#define MAX_N 1000
#define MAX_WORDS 2001

int n;
char words[MAX_WORDS][MAX_N + 1];
int word_count;

int is_valid(char *word) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (word[i] == '1') {
            sum++;
        }
    }
    return sum % (n + 1) == 0 || sum == 0;
}

void insert_zero(char *word, int pos) {
    for (int i = n; i > pos; i--) {
        word[i] = word[i - 1];
    }
    word[pos] = '0';
    n++;
}

void delete_char(char *word, int pos) {
    for (int i = pos; i < n - 1; i++) {
        word[i] = word[i + 1];
    }
    n--;
}

void replace_one_with_zero(char *word, int pos) {
    word[pos] = '0';
}

void restore_word(char *word) {
    for (int i = 0; i < n; i++) {
        if (word[i] == '1' && (i + 1) % (n + 1) != 0) {
            replace_one_with_zero(word, i);
            return;
        }
    }

    for (int i = 0; i < n; i++) {
        if (word[i] == '0') {
            insert_zero(word, i);
            return;
        }
    }

    for (int i = 0; i < n; i++) {
        if (word[i] == '1') {
            delete_char(word, i);
            return;
        }
    }

    // If no operation can be performed, the word cannot be restored.
    printf("-1\n");
}

int main() {
    scanf("%d", &n);

    while (scanf("%s", words[word_count]) != EOF) {
        word_count++;
    }

    for (int i = 0; i < word_count; i++) {
        if (!is_valid(words[i])) {
            printf("-1\n");
            continue;
        }
        restore_word(words[i]);
        printf("%s\n", words[i]);
    }

    return 0;
}
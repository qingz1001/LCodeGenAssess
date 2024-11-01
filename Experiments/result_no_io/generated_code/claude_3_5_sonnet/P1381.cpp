#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 1001
#define MAX_M 100001
#define MAX_LEN 11

char words[MAX_N][MAX_LEN];
char article[MAX_M][MAX_LEN];
int n, m;

int is_word_in_list(char *word) {
    for (int i = 0; i < n; i++) {
        if (strcmp(word, words[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", words[i]);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%s", article[i]);
    }

    int max_words = 0;
    int min_length = m;
    int left = 0, right = 0;
    int count = 0;
    int word_found[MAX_N] = {0};

    while (right < m) {
        if (is_word_in_list(article[right]) && !word_found[is_word_in_list(article[right]) - 1]) {
            word_found[is_word_in_list(article[right]) - 1] = 1;
            count++;
        }

        while (count >= max_words) {
            if (count > max_words || (count == max_words && right - left + 1 < min_length)) {
                max_words = count;
                min_length = right - left + 1;
            }

            if (is_word_in_list(article[left]) && word_found[is_word_in_list(article[left]) - 1]) {
                word_found[is_word_in_list(article[left]) - 1] = 0;
                count--;
            }
            left++;
        }
        right++;
    }

    printf("%d\n%d\n", max_words, min_length);

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LEN 11
#define MAX_N 1001
#define MAX_M 100001

char words[MAX_N][MAX_WORD_LEN];
char article[MAX_M][MAX_WORD_LEN];
int word_count[MAX_N];

int n, m;

int is_word_to_learn(char *word) {
    for (int i = 0; i < n; i++) {
        if (strcmp(words[i], word) == 0) {
            return i;
        }
    }
    return -1;
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

    int left = 0, right = 0;
    int max_words = 0, min_length = m;
    int current_words = 0;

    while (right < m) {
        int word_index = is_word_to_learn(article[right]);
        if (word_index != -1) {
            if (word_count[word_index] == 0) {
                current_words++;
            }
            word_count[word_index]++;
        }

        while (current_words == max_words && left <= right) {
            if (right - left + 1 < min_length) {
                min_length = right - left + 1;
            }
            
            int left_word_index = is_word_to_learn(article[left]);
            if (left_word_index != -1) {
                word_count[left_word_index]--;
                if (word_count[left_word_index] == 0) {
                    current_words--;
                }
            }
            left++;
        }

        if (current_words > max_words) {
            max_words = current_words;
            min_length = right - left + 1;
        }

        right++;
    }

    printf("%d\n%d\n", max_words, min_length);

    return 0;
}
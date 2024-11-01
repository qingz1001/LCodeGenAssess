#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ELEMENT_LEN 11
#define MAX_ELEMENTS 201
#define MAX_SEQ_LEN 200001

char elements[MAX_ELEMENTS][MAX_ELEMENT_LEN];
int element_count = 0;
char sequence[MAX_SEQ_LEN];
bool dp[MAX_SEQ_LEN];

int max(int a, int b) {
    return a > b ? a : b;
}

int longest_prefix() {
    int seq_len = strlen(sequence);
    memset(dp, 0, sizeof(dp));
    dp[0] = true;

    int max_len = 0;
    for (int i = 1; i <= seq_len; i++) {
        for (int j = 0; j < element_count; j++) {
            int elem_len = strlen(elements[j]);
            if (i >= elem_len && strncmp(sequence + i - elem_len, elements[j], elem_len) == 0 && dp[i - elem_len]) {
                dp[i] = true;
                max_len = i;
                break;
            }
        }
    }

    return max_len;
}

int main() {
    char input[MAX_ELEMENT_LEN];
    while (scanf("%s", input) == 1 && input[0] != '.') {
        strcpy(elements[element_count++], input);
    }

    int seq_index = 0;
    while (scanf("%s", input) == 1) {
        strcat(sequence + seq_index, input);
        seq_index += strlen(input);
    }

    printf("%d\n", longest_prefix());
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_P 200
#define MAX_LEN 200000
#define MAX_ELEM_LEN 10

char elements[MAX_P][MAX_ELEM_LEN + 1];
int element_count = 0;
char sequence[MAX_LEN + 1];
bool dp[MAX_LEN + 1];

int main() {
    char line[100];
    while (fgets(line, sizeof(line), stdin) && line[0] != '.') {
        char *token = strtok(line, " \n");
        while (token != NULL) {
            strcpy(elements[element_count++], token);
            token = strtok(NULL, " \n");
        }
    }

    int seq_len = 0;
    while (fgets(line, sizeof(line), stdin)) {
        strcat(sequence + seq_len, line);
        seq_len += strlen(line);
    }
    sequence[seq_len - 1] = '\0'; // Remove the trailing newline
    seq_len--;

    dp[0] = true;
    int max_prefix_len = 0;

    for (int i = 0; i <= seq_len; i++) {
        if (dp[i]) {
            for (int j = 0; j < element_count; j++) {
                int elem_len = strlen(elements[j]);
                if (i + elem_len <= seq_len && strncmp(sequence + i, elements[j], elem_len) == 0) {
                    dp[i + elem_len] = true;
                    if (i + elem_len > max_prefix_len) {
                        max_prefix_len = i + elem_len;
                    }
                }
            }
        }
    }

    printf("%d\n", max_prefix_len);

    return 0;
}
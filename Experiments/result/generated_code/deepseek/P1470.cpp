#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_P 200
#define MAX_LEN 10
#define MAX_S 200000

char P[MAX_P][MAX_LEN + 1];
int P_size = 0;
char S[MAX_S + 1];
bool dp[MAX_S + 1];

int main() {
    char line[100];
    while (fgets(line, sizeof(line), stdin) && line[0] != '.') {
        char *token = strtok(line, " \n");
        while (token != NULL) {
            strcpy(P[P_size++], token);
            token = strtok(NULL, " \n");
        }
    }

    int S_len = 0;
    while (fgets(line, sizeof(line), stdin)) {
        strcat(S + S_len, line);
        S_len += strlen(line) - 1; // -1 to remove newline
    }
    S[S_len] = '\0';

    dp[0] = true;
    int max_prefix = 0;

    for (int i = 0; i <= S_len; i++) {
        if (dp[i]) {
            for (int j = 0; j < P_size; j++) {
                int len = strlen(P[j]);
                if (i + len <= S_len && strncmp(S + i, P[j], len) == 0) {
                    dp[i + len] = true;
                    if (i + len > max_prefix) {
                        max_prefix = i + len;
                    }
                }
            }
        }
    }

    printf("%d\n", max_prefix);
    return 0;
}
#include <stdio.h>
#include <string.h>

#define MAX_LEN 100001
#define MAX_ELEMENT_LEN 11

int main() {
    char elements[MAX_LEN][MAX_ELEMENT_LEN];
    int element_count = 0;
    char s[MAX_LEN];
    int s_length = 0;

    // Read the set of elements
    while (1) {
        scanf("%s", elements[element_count]);
        if (strcmp(elements[element_count], ".") == 0) break;
        element_count++;
    }

    // Read the sequence s
    char line[80];
    while (fgets(line, sizeof(line), stdin)) {
        for (int i = 0; i < strlen(line); i++) {
            if (line[i] != '\n') {
                s[s_length++] = line[i];
            }
        }
    }

    // Initialize DP array
    int dp[MAX_LEN] = {0};

    // Fill the DP array
    for (int i = 1; i <= s_length; i++) {
        for (int j = 0; j < element_count; j++) {
            int len = strlen(elements[j]);
            if (i >= len && strcmp(s + i - len, elements[j]) == 0) {
                dp[i] = dp[i - len] + len;
                break;
            }
        }
    }

    // Output the result
    printf("%d\n", dp[s_length]);

    return 0;
}